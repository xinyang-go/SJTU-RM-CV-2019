#!/bin/sh

exe=$1
while true; do
	state=`ps aux | grep "$1" | grep -v grep | grep -v $0`
	if [ ! "$state" ]; then
		exec $exe &
		echo "restart $exe"
	fi
	sleep 2
done
