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
SRCS	= xsasl_server.c xsasl_cyrus_server.c xsasl_cyrus_log.c \
	xsasl_cyrus_security.c xsasl_client.c xsasl_cyrus_client.c \
	xsasl_dovecot_server.c
OBJS	= xsasl_server.o xsasl_cyrus_server.o xsasl_cyrus_log.o \
	xsasl_cyrus_security.o xsasl_client.o xsasl_cyrus_client.o \
	xsasl_dovecot_server.o
HDRS	= xsasl.h
TESTSRC	= 
DEFS	= -I. -I$(INC_DIR) -D$(SYSTYPE)
CFLAGS	= $(DEBUG) $(OPT) $(DEFS)
INCL	=
LIB	= libxsasl.a
TESTPROG= 

LIBS	= ../../lib/lib$(LIB_PERFIX)global$(LIB_SUFFIX) \
	../../lib/lib$(LIB_PERFIX)util$(LIB_SUFFIX)
LIB_DIR	= ../../lib
INC_DIR	= ../../include
MAKES	=

.c.o:;	$(CC) $(CFLAGS) -c $*.c

all: $(LIB)

$(OBJS): ../../conf/makedefs.out

Makefile: Makefile.in
	cat ../../conf/makedefs.out $? >$@

test:	$(TESTPROG)

tests:

root_tests:

$(LIB):	$(OBJS)
	$(_AR) $(ARFL) $(LIB) $?
	$(_RANLIB) $(LIB)

$(LIB_DIR)/$(LIB): $(LIB)
	cp $(LIB) $(LIB_DIR)
	$(_RANLIB) $(LIB_DIR)/$(LIB)

update: $(LIB_DIR)/$(LIB) $(HDRS)
	-for i in $(HDRS); \
	do \
	  cmp -s $$i $(INC_DIR)/$$i 2>/dev/null || cp $$i $(INC_DIR); \
	done
	cd $(INC_DIR); chmod 644 $(HDRS)

printfck: $(OBJS) $(PROG)
	rm -rf printfck
	mkdir printfck
	cp *.h printfck
	sed '1,/^# do not edit/!d' Makefile >printfck/Makefile
	set -e; for i in *.c; do printfck -f .printfck $$i >printfck/$$i; done
	cd printfck; make "INC_DIR=../../../include" `cd ..; ls *.o`

lint:
	lint $(DEFS) $(SRCS) $(LINTFIX)

clean:
	rm -f *.o $(LIB) *core $(TESTPROG) junk
	rm -rf printfck

tidy:	clean

foo: $(LIB) $(LIBS)
	mv $@.o junk
	$(CC) $(CFLAGS) -DTEST -o $@ $@.c $(LIB) $(LIBS) $(SYSLIBS)
	mv junk $@.o

depend: $(MAKES)
	(sed '1,/^# do not edit/!d' Makefile.in; \
	set -e; for i in [a-z][a-z0-9]*.c; do \
	    $(CC) -E $(DEFS) $(INCL) $$i | grep -v '[<>]' | sed -n -e '/^# *1 *"\([^"]*\)".*/{' \
	    -e 's//'`echo $$i|sed 's/c$$/o/'`': \1/' \
	    -e 's/o: \.\//o: /' -e p -e '}' ; \
	done | sort -u) | grep -v '[.][o][:][ ][/]' >$$$$ && mv $$$$ Makefile.in
	@$(EXPORT) make -f Makefile.in Makefile 1>&2

# do not edit below this line - it is generated by 'make depend'
xsasl_client.o: ../../include/argv.h
xsasl_client.o: ../../include/check_arg.h
xsasl_client.o: ../../include/msg.h
xsasl_client.o: ../../include/mymalloc.h
xsasl_client.o: ../../include/sys_defs.h
xsasl_client.o: ../../include/vbuf.h
xsasl_client.o: ../../include/vstream.h
xsasl_client.o: ../../include/vstring.h
xsasl_client.o: xsasl.h
xsasl_client.o: xsasl_client.c
xsasl_client.o: xsasl_cyrus.h
xsasl_cyrus_client.o: ../../include/argv.h
xsasl_cyrus_client.o: ../../include/check_arg.h
xsasl_cyrus_client.o: ../../include/mail_params.h
xsasl_cyrus_client.o: ../../include/msg.h
xsasl_cyrus_client.o: ../../include/mymalloc.h
xsasl_cyrus_client.o: ../../include/stringops.h
xsasl_cyrus_client.o: ../../include/sys_defs.h
xsasl_cyrus_client.o: ../../include/vbuf.h
xsasl_cyrus_client.o: ../../include/vstream.h
xsasl_cyrus_client.o: ../../include/vstring.h
xsasl_cyrus_client.o: xsasl.h
xsasl_cyrus_client.o: xsasl_cyrus.h
xsasl_cyrus_client.o: xsasl_cyrus_client.c
xsasl_cyrus_client.o: xsasl_cyrus_common.h
xsasl_cyrus_log.o: ../../include/msg.h
xsasl_cyrus_log.o: ../../include/sys_defs.h
xsasl_cyrus_log.o: xsasl_cyrus_common.h
xsasl_cyrus_log.o: xsasl_cyrus_log.c
xsasl_cyrus_security.o: ../../include/check_arg.h
xsasl_cyrus_security.o: ../../include/name_mask.h
xsasl_cyrus_security.o: ../../include/sys_defs.h
xsasl_cyrus_security.o: ../../include/vbuf.h
xsasl_cyrus_security.o: ../../include/vstring.h
xsasl_cyrus_security.o: xsasl_cyrus_common.h
xsasl_cyrus_security.o: xsasl_cyrus_security.c
xsasl_cyrus_server.o: ../../include/argv.h
xsasl_cyrus_server.o: ../../include/check_arg.h
xsasl_cyrus_server.o: ../../include/mail_params.h
xsasl_cyrus_server.o: ../../include/msg.h
xsasl_cyrus_server.o: ../../include/mymalloc.h
xsasl_cyrus_server.o: ../../include/name_mask.h
xsasl_cyrus_server.o: ../../include/stringops.h
xsasl_cyrus_server.o: ../../include/sys_defs.h
xsasl_cyrus_server.o: ../../include/vbuf.h
xsasl_cyrus_server.o: ../../include/vstream.h
xsasl_cyrus_server.o: ../../include/vstring.h
xsasl_cyrus_server.o: xsasl.h
xsasl_cyrus_server.o: xsasl_cyrus.h
xsasl_cyrus_server.o: xsasl_cyrus_common.h
xsasl_cyrus_server.o: xsasl_cyrus_server.c
xsasl_dovecot_server.o: ../../include/argv.h
xsasl_dovecot_server.o: ../../include/check_arg.h
xsasl_dovecot_server.o: ../../include/connect.h
xsasl_dovecot_server.o: ../../include/iostuff.h
xsasl_dovecot_server.o: ../../include/mail_params.h
xsasl_dovecot_server.o: ../../include/msg.h
xsasl_dovecot_server.o: ../../include/myaddrinfo.h
xsasl_dovecot_server.o: ../../include/mymalloc.h
xsasl_dovecot_server.o: ../../include/name_mask.h
xsasl_dovecot_server.o: ../../include/split_at.h
xsasl_dovecot_server.o: ../../include/stringops.h
xsasl_dovecot_server.o: ../../include/sys_defs.h
xsasl_dovecot_server.o: ../../include/vbuf.h
xsasl_dovecot_server.o: ../../include/vstream.h
xsasl_dovecot_server.o: ../../include/vstring.h
xsasl_dovecot_server.o: ../../include/vstring_vstream.h
xsasl_dovecot_server.o: xsasl.h
xsasl_dovecot_server.o: xsasl_dovecot.h
xsasl_dovecot_server.o: xsasl_dovecot_server.c
xsasl_server.o: ../../include/argv.h
xsasl_server.o: ../../include/check_arg.h
xsasl_server.o: ../../include/msg.h
xsasl_server.o: ../../include/mymalloc.h
xsasl_server.o: ../../include/sys_defs.h
xsasl_server.o: ../../include/vbuf.h
xsasl_server.o: ../../include/vstream.h
xsasl_server.o: ../../include/vstring.h
xsasl_server.o: xsasl.h
xsasl_server.o: xsasl_cyrus.h
xsasl_server.o: xsasl_dovecot.h
xsasl_server.o: xsasl_server.c
