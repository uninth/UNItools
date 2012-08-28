#!/bin/sh

lib_path=perl/lib/5.8.7/i686-linux-thread-multi/CORE

env -i \
   PATH=/usr/bin:/bin \
   HOME=$HOME \
   LD_LIBRARY_PATH=$lib_path \
   DYLD_LIBRARY_PATH=$lib_path \
  ./perl/bin/perl -Isupport/lib support/install.pl "$@"
