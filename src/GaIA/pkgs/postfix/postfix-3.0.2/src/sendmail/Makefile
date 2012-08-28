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
SRCS	= sendmail.c
OBJS	= sendmail.o
HDRS	= 
TESTSRC	= 
DEFS	= -I. -I$(INC_DIR) -D$(SYSTYPE)
CFLAGS	= $(DEBUG) $(OPT) $(DEFS)
TESTPROG=
PROG	= sendmail
INC_DIR	= ../../include
LIBS	= ../../lib/lib$(LIB_PREFIX)global$(LIB_SUFFIX) \
	../../lib/lib$(LIB_PREFIX)util$(LIB_SUFFIX)

.c.o:;	$(CC) $(CFLAGS) -c $*.c

$(PROG): $(OBJS) $(LIBS)
	$(CC) $(CFLAGS) $(SHLIB_RPATH) -o $@ $(OBJS) $(LIBS) $(SYSLIBS)

$(OBJS): ../../conf/makedefs.out

Makefile: Makefile.in
	cat ../../conf/makedefs.out $? >$@

test:	$(TESTPROG)

tests:

root_tests:

update: ../../bin/$(PROG)

../../bin/$(PROG): $(PROG)
	cp $(PROG) ../../bin

printfck: $(OBJS) $(PROG)
	rm -rf printfck
	mkdir printfck
	sed '1,/^# do not edit/!d' Makefile >printfck/Makefile
	set -e; for i in *.c; do printfck -f .printfck $$i >printfck/$$i; done
	cd printfck; make "INC_DIR=../../../include" `cd ..; ls *.o`

lint:
	lint $(DEFS) $(SRCS) $(LINTFIX)

clean:
	rm -f *.o *core $(PROG) $(TESTPROG) junk 
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
sendmail.o: ../../include/argv.h
sendmail.o: ../../include/attr.h
sendmail.o: ../../include/check_arg.h
sendmail.o: ../../include/cleanup_user.h
sendmail.o: ../../include/connect.h
sendmail.o: ../../include/debug_process.h
sendmail.o: ../../include/deliver_request.h
sendmail.o: ../../include/dsn.h
sendmail.o: ../../include/dsn_mask.h
sendmail.o: ../../include/fullname.h
sendmail.o: ../../include/header_opts.h
sendmail.o: ../../include/htable.h
sendmail.o: ../../include/iostuff.h
sendmail.o: ../../include/mail_conf.h
sendmail.o: ../../include/mail_flush.h
sendmail.o: ../../include/mail_params.h
sendmail.o: ../../include/mail_proto.h
sendmail.o: ../../include/mail_queue.h
sendmail.o: ../../include/mail_run.h
sendmail.o: ../../include/mail_stream.h
sendmail.o: ../../include/mail_task.h
sendmail.o: ../../include/mail_version.h
sendmail.o: ../../include/mime_state.h
sendmail.o: ../../include/msg.h
sendmail.o: ../../include/msg_stats.h
sendmail.o: ../../include/msg_syslog.h
sendmail.o: ../../include/msg_vstream.h
sendmail.o: ../../include/mymalloc.h
sendmail.o: ../../include/name_code.h
sendmail.o: ../../include/nvtable.h
sendmail.o: ../../include/rec_streamlf.h
sendmail.o: ../../include/rec_type.h
sendmail.o: ../../include/recipient_list.h
sendmail.o: ../../include/record.h
sendmail.o: ../../include/resolve_clnt.h
sendmail.o: ../../include/safe.h
sendmail.o: ../../include/set_ugid.h
sendmail.o: ../../include/split_at.h
sendmail.o: ../../include/stringops.h
sendmail.o: ../../include/sys_defs.h
sendmail.o: ../../include/tok822.h
sendmail.o: ../../include/user_acl.h
sendmail.o: ../../include/username.h
sendmail.o: ../../include/vbuf.h
sendmail.o: ../../include/verp_sender.h
sendmail.o: ../../include/vstream.h
sendmail.o: ../../include/vstring.h
sendmail.o: ../../include/vstring_vstream.h
sendmail.o: ../../include/warn_stat.h
sendmail.o: sendmail.c
