
$Header: /lan/ssi/shared/software/internal/UNItools/src/GaIA/INSTALL.md,v 1.1 2015/06/11 20:18:57 root Exp root $

# Installation procedure for __TARGET__
    Package name: __TARGET__
    Version     : __VERSION__
    Release     : __RELEASE__

## Prerequisite

1. Check Point firewall software installed

2. The following _is done_ by ___TARGET__, at least on R77.20 and R77.30. If you cannot copy packages
   to the firewall, you may have to do it ahead - and by hand:

   ``admin`` (admin user) _must change login shell_ in order for ``scp`` and ``ssh`` login to work, and 
   you are encuraged to change the inactivity time-out as well:

       clish -sc "set user admin shell /bin/bash"
       clish -sc "set inactivity-timeout 720"

   The ``admin`` (admin user) must be able to transfer files with ``scp``: In expert mode do:

       echo "admin" >> /etc/scpusers

Notice that ``__TARGET__`` is a prequisite for most of the other ``UNI``_what-ever-packages_.

## Installation
Copy ``__TARGET__`` to target host and install the package:

    td -x __TARGET__ external-interface
    td external-interface
    /var/tmp/rpm -Uvh __TARGET__

## Uninstallation
Remove the package with:

    rpm -e --nodeps __TARGET__

## Note
This document is in RCS and build with make

##RPM info

View rpm content with

    rpm -lpq __TARGET__

