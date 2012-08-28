#!/bin/sh
#
# fw1-dump.sh
#
# Description: "tcpdump"-like wrapper for "fw monitor"
#
# (P) & (C) 2007-2013 by AERAsec Network Services & Security GmbH <info@aerasec.de>
#                   Peter Bieringer <pbieringer@aerasec.de> (PB)
#
# $Id$
# $Release: 1.0.0
#
# License: GNU General Public License v2
#
# Changes:
# 20070124/PB: initial creation
# 20070125/PB: add support for command line options (-w, -s)
# 20070126/PB: add support for "not"
# 20070129/PB: add selftest, fix parser output, add more options, review
# 20070129/PB: fix mapping of option -X
# 20070212/PB: add version information, set to 1.0.0
#
# Known issues/limitations:
# 20070129/PB: support of other layer 3 protocols than IPv4 is missing
#
# Tested platforms:
# 20070129/PB: Fedora Core 6 (development)
# 20070129/PB: Secure Platform R61
# 20070129/PB: Nokia IPSO 3.7.1


# native 'fw monitor' options:
#
# Usage: fw monitor [- u|s] [-i] [-d] [-T] <{-e expr}+|-f <filter-file|->> [-l len] [-m mask]  [-x offset[,len]] [-o <file>] <[-pi pos] [-pI pos] [-po pos] [-pO pos] | -p all [-a ]> [-ci count] [-co count]
#
# Currently supported:
#
# fw monitor		tcpdump			fwdump.sh
# [-o <file>]		[-w <file>]		[-w <file>]
# [-l len]		[-s len]		[-s len]
# [-ci count]		[-c count]		[-c count]
# [-p all]					[-p all]


##### Default values #####
log_level="6"	# (according to sys/syslog.h)

file_services="/etc/services"
file_protocols="/etc/protocols"

##### Functions #####

## Simple logging
log() {
	local level="$1"
	local message="$2"

	if [ $level -gt $log_level ]; then
		return
	fi

	case $level in
	    7)
		local level="DEBUG "
		;;
	    6)
		local level="INFO  "
		;;
	    5)
		local level="NOTICE"
		;;
	    4)
		local level="WARN  "
		;;
	    3)
		local level="ERROR "
		;;
	    2)
		local level="CRIT  "
		;;
	    1)
		local level="ALERT "
		;;
	    0)
		local level="EMERG "
		;;
	esac

	echo "$level: $message" >&2
}

## Version
print_version() {
	echo -n "Release: " >&2
	grep "^# .Release:" $0 | awk '{ print $3 }' >&2
	echo -n "CVS    : " >&2
	grep "^# .Id:" $0 | awk '{ print $3 " " $4 " " $5 " " $6 }' >&2
}

## Usage
print_usage() {
	cat <<END >&2

fw1-dump.sh

"tcpdump"-like wrapper for "fw monitor"

(P) & (C) 2007-2013 by AERAsec Network Services & Security GmbH

This program converts a given pcap filter string to 'fw monitor' syntax
 and executes 'fw monitor' afterwards.

Some 'tcpdump' options are supported and mapped to 'fw monitor' options 

Normal usage:
$0 [-w <file>] [-l snaplen ] [-c count] [-X] <pcap filter syntax>

Supported 'tcpdump' like options:
  [-w <file>]  write output to file  (mapped to -o <file>)
  [-s len]     packet capture length (mapped to -l len)
  [-c count]   packet count          (mapped to -ci count)
  [-X]         print packet          (mapped to -x 0,(68|len))

Supported 'fw monitor' like options:
  [-p all]     position of packet capturing

Supported pcap filter syntax:
 [not] [src|dst] <host|net|port|portrange>
 [not] ip proto <protocoll>
 [not] icmp|tcp|udp
 less|greater <value>
 ... and|or ...
 not (...)

 if possible, non numeric <port|proto> are resolved to numeric values

Other options:
  [-d]         verbose parser output
  [-h]         (this) online help
  [-V]         version information

Self test:
$0 --selftest

END
	print_version
}

## Test szenarios for selftest
test_scenarios() {
cat <<END
# dst host ____
dst host 127.0.0.1#dst=127.0.0.1

# src host
src host 127.0.0.1#src=127.0.0.1
not src host 127.0.0.1#src!=127.0.0.1

# host ____
host 127.0.0.1#(src=127.0.0.1 or dst=127.0.0.1)
not host 127.0.0.1#(src!=127.0.0.1 , dst!=127.0.0.1)

# dst net ___
dst net 127.0.0.0/8#dst=127.0.0.0/8
not dst net 127.0.0.0/8#dst!=127.0.0.0/8

# src net ___
src net 127.0.0.0/8#src=127.0.0.0/8
not src net 127.0.0.0/8#src!=127.0.0.0/8

# net ___
net 127.0.0.0/8#(src=127.0.0.0/8 or dst=127.0.0.0/8)
not net 127.0.0.0/8#(src!=127.0.0.0/8 , dst!=127.0.0.0/8)

# dst port ____
dst port 80#dport=80
not dst port 80#dport!=80

# src port ____
src port 80#sport=80
not src port 80#sport!=80

# port ____
port 80#(sport=80 or dport=80)
not port 80#(sport!=80 , dport!=80)

# dst portrange _____-_____
dst portrange 1024-4999#(dport>=1024 , dport<=4999)
not dst portrange 1024-4999#(dport<1024 or dport>4999)

# src portrange _____-_____
src portrange 1024-4999#(sport>=1024 , sport<=4999)
not src portrange 1024-4999#(sport<1024 or sport>4999)

# portrange _____-_____
portrange 1024-4999#((sport>=1024 , sport<=4999) or (dport>=1024 , dport<=4999))
not portrange 1024-4999#((sport<1024 or sport>4999) , (dport<1024 or dport>4999))

# less ______
less 1024#ip_len<=1024
not less 1024#ip_len>1024

# greater ______
greater 1024#ip_len>=1024
not greater 1024#ip_len<1024

# ip proto ________
ip proto 50#[9:1]=50
not ip proto 50#[9:1]!=50

# ip broadcast
ip broadcast#((src=0.0.0.0 or src=255.255.255.255) or (dst=0.0.0.0 or dst=255.255.255.255))
not ip broadcast#((src!=0.0.0.0 , src!=255.255.255.255) , (dst!=0.0.0.0 , dst!=255.255.255.255))

# ip multicast
ip multicast#(src=224.0.0.0/4 or dst=224.0.0.0/4)
not ip multicast#(src!=224.0.0.0/4 , dst!=224.0.0.0/4)

# tcp
tcp#[9:1]=6
not tcp#[9:1]!=6

# udp
udp#[9:1]=17
not udp#[9:1]!=17

# icmp
icmp#[9:1]=1
not icmp#[9:1]!=1

# and
src host 192.0.2.1 and dst host 192.0.2.2#src=192.0.2.1 , dst=192.0.2.2

# or
src host 192.0.2.1 or src host 192.0.2.2#src=192.0.2.1 or src=192.0.2.2

# ()
(src host 192.0.2.1 or src host 192.0.2.2) and (dst port 80 or dst port 443)#( src=192.0.2.1 or src=192.0.2.2 ) , ( dport=80 or dport=443 )
not (dst port domain or dst port http)#not ( dport=53 or dport=80 )

## 20070129/PB: until here ^^^ syntax test confirmed: Compiled OK

END
}

## Lookup service number by name
lookupservicebyname() {
	grep -w "$1" $file_services | awk -F# '{ print $1 }' | while read name port rest; do
		for test in $name $rest; do
			if [ "$1" = "$test" ]; then
				echo "$port" | awk -F/ '{ print $1 }'
				return 0
			fi
		done
	done
}

## Lookup protocol number by name
lookupprotobyname() {
	grep -w "$1" $file_protocols | awk -F# '{ print $1 }' | while read name proto rest; do
		for test in $name $rest; do
			if [ "$1" = "$test" ]; then
				echo "$proto"
				return 0
			fi
		done
	done
}

# Simple implementation of getservicebyname
getservicebyname() {
	if echo "$1" | egrep -q "^[0123456789]+$"; then
		# numbers only
		echo "$1"
		return 0
	fi

	if [ ! -e "$file_services" ]; then
		log 3 "given port is not a number, but can't resolv: missing file $file_services"
		exit 1
	fi

	log 7 "given service is not numeric: $1"

	local port="`lookupservicebyname "$1"`"

	if [ -z "$port" ]; then
		log 3 "given port is not a number, but can't be resolved: $1"
		exit 1
	fi

	log 7 "given not numeric service is converted to: $port ($1)"

	echo "$port"
}

# Simple implementation of getprotobyname
getprotobyname() {
	if echo "$1" | egrep -q "^[0123456789]+$"; then
		# numbers only
		echo "$1"
		return 0
	fi

	if [ ! -e $file_protocols ]; then
		log 3 "given protocol is not a number, but can't resolv: $1"
		exit 1
	fi

	log 7 "given protocol is not numeric: $1"

	local proto="`lookupprotobyname "$1"`"

	if [ -z "$proto" ]; then
		log 3 "given protocol is not a number, but can't resolved: $1"
		exit 1
	fi

	log 7 "given not numeric protocol is converted to: $proto ($1)"

	echo "$proto"
}


## pcap syntax parser & converter
parse() {
	fw_monitor=""

	local negate=0
	while [ ! -z "$1" ]; do
		log 7 "#1 $1"
		log 7 "#2 $2"
		log 7 "#3 $3"
		log 7 "#4 $4"

		local count=0
		local token=""
		# catch simple commands
		case $1 in
		    'not')
			log 7 "switch to 'not'"
			local negate=1
			local count=1
			;;
		    'icmp'|'udp'|'tcp')
			case $1 in
			    'icmp')
				local proto=1
				;;
			    'tcp')
				local proto=6
				;;
			    'udp')
				local proto=17
				;;
			esac
			if [ $negate -eq 0 ]; then
				local token="[9:1]=$proto"
			else
				local token="[9:1]!=$proto"
				local negate=0
			fi
			local count=1
			;;
		    'esp')
			local token="[9:1]=50"
			local count=1
			;;
		    'and')
			local token=","
			local count=1
			;;
		    'or')
			local token="or"
			local count=1
			;;
		    '#BO#')
			# Bracket Open
			if [ $negate -eq 0 ]; then
				local token="("
			else
				local token="not ("
				local negate=0
			fi
			local count=1
			;;
		    '#BC#')
			# Bracket Close
			local token=")"
			local count=1
			;;
		    'host')
			if [ $negate -eq 0 ]; then
				local token="(src=$2 or dst=$2)"
			else
				local token="(src!=$2 , dst!=$2)"
				local negate=0
			fi
			local count=2
			;;
		    'port')
			local port="`getservicebyname "$2"`"
			if [ -z "$port" ]; then
				exit 1
			fi
			if [ $negate -eq 0 ]; then
				local token="(sport=$port or dport=$port)"
			else
				local token="(sport!=$port , dport!=$port)"
				local negate=0
			fi
			local count=2
			;;
		    'portrange')
			# split portrange
			local p1="`echo "$2" | awk -F- '{ print $1 }'`"
			local p2="`echo "$2" | awk -F- '{ print $2 }'`"
			if [ $negate -eq 0 ]; then
				local token="((sport>=$p1 , sport<=$p2) or (dport>=$p1 , dport<=$p2))"
			else
				local token="((sport<$p1 or sport>$p2) , (dport<$p1 or dport>$p2))"
				local negate=0
			fi
			local count=2
			;;
		    'net')
			if [ $negate -eq 0 ]; then
				local token="(src=$2 or dst=$2)"
			else
				local token="(src!=$2 , dst!=$2)"
				local negate=0
			fi
			local count=2
			;;
		    'proto')
			local proto="`getprotobyname "$2"`"
			if [ -z "$proto" ]; then
				exit 1
			fi
			if [ $negate -eq 0 ]; then
				local token="[9:1]=$proto"
			else
				local token="[9:1]!=$proto"
				local negate=0
			fi
			local count=2
			;;
		    'ip')
			case $2 in
			    'proto')
				local proto="`getprotobyname "$3"`"
				if [ -z "$proto" ]; then
					exit 1
				fi
				if [ $negate -eq 0 ]; then
					local token="[9:1]=$proto"
				else
					local token="[9:1]!=$proto"
					local negate=0
				fi
				local count=3
				;;
			    'broadcast')
				if [ $negate -eq 0 ]; then
					local token="((src=0.0.0.0 or src=255.255.255.255) or (dst=0.0.0.0 or dst=255.255.255.255))"
				else
					local token="((src!=0.0.0.0 , src!=255.255.255.255) , (dst!=0.0.0.0 , dst!=255.255.255.255))"
					local negate=0
				fi
				local count=2
				;;
			    'multicast')
				if [ $negate -eq 0 ]; then
					local token="(src=224.0.0.0/4 or dst=224.0.0.0/4)"
				else
					local token="(src!=224.0.0.0/4 , dst!=224.0.0.0/4)"
					local negate=0
				fi
				local count=2
				;;
			esac
			;;
		    'less')
			if [ $negate -eq 0 ]; then
				local token="ip_len<=$2"
			else
				local token="ip_len>$2"
				local negate=0
			fi
			local count=2
			;;
		    'greater')
			if [ $negate -eq 0 ]; then
				local token="ip_len>=$2"
			else
				local token="ip_len<$2"
				local negate=0
			fi
			local count=2
			;;
		    'src')
			case $2 in
			    'port')
				local port="`getservicebyname "$3"`"
				if [ -z "$port" ]; then
					exit 1
				fi
				if [ $negate -eq 0 ]; then
					token="sport=$port"
				else
					token="sport!=$port"
					local negate=0
				fi
				local count=3
				;;
			    'host'|'net')
				if [ $negate -eq 0 ]; then
					token="src=$3"
				else
					token="src!=$3"
					local negate=0
				fi
				local count=3
				;;
			    'portrange')
				# split portrange
				local p1="`echo "$3" | awk -F- '{ print $1 }'`"
				local p2="`echo "$3" | awk -F- '{ print $2 }'`"
				if [ $negate -eq 0 ]; then
					token="(sport>=$p1 , sport<=$p2)"
				else
					token="(sport<$p1 or sport>$p2)"
					local negate=0
				fi
				local count=3
				;;
			esac
			;;
		    'dst')
			case $2 in
			    'port')
				local port="`getservicebyname "$3"`"
				if [ -z "$port" ]; then
					exit 1
				fi
				if [ $negate -eq 0 ]; then
					token="dport=$port"
				else
					token="dport!=$port"
					local negate=0
				fi
				local count=3
				;;
			    'host'|'net')
				if [ $negate -eq 0 ]; then
					token="dst=$3"
				else
					token="dst!=$3"
					local negate=0
				fi
				local count=3
				;;
			    'portrange')
				# split portrange
				local p1="`echo "$3" | awk -F- '{ print $1 }'`"
				local p2="`echo "$3" | awk -F- '{ print $2 }'`"
				if [ $negate -eq 0 ]; then
					token="(dport>=$p1 , dport<=$p2)"
				else
					token="(dport<$p1 or dport>$p2)"
					local negate=0
				fi
				local count=3
				;;
			esac
			;;
		    *)
			# default
			if [ -z "$1" ]; then
				# never happens
				return 1
			fi
			;;
		esac
		if [ $count -eq 0 ]; then
			log 3 "unsupported: $*"
			exit 1
		fi

		if [ -n "$token" -a $negate -ne 0 ]; then
			log 3 "unsupported 'not': $*"
			exit 1
		fi

		log 7 "$token"
		fw_monitor="$fw_monitor $token"
		shift $count
	done

	# Remove not needed spaces
	fw_monitor="`echo "$fw_monitor" | sed 's/^ *//g' | sed 's/ *$//g' | sed 's/ +//g'`"
}

## built-in self test
do_selftest() {
	log 5 "selftest scenarios: tcpdump syntax -> fw monitor syntax"

	test_scenarios | grep -v "^#" | grep -v "^$" | while IFS="#" read input output; do
		log 6 "input          : $input"
		log 6 "expected output: $output"

		local line="`echo "$input" | sed 's/(/ #BO# /g' | sed 's/)/ #BC# /g'`"
		parse $line
		if [ "$fw_monitor" != "$output" ]; then
			echo "ERROR : test fails   : $fw_monitor"
			return 1
		else
		log 6 "result ok"
		fi
	done

	if [ $? -ne 0 ]; then
		log 5 "selftest scenarios: tcpdump syntax -> fw monitor syntax - ERROR OCCURS"
		exit 2
	else
		log 5 "selftest scenarios: tcpdump syntax -> fw monitor syntax - OK"
	fi

	log 5 "selftest scenarios: list fw monitor lines"
	test_scenarios | grep -v "^#" | grep -v "^$" | while IFS="#" read input output; do
		echo "fw monitor -e \"accept $output;\""
	done
	log 5 "selftest scenarios: list fw monitor lines - OK"
}



### Main

if [ "$1" = "--selftest" ]; then
	do_selftest
	exit $?
fi


# defaults
fw_monitor_options=""
pcap_length="68"

## get options
TEMP="`getopt XVhdw:s:c:p: "$@"`"

if [ $? != 0 ]; then
	echo "ERROR : something was going wrong during option parsing (try '-h')" >&2
	exit 1
fi

eval set -- "$TEMP"

while true; do
	case "$1" in
	    '-w')
		# write file
		if [ -z "$2" ]; then
			echo "ERROR : missing file name"
			print_usage
			exit 2
		fi
		log 7 "capture file option: $2"
		fw_monitor_options="$fw_monitor_options -o $2"
		shift 2
		;;
	    '-s')
		# capture length
		if [ -z "$2" ]; then
			echo "ERROR : missing capture length"
			print_usage
			exit 2
		fi
		log 7 "capture length option: $2"
		fw_monitor_options="$fw_monitor_options -l $2"
		pcap_length="$2"
		shift 2
		;;
	    '-c')
		# packet counter
		if [ -z "$2" ]; then
			echo "ERROR : missing capture length"
			print_usage
			exit 2
		fi
		log 7 "packet count option: $2"
		fw_monitor_options="$fw_monitor_options -ci $2"
		shift 2
		;;
	    '-X')
		# print packet
		log 7 "print packet option"
		fw_monitor_x="1"
		shift
		;;
	    '-p')
		# position of packet capturing
		case "$2" in
		    'all')
			;;
		    *)
			echo "ERROR : missing or unsupported option value: $2"
			print_usage
			exit 2
			;;
		esac
		
		fw_monitor_options="$fw_monitor_options -p $2"
		log 7 "packet capturing position: $2"
		shift 2
		;;
	    '-d')
		log_level=7
		shift
		;;
	    '-h')
		print_usage
		exit 2
		;;
	    '-V')
		print_version
		exit 0
		;;
	    --)
		shift
		break
		;;
	    *)
		echo "ERROR : unsupported option: $1" >&2
		print_usage
		exit 2
		;;
	esac
done

# Finalize -X
if [ -n "$fw_monitor_x" ]; then
	fw_monitor_options="$fw_monitor_options -x 0,$pcap_length"
fi

# Expand/convert brackets
line="`echo "$*" | sed 's/(/ #BO# /g' | sed 's/)/ #BC# /g'`"

log 7 "pcap line to parse: $line"
parse $line

log 6 "execute fwmonitor with following arguments:"
log 6 "fw monitor $fw_monitor_options -e \"accept $fw_monitor;\""

# Real execution of 'fw monitor'
fw monitor $fw_monitor_options -e "accept $fw_monitor;"
