# #!/bin/sh
# ++
#                                      Mon Mar 13 23:16:41 CET 2006
# 
# Det f�lgende ender med en programpakke best�ende af program(mer),
# README, eksempler, manual(er) osv. til Linux / SPLAT. Ingen include,
# libs eller andet.
# 
# Alle programmer skal installeres under /var/opt/UNItools.
# 
# Programmer mv: /var/opt/UNItools/bin
# Konfiguration: /var/opt/UNItools/etc/bmon
# Dokumentation: /var/opt/UNItools/docs/bmon.2.0.1
# 
# Det er *ikke* programpakker i Linux format (pkg) men blot en
# installation af programmet bmon.
# 
#  1	Download programpakken bmon til /home/projects/UNItools/src/Linux/2.4.21-20cpsmp/pkgs/bmon.
# 	L�s hvordan programpakken overs�ttes og installeres i dokumentationen
# 	for programpakken (typisk README og INSTALL).
# 
# 	wget -N http://freshmeat.net/redir/bmon/36580/url_tgz/bmon-2.0.1.tar.gz
# 
# 	/bin/gtar xvzf bmon-2.0.1.tar.gz
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
# 	bmon.2.0.1.install.tmp
# 
# 	Bem�rk, at alt i dette katalog er MIDLERTIDIGT, og slettes hver
# 	gang pkg_fake_install.sh udf�res!
# 
# 	Dokumentation (installeret sim man - sider) laves i tre udgaver
# 	som html, txt og pdf og gemmes i docs/bmon.2.0.1.  Se efter
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
# 	kopiere de relevante dokumenter til bmon.2.0.1.install.tmp.
# 
# 	Du skal selv lave scriptet, men et eksempel ligger ved siden
# 	af dette dokument, med navnet install_more.sh.
# 	Ellers m� du skrive kommandoerne til at g�re tingene herunder.
# 
#  7	Lav dokumentation for hvad programpakken best�r af osv. med
#  	kommandoen
# 
 	pkg_mkdoc.sh ./CFG
# 
#  8	Lav et tgz arkiv med relative stinavne af det installerede.
# 
 	pkg_build.sh ./CFG
# 
#  9	Installer programpakken (evt. midlertidig) p� en firewall og
#  	test den. Forts�t hvis alt viser sit at v�re OK.
#  
# 10	Virker alt efter hensigten l�gges programmer mv i
# 	 /var/opt/UNItools og div. index sider mv. opdateres. Det sker
# 	 n�r du udf�re kommandoen
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
