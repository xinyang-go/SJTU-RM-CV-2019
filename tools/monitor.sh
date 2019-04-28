#!/bin/sh

# usage: monitor.sh "<the exe file's absolute path and its shell parameter>"
# And then when ever the exe shutdonw it will be automatically restart

exe=$1
while true; do
	state=`ps aux | grep "$1" | grep -v grep | grep -v $0`
	if [ ! "$state" ]; then
		exec $exe &
		echo "restart $exe"
	fi
	sleep 2
done
