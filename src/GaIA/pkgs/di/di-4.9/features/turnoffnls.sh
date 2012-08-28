#!/bin/sh
#
# $Id$
#

ed config.h << HERE > /dev/null
g/^#define[     ]*_lib_bindtextdomain/ s/1//
g/^#define[     ]*_lib_bindtextdomain/ s/^#define/#undef/
g/^#define[     ]*_lib_gettext/ s/1//
g/^#define[     ]*_lib_gettext/ s/^#define/#undef/
g/^#define[     ]*_lib_setlocale/ s/1//
g/^#define[     ]*_lib_setlocale/ s/^#define/#undef/
g/^#define[     ]*_lib_textdomain/ s/1//
g/^#define[     ]*_lib_textdomain/ s/^#define/#undef/
g/^#define[     ]*_hdr_libintl/ s/1//
g/^#define[     ]*_hdr_libintl/ s/^#define/#undef/
g/^#define[     ]*_hdr_locale/ s/1//
g/^#define[     ]*_hdr_locale/ s/^#define/#undef/
g/^#define[     ]*_command_msgfmt/ s/1//
g/^#define[     ]*_command_msgfmt/ s/^#define/#undef/
g/^#define[     ]*_command_gmsgfmt/ s/1//
g/^#define[     ]*_command_gmsgfmt/ s/^#define/#undef/
w
q
HERE

exit 0
