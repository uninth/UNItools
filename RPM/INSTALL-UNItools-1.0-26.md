
$Header: /lan/ssi/shared/software/internal/UNItools/src/GaIA/INSTALL.md,v 1.1 2015/06/11 20:18:57 root Exp root $

# Installation procedure for UNItools-1.0-26.i386.rpm
    Package name: UNItools-1.0-26.i386.rpm
    Version     : 1.0
    Release     : 26

## Prerequisite

1. Check Point firewall software installed

2. The following _is done_ by _UNItools-1.0-26.i386.rpm, at least on R77.20 and R77.30. If you cannot copy packages
   to the firewall, you may have to do it ahead - and by hand:

   ``admin`` (admin user) _must change login shell_ in order for ``scp`` and ``ssh`` login to work, and 
   you are encuraged to change the inactivity time-out as well:

       clish -sc "set user admin shell /bin/bash"
       clish -sc "set inactivity-timeout 720"

   The ``admin`` (admin user) must be able to transfer files with ``scp``: In expert mode do:

       echo "admin" >> /etc/scpusers

Notice that ``UNItools-1.0-26.i386.rpm`` is a prequisite for most of the other ``UNI``_what-ever-packages_.

## Installation
Copy ``UNItools-1.0-26.i386.rpm`` to target host and install the package:

    td -x UNItools-1.0-26.i386.rpm external-interface
    td external-interface
    /var/tmp/rpm -Uvh UNItools-1.0-26.i386.rpm

## Uninstallation
Remove the package with:

    rpm -e --nodeps UNItools-1.0-26.i386.rpm

## Note
This document is in RCS and build with make

##RPM info

View rpm content with

    rpm -lpq UNItools-1.0-26.i386.rpm

