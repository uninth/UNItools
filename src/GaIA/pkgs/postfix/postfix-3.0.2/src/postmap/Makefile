# Do not edit -- this file documents how Postfix was built for your machine.
#----------------------------------------------------------------
# Start of summary of user-configurable 'make makefiles' options.
# CCARGS=
# AUXLIBS=
# shared=
# dynamicmaps=
# pie=
# command_directory=/var/opt/UNItools/postfix/usr/sbin
# config_directory=/var/opt/UNItools/postfix/etc/postfix
# daemon_directory=/var/opt/UNItools/postfix/usr/libexec/postfix
# data_directory=/var/opt/UNItools/postfix/var/lib/postfix
# mailq_path=/var/opt/UNItools/postfix/usr/bin/mailq
# meta_directory=/var/opt/UNItools/postfix/libexec/postfix
# newaliases_path=/var/opt/UNItools/postfix/usr/bin/newaliases
# queue_directory=/var/opt/UNItools/postfix/var/spool/postfix
# sendmail_path=/var/opt/UNItools/postfix/usr/sbin/sendmail
# manpage_directory=/var/opt/UNItools/postfix/usr/local/man
# End of summary of user-configurable 'make makefiles' options.
#--------------------------------------------------------------
# System-dependent settings and compiler/linker overrides.
SYSTYPE	= LINUX2
_AR	= ar
ARFL	= rv
_RANLIB	= ranlib
SYSLIBS	= -ldb -lnsl -lresolv -ldl 
CC	= gcc -I. -I../../include -DNO_EPOLL -DNO_EAI -DHAS_PCRE -I/usr/include/pcre -DDEF_COMMAND_DIR=\"/var/opt/UNItools/postfix/usr/sbin\" -DDEF_CONFIG_DIR=\"/var/opt/UNItools/postfix/etc/postfix\" -DDEF_DAEMON_DIR=\"/var/opt/UNItools/postfix/usr/libexec/postfix\" -DDEF_DATA_DIR=\"/var/opt/UNItools/postfix/var/lib/postfix\" -DDEF_MAILQ_PATH=\"/var/opt/UNItools/postfix/usr/bin/mailq\" -DDEF_META_DIR=\"/var/opt/UNItools/postfix/libexec/postfix\" -DDEF_NEWALIAS_PATH=\"/var/opt/UNItools/postfix/usr/bin/newaliases\" -DDEF_QUEUE_DIR=\"/var/opt/UNItools/postfix/var/spool/postfix\" -DDEF_SENDMAIL_PATH=\"/var/opt/UNItools/postfix/usr/sbin/sendmail\" -DDEF_MANPAGE_DIR=\"/var/opt/UNItools/postfix/usr/local/man\" -UUSE_DYNAMIC_LIBS -DDEF_SHLIB_DIR=\"no\" -UUSE_DYNAMIC_MAPS -Wmissing-prototypes -Wformat -Wno-comment -I. -I../../include -DNO_EAI -DDEF_COMMAND_DIR=\"/var/opt/UNItools/postfix/usr/sbin\" -DDEF_CONFIG_DIR=\"/var/opt/UNItools/postfix/etc/postfix\" -DDEF_DAEMON_DIR=\"/var/opt/UNItools/postfix/usr/libexec/postfix\" -DDEF_DATA_DIR=\"/var/opt/UNItools/postfix/var/lib/postfix\" -DDEF_MAILQ_PATH=\"/var/opt/UNItools/postfix/usr/bin/mailq\" -DDEF_META_DIR=\"/var/opt/UNItools/postfix/libexec/postfix\" -DDEF_NEWALIAS_PATH=\"/var/opt/UNItools/postfix/usr/bin/newaliases\" -DDEF_QUEUE_DIR=\"/var/opt/UNItools/postfix/var/spool/postfix\" -DDEF_SENDMAIL_PATH=\"/var/opt/UNItools/postfix/usr/sbin/sendmail\" -DDEF_MANPAGE_DIR=\"/var/opt/UNItools/postfix/usr/local/man\" -UUSE_DYNAMIC_LIBS -DDEF_SHLIB_DIR=\"no\" -UUSE_DYNAMIC_MAPS -Wmissing-prototypes -Wformat -Wno-comment -I. -I../../include -DNO_EAI -DDEF_COMMAND_DIR=\"/var/opt/UNItools/postfix/usr/sbin\" -DDEF_CONFIG_DIR=\"/var/opt/UNItools/postfix/etc/postfix\" -DDEF_DAEMON_DIR=\"/var/opt/UNItools/postfix/usr/libexec/postfix\" -DDEF_DATA_DIR=\"/var/opt/UNItools/postfix/var/lib/postfix\" -DDEF_MAILQ_PATH=\"/var/opt/UNItools/postfix/usr/bin/mailq\" -DDEF_META_DIR=\"/var/opt/UNItools/postfix/libexec/postfix\" -DDEF_NEWALIAS_PATH=\"/var/opt/UNItools/postfix/usr/bin/newaliases\" -DDEF_QUEUE_DIR=\"/var/opt/UNItools/postfix/var/spool/postfix\" -DDEF_SENDMAIL_PATH=\"/var/opt/UNItools/postfix/usr/sbin/sendmail\" -DDEF_MANPAGE_DIR=\"/var/opt/UNItools/postfix/usr/local/man\" -UUSE_DYNAMIC_LIBS -DDEF_SHLIB_DIR=\"no\" -UUSE_DYNAMIC_MAPS $(WARN)
OPT	= -O
DEBUG	= -g
AWK	= awk
STRCASE = 
EXPORT	= CCARGS='-I. -I../../include -DNO_EAI -DDEF_COMMAND_DIR=\"/var/opt/UNItools/postfix/usr/sbin\" -DDEF_CONFIG_DIR=\"/var/opt/UNItools/postfix/etc/postfix\" -DDEF_DAEMON_DIR=\"/var/opt/UNItools/postfix/usr/libexec/postfix\" -DDEF_DATA_DIR=\"/var/opt/UNItools/postfix/var/lib/postfix\" -DDEF_MAILQ_PATH=\"/var/opt/UNItools/postfix/usr/bin/mailq\" -DDEF_META_DIR=\"/var/opt/UNItools/postfix/libexec/postfix\" -DDEF_NEWALIAS_PATH=\"/var/opt/UNItools/postfix/usr/bin/newaliases\" -DDEF_QUEUE_DIR=\"/var/opt/UNItools/postfix/var/spool/postfix\" -DDEF_SENDMAIL_PATH=\"/var/opt/UNItools/postfix/usr/sbin/sendmail\" -DDEF_MANPAGE_DIR=\"/var/opt/UNItools/postfix/usr/local/man\" -UUSE_DYNAMIC_LIBS -DDEF_SHLIB_DIR=\"no\" -UUSE_DYNAMIC_MAPS' OPT='-O' DEBUG='-g'
WARN	= -Wall -Wno-comment -Wformat -Wimplicit -Wmissing-prototypes \
	-Wparentheses -Wstrict-prototypes -Wswitch -Wuninitialized \
	-Wunused -Wno-missing-braces
DEFINED_MAP_TYPES = 
MAKE_FIX = 
# Switch between Postfix static and dynamically-linked libraries.
AR	= ar
RANLIB	= ranlib
LIB_PREFIX = 
LIB_SUFFIX = .a
SHLIB_CFLAGS = 
SHLIB_DIR = no
SHLIB_ENV = 
SHLIB_LD = :
SHLIB_SYSLIBS = 
SHLIB_RPATH = 
# Switch between dynamicmaps.cf plugins and hard-linked databases.
NON_PLUGIN_MAP_OBJ = $(MAP_OBJ)
PLUGIN_MAP_OBJ = 
PLUGIN_MAP_OBJ_UPDATE = 
PLUGIN_MAP_SO_MAKE = 
PLUGIN_MAP_SO_UPDATE = 
PLUGIN_LD = 
# Application-specific rules.
SHELL	= /bin/sh
SRCS	= postmap.c 
OBJS	= postmap.o
HDRS	= 
TESTSRC	= 
DEFS	= -I. -I$(INC_DIR) -D$(SYSTYPE)
CFLAGS	= $(DEBUG) $(OPT) $(DEFS)
TESTPROG= 
PROG	= postmap
INC_DIR	= ../../include
LIBS	= ../../lib/lib$(LIB_PREFIX)global$(LIB_SUFFIX) \
	../../lib/lib$(LIB_PREFIX)util$(LIB_SUFFIX)

.c.o:;	$(CC) $(CFLAGS) -c $*.c

$(PROG):	$(OBJS) $(LIBS)
	$(CC) $(CFLAGS) $(SHLIB_RPATH) -o $@ $(OBJS) $(LIBS) $(SYSLIBS)

$(OBJS): ../../conf/makedefs.out

Makefile: Makefile.in
	cat ../../conf/makedefs.out $? >$@

update: ../../bin/$(PROG)

../../bin/$(PROG): $(PROG)
	cp $(PROG) ../../bin

tests:	test1 test2 fail_test

root_tests:

test1:	$(PROG) map.in map-abc1.ref map-ghi1.ref map-uABC1.ref
	./$(PROG) map.in
	for key in abc ghi; \
	do \
	    ./$(PROG) -q $${key} map.in | diff map-$${key}1.ref -; \
	done
	./$(PROG) -f map.in
	for key in ABC; \
	do \
	    ./$(PROG) -fq $${key} map.in | diff map-u$${key}1.ref -; \
	done
	rm -f map.in.db

test2:	$(PROG) map.in map-abc2.ref map-ghi2.ref map-uABC2.ref
	./$(PROG) map.in
	for key in abc ghi; \
	do \
	    echo $${key} | ./$(PROG) -q - map.in | diff map-$${key}2.ref -; \
	done
	./$(PROG) -f map.in
	for key in ABC; \
	do \
	    echo $${key} | ./$(PROG) -fq - map.in | diff map-u$${key}2.ref -; \
	done
	rm -f map.in.db

fail_test: $(PROG) aliases fail_test.in fail_test.ref
	-(sh fail_test.in || exit 0) 2>&1 | \
	    sed 's/No error:/Unknown error:/' > fail_test.tmp
	diff fail_test.ref fail_test.tmp
	rm -f fail_test.tmp

printfck: $(OBJS) $(PROG)
	rm -rf printfck
	mkdir printfck
	sed '1,/^# do not edit/!d' Makefile >printfck/Makefile
	set -e; for i in *.c; do printfck -f .printfck $$i >printfck/$$i; done
	cd printfck; make "INC_DIR=../../../include" `cd ..; ls *.o`

lint:
	lint $(DEFS) $(SRCS) $(LINTFIX)

clean:
	rm -f *.o *core $(PROG) $(TESTPROG) junk map.in.db
	rm -rf printfck

tidy:	clean

depend: $(MAKES)
	(sed '1,/^# do not edit/!d' Makefile.in; \
	set -e; for i in [a-z][a-z0-9]*.c; do \
	    $(CC) -E $(DEFS) $(INCL) $$i | grep -v '[<>]' | sed -n -e '/^# *1 *"\([^"]*\)".*/{' \
	    -e 's//'`echo $$i|sed 's/c$$/o/'`': \1/' \
	    -e 's/o: \.\//o: /' -e p -e '}' ; \
	done | sort -u) | grep -v '[.][o][:][ ][/]' >$$$$ && mv $$$$ Makefile.in
	@$(EXPORT) make -f Makefile.in Makefile 1>&2

# do not edit below this line - it is generated by 'make depend'
postmap.o: ../../include/argv.h
postmap.o: ../../include/check_arg.h
postmap.o: ../../include/dict.h
postmap.o: ../../include/dict_proxy.h
postmap.o: ../../include/header_opts.h
postmap.o: ../../include/mail_conf.h
postmap.o: ../../include/mail_dict.h
postmap.o: ../../include/mail_params.h
postmap.o: ../../include/mail_task.h
postmap.o: ../../include/mail_version.h
postmap.o: ../../include/mime_state.h
postmap.o: ../../include/mkmap.h
postmap.o: ../../include/msg.h
postmap.o: ../../include/msg_syslog.h
postmap.o: ../../include/msg_vstream.h
postmap.o: ../../include/myflock.h
postmap.o: ../../include/mymalloc.h
postmap.o: ../../include/readlline.h
postmap.o: ../../include/rec_type.h
postmap.o: ../../include/set_eugid.h
postmap.o: ../../include/split_at.h
postmap.o: ../../include/stringops.h
postmap.o: ../../include/sys_defs.h
postmap.o: ../../include/vbuf.h
postmap.o: ../../include/vstream.h
postmap.o: ../../include/vstring.h
postmap.o: ../../include/vstring_vstream.h
postmap.o: ../../include/warn_stat.h
postmap.o: postmap.c
