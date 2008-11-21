/*
 * libwbxml, the WBXML Library.
 * Copyright (C) 2002-2008 Aymerick Jehanne <aymerick@jehanne.org>
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
 * Contact: aymerick@jehanne.org
 * Home: http://libwbxml.aymerick.com
 */
 
/**
 * @file test_parser.c
 * @ingroup test
 *
 * @author Aymerick Jehanne <aymerick@jehanne.org>
 * @date 03/03/21
 *
 * @brief Test the WBXML Parser
 */

#include <string.h>
#include <wbxml.h>

#define INPUT_BUFFER_SIZE 1000


/** Start Document Callback */
void parse_clb_start_document(void *ctx, WBXMLCharsetMIBEnum charset, const WBXMLLangEntry *lang)
{
    printf("Parsing Document:\n"
           "\tRoot Element: %s\n"
           "\tPublic ID: %s\n"
           "\tDTD: %s\n",
           lang->publicID->xmlRootElt,
           lang->publicID->xmlPublicID,
           lang->publicID->xmlDTD);
}

/** End Document Callback */
void parse_clb_end_document(void *ctx)
{
    printf("End of Document\n");
}

/** Start Element Callback */
void parse_clb_start_element(void *ctx, WBXMLTag *element, WBXMLAttribute **atts, WB_BOOL empty)
{    
    WB_ULONG *indent = (WB_ULONG *) ctx;
    
    WB_ULONG i = 0, j = 0;
    
    /* Indent start Element */
    for (i=0; i<*indent; i++)
        printf(" ");

    /* Write start Element */
    printf("<%s", wbxml_tag_get_xml_name(element));
    
    /* Write Attributes */
    if (atts != NULL) {
        while (atts[j] != NULL)
        {
            /* Write Attribute Name */
            printf(" %s=\"%s\"", wbxml_attribute_get_xml_name(atts[j]), wbxml_attribute_get_xml_value(atts[j]));  
            j++;
        }        
    }
    
    /* End of start Element */
    if (empty) {
        printf("/>\n");
    }
    else {
        printf(">\n");
        (*indent)++;
    }
}

/** End Element Callback */
void parse_clb_end_element(void *ctx, WBXMLTag *element, WB_BOOL empty)
{
    WB_ULONG *indent = (WB_ULONG *) ctx;
    WB_ULONG i = 0;

    if (!empty) {
        (*indent)--;

        /* Indent End Element */
        for (i=0; i<*indent; i++)
            printf(" ");
            
        /* Write end tag */
        printf("</%s>\n", wbxml_tag_get_xml_name(element));        
    }
}

/** Characters Callback */
void parse_clb_characters(void *ctx, WB_UTINY *ch, WB_ULONG start, WB_ULONG length)
{
    WB_ULONG *indent = (WB_ULONG *) ctx;
    WB_ULONG i = 0;
    
    /* Indent Characters */
    for (i=0; i<*indent; i++)
        printf(" ");

    /* Write Content */
    for(i=start; i<length; i++)
        printf("%c", ch[i]);

    printf("\n");
}

/** Main Function */
WB_LONG main(WB_LONG argc, WB_TINY **argv) 
{
    FILE *input_file = NULL;
    WB_ULONG count = 0, total = 0, wbxml_len = 0;
    WB_UTINY input_buffer[INPUT_BUFFER_SIZE + 1];

    WBXMLParser *wbxml_parser = NULL;
    WB_UTINY *wbxml = NULL;
    WB_ULONG indent = 0, error_index = 0;
    WBXMLError ret = WBXML_OK;
    WBXMLContentHandler parse_handler = 
        {
            parse_clb_start_document,
            parse_clb_end_document,
            parse_clb_start_element,
            parse_clb_end_element,
            parse_clb_characters,
            NULL
        };
        
    if (argc != 2) {
        printf("Missing argument: WBXML Filename");
        return 0;
    }

    /**********************************
     *  Read the WBXML Document
     */

    /* Open WBXML document */
    if ((input_file = fopen(argv[1], "rb")) == NULL) {
        printf("Failed to open %s\n", argv[1]);
        return 0;
    }

    /* Read WBXML document */
    while(!feof(input_file))    {
        count = fread(input_buffer, sizeof(WB_UTINY), INPUT_BUFFER_SIZE, input_file);
        if (ferror(input_file))      {
            printf("Error while reading from file %s\n", argv[1]);
            fclose(input_file);
            if (wbxml != NULL)
                wbxml_free(wbxml);
            return 0;
        }

        total += count;
        if ((wbxml = wbxml_realloc(wbxml, total)) == NULL) {
            printf("Not enought memory\n");
            fclose(input_file);
            if (wbxml != NULL)
                wbxml_free(wbxml);
            return 0;
        }

        memcpy(wbxml + wbxml_len, input_buffer, count);
        wbxml_len += count;
    }

    fclose(input_file);
    
    /* Create WBXML Parser */
    if ((wbxml_parser = wbxml_parser_create()) == NULL) {
        wbxml_free(wbxml);
        return 0;
    }
    
    /* Initialize WBXML Parser */
    wbxml_parser_set_user_data(wbxml_parser, &indent);
    wbxml_parser_set_content_handler(wbxml_parser, &parse_handler);
    
    /* Parse WBXML document */
    if ((ret = wbxml_parser_parse(wbxml_parser, wbxml, wbxml_len)) != WBXML_OK)
    {
        error_index = wbxml_parser_get_current_byte_index(wbxml_parser);
        printf("Parsing failed at %u - Token %x - %s", error_index, wbxml[error_index], wbxml_errors_string(ret));
    }
    else {
        printf("Parsing OK !");          
    }
    
    /* Destroy WBXML Parser */
    wbxml_parser_destroy(wbxml_parser);

    /* Free wbxml buffer */
    wbxml_free(wbxml);

    return 0;
}
