#!/bin/sh

# Copyright (C) 2009 Michael Bell <michael.bell@opensync.org>

# setup correct path for binaries if they are not in $PATH
if [ "${CMAKE_CURRENT_BINARY_DIR}" ]
then
	WBXML2XML="${CMAKE_CURRENT_BINARY_DIR}/tools/wbxml2xml"
	XML2WBXML="${CMAKE_CURRENT_BINARY_DIR}/tools/xml2wbxml"
else
	WBXML2XML=`which wbxml2xml`
	XML2WBXML=`which xml2wbxml`
fi

if [ " ${PERL_PROGRAM}" != " " ]
then
	PERL_BIN="${PERL_PROGRAM}"
else
	PERL_BIN=`which perl`
fi

NORMALIZE_SCRIPT="${CMAKE_CURRENT_BINARY_DIR}/normalize_xml.pl"

if [ " ${DIFF_PROGRAM}" != " " ]
then
	DIFF_BIN="${DIFF_PROGRAM}"
else
	DIFF_BIN=`which diff`
fi

if [ ! -x "$WBXML2XML" ]
then
    echo Set WBXML2XML to the binary executable of wbxml2xml tool in order to use that script.
    exit 1
fi

if [ ! -x "$XML2WBXML" ]
then
    echo Set XML2XWBML to the binary executable of xml2wbxml tool in order to use that script.
    exit 1
fi

# if somebody enabled CMAKE_SKIP_RPATH
# then it is necessary to specify the path to the library
# Debian does this by default
if [ "${CMAKE_SKIP_RPATH}" ]
then
	LD_LIBRARY_PATH="${CMAKE_CURRENT_BINARY_DIR}/src"
	export LD_LIBRARY_PATH
fi

# Go to test suite directory
if [ " $1" != " " -a -d "$1" ]
then
	TEST_SUITE_DIR="$1"
else
	TEST_SUITE_DIR=`dirname $0`
fi

cd "$TEST_SUITE_DIR" || exit 1
PWD=`pwd`

echo Test suite directory is $PWD

# Create temporary directory
TMP_DIR=`mktemp -d -t LibWBXMLTestSuite.XXX`

# execute only a special test directory
if [ " $2" != " " ]
then
	DIRLIST=`find $PWD/. \( -type d -a -name $2 -a ! -name . -prune \) -print | sort`
	if [ ! "$DIRLIST" ]
	then
		DIRLIST=`find $PWD/. \( -type d -a ! -name "*svn*" -a ! -name . -prune \) -print | sort`
		COUNTER=0
		for ITEM in $DIRLIST
		do
			if [ "$COUNTER" -eq "$2" ]
			then
				RESULT=$ITEM
			fi
			COUNTER=`expr $COUNTER + 1`
		done
		DIRLIST=$RESULT
	fi
else
	DIRLIST=`find $PWD/. \( -type d -a ! -name "*svn*" -a ! -name . -prune \) -print | sort`
fi

# For each directory
RESULT="SUCCEEDED"
for i in $DIRLIST
do
  if [ $i != `pwd` ]; then

  echo ----------------------------
  echo Entering into: `basename $i`
  echo ----------------------------

  # execute only a special test in a directory
  if [ `basename $i` != 'ddf' ]; then
  	TESTLIST=`find $i/. \( -type f -name "*.xml" -a ! -name . -prune \) -print | sort`
  else
  	TESTLIST=`find $i/. \( -type f \( -name "*.ddf" -or -name "*.xml" \) -a ! -name . -prune \) -print | sort`
  fi
  if [ " $3" != " " ]
  then
	COUNTER=0
	for ITEM in $TESTLIST
	do
		COUNTER=`expr $COUNTER + 1`
		if [ "$COUNTER" -eq "$3" ]
		then
			TESTCASE=$ITEM
		fi
	done
	TESTLIST=$TESTCASE
  fi

  # For each directory
  for j in $TESTLIST
  do
    echo . `basename $j`

    OUT_WBXML="$TMP_DIR/`basename $i`/`basename $j .xml`.wbxml"
    OUT_XML="$TMP_DIR/`basename $i`/`basename $j`"
    
    # Create output directory if they don't exist
    if [ ! -d "$TMP_DIR/`basename $i`" ]; then
        mkdir -p "$TMP_DIR/`basename $i`"
    fi

    # XML ==> WBXML
    echo Converting into: $OUT_WBXML
    if [ "$TESTDIR" != "ota" -a "$TESTDIR" != "airsync" ]; then
	# disable string tables if they are not really necessary
	NO_STR_TBL="-n";
    fi
    CMD="$XML2WBXML $NO_STR_TBL -o $OUT_WBXML $j"
    $CMD
    if [ $? != 0 ]; then RESULT="FAILED"; fi

    # WBXML ==> XML
    echo Converting back: $OUT_XML
    TESTDIR=`basename $i`
    if [ "$TESTDIR" = "ota" ];
    then
        PARAMS="-l OTA"
    else if [ "$TESTDIR" = "airsync" ];
    then
        PARAMS="-l AIRSYNC"
    else if [ "$TESTDIR" = "ddf" -a `basename $j` != `basename $j ddf` ];
    then
	# only pure DDF documents need this option
	# embedded DDF documents do not need this option
        PARAMS="-l DMDDF12"
    else
        PARAMS=""
    fi fi fi
    CMD="$WBXML2XML $PARAMS -o $OUT_XML $OUT_WBXML"
    $CMD
    if [ $? != 0 ]; then RESULT="FAILED"; fi

    # compare original and generated XML
    echo -n "Comparing the original and the generated XML ... "
    if [ " $PERL_BIN" = " " -o " $DIFF_BIN" = " " ]
    then
	echo UNSUPPORTED
    else if [ `basename $j` = "syncml-012.xml" -o  `basename $j` = "syncml-013.xml" -o `basename $j` = "activesync-032-formatted-base64.xml" ]
    then
	# SyncML CDATA fix makes comparing sometimes impossible
	echo CDATA_ENCAPSULATION
    else
	$PERL_BIN $NORMALIZE_SCRIPT --delete-attribute xmlns $j $OUT_XML.org
	$PERL_BIN $NORMALIZE_SCRIPT --delete-attribute xmlns $OUT_XML $OUT_XML.new
	DIFF_RESULT=`$DIFF_BIN -b $OUT_XML.org $OUT_XML.new`
	if [ " $DIFF_RESULT" != " " ];
	then
		echo FAILED
		RESULT="FAILED";
	else
		echo SUCCEEDED
	fi
    fi fi
  done

 fi
done

# Cleanup
if [ "$RESULT" == "SUCCEEDED" ];
then
    rm -rf "$TMP_DIR";
fi

echo ---------------------------
echo \\o/ Finished ! Yeah ! \\o/
echo ---------------------------

echo $RESULT
if [ "$RESULT" != "SUCCEEDED" ];
then
    exit 1;
else
    exit 0;
fi
