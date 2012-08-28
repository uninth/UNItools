# #!/bin/sh
# ++
#                                     Fri Jul  7 12:26:13 CEST 2006
# 
# Det følgende ender med en programpakke bestående af program(mer),
# README, eksempler, manual(er) osv. til Linux / SPLAT. Ingen include,
# libs eller andet.
# 
# Alle programmer skal installeres under /var/opt/UNItools.
# 
# Programmer mv: /var/opt/UNItools/bin
# Konfiguration: /var/opt/UNItools/etc/hping
# Dokumentation: /var/opt/UNItools/docs/hping.2.0.0-rc3
# 
# Det er *ikke* programpakker i Linux format (pkg) men blot en
# installation af programmet hping.
# 
#  1	Download programpakken hping til /home/projects/UNItools/src/Linux/2.4.21-20cpsmp/pkgs/hping.
# 	Læs hvordan programpakken oversættes og installeres i dokumentationen
# 	for programpakken (typisk README og INSTALL).
# 
# 	wget -N http://www.hping.org/hping2.0.0-rc3.tar.gz
# 
 	/bin/gtar xvzf hping2.0.0-rc3.tar.gz
# 
#  2	Ret dokumentet CFG - det blev lavet med scriptet pkg_mk_cfg.sh
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
# export LDFLAGS=-static
# 
(
	/bin/rm -f hping2.0.0-rc3
	/bin/ln -sf hping2-rc3 hping2.0.0-rc3 

	cd hping2.0.0-rc3

	test -f Makefile.in.dist || cp Makefile.in Makefile.in.dist

	sed '/^install:/,/^$/d' < Makefile.in.dist > Makefile.in

	cat << 'EOF' >> Makefile.in
install: strip
	cp -f hping2 /var/opt/UNItools/bin;
	chmod 755 /var/opt/UNItools/bin/hping2;
	ln -sf /var/opt/UNItools/bin/hping2 /var/opt/UNItools/bin/hping;
	mkdir -p /var/opt/UNItools/share/man/man8;
	cp ./docs/hping2.8 /var/opt/UNItools/share/man/man8;
	chmod 644 /var/opt/UNItools/share/man/man8/hping2.8;
EOF

)

 	pkg_fake_install.sh -n ./CFG
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
# 	hping.2.0.0-rc3.install.tmp
# 
# 	Bemærk, at alt i dette katalog er MIDLERTIDIGT, og slettes hver
# 	gang pkg_fake_install.sh udføres!
# 
# 	Dokumentation (installeret sim man - sider) laves i tre udgaver
# 	som html, txt og pdf og gemmes i docs/hping.2.0.0-rc3.  Se efter
# 	om der er andre dokumenter der burde kopieres med (licens og
# 	andet).
# 
#  5	Lav et dokument der beskriver afhængigheder (rpm'er) for programpakken.
#  	Det er ikke strængt nødvendigt, men jeg forventer en gang med tiden
# 	at få det her lavet om, så man faktisk laver rigtige rpm'er.
# 
 	pkg_mkrpm_dep.sh ./CFG depend
#  	
# 	Kræver programpakken start/stop scripts skal de laves andetsteds
#  	i forbindelse med setup.sh af UINtools.
# 
#  6 	Tilføj evt. ekstra dokumenter der ikke kommer med i forbindelse
# 	med installation (make install).
# 
# 	Du kan med fordel sætte INSTALL_MORE til et script, der vil
# 	kopiere de relevante dokumenter til hping.2.0.0-rc3.install.tmp.
# 
# 	Du skal selv lave scriptet, men et eksempel ligger ved siden
# 	af dette dokument, med navnet install_more.sh.
# 	Ellers må du skrive kommandoerne til at gøre tingene herunder.
# 
#  7	Lav dokumentation for hvad programpakken består af osv. med
#  	kommandoen
# 
 	pkg_mkdoc.sh ./CFG
# 
#  8	Lav et tgz arkiv med relative stinavne af det installerede.
# 
 	pkg_build.sh ./CFG
# 
#  9	Installer programpakken (evt. midlertidig) på en firewall og
#  	test den. Fortsæt hvis alt viser sit at være OK.
#  
# 10	Virker alt efter hensigten lægges programmer mv i
# 	 /var/opt/UNItools og div. index sider mv. opdateres. Det sker
# 	 når du udføre kommandoen
# 
 	pkg_install.sh ./CFG
# 
# 11	Ryd op, slet overflødige dokumenter osv. (make distclean)
# 
 	pkg_clean.sh	./CFG
# 
# 
# Hvis du begår en fejl og har en mistanke om, at /var/opt/UNItools er
# grisset til, sletter du det hele, og udfører kommandoen
# 
# 	pkg_do_it_all_for_all_known_packages
# 
# 
# --
