#
# Standardværdier for shell scripts der sender post 
#
# $Header: /lan/ssi/shared/software/internal/UNItools/src/GaIA/pkgs/conf_template/conf_template.1.0/RCS/smtpclient.SH,v 1.5 2014/03/19 12:02:43 root Exp $
#

DNSDOMAIN=`domainname`

case $DNSDOMAIN in
        ""|\(none\))
                DNSDOMAIN=""	# fqdn kan være identisk med `hostname`
        ;;
        *)      DNSDOMAIN=".${DNSDOMAIN}"
esac


# Der er ingen garanti for, at navnet findes i en ekstern DNS.
FQDN="`hostname`${DNSDOMAIN}"

# Modtager:
DEF_RCPT="fwsupport@i2.dk"

# Afsender (kan ikke modtage post!):
DEF_FROM="no-reply@${FQDN}"

# Svar til denne adresse:
DEF_RETO="fwsupport@i2.dk"

# Fejl ved smtp sendes til:
DEF_ERTO="fwsupport@i2.dk"

# Brug denne smtp server:
DEF_SMTP="spamfilter1.dtu.dk"

# Hvis navneservice fejler, anvend denne IP. Den vil sikkert skifte, men det er det sidste skud vi har
DEF_SMTP_IPADDR="130.225.73.112"

host -q -s 1 ${DEF_SMTP} > /dev/null 2>&1
case $? in
	0)	: # navneservice virker
	;;
	*)	DEF_SMTP=${DEF_SMTP_IPADDR}
		# navneservice virker ikke, brug en IP addresse og håb på det bedste
	;;
esac

OPTIONS="-f ${DEF_FROM} -r ${DEF_RETO} -e ${DEF_ERTO} -S ${DEF_SMTP} ${DEF_RCPT}"
SMTPCLIENT="/var/opt/UNItools/bin/smtpclient"
