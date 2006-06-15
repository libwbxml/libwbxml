##  Process this file with automake to produce Makefile.in

INCLUDES =\
	 -I. -I../src -I/usr/include

CFLAGS =\
	 -DHAVE_CONFIG_H\
	 -DHAVE_EXPAT\
	 -D_REENTRANT\
	 -DWBXML_ENCODER_USE_STRTBL\
	 -DWBXML_SUPPORT_WML\
	 -DWBXML_SUPPORT_WTA\
	 -DWBXML_SUPPORT_SI\
	 -DWBXML_SUPPORT_SL\
	 -DWBXML_SUPPORT_CO\
	 -DWBXML_SUPPORT_PROV\
	 -DWBXML_SUPPORT_EMN\
	 -DWBXML_SUPPORT_DRMREL\
	 -DWBXML_SUPPORT_OTA_SETTINGS\
	 -DWBXML_SUPPORT_SYNCML\
	 -DWBXML_SUPPORT_WV\
	 -Wall -Wimplicit -Wreturn-type -Wunused -Wswitch -Wcomment -Wuninitialized -Wparentheses -Wpointer-arith -Wmissing-prototypes\
	 -O3\
	 -g

bin_PROGRAMS = wbxml2xml xml2wbxml

wbxml2xml_SOURCES = \
	wbxml2xml_tool.c\
	attgetopt.c

xml2wbxml_SOURCES = \
	xml2wbxml_tool.c\
	attgetopt.c

noinst_HEADERS = \
	getopt.h

wbxml2xml_LDADD = \
	../src/libwbxml2.la

xml2wbxml_LDFLAGS = \
	-lexpat

xml2wbxml_LDADD = \
	../src/libwbxml2.la
