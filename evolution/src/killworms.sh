#!/bin/sh

ps -U evouser | awk '{ print $1 }' > /tmp/killworms.sh.2.tmp
lc=`wc -l /tmp/killworms.sh.2.tmp | awk '{ print $1 }'`
tail -n `expr $lc - 1` /tmp/killworms.sh.2.tmp > /tmp/killworms.sh.tmp
ps -U ewwuser | awk '{ print $1 }' > /tmp/killworms.sh.2.tmp
lc=`wc -l /tmp/killworms.sh.2.tmp | awk '{ print $1 }'`
tail -n `expr $lc - 1` /tmp/killworms.sh.2.tmp >> /tmp/killworms.sh.tmp
while test -s /tmp/killworms.sh.tmp; do
	kill -9 `cat /tmp/killworms.sh.tmp`
	ps -U evouser | awk '{ print $1 }' > /tmp/killworms.sh.2.tmp
	lc=`wc -l /tmp/killworms.sh.2.tmp | awk '{ print $1 }'`
	tail -n `expr $lc - 1` /tmp/killworms.sh.2.tmp > /tmp/killworms.sh.tmp
done
