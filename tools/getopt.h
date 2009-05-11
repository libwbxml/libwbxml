/**
 * @file getopt.h
 * @ingroup wbxml2xml_tool
 * @ingroup xml2wbxml_tool
 *
 * @brief wbxml_getopt() is just another copy of the getopt implementation of AT&T
 */

#ifndef WBXML_GETOPT_H
#define WBXML_GETOPT_H

#include "tools/config.h"

#ifdef FOUND_POSIX_GETOPT

#include <unistd.h>
#define wbxml_getopt getopt

#else /* FOUND_POSIX_GETOPT */

int wbxml_getopt(int argc, char **argv, char *opts);
extern int optind;
/* useless variable
extern int optopt;
*/
extern char *optarg;

#endif /* FOUND_POSIX_GETOPT */

#endif
