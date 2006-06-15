## Process this file with automake to produce Makefile.in

INCLUDES =\
	 -I. -I/usr/include

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

lib_LTLIBRARIES = libwbxml2.la

libwbxml2_la_SOURCES = \
	wbxml_base64.c\
	wbxml_buffers.c\
	wbxml_charset.c\
	wbxml_conv.c\
	wbxml_elt.c\
	wbxml_encoder.c\
	wbxml_errors.c\
	wbxml_lists.c\
	wbxml_log.c\
	wbxml_mem.c\
	wbxml_parser.c\
	wbxml_tables.c\
	wbxml_tree.c\
	wbxml_tree_clb_wbxml.c\
	wbxml_tree_clb_xml.c

include_HEADERS = \
	wbxml.h\
	wbxml_base64.h\
	wbxml_buffers.h\
	wbxml_charset.h\
	wbxml_conv.h\
	wbxml_elt.h\
	wbxml_encoder.h\
	wbxml_errors.h\
	wbxml_handlers.h\
	wbxml_lists.h\
	wbxml_log.h\
	wbxml_mem.h\
	wbxml_parser.h\
	wbxml_tables.h\
	wbxml_tree.h\
	wbxml_tree_clb_wbxml.h\
	wbxml_tree_clb_xml.h

libwbxml2_la_LDFLAGS = -no-undefined -version-info 0:9:0
