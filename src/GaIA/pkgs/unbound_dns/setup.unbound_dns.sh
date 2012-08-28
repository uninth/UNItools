# #!/bin/sh
# ++
#                                     Wed May 22 16:40:00 CEST 2013
# 
# Det følgende ender med en programpakke bestående af program(mer),
# README, eksempler, manual(er) osv. til Linux / SPLAT. Ingen include,
# libs eller andet. Det er lavet til R76, hvor nye brugere kun kan
# laves med HOME under /home (suk).
# 
# Alle programmer er derfor installeret under /home/unbound
# 
# Programmer mv: /home/unbound/bin
# Konfiguration: /home/unbound/etc/unbound_dns
# Dokumentation: /home/unbound/docs/unbound_dns.1.4.22
# 
# Det er *ikke* programpakker i Linux format (pkg) men blot en
# installation af programmet unbound_dns.
# 
#  1	Download programpakken unbound_dns til /lan/ssi/projects/UNItools/src/Linux/2.4.21-20cpsmp/pkgs/unbound_dns.
# 	Læs hvordan programpakken oversættes og installeres i dokumentationen
# 	for programpakken (typisk README og INSTALL).
#
#	For at kunne oversætte den skal følgende downloades:
# 
# 	wget -N http://unbound.net/downloads/unbound-1.4.22.tar.gz
# 	wget -N http://www.nlnetlabs.nl/downloads/ldns/ldns-1.6.17.tar.gz
#	wget -N http://www.openssl.org/source/openssl-1.0.1e.tar.gz
#   wget -N http://sourceforge.net/projects/expat/files/latest/download
# 
# 	/bin/gtar xvzf unbound-1.4.22.tar.gz
# 	/bin/gtar xvzf ldns-1.6.17.tar.gz
#	/bin/gtar xvzf expat-2.1.0.tar.gz
#	/bin/gtar xvzf openssl-1.0.1e.tar.gz
# 
#  2	Her burde du rette dokumentet CFG, men da jeg har valgt at installere
#	det hele under /home/unbound er det ligegyldigt. CFG anvendes/læses af
#	pkg_* -- der ikke anvendes her.
#	CFG blev lavet med scriptet pkg_mk_cfg.sh
#
#  	Du skal angive hvordan programmet oversættes og installeres,
# 	dvs.  argumenterne til config/configure og Make, samt om der
# 	skal anvendes et start/stop script.
# 
# 	Du skal som minimum udfylde NAME og VENDOR.
# 
#  3	Oversæt programpakken og lav en midlertidig installation. Hvis
#  	programmerne skal oversættes statisk, *kan* det være nødvendigt
# 	at sætte variablen LDFLAGS=-static
#
#	Openssl installeres 'normalt' i /usr/local/ssl/... her installeres
#	det i /home/unbound - svarende til /usr/local.
#	for også at kunne virke med GaIA

INSTALL_HOME=/home/unbound

cat << EOF > /dev/null
	(
		cd openssl-1.0.1e/
		cd openssl			# seneste
		make clean
		./config --prefix=$INSTALL_HOME --openssldir=$INSTALL_HOME
		make install

		# Fjern manual sider - de anvendes ikke

		/bin/rm -fr $INSTALL_HOME/man
		
		#
		# kopier dokumenter, licenser osv.
		#
		DOCDIR=$INSTALL_HOME/doc/ssl/
		test -d $DOCDIR || mkdir -p $DOCDIR

		cp -r doc ACKNOWLEDGMENTS CHANGES CHANGES.SSLeay FAQ INSTALL LICENSE NEWS PROBLEMS README README.ASN1 README.ENGINE $DOCDIR
		chmod 555 `find $DOCDIR -type d`
		chmod 444 `find $DOCDIR -type f`
	)

	(
		cd expat-2.1.0
		make clean
		./configure --prefix=$INSTALL_HOME/ --bindir=$INSTALL_HOME/bin --sbindir=$INSTALL_HOME/bin --mandir=$INSTALL_HOME/man
		make install 
		/bin/rm -fr $INSTALL_HOME/man
		mkdir -p $INSTALL_HOME/doc/expat
		cp Changes COPYING MANIFEST README $INSTALL_HOME/doc/expat/
	)

	(
		cd ldns-1.6-17
		make clean
		./configure --with-ssl=$INSTALL_HOME --prefix=$INSTALL_HOME --mandir=$INSTALL_HOME/man --bindir=$INSTALL_HOME --sbindir=$INSTALL_HOME/bin
		make install 

		mkdir $INSTALL_HOME/doc/ldns
		cp Changelog LICENSE README README.snapshots README.svn $INSTALL_HOME/doc/ldns

		cd drill
		make clean
		./configure --with-ssl=$INSTALL_HOME  --prefix=$INSTALL_HOME/ --with-ldns=$INSTALL_HOME/ --mandir=$INSTALL_HOME/man --bindir=$INSTALL_HOME/bin --sbindir=$INSTALL_HOME/bin
		make install 

		/bin/rm -fr $INSTALL_HOME/man
		nroff -man -Tutf8 drill.1 |col -bx > $INSTALL_HOME/doc/ldns/drill.txt

	)

	(
		cd unbound-1.4.22/
		make clean
		./configure --with-ssl=$INSTALL_HOME --prefix=$INSTALL_HOME --mandir=$INSTALL_HOME/man --bindir=$INSTALL_HOME --sbindir=$INSTALL_HOME/bin --with-ldns=$INSTALL_HOME/ --with-libexpat=$INSTALL_HOME/
		make install 

		mkdir $INSTALL_HOME/doc/unbound
		cd doc
		cp Changelog control_proto_spec.txt CREDITS example.conf FEATURES ietf67-design-02.odp ietf67-design-02.pdf LICENSE README README.svn README.tests requirements.txt TODO $INSTALL_HOME/doc/unbound

		groff -man -Tutf8 libunbound.3			| col -bx > $INSTALL_HOME/doc/libunbound.txt
		groff -man -Tutf8 	unbound.8			| col -bx > $INSTALL_HOME/doc/unbound.txt
		groff -man -Tutf8 	unbound-anchor.8	| col -bx > $INSTALL_HOME/doc/unbound-anchor.txt
		groff -man -Tutf8 	unbound-checkconf.8	| col -bx > $INSTALL_HOME/doc/unbound-checkconf.txt
		groff -man -Tutf8 	unbound.conf.5		| col -bx > $INSTALL_HOME/doc/unbound.conf.txt
		groff -man -Tutf8 	unbound-control.8	| col -bx > $INSTALL_HOME/doc/unbound-control.txt
		groff -man -Tutf8 	unbound-host.1		| col -bx > $INSTALL_HOME/doc/unbound-host.txt

		/bin/rm -fr $INSTALL_HOME/man $INSTALL_HOME/ldns-config

	)

	(

		cd  $INSTALL_HOME/etc/unbound
		wget ftp://ftp.internic.net/domain/named.cache

	)

	(
		mkdir $INSTALL_HOME/run/
		cp unbound.init $INSTALL_HOME/etc/unbound.init
		cp unbound.conf $INSTALL_HOME/etc/unbound/unbound.conf
		cp setup.sh $INSTALL_HOME/bin
		chmod 755 $INSTALL_HOME/bin/setup.sh
	)

rm -f UNIdns.tgz
tgz   UNIdns.tgz $INSTALL_HOME

EOF

#	Nu skal der laves en RPM pakke. Først skal vi have det hele flyttet til
#	et midlertidigt chroot (for at få filer i /etc med på en enkel måde)

echo $INSTALL_HOME


exit 0

# 
# export LDFLAGS=-static
# 
# 	pkg_fake_install.sh -n ./CFG
# 
# 	hvilket vil konfigurere, oversætte og installere programpakken,
# 	hvis den er skrevet med automake/configure/osv. Fjern '-n' hvis
# 	du eller andre anvender programmer i /var/opt/UNItools; flaget
# 	betyder 'prompt mig ikke'.
# 
# 	I modsat fald må du rette CFG eller skrive kommandoerne her.
# 
# 	Pakken flyttes efterfølgende til
# 
# 	unbound_dns.1.4.22.install.tmp
# 
# 	Bemærk, at alt i dette katalog er MIDLERTIDIGT, og slettes hver
# 	gang pkg_fake_install.sh udføres!
# 
# 	Dokumentation (installeret sim man - sider) laves i tre udgaver
# 	som html, txt og pdf og gemmes i docs/unbound_dns.1.4.22.  Se efter
# 	om der er andre dokumenter der burde kopieres med (licens og
# 	andet).
# 
#  5	Lav et dokument der beskriver afhængigheder (rpm'er) for programpakken.
#  	Det er ikke strængt nødvendigt, men jeg forventer en gang med tiden
# 	at få det her lavet om, så man faktisk laver rigtige rpm'er.
# 
# 	pkg_mkrpm_dep.sh ./CFG depend
#  	
# 	Kræver programpakken start/stop scripts skal de laves andetsteds
#  	i forbindelse med setup.sh af UINtools.
# 
#  6 	Tilføj evt. ekstra dokumenter der ikke kommer med i forbindelse
# 	med installation (make install).
# 
# 	Du kan med fordel sætte INSTALL_MORE til et script, der vil
# 	kopiere de relevante dokumenter til unbound_dns.1.4.22.install.tmp.
# 
# 	Du skal selv lave scriptet, men et eksempel ligger ved siden
# 	af dette dokument, med navnet install_more.sh.
# 	Ellers må du skrive kommandoerne til at gøre tingene herunder.
# 
#  7	Lav dokumentation for hvad programpakken består af osv. med
#  	kommandoen
# 
# 	pkg_mkdoc.sh ./CFG
# 
#  8	Lav et tgz arkiv med relative stinavne af det installerede.
# 
# 	pkg_build.sh ./CFG
# 
#  9	Installer programpakken (evt. midlertidig) på en firewall og
#  	test den. Fortsæt hvis alt viser sit at være OK.
#  
# 10	Virker alt efter hensigten lægges programmer mv i
# 	 /var/opt/UNItools og div. index sider mv. opdateres. Det sker
# 	 når du udføre kommandoen
# 
# 	pkg_install.sh ./CFG
# 
# 11	Ryd op, slet overflødige dokumenter osv. (make distclean)
# 
# 	pkg_clean.sh	./CFG
# 
# 
# Hvis du begår en fejl og har en mistanke om, at /var/opt/UNItools er
# grisset til, sletter du det hele, og udfører kommandoen
# 
# 	pkg_do_it_all_for_all_known_packages
# 
# 
# --
