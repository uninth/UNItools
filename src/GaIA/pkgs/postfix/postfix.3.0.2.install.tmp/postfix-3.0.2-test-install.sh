#! /bin/sh
#
# Test script for postfix
#
ERROR=0
TMPROOT=/lan/ssi/shared/software/internal/UNItools/src/GaIA/pkgs/postfix/postfix.3.0.2.install.tmp

function rmfiles()
{
	echo "removing files ..."
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/QSHAPE_README
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/XCLIENT_README.html
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/LINUX_README.html
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/ADDRESS_CLASS_README
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/BASIC_CONFIGURATION_README.html
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/POSTSCREEN_README
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/TLS_LEGACY_README.html
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/SMTPD_POLICY_README
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/CDB_README
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/VERP_README
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/NFS_README
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/PCRE_README
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/MAILDROP_README.html
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/STRESS_README.html
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/RESTRICTION_CLASS_README
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/OVERVIEW
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/BASIC_CONFIGURATION_README
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/MEMCACHE_README.html
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/MEMCACHE_README
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/ETRN_README.html
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/SASL_README.html
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/SCHEDULER_README
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/CONTENT_INSPECTION_README.html
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/VERP_README.html
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/LMDB_README
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/ADDRESS_VERIFICATION_README.html
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/DSN_README.html
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/BUILTIN_FILTER_README.html
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/DATABASE_README.html
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/BUILTIN_FILTER_README
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/LICENSE
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/DEBUG_README
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/PGSQL_README
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/TLS_LICENSE
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/PACKAGE_README.html
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/ULTRIX_README
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/ADDRESS_VERIFICATION_README
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/MULTI_INSTANCE_README
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/POSTSCREEN_README.html
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/README
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/QSHAPE_README.html
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/SMTPD_ACCESS_README.html
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/VIRTUAL_README
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/SCHEDULER_README.html
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/newaliases.1.html
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/MYSQL_README.html
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/QMQP_README
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/SMTPD_ACCESS_README
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/readme2html
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/UUCP_README.html
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/LMDB_README.html
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/DSN_README
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/SMTPD_PROXY_README
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/RESTRICTION_CLASS_README.html
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/FILTER_README.html
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/BACKSCATTER_README.html
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/TUNING_README
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/SOHO_README.html
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/NFS_README.html
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/XFORWARD_README.html
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/STANDARD_CONFIGURATION_README
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/TLS_README.html
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/IPV6_README
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/INSTALL
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/FILTER_README
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/SMTPD_POLICY_README.html
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/MULTI_INSTANCE_README.html
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/html2readme
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/TUNING_README.html
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/CDB_README.html
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/make_soho_readme
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/LINUX_README
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/MYSQL_README
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/MILTER_README.html
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/LDAP_README
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/ADDRESS_REWRITING_README
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/DEBUG_README.html
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/PGSQL_README.html
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/LOCAL_RECIPIENT_README
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/MAILDROP_README
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/DATABASE_README
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/SQLITE_README
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/TLS_LEGACY_README
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/STANDARD_CONFIGURATION_README.html
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/ADDRESS_REWRITING_README.html
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/ETRN_README
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/DB_README.html
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/ADDRESS_CLASS_README.html
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/TLS_README
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/MILTER_README
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/README.SPF
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/SASL_README
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/XFORWARD_README
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/UUCP_README
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/newaliases.1
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/makereadme
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/SMTPUTF8_README.html
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/PACKAGE_README
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/COMPATIBILITY_README.html
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/SQLITE_README.html
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/LDAP_README.html
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/IPv6-ChangeLog
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/AAAREADME
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/PCRE_README.html
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/SOHO_README
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/SMTPUTF8_README
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/IPV6_README.html
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/BACKSCATTER_README
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/FORWARD_SECRECY_README.html
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/FORWARD_SECRECY_README
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/XCLIENT_README
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/CONNECTION_CACHE_README
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/STRESS_README
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/DB_README
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/LOCAL_RECIPIENT_README.html
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/CONTENT_INSPECTION_README
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/VIRTUAL_README.html
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/CONNECTION_CACHE_README.html
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/SMTPD_PROXY_README.html
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/COMPATIBILITY_README
/bin/rm -f /var/opt/UNItools/docs/postfix.3.0.2/CYRUS_README
}

function test_noclobber()
{
	echo "testing that installation will not clobber existing files"
if [ -f /var/opt/UNItools/docs/postfix.3.0.2/QSHAPE_README ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/QSHAPE_README exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/XCLIENT_README.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/XCLIENT_README.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/LINUX_README.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/LINUX_README.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/ADDRESS_CLASS_README ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/ADDRESS_CLASS_README exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/BASIC_CONFIGURATION_README.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/BASIC_CONFIGURATION_README.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/POSTSCREEN_README ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/POSTSCREEN_README exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/TLS_LEGACY_README.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/TLS_LEGACY_README.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/SMTPD_POLICY_README ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/SMTPD_POLICY_README exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/CDB_README ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/CDB_README exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/VERP_README ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/VERP_README exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/NFS_README ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/NFS_README exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/PCRE_README ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/PCRE_README exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/MAILDROP_README.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/MAILDROP_README.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/STRESS_README.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/STRESS_README.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/RESTRICTION_CLASS_README ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/RESTRICTION_CLASS_README exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/OVERVIEW ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/OVERVIEW exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/BASIC_CONFIGURATION_README ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/BASIC_CONFIGURATION_README exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/MEMCACHE_README.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/MEMCACHE_README.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/MEMCACHE_README ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/MEMCACHE_README exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/ETRN_README.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/ETRN_README.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/SASL_README.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/SASL_README.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/SCHEDULER_README ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/SCHEDULER_README exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/CONTENT_INSPECTION_README.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/CONTENT_INSPECTION_README.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/VERP_README.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/VERP_README.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/LMDB_README ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/LMDB_README exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/ADDRESS_VERIFICATION_README.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/ADDRESS_VERIFICATION_README.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/DSN_README.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/DSN_README.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/BUILTIN_FILTER_README.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/BUILTIN_FILTER_README.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/DATABASE_README.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/DATABASE_README.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/BUILTIN_FILTER_README ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/BUILTIN_FILTER_README exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/LICENSE ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/LICENSE exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/DEBUG_README ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/DEBUG_README exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/PGSQL_README ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/PGSQL_README exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/TLS_LICENSE ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/TLS_LICENSE exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/PACKAGE_README.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/PACKAGE_README.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/ULTRIX_README ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/ULTRIX_README exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/ADDRESS_VERIFICATION_README ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/ADDRESS_VERIFICATION_README exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/MULTI_INSTANCE_README ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/MULTI_INSTANCE_README exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/POSTSCREEN_README.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/POSTSCREEN_README.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/README ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/README exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/QSHAPE_README.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/QSHAPE_README.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/SMTPD_ACCESS_README.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/SMTPD_ACCESS_README.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/VIRTUAL_README ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/VIRTUAL_README exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/SCHEDULER_README.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/SCHEDULER_README.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/newaliases.1.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/newaliases.1.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/MYSQL_README.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/MYSQL_README.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/QMQP_README ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/QMQP_README exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/SMTPD_ACCESS_README ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/SMTPD_ACCESS_README exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/readme2html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/readme2html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/UUCP_README.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/UUCP_README.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/LMDB_README.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/LMDB_README.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/DSN_README ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/DSN_README exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/SMTPD_PROXY_README ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/SMTPD_PROXY_README exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/RESTRICTION_CLASS_README.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/RESTRICTION_CLASS_README.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/FILTER_README.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/FILTER_README.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/BACKSCATTER_README.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/BACKSCATTER_README.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/TUNING_README ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/TUNING_README exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/SOHO_README.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/SOHO_README.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/NFS_README.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/NFS_README.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/XFORWARD_README.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/XFORWARD_README.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/STANDARD_CONFIGURATION_README ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/STANDARD_CONFIGURATION_README exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/TLS_README.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/TLS_README.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/IPV6_README ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/IPV6_README exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/INSTALL ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/INSTALL exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/FILTER_README ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/FILTER_README exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/SMTPD_POLICY_README.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/SMTPD_POLICY_README.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/MULTI_INSTANCE_README.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/MULTI_INSTANCE_README.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/html2readme ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/html2readme exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/TUNING_README.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/TUNING_README.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/CDB_README.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/CDB_README.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/make_soho_readme ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/make_soho_readme exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/LINUX_README ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/LINUX_README exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/MYSQL_README ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/MYSQL_README exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/MILTER_README.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/MILTER_README.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/LDAP_README ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/LDAP_README exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/ADDRESS_REWRITING_README ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/ADDRESS_REWRITING_README exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/DEBUG_README.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/DEBUG_README.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/PGSQL_README.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/PGSQL_README.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/LOCAL_RECIPIENT_README ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/LOCAL_RECIPIENT_README exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/MAILDROP_README ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/MAILDROP_README exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/DATABASE_README ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/DATABASE_README exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/SQLITE_README ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/SQLITE_README exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/TLS_LEGACY_README ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/TLS_LEGACY_README exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/STANDARD_CONFIGURATION_README.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/STANDARD_CONFIGURATION_README.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/ADDRESS_REWRITING_README.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/ADDRESS_REWRITING_README.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/ETRN_README ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/ETRN_README exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/DB_README.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/DB_README.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/ADDRESS_CLASS_README.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/ADDRESS_CLASS_README.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/TLS_README ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/TLS_README exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/MILTER_README ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/MILTER_README exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/README.SPF ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/README.SPF exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/SASL_README ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/SASL_README exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/XFORWARD_README ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/XFORWARD_README exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/UUCP_README ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/UUCP_README exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/newaliases.1 ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/newaliases.1 exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/makereadme ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/makereadme exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/SMTPUTF8_README.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/SMTPUTF8_README.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/PACKAGE_README ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/PACKAGE_README exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/COMPATIBILITY_README.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/COMPATIBILITY_README.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/SQLITE_README.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/SQLITE_README.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/LDAP_README.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/LDAP_README.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/IPv6-ChangeLog ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/IPv6-ChangeLog exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/AAAREADME ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/AAAREADME exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/PCRE_README.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/PCRE_README.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/SOHO_README ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/SOHO_README exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/SMTPUTF8_README ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/SMTPUTF8_README exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/IPV6_README.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/IPV6_README.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/BACKSCATTER_README ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/BACKSCATTER_README exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/FORWARD_SECRECY_README.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/FORWARD_SECRECY_README.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/FORWARD_SECRECY_README ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/FORWARD_SECRECY_README exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/XCLIENT_README ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/XCLIENT_README exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/CONNECTION_CACHE_README ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/CONNECTION_CACHE_README exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/STRESS_README ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/STRESS_README exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/DB_README ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/DB_README exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/LOCAL_RECIPIENT_README.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/LOCAL_RECIPIENT_README.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/CONTENT_INSPECTION_README ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/CONTENT_INSPECTION_README exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/VIRTUAL_README.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/VIRTUAL_README.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/CONNECTION_CACHE_README.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/CONNECTION_CACHE_README.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/SMTPD_PROXY_README.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/SMTPD_PROXY_README.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/COMPATIBILITY_README ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/COMPATIBILITY_README exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/postfix.3.0.2/CYRUS_README ]; then
	echo "ERROR: file /var/opt/UNItools/docs/postfix.3.0.2/CYRUS_README exists"
	ERROR=1
fi
}

function test_shared_libs()
{
	if [ -s /tmp/test_ldd_files ]; then
		echo "testing that all shared libs are available:"
	(
	
	) | sed '/=>/!d; s/.*=>//; s/(.*//' | while read SHAREDLIB
	do
		echo "$SHAREDLIB ... "
		if [ ! -e $SHAREDLIB ]; then
			echo "ERROR: shared lib $SHAREDLIB not found"
			ERROR=1
		else
			echo "ok"
		fi
	done
	else
		echo "no dynamically linked files found"
	fi
}

################################################################################
# Main
################################################################################

case $1 in
	cleanup)	rmfiles
				exit 0
	;;
	test)		:
	;;
	*)			echo "usage: /usr/local/bin/pkg_conbat cleanup | test"
				exit 0
esac

test_noclobber
case $ERROR in
	0)	echo "no clobber passed ok"
	;;
	*)	echo error: fix the errors first
		exit 1
	;;
esac

(
	echo "installing files ... "
	cd $TMPROOT
	find var -type f| /bin/cpio -pvdVn /
)

echo "testing shared libs ... "
test_shared_libs

echo "Now try executing some of the commands"
echo "Clean up by executing /usr/local/bin/pkg_conbat cleanup"

