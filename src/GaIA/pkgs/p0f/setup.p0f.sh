# #!/bin/sh
# ++
#                                      Tue Nov  8 13:43:26 CET 2005
# 
# Det f�lgende ender med en programpakke best�ende af program(mer),
# README, eksempler, manual(er) osv. til Linux / SPLAT. Ingen include,
# libs eller andet.
# 
# Alle programmer skal installeres under /var/opt/UNItools.
# 
# Programmer mv: /var/opt/UNItools/bin
# Konfiguration: /var/opt/UNItools/etc/p0f
# Dokumentation: /var/opt/UNItools/docs/p0f.2.0.5
# 
# Det er *ikke* programpakker i Linux format (pkg) men blot en
# installation af programmet p0f.
# 
#  1	Download programpakken p0f til /lan/ssi/projects/UNItools/src/Linux/2.4.21-20cpsmp/pkgs/p0f.
# 	L�s hvordan programpakken overs�ttes og installeres i dokumentationen
# 	for programpakken (typisk README og INSTALL).
# 
# 	wget -N http://lcamtuf.coredump.cx/p0f/p0f-2.0.5.tgz
# 
	/bin/rm -fr p0f-2.0.5
 	/bin/gtar xvzf p0f-2.0.5.tgz
	mv p0f p0f-2.0.5
# 
#  2	Ret dokumentet CFG - det blev lavet med scriptet pkg_mk_cfg.sh
#  	Du skal angive hvordan programmet overs�ttes og installeres,
# 	dvs.  argumenterne til config/configure og Make, samt om der
# 	skal anvendes et start/stop script.
# 
# 	Du skal som minimum udfylde NAME og VENDOR.
# 
#  3	Overs�t programpakken og lav en midlertidig installation. Hvis
#  	programmerne skal overs�ttes statisk, *kan* det v�re n�dvendigt
# 	at s�tte variablen LDFLAGS=-static
# 
export LDFLAGS=-static
# 

	(

	cd p0f-2.0.5

	test -f mk/Linux.DIST || cp mk/Linux mk/Linux.DIST
	test -f config.h.DIST || cp config.h config.h.DIST

	sed '
		s%^CC.*%CC      = gcc -static%g
		s%/usr/sbin/%/var/opt/UNItools/bin/%g
		s%/etc/p0f%/var/opt/UNItools/etc/p0f%g
		s%/usr/man/man1%/var/opt/UNItools/share/man/man1%g
		s%/usr/local/man/man1%/var/opt/UNItools/share/man/man1%g
		s%mkdir%mkdir -p%g
	' < mk/Linux.DIST > mk/Linux

	sed 's%#.*define CONFIG_DIR.*"/etc/p0f"%#    define CONFIG_DIR  "/var/opt/UNItools/etc/p0f"%' < config.h.DIST > config.h

	)

 	pkg_fake_install.sh -n ./CFG
# 
# 	hvilket vil konfigurere, overs�tte og installere programpakken,
# 	hvis den er skrevet med automake/configure/osv. Fjern '-n' hvis
# 	du eller andre anvender programmer i /var/opt/UNItools; flaget
# 	betyder 'prompt mig ikke'.
# 
# 	I modsat fald m� du rette CFG eller skrive kommandoerne her.
# 
# 	Pakken flyttes efterf�lgende til
# 
# 	p0f.2.0.5.install.tmp
# 
# 	Bem�rk, at alt i dette katalog er MIDLERTIDIGT, og slettes hver
# 	gang pkg_fake_install.sh udf�res!
# 
# 	Dokumentation (installeret sim man - sider) laves i tre udgaver
# 	som html, txt og pdf og gemmes i docs/p0f.2.0.5.  Se efter
# 	om der er andre dokumenter der burde kopieres med (licens og
# 	andet).
# 
#  5	Lav et dokument der beskriver afh�ngigheder (rpm'er) for programpakken.
#  	Det er ikke str�ngt n�dvendigt, men jeg forventer en gang med tiden
# 	at f� det her lavet om, s� man faktisk laver rigtige rpm'er.
# 
 	pkg_mkrpm_dep.sh ./CFG depend
#  	
# 	Kr�ver programpakken start/stop scripts skal de laves andetsteds
#  	i forbindelse med setup.sh af UINtools.
# 
#  6 	Tilf�j evt. ekstra dokumenter der ikke kommer med i forbindelse
# 	med installation (make install).
# 
# 	Du kan med fordel s�tte INSTALL_MORE til et script, der vil
# 	kopiere de relevante dokumenter til p0f.2.0.5.install.tmp.
# 
# 	Du skal selv lave scriptet, men et eksempel ligger ved siden
# 	af dette dokument, med navnet install_more.sh.
# 	Ellers m� du skrive kommandoerne til at g�re tingene herunder.
# 
# 7     Lav dokumentation for hvad programpakken best�r af osv. med
#       kommandoen
#
        pkg_mkdoc.sh ./CFG
#
# 8     Lav et tgz arkiv med relative stinavne af det installerede.
#
        pkg_build.sh ./CFG
#
# 9     Installer programpakken (evt. midlertidig) p� en firewall og
#       test den. Forts�t hvis alt viser sit at v�re OK.
#
#       Kopier $PKG.$VER.install-archive.tgz til en firewall, og
#       pak arkivet ud. Stinavne er relative til '.' Der ligger et
#       simpelt test script under var/opt/UNItools/setup. Det kan anvendes
#       til at slette alt med, hvis du installerer fra /
#  
# 10    Virker alt efter hensigten l�gges programmer mv i
#        /var/opt/UNItools og div. index sider mv. opdateres. Det sker
#        n�r du udf�re kommandoen
# 
        pkg_install.sh ./CFG
# 
# 11	Ryd op, slet overfl�dige dokumenter osv. (make distclean)
# 
# 	pkg_clean.sh	./CFG
# 
# 
# Hvis du beg�r en fejl og har en mistanke om, at /var/opt/UNItools er
# grisset til, sletter du det hele, og udf�rer kommandoen
# 
# 	pkg_do_it_all_for_all_known_packages
# 
# 
# --
