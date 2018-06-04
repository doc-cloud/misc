/*******************************************************************************
#                                                                              #
#      MJPG-streamer allows to stream JPG frames from an input-plugin          #
#      to several output plugins                                               #
#                                                                              #
#      Copyright (C) 2007 Tom Stöveken                                         #
#                                                                              #
# This program is free software; you can redistribute it and/or modify         #
# it under the terms of the GNU General Public License as published by         #
# the Free Software Foundation; version 2 of the License.                      #
#                                                                              #
# This program is distributed in the hope that it will be useful,              #
# but WITHOUT ANY WARRANTY; without even the implied warranty of               #
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                #
# GNU General Public License for more details.                                 #
#                                                                              #
# You should have received a copy of the GNU General Public License            #
# along with this program; if not, write to the Free Software                  #
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA    #
#                                                                              #
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <linux/videodev.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <signal.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <getopt.h>
#include <pthread.h>
#include <dlfcn.h>
#include <fcntl.h>
#include <syslog.h>

#include "utils.h"
#include "mjpg_streamer.h"

/* globals */
static globals global;

/******************************************************************************
Description.: Display a help message
Input Value.: argv[0] is the program name and the parameter progname
Return Value: -
******************************************************************************/
void help(char *progname)
{
  fprintf(stderr, "-----------------------------------------------------------------------\n");
  fprintf(stderr, "Usage: %s\n" \
                  "  -i | --input \"<input-plugin.so> [parameters]\"\n" \
                  "  -o | --output \"<output-plugin.so> [parameters]\"\n" \
                  " [-h | --help ]........: display this help\n" \
                  " [-v | --version ].....: display version information\n" \
                  " [-b | --background]...: fork to the background, daemon mode\n", progname);
  fprintf(stderr, "-----------------------------------------------------------------------\n");
  fprintf(stderr, "Example #1:\n" \
                  " To open an UVC webcam \"/dev/video1\" and stream it via HTTP:\n" \
                  "  %s -i \"input_uvc.so -d /dev/video1\" -o \"output_http.so\"\n", progname);
  fprintf(stderr, "-----------------------------------------------------------------------\n");
  fprintf(stderr, "Example #2:\n" \
                  " To open an UVC webcam and stream via HTTP port 8090:\n" \
                  "  %s -i \"input_uvc.so\" -o \"output_http.so -p 8090\"\n", progname);
  fprintf(stderr, "-----------------------------------------------------------------------\n");
  fprintf(stderr, "Example #3:\n" \
                  " To get help for a certain input plugin:\n" \
                  "  %s -i \"input_uvc.so --help\"\n", progname);
  fprintf(stderr, "-----------------------------------------------------------------------\n");
  fprintf(stderr, "In case the modules (=plugins) can not be found:\n" \
                  " * Set the default search path for the modules with:\n" \
                  "   export LD_LIBRARY_PATH=/path/to/plugins,\n" \
                  " * or put the plugins into the \"/lib/\" or \"/usr/lib\" folder,\n" \
                  " * or instead of just providing the plugin file name, use a complete\n" \
                  "   path and filename:\n" \
                  "   %s -i \"/path/to/modules/input_uvc.so\"\n", progname);
  fprintf(stderr, "-----------------------------------------------------------------------\n");
}

/******************************************************************************
Description.: pressing CTRL+C sends signals to this process instead of just
              killing it plugins can tidily shutdown and free allocated
              ressources. The function prototype is defined by the system,
              because it is a callback function.
Input Value.: sig tells us which signal was received
Return Value: -
******************************************************************************/
void signal_handler(int sig)
{
  int i;

  /* signal "stop" to threads */
  LOG("setting signal to stop\n");
  global.stop = 1;
  usleep(1000*1000);

  /* clean up threads */
  LOG("force cancelation of threads and cleanup ressources\n");
  global.in.stop();
  for(i=0; i<global.outcnt; i++) {
    global.out[i].stop(global.out[i].param.id);
  }
  usleep(1000*1000);

  /* close handles of input plugins */
  dlclose(&global.in.handle);
  for(i=0; i<global.outcnt; i++) {
    /* skip = 0;
    DBG("about to decrement usage counter for handle of %s, id #%02d, handle: %p\n", \
        global.out[i].plugin, global.out[i].param.id, global.out[i].handle);
    for(j=i+1; j<global.outcnt; j++) {
      if ( global.out[i].handle == global.out[j].handle ) {
        DBG("handles are pointing to the same destination (%p == %p)\n", global.out[i].handle, global.out[j].handle);
        skip = 1;
      }
    }
    if ( skip ) {
      continue;
    }

    DBG("closing handle %p\n", global.out[i].handle);
    */
    dlclose(global.out[i].handle);
  }
  DBG("all plugin handles closed\n");

  pthread_cond_destroy(&global.db_update);
  pthread_mutex_destroy(&global.db);

  LOG("done\n");

  closelog();
  exit(0);
  return;
}

/******************************************************************************
Description.: 
Input Value.: 
Return Value: 
******************************************************************************/
int main(int argc, char *argv[])
{
	char *input  = "input_uvc.so --resolution 640x480 --fps 5 --device /dev/video0";	// ָ������ѡ��Ĳ����ַ���
	char *output[MAX_OUTPUT_PLUGINS];	/* ָ�����ѡ��Ĳ����ַ��� */
	int daemon=0, i;						/* �Ƿ��ó����ں�̨���еı�־ */
	size_t tmp=0;

	output[0] = "output_http.so --port 8080";
	global.outcnt = 0;							/* ��ʱ���ͨ���м��ַ�ʽ, 0 */

	/* parameter parsing */
	/* ��������(�ؼ��ǿ��� getopt_long_only ����) */
	/*
	getopt_long_only():
		���ڽ���������ѡ��
	��������:
		�ڶ�������:ֱ�Ӵ�main�������ݶ���,��ʾ���Ǵ��˵Ĳ���
		����������:��ѡ���ַ���
		���ĸ�����:�� struct option ����,���ڴ�ų�ѡ�����
		���������:���ڷ��س�ѡ����longopts�ṹ�������е�����ֵ
	����ֵ:
		������ϣ�����-1
		����δ����ĳ�ѡ����߶�ѡ�getopt_long���أ�

	ע��:
		��ѡ������'-'
	*/
	while(1)
	{
		int option_index = 0, c=0;
		static struct option long_options[] = \
		{
			{"h", no_argument, 0, 0},
			{"help", no_argument, 0, 0},
			{"i", required_argument, 0, 0},
			{"input", required_argument, 0, 0},
			{"o", required_argument, 0, 0},
			{"output", required_argument, 0, 0},
			{"v", no_argument, 0, 0},
			{"version", no_argument, 0, 0},
			{"b", no_argument, 0, 0},
			{"background", no_argument, 0, 0},
			{0, 0, 0, 0}
		};

		/* argv = " -i "input_uvc.so -f 10 -r 320*240" -o "output_http.so -w www" " */
		c = getopt_long_only(argc, argv, "", long_options, &option_index);

		/* no more options to parse */
		/* ����������� */
		if (c == -1)
			break;

		/* unrecognized option */
		/* ������˵Ĳ�������ȷ,���ӡ������Ϣ */
		if(c=='?')
		{
			help(argv[0]);
			return 0;
		}

		switch (option_index)
		{
			/* h, help */
			case 0:
			case 1:
			help(argv[0]);
			return 0;
			break;

			/* i, input */
			case 2:
			case 3:
				input = strdup(optarg);	// input = "input_uvc.so -f 10 -r 320*240"
				break;

			/* o, output */
			case 4:
			case 5:
				output[global.outcnt++] = strdup(optarg);	// output[0] = "output_http.so -w www"
				break;

			/* v, version */
			case 6:
			case 7:
			printf("MJPG Streamer Version: %s\n" \
			"Compilation Date.....: %s\n" \
			"Compilation Time.....: %s\n", SOURCE_VERSION, __DATE__, __TIME__);
			return 0;
			break;

			/* b, background */
			case 8:
			case 9:
			daemon=1;
			break;

			default:
			help(argv[0]);
			return 0;
		}
	}

	/* ��һ�������ϵͳ��¼�������� */
	openlog("MJPG-streamer ", LOG_PID|LOG_CONS, LOG_USER);
	//openlog("MJPG-streamer ", LOG_PID|LOG_CONS|LOG_PERROR, LOG_USER);
	syslog(LOG_INFO, "starting application");		// �� "starting application" �ַ���д��ϵͳ��¼��

	/* fork to the background */
	/* ���daemon = 1,���ó����ں�̨���� */
	if ( daemon )
	{
		LOG("enabling daemon mode");
		daemon_mode();
	}

	/* initialise the global variables */
	/* ��ʼ�� global �еĳ�Ա */
	global.stop      = 0;
	global.buf       = NULL;
	global.size      = 0;
	global.in.plugin = NULL;

	/* this mutex and the conditional variable are used to synchronize access to the global picture buffer */
	if( pthread_mutex_init(&global.db, NULL) != 0 )		/* ��ʼ�� global.db ��Ա */
	{
		LOG("could not initialize mutex variable\n");
		closelog();
		exit(EXIT_FAILURE);
	}
	if( pthread_cond_init(&global.db_update, NULL) != 0 )	/* ��ʼ�� global.db_update(��������) ��Ա */
	{
		LOG("could not initialize condition variable\n");
		closelog();
		exit(EXIT_FAILURE);
	}

	/* ignore SIGPIPE (send by OS if transmitting to closed TCP sockets) */
	signal(SIGPIPE, SIG_IGN);		/* ���� SIGPIPE �ź� */

	/* register signal handler for <CTRL>+C in order to clean up */
	/*
		�����ǰ��� <CTRL>+C ʱ,�����signal_handler()����,��һЩ������
	*/
	if (signal(SIGINT, signal_handler) == SIG_ERR)
	{
		LOG("could not register signal handler\n");
		closelog();
		exit(EXIT_FAILURE);
	}

	/*
	* messages like the following will only be visible on your terminal
	* if not running in daemon mode
	*/
	LOG("MJPG Streamer Version.: %s\n", SOURCE_VERSION);		// ��ӡ�� MJPG Streamer �汾��

	/* check if at least one output plugin was selected */
	if ( global.outcnt == 0 )	// ��������ʽ������Ϊ0,������Ϊ1
	{
		/* no? Then use the default plugin instead */
		global.outcnt = 1;
	}

	/* open input plugin */
	/* "input_uvc.so -f 10 -r 320*240" */
	tmp = (size_t)(strchr(input, ' ')-input);		// ��tmp ���� "input_uvc.so"�ַ����ĳ���
	global.in.plugin = (tmp > 0)?strndup(input, tmp):strdup(input);	// global.in.plugin = "input_uvc.so"
	global.in.handle = dlopen(global.in.plugin, RTLD_LAZY);			// �� "input_uvc.so" �����̬���ӿ�
	if ( !global.in.handle )
	{
		LOG("ERROR: could not find input plugin\n");
		LOG("       Perhaps you want to adjust the search path with:\n");
		LOG("       # export LD_LIBRARY_PATH=/path/to/plugin/folder\n");
		LOG("       dlopen: %s\n", dlerror() );
		closelog();
		exit(EXIT_FAILURE);
	}
	global.in.init = dlsym(global.in.handle, "input_init");	// �� global.in.init = input_init
	if ( global.in.init == NULL )
	{
		LOG("%s\n", dlerror());
		exit(EXIT_FAILURE);
	}
	global.in.stop = dlsym(global.in.handle, "input_stop");	// �� global.in.stop = input_stop
	if ( global.in.stop == NULL )
	{
		LOG("%s\n", dlerror());
		exit(EXIT_FAILURE);
	}
	global.in.run = dlsym(global.in.handle, "input_run");	// �� global.in.run = input_run
	if ( global.in.run == NULL )
	{
		LOG("%s\n", dlerror());
		exit(EXIT_FAILURE);
	}
	/* try to find optional command */
	global.in.cmd = dlsym(global.in.handle, "input_cmd");	// global.in.cmd = input_cmd

	global.in.param.parameter_string = strchr(input, ' ');		// global.in.param.parameter_string = "-f 10 -r 320*240"
	global.in.param.global = &global;

	if ( global.in.init(&global.in.param) )		// ����input_uvc.c�е�input_init(&global.in.param)����
	{
		LOG("input_init() return value signals to exit");
		closelog();
		exit(0);
	}

	/* open output plugin */
	for (i=0; i<global.outcnt; i++)		// outcnt = 1
	{
		/* "output_http.so -w www" */
		tmp = (size_t)(strchr(output[i], ' ')-output[i]);		// ��tmp ���� "output_http.so"�ַ����ĳ���
		global.out[i].plugin = (tmp > 0)?strndup(output[i], tmp):strdup(output[i]);	// �� global.out[i].plugin = "output_http.so"
		global.out[i].handle = dlopen(global.out[i].plugin, RTLD_LAZY);	// �� "output_http.so" ��̬���ӿ�
		if ( !global.out[i].handle )
		{
			LOG("ERROR: could not find output plugin %s\n", global.out[i].plugin);
			LOG("       Perhaps you want to adjust the search path with:\n");
			LOG("       # export LD_LIBRARY_PATH=/path/to/plugin/folder\n");
			LOG("       dlopen: %s\n", dlerror() );
			closelog();
			exit(EXIT_FAILURE);
		}
		global.out[i].init = dlsym(global.out[i].handle, "output_init");		// �� global.out[i].init = output_init
		if ( global.out[i].init == NULL )
		{
			LOG("%s\n", dlerror());
			exit(EXIT_FAILURE);
		}
		global.out[i].stop = dlsym(global.out[i].handle, "output_stop");	// �� global.out[i].stop = output_stop
		if ( global.out[i].stop == NULL )
		{
			LOG("%s\n", dlerror());
			exit(EXIT_FAILURE);
		}
		global.out[i].run = dlsym(global.out[i].handle, "output_run");		// �� global.out[i].run = output_run
		if ( global.out[i].run == NULL )
		{
			LOG("%s\n", dlerror());
			exit(EXIT_FAILURE);
		}
		/* try to find optional command */
		global.out[i].cmd = dlsym(global.out[i].handle, "output_cmd");	// �� global.out[i].cmd = output_cmd

		global.out[i].param.parameter_string = strchr(output[i], ' ');	// �� global.out[i].param.parameter_string = "-w www"
		global.out[i].param.global = &global;
		global.out[i].param.id = i;
		if ( global.out[i].init(&global.out[i].param) )	// ���� output_http.c�е�output_init(&global.out[i].param)����
		{
			LOG("output_init() return value signals to exit");
			closelog();
			exit(0);
		}
	}

	/* start to read the input, push pictures into global buffer */
	DBG("starting input plugin\n");			// ��ӡ������Ϣ "starting input plugin\n"
	syslog(LOG_INFO, "starting input plugin");	// �� "starting input plugin" �ַ���д����¼����
	global.in.run();		// ���� input_uvc.c�е�input_run����

	DBG("starting %d output plugin(s)\n", global.outcnt);	// ��ӡ������Ϣ
	for(i=0; i<global.outcnt; i++)
	{
		syslog(LOG_INFO, "starting output plugin: %s (ID: %02d)", global.out[i].plugin, global.out[i].param.id);
		global.out[i].run(global.out[i].param.id);		// ���� output_http.c �е� output_run ����
	}

	/* wait for signals */
	pause();			// ����ȴ��źŵķ���

	return 0;
}
