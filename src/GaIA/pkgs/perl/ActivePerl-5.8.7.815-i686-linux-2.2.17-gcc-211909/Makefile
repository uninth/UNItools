all:
	@echo done

install:	
	./AP_install.exp
	/bin/rm -fr /var/opt/UNItools/man /var/tmp/html
	# flyt html -> /var/tmp, flyt tilbage efter kald af pkg_conbat
	# for at undgå konvertering af html til pdf
	/bin/mv /var/opt/UNItools/html /var/tmp/html

