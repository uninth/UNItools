#!/bin/sh
#
#

nipper --fw1 --input=$FWDIR/conf --output=/tmp/nipper-out.tmp
iconv -f latin1 -t utf8 /tmp/nipper-out.tmp > /tmp/`hostname`.html
/bin/rm -f /tmp/nipper-out.tmp

