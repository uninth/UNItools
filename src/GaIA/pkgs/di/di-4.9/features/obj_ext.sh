#!/bin/sh
#
# $Id$
# $Source: /home/bll/DI/features.base/RCS/obj_ext.sh,v $
# Copyright 2001-2002 Brad Lanam, Walnut Creek, California, USA
#

if [ ! -f "object_ext" ]
then
    cat > x$$.c << HERE
#include <stdio.h>
main ()
{
    printf ("hello\n");
    return 0;
}
HERE

    ${CC} ${CFLAGS} -c x$$.c > /dev/null 2>&1 # don't care about warnings...
    OBJ_EXT=".o"
    if [ -f "x$$.obj" ]
    then
         OBJ_EXT=".obj"
    fi
    rm -f x$$.o x$$.obj a.out > /dev/null 2>&1

    ${CC} ${CFLAGS} -o x$$ x$$.c > /dev/null 2>&1 # don't care about warnings...
    EXE_EXT=""
    if [ -f "x$$.exe" ]
    then
         EXE_EXT=".exe"
    fi
    rm -f x$$.c x$$.o x$$.obj x$$ x$$.exe a.out > /dev/null 2>&1
fi
if [ -f "object_ext" ]
then
    eval `cat object_ext`
fi

echo "OBJ_EXT=${OBJ_EXT}" > object_ext
echo "EXE_EXT=${EXE_EXT}" >> object_ext
echo "OBJ_EXT=${OBJ_EXT}"
echo "EXE_EXT=${EXE_EXT}"
echo "export OBJ_EXT"
echo "export EXE_EXT"

exit 0
