#! /bin/env bash
#
# This is a hack to compile customer/internal documentation as pdf - it's
# easyer to mail one pdf document than a set of files.
#
# So, unite all pdf files from /var/opt/UNItools
# together with a table of contents describing tool name, version and vendor
# and put a splashing cover on and call it 'documentation'
#

function make_toc_file()
{
	# Create a table with all all software, version, vendor and URL
	# in
	#	- pdf using tbl and groff for combined documentation
	#	- html/markdown for github/online viewing
	#	- dokuwiki for internal use (abandoned and removed)

	# star here
	SAVE_DIR=`pwd`

	cd ..

	cat << EOF > ${TBL_TXT_FILE}

.PAPER A 4


.TS H box;
c s s
c | c | c 
l | l | l | l.
.TH UNItools 1 "Table of Contents"
UNItools Table of Contents
=
Package	Version		Description
EOF

	find . -maxdepth 2 -type f  -name CFG|while read CFG; do
		. $CFG
		VENDOR=`echo $VENDOR | fmt -w 16`
		URL=`echo $URL | fmt -w 20`
		cat << EOF  >> ${TBL_TXT_FILE}
_
		Name	$NAME
$PKG	$VER	Vendor	T{
$VENDOR
T}
		URL	T{
$URL
T}
EOF
	done

	cat << EOF >> ${TBL_TXT_FILE}
.TE

The next pages describes the manual pages for the installed versions of the software components.

EOF

tbl ${TBL_TXT_FILE} | groff -man -Tps | ps2pdf13 - ${TBL_PDF_FILE}
# tbl ${TBL_TXT_FILE} | groff -man -Tascii

#printf "^ %-18s ^ %10s ^ %-45s ^%-45s^\n" "Package" "Version" "Name" "URL"
#find . -maxdepth 2 -type f -name CFG|while read CFG; do
#	. $CFG
#printf "| %-18s | %10s | %-45s | %-45s |\n" "$PKG" "$VER" "$NAME" "$URL" >> /tmp/tmpfile
#done

	cd $SAVE_DIR
}

#
# Main
#
MYNAME="/lan/ssi/shared/software/internal/pkg_tools/bin/pkg_mk_wikitoc.sh"

PREFIX=/lan/ssi/shared/software/internal/UNItools

SRC=$PREFIX/src/GAiA

TARGET=/var/opt/UNItools/docs/UNItools.pdf
COVER=UNItools-coverpage.pdf

TBL_TXT_FILE="/tmp/unitools_list_of_apps.txt"
TBL_PDF_FILE="/tmp/unitools_list_of_apps.pdf"
ALLPDF=`find /var/opt/UNItools/ -name '*.pdf' -type f`

make_toc_file

pdfunite ${COVER} ${TBL_PDF_FILE} ${ALLPDF} ${TARGET} 

ls -l ${TARGET}

exit 0

