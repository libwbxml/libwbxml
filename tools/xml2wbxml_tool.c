/*
 * libwbxml, the WBXML Library.
 * Copyright (C) 2002-2008 Aymerick Jehanne <aymerick@jehanne.org>
 * Copyright (C) 2011 Michael Bell <michael.bell@opensync.org>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 * 
 * LGPL v2.1: http://www.gnu.org/copyleft/lesser.txt
 * 
 *
 * Contact: aymerick@jehanne.org
 * Home: http://libwbxml.aymerick.com
 */

/**
 * @file xml2wbxml_tool.c
 * @ingroup xml2wbxml_tool
 *
 * @author Aymerick Jehanne <aymerick@jehanne.org>
 * @date 03/03/11
 *
 * @brief XML to WBXML Converter Tool
 *
 */

#if !defined ( __SYMBIAN32__ )
#include <memory.h>
#endif /* ! __SYMBIAN32__ */

/* The real libwbxml include is:
 *
 * #include <wbxml/wbxml.h>
 *
 * We must use a direct reference to enforce the correct include.
 */
#include "../src/wbxml.h"

#ifdef WBXML_USE_LEAKTRACKER
#include "src/wbxml_mem.h"
#endif

#include "getopt.h"

/*
 * This sytem include is here instead of the *.c files because
 * we want it to be included AFTER 'e32def.h' (in 'wbxml.h') on Symbian.
 * If not so, Warnings are displayed ('NULL' : macro redefinition)
 */
#include <stdio.h>


#define INPUT_BUFFER_SIZE 1000


static WBXMLVersion get_version(const WB_TINY *lang)
{
    if (WBXML_STRCMP(lang, "1.0") == 0)
        return WBXML_VERSION_10;
    if (WBXML_STRCMP(lang, "1.1") == 0)
        return WBXML_VERSION_11;
    if (WBXML_STRCMP(lang, "1.2") == 0)
        return WBXML_VERSION_12;
    if (WBXML_STRCMP(lang, "1.3") == 0)
        return WBXML_VERSION_13;

    return WBXML_VERSION_UNKNOWN;
}


static void help(void) {
    fprintf(stderr, "xml2wbxml [libwbxml %s] by OpenSync\n", WBXML_LIB_VERSION);
    fprintf(stderr, "This library was originally written by Aymerick Jehanne <aymerick@jehanne.org>\n");
    fprintf(stderr, "If you use this tool, please send feedbacks to opensync-users@opensync.org\n");
    fprintf(stderr, "http://libwbxml.opensync.org/\n");
#if defined( HAVE_EXPAT )
    fprintf(stderr, "This tool is linked with Expat (http://expat.sourceforge.net)\n\n");
#endif /* HAVE_EXPAT */
    fprintf(stderr, "Usage: \n");
    fprintf(stderr, "  xml2wbxml -o output.wbxml input.xml\n");
    fprintf(stderr, "  xml2wbxml -k -n -v 1.1 -o output.wbxml input.xml\n\n");
    fprintf(stderr, "Options: \n");
    fprintf(stderr, "    -o output.wbxml : output file\n");
    fprintf(stderr, "    -k : keep ignorable whitespaces (Default: ignore)\n");
    fprintf(stderr, "    -n : do NOT generate String Table (Default: generate)\n");
    fprintf(stderr, "    -v X (WBXML Version of output document)\n");
    fprintf(stderr, "       1.0 : WBXML 1.0\n");
    fprintf(stderr, "       1.1 : WBXML 1.1\n");
    fprintf(stderr, "       1.2 : WBXML 1.2\n");
    fprintf(stderr, "       1.3 : WBXML 1.3\n");
    fprintf(stderr, "    -a : anonymous format\n");
    fprintf(stderr, "         do NOT include any format information (e.g. public ID or DTD)\n");
    fprintf(stderr, "\nNote: '-' can be used to mean stdin on input or stdout on output\n\n");
}


WB_LONG main(WB_LONG argc, WB_TINY **argv)
{
    WB_UTINY *wbxml = NULL, *output = NULL, *xml = NULL;
    FILE *input_file = NULL, *output_file = NULL;
    WB_ULONG wbxml_len = 0;
    WB_LONG count = 0, xml_len = 0, total = 0;
    WB_TINY opt;
    WBXMLError ret = WBXML_OK;
    WB_UTINY input_buffer[INPUT_BUFFER_SIZE + 1];
    WBXMLConvXML2WBXML *conv = NULL;

    ret = wbxml_conv_xml2wbxml_create(&conv);
    if (ret != WBXML_OK)
    {
        fprintf(stderr, "xml2wbxml failed: %s\n", wbxml_errors_string(ret));
        goto clean_up;
    }


    while ((opt = (WB_TINY) wbxml_getopt(argc, argv, "nkah?o:v:")) != EOF)
    {
        switch (opt) {
        case 'v':
            wbxml_conv_xml2wbxml_set_version(conv, get_version((const WB_TINY*)optarg));
            break;
        case 'n':
            wbxml_conv_xml2wbxml_disable_string_table(conv);
            break;
        case 'k':
            wbxml_conv_xml2wbxml_enable_preserve_whitespaces(conv);
            break;
        case 'a':
            wbxml_conv_xml2wbxml_disable_public_id(conv);
            break;
        case 'o':
            output = (WB_UTINY*) optarg;
            break;
        case 'h':
        case '?':
        default:
            help();
            return 0;
        }
    }

    if (optind >= argc) {
        fprintf(stderr, "Missing arguments\n");
        help();
        return 0;
    }

#ifdef WBXML_USE_LEAKTRACKER
    lt_init_mem();
    lt_log_open_file("xml2wbxml.log");
    lt_log(0, "\n***************************\n Converting file: %s", argv[optind]);
#endif

    /**********************************
     *  Read the XML Document
     */

    if (WBXML_STRCMP(argv[optind], "-") == 0) {
        input_file = stdin;
    } else {
        /* Open XML document */
        input_file = fopen(argv[optind], "r");
        if (input_file == NULL) {
            printf("Failed to open %s\n", argv[optind]);
            goto clean_up;
        }
    }

    /* Read XML document */
    while(!feof(input_file))    {
        count = fread(input_buffer, sizeof(WB_UTINY), INPUT_BUFFER_SIZE, input_file);
        if (ferror(input_file))      {
            fprintf(stderr, "Error while reading from file %s\n", argv[1]);
            if (input_file != stdin)
                fclose(input_file);
            if (xml != NULL)
#ifdef WBXML_USE_LEAKTRACKER
                wbxml_free(xml);
#else
                free(xml);
#endif
            goto clean_up;
        }

        total += count;
#ifdef WBXML_USE_LEAKTRACKER
        xml = wbxml_realloc(xml, total + 1);
#else
        xml = realloc(xml, total + 1);
#endif
        if (xml == NULL) {
            fprintf(stderr, "Not enought memory\n");
            if (input_file != stdin)
                fclose(input_file);
            goto clean_up;
        }

        memcpy(xml + xml_len, input_buffer, count);
        xml_len += count;
    }

    if (input_file != stdin)
        fclose(input_file);

    xml[xml_len] = '\0';

    /* Convert XML document */
    ret = wbxml_conv_xml2wbxml_run(conv, xml, xml_len, &wbxml, &wbxml_len);
    if (ret != WBXML_OK) {
        fprintf(stderr, "xml2wbxml failed: %s\n", wbxml_errors_string(ret));
    }
    else {
        fprintf(stderr, "xml2wbxml succeded\n");

        if (output != NULL) {
            if (WBXML_STRCMP(output, "-") == 0) {
                output_file = stdout;
            }
            else {
                /* Open Output File */
                output_file = fopen((const WB_TINY*) output, "wb");
            }

            if (output_file == NULL) {
                fprintf(stderr, "Failed to open output file: %s\n", output);
            }
            else {
                /* Write to Output File */
                if (fwrite(wbxml, sizeof(WB_UTINY), wbxml_len, output_file) < wbxml_len)
                    fprintf(stderr, "Error while writing to file: %s\n", output);
                /*
                else
                    fprintf(stderr, "Written %u bytes to file: %s\n", wbxml_len, output);
                */

                if (output_file != stdout)
                    fclose(output_file);
            }
        }

        /* Clean-up */
        if (wbxml != NULL)
#ifdef WBXML_USE_LEAKTRACKER
            wbxml_free(wbxml);
#else
            free(wbxml);
#endif
    }

    if (xml != NULL)
#ifdef WBXML_USE_LEAKTRACKER
        wbxml_free(xml);
#else
       free(xml);
#endif

clean_up:

    if (conv != NULL)
        wbxml_conv_xml2wbxml_destroy(conv);

#ifdef WBXML_USE_LEAKTRACKER
    lt_check_leaks();
    lt_shutdown_mem();
    lt_log_close_file();
#endif

    return ret;
}
