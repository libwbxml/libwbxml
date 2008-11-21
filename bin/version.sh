#!/bin/sh
#
# USAGE: version.sh path/to/wbxml.h
#
# This script will print libwbxml version number on stdout. For example:
#
#   $ ./version.sh ../src/wbxml.h
#   0.9.3
#   $
#

if test $# = 0; then
  echo "ERROR: pathname for wbxml.h was not provided."
  echo ""
  echo "USAGE: $0 path/to/wbxml.h"
  exit 1
fi

if test $# != 1; then
  echo "ERROR: too many arguments were provided."
  echo ""
  echo "USAGE: $0 path/to/wbxml.h"
  exit 1
fi

hdr="$1"
if test ! -r "$hdr"; then
  echo "ERROR: '$hdr' does not exist, or is not readable."
  exit 1
fi

WBXML_VERSION="`sed -n -e '/WBXML_LIB_VERSION/s/[^0-9.]*//gp' $hdr`"

# Determine how to tell echo not to print the trailing \n. This is
# similar to Autoconf's @ECHO_C@ and @ECHO_N@;
case `echo "testing\c"; echo 1,2,3`,`echo -n testing; echo 1,2,3` in
  *c*,-n*) ECHO_N= ECHO_C='
' ;;
  *c*,*  ) ECHO_N=-n ECHO_C= ;;
  *)      ECHO_N= ECHO_C='\c' ;;
esac

echo $ECHO_N "$WBXML_VERSION$ECHO_C"
