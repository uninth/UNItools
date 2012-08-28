#!/bin/sh
#
# $Id$
# $Source: /export/home/bll/DI/features.base/RCS/cflags.sh,v $
# Copyright 2001-2002 Brad Lanam, Walnut Creek, California USA
#

bit64=""
while test $# -gt 0
do
    case $1 in
        -*)
            case $1 in
                -64)
                    bit64="1"
                    shift
                    ;;
            esac
            ;;
        *)
            break
            ;;
    esac
done

CC=${CC:-cc}
ccflags=""
ldflags=""
libs=""
includes=""
usinggcc="N"
path=$PATH

## need path separator...
tpath=`echo $PATH | sed 's/:/ /g'`
set ${tpath}
for i in $@
do
    if [ -x "$i/uname" ]
    then
        xuname="$i/uname"
    fi
    if [ -x "$i/getconf" ]
    then
        xgetconf="$i/getconf"
    fi
    # first located
    if [ -x "$i/msgfmt" -a "$xmsgfmt" = "" ]
    then
        xmsgfmt="$i/msgfmt"
    fi
    # first located
    if [ -x "$i/gmsgfmt" -a "$xgmsgfmt" = "" ]
    then
        xgmsgfmt="$i/gmsgfmt"
    fi
    if [ -x "$i/${CC}" ]
    then
        xccpath="$i"
    fi
done

case ${CC} in
    /*)
        xccpath=`echo ${CC} | sed 's,.*/,,'`
        ;;
esac

if [ "${xuname}" != "" ]
then
    SYSTYPE=`${xuname} -s`
    SYSREV=`${xuname} -r`
    SYSARCH=`${xuname} -m`
    case ${SYSTYPE} in
        AIX)
            tmp=`( (oslevel) 2>/dev/null || echo "not found") 2>&1`
            case "$tmp" in
                'not found') SYSREV="$4"."$3" ;;
                '<3240'|'<>3240') SYSREV=3.2.0 ;;
                '=3240'|'>3240'|'<3250'|'<>3250') SYSREV=3.2.4 ;;
                '=3250'|'>3250') SYSREV=3.2.5 ;;
                *) SYSREV=$tmp;;
            esac
            ;;
    esac
fi

if [ "$DI_IN_BUILD" != "1" ]
then
    ccflags="${CFLAGS:--O}"
    ldflags="${LDFLAGS:-}"
    libs="${LIBS:-}"
fi

libs="$libs -lm"

vers="`${CC} -v 2>&1`" # attempt to get version...

if [ "${xgetconf}" != "" ]
then
    tccflags="`${xgetconf} LFS_CFLAGS 2>/dev/null`"
    tldflags="`${xgetconf} LFS_LDFLAGS 2>/dev/null`"
    tlibs="`${xgetconf} LFS_LIBS 2>/dev/null`"
fi

# -Wtraditional
case ${CC} in
    *gcc*)
        usinggcc="Y"
        ccflags="-Wall -Waggregate-return -Wconversion -Wformat -Wmissing-prototypes -Wmissing-declarations -Wnested-externs -Wpointer-arith -Wshadow -Wstrict-prototypes -Wunused $ccflags"
        vers=""  # we know it's gcc...don't run again
        case "${bit64}" in
            1)
                ccflags="-m64 $ccflags"
                ;;
        esac
        ;;
esac

# -Wtraditional
case ${vers} in     # gcc in disguise...
    *gcc*)
        usinggcc="Y"
        ccflags="-Wall -Waggregate-return -Wconversion -Wformat -Wmissing-prototypes -Wmissing-declarations -Wnested-externs -Wpointer-arith -Wshadow -Wstrict-prototypes -Wunused $ccflags"
        case "${bit64}" in
            1)
                ccflags="-m64 $ccflags"
                ;;
        esac
        ;;
esac

case ${SYSTYPE} in
    AIX)
        usinggcc="N"
        ccflags="-qhalt=e $ccflags"
        ccflags="$ccflags -qmaxmem=-1"
        case ${SYSREV} in
            4.*)
                ccflags="-DUSE_ETC_FILESYSTEMS=1 $ccflags"
                ;;
        esac
        ;;
    BeOS)
        case ${SYSARCH} in
            BePC)
                #libpth="/boot/develop/lib/x86"
                #libc="/boot/develop/lib/x86/libroot.so"
                libs="-lroot -lbe $libs"
                ;;
            *)
                #libpth="/boot/develop/lib/ppc" #???
                #libc="/boot/develop/lib/ppc/libroot.so" #???
                libs="-lroot -lbe $libs"
                ;;
        esac
        ;;
    CYGWIN*)
        if [ $DI_BUILD_NO_NLS -eq 0 ]
        then
            libs="-lintl $libs"
        fi
        ;;
    FreeBSD)
        includes="-I/usr/local/include $includes"
        ldflags="-L/usr/local/lib $ldflags"
        if [ $DI_BUILD_NO_NLS -eq 0 ]
        then
            libs="-lintl -liconv $libs"
        fi
        ;;
    DYNIX)
        libs="-lseq $libs"
        ;;
    DYNIX/ptx)
        libs="-lseq $libs"
        ;;
    HP-UX)
        if [ "${tccflags}" = "" ]
        then
            ccflags="-D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64 $ccflags"
        fi
        case ${CC} in
            cc)
                case ${SYSREV} in
                    *.10.*)
                        ccflags="+DAportable $ccflags"
                        ;;
                esac
                ccflags="-Ae $ccflags"
                usinggcc="N"
                ;;
        esac
        if [ $DI_BUILD_NO_NLS -eq 0 -a \
            -d /usr/local/include -a \
            -d /usr/local/lib -a \
            -f /usr/local/lib/libintl.sl -a \
            -f /usr/local/lib/libiconv.sl ]
        then
            includes="-I/usr/local/include $includes"
            ldflags="-L/usr/local/lib $ldflags"
            libs="-lintl $libs"
            if [ $xmsgfmt != "/usr/local/bin/msgfmt" ]
            then
                path="/usr/local/bin:${path}"
            fi
        elif [ $DI_BUILD_NO_NLS -eq 0 -a \
            -d /opt/gnome/include -a \
            -d /opt/gnome/lib -a \
            -f /opt/gnome/lib/libintl.sl -a \
            -f /opt/gnome/lib/libiconv.sl ]
        then
            includes="-I/opt/gnome/include $includes"
            ldflags="-L/opt/gnome/lib $ldflags"
            libs="-lintl $libs"
            if [ $xmsgfmt != "/usr/local/bin/msgfmt" ]
            then
                path="/opt/gnome/bin:${path}"
            fi
        fi
        ;;
    IRIX*)
        case ${SYSREV} in
            [45].*)
                libs="-lsun"
                ;;
        esac
        ;;
    NetBSD)
        if [ $DI_BUILD_NO_NLS -eq 0 ]
        then
            libs="-lintl $libs"
        fi
        ;;
    OSF1)
        ccflags="-std1 $ccflags"
        ;;
    SunOS)
        case ${SYSREV} in
            5.*)
                case ${CC} in
                    cc)
                        # If solaris is compile w/strict ansi, we get
                        # a work-around for the long long type with
                        # large files.  So we compile w/extensions.
                        ccflags="-Xa -v $ccflags"
                        # optimization
                        ccflags="`echo $ccflags | sed 's,-xO. *,-xO4 ,'`"
                        ccflags="`echo $ccflags | sed 's,-O *,-xO4 ,'`"
                        echo $ccflags | grep -- '-xO4' >/dev/null 2>&1
                        case $rc in
                            0)
                                ldflags="-fast $ldflags"
                                ;;
                        esac

                        case "${bit64}" in
                            1)
                                ;;
                        esac
                        ;;
                    *gcc*)
                        ;;
                esac
                ;;
        esac
        ;;
esac

# largefile stuff
ccflags="$ccflags $tccflags"
ldflags="$ldflags $tldflags"
libs="$libs $tlibs"

mfmt="${xmsgfmt}"
if [ "$usinggcc" = "Y" ]
then
    mfmt="${xgmsgfmt:-${xmsgfmt}}"
    if [ -f "${xccpath}/msgfmt" ]
    then
        mfmt="${xccpath}/msgfmt"
    fi
    if [ -f "${xccpath}/gmsgfmt" ]
    then
        mfmt="${xccpath}/gmsgfmt"
    fi
fi

echo "CC=\"${CC}\""
echo "CFLAGS=\"$ccflags $includes\""
echo "CINCLUDES=\"$includes\""
echo "LDFLAGS=\"$ldflags\""
echo "LIBS=\"$libs\""
echo "PATH=\"$path\""
echo "XMSGFMT=\"$mfmt\""
echo "export CC"
echo "export CFLAGS"
echo "export CINCLUDES"
echo "export LDFLAGS"
echo "export LIBS"
echo "export PATH"
echo "export XMSGFMT"
exit 0
