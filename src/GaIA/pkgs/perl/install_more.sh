#!/bin/sh
#
# Script der *kan kaldes* efter selve installationen og skal
# installere / fjerne / ... ting i /var/opt/UNItools
#

# Source konfiguration for perl
. ./CFG

# Preserve CWD
SAVEDIR=`pwd`

# Source til perl ligger her:
SRC=$SRC

# Installer / fjern / ... herunder:
INSTALL_ROOT=$ROOT


#
# Unødvendige programmer
#
cd $ROOT/bin
/bin/rm -fr	c2ph cpan decode-qp dprofpp enc2xs find2perl	\
		gedi GET h2ph h2xs HEAD instmodsh perlbug	\
		perlcc perldoc perlivp piconv pl2pm pod2html	\
		pod2latex pod2man pod2text pod2usage podchecker	\
		podselect POST ppm ppm3 ppm3-bin prove ptked	\
		ptksh reloc_perl s2p SOAPsh.pl splain		\
		stubmaker.pl tkjpeg widget XMLRPCsh.pl xsubpp	\


#
# forkert / unødvendig dokumentation
cd $ROOT/docs/$PKG.$VER || { echo "chdir '$ROOT/docs/$PKG.$VER' failed, bye"; exit 1; }

for DOC in	ChangeLog CHANGELOG grey.html grey.pdf grey.txt	\
		InNewTai.pl newgetopt.pl news.pm NewTaiLu.pl	\
		perl5.8.html perl5.8.pdf perl5.8.txt		\
		perlnewmod.html perlnewmod.pdf perlnewmod.pod	\
		perlnewmod.1 perlnewmod.txt README		\
		README.Adjust README.e2x readme.html		\
		README.libnet README.perl snews.pm EULA-Community_License.rtf
do
	FILE="`file $DOC >/dev/null`"
	echo "removing ${FILE:=$DOC}"
	/bin/rm -f $DOC
done

exit 0
