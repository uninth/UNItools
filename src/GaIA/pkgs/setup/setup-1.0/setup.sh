#!/bin/bash
#
# $Header: /lan/ssi/shared/software/internal/UNItools/src/GaIA/pkgs/setup/setup-1.0/RCS/setup.sh,v 1.4 2016/05/31 16:03:16 root Exp $
#

# Source global definitions
if [ -f /etc/bashrc ]; then
	. /etc/bashrc
fi

if [ -f /etc/profile.d/CP.sh ]; then 
	.  /etc/profile.d/CP.sh
fi

if [ -f /etc/profile.d/CPshell.sh ]; then 
	.  /etc/profile.d/CPshell.sh
fi      

if [ "x$SHLVL" != "x1" ]; then # We're not a login shell
	for i in /etc/profile.d/*.sh; do
		if [ -x $i ]; then 
			. $i    
		fi      
	done    
fi

trap 'echo "please do NOT attempt to stop the installation process"' 1 2 3 13 15

echo "Wellcome to UNItools configuration for GaIA R77.10, 20, 30 and beyond"

echo "changing admin user shell and inactivity-timeout"
echo "user = admin shell = /bin/bash inactivity-timeout 720"

tmpfile=/tmp/"$$"."$(awk 'BEGIN {srand();printf "%d\n", rand() * 10^8}')"

cat << EOF > ${tmpfile}
set user admin shell /bin/bash
set inactivity-timeout 720
EOF

clish -i -s -f ${tmpfile}
echo "clish command done"

/bin/rm -f ${tmpfile}

echo  "enabeling admin scp in /etc/scpusers ... "
echo "admin" > /etc/scpusers

/bin/chown root:root /etc/scpusers
/bin/chmod 444 /etc/scpusers

echo "done"

echo "configuring .bash_profile for the admin user ... "
/bin/cp /var/opt/UNItools/conf/.bash_profile /home/admin

echo "Setting up ssh keys for user admin (aka root, uid 0) ... "

if [ ! -f "$HOME/.ssh/authorized_keys" ]; then
echo "creating rsa key ... "
ssh-keygen -t dsa -b 4096 -q -N "" -f $HOME/admin/.ssh/id_rsa
echo "" | ssh-keygen -t rsa 2>/dev/null
#echo "" | ssh-keygen -t rsa 2>/dev/null
#echo "" | ssh-keygen -t rsa1 2>/dev/null
echo "adding our key to authorized_keys ... "
#cat << EOF > /home/admin/.ssh/authorized_keys
ssh-rsa AAAAB3NzaC1yc2EAAAADAQABAAACAQDFzg7XMQuCJ/nOs4eUN734PsPEbE82xYDS04qxgaC0CotkUK+4hzGUeHawuuIDAtJL6LTS304mYj7MYaFTG/Qx0QK5xopzVriX3WmZtnuDq5d7ddzOIcmpYDYG6lHnEZs/LZhOEultYlEKtzNozDFqUyfuzAFpgv1harC+2YPzxgw0CLZFWz10YOQDo9spNEQX684Zy4j/0IMa+e8ijPFiGhGItZkRkHDUkf15G9K9F2rnHecIHo6IL0rMARrktexiQsVLCl0lFZVDP3ApiHaaDoQClP106XuSqd+oBUGN2/3Hkn8gtnDWUREeTCtS6QHfFa1NYtR5Z0MJUjGscNGTsBF8p4rHKG2sumf0HFi7mGQ5TmAGF1+/eIZTOB2Fq5YxWrwKdCqx/KbgkgGEc9Mgm3QtLEqyPr7vaT0hbtSip30Ad40RWOWlIu50ljz8bijxRWMyqwbVrcaOS+KVitbWwKubf1oeHEVeLbcFNMgj74HWm+wqqqRwbgaL7yU0WTnzClns/d4+zHMxK3XjKHjOJsmaeDPVDEHe66nGG1iF+zvVhaC5KHGHZwuH2dbjETvF5CxnNy58GRZc098gBy+bOf6NKBHXfJgU+X22NjBPrZCZ5LDU/J6DHF5ZCAT/akJ8wmtPIan9WEQcBzRkTRq1O6w5BhJ0NB3ujaTR8TwsOw== root@buh
#EOF
else
echo "existing ssh configuration not changed"
fi

chmod -R 700 $HOME/.ssh $HOME/.ssh/*

grep -q 130.225.245.210 /etc/hosts
case $? in
	0) echo "found 130.225.245.210 in /etc/hosts"
	;;
	*) clish -sc "add host name fwgui ipv4-address 130.225.245.210"
	   echo "added 130.225.245.210 to /etc/hosts"
	;;
esac

echo "done. ssh access w/o password granted from SSI"

echo "Enabeling scheduled backup of Check Point firewall-1 ... "

if [ -d /etc/cron.d ]; then
	cat << EOF > /etc/cron.d/UNItools_backup
# periodic firewall backup
40 7 * * * root /var/opt/UNItools/fwbu/bin/UNIcpfwbu.sh
EOF
	chmod 644 /etc/cron.d/UNItools_backup

	/etc/init.d/crond restart
else
	echo "no /etc/cron.d please fix"
fi
            
echo "setting up softlinks ... "
(
	cd /var/opt/UNItools/bin
	for FILE in tar gunzip gzip bash domainname hostname md5sum
	do
		/bin/rm -f ${FILE}
		ln -s `type ${FILE} | awk '{ print $NF }'` ${FILE}
		echo "${FILE} ... "
	done
)

find /var/opt/UNItools/bin -type l -exec ls -l {} \; 

echo "undo by un-install UNItools and remove admin user auth. keys"
echo "use clish to change admin users SHELL and time out"
echo "remove /etc/hosts entries with clish"
