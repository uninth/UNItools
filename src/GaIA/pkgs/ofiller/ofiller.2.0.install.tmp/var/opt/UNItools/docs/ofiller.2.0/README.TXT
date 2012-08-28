******************************************************************************
* Unofficial/unsupported Object Filler and Object Dumper for Check Point's   *
* SmartCenter Server and Provider-1 MDS - Developed by Martin Hoz            *
* (c) 2003-2005 by Check Point Software Technologies, Ltd. and subsidiaries  *
****************************************************************************** 
* Version 2.0 - February 2005                                                 *
******************************************************************************

******************************************************************************
Disclaimer
------------------------------------------------------------------------------

These programs are not Official, nor supported in any form.

These programs come with no support of any kind and with no  warranty  of  any
kind (I'm doing it as a  hobby,  Come  on!   ;-).   So,  you  (the  user)  are
responsible for any use these programs may have, good  or  bad;  and  for  any
other good or bad thing derived of  this  program  anyhow  while  you  use  it
directly or indirectly (including but not limited to  data  loss  or  programs
failure of any kind).  The author(s) have made no warranty  or	representation
that the operation of this software will be error-free	or  suitable  for  any
direct or indirect application, and they are under no  obligation  to  provide
any services, by way of maintenance, update, or otherwise.  This  software  is
an always experimental prototype offered on an	as-is  basis;  and  should  be
treated accordingly.

All brands and commercial trademarks mentioned  here  are  property  of  their
respective owners.


******************************************************************************
Documentation
------------------------------------------------------------------------------
For a more complete documentation, please read the User's Manual  included  in
the package, under the Doc directory


******************************************************************************
Programs Availability
------------------------------------------------------------------------------
Object Filler and Object Dumper have no associated cost (i.e. no license fee),
as they are not part of the official Check Point Software.

Latest versions are always available at the  following  sites  (they  are  not 
listed on any particular order):
http://www.phoneboy.com  - under FireWall-1 FAQs and then Software Downloads
http://lindos.dnsalias.com/ 
http://www.lindercentral.com/ofiller/
http://mhoz1.sofaware.net/ofiller/ - Unreliable Server

These programs are also available through Check Point System  Engineers  world
wide on a non-official way - i.e. they are not obligated to provide it to you,
they are also not obligated to support you if you run into problems. They  are 
not even obligated to know that these tools exist. 


******************************************************************************
Files on the package
------------------------------------------------------------------------------

Martin_Hoz.asc - Author's public PGP key.

** Windows Directory
 ofiller.exe - Object Filler program executable for Windows platforms.

 odumper.exe - Object Dumper program executable for Windows platform.
 
** Linux_and_SPLAT Directory        
 ofiller.lin - Object	Filler	program  executable  for  SecurePlatform   and
              GNU/Linux (Red Hat).

 odumper.lin - Object	Dumper	program  executable  for  SecurePlatform   and
              GNU/Linux (Red Hat).

** Samples directory
 sample_csv.csv - csv file to feed object filer with very detailed information
        on objects. Used with "-i csv" option with Object Filler.

 sample_rules.csv - an example CSV file that contains the definition of  rules
        to be imported with Object Filler.

 sample_list1.csv - sample of listing file  number  1.	Used  with  "-i  list"
        option of Object Filler.

 sample_list2.csv - sample of listing file  number  2.	Used  with  "-i  list"

 sample_hosts - sample of a hosts file. Used with "-i hosts" option.
        option of Object Filler.

 sample_pix.txt - sample of access-list statements  used  to  demonstrate  the
        PIX import option "-i pix" with Object Filler.

 sample_objects_5_0.C - sample of Objects_5_0.C. Used to be "dumped" to a  CSV
        file using Object Dumper.

 sample_rulebases_5_0.fws - sample of rulebases_5_0.fws used to be "dumped" to
        a CSV file using Object Dumper.

** HTML directory
 ofiller.html - Proof of concept for HTML interface. See documentation below.

 ofiller.pl - Proof of concept program for HTML interface.  See  documentation
        below.

** Docs directory
 Users_Manual.pdf - Users Manual document


******************************************************************************
What's New - (Fixed bugs and new features) - And program history
------------------------------------------------------------------------------
* Version 2.0 – February 2005
------------------------------------------------------------------------------
= Object Filler
- Added support for ICMP, Other, RPC and DCE-RPC services in CSV files.
- Added support for Check Point Dynamic Gateways (Check  Point  Gateways  with
  Dynamic IP address) in CSV Files
- Enhanced support for Raptor files, including services recognition.
- Added support for interfaces on Check Point gateways (including Clusters and 
  Dynamic IP gateways) and interoperable devices. Interfaces with  dynamic  IP 
  are also supported. This is in CSV files.
- Added support for setting the encryption  domain  on  Check  Point  gateways 
  (including clusters and dynamic IP gateways) and  interoperable  devices  in 
  CSV files.
- Added support for setting the WebServer property, when configuring Hosts  in 
  CSV files.
- Enhanced and corrected bugs in the support for rules from CSV files
- Added support for  a  “modifications  mode”,  used  mainly  to  modify  some 
  properties on currently build objects in CSV files. This option is  designed 
  to be used with object dumper.
- Enhanced support for NATted objects when importing from  PIX  configurations. 
  Now the results are more accurate.
- Enhanced support for Rules processing when  importing  from  PIX  and  Cisco 
  Router configurations: Now splits in  different  sections  of  the  imported  
  rulebase, the different ACLs that the configuration may have
- Now, when creating groups from CSV Files the groups are  created  first  and 
  then elements are added to them.

= Object Dumper
- Added support for services (TCP, UDP, ICMP, Other and RPC)
- Added   support   to   recognize   basic   rules    from    the    rulebases  
  (rulebases_5_0.fws) file.
- Added support for interfaces with Check Point gateways  (including  clusters 
  and dynamic IP gateways) and Interoperable devices. This includes interfaces 
  with dynamic IP
- Support for recognizing the webserver property on hosts
- Support for recognizing  the  encryption  domain  on  Check  Point  Gateways 
  (including clusters and dynamic IP gateways) and Interoperable devices.
- Enhanced the support for reading objects.C files from gateways.
- Tabulation (-tab) mode is not supported  anymore.  (seems  that  nobody  was 
  actually using it)

= Documentation
- For the first time, the tools have a more decent manual. It’s  the  plan  to 
  enhance the documentation in the next releases

------------------------------------------------------------------------------
* Version 1.9.2 - November 2004
------------------------------------------------------------------------------
= Object Filler:
- Added support for TCP/UDP services when importing from CSV Files, Cisco PIX, 
  Cisco Routers and NetScreen configuration files.
- Added support for importing basic layer 3 and layer  4  rulebases  from  CSV
  files, and also importing  from  Cisco  PIX  and  Cisco  Router  Access-list
  configurations.
- Limitation: This version does not support Check Point dynamic IP gateways.

= Object Dumper:
- Added support for objects.C files found on gateways, for recovery options.
- Added support for Check Point dynamic IP gateways.

------------------------------------------------------------------------------
* Version 1.8 - March 2004
------------------------------------------------------------------------------
= Object Filler:
- Support to DELETE and RENAME operations over objects, when  specifying  such
  operations on CSV files
- Support to Domain and Dynamic objects. Clusters and cluster members are also
  now supported.
- Support to the following SmartLSM objects: IP40 ROBO gateways, Edge X ROBO
  gateways, profiles (SmartLSM VPN-1 Egde/Embedded NG profiles).
- Support to PIX network-object groups and to name statements.
- Support to Raptor configuration files.
- Support to Cisco IOS ACLs (including the ones declared with inverse masks).
- Support to NONAT mode when importing from files.

= Object Dumper:
- Added support to clusters and cluster members.
- Added support to Domain objects.
- Added support to SmartLSM VPN-1 Edge/Embedded profiles 
- Added support to Dynamic Objects.

------------------------------------------------------------------------------
* Version 1.6 - January 2004
------------------------------------------------------------------------------
= Object Filler:
- Fixed bug: Now it works with IP address range objects behind a NAT IP range.
- Fixed bug: Now it recognizes "cpgws" as  a  valid  object  type  when  using
  command line parameters.
- Fixed bug: Correctly handles objects hiddend behind All gateways, when "All"
  is specified on the NATting Object column, when importing from CSV files.
- Enhanced interactive mode with more comments to ease user experience.
- Improved support to NAT statements when importing from PIX.
- Improved summary information when importing information from any file.
- Now groups are supported when using the cgi mode (HTML form)	and  importing
  from CSV files.
- Support to import from SideWinder configuration files.
- New  output  mode  (ASCII)  introduced,  which  instead  of  writing	dbedit
  commands, leaves the information on  CSV  format  (more  easy  to  read  and
  compare).
- Support to Interoperable  Devices,  Plain  Gateways  and  OSE  Devices  when
  importing from CSV files and when generating objects from command line.
- Now when importing from a  LIST  type  of  file,  it's  possible  to	create
  ranges and groups.
- Native binary support for Linux/SecurePlatform.

= Object Dumper:
- Now it recognizes Interoperable Devices, Plain Gateways and OSE Devices.
- Enhanced interactive mode with more comments to ease user experience.
- HTML mode for output files is now available. 
- TAB (Column) mode for output files is now available. 
- Native binary support for Linux/SecurePlatform.

------------------------------------------------------------------------------
* Version 1.4 - December 2003
------------------------------------------------------------------------------
- Support to interactive mode (command line is still supported).
- Enhanced support to duplicates (now it takes in account the object type, not
  only the IP address).
- IP ranges support when creating objects and when importing from CSV files.
- Support to import objects from Gauntlet configuration files.
- Support to comments when importing from CSV files and List files.
- Support to import groups when importing from CSV files.
- Support to groups when importing from CSV files.
- Gives a summary of how many objects of each known type were processed.
- Object Dumper companion tool was created. 

------------------------------------------------------------------------------
* Version 1.2 - July 2003
------------------------------------------------------------------------------
- Support to import objects from CSV (comma separated) files,  where  you  can
  detail the objects you need to create.
- Support to import from lists files, where you just detail  IP  and  netmask,
  Object name and everything else is calculated automatically.
- Support to import objects from operating system's host file.
- Support to import objects from Cisco PIX and NetScreen configuration	files,
  and create network objects from there. Importing rules is not supported.
- Support for Hide NAT on created sequential objects.
- Support for Static NAT on imported objects from files.
- Support to NAT ranges to hide created objects.
- Support for color specification on new objects.

------------------------------------------------------------------------------
* Version 0.96 - May 2003
------------------------------------------------------------------------------
- Support for importing from CSV files.
- Support to Check Point Host and Check Point Gateway objects.
- Support to Hide NAT for objects generated using command line.
- Support for colors on created objects.

------------------------------------------------------------------------------
* Version 0.8 - April 2003
------------------------------------------------------------------------------
- This was the Initial Public release.
- Supported only creating hosts and networks.

------------------------------------------------------------------------------
* Version 0.5 - April 20th, 2003 – 06:57 AM
------------------------------------------------------------------------------
- This idea of Object Filler is born. I started with some preliminary designs, 
  algorithms and coding that morning.


******************************************************************************
