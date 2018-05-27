#!/bin/bash

if [ ! -d /home/s/logs/history ]; then
	mkdir /home/s/logs/history
fi

cd $(dirname $0) && cd ..
idc=$(hostname |awk -F "." '{printf $3}')
conf_file="./conf/bloomd_server.$idc.master.conf"

if [ -e $conf_file ]; then
	cp -f $conf_file ./conf/bloomd_server.conf
	if ps -ef | grep nginx | grep -v grep; then
		/home/s/apps/openresty/nginx/sbin/nginx -p . -s reload
	else
		/home/s/apps/openresty/nginx/sbin/nginx -p .
	fi
else
	echo "missing config: " $conf_file
fi
