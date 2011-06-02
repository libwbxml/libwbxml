/*
 * libwbxml, the WBXML Library.
 * Copyright (C) 2002-2008 Aymerick Jehanne <aymerick@jehanne.org>
 * Copyright (C) 2008-2011 Michael Bell <michael.bell@opensync.org>
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
 * @file wbxml_tables.c
 * @ingroup wbxml_tables
 *
 * @author Aymerick Jehanne <aymerick@jehanne.org>
 * @date 02/03/17
 *
 * @brief WBXML Tables
 */

#include "wbxml_tables.h"
#include "wbxml_internals.h"
#include "wbxml_log.h"

/** 
 * @brief If undefined, only the WML 1.3 tables are used for all WML versions (WML 1.0 / WML 1.1 / WML 1.2 / WML 1.3).
 *        It saves space, and, well, every handset must supports WML 1.3 right now.
 *        If defined, each version has its own exact tables.
 */
#undef WBXML_TABLES_SEPARATE_WML_VERSIONS


/**************************************
 * Languages Public IDs
 */

/* WAP */
#if defined( WBXML_SUPPORT_WML )
const WBXMLPublicIDEntry sv_wml10_public_id           = { WBXML_PUBLIC_ID_WML10,              XML_PUBLIC_ID_WML10,            "wml",                  "http://www.wapforum.org/DTD/wml.xml"               };
const WBXMLPublicIDEntry sv_wml11_public_id           = { WBXML_PUBLIC_ID_WML11,              XML_PUBLIC_ID_WML11,            "wml",                  "http://www.wapforum.org/DTD/wml_1_1.dtd"           };
const WBXMLPublicIDEntry sv_wml12_public_id           = { WBXML_PUBLIC_ID_WML12,              XML_PUBLIC_ID_WML12,            "wml",                  "http://www.wapforum.org/DTD/wml12.dtd"             };
const WBXMLPublicIDEntry sv_wml13_public_id           = { WBXML_PUBLIC_ID_WML13,              XML_PUBLIC_ID_WML13,            "wml",                  "http://www.wapforum.org/DTD/wml13.dtd"             };
#endif /* WBXML_SUPPORT_WML */

#if defined( WBXML_SUPPORT_WTA )
const WBXMLPublicIDEntry sv_wta10_public_id           = { WBXML_PUBLIC_ID_WTA10,              XML_PUBLIC_ID_WTA10,            "wtai",                 "wtai.dtd"                                          };
const WBXMLPublicIDEntry sv_wtawml12_public_id        = { WBXML_PUBLIC_ID_WTAWML12,           XML_PUBLIC_ID_WTAWML12,         "wta-wml",              "http://www.wapforum.org/DTD/wta-wml12.dtd"         };
const WBXMLPublicIDEntry sv_channel11_public_id       = { WBXML_PUBLIC_ID_CHANNEL11,          XML_PUBLIC_ID_CHANNEL11,        "channel",              ""                                                  };
const WBXMLPublicIDEntry sv_channel12_public_id       = { WBXML_PUBLIC_ID_CHANNEL12,          XML_PUBLIC_ID_CHANNEL12,        "channel",              "http://www.wapforum.org/DTD/channel12.dtd"         };
#endif /* WBXML_SUPPORT_WTA */

#if defined( WBXML_SUPPORT_SI )
const WBXMLPublicIDEntry sv_si10_public_id            = { WBXML_PUBLIC_ID_SI10,               XML_PUBLIC_ID_SI10,             "si",                   "http://www.wapforum.org/DTD/si.dtd"                };
#endif /* WBXML_SUPPORT_SI */

#if defined( WBXML_SUPPORT_SL )
const WBXMLPublicIDEntry sv_sl10_public_id            = { WBXML_PUBLIC_ID_SL10,               XML_PUBLIC_ID_SL10,             "sl",                   "http://www.wapforum.org/DTD/sl.dtd"                };
#endif /* WBXML_SUPPORT_SL */

#if defined( WBXML_SUPPORT_CO )
const WBXMLPublicIDEntry sv_co10_public_id            = { WBXML_PUBLIC_ID_CO10,               XML_PUBLIC_ID_CO10,             "co",                   "http://www.wapforum.org/DTD/co_1.0.dtd"            };
#endif /* WBXML_SUPPORT_CO */

#if defined( WBXML_SUPPORT_PROV )
const WBXMLPublicIDEntry sv_prov10_public_id          = { WBXML_PUBLIC_ID_PROV10,             XML_PUBLIC_ID_PROV10,           "wap-provisioningdoc",  "http://www.wapforum.org/DTD/prov.dtd"              };
#endif /* WBXML_SUPPORT_PROV */

#if defined( WBXML_SUPPORT_EMN )
const WBXMLPublicIDEntry sv_emn10_public_id           = { WBXML_PUBLIC_ID_EMN10,              XML_PUBLIC_ID_EMN10,            "emn",                  "http://www.wapforum.org/DTD/emn.dtd"               }; 
#endif /* WBXML_SUPPORT_EMN */

#if defined( WBXML_SUPPORT_DRMREL )
const WBXMLPublicIDEntry sv_drmrel10_public_id        = { WBXML_PUBLIC_ID_DRMREL10,           XML_PUBLIC_ID_DRMREL10,         "o-ex:rights",          "http://www.openmobilealliance.org/DTD/drmrel10.dtd"};
#endif /* WBXML_SUPPORT_DRMREL */

#if defined( WBXML_SUPPORT_OTA_SETTINGS )
/* Ericsson / Nokia OTA Settings v7.0 */
const WBXMLPublicIDEntry sv_ota_settings_public_id    = { WBXML_PUBLIC_ID_OTA_SETTINGS,       XML_PUBLIC_ID_OTA_SETTINGS,     "CHARACTERISTIC-LIST",  "characteristic-list.dtd"  };
#endif /* WBXML_SUPPORT_OTA_SETTINGS */

#if defined( WBXML_SUPPORT_SYNCML )
/* SyncML 1.0 */
const WBXMLPublicIDEntry sv_syncml_syncml10_public_id = { WBXML_PUBLIC_ID_SYNCML_SYNCML10,    XML_PUBLIC_ID_SYNCML_SYNCML10,  "SyncML",               "http://www.syncml.org/docs/syncml_represent_v10_20001207.dtd"  };  
const WBXMLPublicIDEntry sv_syncml_devinf10_public_id = { WBXML_PUBLIC_ID_SYNCML_DEVINF10,    XML_PUBLIC_ID_SYNCML_DEVINF10,  "DevInf",               "http://www.syncml.org/docs/syncml_devinf_v10_20001207.dtd"     };
const WBXMLPublicIDEntry sv_syncml_metinf10_public_id = { WBXML_PUBLIC_ID_SYNCML_METINF10,    XML_PUBLIC_ID_SYNCML_METINF10,  "MetInf",               "http://www.syncml.org/docs/syncml_metinf_v10_20001207.dtd"     };

/* SyncML 1.1 */
const WBXMLPublicIDEntry sv_syncml_syncml11_public_id = { WBXML_PUBLIC_ID_SYNCML_SYNCML11,    XML_PUBLIC_ID_SYNCML_SYNCML11,  "SyncML",               "http://www.syncml.org/docs/syncml_represent_v11_20020213.dtd"  };
const WBXMLPublicIDEntry sv_syncml_devinf11_public_id = { WBXML_PUBLIC_ID_SYNCML_DEVINF11,    XML_PUBLIC_ID_SYNCML_DEVINF11,  "DevInf",               "http://www.syncml.org/docs/devinf_v11_20020215.dtd"            };
const WBXMLPublicIDEntry sv_syncml_metinf11_public_id = { WBXML_PUBLIC_ID_SYNCML_METINF11,    XML_PUBLIC_ID_SYNCML_METINF11,  "MetInf",               "http://www.syncml.org/docs/syncml_metinf_v11_20020215.dtd"     };

/* SyncML 1.2 */
const WBXMLPublicIDEntry sv_syncml_syncml12_public_id = { WBXML_PUBLIC_ID_SYNCML_SYNCML12,    XML_PUBLIC_ID_SYNCML_SYNCML12,  "SyncML",               "http://www.openmobilealliance.org/tech/DTD/OMA-TS-SyncML_RepPro_DTD-V1_2.dtd"         };
const WBXMLPublicIDEntry sv_syncml_devinf12_public_id = { WBXML_PUBLIC_ID_SYNCML_DEVINF12,    XML_PUBLIC_ID_SYNCML_DEVINF12,  "DevInf",               "http://www.openmobilealliance.org/tech/DTD/OMA-SyncML-Device_Information-DTD-1.2.dtd" };
const WBXMLPublicIDEntry sv_syncml_metinf12_public_id = { WBXML_PUBLIC_ID_SYNCML_METINF12,    XML_PUBLIC_ID_SYNCML_METINF12,  "MetInf",               "http://www.openmobilealliance.org/tech/DTD/OMA-TS-SyncML_MetaInfo_DTD-V1_2.dtd"       };
const WBXMLPublicIDEntry sv_syncml_dmddf12_public_id = { WBXML_PUBLIC_ID_SYNCML_DMDDF12,    XML_PUBLIC_ID_SYNCML_DMDDF12,     "MgmtTree",                "http://www.openmobilealliance.org/tech/DTD/dm_ddf-v1_2.dtd" };
#endif /* WBXML_SUPPORT_SYNCML */

#if defined( WBXML_SUPPORT_WV )
/* OMA Wireless Village CSP 1.1 / 1.2 */
const WBXMLPublicIDEntry sv_wv_csp11_public_id        = { WBXML_PUBLIC_ID_WV_CSP11,           XML_PUBLIC_ID_WV_CSP11,         "WV-CSP-Message",       "http://www.openmobilealliance.org/DTD/WV-CSP.XML"  };
const WBXMLPublicIDEntry sv_wv_csp12_public_id        = { WBXML_PUBLIC_ID_WV_CSP12,           XML_PUBLIC_ID_WV_CSP12,         "WV-CSP-Message",       "http://www.openmobilealliance.org/DTD/WV-CSP.DTD"  };
#endif /* WBXML_SUPPORT_WV */

#if defined( WBXML_SUPPORT_AIRSYNC )
const WBXMLPublicIDEntry sv_airsync_public_id         = { WBXML_PUBLIC_ID_AIRSYNC,            XML_PUBLIC_ID_AIRSYNC,          "AirSync",              "http://www.microsoft.com/"};
const WBXMLPublicIDEntry sv_activesync_public_id      = { WBXML_PUBLIC_ID_ACTIVESYNC,         XML_PUBLIC_ID_ACTIVESYNC,       "ActiveSync",           "http://www.microsoft.com/"};
#endif /* WBXML_SUPPORT_AIRSYNC */

#if defined( WBXML_SUPPORT_CONML )
const WBXMLPublicIDEntry sv_conml_public_id         = { WBXML_PUBLIC_ID_CONML,                XML_PUBLIC_ID_CONML,            "ConML",                "http://www.nokia.com/"};
#endif /* WBXML_SUPPORT_CONML */


/**************************************
 * Languages Tables
 */

#if defined( WBXML_SUPPORT_WML )

#ifdef WBXML_TABLES_SEPARATE_WML_VERSIONS

/********************************************
 *    WML 1.0 (WAP 1.0: "WML-30-Apr-98.pdf")
 */

const WBXMLTagEntry sv_wml10_tag_table[] = {
    { "a",         0x00, 0x22 },
    { "access",    0x00, 0x23 },
    { "b",         0x00, 0x24 },
    { "big",       0x00, 0x25 },
    { "br",        0x00, 0x26 },
    { "card",      0x00, 0x27 },
    { "do",        0x00, 0x28 },
    { "em",        0x00, 0x29 },
    { "fieldset",  0x00, 0x2a },
    { "go",        0x00, 0x2b },
    { "head",      0x00, 0x2c },
    { "i",         0x00, 0x2d },
    { "img",       0x00, 0x2e },
    { "input",     0x00, 0x2f },
    { "meta",      0x00, 0x30 },
    { "noop",      0x00, 0x31 },
    { "prev",      0x00, 0x32 },
    { "onevent",   0x00, 0x33 },
    { "optgroup",  0x00, 0x34 },
    { "option",    0x00, 0x35 },
    { "refresh",   0x00, 0x36 },
    { "select",    0x00, 0x37 },
    { "small",     0x00, 0x38 },
    { "strong",    0x00, 0x39 },
    { "tab",       0x00, 0x3a }, /* Deprecated */
    { "template",  0x00, 0x3b },
    { "timer",     0x00, 0x3c },
    { "u",         0x00, 0x3d },
    { "var",       0x00, 0x3e },
    { "wml",       0x00, 0x3f },
    { NULL,        0x00, 0x00 }
};


const WBXMLAttrEntry sv_wml10_attr_table[] = {
    { "accept-charset",  NULL,                                0x00, 0x05 },
    { "align",           "bottom",                            0x00, 0x06 },
    { "align",           "center",                            0x00, 0x07 },
    { "align",           "left",                              0x00, 0x08 },
    { "align",           "middle",                            0x00, 0x09 },
    { "align",           "right",                             0x00, 0x0a },
    { "align",           "top",                               0x00, 0x0b },
    { "alt",             NULL,                                0x00, 0x0c },
    { "content",         NULL,                                0x00, 0x0d },
    { "default",         NULL,                                0x00, 0x0e },
    { "domain",          NULL,                                0x00, 0x0f },
    { "emptyok",         "false",                             0x00, 0x10 },
    { "emptyok",         "true",                              0x00, 0x11 },
    { "format",          NULL,                                0x00, 0x12 },
    { "height",          NULL,                                0x00, 0x13 },
    { "hspace",          NULL,                                0x00, 0x14 },
    { "idefault",        NULL,                                0x00, 0x15 }, /* Deprecated */
    { "ikey",            NULL,                                0x00, 0x16 }, /* Deprecated */
    { "key",             NULL,                                0x00, 0x17 }, /* Deprecated */
    { "label",           NULL,                                0x00, 0x18 },
    { "localsrc",        NULL,                                0x00, 0x19 },
    { "maxlength",       NULL,                                0x00, 0x1a },
    { "method",          "get",                               0x00, 0x1b },
    { "method",          "post",                              0x00, 0x1c },
    { "mode",            "nowrap",                            0x00, 0x1d },
    { "mode",            "wrap",                              0x00, 0x1e },
    { "multiple",        "false",                             0x00, 0x1f },
    { "multiple",        "true",                              0x00, 0x20 },
    { "name",            NULL,                                0x00, 0x21 },
    { "newcontext",      "false",                             0x00, 0x22 },
    { "newcontext",      "true",                              0x00, 0x23 },
    { "onclick",         NULL,                                0x00, 0x24 }, /* Deprecated */
    { "onenterbackward", NULL,                                0x00, 0x25 },
    { "onenterforward",  NULL,                                0x00, 0x26 },
    { "ontimer",         NULL,                                0x00, 0x27 },
    { "optional",        "false",                             0x00, 0x28 },
    { "optional",        "true",                              0x00, 0x29 },
    { "path",            NULL,                                0x00, 0x2a },
    { "postdata",        NULL,                                0x00, 0x2b }, /* Deprecated */
    { "public",          "false",                             0x00, 0x2c }, /* Deprecated */
    { "public",          "true",                              0x00, 0x2d }, /* Deprecated */
    { "scheme",          NULL,                                0x00, 0x2e },
    { "sendreferer",     "false",                             0x00, 0x2f },
    { "sendreferer",     "true",                              0x00, 0x30 },
    { "size",            NULL,                                0x00, 0x31 },
    { "src",             NULL,                                0x00, 0x32 },
    { "style",           "list",                              0x00, 0x33 }, /* Deprecated */
    { "style",           "set",                               0x00, 0x34 }, /* Deprecated */
    { "tabindex",        NULL,                                0x00, 0x35 },
    { "title",           NULL,                                0x00, 0x36 },
    { "type",            NULL,                                0x00, 0x37 },
    { "type",            "accept",                            0x00, 0x38 },
    { "type",            "delete",                            0x00, 0x39 },
    { "type",            "help",                              0x00, 0x3a },
    { "type",            "password",                          0x00, 0x3b },
    { "type",            "onpick",                            0x00, 0x3c },
    { "type",            "onenterbackward",                   0x00, 0x3d },
    { "type",            "onenterforward",                    0x00, 0x3e },
    { "type",            "ontimer",                           0x00, 0x3f },
    { "type",            "options",                           0x00, 0x45 },
    { "type",            "prev",                              0x00, 0x46 },
    { "type",            "reset",                             0x00, 0x47 },
    { "type",            "text",                              0x00, 0x48 },
    { "type",            "vnd.",                              0x00, 0x49 },
    { "url",             NULL,                                0x00, 0x4a }, /* Deprecated */
    { "url",             "http://",                           0x00, 0x4b }, /* Deprecated */
    { "url",             "https://",                          0x00, 0x4c }, /* Deprecated */
    { "user-agent",      NULL,                                0x00, 0x4d }, /* Deprecated */
    { "value",           NULL,                                0x00, 0x4e },
    { "vspace",          NULL,                                0x00, 0x4f },
    { "width",           NULL,                                0x00, 0x50 },
    { "xml:lang",        NULL,                                0x00, 0x51 },
    { NULL,              NULL,                                0x00, 0x00 }
};


const WBXMLAttrValueEntry sv_wml10_attr_value_table[] = {
    { ".com/",           0x00, 0x85 },
    { ".edu/",           0x00, 0x86 },
    { ".net/",           0x00, 0x87 },
    { ".org/",           0x00, 0x88 },
    { "accept",          0x00, 0x89 },
    { "bottom",          0x00, 0x8a },
    { "clear",           0x00, 0x8b },
    { "delete",          0x00, 0x8c },
    { "help",            0x00, 0x8d },
    /* Do NOT change the order in this table please ! */
    { "http://www.",     0x00, 0x8f }, 
    { "http://",         0x00, 0x8e },
    { "https://www.",    0x00, 0x91 },
    { "https://",        0x00, 0x90 },    
    { "list",            0x00, 0x92 }, /* Deprecated */
    { "middle",          0x00, 0x93 },
    { "nowrap",          0x00, 0x94 },
    { "onclick",         0x00, 0x95 }, /* Deprecated */
    { "onenterbackward", 0x00, 0x96 },
    { "onenterforward",  0x00, 0x97 },
    { "ontimer",         0x00, 0x98 },
    { "options",         0x00, 0x99 },
    { "password",        0x00, 0x9a },
    { "reset",           0x00, 0x9b },
    { "set",             0x00, 0x9c }, /* Deprecated */
    { "text",            0x00, 0x9d },
    { "top",             0x00, 0x9e },
    { "unknown",         0x00, 0x9f },
    { "wrap",            0x00, 0xa0 },
    { "www.",            0x00, 0xa1 },
    { NULL,              0x00, 0x00 }
};


/***********************************************
 *    WML 1.1 (WAP 1.1: "SPEC-WML-19990616.pdf")
 */

const WBXMLTagEntry sv_wml11_tag_table[] = {
    { "a",         0x00, 0x1c },
    { "anchor",    0x00, 0x22 }, /* WML 1.1 */
    { "access",    0x00, 0x23 },
    { "b",         0x00, 0x24 },
    { "big",       0x00, 0x25 },
    { "br",        0x00, 0x26 },
    { "card",      0x00, 0x27 },
    { "do",        0x00, 0x28 },
    { "em",        0x00, 0x29 },
    { "fieldset",  0x00, 0x2a },
    { "go",        0x00, 0x2b },
    { "head",      0x00, 0x2c },
    { "i",         0x00, 0x2d },
    { "img",       0x00, 0x2e },
    { "input",     0x00, 0x2f },
    { "meta",      0x00, 0x30 },
    { "noop",      0x00, 0x31 },
    { "p",         0x00, 0x20 }, /* WML 1.1 */
    { "postfield", 0x00, 0x21 }, /* WML 1.1 */
    { "prev",      0x00, 0x32 },
    { "onevent",   0x00, 0x33 },
    { "optgroup",  0x00, 0x34 },
    { "option",    0x00, 0x35 },
    { "refresh",   0x00, 0x36 },
    { "select",    0x00, 0x37 },
    { "setvar",    0x00, 0x3e }, /* WML 1.1 */
    { "small",     0x00, 0x38 }, 
    { "strong",    0x00, 0x39 },
    { "table",     0x00, 0x1f }, /* WML 1.1 */
    { "td",        0x00, 0x1d }, /* WML 1.1 */
    { "template",  0x00, 0x3b },
    { "timer",     0x00, 0x3c },
    { "tr",        0x00, 0x1e }, /* WML 1.1 */
    { "u",         0x00, 0x3d },
    { "wml",       0x00, 0x3f },
    { NULL,        0x00, 0x00 }
};


const WBXMLAttrEntry sv_wml11_attr_table[] = {
    { "accept-charset",  NULL,                                0x00, 0x05 },
    { "align",           NULL,                                0x00, 0x52 }, /* WML 1.1 */
    { "align",           "bottom",                            0x00, 0x06 },
    { "align",           "center",                            0x00, 0x07 },
    { "align",           "left",                              0x00, 0x08 },
    { "align",           "middle",                            0x00, 0x09 },
    { "align",           "right",                             0x00, 0x0a },
    { "align",           "top",                               0x00, 0x0b },
    { "alt",             NULL,                                0x00, 0x0c },
    { "class",           NULL,                                0x00, 0x54 }, /* WML 1.1 */
    { "columns",         NULL,                                0x00, 0x53 }, /* WML 1.1 */
    { "content",         NULL,                                0x00, 0x0d },
    { "content",         "application/vnd.wap.wmlc;charset=", 0x00, 0x5c }, /* WML 1.1 */
    { "domain",          NULL,                                0x00, 0x0f },
    { "emptyok",         "false",                             0x00, 0x10 },
    { "emptyok",         "true",                              0x00, 0x11 },
    { "format",          NULL,                                0x00, 0x12 },
    { "forua",           "false",                             0x00, 0x56 }, /* WML 1.1 */
    { "forua",           "true",                              0x00, 0x57 }, /* WML 1.1 */
    { "height",          NULL,                                0x00, 0x13 },
    { "href",            NULL,                                0x00, 0x4a }, /* WML 1.1 */
    { "href",            "http://",                           0x00, 0x4b }, /* WML 1.1 */
    { "href",            "https://",                          0x00, 0x4c }, /* WML 1.1 */
    { "hspace",          NULL,                                0x00, 0x14 },
    { "http-equiv",      NULL,                                0x00, 0x5a }, /* WML 1.1 */
    { "http-equiv",      "Content-Type",                      0x00, 0x5b }, /* WML 1.1 */
    { "http-equiv",      "Expires",                           0x00, 0x5d }, /* WML 1.1 */
    { "id",              NULL,                                0x00, 0x55 }, /* WML 1.1 */
    { "ivalue",          NULL,                                0x00, 0x15 }, /* WML 1.1 */
    { "iname",           NULL,                                0x00, 0x16 }, /* WML 1.1 */
    { "label",           NULL,                                0x00, 0x18 },
    { "localsrc",        NULL,                                0x00, 0x19 },
    { "maxlength",       NULL,                                0x00, 0x1a },
    { "method",          "get",                               0x00, 0x1b },
    { "method",          "post",                              0x00, 0x1c },
    { "mode",            "nowrap",                            0x00, 0x1d },
    { "mode",            "wrap",                              0x00, 0x1e },
    { "multiple",        "false",                             0x00, 0x1f },
    { "multiple",        "true",                              0x00, 0x20 },
    { "name",            NULL,                                0x00, 0x21 },
    { "newcontext",      "false",                             0x00, 0x22 },
    { "newcontext",      "true",                              0x00, 0x23 },
    { "onenterbackward", NULL,                                0x00, 0x25 },
    { "onenterforward",  NULL,                                0x00, 0x26 },
    { "onpick",          NULL,                                0x00, 0x24 }, /* WML 1.1 */
    { "ontimer",         NULL,                                0x00, 0x27 },
    { "optional",        "false",                             0x00, 0x28 },
    { "optional",        "true",                              0x00, 0x29 },
    { "path",            NULL,                                0x00, 0x2a },
    { "scheme",          NULL,                                0x00, 0x2e },
    { "sendreferer",     "false",                             0x00, 0x2f },
    { "sendreferer",     "true",                              0x00, 0x30 },
    { "size",            NULL,                                0x00, 0x31 },
    { "src",             NULL,                                0x00, 0x32 },
    { "src",             "http://",                           0x00, 0x58 }, /* WML 1.1 */
    { "src",             "https://",                          0x00, 0x59 }, /* WML 1.1 */
    { "ordered",         "true",                              0x00, 0x33 }, /* WML 1.1 */
    { "ordered",         "false",                             0x00, 0x34 }, /* WML 1.1 */
    { "tabindex",        NULL,                                0x00, 0x35 },
    { "title",           NULL,                                0x00, 0x36 },
    { "type",            NULL,                                0x00, 0x37 },
    { "type",            "accept",                            0x00, 0x38 },
    { "type",            "delete",                            0x00, 0x39 },
    { "type",            "help",                              0x00, 0x3a },
    { "type",            "password",                          0x00, 0x3b },
    { "type",            "onpick",                            0x00, 0x3c },
    { "type",            "onenterbackward",                   0x00, 0x3d },
    { "type",            "onenterforward",                    0x00, 0x3e },
    { "type",            "ontimer",                           0x00, 0x3f },
    { "type",            "options",                           0x00, 0x45 },
    { "type",            "prev",                              0x00, 0x46 },
    { "type",            "reset",                             0x00, 0x47 },
    { "type",            "text",                              0x00, 0x48 },
    { "type",            "vnd.",                              0x00, 0x49 },
    { "value",           NULL,                                0x00, 0x4d },
    { "vspace",          NULL,                                0x00, 0x4e },
    { "width",           NULL,                                0x00, 0x4f },
    { "xml:lang",        NULL,                                0x00, 0x50 },
    { NULL,              NULL,                                0x00, 0x00 }
};


const WBXMLAttrValueEntry sv_wml11_attr_value_table[] = {
    { ".com/",           0x00, 0x85 },
    { ".edu/",           0x00, 0x86 },
    { ".net/",           0x00, 0x87 },
    { ".org/",           0x00, 0x88 },
    { "accept",          0x00, 0x89 },
    { "bottom",          0x00, 0x8a },
    { "clear",           0x00, 0x8b },
    { "delete",          0x00, 0x8c },
    { "help",            0x00, 0x8d },
    /* Do NOT change the order in this table please ! */
    { "http://www.",     0x00, 0x8f },
    { "http://",         0x00, 0x8e },
    { "https://www.",    0x00, 0x91 },
    { "https://",        0x00, 0x90 },    
    { "middle",          0x00, 0x93 },
    { "nowrap",          0x00, 0x94 },
    { "onenterbackward", 0x00, 0x96 },
    { "onenterforward",  0x00, 0x97 },
    { "onpick",          0x00, 0x95 }, /* WML 1.1 */
    { "ontimer",         0x00, 0x98 },
    { "options",         0x00, 0x99 },
    { "password",        0x00, 0x9a },
    { "reset",           0x00, 0x9b },
    { "text",            0x00, 0x9d },
    { "top",             0x00, 0x9e },
    { "unknown",         0x00, 0x9f },
    { "wrap",            0x00, 0xa0 },
    { "www.",            0x00, 0xa1 },
    { NULL,              0x00, 0x00 }
};


/***********************************************
 *    WML 1.2 (WAP 1.2: "SPEC-WML-19991104.pdf")
 */

const WBXMLTagEntry sv_wml12_tag_table[] = {
    { "a",         0x00, 0x1c },
    { "anchor",    0x00, 0x22 },
    { "access",    0x00, 0x23 },
    { "b",         0x00, 0x24 },
    { "big",       0x00, 0x25 },
    { "br",        0x00, 0x26 },
    { "card",      0x00, 0x27 },
    { "do",        0x00, 0x28 },
    { "em",        0x00, 0x29 },
    { "fieldset",  0x00, 0x2a },
    { "go",        0x00, 0x2b },
    { "head",      0x00, 0x2c },
    { "i",         0x00, 0x2d },
    { "img",       0x00, 0x2e },
    { "input",     0x00, 0x2f },
    { "meta",      0x00, 0x30 },
    { "noop",      0x00, 0x31 },
    { "p",         0x00, 0x20 },
    { "postfield", 0x00, 0x21 },
    { "pre",       0x00, 0x1b },
    { "prev",      0x00, 0x32 },
    { "onevent",   0x00, 0x33 },
    { "optgroup",  0x00, 0x34 },
    { "option",    0x00, 0x35 },
    { "refresh",   0x00, 0x36 },
    { "select",    0x00, 0x37 },
    { "setvar",    0x00, 0x3e },
    { "small",     0x00, 0x38 },
    { "strong",    0x00, 0x39 },
    { "table",     0x00, 0x1f },
    { "td",        0x00, 0x1d },
    { "template",  0x00, 0x3b },
    { "timer",     0x00, 0x3c },
    { "tr",        0x00, 0x1e },
    { "u",         0x00, 0x3d },
    { "wml",       0x00, 0x3f },
    { NULL,        0x00, 0x00 }
};


const WBXMLAttrEntry sv_wml12_attr_table[] = {
    { "accept-charset",  NULL,                                0x00, 0x05 },
    { "accesskey",       NULL,                                0x00, 0x5e }, /* WML 1.2 */
    { "align",           NULL,                                0x00, 0x52 },
    { "align",           "bottom",                            0x00, 0x06 },
    { "align",           "center",                            0x00, 0x07 },
    { "align",           "left",                              0x00, 0x08 },
    { "align",           "middle",                            0x00, 0x09 },
    { "align",           "right",                             0x00, 0x0a },
    { "align",           "top",                               0x00, 0x0b },
    { "alt",             NULL,                                0x00, 0x0c },
    { "class",           NULL,                                0x00, 0x54 },
    { "columns",         NULL,                                0x00, 0x53 },
    { "content",         NULL,                                0x00, 0x0d },
    { "content",         "application/vnd.wap.wmlc;charset=", 0x00, 0x5c },
    { "domain",          NULL,                                0x00, 0x0f },
    { "emptyok",         "false",                             0x00, 0x10 },
    { "emptyok",         "true",                              0x00, 0x11 },
    { "enctype",         NULL,                                0x00, 0x5f }, /* WML 1.2 */
    { "enctype",         "application/x-www-form-urlencoded", 0x00, 0x60 }, /* WML 1.2 */
    { "enctype",         "multipart/form-data",               0x00, 0x61 }, /* WML 1.2 */
    { "format",          NULL,                                0x00, 0x12 },
    { "forua",           "false",                             0x00, 0x56 },
    { "forua",           "true",                              0x00, 0x57 },
    { "height",          NULL,                                0x00, 0x13 },
    { "href",            NULL,                                0x00, 0x4a },
    { "href",            "http://",                           0x00, 0x4b },
    { "href",            "https://",                          0x00, 0x4c },
    { "hspace",          NULL,                                0x00, 0x14 },
    { "http-equiv",      NULL,                                0x00, 0x5a },
    { "http-equiv",      "Content-Type",                      0x00, 0x5b },
    { "http-equiv",      "Expires",                           0x00, 0x5d },
    { "id",              NULL,                                0x00, 0x55 },
    { "ivalue",          NULL,                                0x00, 0x15 },
    { "iname",           NULL,                                0x00, 0x16 },
    { "label",           NULL,                                0x00, 0x18 },
    { "localsrc",        NULL,                                0x00, 0x19 },
    { "maxlength",       NULL,                                0x00, 0x1a },
    { "method",          "get",                               0x00, 0x1b },
    { "method",          "post",                              0x00, 0x1c },
    { "mode",            "nowrap",                            0x00, 0x1d },
    { "mode",            "wrap",                              0x00, 0x1e },
    { "multiple",        "false",                             0x00, 0x1f },
    { "multiple",        "true",                              0x00, 0x20 },
    { "name",            NULL,                                0x00, 0x21 },
    { "newcontext",      "false",                             0x00, 0x22 },
    { "newcontext",      "true",                              0x00, 0x23 },
    { "onenterbackward", NULL,                                0x00, 0x25 },
    { "onenterforward",  NULL,                                0x00, 0x26 },
    { "onpick",          NULL,                                0x00, 0x24 },
    { "ontimer",         NULL,                                0x00, 0x27 },
    { "optional",        "false",                             0x00, 0x28 },
    { "optional",        "true",                              0x00, 0x29 },
    { "path",            NULL,                                0x00, 0x2a },
    { "scheme",          NULL,                                0x00, 0x2e },
    { "sendreferer",     "false",                             0x00, 0x2f },
    { "sendreferer",     "true",                              0x00, 0x30 },
    { "size",            NULL,                                0x00, 0x31 },
    { "src",             NULL,                                0x00, 0x32 },
    { "src",             "http://",                           0x00, 0x58 },
    { "src",             "https://",                          0x00, 0x59 },
    { "ordered",         "true",                              0x00, 0x33 },
    { "ordered",         "false",                             0x00, 0x34 },
    { "tabindex",        NULL,                                0x00, 0x35 },
    { "title",           NULL,                                0x00, 0x36 },
    { "type",            NULL,                                0x00, 0x37 },
    { "type",            "accept",                            0x00, 0x38 },
    { "type",            "delete",                            0x00, 0x39 },
    { "type",            "help",                              0x00, 0x3a },
    { "type",            "password",                          0x00, 0x3b },
    { "type",            "onpick",                            0x00, 0x3c },
    { "type",            "onenterbackward",                   0x00, 0x3d },
    { "type",            "onenterforward",                    0x00, 0x3e },
    { "type",            "ontimer",                           0x00, 0x3f },
    { "type",            "options",                           0x00, 0x45 },
    { "type",            "prev",                              0x00, 0x46 },
    { "type",            "reset",                             0x00, 0x47 },
    { "type",            "text",                              0x00, 0x48 },
    { "type",            "vnd.",                              0x00, 0x49 },
    { "value",           NULL,                                0x00, 0x4d },
    { "vspace",          NULL,                                0x00, 0x4e },
    { "width",           NULL,                                0x00, 0x4f },
    { "xml:lang",        NULL,                                0x00, 0x50 },
    { NULL,              NULL,                                0x00, 0x00 }
};


const WBXMLAttrValueEntry sv_wml12_attr_value_table[] = {
    { ".com/",           0x00, 0x85 },
    { ".edu/",           0x00, 0x86 },
    { ".net/",           0x00, 0x87 },
    { ".org/",           0x00, 0x88 },
    { "accept",          0x00, 0x89 },
    { "bottom",          0x00, 0x8a },
    { "clear",           0x00, 0x8b },
    { "delete",          0x00, 0x8c },
    { "help",            0x00, 0x8d },
    /* Do NOT change the order in this table please ! */
    { "http://www.",     0x00, 0x8f },
    { "http://",         0x00, 0x8e },
    { "https://www.",    0x00, 0x91 },
    { "https://",        0x00, 0x90 },    
    { "middle",          0x00, 0x93 },
    { "nowrap",          0x00, 0x94 },
    { "onenterbackward", 0x00, 0x96 },
    { "onenterforward",  0x00, 0x97 },
    { "onpick",          0x00, 0x95 },
    { "ontimer",         0x00, 0x98 },
    { "options",         0x00, 0x99 },
    { "password",        0x00, 0x9a },
    { "reset",           0x00, 0x9b },
    { "text",            0x00, 0x9d },
    { "top",             0x00, 0x9e },
    { "unknown",         0x00, 0x9f },
    { "wrap",            0x00, 0xa0 },
    { "www.",            0x00, 0xa1 },
    { NULL,              0x00, 0x00 }
};

#endif /* WBXML_TABLES_SEPARATE_WML_VERSIONS */


/******************************************************
 *    WML 1.3 (WAP 1.2.1: "WAP-191-WML-20000219-a.pdf")
 */

const WBXMLTagEntry sv_wml13_tag_table[] = {
    { "a",         0x00, 0x1c },
    { "anchor",    0x00, 0x22 }, /* WML 1.1 */
    { "access",    0x00, 0x23 },
    { "b",         0x00, 0x24 },
    { "big",       0x00, 0x25 },
    { "br",        0x00, 0x26 },
    { "card",      0x00, 0x27 },
    { "do",        0x00, 0x28 },
    { "em",        0x00, 0x29 },
    { "fieldset",  0x00, 0x2a },
    { "go",        0x00, 0x2b },
    { "head",      0x00, 0x2c },
    { "i",         0x00, 0x2d },
    { "img",       0x00, 0x2e },
    { "input",     0x00, 0x2f },
    { "meta",      0x00, 0x30 },
    { "noop",      0x00, 0x31 },
    { "p",         0x00, 0x20 }, /* WML 1.1 */
    { "postfield", 0x00, 0x21 }, /* WML 1.1 */
    { "pre",       0x00, 0x1b },
    { "prev",      0x00, 0x32 },
    { "onevent",   0x00, 0x33 },
    { "optgroup",  0x00, 0x34 },
    { "option",    0x00, 0x35 },
    { "refresh",   0x00, 0x36 },
    { "select",    0x00, 0x37 },
    { "setvar",    0x00, 0x3e }, /* WML 1.1 */
    { "small",     0x00, 0x38 },
    { "strong",    0x00, 0x39 },
    { "table",     0x00, 0x1f }, /* WML 1.1 */
    { "td",        0x00, 0x1d }, /* WML 1.1 */
    { "template",  0x00, 0x3b },
    { "timer",     0x00, 0x3c },
    { "tr",        0x00, 0x1e }, /* WML 1.1 */
    { "u",         0x00, 0x3d },
    { "wml",       0x00, 0x3f },
    { NULL,        0x00, 0x00 }
};


const WBXMLAttrEntry sv_wml13_attr_table[] = {
    { "accept-charset",  NULL,                                0x00, 0x05 },
    { "accesskey",       NULL,                                0x00, 0x5e }, /* WML 1.2 */
    { "align",           NULL,                                0x00, 0x52 }, /* WML 1.1 */
    { "align",           "bottom",                            0x00, 0x06 },
    { "align",           "center",                            0x00, 0x07 },
    { "align",           "left",                              0x00, 0x08 },
    { "align",           "middle",                            0x00, 0x09 },
    { "align",           "right",                             0x00, 0x0a },
    { "align",           "top",                               0x00, 0x0b },
    { "alt",             NULL,                                0x00, 0x0c },
    { "cache-control",   "no-cache",                          0x00, 0x64 }, /* WML 1.3 */
    { "class",           NULL,                                0x00, 0x54 }, /* WML 1.1 */
    { "columns",         NULL,                                0x00, 0x53 }, /* WML 1.1 */
    { "content",         NULL,                                0x00, 0x0d }, 
    { "content",         "application/vnd.wap.wmlc;charset=", 0x00, 0x5c }, /* WML 1.1 */
    { "domain",          NULL,                                0x00, 0x0f },
    { "emptyok",         "false",                             0x00, 0x10 },
    { "emptyok",         "true",                              0x00, 0x11 },
    { "enctype",         NULL,                                0x00, 0x5f }, /* WML 1.2 */
    { "enctype",         "application/x-www-form-urlencoded", 0x00, 0x60 }, /* WML 1.2 */
    { "enctype",         "multipart/form-data",               0x00, 0x61 }, /* WML 1.2 */
    { "format",          NULL,                                0x00, 0x12 },
    { "forua",           "false",                             0x00, 0x56 }, /* WML 1.1 */
    { "forua",           "true",                              0x00, 0x57 }, /* WML 1.1 */
    { "height",          NULL,                                0x00, 0x13 },
    { "href",            NULL,                                0x00, 0x4a }, /* WML 1.1 */
    { "href",            "http://",                           0x00, 0x4b }, /* WML 1.1 */
    { "href",            "https://",                          0x00, 0x4c }, /* WML 1.1 */
    { "hspace",          NULL,                                0x00, 0x14 },
    { "http-equiv",      NULL,                                0x00, 0x5a }, /* WML 1.1 */
    { "http-equiv",      "Content-Type",                      0x00, 0x5b }, /* WML 1.1 */
    { "http-equiv",      "Expires",                           0x00, 0x5d }, /* WML 1.1 */
    { "id",              NULL,                                0x00, 0x55 }, /* WML 1.1 */
    { "ivalue",          NULL,                                0x00, 0x15 }, /* WML 1.1 */
    { "iname",           NULL,                                0x00, 0x16 }, /* WML 1.1 */
    { "label",           NULL,                                0x00, 0x18 },
    { "localsrc",        NULL,                                0x00, 0x19 },
    { "maxlength",       NULL,                                0x00, 0x1a },
    { "method",          "get",                               0x00, 0x1b },
    { "method",          "post",                              0x00, 0x1c },
    { "mode",            "nowrap",                            0x00, 0x1d },
    { "mode",            "wrap",                              0x00, 0x1e },
    { "multiple",        "false",                             0x00, 0x1f },
    { "multiple",        "true",                              0x00, 0x20 },
    { "name",            NULL,                                0x00, 0x21 },
    { "newcontext",      "false",                             0x00, 0x22 },
    { "newcontext",      "true",                              0x00, 0x23 },
    { "onenterbackward", NULL,                                0x00, 0x25 },
    { "onenterforward",  NULL,                                0x00, 0x26 },
    { "onpick",          NULL,                                0x00, 0x24 }, /* WML 1.1 */
    { "ontimer",         NULL,                                0x00, 0x27 },
    { "optional",        "false",                             0x00, 0x28 },
    { "optional",        "true",                              0x00, 0x29 },
    { "path",            NULL,                                0x00, 0x2a },
    { "scheme",          NULL,                                0x00, 0x2e },
    { "sendreferer",     "false",                             0x00, 0x2f },
    { "sendreferer",     "true",                              0x00, 0x30 },
    { "size",            NULL,                                0x00, 0x31 },
    { "src",             NULL,                                0x00, 0x32 },
    { "src",             "http://",                           0x00, 0x58 }, /* WML 1.1 */
    { "src",             "https://",                          0x00, 0x59 }, /* WML 1.1 */
    { "ordered",         "true",                              0x00, 0x33 }, /* WML 1.1 */
    { "ordered",         "false",                             0x00, 0x34 }, /* WML 1.1 */
    { "tabindex",        NULL,                                0x00, 0x35 },
    { "title",           NULL,                                0x00, 0x36 },
    { "type",            NULL,                                0x00, 0x37 },
    { "type",            "accept",                            0x00, 0x38 },
    { "type",            "delete",                            0x00, 0x39 },
    { "type",            "help",                              0x00, 0x3a },
    { "type",            "password",                          0x00, 0x3b },
    { "type",            "onpick",                            0x00, 0x3c },
    { "type",            "onenterbackward",                   0x00, 0x3d },
    { "type",            "onenterforward",                    0x00, 0x3e },
    { "type",            "ontimer",                           0x00, 0x3f },
    { "type",            "options",                           0x00, 0x45 },
    { "type",            "prev",                              0x00, 0x46 },
    { "type",            "reset",                             0x00, 0x47 },
    { "type",            "text",                              0x00, 0x48 },
    { "type",            "vnd.",                              0x00, 0x49 },
    { "value",           NULL,                                0x00, 0x4d },
    { "vspace",          NULL,                                0x00, 0x4e },
    { "width",           NULL,                                0x00, 0x4f },
    { "xml:lang",        NULL,                                0x00, 0x50 },
    { "xml:space",       "preserve",                          0x00, 0x62 }, /* WML 1.3 */
    { "xml:space",       "default",                           0x00, 0x63 }, /* WML 1.3 */
    { NULL,              NULL,                                0x00, 0x00 }
};


const WBXMLAttrValueEntry sv_wml13_attr_value_table[] = {
    { ".com/",           0x00, 0x85 },
    { ".edu/",           0x00, 0x86 },
    { ".net/",           0x00, 0x87 },
    { ".org/",           0x00, 0x88 },
    { "accept",          0x00, 0x89 },
    { "bottom",          0x00, 0x8a },
    { "clear",           0x00, 0x8b },
    { "delete",          0x00, 0x8c },
    { "help",            0x00, 0x8d },
    /* Do NOT change the order in this table please ! */
    { "http://www.",     0x00, 0x8f },
    { "http://",         0x00, 0x8e },
    { "https://www.",    0x00, 0x91 },
    { "https://",        0x00, 0x90 },    
    { "middle",          0x00, 0x93 },
    { "nowrap",          0x00, 0x94 },
    { "onenterbackward", 0x00, 0x96 },
    { "onenterforward",  0x00, 0x97 },
    { "onpick",          0x00, 0x95 }, /* WML 1.1 */
    { "ontimer",         0x00, 0x98 },
    { "options",         0x00, 0x99 },
    { "password",        0x00, 0x9a },
    { "reset",           0x00, 0x9b },
    { "text",            0x00, 0x9d },
    { "top",             0x00, 0x9e },
    { "unknown",         0x00, 0x9f },
    { "wrap",            0x00, 0xa0 },
    { "www.",            0x00, 0xa1 },
    { NULL,              0x00, 0x00 }
};

#endif /* WBXML_SUPPORT_WML */



#if defined( WBXML_SUPPORT_WTA )

/********************************************
 *    WTA 1.0 (WAP 1.0: "wta-30-apr-98.pdf")
 */

const WBXMLTagEntry sv_wta10_tag_table[] = {
    { "EVENT",          0x00, 0x05 },
    { "EVENTTABLE",     0x00, 0x06 },
    { "TYPE",           0x00, 0x07 },
    { "URL",            0x00, 0x08 },
    { "WTAI",           0x00, 0x09 },
    { NULL,             0x00, 0x00 }
};

const WBXMLAttrEntry sv_wta10_attr_table[] = {
    { "NAME",       NULL,                    0x00, 0x05 },
    { "VALUE",      NULL,                    0x00, 0x06 },
    { NULL,         NULL,                    0x00, 0x00 }
};


/***********************************************
 *    WTA WML 1.2 ("WAP-266-WTA-20010908-a.pdf")
 */

const WBXMLTagEntry sv_wtawml12_tag_table[] = {
    /* Code Page 0 (WML 1.2) */
    { "a",         0x00, 0x1c },
    { "anchor",    0x00, 0x22 },
    { "access",    0x00, 0x23 },
    { "b",         0x00, 0x24 },
    { "big",       0x00, 0x25 },
    { "br",        0x00, 0x26 },
    { "card",      0x00, 0x27 },
    { "do",        0x00, 0x28 },
    { "em",        0x00, 0x29 },
    { "fieldset",  0x00, 0x2a },
    { "go",        0x00, 0x2b },
    { "head",      0x00, 0x2c },
    { "i",         0x00, 0x2d },
    { "img",       0x00, 0x2e },
    { "input",     0x00, 0x2f },
    { "meta",      0x00, 0x30 },
    { "noop",      0x00, 0x31 },
    { "p",         0x00, 0x20 },
    { "postfield", 0x00, 0x21 },
    { "pre",       0x00, 0x1b },
    { "prev",      0x00, 0x32 },
    { "onevent",   0x00, 0x33 },
    { "optgroup",  0x00, 0x34 },
    { "option",    0x00, 0x35 },
    { "refresh",   0x00, 0x36 },
    { "select",    0x00, 0x37 },
    { "setvar",    0x00, 0x3e },
    { "small",     0x00, 0x38 },
    { "strong",    0x00, 0x39 },
    { "table",     0x00, 0x1f },
    { "td",        0x00, 0x1d },
    { "template",  0x00, 0x3b },
    { "timer",     0x00, 0x3c },
    { "tr",        0x00, 0x1e },
    { "u",         0x00, 0x3d },
    { "wml",       0x00, 0x3f },

    /* Code Page 1 (WTA) */
    { "wta-wml",   0x01, 0x3f },
    { NULL,        0x00, 0x00 }
};

const WBXMLAttrEntry sv_wtawml12_attr_table[] = {
    /* Code Page 0 (WML 1.2) */
    { "accept-charset",  NULL,                                0x00, 0x05 },
    { "accesskey",       NULL,                                0x00, 0x5e },
    { "align",           NULL,                                0x00, 0x52 },
    { "align",           "bottom",                            0x00, 0x06 },
    { "align",           "center",                            0x00, 0x07 },
    { "align",           "left",                              0x00, 0x08 },
    { "align",           "middle",                            0x00, 0x09 },
    { "align",           "right",                             0x00, 0x0a },
    { "align",           "top",                               0x00, 0x0b },
    { "alt",             NULL,                                0x00, 0x0c },
    { "class",           NULL,                                0x00, 0x54 },
    { "columns",         NULL,                                0x00, 0x53 },
    { "content",         NULL,                                0x00, 0x0d },
    { "content",         "application/vnd.wap.wmlc;charset=", 0x00, 0x5c },
    { "domain",          NULL,                                0x00, 0x0f },
    { "emptyok",         "false",                             0x00, 0x10 },
    { "emptyok",         "true",                              0x00, 0x11 },
    { "enctype",         NULL,                                0x00, 0x5f },
    { "enctype",         "application/x-www-form-urlencoded", 0x00, 0x60 },    
    { "enctype",         "multipart/form-data",               0x00, 0x61 },
    { "format",          NULL,                                0x00, 0x12 },
    { "forua",           "false",                             0x00, 0x56 },
    { "forua",           "true",                              0x00, 0x57 },
    { "height",          NULL,                                0x00, 0x13 },
    { "href",            NULL,                                0x00, 0x4a },
    { "href",            "http://",                           0x00, 0x4b },
    { "href",            "https://",                          0x00, 0x4c },
    { "hspace",          NULL,                                0x00, 0x14 },
    { "http-equiv",      NULL,                                0x00, 0x5a },
    { "http-equiv",      "Content-Type",                      0x00, 0x5b },
    { "http-equiv",      "Expires",                           0x00, 0x5d },
    { "id",              NULL,                                0x00, 0x55 },
    { "ivalue",          NULL,                                0x00, 0x15 },
    { "iname",           NULL,                                0x00, 0x16 },
    { "label",           NULL,                                0x00, 0x18 },
    { "localsrc",        NULL,                                0x00, 0x19 },
    { "maxlength",       NULL,                                0x00, 0x1a },
    { "method",          "get",                               0x00, 0x1b },
    { "method",          "post",                              0x00, 0x1c },
    { "mode",            "nowrap",                            0x00, 0x1d },
    { "mode",            "wrap",                              0x00, 0x1e },
    { "multiple",        "false",                             0x00, 0x1f },
    { "multiple",        "true",                              0x00, 0x20 },
    { "name",            NULL,                                0x00, 0x21 },
    { "newcontext",      "false",                             0x00, 0x22 },
    { "newcontext",      "true",                              0x00, 0x23 },
    { "onenterbackward", NULL,                                0x00, 0x25 },
    { "onenterforward",  NULL,                                0x00, 0x26 },
    { "onpick",          NULL,                                0x00, 0x24 },
    { "ontimer",         NULL,                                0x00, 0x27 },
    { "optional",        "false",                             0x00, 0x28 },
    { "optional",        "true",                              0x00, 0x29 },
    { "path",            NULL,                                0x00, 0x2a },
    { "scheme",          NULL,                                0x00, 0x2e },
    { "sendreferer",     "false",                             0x00, 0x2f },
    { "sendreferer",     "true",                              0x00, 0x30 },
    { "size",            NULL,                                0x00, 0x31 },
    { "src",             NULL,                                0x00, 0x32 },
    { "src",             "http://",                           0x00, 0x58 },
    { "src",             "https://",                          0x00, 0x59 },
    { "ordered",         "true",                              0x00, 0x33 },
    { "ordered",         "false",                             0x00, 0x34 },
    { "tabindex",        NULL,                                0x00, 0x35 },
    { "title",           NULL,                                0x00, 0x36 },
    { "type",            NULL,                                0x00, 0x37 },
    { "type",            "accept",                            0x00, 0x38 },
    { "type",            "delete",                            0x00, 0x39 },
    { "type",            "help",                              0x00, 0x3a },
    { "type",            "password",                          0x00, 0x3b },
    { "type",            "onpick",                            0x00, 0x3c },
    { "type",            "onenterbackward",                   0x00, 0x3d },
    { "type",            "onenterforward",                    0x00, 0x3e },
    { "type",            "ontimer",                           0x00, 0x3f },
    { "type",            "options",                           0x00, 0x45 },
    { "type",            "prev",                              0x00, 0x46 },
    { "type",            "reset",                             0x00, 0x47 },
    { "type",            "text",                              0x00, 0x48 },
    { "type",            "vnd.",                              0x00, 0x49 },
    { "value",           NULL,                                0x00, 0x4d },
    { "vspace",          NULL,                                0x00, 0x4e },
    { "width",           NULL,                                0x00, 0x4f },
    { "xml:lang",        NULL,                                0x00, 0x50 },

    /* Code Page 1 (WTA) */
    /* Do NOT change the order in this table please ! */
    { "href",             "wtai://wp/mc;",                      0x01, 0x06 },
    { "href",             "wtai://wp/sd;",                      0x01, 0x07 },
    { "href",             "wtai://wp/ap;",                      0x01, 0x08 },
    { "href",             "wtai://ms/ec;",                      0x01, 0x09 },
    { "href",             "wtai://",                            0x01, 0x05 },        
    { "type",             "wtaev-cc/ic",                        0x01, 0x12 },
    { "type",             "wtaev-cc/cl",                        0x01, 0x13 },
    { "type",             "wtaev-cc/co",                        0x01, 0x14 },
    { "type",             "wtaev-cc/oc",                        0x01, 0x15 },
    { "type",             "wtaev-cc/cc",                        0x01, 0x16 },
    { "type",             "wtaev-cc/dtmf",                      0x01, 0x17 },
    { "type",             "wtaev-nt/it",                        0x01, 0x21 },
    { "type",             "wtaev-nt/st",                        0x01, 0x22 },
    { "type",             "wtaev-nt/",                          0x01, 0x20 },
    { "type",             "wtaev-pb/",                          0x01, 0x30 },
    { "type",             "wtaev-lg/",                          0x01, 0x38 },
    { "type",             "wtaev-ms/ns",                        0x01, 0x51 },
    { "type",             "wtaev-ms/",                          0x01, 0x50 },
    { "type",             "wtaev-gsm/ru",                       0x01, 0x59 },
    { "type",             "wtaev-gsm/ch",                       0x01, 0x5a },
    { "type",             "wtaev-gsm/ca",                       0x01, 0x5b },
    { "type",             "wtaev-gsm/",                         0x01, 0x58 },
    { "type",             "wtaev-pdc",                          0x01, 0x60 },
    { "type",             "wtaev-ansi136/ia",                   0x01, 0x69 },
    { "type",             "wtaev-ansi136/if",                   0x01, 0x6a },
    { "type",             "wtaev-ansi136",                      0x01, 0x68 },
    { "type",             "wtaev-cdma/",                        0x01, 0x70 },
    { "type",             "wtaev-cc",                           0x01, 0x11 },
    { "type",             "wtaev-",                             0x01, 0x10 },
    { NULL,               NULL,                                 0x00, 0x00 }
};

const WBXMLAttrValueEntry sv_wtawml12_attr_value_table[] = {
    /* Code Page 0 (WML 1.2) */
    { ".com/",           0x00, 0x85 },
    { ".edu/",           0x00, 0x86 },
    { ".net/",           0x00, 0x87 },
    { ".org/",           0x00, 0x88 },
    { "accept",          0x00, 0x89 },
    { "bottom",          0x00, 0x8a },
    { "clear",           0x00, 0x8b },
    { "delete",          0x00, 0x8c },
    { "help",            0x00, 0x8d },
    /* Do NOT change the order in this table please ! */
    { "http://www.",     0x00, 0x8f },
    { "http://",         0x00, 0x8e },    
    { "https://www.",    0x00, 0x91 },
    { "https://",        0x00, 0x90 },    
    { "middle",          0x00, 0x93 },
    { "nowrap",          0x00, 0x94 },
    { "onenterbackward", 0x00, 0x96 },
    { "onenterforward",  0x00, 0x97 },
    { "onpick",          0x00, 0x95 },
    { "ontimer",         0x00, 0x98 },
    { "options",         0x00, 0x99 },
    { "password",        0x00, 0x9a },
    { "reset",           0x00, 0x9b },
    { "text",            0x00, 0x9d },
    { "top",             0x00, 0x9e },
    { "unknown",         0x00, 0x9f },
    { "wrap",            0x00, 0xa0 },
    { "www.",            0x00, 0xa1 },
    { NULL,              0x00, 0x00 }
};


/***************************************************
 *    CHANNEL 1.1 (WAP 1.1: "SPEC-WTA-19990716.pdf")
 */

const WBXMLTagEntry sv_channel11_tag_table[] = {
    { "channel",        0x00, 0x05 },
    { "title",          0x00, 0x06 },
    { "abstract",       0x00, 0x07 },
    { "resource",       0x00, 0x08 },
    { NULL,             0x00, 0x00 }
};

const WBXMLAttrEntry sv_channel11_attr_table[] = {
    { "maxspace",   NULL,           0x00, 0x05 },
    { "base",       NULL,           0x00, 0x06 },
    { "href",       NULL,           0x00, 0x07 },
    { "href",       "http://",      0x00, 0x08 },
    { "href",       "https://",     0x00, 0x09 },
    { "lastmod",    NULL,           0x00, 0x0a },
    { "etag",       NULL,           0x00, 0x0b },
    { "md5",        NULL,           0x00, 0x0c },
    { "success",    NULL,           0x00, 0x0d },
    { "success",    "http://",      0x00, 0x0e },
    { "success",    "https://",     0x00, 0x0f },
    { "failure",    NULL,           0x00, 0x10 },
    { "failure",    "http://",      0x00, 0x11 },
    { "failure",    "https://",     0x00, 0x12 },
    { "EventId",    NULL,           0x00, 0x13 },
    { NULL,         NULL,           0x00, 0x00 }
};


/***********************************************
 *    CHANNEL 1.2 ("WAP-266-WTA-20010908-a.pdf")
 */

const WBXMLTagEntry sv_channel12_tag_table[] = {
    { "channel",        0x00, 0x05 },
    { "title",          0x00, 0x06 },
    { "abstract",       0x00, 0x07 },
    { "resource",       0x00, 0x08 },
    { NULL,             0x00, 0x00 }
};


const WBXMLAttrEntry sv_channel12_attr_table[] = {
    { "maxspace",       NULL,           0x00, 0x05 },
    { "base",           NULL,           0x00, 0x06 },
    { "href",           NULL,           0x00, 0x07 },
    { "href",           "http://",      0x00, 0x08 },
    { "href",           "https://",     0x00, 0x09 },
    { "lastmod",        NULL,           0x00, 0x0a },
    { "etag",            NULL,          0x00, 0x0b },
    { "md5",            NULL,           0x00, 0x0c },
    { "success",        NULL,           0x00, 0x0d },
    { "success",        "http://",      0x00, 0x0e },
    { "success",        "https://",     0x00, 0x0f },
    { "failure",        NULL,           0x00, 0x10 },
    { "failure",        "http://",      0x00, 0x11 },
    { "failure",        "https://",     0x00, 0x12 },
    { "eventid",        NULL,           0x00, 0x13 },
    { "eventid",            "wtaev-",   0x00, 0x14 },
    { "channelid",          NULL,       0x00, 0x15 },
    { "useraccessible",     NULL,       0x00, 0x16 },
    { NULL,                 NULL,       0x00, 0x00 }
};

#endif /* WBXML_SUPPORT_WTA */


#if defined( WBXML_SUPPORT_SI )

/*************************************************
 *    SI 1.0 ("WAP-167-ServiceInd-20010731-a.pdf")
 */

const WBXMLTagEntry sv_si10_tag_table[] = {
    { "si",             0x00, 0x05 },
    { "indication",     0x00, 0x06 },
    { "info",           0x00, 0x07 },
    { "item",           0x00, 0x08 },
    { NULL,             0x00, 0x00 }
};


const WBXMLAttrEntry sv_si10_attr_table[] = {
    { "action",  "signal-none",             0x00, 0x05 },
    { "action",  "signal-low",              0x00, 0x06 },
    { "action",  "signal-medium",           0x00, 0x07 },
    { "action",  "signal-high",             0x00, 0x08 },
    { "action",  "delete",                  0x00, 0x09 },
    { "created", NULL,                      0x00, 0x0a },
    { "href",    NULL,                      0x00, 0x0b },
    /* Do NOT change the order in this table please ! */
    { "href",    "http://www.",             0x00, 0x0d },
    { "href",    "http://",                 0x00, 0x0c },
    { "href",    "https://www.",            0x00, 0x0f },
    { "href",    "https://",                0x00, 0x0e },    
    { "si-expires", NULL,                   0x00, 0x10 },
    { "si-id",      NULL,                   0x00, 0x11 },
    { "class",      NULL,                   0x00, 0x12 },
    { NULL,         NULL,                   0x00, 0x00 }
};


const WBXMLAttrValueEntry sv_si10_attr_value_table[] = {
    { ".com/",           0x00, 0x85 },
    { ".edu/",           0x00, 0x86 },
    { ".net/",           0x00, 0x87 },
    { ".org/",           0x00, 0x88 },
    { NULL,              0x00, 0x00 }
};

#endif /* WBXML_SUPPORT_SI */


#if defined( WBXML_SUPPORT_SL )

/**************************************************
 *    SL 1.0 ("WAP-168-ServiceLoad-20010731-a.pdf")
 */

const WBXMLTagEntry sv_sl10_tag_table[] = {
    { "sl",              0x00, 0x05 },
    { NULL,              0x00, 0x00 }
};


const WBXMLAttrEntry sv_sl10_attr_table[] = {
    { "action",  "execute-low",         0x00, 0x05 },
    { "action",  "execute-high",        0x00, 0x06 },
    { "action",  "cache",               0x00, 0x07 },
    { "href",    NULL,                  0x00, 0x08 },
    /* Do NOT change the order in this table please ! */
    { "href",    "http://www.",         0x00, 0x0a },
    { "href",    "http://",             0x00, 0x09 },
    { "href",    "https://www.",        0x00, 0x0c },
    { "href",    "https://",            0x00, 0x0b },    
    { NULL,      NULL,                  0x00, 0x00 }
};


const WBXMLAttrValueEntry sv_sl10_attr_value_table[] = {
    { ".com/",           0x00, 0x85 },
    { ".edu/",           0x00, 0x86 },
    { ".net/",           0x00, 0x87 },
    { ".org/",           0x00, 0x88 },
    { NULL,              0x00, 0x00 }
};

#endif /* WBXML_SUPPORT_SL */


#if defined( WBXML_SUPPORT_CO )

/***********************************************
 *    CO 1.0 ("WAP-175-CacheOp-20010731-a.pdf")
 */

const WBXMLTagEntry sv_co10_tag_table[] = {
    { "co",                     0x00, 0x05 },
    { "invalidate-object",      0x00, 0x06 },
    { "invalidate-service",     0x00, 0x07 },
    { NULL,                     0x00, 0x00 }
};


const WBXMLAttrEntry sv_co10_attr_table[] = {
    { "uri",    NULL,                   0x00, 0x05 },
    /* Do NOT change the order in this table please ! */
    { "uri",    "http://www.",          0x00, 0x07 },
    { "uri",    "http://",              0x00, 0x06 },
    { "uri",    "https://www.",         0x00, 0x09 },
    { "uri",    "https://",             0x00, 0x08 },    
    { NULL,     NULL,                   0x00, 0x00 }
};


const WBXMLAttrValueEntry sv_co10_attr_value_table[] = {
    { ".com/",           0x00, 0x85 },
    { ".edu/",           0x00, 0x86 },
    { ".net/",           0x00, 0x87 },
    { ".org/",           0x00, 0x88 },
    { NULL,              0x00, 0x00 }
};

#endif /* WBXML_SUPPORT_CO */


#if defined( WBXML_SUPPORT_PROV )

/** Use OMA PROV 1.1 Tables (only 'sv_prov10_attr_value_table' changed) */
#define WBXML_SUPPORT_PROV_11

/**********************************************************
 *    PROV 1.0
 *      WAP 2.0: "WAP-183-PROVCONT-20010724-a.pdf"
 *      OMA: "OMA-WAP-ProvCont-v1_1-20021112-C.PDF"
 *
 *    PROV 1.1
 *      OMA: OMA-WAP-ProvCont-v1_1-20050428-Cchangebars.doc
 *      There is no new Public ID defined for this new version,
 *      so how should we handle this ??
 */

const WBXMLTagEntry sv_prov10_tag_table[] = {
    { "wap-provisioningdoc",        0x00, 0x05 },
    { "characteristic",             0x00, 0x06 },
    { "parm",                       0x00, 0x07 },
    
    { "characteristic",             0x01, 0x06 }, /* OMA */
    { "parm",                       0x01, 0x07 }, /* OMA */
    { NULL,                         0x00, 0x00 }
};


const WBXMLAttrEntry sv_prov10_attr_table[] = {
    /* Wap-provisioningdoc */
    { "version",    NULL,               0x00, 0x45 },
    { "version",    "1.0",              0x00, 0x46 },

    /* Characteristic */
    { "type",        NULL,                  0x00, 0x50 },
    { "type",        "PXLOGICAL",           0x00, 0x51 },
    { "type",        "PXPHYSICAL",          0x00, 0x52 },
    { "type",        "PORT",                0x00, 0x53 },
    { "type",        "VALIDITY",            0x00, 0x54 },
    { "type",        "NAPDEF",              0x00, 0x55 },
    { "type",        "BOOTSTRAP",           0x00, 0x56 },
    { "type",        "VENDORCONFIG",        0x00, 0x57 },
    { "type",        "CLIENTIDENTITY",      0x00, 0x58 },
    { "type",        "PXAUTHINFO",          0x00, 0x59 },
    { "type",        "NAPAUTHINFO",         0x00, 0x5a },
    { "type",        "ACCESS",              0x00, 0x5b }, /* OMA */
    
    { "type",        NULL,                  0x01, 0x50 }, /* OMA */
    { "type",        "PORT",                0x01, 0x53 }, /* OMA */
    { "type",        "CLIENTIDENTITY",      0x01, 0x58 }, /* OMA */
    { "type",        "APPLICATION",         0x01, 0x55 }, /* OMA */
    { "type",        "APPADDR",             0x01, 0x56 }, /* OMA */
    { "type",        "APPAUTH",             0x01, 0x57 }, /* OMA */
    { "type",        "RESOURCE",            0x01, 0x59 }, /* OMA */

    /* Parm */
    { "name",        NULL,                  0x00, 0x05 },
    { "value",       NULL,                  0x00, 0x06 },
    { "name",        "NAME",                0x00, 0x07 },
    { "name",        "NAP-ADDRESS",         0x00, 0x08 },
    { "name",        "NAP-ADDRTYPE",        0x00, 0x09 },
    { "name",        "CALLTYPE",            0x00, 0x0a },
    { "name",        "VALIDUNTIL",          0x00, 0x0b },
    { "name",        "AUTHTYPE",            0x00, 0x0c },
    { "name",        "AUTHNAME",            0x00, 0x0d },
    { "name",        "AUTHSECRET",          0x00, 0x0e },
    { "name",        "LINGER",              0x00, 0x0f },
    { "name",        "BEARER",              0x00, 0x10 },
    { "name",        "NAPID",               0x00, 0x11 },
    { "name",        "COUNTRY",             0x00, 0x12 },
    { "name",        "NETWORK",             0x00, 0x13 },
    { "name",        "INTERNET",            0x00, 0x14 },
    { "name",        "PROXY-ID",            0x00, 0x15 },
    { "name",        "PROXY-PROVIDER-ID",   0x00, 0x16 },
    { "name",        "DOMAIN",              0x00, 0x17 },
    { "name",        "PROVURL",             0x00, 0x18 },
    { "name",        "PXAUTH-TYPE",         0x00, 0x19 },
    { "name",        "PXAUTH-ID",           0x00, 0x1a },
    { "name",        "PXAUTH-PW",           0x00, 0x1b },
    { "name",        "STARTPAGE",           0x00, 0x1c },
    { "name",        "BASAUTH-ID",          0x00, 0x1d },
    { "name",        "BASAUTH-PW",          0x00, 0x1e },
    { "name",        "PUSHENABLED",         0x00, 0x1f },
    { "name",        "PXADDR",              0x00, 0x20 },
    { "name",        "PXADDRTYPE",          0x00, 0x21 },
    { "name",        "TO-NAPID",            0x00, 0x22 },
    { "name",        "PORTNBR",             0x00, 0x23 },
    { "name",        "SERVICE",             0x00, 0x24 },
    { "name",        "LINKSPEED",           0x00, 0x25 },
    { "name",        "DNLINKSPEED",         0x00, 0x26 },
    { "name",        "LOCAL-ADDR",          0x00, 0x27 },
    { "name",        "LOCAL-ADDRTYPE",      0x00, 0x28 },
    { "name",        "CONTEXT-ALLOW",       0x00, 0x29 },
    { "name",        "TRUST",               0x00, 0x2a },
    { "name",        "MASTER",              0x00, 0x2b },
    { "name",        "SID",                 0x00, 0x2c },
    { "name",        "SOC",                 0x00, 0x2d },
    { "name",        "WSP-VERSION",         0x00, 0x2e },
    { "name",        "PHYSICAL-PROXY-ID",   0x00, 0x2f },
    { "name",        "CLIENT-ID",           0x00, 0x30 },
    { "name",        "DELIVERY-ERR-SDU",    0x00, 0x31 },
    { "name",        "DELIVERY-ORDER",      0x00, 0x32 },
    { "name",        "TRAFFIC-CLASS",       0x00, 0x33 },
    { "name",        "MAX-SDU-SIZE",        0x00, 0x34 },
    { "name",        "MAX-BITRATE-UPLINK",  0x00, 0x35 },
    { "name",        "MAX-BITRATE-DNLINK",  0x00, 0x36 },
    { "name",        "RESIDUAL-BER",        0x00, 0x37 },
    { "name",        "SDU-ERROR-RATIO",     0x00, 0x38 },
    { "name",        "TRAFFIC-HANDL-PRIO",  0x00, 0x39 },
    { "name",        "TRANSFER-DELAY",      0x00, 0x3a },
    { "name",        "GUARANTEED-BITRATE-UPLINK",   0x00, 0x3b },
    { "name",        "GUARANTEED-BITRATE-DNLINK",   0x00, 0x3c },
    { "name",        "PXADDR-FQDN",         0x00, 0x3d }, /* OMA */
    { "name",        "PROXY-PW",            0x00, 0x3e }, /* OMA */
    { "name",        "PPGAUTH-TYPE",        0x00, 0x3f }, /* OMA */
    { "name",        "PULLENABLED",         0x00, 0x47 }, /* OMA */
    { "name",        "DNS-ADDR",            0x00, 0x48 }, /* OMA */
    { "name",        "MAX-NUM-RETRY",       0x00, 0x49 }, /* OMA */
    { "name",        "FIRST-RETRY-TIMEOUT", 0x00, 0x4a }, /* OMA */
    { "name",        "REREG-THRESHOLD",     0x00, 0x4b }, /* OMA */
    { "name",        "T-BIT",               0x00, 0x4c }, /* OMA */
    { "name",        "AUTH-ENTITY",         0x00, 0x4e }, /* OMA */
    { "name",        "SPI",                 0x00, 0x4f }, /* OMA */
    
    { "name",        NULL,                  0x01, 0x05 }, /* OMA */
    { "value",       NULL,                  0x01, 0x06 }, /* OMA */
    { "name",        "NAME",                0x01, 0x07 }, /* OMA */
    { "name",        "INTERNET",            0x01, 0x14 }, /* OMA */
    { "name",        "STARTPAGE",           0x01, 0x1c }, /* OMA */
    { "name",        "TO-NAPID",            0x01, 0x22 }, /* OMA */
    { "name",        "PORTNBR",             0x01, 0x23 }, /* OMA */
    { "name",        "SERVICE",             0x01, 0x24 }, /* OMA */
    { "name",        "AACCEPT",             0x01, 0x2e }, /* OMA */
    { "name",        "AAUTHDATA",           0x01, 0x2f }, /* OMA */
    { "name",        "AAUTHLEVEL",          0x01, 0x30 }, /* OMA */
    { "name",        "AAUTHNAME",           0x01, 0x31 }, /* OMA */
    { "name",        "AAUTHSECRET",         0x01, 0x32 }, /* OMA */
    { "name",        "AAUTHTYPE",           0x01, 0x33 }, /* OMA */
    { "name",        "ADDR",                0x01, 0x34 }, /* OMA */
    { "name",        "ADDRTYPE",            0x01, 0x35 }, /* OMA */
    { "name",        "APPID",               0x01, 0x36 }, /* OMA */
    { "name",        "APROTOCOL",           0x01, 0x37 }, /* OMA */
    { "name",        "PROVIDER-ID",         0x01, 0x38 }, /* OMA */
    { "name",        "TO-PROXY",            0x01, 0x39 }, /* OMA */
    { "name",        "URI",                 0x01, 0x3a }, /* OMA */
    { "name",        "RULE",                0x01, 0x3b }, /* OMA */
    
    { NULL,          NULL,                  0x00, 0x00 }
};


const WBXMLAttrValueEntry sv_prov10_attr_value_table[] = {
    /* ADDRTYPE */
    { "IPV4",                   0x00, 0x85 },
    { "IPV6",                   0x00, 0x86 },
    { "E164",                   0x00, 0x87 },
    { "ALPHA",                  0x00, 0x88 },
    { "APN",                    0x00, 0x89 },
    { "SCODE",                  0x00, 0x8a },
    { "TETRA-ITSI",             0x00, 0x8b },
    { "MAN",                    0x00, 0x8c },
    
    { "IPV6",                   0x01, 0x86 }, /* OMA */
    { "E164",                   0x01, 0x87 }, /* OMA */
    { "ALPHA",                  0x01, 0x88 }, /* OMA */
    { "APPSRV",                 0x01, 0x8d }, /* OMA */
    { "OBEX",                   0x01, 0x8e }, /* OMA */

    /* CALLTYPE */
    { "ANALOG-MODEM",           0x00, 0x90 },
    { "V.120",                  0x00, 0x91 },
    { "V.110",                  0x00, 0x92 },
    { "X.31",                   0x00, 0x93 },
    { "BIT-TRANSPARENT",        0x00, 0x94 },
    { "DIRECT-ASYNCHRONOUS-DATA-SERVICE",    0x00, 0x95 },

    /* AUTHTYPE/PXAUTH-TYPE */
    { "PAP",                    0x00, 0x9a },
    { "CHAP",                   0x00, 0x9b },
    { "HTTP-BASIC",             0x00, 0x9c },
    { "HTTP-DIGEST",            0x00, 0x9d },
    { "WTLS-SS",                0x00, 0x9e },
    { "MD5",                    0x00, 0x9f }, /* OMA */

    /* BEARER */
    { "GSM-USSD",               0x00, 0xa2 },
    { "GSM-SMS",                0x00, 0xa3 },
    { "ANSI-136-GUTS",          0x00, 0xa4 },
    { "IS-95-CDMA-SMS",         0x00, 0xa5 },
    { "IS-95-CDMA-CSD",         0x00, 0xa6 },
    { "IS-95-CDMA-PACKET",      0x00, 0xa7 },
    { "ANSI-136-CSD",           0x00, 0xa8 },
    { "ANSI-136-GPRS",          0x00, 0xa9 },
    { "GSM-CSD",                0x00, 0xaa },
    { "GSM-GPRS",               0x00, 0xab },
    { "AMPS-CDPD",              0x00, 0xac },
    { "PDC-CSD",                0x00, 0xad },
    { "PDC-PACKET",             0x00, 0xae },
    { "IDEN-SMS",               0x00, 0xaf },
    { "IDEN-CSD",               0x00, 0xb0 },
    { "IDEN-PACKET",            0x00, 0xb1 },
    { "FLEX/REFLEX",            0x00, 0xb2 },
    { "PHS-SMS",                0x00, 0xb3 },
    { "PHS-CSD",                0x00, 0xb4 },
    { "TRETRA-SDS",             0x00, 0xb5 },
    { "TRETRA-PACKET",          0x00, 0xb6 },
    { "ANSI-136-GHOST",         0x00, 0xb7 },
    { "MOBITEX-MPAK",           0x00, 0xb8 },
    { "CDMA2000-1X-SIMPLE-IP",  0x00, 0xb9 }, /* OMA */
    { "CDMA2000-1X-MOBILE-IP",  0x00, 0xba }, /* OMA */

    /* LINKSPEED */
    { "AUTOBAUDING",            0x00, 0xc5 },

    /* SERVICE */
    { "CL-WSP",                 0x00, 0xca },
    { "CO-WSP",                 0x00, 0xcb },
    { "CL-SEC-WSP",             0x00, 0xcc },
    { "CO-SEC-WSP",             0x00, 0xcd },
    { "CL-SEC-WTA",             0x00, 0xce },
    { "CO-SEC-WTA",             0x00, 0xcf },
    { "OTA-HTTP-TO",            0x00, 0xd0 }, /* OMA */
    { "OTA-HTTP-TLS-TO",        0x00, 0xd1 }, /* OMA */
    { "OTA-HTTP-PO",            0x00, 0xd2 }, /* OMA */
    { "OTA-HTTP-TLS-PO",        0x00, 0xd3 }, /* OMA */
    
    /* AAUTHTYPE */
#if defined( WBXML_SUPPORT_PROV_11 )
    
    { ",",                      0x01, 0x90 }, /* OMA */
    { "HTTP-",                  0x01, 0x91 }, /* OMA */
    { "BASIC",                  0x01, 0x92 }, /* OMA */
    { "DIGEST",                 0x01, 0x93 }, /* OMA */
    
#else

    { ",",                      0x01, 0x80 }, /* OMA */
    { "HTTP-",                  0x01, 0x81 }, /* OMA */
    { "BASIC",                  0x01, 0x82 }, /* OMA */
    { "DIGEST",                 0x01, 0x83 }, /* OMA */
    
#endif /* WBXML_SUPPORT_PROV_11 */
    
    /* AUTH-ENTITY */
    { "AAA",                    0x00, 0xe0 }, /* OMA */
    { "HA",                     0x00, 0xe1 }, /* OMA */

    { NULL,                     0x00, 0x00 }
};

#endif /* WBXML_SUPPORT_PROV */


#if defined( WBXML_SUPPORT_EMN )

/*************************************************
 *    Email Notification 1.0 ("OMA-Push-EMN-v1_0-20020830-C.PDF")
 */

const WBXMLTagEntry sv_emn10_tag_table[] = {
    { "emn",    0x00, 0x05 },
    { NULL,     0x00, 0x00 }
};

const WBXMLAttrEntry sv_emn10_attr_table[] = {
    { "timestamp",      NULL,           0x00, 0x05 },
    { "mailbox",        NULL,           0x00, 0x06 },
    { "mailbox",        "mailat:",      0x00, 0x07 },
    { "mailbox",        "pop://",       0x00, 0x08 },
    { "mailbox",        "imap://",      0x00, 0x09 },
    /* Do NOT change the order in this table please ! */
    { "mailbox",        "http://www.",  0x00, 0x0b },
    { "mailbox",        "http://",      0x00, 0x0a },
    { "mailbox",        "https://www.", 0x00, 0x0d },
    { "mailbox",        "https://",     0x00, 0x0c },    
    { NULL,             NULL,           0x00, 0x00 }
};

const WBXMLAttrValueEntry sv_emn10_attr_value_table[] = {
    { ".com",       0x00, 0x85 },
    { ".edu",       0x00, 0x86 },
    { ".net",       0x00, 0x87 },
    { ".org",       0x00, 0x88 },
    { NULL,         0x00, 0x00 }
};

#endif /* WBXML_SUPPORT_EMN */


#if defined( WBXML_SUPPORT_DRMREL )

/*************************************************
 *    Rights Expression Language Version 1.0 ("OMA-Download-DRMREL-v1_0-20020913-a.pdf")
 */
 
const WBXMLTagEntry sv_drmrel10_tag_table[] = {
    { "o-ex:rights",    0x00, 0x05 },
    { "o-ex:context",   0x00, 0x06 },
    { "o-dd:version",   0x00, 0x07 },
    { "o-dd:uid",       0x00, 0x08 },
    { "o-ex:agreement", 0x00, 0x09 },
    { "o-ex:asset",     0x00, 0x0A },
    { "ds:KeyInfo",     0x00, 0x0B },
    { "ds:KeyValue",    0x00, 0x0C },
    { "o-ex:permission",0x00, 0x0D },
    { "o-dd:play",      0x00, 0x0E },
    { "o-dd:display",   0x00, 0x0F },
    { "o-dd:execute",   0x00, 0x10 },
    { "o-dd:print",     0x00, 0x11 },
    { "o-ex:constraint",0x00, 0x12 },
    { "o-dd:count",     0x00, 0x13 },
    { "o-dd:datetime",  0x00, 0x14 },
    { "o-dd:start",     0x00, 0x15 },
    { "o-dd:end",       0x00, 0x16 },
    { "o-dd:interval",  0x00, 0x17 },
    { NULL,             0x00, 0x00 }
};

const WBXMLAttrEntry sv_drmrel10_attr_table[] = {
    { "xmlns:o-ex",     NULL,       0x00, 0x05 },
    { "xmlns:o-dd",     NULL,       0x00, 0x06 },
    { "xmlns:ds",       NULL,       0x00, 0x07 },
    { NULL,             NULL,       0x00, 0x00 }
};

const WBXMLAttrValueEntry sv_drmrel10_attr_value_table[] = {
    { "http://odrl.net/1.1/ODRL-EX",        0x00, 0x85 },
    { "http://odrl.net/1.1/ODRL-DD",        0x00, 0x86 },
    { "http://www.w3.org/2000/09/xmldsig#/",0x00, 0x87 },
    { NULL,                                 0x00, 0x00 }
};

#endif /* WBXML_SUPPORT_DRMREL */


#if defined( WBXML_SUPPORT_OTA_SETTINGS )

/********************************************************************
 *    Ericsson / Nokia OTA Settings ("OTA_settings_general_7_0.pdf")
 */
 
const WBXMLTagEntry sv_ota_settings_tag_table[] = {
    { "CHARACTERISTIC-LIST",        0x00, 0x05 },
    { "CHARACTERISTIC",             0x00, 0x06 },
    { "PARM",                       0x00, 0x07 },
    
    { NULL,                         0x00, 0x00 }
};

const WBXMLAttrEntry sv_ota_settings_attr_table[] = {
    /* Characteristic */
    { "TYPE",        "ADDRESS",             0x00, 0x06 },
    { "TYPE",        "URL",                 0x00, 0x07 },
    { "TYPE",        "NAME",                0x00, 0x08 },
    { "NAME",        NULL,                  0x00, 0x10 },
    { "VALUE",       NULL,                  0x00, 0x11 },
    { "NAME",        "BEARER",              0x00, 0x12 },
    { "NAME",        "PROXY",               0x00, 0x13 },
    { "NAME",        "PORT",                0x00, 0x14 },
    { "NAME",        "NAME",                0x00, 0x15 },
    { "NAME",        "PROXY_TYPE",          0x00, 0x16 },
    { "NAME",        "URL",                 0x00, 0x17 },
    { "NAME",        "PROXY_AUTHNAME",      0x00, 0x18 },
    { "NAME",        "PROXY_AUTHSECRET",    0x00, 0x19 },
    { "NAME",        "SMS_SMSC_ADDRESS",    0x00, 0x1A },
    { "NAME",        "USSD_SERVICE_CODE",   0x00, 0x1B },
    { "NAME",        "GPRS_ACCESSPOINTNAME",0x00, 0x1C },
    { "NAME",        "PPP_LOGINTYPE",       0x00, 0x1D },
    { "NAME",        "PROXY_LOGINTYPE",     0x00, 0x1E },
    { "NAME",        "CSD_DIALSTRING",      0x00, 0x21 },
    { "NAME",        "CSD_CALLTYPE",        0x00, 0x28 },
    { "NAME",        "CSD_CALLSPEED",       0x00, 0x29 },
    { "NAME",        "PPP_AUTHTYPE",        0x00, 0x22 },
    { "NAME",        "PPP_AUTHNAME",        0x00, 0x23 },
    { "NAME",        "PPP_AUTHSECRET",      0x00, 0x24 },
    { "VALUE",       "GSM/CSD",             0x00, 0x45 },
    { "VALUE",       "GSM/SMS",             0x00, 0x46 },
    { "VALUE",       "GSM/USSD",            0x00, 0x47 },
    { "VALUE",       "IS-136/CSD",          0x00, 0x48 },
    { "VALUE",       "GPRS",                0x00, 0x49 },
    { "VALUE",       "9200",                0x00, 0x60 },
    { "VALUE",       "9201",                0x00, 0x61 },
    { "VALUE",       "9202",                0x00, 0x62 },
    { "VALUE",       "9203",                0x00, 0x63 },
    { "VALUE",       "AUTOMATIC",           0x00, 0x64 },
    { "VALUE",       "MANUAL",              0x00, 0x65 },
    { "VALUE",       "AUTO",                0x00, 0x6A },
    { "VALUE",       "9600",                0x00, 0x6B },
    { "VALUE",       "14400",               0x00, 0x6C },
    { "VALUE",       "19200",               0x00, 0x6D },
    { "VALUE",       "28800",               0x00, 0x6E },
    { "VALUE",       "38400",               0x00, 0x6F },
    { "VALUE",       "PAP",                 0x00, 0x70 },
    { "VALUE",       "CHAP",                0x00, 0x71 },
    { "VALUE",       "ANALOGUE",            0x00, 0x72 },
    { "VALUE",       "ISDN",                0x00, 0x73 },
    { "VALUE",       "43200",               0x00, 0x74 },
    { "VALUE",       "57600",               0x00, 0x75 },
    { "VALUE",       "MSISDN_NO",           0x00, 0x76 },
    { "VALUE",       "IPV4",                0x00, 0x77 },
    { "VALUE",       "MS_CHAP",             0x00, 0x78 },
    { "TYPE",        "MMSURL",              0x00, 0x7C },
    { "TYPE",        "ID",                  0x00, 0x7D },
    { "NAME",        "ISP_NAME",            0x00, 0x7E },
    { "TYPE",        "BOOKMARK",            0x00, 0x7F },
    
    { NULL,          NULL,                  0x00, 0x00 }
};

#endif /* WBXML_SUPPORT_OTA_SETTINGS */


#if defined( WBXML_SUPPORT_SYNCML )

const WBXMLNameSpaceEntry sv_syncml_syncml10_ns_table[] = {
    { "SYNCML:SYNCML1.0",   0x00 },     /**< Code Page 0: SYNCML1.0 */
    { "syncml:metinf",      0x01 },     /**< Code Page 1: metinf */
    { NULL,                 0x00 }
};


const WBXMLNameSpaceEntry sv_syncml_syncml11_ns_table[] = {
    { "SYNCML:SYNCML1.1",   0x00 },     /**< Code Page 0: SYNCML1.1 */
    { "syncml:metinf",      0x01 },     /**< Code Page 1: metinf */
    { NULL,                 0x00 }
};


const WBXMLNameSpaceEntry sv_syncml_syncml12_ns_table[] = {
    { "SYNCML:SYNCML1.2",   0x00 },     /**< Code Page 0: SYNCML1.2 */
    { "syncml:metinf",      0x01 },     /**< Code Page 1: metinf */
    { NULL,                 0x00 }
};


/******************************************************
 *    SyncML 1.1 ("syncml_represent_v11_20020215.pdf")
 */

const WBXMLTagEntry sv_syncml_syncml11_tag_table[] = {
    /* Code Page 0: SyncML */
    { "Add",            0x00, 0x05 },
    { "Alert",          0x00, 0x06 },
    { "Archive",        0x00, 0x07 },
    { "Atomic",         0x00, 0x08 },
    { "Chal",           0x00, 0x09 },
    { "Cmd",            0x00, 0x0a },
    { "CmdID",          0x00, 0x0b },
    { "CmdRef",         0x00, 0x0c },
    { "Copy",           0x00, 0x0d },
    { "Cred",           0x00, 0x0e },
    { "Data",           0x00, 0x0f },
    { "Delete",         0x00, 0x10 },
    { "Exec",           0x00, 0x11 },
    { "Final",          0x00, 0x12 },
    { "Get",            0x00, 0x13 },
    { "Item",           0x00, 0x14 },
    { "Lang",           0x00, 0x15 },
    { "LocName",        0x00, 0x16 },
    { "LocURI",         0x00, 0x17 },
    { "Map",            0x00, 0x18 },
    { "MapItem",        0x00, 0x19 },
    { "Meta",           0x00, 0x1a },
    { "MsgID",          0x00, 0x1b },
    { "MsgRef",         0x00, 0x1c },
    { "NoResp",         0x00, 0x1d },
    { "NoResults",      0x00, 0x1e },
    { "Put",            0x00, 0x1f },
    { "Replace",        0x00, 0x20 },
    { "RespURI",        0x00, 0x21 },
    { "Results",        0x00, 0x22 },
    { "Search",         0x00, 0x23 },
    { "Sequence",       0x00, 0x24 },
    { "SessionID",      0x00, 0x25 },
    { "SftDel",         0x00, 0x26 },
    { "Source",         0x00, 0x27 },
    { "SourceRef",      0x00, 0x28 },
    { "Status",         0x00, 0x29 },
    { "Sync",           0x00, 0x2a },
    { "SyncBody",       0x00, 0x2b },
    { "SyncHdr",        0x00, 0x2c },
    { "SyncML",         0x00, 0x2d },
    { "Target",         0x00, 0x2e },
    { "TargetRef",      0x00, 0x2f },
    { "Reserved for future use",    0x00, 0x30 },
    { "VerDTD",         0x00, 0x31 },
    { "VerProto",       0x00, 0x32 },
    { "NumberOfChanges",0x00, 0x33 },
    { "MoreData",       0x00, 0x34 },

    /* SourceParent is officially only specified for SyncML 1.2.
     * Nevertheless Nokia uses this tag during the synchronization
     * of SMS. So this is a proprietary extension to avoid that
     * there is a tag called "unknown".
     */
    { "SourceParent",   0x00, 0x39 },

    /* Code Page 1: MetInf11 */
    { "Anchor",         0x01, 0x05 },
    { "EMI",            0x01, 0x06 },
    { "Format",         0x01, 0x07 },
    { "FreeID",         0x01, 0x08 },
    { "FreeMem",        0x01, 0x09 },
    { "Last",           0x01, 0x0a },
    { "Mark",           0x01, 0x0b },
    { "MaxMsgSize",     0x01, 0x0c },
    { "Mem",            0x01, 0x0d },
    { "MetInf",         0x01, 0x0e },
    { "Next",           0x01, 0x0f },
    { "NextNonce",      0x01, 0x10 },
    { "SharedMem",      0x01, 0x11 },
    { "Size",           0x01, 0x12 },
    { "Type",           0x01, 0x13 },
    { "Version",        0x01, 0x14 },
    { "MaxObjSize",     0x01, 0x15 },
    { NULL,             0x00, 0x00 }
};


/*********************************************************
 *    SyncML DevInf 1.1 ("syncml_devinf_v11_20020215.pdf")
 */

const WBXMLTagEntry sv_syncml_devinf11_tag_table[] = {
    { "CTCap",          0x00, 0x05 },
    { "CTType",         0x00, 0x06 },
    { "DataStore",      0x00, 0x07 },
    { "DataType",       0x00, 0x08 },
    { "DevID",          0x00, 0x09 },
    { "DevInf",         0x00, 0x0a },
    { "DevTyp",         0x00, 0x0b },
    { "DisplayName",    0x00, 0x0c },
    { "DSMem",          0x00, 0x0d },
    { "Ext",            0x00, 0x0e },
    { "FwV",            0x00, 0x0f },
    { "HwV",            0x00, 0x10 },
    { "Man",            0x00, 0x11 },
    { "MaxGUIDSize",    0x00, 0x12 },
    { "MaxID",          0x00, 0x13 },
    { "MaxMem",         0x00, 0x14 },
    { "Mod",            0x00, 0x15 },
    { "OEM",            0x00, 0x16 },
    { "ParamName",      0x00, 0x17 },
    { "PropName",       0x00, 0x18 },
    { "Rx",             0x00, 0x19 },
    { "Rx-Pref",        0x00, 0x1a },
    { "SharedMem",      0x00, 0x1b },
    { "Size",           0x00, 0x1c },
    { "SourceRef",      0x00, 0x1d },
    { "SwV",            0x00, 0x1e },
    { "SyncCap",        0x00, 0x1f },
    { "SyncType",       0x00, 0x20 },
    { "Tx",             0x00, 0x21 },
    { "Tx-Pref",        0x00, 0x22 },
    { "ValEnum",        0x00, 0x23 },
    { "VerCT",          0x00, 0x24 },
    { "VerDTD",         0x00, 0x25 },
    { "XNam",           0x00, 0x26 },
    { "XVal",           0x00, 0x27 },
    { "UTC",            0x00, 0x28 },
    { "SupportNumberOfChanges", 0x00, 0x29 },
    { "SupportLargeObjs",       0x00, 0x2a },
    { NULL,                0x00, 0x00 }
};


const WBXMLNameSpaceEntry sv_syncml_devinf11_ns_table[] = {
    { "syncml:devinf",  0x00 },     /**< Code Page 0: devinf */
    { NULL,             0x00 }
};


/*********************************************************
 *    SyncML MetInf 1.1 ("syncml_metinf_v11_20020215.pdf")
 */

const WBXMLTagEntry sv_syncml_metinf11_tag_table[] = {
    { "Anchor",         0x01, 0x05 },
    { "EMI",            0x01, 0x06 },
    { "Format",         0x01, 0x07 },
    { "FreeID",         0x01, 0x08 },
    { "FreeMem",        0x01, 0x09 },
    { "Last",           0x01, 0x0a },
    { "Mark",           0x01, 0x0b },
    { "MaxMsgSize",     0x01, 0x0c },
    { "Mem",            0x01, 0x0d },
    { "MetInf",         0x01, 0x0e },
    { "Next",           0x01, 0x0f },
    { "NextNonce",      0x01, 0x10 },
    { "SharedMem",      0x01, 0x11 },
    { "Size",           0x01, 0x12 },
    { "Type",           0x01, 0x13 },
    { "Version",        0x01, 0x14 },
    { "MaxObjSize",     0x01, 0x15 },
    { NULL,             0x00, 0x00 }
};


/******************************************************
 *    SyncML 1.2 ("OMA-TS-SyncML_RepPro-V1_2-20050509-C.pdf")
 */

const WBXMLTagEntry sv_syncml_syncml12_tag_table[] = {
    /* Code Page 0: SyncML */
    { "Add",            0x00, 0x05 },
    { "Alert",          0x00, 0x06 },
    { "Archive",        0x00, 0x07 },
    { "Atomic",         0x00, 0x08 },
    { "Chal",           0x00, 0x09 },
    { "Cmd",            0x00, 0x0a },
    { "CmdID",          0x00, 0x0b },
    { "CmdRef",         0x00, 0x0c },
    { "Copy",           0x00, 0x0d },
    { "Cred",           0x00, 0x0e },
    { "Data",           0x00, 0x0f },
    { "Delete",         0x00, 0x10 },
    { "Exec",           0x00, 0x11 },
    { "Final",          0x00, 0x12 },
    { "Get",            0x00, 0x13 },
    { "Item",           0x00, 0x14 },
    { "Lang",           0x00, 0x15 },
    { "LocName",        0x00, 0x16 },
    { "LocURI",         0x00, 0x17 },
    { "Map",            0x00, 0x18 },
    { "MapItem",        0x00, 0x19 },
    { "Meta",           0x00, 0x1a },
    { "MsgID",          0x00, 0x1b },
    { "MsgRef",         0x00, 0x1c },
    { "NoResp",         0x00, 0x1d },
    { "NoResults",      0x00, 0x1e },
    { "Put",            0x00, 0x1f },
    { "Replace",        0x00, 0x20 },
    { "RespURI",        0x00, 0x21 },
    { "Results",        0x00, 0x22 },
    { "Search",         0x00, 0x23 },
    { "Sequence",       0x00, 0x24 },
    { "SessionID",      0x00, 0x25 },
    { "SftDel",         0x00, 0x26 },
    { "Source",         0x00, 0x27 },
    { "SourceRef",      0x00, 0x28 },
    { "Status",         0x00, 0x29 },
    { "Sync",           0x00, 0x2a },
    { "SyncBody",       0x00, 0x2b },
    { "SyncHdr",        0x00, 0x2c },
    { "SyncML",         0x00, 0x2d },
    { "Target",         0x00, 0x2e },
    { "TargetRef",      0x00, 0x2f },
    { "Reserved for future use",    0x00, 0x30 },
    { "VerDTD",         0x00, 0x31 },
    { "VerProto",       0x00, 0x32 },
    { "NumberOfChanges",0x00, 0x33 },
    { "MoreData",       0x00, 0x34 },
    { "Field",          0x00, 0x35 },
    { "Filter",         0x00, 0x36 },
    { "Record",         0x00, 0x37 },
    { "FilterType",     0x00, 0x38 },
    { "SourceParent",   0x00, 0x39 },
    { "TargetParent",   0x00, 0x3a },
    { "Move",           0x00, 0x3b },
    { "Correlator",     0x00, 0x3c },

    /* Code Page 1: MetInf */
    { "Anchor",         0x01, 0x05 },
    { "EMI",            0x01, 0x06 },
    { "Format",         0x01, 0x07 },
    { "FreeID",         0x01, 0x08 },
    { "FreeMem",        0x01, 0x09 },
    { "Last",           0x01, 0x0a },
    { "Mark",           0x01, 0x0b },
    { "MaxMsgSize",     0x01, 0x0c },
    { "Mem",            0x01, 0x0d },
    { "MetInf",         0x01, 0x0e },
    { "Next",           0x01, 0x0f },
    { "NextNonce",      0x01, 0x10 },
    { "SharedMem",      0x01, 0x11 },
    { "Size",           0x01, 0x12 },
    { "Type",           0x01, 0x13 },
    { "Version",        0x01, 0x14 },
    { "MaxObjSize",     0x01, 0x15 },
    { "FieldLevel",     0x01, 0x16 },
    { NULL,             0x00, 0x00 }
};


/*********************************************************
 *    SyncML DevInf 1.2 ("OMA-TS-DS_DevInf-V1_2-20060710-A.pdf")
 */

const WBXMLTagEntry sv_syncml_devinf12_tag_table[] = {
    { "CTCap",          0x00, 0x05 },
    { "CTType",         0x00, 0x06 },
    { "DataStore",      0x00, 0x07 },
    { "DataType",       0x00, 0x08 },
    { "DevID",          0x00, 0x09 },
    { "DevInf",         0x00, 0x0a },
    { "DevTyp",         0x00, 0x0b },
    { "DisplayName",    0x00, 0x0c },
    { "DSMem",          0x00, 0x0d },
    { "Ext",            0x00, 0x0e },
    { "FwV",            0x00, 0x0f },
    { "HwV",            0x00, 0x10 },
    { "Man",            0x00, 0x11 },
    { "MaxGUIDSize",    0x00, 0x12 },
    { "MaxID",          0x00, 0x13 },
    { "MaxMem",         0x00, 0x14 },
    { "Mod",            0x00, 0x15 },
    { "OEM",            0x00, 0x16 },
    { "ParamName",      0x00, 0x17 },
    { "PropName",       0x00, 0x18 },
    { "Rx",             0x00, 0x19 },
    { "Rx-Pref",        0x00, 0x1a },
    { "SharedMem",      0x00, 0x1b },
    { "MaxSize",        0x00, 0x1c },
    { "SourceRef",      0x00, 0x1d },
    { "SwV",            0x00, 0x1e },
    { "SyncCap",        0x00, 0x1f },
    { "SyncType",       0x00, 0x20 },
    { "Tx",             0x00, 0x21 },
    { "Tx-Pref",        0x00, 0x22 },
    { "ValEnum",        0x00, 0x23 },
    { "VerCT",          0x00, 0x24 },
    { "VerDTD",         0x00, 0x25 },
    { "XNam",           0x00, 0x26 },
    { "XVal",           0x00, 0x27 },
    { "UTC",            0x00, 0x28 },
    { "SupportNumberOfChanges", 0x00, 0x29 },
    { "SupportLargeObjs",       0x00, 0x2a },
    { "Property",       0x00, 0x2b },
    { "PropParam",      0x00, 0x2c },
    { "MaxOccur",       0x00, 0x2d },
    { "NoTruncate",     0x00, 0x2e },
    { "Filter-Rx",      0x00, 0x30 },
    { "FilterCap",      0x00, 0x31 },
    { "FilterKeyword",  0x00, 0x32 },
    { "FieldLevel",     0x00, 0x33 },
    { "SupportHierarchicalSync", 0x00, 0x34 },
    { NULL,             0x00, 0x00 }
};


const WBXMLNameSpaceEntry sv_syncml_devinf12_ns_table[] = {
    { "syncml:devinf",  0x00 },     /**< Code Page 0: devinf */
    { NULL,             0x00 }
};


/*********************************************************
 *    SyncML MetInf 1.2 ("OMA-TS-SyncML_MetaInfo-V1_2-20050509-C.pdf")
 */

const WBXMLTagEntry sv_syncml_metinf12_tag_table[] = {
    { "Anchor",         0x01, 0x05 },
    { "EMI",            0x01, 0x06 },
    { "Format",         0x01, 0x07 },
    { "FreeID",         0x01, 0x08 },
    { "FreeMem",        0x01, 0x09 },
    { "Last",           0x01, 0x0a },
    { "Mark",           0x01, 0x0b },
    { "MaxMsgSize",     0x01, 0x0c },
    { "Mem",            0x01, 0x0d },
    { "MetInf",         0x01, 0x0e },
    { "Next",           0x01, 0x0f },
    { "NextNonce",      0x01, 0x10 },
    { "SharedMem",      0x01, 0x11 },
    { "Size",           0x01, 0x12 },
    { "Type",           0x01, 0x13 },
    { "Version",        0x01, 0x14 },
    { "MaxObjSize",     0x01, 0x15 },
    { "FieldLevel",     0x01, 0x16 },
    { NULL,             0x00, 0x00 }
};

/*********************************************************
 *    SyncML DM DDF 1.2 ("OMA-TS-DM_TND-V1_2_1-20080617-A.pdf")
 */

const WBXMLTagEntry sv_syncml_dmddf12_tag_table[] = {
    { "AccessType",     0x02, 0x05 },
    { "ACL",            0x02, 0x06 },
    { "Add",            0x02, 0x07 },
    { "b64",            0x02, 0x08 },
    { "bin",            0x02, 0x09 },
    { "bool",           0x02, 0x0A },
    { "chr",            0x02, 0x0B },
    { "CaseSense",      0x02, 0x0C },
    { "CIS",            0x02, 0x0D },
    { "Copy",           0x02, 0x0E },
    { "CS",             0x02, 0x0F },
    { "date",           0x02, 0x10 },
    { "DDFName",        0x02, 0x11 },
    { "DefaultValue",   0x02, 0x12 },
    { "Delete",         0x02, 0x13 },
    { "Description",    0x02, 0x14 },
    { "DFFormat",       0x02, 0x15 },
    { "DFProperties",   0x02, 0x16 },
    { "DFTitle",        0x02, 0x17 },
    { "DFType",         0x02, 0x18 },
    { "Dynamic",        0x02, 0x19 },
    { "Exec",           0x02, 0x1A },
    { "float",          0x02, 0x1B },
    { "Format",         0x02, 0x1C },
    { "Get",            0x02, 0x1D },
    { "int",            0x02, 0x1E },
    { "Man",            0x02, 0x1F },
    { "MgmtTree",       0x02, 0x20 },
    { "MIME",           0x02, 0x21 },
    { "Mod",            0x02, 0x22 },
    { "Name",           0x02, 0x23 },
    { "Node",           0x02, 0x24 },
    { "node",           0x02, 0x25 },
    { "NodeName",       0x02, 0x26 },
    { "null",           0x02, 0x27 },
    { "Occurrence",     0x02, 0x28 },
    { "One",            0x02, 0x29 },
    { "OneOrMore",      0x02, 0x2A },
    { "OneOrN",         0x02, 0x2B },
    { "Path",           0x02, 0x2C },
    { "Permanent",      0x02, 0x2D },
    { "Replace",        0x02, 0x2E },
    { "RTProperties",   0x02, 0x2F },
    { "Scope",          0x02, 0x30 },
    { "Size",           0x02, 0x31 },
    { "time",           0x02, 0x32 },
    { "Title",          0x02, 0x33 },
    { "TStamp",         0x02, 0x34 },
    { "Type",           0x02, 0x35 },
    { "Value",          0x02, 0x36 },
    { "VerDTD",         0x02, 0x37 },
    { "VerNo",          0x02, 0x38 },
    { "xml",            0x02, 0x39 },
    { "ZeroOrMore",     0x02, 0x3A },
    { "ZeroOrN",        0x02, 0x3B },
    { "ZeroOrOne",      0x02, 0x3C },
    { NULL,             0x00, 0x00 }
};

const WBXMLNameSpaceEntry sv_syncml_dmddf12_ns_table[] = {
    { "syncml:dmddf1.2", 0x02 },     /**< Code Page 2: OMA DM DDF */
    { NULL,              0x00 }
};

#endif /* WBXML_SUPPORT_SYNCML */


#if defined( WBXML_SUPPORT_WV )

/*****************************************************************************
 *    Wireless Village CSP 1.1 ("OMA-WV-CSP-V1_1-20021001-A.pdf")
 *    Wireless Village CSP 1.2 ("OMA-IMPS-WV-CSP_WBXML-V1_2-20040522-C.pdf")
 */

const WBXMLTagEntry sv_wv_csp_tag_table[] = {
    /* Common ... continue on Page 0x09 */
    { "Acceptance",     0x00, 0x05 },
    { "AddList",        0x00, 0x06 },
    { "AddNickList",    0x00, 0x07 },
    { "ClientID",       0x00, 0x0A },
    { "Code",           0x00, 0x0B },
    { "ContactList",    0x00, 0x0C },
    { "ContentData",    0x00, 0x0D },
    { "ContentEncoding",0x00, 0x0E },
    { "ContentSize",    0x00, 0x0F },
    { "ContentType",    0x00, 0x10 },
    { "DateTime",       0x00, 0x11 },
    { "Description",    0x00, 0x12 },
    { "DetailedResult", 0x00, 0x13 },
    { "EntityList",     0x00, 0x14 },
    { "Group",          0x00, 0x15 },
    { "GroupID",        0x00, 0x16 },
    { "GroupList",      0x00, 0x17 },
    { "InUse",          0x00, 0x18 },
    { "Logo",           0x00, 0x19 },
    { "MessageCount",   0x00, 0x1A },
    { "MessageID",      0x00, 0x1B },
    { "MessageURI",     0x00, 0x1C },
    { "MSISDN",         0x00, 0x1D },
    { "Name",           0x00, 0x1E },
    { "NickList",       0x00, 0x1F },
    { "NickName",       0x00, 0x20 },
    { "Poll",           0x00, 0x21 },
    { "Presence",       0x00, 0x22 },
    { "PresenceSubList",0x00, 0x23 },
    { "PresenceValue",  0x00, 0x24 },
    { "Property",       0x00, 0x25 },
    { "Qualifier",      0x00, 0x26 },
    { "Recipient",      0x00, 0x27 },
    { "RemoveList",     0x00, 0x28 },
    { "RemoveNickList", 0x00, 0x29 },
    { "Result",         0x00, 0x2A },
    { "ScreenName",     0x00, 0x2B },
    { "Sender",         0x00, 0x2C },
    { "Session",        0x00, 0x2D },
    { "SessionDescriptor",      0x00, 0x2E },
    { "SessionID",              0x00, 0x2F },
    { "SessionType",            0x00, 0x30 },
    { "SName",                  0x00, 0x08 },
    { "Status",                 0x00, 0x31 },
    { "Transaction",            0x00, 0x32 },
    { "TransactionContent",     0x00, 0x33 },
    { "TransactionDescriptor",  0x00, 0x34 },
    { "TransactionID",  0x00, 0x35 },
    { "TransactionMode",0x00, 0x36 },
    { "URL",            0x00, 0x37 },
    { "URLList",        0x00, 0x38 },
    { "User",           0x00, 0x39 },
    { "UserID",         0x00, 0x3A },
    { "UserList",       0x00, 0x3B },
    { "Validity",       0x00, 0x3C },
    { "Value",          0x00, 0x3D },
    { "WV-CSP-Message", 0x00, 0x09 },
    
    /* Access ... continue on Page 0x0A */
    { "AgreedCapabilityList",       0x01, 0x3A }, /* WV 1.2 */
    { "AllFunctions",               0x01, 0x05 },
    { "AllFunctionsRequest",        0x01, 0x06 },
    { "CancelInvite-Request",       0x01, 0x07 },
    { "CancelInviteUser-Request",   0x01, 0x08 },
    { "Capability",                 0x01, 0x09 },
    { "CapabilityList",             0x01, 0x0A },
    { "CapabilityRequest",          0x01, 0x0B },
    { "ClientCapability-Request",   0x01, 0x0C },
    { "ClientCapability-Response",  0x01, 0x0D },
    { "CompletionFlag",         0x01, 0x34 },
    { "DigestBytes",            0x01, 0x0E },
    { "DigestSchema",           0x01, 0x0F },
    { "Disconnect",             0x01, 0x10 },
    { "Extended-Request",       0x01, 0x38 }, /* WV 1.2 */
    { "Extended-Response",      0x01, 0x39 }, /* WV 1.2 */
    { "Extended-Data",          0x01, 0x3B }, /* WV 1.2 */
    { "Functions",              0x01, 0x11 },
    { "GetSPInfo-Request",      0x01, 0x12 },
    { "GetSPInfo-Response",     0x01, 0x13 },
    { "InviteID",               0x01, 0x14 },
    { "InviteNote",             0x01, 0x15 },
    { "Invite-Request",         0x01, 0x16 },
    { "Invite-Response",        0x01, 0x17 },
    { "InviteType",             0x01, 0x18 },
    { "InviteUser-Request",     0x01, 0x19 },
    { "InviteUser-Response",    0x01, 0x1A },
    { "KeepAlive-Request",      0x01, 0x1B },
    { "KeepAlive-Response",     0x01, 0x29 },
    { "KeepAliveTime",          0x01, 0x1C },
    { "Login-Request",          0x01, 0x1D },
    { "Login-Response",         0x01, 0x1E },
    { "Logout-Request",         0x01, 0x1F },
    { "Nonce",                  0x01, 0x20 },
    { "OtherServer",            0x01, 0x3C }, /* WV 1.2 */
    { "Password",               0x01, 0x21 },
    { "Polling-Request",        0x01, 0x22 },
    { "PresenceAttributeNSName",0x01, 0x3D }, /* WV 1.2 */
    { "ReceiveList",            0x01, 0x36 }, /* WV 1.2 */
    { "ResponseNote",           0x01, 0x23 },
    { "SearchElement",          0x01, 0x24 },
    { "SearchFindings",         0x01, 0x25 },
    { "SearchID",               0x01, 0x26 },
    { "SearchIndex",            0x01, 0x27 },
    { "SearchLimit",            0x01, 0x28 },
    { "SearchPairList",         0x01, 0x2A },
    { "Search-Request",         0x01, 0x2B },
    { "Search-Response",        0x01, 0x2C },
    { "SearchResult",           0x01, 0x2D },
    { "SearchString",           0x01, 0x33 },
    { "Service-Request",        0x01, 0x2E },
    { "Service-Response",       0x01, 0x2F },
    { "SessionCookie",          0x01, 0x30 },
    { "SessionNSName",          0x01, 0x3E }, /* WV 1.2 */
    { "StopSearch-Request",     0x01, 0x31 },
    { "TimeToLive",             0x01, 0x32 },
    { "TransactionNSName",      0x01, 0x3F }, /* WV 1.2 */
    { "VerifyID-Request",       0x01, 0x37 }, /* WV 1.2 */
        
    /* Service ... continue on Page 0x08 */
    { "ADDGM",          0x02, 0x05 },
    { "AttListFunc",    0x02, 0x06 },
    { "BLENT",          0x02, 0x07 },
    { "CAAUT",          0x02, 0x08 },
    { "CAINV",          0x02, 0x09 },
    { "CALI",           0x02, 0x0A },
    { "CCLI",           0x02, 0x0B },
    { "ContListFunc",   0x02, 0x0C },
    { "CREAG",          0x02, 0x0D },
    { "DALI",           0x02, 0x0E },
    { "DCLI",           0x02, 0x0F },
    { "DELGR",          0x02, 0x10 },
    { "FundamentalFeat",0x02, 0x11 },
    { "FWMSG",          0x02, 0x12 },
    { "GALS",           0x02, 0x13 },
    { "GCLI",           0x02, 0x14 },
    { "GETGM",          0x02, 0x15 },
    { "GETGP",          0x02, 0x16 },
    { "GETLM",          0x02, 0x17 },
    { "GETM",           0x02, 0x18 },
    { "GETPR",          0x02, 0x19 },
    { "GETSPI",         0x02, 0x1A },
    { "GETWL",          0x02, 0x1B },
    { "GLBLU",          0x02, 0x1C },
    { "GRCHN",          0x02, 0x1D },
    { "GroupAuthFunc",  0x02, 0x1E },
    { "GroupFeat",      0x02, 0x1F },
    { "GroupMgmtFunc",  0x02, 0x20 },
    { "GroupUseFunc",   0x02, 0x21 },
    { "IMAuthFunc",     0x02, 0x22 },
    { "IMFeat",         0x02, 0x23 },
    { "IMReceiveFunc",  0x02, 0x24 },
    { "IMSendFunc",     0x02, 0x25 },
    { "INVIT",          0x02, 0x26 },
    { "InviteFunc",     0x02, 0x27 },
    { "MBRAC",          0x02, 0x28 },
    { "MCLS",           0x02, 0x29 },
    { "MF",             0x02, 0x3D }, /* WV 1.2 */
    { "MG",             0x02, 0x3E }, /* WV 1.2 */
    { "MM",             0x02, 0x3F }, /* WV 1.2 */
    { "MDELIV",         0x02, 0x2A },
    { "NEWM",           0x02, 0x2B },
    { "NOTIF",          0x02, 0x2C },
    { "PresenceAuthFunc",   0x02, 0x2D },
    { "PresenceDeliverFunc",0x02, 0x2E },
    { "PresenceFeat",       0x02, 0x2F },
    { "REACT",          0x02, 0x30 },
    { "REJCM",          0x02, 0x31 },
    { "REJEC",          0x02, 0x32 },
    { "RMVGM",          0x02, 0x33 },
    { "SearchFunc",     0x02, 0x34 },
    { "ServiceFunc",    0x02, 0x35 },
    { "SETD",           0x02, 0x36 },
    { "SETGP",          0x02, 0x37 },
    { "SRCH",           0x02, 0x38 },
    { "STSRC",          0x02, 0x39 },
    { "SUBGCN",         0x02, 0x3A },
    { "UPDPR",          0x02, 0x3B },
    { "WVCSPFeat",      0x02, 0x3C },
    
    /* Client Capability */
    { "AcceptedCharset",            0x03, 0x05 },
    { "AcceptedContentLength",      0x03, 0x06 },
    { "AcceptedContentType",        0x03, 0x07 },
    { "AcceptedTransferEncoding",   0x03, 0x08 },
    { "AnyContent",                 0x03, 0x09 },
    { "DefaultLanguage",            0x03, 0x0A },
    { "InitialDeliveryMethod",      0x03, 0x0B },
    { "MultiTrans",                 0x03, 0x0C },
    { "ParserSize",                 0x03, 0x0D },
    { "ServerPollMin",              0x03, 0x0E },
    { "SupportedBearer",            0x03, 0x0F },
    { "SupportedCIRMethod",         0x03, 0x10 },
    { "TCPAddress",                 0x03, 0x11 },
    { "TCPPort",                    0x03, 0x12 },
    { "UDPPort",                    0x03, 0x13 },    
    
    /* Presence Primitive */
    { "Auto-Subscribe",                 0x04, 0x1E }, /* WV 1.2 */
    { "CancelAuth-Request",             0x04, 0x05 },
    { "ContactListProperties",          0x04, 0x06 },
    { "CreateAttributeList-Request",    0x04, 0x07 },
    { "CreateList-Request",             0x04, 0x08 },
    { "DefaultAttributeList",           0x04, 0x09 },
    { "DefaultContactList",             0x04, 0x0A },
    { "DefaultList",                    0x04, 0x0B },
    { "DeleteAttributeList-Request",    0x04, 0x0C },
    { "DeleteList-Request",             0x04, 0x0D },
    { "GetAttributeList-Request",       0x04, 0x0E },
    { "GetAttributeList-Response",      0x04, 0x0F },
    { "GetList-Request",                0x04, 0x10 },
    { "GetList-Response",               0x04, 0x11 },
    { "GetPresence-Request",            0x04, 0x12 },
    { "GetPresence-Response",           0x04, 0x13 },
    { "GetReactiveAuthStatus-Request",  0x04, 0x1F }, /* WV 1.2 */
    { "GetReactiveAuthStatus-Response", 0x04, 0x20 }, /* WV 1.2 */
    { "GetWatcherList-Request",         0x04, 0x14 },
    { "GetWatcherList-Response",        0x04, 0x15 },
    { "ListManage-Request",             0x04, 0x16 },
    { "ListManage-Response",            0x04, 0x17 },
    { "PresenceAuth-Request",           0x04, 0x19 },
    { "PresenceAuth-User",              0x04, 0x1A },
    { "PresenceNotification-Request",   0x04, 0x1B },
    { "SubscribePresence-Request",      0x04, 0x1D },
    { "UnsubscribePresence-Request",    0x04, 0x18 },
    { "UpdatePresence-Request",         0x04, 0x1C },
    
    /* Presence Attribute */
    { "Accuracy",           0x05, 0x05 },
    { "Address",            0x05, 0x06 },
    { "AddrPref",           0x05, 0x07 },
    { "Alias",              0x05, 0x08 },
    { "Altitude",           0x05, 0x09 },
    { "Building",           0x05, 0x0A },
    { "Caddr",              0x05, 0x0B },
    { "Cap",                0x05, 0x2F },
    { "City",               0x05, 0x0C },
    { "ClientInfo",         0x05, 0x0D },
    { "ClientProducer",     0x05, 0x0E },
    { "ClientType",         0x05, 0x0F },
    { "ClientVersion",      0x05, 0x10 },
    { "Cname",              0x05, 0x30 },
    { "CommC",              0x05, 0x11 },
    { "CommCap",            0x05, 0x12 },
    { "Contact",            0x05, 0x31 },
    { "ContactInfo",        0x05, 0x13 },
    { "ContainedvCard",     0x05, 0x14 },
                                          /* WV 1.2: removed in last version */
    { "Country",            0x05, 0x15 },
    { "Cpriority",          0x05, 0x32 },
    { "Crossing1",          0x05, 0x16 },
    { "Crossing2",          0x05, 0x17 },
    { "Cstatus",            0x05, 0x33 },
    { "DevManufacturer",    0x05, 0x18 },
    { "DirectContent",      0x05, 0x19 },
    { "FreeTextLocation",   0x05, 0x1A },
    { "GeoLocation",        0x05, 0x1B },
    { "Inf_link",           0x05, 0x37 }, /* WV 1.2 */
    { "InfoLink",           0x05, 0x38 }, /* WV 1.2 */
    { "Language",           0x05, 0x1C },
    { "Latitude",           0x05, 0x1D },
    { "Link",               0x05, 0x39 }, /* WV 1.2 */
    { "Longitude",          0x05, 0x1E },
    { "Model",              0x05, 0x1F },
    { "NamedArea",          0x05, 0x20 },    
    { "Note",               0x05, 0x34 }, /* WV 1.2 */
    { "OnlineStatus",       0x05, 0x21 },
    { "PLMN",               0x05, 0x22 },
    { "PrefC",              0x05, 0x23 },
    { "PreferredContacts",  0x05, 0x24 },
    { "PreferredLanguage",  0x05, 0x25 },
    { "PreferredContent",   0x05, 0x26 },
    { "PreferredvCard",     0x05, 0x27 },
    { "Registration",       0x05, 0x28 },
    { "StatusContent",      0x05, 0x29 },
    { "StatusMood",         0x05, 0x2A },
    { "StatusText",         0x05, 0x2B },
    { "Street",             0x05, 0x2C },
    { "Text",               0x05, 0x3A }, /* WV 1.2 */
    { "TimeZone",           0x05, 0x2D },
    { "UserAvailability",   0x05, 0x2E },
    { "Zone",               0x05, 0x35 },
        
    /* Messaging */
    { "BlockList",                  0x06, 0x05 },
    { "BlockEntity-Request",        0x06, 0x06 }, /* WV 1.2 : changed from 'BlockUser-Request' in WV 1.1 */
    { "DeliveryMethod",             0x06, 0x07 },
    { "DeliveryReport",             0x06, 0x08 },
    { "DeliveryReport-Request",     0x06, 0x09 },
    { "DeliveryTime",               0x06, 0x1A },
    { "ForwardMessage-Request",     0x06, 0x0A },
    { "GetBlockedList-Request",     0x06, 0x0B },
    { "GetBlockedList-Response",    0x06, 0x0C },
    { "GetMessageList-Request",     0x06, 0x0D },
    { "GetMessageList-Response",    0x06, 0x0E },
    { "GetMessage-Request",         0x06, 0x0F },
    { "GetMessage-Response",        0x06, 0x10 },
    { "GrantList",                  0x06, 0x11 },
    { "MessageDelivered",           0x06, 0x12 },
    { "MessageInfo",                0x06, 0x13 },
    { "MessageNotification",        0x06, 0x14 },
    { "NewMessage",                 0x06, 0x15 },
    { "RejectMessage-Request",      0x06, 0x16 },
    { "SendMessage-Request",        0x06, 0x17 },
    { "SendMessage-Response",       0x06, 0x18 },
    { "SetDeliveryMethod-Request",  0x06, 0x19 },
    
    /* Group */
    { "AddGroupMembers-Request",    0x07, 0x05 },
    { "Admin",                      0x07, 0x06 },
    { "AdminMapList",               0x07, 0x26 }, /* WV 1.2 */
    { "AdminMapping",               0x07, 0x27 }, /* WV 1.2 */
    { "CreateGroup-Request",        0x07, 0x07 },
    { "DeleteGroup-Request",        0x07, 0x08 },
    { "GetGroupMembers-Request",    0x07, 0x09 },
    { "GetGroupMembers-Response",   0x07, 0x0A },
    { "GetGroupProps-Request",      0x07, 0x0B },
    { "GetGroupProps-Response",     0x07, 0x0C },
    { "GetJoinedUsers-Request",     0x07, 0x24 }, /* WV 1.2 */
    { "GetJoinedUsers-Response",    0x07, 0x25 }, /* WV 1.2 */
    { "GroupChangeNotice",          0x07, 0x0D },
    { "GroupProperties",            0x07, 0x0E },
    { "Joined",                     0x07, 0x0F },
    { "JoinGroup",                  0x07, 0x21 },
    { "JoinedRequest",              0x07, 0x10 },
    { "JoinGroup-Request",          0x07, 0x11 },
    { "JoinGroup-Response",         0x07, 0x12 },
    { "LeaveGroup-Request",         0x07, 0x13 },
    { "LeaveGroup-Response",        0x07, 0x14 },
    { "Left",                       0x07, 0x15 },
    { "Mapping",                    0x07, 0x28 }, /* WV 1.2 */
    { "MemberAccess-Request",       0x07, 0x16 },
    { "Mod",                        0x07, 0x17 },
    { "ModMapping",                 0x07, 0x29 }, /* WV 1.2 */
    { "OwnProperties",              0x07, 0x18 },
    { "RejectList-Request",         0x07, 0x19 },
    { "RejectList-Response",        0x07, 0x1A },
    { "RemoveGroupMembers-Request", 0x07, 0x1B },
    { "SetGroupProps-Request",      0x07, 0x1C },
    { "SubscribeGroupNotice-Request",   0x07, 0x1D },
    { "SubscribeGroupNotice-Response",  0x07, 0x1E },
    { "SubscribeNotification",          0x07, 0x22 },
    { "SubscribeType",                  0x07, 0x23 },
    { "UserMapList",                0x07, 0x2A }, /* WV 1.2 */
    { "UserMapping",                0x07, 0x2B }, /* WV 1.2 */
    { "Users",                      0x07, 0x1F },
    { "WelcomeNote",                0x07, 0x20 },

    /* Service ... continued */
    { "GETAUT",                     0x08, 0x06 }, /* WV 1.2 */
    { "GETJU",                      0x08, 0x07 }, /* WV 1.2 */
    { "MP",                         0x08, 0x05 }, /* WV 1.2 */
    { "VRID",                       0x08, 0x08 }, /* WV 1.2 */
    { "VerifyIDFunc",               0x08, 0x09 }, /* WV 1.2 */

    /* Common ... continued */
    { "CIR",                        0x09, 0x05 }, /* WV 1.2 */
    { "Domain",                     0x09, 0x06 }, /* WV 1.2 */
    { "ExtBlock",                   0x09, 0x07 }, /* WV 1.2 */
    { "HistoryPeriod",              0x09, 0x08 }, /* WV 1.2 */
    { "IDList",                     0x09, 0x09 }, /* WV 1.2 */
    { "MaxWatcherList",             0x09, 0x0A }, /* WV 1.2 */
    { "ReactiveAuthState",          0x09, 0x0B }, /* WV 1.2 */
    { "ReactiveAuthStatus",         0x09, 0x0C }, /* WV 1.2 */
    { "ReactiveAuthStatusList",     0x09, 0x0D }, /* WV 1.2 */
    { "Watcher",                    0x09, 0x0E }, /* WV 1.2 */
    { "WatcherStatus",              0x09, 0x0F }, /* WV 1.2 */

    /* Access ... continued */
    { "WV-CSP-VersionDiscovery-Request",  0x0A, 0x05 }, /* WV 1.2 */
    { "WV-CSP-VersionDiscovery-Response", 0x0A, 0x06 }, /* WV 1.2 */
    { "VersionList",                      0x0A, 0x07 }, /* WV 1.2 */

    { NULL,                         0x00, 0x00 }
};

const WBXMLAttrEntry sv_wv_csp_attr_table[] = {
    { "xmlns",      "http://www.wireless-village.org/CSP",  0x00, 0x05 },
    { "xmlns",      "http://www.wireless-village.org/PA",   0x00, 0x06 },
    { "xmlns",      "http://www.wireless-village.org/TRC",  0x00, 0x07 },
    { "xmlns",      "http://www.openmobilealliance.org/DTD/WV-CSP",     0x00, 0x08 },
    { "xmlns",      "http://www.openmobilealliance.org/DTD/WV-PA",      0x00, 0x09 },
    { "xmlns",      "http://www.openmobilealliance.org/DTD/WV-TRC",     0x00, 0x0A },
    { NULL,         NULL,                                   0x00, 0x00 }
};

const WBXMLExtValueEntry sv_wv_csp_ext_table[] = {
    /*
     * DO NOT CHANGE THIS TABLE ORDER PLEASE ! 
     * Extension Tokens must be sorted by length !
     */

    { "application/vnd.wap.mms-message",    0x04 }, /* Common value token */
    { "www.wireless-village.org",           0x30 }, /* Common value token */
    { "GROUP_USER_ID_AUTOJOIN",             0x50 }, /* Access value token */ /* WV 1.2 */
    { "GROUP_USER_ID_JOINED",               0x40 }, /* Access value token */
    { "GROUP_USER_ID_OWNER",                0x41 }, /* Access value token */
    { "USER_EMAIL_ADDRESS",                 0x47 }, /* Access value token */
    { "USER_MOBILE_NUMBER",                 0x4b }, /* Access value token */
    { "USER_ONLINE_STATUS",                 0x4c }, /* Access value token */
    { "application/x-sms",                  0x05 }, /* Common value token */
    { "PrivateMessaging",                   0x1c }, /* Common value token */
    { "text/x-vCalendar",                   0x29 }, /* Common value token */
    { "USER_FIRST_NAME",                    0x48 }, /* Access value token */
    { "MaxActiveUsers",                     0x13 }, /* Common value token */
    { "PrivilegeLevel",                     0x1d }, /* Common value token */
    { "USER_LAST_NAME",                     0x4a }, /* Access value token */
    { "NOT_AVAILABLE",                      0x70 }, /* Presence value token */
    { "application/",                       0x03 }, /* Common value token */
    { "text/x-vCard",                       0x2a }, /* Common value token */
    { "MOBILE_PHONE",                       0x6f }, /* Presence value token */   
    { "VIDEO_STREAM",                       0x77 }, /* Presence value token */
    { "ActiveUsers",                        0x01 }, /* Common value token */
    { "DisplayName",                        0x0a }, /* Common value token */
    { "GROUP_TOPIC",                        0x3f }, /* Access value token */
    { "AccessType",                         0x00 }, /* Common value token */
    { "AutoDelete",                         0x31 }, /* Common value token */ /* WV 1.2 */
    { "Restricted",                         0x22 }, /* Common value token */
    { "ScreenName",                         0x23 }, /* Common value token */
    { "Searchable",                         0x24 }, /* Common value token */
    { "text/plain",                         0x28 }, /* Common value token */
    { "GROUP_NAME",                         0x3e }, /* Access value token */
    { "USER_ALIAS",                         0x46 }, /* Access value token */
    { "AUDIO_CALL",                         0x5e }, /* Presence value token */
    { "IM_OFFLINE",                         0x69 }, /* Presence value token */
    { "INVINCIBLE",                         0x6c }, /* Presence value token */
    { "VIDEO_CALL",                         0x76 }, /* Presence value token */
    { "AVAILABLE",                          0x5f }, /* Presence value token */
    { "IM_ONLINE",                          0x6a }, /* Presence value token */
    { "https://",                           0x0f }, /* Common value token */
    { "AutoJoin",                           0x06 }, /* Common value token */
    { "Response",                           0x21 }, /* Common value token */
    { "Validity",                           0x33 }, /* Common value token */ /* WV 1.2 */
    { "GROUP_ID",                           0x3d }, /* Access value token */
    { "COMPUTER",                           0x63 }, /* Presence value token */
    { "DISCREET",                           0x64 }, /* Presence value token */
    { "Default",                            0x09 }, /* Common value token */
    { "GRANTED",                            0x35 }, /* Common value token */ /* WV 1.2 */
    { "http://",                            0x0e }, /* Common value token */
    { "Outband",                            0x19 }, /* Common value token */
    { "PENDING",                            0x36 }, /* Common value token */ /* WV 1.2 */
    { "Private",                            0x1b }, /* Common value token */
    { "Request",                            0x20 }, /* Common value token */
    { "USER_ID",                            0x49 }, /* Access value token */
    { "ANXIOUS",                            0x5c }, /* Presence value token */
    { "ASHAMED",                            0x5d }, /* Presence value token */
    { "EXCITED",                            0x66 }, /* Presence value token */
    { "IN_LOVE",                            0x6b }, /* Presence value token */
    { "JEALOUS",                            0x6d }, /* Presence value token */
    { "BASE64",                             0x07 }, /* Common value token */
    { "Closed",                             0x08 }, /* Common value token */
    { "image/",                             0x10 }, /* Common value token */
    { "Inband",                             0x11 }, /* Common value token */
    { "Public",                             0x1e }, /* Common value token */    
    { "DENIED",                             0x34 }, /* Common value token */ /* WV 1.2 */  
    { "WAPSMS",                             0x4d }, /* Access value token */
    { "WAPUDP",                             0x4e }, /* Access value token */  
    { "SLEEPY",                             0x74 }, /* Presence value token */
    { "ShowID",                             0x37 }, /* Common value token */ /* WV 1.2 */
    { "Admin",                              0x02 }, /* Common value token */
    { "text/",                              0x27 }, /* Common value token */
    { "Topic",                              0x2b }, /* Common value token */
    { "ANGRY",                              0x5b }, /* Presence value token */
    { "BORED",                              0x60 }, /* Presence value token */
    { "EMAIL",                              0x65 }, /* Presence value token */
    { "HAPPY",                              0x67 }, /* Presence value token */
    { "OTHER",                              0x71 }, /* Presence value token */
    { "Name",                               0x15 }, /* Common value token */
    { "None",                               0x16 }, /* Common value token */
    { "Open",                               0x18 }, /* Common value token */
    { "Type",                               0x2d }, /* Common value token */
    { "HTTP",                               0x42 }, /* Access value token */
    { "STCP",                               0x44 }, /* Access value token */
    { "SUDP",                               0x45 }, /* Access value token */
    { "CALL",                               0x61 }, /* Presence value token */
    { "Mod",                                0x14 }, /* Common value token */
    { "SMS",                                0x43 }, /* Access value token */
    { "WSP",                                0x4f }, /* Access value token */
    { "CLI",                                0x62 }, /* Presence value token */
    { "MMS",                                0x6e }, /* Presence value token */
    { "PDA",                                0x72 }, /* Presence value token */
    { "SAD",                                0x73 }, /* Presence value token */
    { "SMS",                                0x75 }, /* Presence value token */
    { "GM",                                 0x32 }, /* Common value token */ /* WV 1.2 */
    { "GR",                                 0x0d }, /* Common value token */
    { "IM",                                 0x12 }, /* Common value token */    
    { "PR",                                 0x1a }, /* Common value token */
    { "SC",                                 0x26 }, /* Common value token */
    { "US",                                 0x2f }, /* Common value token */
    { "IM",                                 0x68 }, /* Presence value token */ /* Obsolete in WV 1.2 */
    { "F",                                  0x0b }, /* Common value token */
    { "G",                                  0x0c }, /* Common value token */
    { "N",                                  0x17 }, /* Common value token */
    { "P",                                  0x1f }, /* Common value token */
    { "S",                                  0x25 }, /* Common value token */
    { "T",                                  0x2c }, /* Common value token */
    { "U",                                  0x2e }, /* Common value token */

    { NULL,                                 0x00 }, /* Presence value token */
};

#endif /* WBXML_SUPPORT_WV */


#if defined( WBXML_SUPPORT_AIRSYNC )

/*************************************************
 *    Microsoft ActiveSync (aka AirSync)
 *
 *    Actually the table represent [MS-ASWBXML] 8.0.
 *
 *    The version means the protocol version (e.g. v12.0).
 *    The revision means the revision of the specification document (e.g. r8.0).
 * 
 *    mainly used by Microsoft Exchange and
 *    modern mobiles from all vendors
 */
 
const WBXMLTagEntry sv_airsync_tag_table[] = {
    /* Code Page: "AirSync" (since v2.5 and r1.0) */
    { "Sync",                   0x00, 0x05 }, /* since r1.0 */
    { "Responses",              0x00, 0x06 }, /* since r1.0 */
    { "Add",                    0x00, 0x07 }, /* since r1.0 */
    { "Change",                 0x00, 0x08 }, /* since r1.0 */
    { "Delete",                 0x00, 0x09 }, /* since r1.0 */
    { "Fetch",                  0x00, 0x0a }, /* since r1.0 */
    { "SyncKey",                0x00, 0x0b }, /* since r1.0 */
    { "ClientId",               0x00, 0x0c }, /* since r1.0 */
    { "ServerId",               0x00, 0x0d }, /* since r1.0 */
    { "Status",                 0x00, 0x0e }, /* since r1.0 */
    { "Collection",             0x00, 0x0f }, /* since r1.0 */
    { "Class",                  0x00, 0x10 }, /* since r1.0 */
    { "Version",                0x00, 0x11 }, /* not defined in r8.0 but in r1.0 */
    { "CollectionId",           0x00, 0x12 }, /* since r1.0 */
    { "GetChanges",             0x00, 0x13 }, /* since r1.0 */
    { "MoreAvailable",          0x00, 0x14 }, /* since r1.0 */
    { "WindowSize",             0x00, 0x15 }, /* since r1.0 */
    { "Commands",               0x00, 0x16 }, /* since r1.0 */
    { "Options",                0x00, 0x17 }, /* since r1.0 */
    { "FilterType",             0x00, 0x18 }, /* since r1.0 */
    { "Truncation",             0x00, 0x19 }, /* not defined in r8.0 but in r1.0 */
    { "RTFTruncation",          0x00, 0x1a }, /* corrected in libwbxml 0.11.0, not defined in r8.0 but in r1.0 */
    { "Conflict",               0x00, 0x1b }, /* since r1.0 */
    { "Collections",            0x00, 0x1c }, /* since r1.0 */
    { "ApplicationData",        0x00, 0x1d }, /* since r1.0 */
    { "DeletesAsMoves",         0x00, 0x1e }, /* since r1.0 */
    { "NotifyGUID",             0x00, 0x1f }, /* not defined in r8.0 but in r1.0 */
    { "Supported",              0x00, 0x20 }, /* since r1.0 */
    { "SoftDelete",             0x00, 0x21 }, /* since r1.0 */
    { "MIMESupport",            0x00, 0x22 }, /* since r1.0 */
    { "MIMETruncation",         0x00, 0x23 }, /* since r1.0 */
    { "Wait",                   0x00, 0x24 }, /* since r1.0 */
    { "Limit",                  0x00, 0x25 }, /* since r1.0 */
    { "Partial",                0x00, 0x26 }, /* since r1.0 */
    { "ConversationMode",       0x00, 0x27 }, /* r8.0: not supported when the MS-ASProtocolVersion header is set to 12.1 */
    { "MaxItems",               0x00, 0x28 }, /* r8.0: not supported when the MS-ASProtocolVersion header is set to 12.1 */
    { "HeartbeatInterval",      0x00, 0x29 }, /* r8.0: not supported when the MS-ASProtocolVersion header is set to 12.1 */

    /* Code Page: Contacts (since v2.5 and r1.0) */
    { "Anniversary",            0x01, 0x05 }, /* since r1.0 */
    { "AssistantName",          0x01, 0x06 }, /* since r1.0 */
    { "AssistantTelephoneNumber", 0x01, 0x07 }, /* corrected in libwbxml 0.11.0 */
    { "Birthday",               0x01, 0x08 }, /* since r1.0 */
    { "Body",                   0x01, 0x09 }, /* not defined in r8.0 but in r1.0 */
    { "BodySize",               0x01, 0x0a }, /* not defined in r8.0 but in r1.0 */
    { "BodyTruncated",          0x01, 0x0b }, /* not defined in r8.0 but in r1.0 */
    { "Business2PhoneNumber",   0x01, 0x0c }, /* changed in r8.0, r1.0: Business2TelephoneNumber */
    { "BusinessCity",           0x01, 0x0d }, /* since r1.0 */
    { "BusinessCountry",        0x01, 0x0e }, /* since r1.0 */
    { "BusinessPostalCode",     0x01, 0x0f }, /* since r1.0 */
    { "BusinessState",          0x01, 0x10 }, /* since r1.0 */
    { "BusinessStreet",         0x01, 0x11 }, /* since r1.0 */
    { "BusinessFaxNumber",      0x01, 0x12 }, /* since r1.0 */
    { "BusinessPhoneNumber",    0x01, 0x13 }, /* changed in r8.0, r1.0: BusinessTelephoneNumber */
    { "CarPhoneNumber",         0x01, 0x14 }, /* since r1.0 */
    { "Categories",             0x01, 0x15 }, /* since r1.0 */
    { "Category",               0x01, 0x16 }, /* since r1.0 */
    { "Children",               0x01, 0x17 }, /* since r1.0 */
    { "Child",                  0x01, 0x18 }, /* since r1.0 */
    { "CompanyName",            0x01, 0x19 }, /* since r1.0 */
    { "Department",             0x01, 0x1a }, /* since r1.0 */
    { "Email1Address",          0x01, 0x1b }, /* since r1.0 */
    { "Email2Address",          0x01, 0x1c }, /* since r1.0 */
    { "Email3Address",          0x01, 0x1d }, /* since r1.0 */
    { "FileAs",                 0x01, 0x1e }, /* since r1.0 */
    { "FirstName",              0x01, 0x1f }, /* since r1.0 */
    { "Home2PhoneNumber",       0x01, 0x20 }, /* changed in r8.0, r1.0: BusinessTelephoneNumber */
    { "HomeCity",               0x01, 0x21 }, /* since r1.0 */
    { "HomeCountry",            0x01, 0x22 }, /* since r1.0 */
    { "HomePostalCode",         0x01, 0x23 }, /* since r1.0 */
    { "HomeState",              0x01, 0x24 }, /* since r1.0 */
    { "HomeStreet",             0x01, 0x25 }, /* since r1.0 */
    { "HomeFaxNumber",          0x01, 0x26 }, /* since r1.0 */
    { "HomePhoneNumber",        0x01, 0x27 }, /* changed in r8.0, r1.0: BusinessTelephoneNumber */
    { "JobTitle",               0x01, 0x28 }, /* since r1.0 */
    { "LastName",               0x01, 0x29 }, /* since r1.0 */
    { "MiddleName",             0x01, 0x2a }, /* since r1.0 */
    { "MobilePhoneNumber",      0x01, 0x2b }, /* changed in r8.0, r1.0: BusinessTelephoneNumber */
    { "OfficeLocation",         0x01, 0x2c }, /* since r1.0 */
    { "OtherCity",              0x01, 0x2d }, /* since r1.0 */
    { "OtherCountry",           0x01, 0x2e }, /* since r1.0 */
    { "OtherPostalCode",        0x01, 0x2f }, /* since r1.0 */
    { "OtherState",             0x01, 0x30 }, /* since r1.0 */
    { "OtherStreet",            0x01, 0x31 }, /* since r1.0 */
    { "PagerNumber",            0x01, 0x32 }, /* since r1.0 */
    { "RadioPhoneNumber",       0x01, 0x33 }, /* changed in r8.0, r1.0: BusinessTelephoneNumber */
    { "Spouse",                 0x01, 0x34 }, /* since r1.0 */
    { "Suffix",                 0x01, 0x35 }, /* since r1.0 */
    { "Title",                  0x01, 0x36 }, /* since r1.0 */
    { "WebPage",                0x01, 0x37 }, /* since r1.0 */
    { "YomiCompanyName",        0x01, 0x38 }, /* since r1.0 */
    { "YomiFirstName",          0x01, 0x39 }, /* since r1.0 */
    { "YomiLastName",           0x01, 0x3a }, /* since r1.0 */
    { "CompressedRTF",          0x01, 0x3b }, /* corrected in libwbxml 0.11.0, not defined in r8.0 but in r1.0 */
    { "Picture",                0x01, 0x3c }, /* since r1.0 */
    { "Alias",                  0x01, 0x3d }, /* r8.0: not supported when the MS-ASProtocolVersion header is set to 12.1 */
    { "WeightedRank",           0x01, 0x3e }, /* r8.0: not supported when the MS-ASProtocolVersion header is set to 12.1 */

    /* Code Page: Email (since v2.5 and r1.0) */
    { "Attachment",             0x02, 0x05 }, /* not defined in r8.0 but in r1.0, supported by v2.5, v12.0 and v12.1 */
    { "Attachments",            0x02, 0x06 }, /* not defined in r8.0 but in r1.0, supported by v2.5, v12.0 and v12.1 */
    { "AttName",                0x02, 0x07 }, /* not defined in r8.0 but in r1.0, supported by v2.5, v12.0 and v12.1 */
    { "AttSize",                0x02, 0x08 }, /* not defined in r8.0 but in r1.0, supported by v2.5, v12.0 and v12.1 */
    { "AttOId",                 0x02, 0x09 }, /* corrected in libwbxml 0.11.0, not defined in r8.0 but in r1.0, supported by v2.5, v12.0 and v12.1 */
    { "AttMethod",              0x02, 0x0a }, /* not defined in r8.0 but in r1.0, supported by v2.5, v12.0 and v12.1 */
    { "AttRemoved",             0x02, 0x0b }, /* not defined in r8.0 but in r1.0, supported by v2.5, v12.0 and v12.1 */
    { "Body",                   0x02, 0x0c }, /* not defined in r8.0 but in r1.0, supported by v2.5, v12.0 and v12.1 */
    { "BodySize",               0x02, 0x0d }, /* not defined in r8.0 but in r1.0, supported by v2.5, v12.0 and v12.1 */
    { "BodyTruncated",          0x02, 0x0e }, /* not defined in r8.0 but in r1.0, supported by v2.5, v12.0 and v12.1 */
    { "DateReceived",           0x02, 0x0f }, /* supported since v2.5 */
    { "DisplayName",            0x02, 0x10 }, /* not defined in r8.0 but in r1.0, supported by v2.5, v12.0 and v12.1 */
    { "DisplayTo",              0x02, 0x11 }, /* supported since v2.5 */
    { "Importance",             0x02, 0x12 }, /* supported since v2.5 */
    { "MessageClass",           0x02, 0x13 }, /* supported since v2.5 */
    { "Subject",                0x02, 0x14 }, /* supported since v2.5 */
    { "Read",                   0x02, 0x15 }, /* supported since v2.5 */
    { "To",                     0x02, 0x16 }, /* supported since v2.5 */
    { "Cc",                     0x02, 0x17 }, /* supported since v2.5 */
    { "From",                   0x02, 0x18 }, /* supported since v2.5 */
    { "Reply-To",               0x02, 0x19 }, /* supported since v2.5 */
    { "AllDayEvent",            0x02, 0x1a }, /* supported since v2.5 */
    { "Categories",             0x02, 0x1b }, /* r1.0: supported by v2.5, v12.0 and 12.1; BUT r8.0: not supported by 12.1 */
    { "Category",               0x02, 0x1c }, /* r1.0: supported by v2.5, v12.0 and 12.1; BUT r8.0: not supported by 12.1 */
    { "DTStamp",                0x02, 0x1d }, /* corrected in libwbxml 0.11.0, supported since v2.5 */
    { "EndTime",                0x02, 0x1e }, /* supported since v2.5 */
    { "InstanceType",           0x02, 0x1f }, /* supported since v2.5 */
    { "BusyStatus",             0x02, 0x20 }, /* supported since v2.5 */
    { "Location",               0x02, 0x21 }, /* supported since v2.5 */
    { "MeetingRequest",         0x02, 0x22 }, /* supported since v2.5 */
    { "Organizer",              0x02, 0x23 }, /* supported since v2.5 */
    { "RecurrenceId",           0x02, 0x24 }, /* supported since v2.5 */
    { "Reminder",               0x02, 0x25 }, /* supported since v2.5 */
    { "ResponseRequested",      0x02, 0x26 }, /* supported since v2.5 */
    { "Recurrences",            0x02, 0x27 }, /* supported since v2.5 */
    { "Recurrence",             0x02, 0x28 }, /* supported since v2.5 */
    { "Recurrence_Type",        0x02, 0x29 }, /* corrected in libwbxml 0.11.0, supported since v2.5 */
    { "Recurrence_Until",       0x02, 0x2a }, /* corrected in libwbxml 0.11.0, supported since v2.5 */
    { "Recurrence_Occurrences", 0x02, 0x2b }, /* corrected in libwbxml 0.11.0, supported since v2.5 */
    { "Recurrence_Interval",    0x02, 0x2c }, /* corrected in libwbxml 0.11.0, supported since v2.5 */
    { "Recurrence_DayOfWeek",   0x02, 0x2d }, /* corrected in libwbxml 0.11.0, supported since v2.5 */
    { "Recurrence_DayOfMonth",  0x02, 0x2e }, /* corrected in libwbxml 0.11.0, supported since v2.5 */
    { "Recurrence_WeekOfMonth", 0x02, 0x2f }, /* corrected in libwbxml 0.11.0, supported since v2.5 */
    { "Recurrence_MonthOfYear", 0x02, 0x30 }, /* corrected in libwbxml 0.11.0, supported since v2.5 */
    { "StartTime",              0x02, 0x31 }, /* supported since v2.5 */
    { "Sensitivity",            0x02, 0x32 }, /* supported since v2.5 */
    { "TimeZone",               0x02, 0x33 }, /* supported since v2.5 */
    { "GlobalObjId",            0x02, 0x34 }, /* supported since v2.5 */
    { "ThreadTopic",            0x02, 0x35 }, /* supported since v2.5 */
    { "MIMEData",               0x02, 0x36 }, /* not defined in r8.0 but in r1.0, supported by v2.5, v12.0 and v12.1 */
    { "MIMETruncated",          0x02, 0x37 }, /* not defined in r8.0 but in r1.0, supported by v2.5, v12.0 and v12.1 */
    { "MIMESize",               0x02, 0x38 }, /* not defined in r8.0 but in r1.0, supported by v2.5, v12.0 and v12.1 */
    { "InternetCPID",           0x02, 0x39 }, /* supported since v2.5 */
    { "Flag",                   0x02, 0x3a }, /* supported since v12.0 */
    { "FlagStatus",             0x02, 0x3b }, /* supported since v12.0 */
    { "ContentClass",           0x02, 0x3c }, /* supported since v12.0 */
    { "FlagType",               0x02, 0x3d }, /* supported since v12.0 */
    { "CompleteTime",           0x02, 0x3e }, /* supported since v12.0 */
    { "DisallowNewTimeProposal",0x02, 0x3f }, /* r8.0: not supported when the MS-ASProtocolVersion header is set to 12.1 */

    /* Code Page: AirNotify */

    /* There are conflicting version informations.
     *
     * r1.0: supported by v2.5, v12.0 and v12.1
     * r8.0: This code page is no longer in use.
     * r8.0: Tokens 05 to 17 have been defined.
     */

    { "Notify",                 0x03, 0x05 }, /* not defined in r8.0 but in r1.0, only supported by v2.0 and v2.5 */
    { "Notification",           0x03, 0x06 }, /* not defined in r8.0 but in r1.0, supported by v2.5, v12.0 and v12.1 */
    { "Version",                0x03, 0x07 }, /* not defined in r8.0 but in r1.0, supported by v2.5, v12.0 and v12.1 */
    { "LifeTime",               0x03, 0x08 }, /* corrected in libwbxml 0.11.0, not defined in r8.0 but in r1.0, supported by v2.5, v12.0 and v12.1 */
    { "DeviceInfo",             0x03, 0x09 }, /* not defined in r8.0 but in r1.0, supported by v2.5, v12.0 and v12.1 */
    { "Enable",                 0x03, 0x0a }, /* not defined in r8.0 but in r1.0, supported by v2.5, v12.0 and v12.1 */
    { "Folder",                 0x03, 0x0b }, /* not defined in r8.0 but in r1.0, supported by v2.5, v12.0 and v12.1 */
    { "ServerId",               0x03, 0x0c }, /* not defined in r8.0 but in r1.0, supported by v2.5, v12.0 and v12.1 */
    { "DeviceAddress",          0x03, 0x0d }, /* not defined in r8.0 but in r1.0, supported by v2.5, v12.0 and v12.1 */
    { "ValidCarrierProfiles",   0x03, 0x0e }, /* not defined in r8.0 but in r1.0, supported by v2.5, v12.0 and v12.1 */
    { "CarrierProfile",         0x03, 0x0f }, /* not defined in r8.0 but in r1.0, supported by v2.5, v12.0 and v12.1 */
    { "Status",                 0x03, 0x10 }, /* not defined in r8.0 but in r1.0, supported by v2.5, v12.0 and v12.1 */
    { "Responses",              0x03, 0x11 }, /* not defined in r8.0 but in r1.0, supported by v2.5, v12.0 and v12.1 */
    { "Devices",                0x03, 0x12 }, /* not defined in r8.0 but in r1.0, supported by v2.5, v12.0 and v12.1 */
    { "Device",                 0x03, 0x13 }, /* not defined in r8.0 but in r1.0, supported by v2.5, v12.0 and v12.1 */
    { "Id",                     0x03, 0x14 }, /* not defined in r8.0 but in r1.0, supported by v2.5, v12.0 and v12.1 */
    { "Expiry",                 0x03, 0x15 }, /* not defined in r8.0 but in r1.0, supported by v2.5, v12.0 and v12.1 */
    { "NotifyGUID",             0x03, 0x16 }, /* not defined in r8.0 but in r1.0, supported by v2.5, v12.0 and v12.1 */
    { "DeviceFriendlyName",     0x03, 0x17 }, /* not defined in r8.0 but in r1.0, supported by v2.5, v12.0 and v12.1 */

    /* Code Page: Calendar (since v2.5 and r1.0) */
    { "TimeZone",               0x04, 0x05 }, /* corrected in libwbxml 0.11.0, supported since v2.5 */
    { "AllDayEvent",            0x04, 0x06 }, /* supported since v2.5 */
    { "Attendees",              0x04, 0x07 }, /* supported since v2.5 */
    { "Attendee",               0x04, 0x08 }, /* supported since v2.5 */
    { "Attendee_Email",         0x04, 0x09 }, /* corrected in libwbxml 0.11.0, supported since v2.5 */
    { "Attendee_Name",          0x04, 0x0a }, /* corrected in libwbxml 0.11.0, supported since v2.5 */
    { "Body",                   0x04, 0x0b }, /* not defined in r8.0 but in r1.0, supported by v2.5, v12.0 and v12.1 */
    { "BodyTruncated",          0x04, 0x0c }, /* not defined in r8.0 but in r1.0, supported by v2.5, v12.0 and v12.1 */
    { "BusyStatus",             0x04, 0x0d }, /* supported since v2.5 */
    { "Categories",             0x04, 0x0e }, /* supported since v2.5 */
    { "Category",               0x04, 0x0f }, /* supported since v2.5 */
    { "Compressed_RTF",         0x04, 0x10 }, /* corrected in libwbxml 0.11.0, not defined in r8.0 but in r1.0, supported by v2.5, v12.0 and v12.1 */
    { "DTStamp",                0x04, 0x11 }, /* corrected in libwbxml 0.11.0, supported since v2.5 */
    { "EndTime",                0x04, 0x12 }, /* supported since v2.5 */
    { "Exception",              0x04, 0x13 }, /* supported since v2.5 */
    { "Exceptions",             0x04, 0x14 }, /* supported since v2.5 */
    { "Exception_Deleted",      0x04, 0x15 }, /* corrected in libwbxml 0.11.0, supported since v2.5, changed in r8.0, r1.0: Exception_IsDeleted */
    { "Exception_StartTime",    0x04, 0x16 }, /* corrected in libwbxml 0.11.0, supported since v2.5 */
    { "Location",               0x04, 0x17 }, /* supported since v2.5 */
    { "MeetingStatus",          0x04, 0x18 }, /* supported since v2.5 */
    { "Organizer_Email",        0x04, 0x19 }, /* corrected in libwbxml 0.11.0, supported since v2.5 */
    { "Organizer_Name",         0x04, 0x1a }, /* corrected in libwbxml 0.11.0, supported since v2.5 */
    { "Recurrence",             0x04, 0x1b }, /* supported since v2.5 */
    { "Recurrence_Type",        0x04, 0x1c }, /* corrected in libwbxml 0.11.0, supported since v2.5 */
    { "Recurrence_Until",       0x04, 0x1d }, /* corrected in libwbxml 0.11.0, supported since v2.5 */
    { "Recurrence_Occurrences", 0x04, 0x1e }, /* corrected in libwbxml 0.11.0, supported since v2.5 */
    { "Recurrence_Interval",    0x04, 0x1f }, /* corrected in libwbxml 0.11.0, supported since v2.5 */
    { "Recurrence_DayOfWeek",   0x04, 0x20 }, /* corrected in libwbxml 0.11.0, supported since v2.5 */
    { "Recurrence_DayOfMonth",  0x04, 0x21 }, /* corrected in libwbxml 0.11.0, supported since v2.5 */
    { "Recurrence_WeekOfMonth", 0x04, 0x22 }, /* corrected in libwbxml 0.11.0, supported since v2.5 */
    { "Recurrence_MonthOfYear", 0x04, 0x23 }, /* corrected in libwbxml 0.11.0, supported since v2.5 */
    { "Reminder",               0x04, 0x24 }, /* supported since v2.5 */
    { "Sensitivity",            0x04, 0x25 }, /* supported since v2.5 */
    { "Subject",                0x04, 0x26 }, /* supported since v2.5 */
    { "StartTime",              0x04, 0x27 }, /* supported since v2.5 */
    { "UID",                    0x04, 0x28 }, /* supported since v2.5 */
    { "Attendee_Status",        0x04, 0x29 }, /* corrected in libwbxml 0.11.0, supported since v12.0 */
    { "Attendee_Type",          0x04, 0x2a }, /* corrected in libwbxml 0.11.0, supported since v12.0 */
    { "DisallowNewTimeProposal",0x04, 0x33 }, /* r8.0: not supported when the MS-ASProtocolVersion header is set to 12.1 */
    { "ResponseRequested",      0x04, 0x34 }, /* r8.0: not supported when the MS-ASProtocolVersion header is set to 12.1 */
    { "AppointmentReplyTime",   0x04, 0x35 }, /* r8.0: not supported when the MS-ASProtocolVersion header is set to 12.1 */
    { "ResponseType",           0x04, 0x36 }, /* r8.0: not supported when the MS-ASProtocolVersion header is set to 12.1 */
    { "CalendarType",           0x04, 0x37 }, /* r8.0: not supported when the MS-ASProtocolVersion header is set to 12.1 */
    { "IsLeapMonth",            0x04, 0x38 }, /* r8.0: not supported when the MS-ASProtocolVersion header is set to 12.1 */
    { "FirstDayOfWeek",         0x04, 0x39 }, /* r8.0: not supported when the MS-ASProtocolVersion header is set to 14.0 or 12.1 */
    { "OnlineMeetingConfLink",  0x04, 0x3a }, /* r8.0: not supported when the MS-ASProtocolVersion header is set to 14.0 or 12.1 */
    { "OnlineMeetingExternalLink",0x04, 0x3b }, /* r8.0: not supported when the MS-ASProtocolVersion header is set to 14.0 or 12.1 */

    /* Code Page: Move (since v2.5 and r1.0) */
    { "MoveItems",              0x05, 0x05 }, /* corrected in libwbxml 0.11.0, supported since v2.5 */
    { "Move",                   0x05, 0x06 }, /* since r1.0 */
    { "SrcMsgId",               0x05, 0x07 }, /* since r1.0 */
    { "SrcFldId",               0x05, 0x08 }, /* since r1.0 */
    { "DstFldId",               0x05, 0x09 }, /* since r1.0 */
    { "Response",               0x05, 0x0a }, /* since r1.0 */
    { "Status",                 0x05, 0x0b }, /* since r1.0 */
    { "DstMsgId",               0x05, 0x0c }, /* since r1.0 */

    /* Code Page: ItemEstimate (since v2.5 and r1.0) */
    { "GetItemEstimate",        0x06, 0x05 }, /* since r1.0 */
    { "Version",                0x06, 0x06 }, /* r8.0: only supported when the MS-ASProtocolVersion header is set to 12.1 */
    { "Collections",            0x06, 0x07 }, /* since r1.0 */
    { "Collection",             0x06, 0x08 }, /* since r1.0 */
    { "Class",                  0x06, 0x09 }, /* r8.0: only supported when the MS-ASProtocolVersion header is set to 12.1 */
    { "CollectionId",           0x06, 0x0a }, /* since r1.0 */
    { "DateTime",               0x06, 0x0b }, /* r8.0: only supported when the MS-ASProtocolVersion header is set to 12.1 */
    { "Estimate",               0x06, 0x0c }, /* since r1.0 */
    { "Response",               0x06, 0x0d }, /* since r1.0 */
    { "Status",                 0x06, 0x0e }, /* since r1.0 */

    /* Code Page: FolderHierarchy (since v2.5 and r1.0) */
    { "Folders",                0x07, 0x05 }, /* not defined in r8.0 but in r1.0 */
    { "Folder",                 0x07, 0x06 }, /* not defined in r8.0 but in r1.0 */
    { "DisplayName",            0x07, 0x07 }, /* since r1.0 */
    { "ServerId",               0x07, 0x08 }, /* since r1.0 */
    { "ParentId",               0x07, 0x09 }, /* since r1.0 */
    { "Type",                   0x07, 0x0a }, /* since r1.0 */
    { "Response",               0x07, 0x0b }, /* not defined in r8.0 but in r1.0 */
    { "Status",                 0x07, 0x0c }, /* since r1.0 */
    { "ContentClass",           0x07, 0x0d }, /* not defined in r8.0 but in r1.0 */
    { "Changes",                0x07, 0x0e }, /* since r1.0 */
    { "Add",                    0x07, 0x0f }, /* since r1.0 */
    { "Delete",                 0x07, 0x10 }, /* since r1.0 */
    { "Update",                 0x07, 0x11 }, /* since r1.0 */
    { "SyncKey",                0x07, 0x12 }, /* since r1.0 */
    { "FolderCreate",           0x07, 0x13 }, /* since r1.0 */
    { "FolderDelete",           0x07, 0x14 }, /* since r1.0 */
    { "FolderUpdate",           0x07, 0x15 }, /* since r1.0 */
    { "FolderSync",             0x07, 0x16 }, /* since r1.0 */
    { "Count",                  0x07, 0x17 }, /* since r1.0 */
    { "Version",                0x07, 0x18 }, /* not defined in r8.0 but in r1.0 */

    /* Code Page: MeetingResponse (since v2.5 and r1.0) */
    { "CalendarId",             0x08, 0x05 }, /* changed in r8.0, r1.0: CallID */
    { "CollectionId",           0x08, 0x06 }, /* since r1.0 */
    { "MeetingResponse",        0x08, 0x07 }, /* since r1.0 */
    { "RequestId",              0x08, 0x08 }, /* changed in r8.0, r1.0: ReqId */
    { "Request",                0x08, 0x09 }, /* since r1.0 */
    { "Result",                 0x08, 0x0a }, /* since r1.0 */
    { "Status",                 0x08, 0x0b }, /* since r1.0 */
    { "UserResponse",           0x08, 0x0c }, /* since r1.0 */
    { "Version",                0x08, 0x0d }, /* not defined in r8.0 but in r1.0 */
    { "InstanceId",             0x08, 0x0e }, /* since r8.0? */

    /* Code Page: Tasks (since v2.5 and r1.0) */
    { "Body",                   0x09, 0x05 }, /* not defined in r8.0 but in r1.0, supported by v2.5, v12.0 and v12.1 */
    { "BodySize",               0x09, 0x06 }, /* not defined in r8.0 but in r1.0, supported by v2.5, v12.0 and v12.1 */
    { "BodyTruncated",          0x09, 0x07 }, /* not defined in r8.0 but in r1.0, supported by v2.5, v12.0 and v12.1 */
    { "Categories",             0x09, 0x08 }, /* supported since v2.5 */
    { "Category",               0x09, 0x09 }, /* supported since v2.5 */
    { "Complete",               0x09, 0x0a }, /* supported since v2.5 */
    { "DateCompleted",          0x09, 0x0b }, /* supported since v2.5 */
    { "DueDate",                0x09, 0x0c }, /* supported since v2.5 */
    { "UTCDueDate",             0x09, 0x0d }, /* corrected in libwbxml 0.11.0, supported since v2.5 */
    { "Importance",             0x09, 0x0e }, /* supported since v2.5 */
    { "Recurrence",             0x09, 0x0f }, /* supported since v2.5 */
    { "Recurrence_Type",        0x09, 0x10 }, /* corrected in libwbxml 0.11.0, supported since v2.5, changed in r8.0, r1.0: RecurrenceType */
    { "Recurrence_Start",       0x09, 0x11 }, /* corrected in libwbxml 0.11.0, supported since v2.5, changed in r8.0, r1.0: RecurrenceStart */
    { "Recurrence_Until",       0x09, 0x12 }, /* corrected in libwbxml 0.11.0, supported since v2.5, changed in r8.0, r1.0: RecurrenceUntil */
    { "Recurrence_Occurrences", 0x09, 0x13 }, /* corrected in libwbxml 0.11.0, supported since v2.5, changed in r8.0, r1.0: RecurrenceOccurrences */
    { "Recurrence_Interval",    0x09, 0x14 }, /* corrected in libwbxml 0.11.0, supported since v2.5, changed in r8.0, r1.0: RecurrenceInterval */
    { "Recurrence_DayOfMonth",  0x09, 0x15 }, /* supported since v2.5, changed in r8.0, r1.0: RecurrenceDayOfMonth */
    { "Recurrence_DayOfWeek",   0x09, 0x16 }, /* corrected in libwbxml 0.11.0, supported since v2.5, changed in r8.0, r1.0: RecurrenceDayOfWeek */
    { "Recurrence_DayOfMonth",  0x09, 0x15 }, /* corrected in libwbxml 0.11.0, supported since v2.5, changed in r8.0, r1.0: RecurrenceDayOfMonth */
    { "Recurrence_WeekOfMonth", 0x09, 0x17 }, /* corrected in libwbxml 0.11.0, supported since v2.5, changed in r8.0, r1.0: RecurrenceWeekOfMonth */
    { "Recurrence_MonthOfYear", 0x09, 0x18 }, /* corrected in libwbxml 0.11.0, supported since v2.5, changed in r8.0, r1.0: RecurrenceMonthOfYear */
    { "Recurrence_Regenerate",  0x09, 0x19 }, /* corrected in libwbxml 0.11.0, supported since v2.5, changed in r8.0, r1.0: RecurrenceRegenerate */
    { "Recurrence_DeadOccur",   0x09, 0x1a }, /* corrected in libwbxml 0.11.0, supported since v2.5, changed in r8.0, r1.0: RecurrenceDeadOccour */
    { "ReminderSet",            0x09, 0x1b }, /* supported since v2.5 */
    { "ReminderTime",           0x09, 0x1c }, /* supported since v2.5 */
    { "Sensitivity",            0x09, 0x1d }, /* supported since v2.5 */
    { "StartDate",              0x09, 0x1e }, /* supported since v2.5 */
    { "UTCStartDate",           0x09, 0x1f }, /* corrected in libwbxml 0.11.0, supported since v2.5 */
    { "Subject",                0x09, 0x20 }, /* supported since v2.5 */
    { "CompressedRTF",          0x09, 0x21 }, /* corrected in libwbxml 0.11.0, not defined in r8.0 but in r1.0, supported by v2.5, v12.0 and v12.1 */
    { "OrdinalDate",            0x09, 0x22 }, /* supported since v12.0 */
    { "SubOrdinalDate",         0x09, 0x23 }, /* supported since v12.0 */
    { "CalendarType",           0x09, 0x24 }, /* r8.0: not supported when the MS-ASProtocolVersion header is set to 12.1 */
    { "IsLeapMonth",            0x09, 0x25 }, /* r8.0: not supported when the MS-ASProtocolVersion header is set to 12.1 */
    { "FirstDayOfWeek",         0x09, 0x26 }, /* r8.0: not supported when the MS-ASProtocolVersion header is set to 14.0 or 12.1 */

    /* Code Page: ResolveRecipients (since v2.5 and r1.0) */
    { "ResolveRecipients",      0x0a, 0x05 }, /* since r1.0 */
    { "Response",               0x0a, 0x06 }, /* since r1.0 */
    { "Status",                 0x0a, 0x07 }, /* since r1.0 */
    { "Type",                   0x0a, 0x08 }, /* since r1.0 */
    { "Recipient",              0x0a, 0x09 }, /* since r1.0 */
    { "DisplayName",            0x0a, 0x0a }, /* since r1.0 */
    { "EmailAddress",           0x0a, 0x0b }, /* since r1.0 */
    { "Certificates",           0x0a, 0x0c }, /* since r1.0 */
    { "Certificate",            0x0a, 0x0d }, /* since r1.0 */
    { "MiniCertificate",        0x0a, 0x0e }, /* since r1.0 */
    { "Options",                0x0a, 0x0f }, /* since r1.0 */
    { "To",                     0x0a, 0x10 }, /* since r1.0 */
    { "CertificateRetrieval",   0x0a, 0x11 }, /* since r1.0 */
    { "RecipientCount",         0x0a, 0x12 }, /* since r1.0 */
    { "MaxCertificates",        0x0a, 0x13 }, /* since r1.0 */
    { "MaxAmbiguousRecipients", 0x0a, 0x14 }, /* since r1.0 */
    { "CertificateCount",       0x0a, 0x15 }, /* since r1.0 */
    { "Availability",           0x0a, 0x16 }, /* r8.0: not supported when the MS-ASProtocolVersion header is set to 12.1 */
    { "StartTime",              0x0a, 0x17 }, /* r8.0: not supported when the MS-ASProtocolVersion header is set to 12.1 */
    { "EndTime",                0x0a, 0x18 }, /* r8.0: not supported when the MS-ASProtocolVersion header is set to 12.1 */
    { "MergedFreeBusy",         0x0a, 0x19 }, /* r8.0: not supported when the MS-ASProtocolVersion header is set to 12.1 */
    { "Picture",                0x0a, 0x1a }, /* r8.0: not supported when the MS-ASProtocolVersion header is set to 14.0 or 12.1 */
    { "MaxSize",                0x0a, 0x1b }, /* r8.0: not supported when the MS-ASProtocolVersion header is set to 14.0 or 12.1 */
    { "Data",                   0x0a, 0x1c }, /* r8.0: not supported when the MS-ASProtocolVersion header is set to 14.0 or 12.1 */
    { "MaxPictures",            0x0a, 0x1d }, /* r8.0: not supported when the MS-ASProtocolVersion header is set to 14.0 or 12.1 */

    /* Code Page: ValidateCert (since v2.5 and r1.0) */
    { "ValidateCert",           0x0b, 0x05 }, /* since r1.0 */
    { "Certificates",           0x0b, 0x06 }, /* since r1.0 */
    { "Certificate",            0x0b, 0x07 }, /* since r1.0 */
    { "CertificateChain",       0x0b, 0x08 }, /* since r1.0 */
    { "CheckCRL",               0x0b, 0x09 }, /* since r1.0 */
    { "Status",                 0x0b, 0x0a }, /* since r1.0 */

    /* Code Page: Contacts2 (since v2.5 and r1.0) */
    { "CustomerId",             0x0c, 0x05 }, /* since r1.0 */
    { "GovernmentId",           0x0c, 0x06 }, /* since r1.0 */
    { "IMAddress",              0x0c, 0x07 }, /* since r1.0 */
    { "IMAddress2",             0x0c, 0x08 }, /* since r1.0 */
    { "IMAddress3",             0x0c, 0x09 }, /* since r1.0 */
    { "ManagerName",            0x0c, 0x0a }, /* since r1.0 */
    { "CompanyMainPhone",       0x0c, 0x0b }, /* since r1.0 */
    { "AccountName",            0x0c, 0x0c }, /* since r1.0 */
    { "NickName",               0x0c, 0x0d }, /* since r1.0 */
    { "MMS",                    0x0c, 0x0e }, /* since r1.0 */

    /* Code Page: Ping (since v2.5 and r1.0) */
    { "Ping",                   0x0d, 0x05 }, /* since r1.0 */
    { "AutdState",              0x0d, 0x06 }, /* not used by protocol */
    { "Status",                 0x0d, 0x07 }, /* since r1.0 */
    { "HeartbeatInterval",      0x0d, 0x08 }, /* since r1.0 */
    { "Folders",                0x0d, 0x09 }, /* since r1.0 */
    { "Folder",                 0x0d, 0x0a }, /* since r1.0 */
    { "Id",                     0x0d, 0x0b }, /* since r1.0 */
    { "Class",                  0x0d, 0x0c }, /* since r1.0 */
    { "MaxFolders",             0x0d, 0x0d }, /* since r1.0 */

    /* Code Page: Provision (since v2.5 and r1.0) */
    { "Provision",                                0x0e, 0x05 }, /* supported since v2.5 */
    { "Policies",                                 0x0e, 0x06 }, /* supported since v2.5 */
    { "Policy",                                   0x0e, 0x07 }, /* supported since v2.5 */
    { "PolicyType",                               0x0e, 0x08 }, /* supported since v2.5 */
    { "PolicyKey",                                0x0e, 0x09 }, /* supported since v2.5 */
    { "Data",                                     0x0e, 0x0a }, /* supported since v2.5 */
    { "Status",                                   0x0e, 0x0b }, /* supported since v2.5 */
    { "RemoteWipe",                               0x0e, 0x0c }, /* supported since v2.5 */
    { "EASProvisionDoc",                          0x0e, 0x0d }, /* supported since v12.0 */
    { "DevicePasswordEnabled",                    0x0e, 0x0e }, /* supported since v12.0 */
    { "AlphanumericDevicePasswordRequired",       0x0e, 0x0f }, /* supported since v12.0 */
    { "DeviceEncryptionEnabled",                  0x0e, 0x10 }, /* r1.0: supported since v12.0 */
    { "RequireStorageCardEncryption",             0x0e, 0x10 }, /* r1.0: supported by v2.0 and v2.5 */
    { "PasswordRecoveryEnabled",                  0x0e, 0x11 }, /* supported since v12.0 */
    { "DocumentBrowseEnabled",                    0x0e, 0x12 }, /* supported since v12.0, not defined in r8.0 but in r1.0 */
    { "AttachmentsEnabled",                       0x0e, 0x13 }, /* supported since v12.0 */
    { "MinDevicePasswordLength",                  0x0e, 0x14 }, /* supported since v12.0 */
    { "MaxInactivityTimeDeviceLock",              0x0e, 0x15 }, /* supported since v12.0 */
    { "MaxDevicePasswordFailedAttempts",          0x0e, 0x16 }, /* supported since v12.0 */
    { "MaxAttachmentSize",                        0x0e, 0x17 }, /* supported since v12.0 */
    { "AllowSimpleDevicePassword",                0x0e, 0x18 }, /* supported since v12.0 */
    { "DevicePasswordExpiration",                 0x0e, 0x19 }, /* supported since v12.0 */
    { "DevicePasswordHistory",                    0x0e, 0x1a }, /* supported since v12.0 */
    { "AllowStorageCard",                         0x0e, 0x1b }, /* supported since v12.1 */
    { "AllowCamera",                              0x0e, 0x1c }, /* supported by v2.0 and v2.5 */
    { "RequireDeviceEncryption",                  0x0e, 0x1d }, /* supported by v2.0 and v2.5 */
    { "AllowUnsignedApplications",                0x0e, 0x1e }, /* supported by v2.0 and v2.5 */
    { "AllowUnsignedInstallationPackages",        0x0e, 0x1f }, /* supported by v2.0 and v2.5 */
    { "MinDevicePasswordComplexCharacters",       0x0e, 0x20 }, /* supported by v2.0 and v2.5 */
    { "AllowWiFi",                                0x0e, 0x21 }, /* supported by v2.0 and v2.5 */
    { "AllowTextMessaging",                       0x0e, 0x22 }, /* supported by v2.0 and v2.5 */
    { "AllowPOPIMAPEmail",                        0x0e, 0x23 }, /* supported by v2.0 and v2.5 */
    { "AllowBluetooth",                           0x0e, 0x24 }, /* supported by v2.0 and v2.5 */
    { "AllowIrDA",                                0x0e, 0x25 }, /* supported by v2.0 and v2.5 */
    { "RequireManualSyncWhenRoaming",             0x0e, 0x26 }, /* supported by v2.0 and v2.5 */
    { "AllowDesktopSync",                         0x0e, 0x27 }, /* supported by v2.0 and v2.5 */
    { "MaxCalendarAgeFilter",                     0x0e, 0x28 }, /* supported by v2.0 and v2.5 */
    { "AllowHTMLEmail",                           0x0e, 0x29 }, /* supported by v2.0 and v2.5 */
    { "MaxEmailAgeFilter",                        0x0e, 0x2a }, /* supported by v2.0 and v2.5 */
    { "MaxEmailBodyTruncationSize",               0x0e, 0x2b }, /* supported by v2.0 and v2.5 */
    { "MaxEmailHTMLBodyTruncationSize",           0x0e, 0x2c }, /* supported by v2.0 and v2.5 */
    { "RequireSignedSMIMEMessages",               0x0e, 0x2d }, /* supported by v2.0 and v2.5 */
    { "RequireEncryptedSMIMEMessages",            0x0e, 0x2e }, /* supported by v2.0 and v2.5 */
    { "RequireSignedSMIMEAlgorithm",              0x0e, 0x2f }, /* supported by v2.0 and v2.5 */
    { "RequireEncryptionSMIMEAlgorithm",          0x0e, 0x30 }, /* supported by v2.0 and v2.5 */
    { "AllowSMIMEEncryptionAlgorithmNegotiation", 0x0e, 0x31 }, /* supported by v2.0 and v2.5 */
    { "AllowSMIMESoftCerts",                      0x0e, 0x32 }, /* supported by v2.0 and v2.5 */
    { "AllowBrowser",                             0x0e, 0x33 }, /* supported by v2.0 and v2.5 */
    { "AllowConsumerEmail",                       0x0e, 0x34 }, /* supported by v2.0 and v2.5 */
    { "AllowRemoteDesktop",                       0x0e, 0x35 }, /* supported by v2.0 and v2.5 */
    { "AllowInternetSharing",                     0x0e, 0x36 }, /* supported by v2.0 and v2.5 */
    { "UnapprovedInROMApplicationList",           0x0e, 0x37 }, /* supported by v2.0 and v2.5 */
    { "ApplicationName",                          0x0e, 0x38 }, /* supported by v2.0 and v2.5 */
    { "ApprovedApplicationList",                  0x0e, 0x39 }, /* supported by v2.0 and v2.5 */
    { "Hash",                                     0x0e, 0x3a }, /* supported by v2.0 and v2.5 */

    /* Code Page: Search (since v2.5 and r1.0) */
    /* Token 0x06 and 0x16 are not supported. */
    { "Search",                 0x0f, 0x05 }, /* supported since v2.5 */
    { "Store",                  0x0f, 0x07 }, /* supported since v2.5 */
    { "Name",                   0x0f, 0x08 }, /* supported since v2.5 */
    { "Query",                  0x0f, 0x09 }, /* supported since v2.5 */
    { "Options",                0x0f, 0x0a }, /* supported since v2.5 */
    { "Range",                  0x0f, 0x0b }, /* supported since v2.5 */
    { "Status",                 0x0f, 0x0c }, /* supported since v2.5 */
    { "Response",               0x0f, 0x0d }, /* supported since v2.5 */
    { "Result",                 0x0f, 0x0e }, /* supported since v2.5 */
    { "Properties",             0x0f, 0x0f }, /* supported since v2.5 */
    { "Total",                  0x0f, 0x10 }, /* supported since v2.5 */
    { "EqualTo",                0x0f, 0x11 }, /* supported since v12.0 */
    { "Value",                  0x0f, 0x12 }, /* supported since v12.0 */
    { "And",                    0x0f, 0x13 }, /* supported since v12.0 */
    { "Or",                     0x0f, 0x14 }, /* supported since v12.0, r8.0: not supported when the MS-ASProtocolVersion header is set to 12.1 */
    { "FreeText",               0x0f, 0x15 }, /* supported since v12.0 */
    { "DeepTraversal",          0x0f, 0x17 }, /* supported since v12.0 */
    { "LongId",                 0x0f, 0x18 }, /* supported since v12.0 */
    { "RebuildResults",         0x0f, 0x19 }, /* supported since v12.0 */
    { "LessThan",               0x0f, 0x1a }, /* supported since v12.0 */
    { "GreaterThan",            0x0f, 0x1b }, /* supported since v12.0 */
    { "Schema",                 0x0f, 0x1c }, /* supported since v12.0, r8.0: not defined in r8.0 but in r1.0 */
    { "Supported",              0x0f, 0x1d }, /* supported since v12.0, r8.0: not defined in r8.0 but in r1.0 */
    { "UserName",               0x0f, 0x1e }, /* since 8.0? */
    { "Password",               0x0f, 0x1f }, /* since 8.0? */
    { "ConversationId",         0x0f, 0x20, WBXML_TAG_OPTION_BINARY }, /* since 8.0? */
    { "Picture",                0x0f, 0x21 }, /* r8.0: not supported when the MS-ASProtocolVersion header is set to 14.0 or 12.1 */
    { "MaxSize",                0x0f, 0x22 }, /* r8.0: not supported when the MS-ASProtocolVersion header is set to 14.0 or 12.1 */
    { "MaxPictures",            0x0f, 0x23 }, /* r8.0: not supported when the MS-ASProtocolVersion header is set to 14.0 or 12.1 */

    /* Code Page: GAL (since v2.5 and r1.0) */
    { "DisplayName",            0x10, 0x05 }, /* since r1.0 */
    { "Phone",                  0x10, 0x06 }, /* since r1.0 */
    { "Office",                 0x10, 0x07 }, /* since r1.0 */
    { "Title",                  0x10, 0x08 }, /* since r1.0 */
    { "Company",                0x10, 0x09 }, /* since r1.0 */
    { "Alias",                  0x10, 0x0a }, /* since r1.0 */
    { "FirstName",              0x10, 0x0b }, /* since r1.0 */
    { "LastName",               0x10, 0x0c }, /* since r1.0 */
    { "HomePhone",              0x10, 0x0d }, /* since r1.0 */
    { "MobilePhone",            0x10, 0x0e }, /* since r1.0 */
    { "EmailAddress",           0x10, 0x0f }, /* since r1.0 */
    { "Picture",                0x10, 0x10 }, /* not supported when the MS-ASProtocolVersion header is set to 14.0 or 12.1 */
    { "Status",                 0x10, 0x11 }, /* not supported when the MS-ASProtocolVersion header is set to 14.0 or 12.1 */
    { "Data",                   0x10, 0x12 }, /* not supported when the MS-ASProtocolVersion header is set to 14.0 or 12.1 */

    /* Code Page: AirSyncBase (since v12.0 and r1.0) */
    { "BodyPreference",         0x11, 0x05 }, /* since r1.0 */
    { "Type",                   0x11, 0x06 }, /* since r1.0 */
    { "TruncationSize",         0x11, 0x07 }, /* since r1.0 */
    { "AllOrNone",              0x11, 0x08 }, /* since r1.0 */
    { "Body",                   0x11, 0x0a }, /* since r1.0 */
    { "Data",                   0x11, 0x0b }, /* since r1.0 */
    { "EstimatedDataSize",      0x11, 0x0c }, /* since r1.0 */
    { "Truncated",              0x11, 0x0d }, /* since r1.0 */
    { "Attachments",            0x11, 0x0e }, /* since r1.0 */
    { "Attachment",             0x11, 0x0f }, /* since r1.0 */
    { "DisplayName",            0x11, 0x10 }, /* since r1.0 */
    { "FileReference",          0x11, 0x11 }, /* since r1.0 */
    { "Method",                 0x11, 0x12 }, /* since r1.0 */
    { "ContentId",              0x11, 0x13 }, /* since r1.0 */
    { "ContentLocation",        0x11, 0x14 }, /* r8.0: not used */
    { "IsInline",               0x11, 0x15 }, /* since r1.0 */
    { "NativeBodyType",         0x11, 0x16 }, /* since r1.0 */
    { "ContentType",            0x11, 0x17 }, /* since r1.0 */
    { "Preview",                0x11, 0x18 }, /* r8.0: not supported when the MS-ASProtocolVersion header is set to 12.1 */
    { "BodyPartPreference",     0x11, 0x19 }, /* r8.0: not supported when the MS-ASProtocolVersion header is set to 12.1 or 14 */
    { "BodyPart",               0x11, 0x1a }, /* r8.0: not supported when the MS-ASProtocolVersion header is set to 12.1 or 14 */
    { "Status",                 0x11, 0x1b }, /* r8.0: not supported when the MS-ASProtocolVersion header is set to 12.1 or 14 */

    /* Code Page: Settings (since v12.1 and r1.0) */
    { "Settings",                   0x12, 0x05 }, /* since r1.0 */
    { "Status",                     0x12, 0x06 }, /* since r1.0 */
    { "Get",                        0x12, 0x07 }, /* since r1.0 */
    { "Set",                        0x12, 0x08 }, /* since r1.0 */
    { "Oof",                        0x12, 0x09 }, /* since r1.0 */
    { "OofState",                   0x12, 0x0a }, /* since r1.0 */
    { "StartTime",                  0x12, 0x0b }, /* since r1.0 */
    { "EndTime",                    0x12, 0x0c }, /* since r1.0 */
    { "OofMessage",                 0x12, 0x0d }, /* since r1.0 */
    { "AppliesToInternal",          0x12, 0x0e }, /* since r1.0 */
    { "AppliesToExternalKnown",     0x12, 0x0f }, /* since r1.0 */
    { "AppliesToExternalUnknown",   0x12, 0x10 }, /* since r1.0 */
    { "Enabled",                    0x12, 0x11 }, /* since r1.0 */
    { "ReplyMessage",               0x12, 0x12 }, /* since r1.0 */
    { "BodyType",                   0x12, 0x13 }, /* since r1.0 */
    { "DevicePassword",             0x12, 0x14 }, /* since r1.0 */
    { "Password",                   0x12, 0x15 }, /* since r1.0 */
    { "DeviceInformation",          0x12, 0x16 }, /* since r1.0 */
    { "Model",                      0x12, 0x17 }, /* since r1.0 */
    { "IMEI",                       0x12, 0x18 }, /* since r1.0 */
    { "FriendlyName",               0x12, 0x19 }, /* since r1.0 */
    { "OS",                         0x12, 0x1a }, /* since r1.0 */
    { "OSLanguage",                 0x12, 0x1b }, /* since r1.0 */
    { "PhoneNumber",                0x12, 0x1c }, /* since r1.0 */
    { "UserInformation",            0x12, 0x1d }, /* since r1.0 */
    { "EmailAddresses",             0x12, 0x1e }, /* since r1.0 */
    { "SmtpAddress",                0x12, 0x1f }, /* since r1.0 */
    { "UserAgent",                  0x12, 0x20 }, /* since r8.0? */
    { "EnableOutboundSMS",          0x12, 0x21 }, /* r8.0: not supported when the MS-ASProtocolVersion header is set to 12.1 */
    { "MobileOperator",             0x12, 0x22 }, /* r8.0: not supported when the MS-ASProtocolVersion header is set to 12.1 */
    { "PrimarySmtpAddress",         0x12, 0x23 }, /* r8.0: not supported when the MS-ASProtocolVersion header is set to 14.0 or 12.1 */
    { "Accounts",                   0x12, 0x24 }, /* r8.0: not supported when the MS-ASProtocolVersion header is set to 14.0 or 12.1 */
    { "Account",                    0x12, 0x25 }, /* r8.0: not supported when the MS-ASProtocolVersion header is set to 14.0 or 12.1 */
    { "AccountId",                  0x12, 0x26 }, /* r8.0: not supported when the MS-ASProtocolVersion header is set to 14.0 or 12.1 */
    { "AccountName",                0x12, 0x27 }, /* r8.0: not supported when the MS-ASProtocolVersion header is set to 14.0 or 12.1 */
    { "UserDisplayName",            0x12, 0x28 }, /* r8.0: not supported when the MS-ASProtocolVersion header is set to 14.0 or 12.1 */
    { "SendDisabled",               0x12, 0x29 }, /* r8.0: not supported when the MS-ASProtocolVersion header is set to 14.0 or 12.1 */
    { "ihsManagementInformation",   0x12, 0x2b }, /* r8.0: not supported when the MS-ASProtocolVersion header is set to 14.0 or 12.1 */

    /* Code Page: DocumentLibrary (since v12.1 and r1.0) */
    { "LinkId",             0x13, 0x05 }, /* since r1.0 */
    { "DisplayName",        0x13, 0x06 }, /* since r1.0 */
    { "IsFolder",           0x13, 0x07 }, /* since r1.0 */
    { "CreationDate",       0x13, 0x08 }, /* since r1.0 */
    { "LastModifiedDate",   0x13, 0x09 }, /* since r1.0 */
    { "IsHidden",           0x13, 0x0a }, /* since r1.0 */
    { "ContentLength",      0x13, 0x0b }, /* since r1.0 */
    { "ContentType",        0x13, 0x0c }, /* since r1.0 */

    /* Code Page: ItemOperations (since v12.1 and r1.0) */
    { "ItemOperations",      0x14, 0x05 }, /* since r1.0 */
    { "Fetch",               0x14, 0x06 }, /* since r1.0 */
    { "Store",               0x14, 0x07 }, /* since r1.0 */
    { "Options",             0x14, 0x08 }, /* since r1.0 */
    { "Range",               0x14, 0x09 }, /* since r1.0 */
    { "Total",               0x14, 0x0a }, /* since r1.0 */
    { "Properties",          0x14, 0x0b }, /* since r1.0 */
    { "Data",                0x14, 0x0c }, /* since r1.0 */
    { "Status",              0x14, 0x0d }, /* since r1.0 */
    { "Response",            0x14, 0x0e }, /* since r1.0 */
    { "Version",             0x14, 0x0f }, /* since r1.0 */
    { "Schema",              0x14, 0x10 }, /* since r1.0 */
    { "Part",                0x14, 0x11 }, /* since r1.0 */
    { "EmptyFolderContents", 0x14, 0x12 }, /* since r1.0 */
    { "DeleteSubFolders",    0x14, 0x13 }, /* since r1.0 */
    { "UserName",            0x14, 0x14 }, /* since r8.0? */
    { "Password",            0x14, 0x15 }, /* since r8.0? */
    { "Move",                0x14, 0x16 }, /* r8.0: not supported when the MS-ASProtocolVersion header is set to 12.1 */
    { "DstFldId",            0x14, 0x17 }, /* r8.0: not supported when the MS-ASProtocolVersion header is set to 12.1 */
    { "ConversationId",      0x14, 0x18, WBXML_TAG_OPTION_BINARY }, /* r8.0: not supported when the MS-ASProtocolVersion header is set to 12.1 */
    { "MoveAlways",          0x14, 0x19 }, /* r8.0: not supported when the MS-ASProtocolVersion header is set to 12.1 */

    /* Code Page: ComposeMail (since v14.0 and r8.0?) */
    /* r8.0: not supported when the MS-ASProtocolVersion header is set to 12.1 */
    { "SendMail",               0x15, 0x05 }, /* since r8.0? */
    { "SmartForward",           0x15, 0x06 }, /* since r8.0? */
    { "SmartReply",             0x15, 0x07 }, /* since r8.0? */
    { "SaveInSentItems",        0x15, 0x08 }, /* since r8.0? */
    { "ReplaceMime",            0x15, 0x09 }, /* since r8.0? */
    { "Source",                 0x15, 0x0b }, /* since r8.0? */
    { "FolderId",               0x15, 0x0c }, /* since r8.0? */
    { "ItemId",                 0x15, 0x0d }, /* since r8.0? */
    { "LongId",                 0x15, 0x0e }, /* since r8.0? */
    { "InstanceId",             0x15, 0x0f }, /* since r8.0? */
    { "MIME",                   0x15, 0x10, WBXML_TAG_OPTION_BINARY }, /* since r8.0? */
    { "ClientId",               0x15, 0x11 }, /* since r8.0? */
    { "Status",                 0x15, 0x12 }, /* since r8.0? */
    { "AccountId",              0x15, 0x13 }, /* r8.0: not supported when the MS-ASProtocolVersion header is set to 14.0 or 12.1 */

    /* Code Page: Email2 (since v14.0 and r8.0?) */
    /* r8.0: not supported when the MS-ASProtocolVersion header is set to 12.1 */
    { "UmCallerID",             0x16, 0x05 }, /* since r8.0? */
    { "UmUserNotes",            0x16, 0x06 }, /* since r8.0? */
    { "UmAttDuration",          0x16, 0x07 }, /* since r8.0? */
    { "UmAttOrder",             0x16, 0x08 }, /* since r8.0? */
    { "ConversationId",         0x16, 0x09, WBXML_TAG_OPTION_BINARY }, /* since r8.0? */
    { "ConversationIndex",      0x16, 0x0a, WBXML_TAG_OPTION_BINARY }, /* since r8.0? */
    { "LastVerbExecuted",       0x16, 0x0b }, /* since r8.0? */
    { "LastVerbExecutionTime",  0x16, 0x0c }, /* since r8.0? */
    { "ReceivedAsBcc",          0x16, 0x0d }, /* since r8.0? */
    { "Sender",                 0x16, 0x0e }, /* since r8.0? */
    { "CalendarType",           0x16, 0x0f }, /* since r8.0? */
    { "IsLeapMonth",            0x16, 0x10 }, /* since r8.0? */
    { "AccountId",              0x16, 0x11 }, /* r8.0: not supported when the MS-ASProtocolVersion header is set to 14.0 or 12.1 */
    { "FirstDayOfWeek",         0x16, 0x12 }, /* r8.0: not supported when the MS-ASProtocolVersion header is set to 14.0 or 12.1 */
    { "MeetingMessageType",     0x16, 0x13 }, /* r8.0: not supported when the MS-ASProtocolVersion header is set to 14.0 or 12.1 */

    /* Code Page: Notes (since v14.0 and r8.0?) */
    /* r8.0: not supported when the MS-ASProtocolVersion header is set to 12.1 */
    { "Subject",                0x17, 0x05 }, /* since r8.0? */
    { "MessageClass",           0x17, 0x06 }, /* since r8.0? */
    { "LastModifiedDate",       0x17, 0x07 }, /* since r8.0? */
    { "Categories",             0x17, 0x08 }, /* since r8.0? */
    { "Category",               0x17, 0x09 }, /* since r8.0? */

    /* Code Page: RightsManagement (since r8.0?) */
    /* r8.0: not supported when the MS-ASProtocolVersion header is set to 14.0 or 12.1 */
    { "RightsManagementSupport",0x18, 0x05 }, /* since r8.0? */
    { "RightsManagementTemplates",0x18, 0x06 }, /* since r8.0? */
    { "RightsManagementTemplate",0x18, 0x07 }, /* since r8.0? */
    { "RightsManagementLicense",0x18, 0x08 }, /* since r8.0? */
    { "EditAllowed",            0x18, 0x09 }, /* since r8.0? */
    { "ReplyAllowed",           0x18, 0x0a }, /* since r8.0? */
    { "ReplyAllAllowed",        0x18, 0x0b }, /* since r8.0? */
    { "ForwardAllowed",         0x18, 0x0c }, /* since r8.0? */
    { "ModifyRecipientsAllowed",0x18, 0x0d }, /* since r8.0? */
    { "ExtractAllowed",         0x18, 0x0e }, /* since r8.0? */
    { "PrintAllowed",           0x18, 0x0f }, /* since r8.0? */
    { "ExportAllowed",          0x18, 0x10 }, /* since r8.0? */
    { "ProgrammaticAccessAllowed",0x18, 0x11 }, /* since r8.0? */
    { "RMOwner",                0x18, 0x12 }, /* since r8.0? */
    { "ContentExpiryDate",      0x18, 0x13 }, /* since r8.0? */
    { "TemplateID",             0x18, 0x14 }, /* since r8.0? */
    { "TemplateName",           0x18, 0x15 }, /* since r8.0? */
    { "TemplateDescription",    0x18, 0x16 }, /* since r8.0? */
    { "ContentOwner",           0x18, 0x17 }, /* since r8.0? */
    { "RemoveRightsManagementDistribution",0x18, 0x18 }, /* since r8.0? */

    { NULL,                  0x00, 0x00 }
};

const WBXMLAttrEntry sv_airsync_attr_table[] = {
    { "Version", "1.1", 0x03, 0x05 }, /* not defined in r8.0 but in r1.0, supported by v2.5, v12.0 and v12.1 */
    { NULL,      NULL,  0x00, 0x00 }
};

/* NOTE:
 * These namespace names differ from the Microsoft-assigned namespaces.  The
 * reason for the difference is that the Microsoft-assigned names are not
 * valid URI's and hence produce warning messages when processed by some
 * libraries.  The mapping is as follows:
 * 
 *   Microsoft	          Ours
 *   ---------            ----
 *   AirSync:             http://synce.org/formats/airsync_wm5/airsync
 *   Contacts:            http://synce.org/formats/airsync_wm5/contacts
 *   Email:               http://synce.org/formats/airsync_wm5/email
 *   AirNotify:           http://synce.org/formats/airsync_wm5/airnotify
 *   Calendar:            http://synce.org/formats/airsync_wm5/calendar
 *   Move:                http://synce.org/formats/airsync_wm5/move
 *   ItemEstimate:        http://synce.org/formats/airsync_wm5/itemestimate
 *   FolderHierarchy:     http://synce.org/formats/airsync_wm5/folderhierarchy
 *   MeetingResponse:     http://synce.org/formats/airsync_wm5/meetingresponse
 *   Tasks:               http://synce.org/formats/airsync_wm5/tasks
 *   ResolveRecipients:   http://synce.org/formats/airsync_wm5/resolverecipients
 *   ValidateCert:        http://synce.org/formats/airsync_wm5/validatecert
 *   Contacts2:           http://synce.org/formats/airsync_wm5/contacts2
 *   Ping:                http://synce.org/formats/airsync_wm5/ping
 *   Provision:           http://synce.org/formats/airsync_wm5/provision
 *   Search:              http://synce.org/formats/airsync_wm5/search
 *   Gal:                 http://synce.org/formats/airsync_wm5/gal
 *   AirSyncBase:         http://synce.org/formats/airsync_wm5/airsyncbase
 *   Settings:            http://synce.org/formats/airsync_wm5/settings
 *   DocumentLibrary:     http://synce.org/formats/airsync_wm5/documentlibrary
 *   ItemOperations:      http://synce.org/formats/airsync_wm5/itemoperations
 *   ComposeMail:         http://synce.org/formats/airsync_wm5/composemail
 *   Email2:              http://synce.org/formats/airsync_wm5/email2
 *   Notes:               http://synce.org/formats/airsync_wm5/notes
 *   RightsManagement:    http://synce.org/formats/airsync_wm5/rightsmanagement
 *
 */
const WBXMLNameSpaceEntry sv_airsync_ns_table[] = {
    { "http://synce.org/formats/airsync_wm5/airsync",           0x00 },     /**< Code Page 0 */
    { "http://synce.org/formats/airsync_wm5/contacts",          0x01 },     /**< Code Page 1 */
    { "http://synce.org/formats/airsync_wm5/email",             0x02 },     /**< Code Page 2 */
    { "http://synce.org/formats/airsync_wm5/airnotify",         0x03 },     /**< Code Page 3 */
    { "http://synce.org/formats/airsync_wm5/calendar",          0x04 },     /**< Code Page 4 */
    { "http://synce.org/formats/airsync_wm5/move",              0x05 },     /**< Code Page 5 */
    { "http://synce.org/formats/airsync_wm5/itemestimate",      0x06 },     /**< Code Page 6 */
    { "http://synce.org/formats/airsync_wm5/folderhierarchy",   0x07 },     /**< Code Page 7 */
    { "http://synce.org/formats/airsync_wm5/meetingresponse",   0x08 },     /**< Code Page 8 */
    { "http://synce.org/formats/airsync_wm5/tasks",             0x09 },     /**< Code Page 9 */
    { "http://synce.org/formats/airsync_wm5/resolverecipients", 0x0a },     /**< Code Page 10 */
    { "http://synce.org/formats/airsync_wm5/validatecert",      0x0b },     /**< Code Page 11 */
    { "http://synce.org/formats/airsync_wm5/contacts2",         0x0c },     /**< Code Page 12 */
    { "http://synce.org/formats/airsync_wm5/ping",              0x0d },     /**< Code Page 13 */
    { "http://synce.org/formats/airsync_wm5/provision",         0x0e },     /**< Code Page 14 */
    { "http://synce.org/formats/airsync_wm5/search",            0x0f },     /**< Code Page 15 */
    { "http://synce.org/formats/airsync_wm5/gal",               0x10 },     /**< Code Page 16 */
    { "http://synce.org/formats/airsync_wm5/airsyncbase",       0x11 },     /**< Code Page 17 */
    { "http://synce.org/formats/airsync_wm5/settings",          0x12 },     /**< Code Page 18 */
    { "http://synce.org/formats/airsync_wm5/documentlibrary",   0x13 },     /**< Code Page 19 */
    { "http://synce.org/formats/airsync_wm5/itemoperations",    0x14 },     /**< Code Page 20 */
    { "http://synce.org/formats/airsync_wm5/composemail",       0x15 },     /**< Code Page 21 */
    { "http://synce.org/formats/airsync_wm5/email2",            0x16 },     /**< Code Page 22 */
    { "http://synce.org/formats/airsync_wm5/notes",             0x17 },     /**< Code Page 23 */
    { "http://synce.org/formats/airsync_wm5/rightsmanagement",  0x18 },     /**< Code Page 24 */
    { NULL,                                                     0x00 }
};

const WBXMLNameSpaceEntry sv_activesync_ns_table[] = {
    { "AirSync:",           0x00 },     /**< Code Page 0 */
    { "Contacts:",          0x01 },     /**< Code Page 1 */
    { "Email:",             0x02 },     /**< Code Page 2 */
    { "AirNotify:",         0x03 },     /**< Code Page 3 */
    { "Calendar:",          0x04 },     /**< Code Page 4 */
    { "Move:",              0x05 },     /**< Code Page 5 */
    { "GetItemEstimate:",   0x06 },     /**< Code Page 6 */
    { "FolderHierarchy:",   0x07 },     /**< Code Page 7 */
    { "MeetingResponse:",   0x08 },     /**< Code Page 8 */
    { "Tasks:",             0x09 },     /**< Code Page 9 */
    { "ResolveRecipients:", 0x0a },     /**< Code Page 10 */
    { "ValidateCert:",      0x0b },     /**< Code Page 11 */
    { "Contacts2:",         0x0c },     /**< Code Page 12 */
    { "Ping:",              0x0d },     /**< Code Page 13 */
    { "Provision:",         0x0e },     /**< Code Page 14 */
    { "Search:",            0x0f },     /**< Code Page 15 */
    { "Gal:",               0x10 },     /**< Code Page 16 */
    { "AirSyncBase:",       0x11 },     /**< Code Page 17 */
    { "Settings:",          0x12 },     /**< Code Page 18 */
    { "DocumentLibrary:",   0x13 },     /**< Code Page 19 */
    { "ItemOperations:",    0x14 },     /**< Code Page 20 */
    { "ComposeMail:",       0x15 },     /**< Code Page 21 */
    { "Email2:",            0x16 },     /**< Code Page 22 */
    { "Notes:",             0x17 },     /**< Code Page 23 */
    { "RightsManagement:",  0x18 },     /**< Code Page 24 */
    { NULL,                 0x00 }
};

#endif /* WBXML_SUPPORT_AIRSYNC */


#if defined( WBXML_SUPPORT_CONML )

/*************************************************
 *    Nokia ConML
 *
 *    This is no official markup language from Nokia.
 *    It is used for example by Nokia PC Suite to install software.
 */
 
const WBXMLTagEntry sv_conml_tag_table[] = {
    /* Code Page: "ConML" */
    { "All",                  0x00, 0x05 },
    { "Application",          0x00, 0x06 },
    { "Applications",         0x00, 0x07 },
    { "Unknown_0x08",         0x00, 0x08 },
    { "Cancel",               0x00, 0x09 },
    { "Complete",             0x00, 0x0a },
    { "ConML",                0x00, 0x0b },
    { "Data",                 0x00, 0x0c },
    /* Candidates from SyncML:
         DataType     *
         DefaultValue
         Delete
         Description  *
         DevID        *
     */
    { "Unknown_0x0d",         0x00, 0x0d },
    { "Unknown_0x0e",         0x00, 0x0e },
    { "Unknown_0x0f",         0x00, 0x0f },
    { "DeviceInfo",           0x00, 0x10 },
    /* Candidates from SyncML:
         DevTyp
     */
    { "Unknown_0x11",         0x00, 0x11 },
    { "Drives",               0x00, 0x12 },
    { "Execute",              0x00, 0x13 },
    /* Candidates from SyncML:
         Final
     */
    { "Unknown_0x14",         0x00, 0x14 },
    { "Unknown_0x15",         0x00, 0x15 },
    { "Unknown_0x16",         0x00, 0x16 },
    { "GetDataSize",          0x00, 0x17 },
    { "GetStatus",            0x00, 0x18 },
    { "HasFiles",             0x00, 0x19 },
    { "ID",                   0x00, 0x1a },
    { "IncType",              0x00, 0x1b },
    { "Install",              0x00, 0x1c },
    { "InstParams",           0x00, 0x1d },
    { "ListInstalledApps",    0x00, 0x1f },
    /* Candidates from SyncML:
         MaxMsgSize
     */
    { "Unknown_0x20",         0x00, 0x20 },
    { "MaxObjectSize",        0x00, 0x21 },
    { "Modified",             0x00, 0x22 },
    { "MoreData",             0x00, 0x23 },
    /* The content of the element Name is originally encoded as opaque data.
       The mobiles accepts the element data also as a normal string.
       Therefore the data will be encoded as a string.
       If there is a requirement for the original behavior
       then it is necessary to add some code to wbxml_encoder.c.
     */
    { "Name",                 0x00, 0x24 },
    { "PackageInfo",          0x00, 0x25 },
    { "Param",                0x00, 0x26 },
    { "PartialType",          0x00, 0x27 },
    { "Progress",             0x00, 0x28 },
    { "Reboot",               0x00, 0x29 },
    /* Candidates from SyncML:
         Replace
         RespURI
     */
    { "Unknown_0x2a",         0x00, 0x2a },
    { "Unknown_0x2b",         0x00, 0x2b },
    { "Results",              0x00, 0x2c },
    /* Candidates from SyncML:
         Search
         Sequence
         SessionID
         SftDel
         Source
         SourceRef
     */
    { "Unknown_0x2d",         0x00, 0x2d },
    { "Unknown_0x2e",         0x00, 0x2e },
    { "Unknown_0x2f",         0x00, 0x2f },
    { "Unknown_0x30",         0x00, 0x30 },
    { "Status",               0x00, 0x31 },
    /* Candidates from SyncML:
         Target
         TargetRef
     */
    { "Unknown_0x32",         0x00, 0x32 },
    { "Unknown_0x33",         0x00, 0x33 },
    { "Unknown_0x34",         0x00, 0x34 },
    { "Task",                 0x00, 0x35 },
    /* Candidates from SyncML:
         Time
         TStamp
         Title
     */
    { "Unknown_0x36",         0x00, 0x36 },
    { "Type",                 0x00, 0x37 },
    { "UID",                  0x00, 0x38 },
    { "UnInstall",            0x00, 0x39 },
    /* Candidates from SyncML:
         ValEnum
     */
    { "Unknown_0x3a",         0x00, 0x3a },
    { "Unknown_0x3b",         0x00, 0x3b },
    { "Value",                0x00, 0x3c },
    { "Version",              0x00, 0x3d },
    { NULL,                   0x00, 0x00 }
};

#endif /* WBXML_SUPPORT_CONML */


/******************************
 *    Main Table
 */

const WBXMLLangEntry sv_table_entry[] = {
#if defined( WBXML_SUPPORT_WML )
#ifdef WBXML_TABLES_SEPARATE_WML_VERSIONS    
    { WBXML_LANG_WML10,             &sv_wml10_public_id,            sv_wml10_tag_table,             NULL,                           sv_wml10_attr_table,        sv_wml10_attr_value_table,      NULL },
    { WBXML_LANG_WML11,             &sv_wml11_public_id,            sv_wml11_tag_table,             NULL,                           sv_wml11_attr_table,        sv_wml11_attr_value_table,      NULL },
    { WBXML_LANG_WML12,             &sv_wml12_public_id,            sv_wml12_tag_table,             NULL,                           sv_wml12_attr_table,        sv_wml12_attr_value_table,      NULL },
#else /* WBXML_TABLES_SEPARATE_WML_VERSIONS */
    { WBXML_LANG_WML10,             &sv_wml10_public_id,            sv_wml13_tag_table,             NULL,                           sv_wml13_attr_table,        sv_wml13_attr_value_table,      NULL },
    { WBXML_LANG_WML11,             &sv_wml11_public_id,            sv_wml13_tag_table,             NULL,                           sv_wml13_attr_table,        sv_wml13_attr_value_table,      NULL },
    { WBXML_LANG_WML12,             &sv_wml12_public_id,            sv_wml13_tag_table,             NULL,                           sv_wml13_attr_table,        sv_wml13_attr_value_table,      NULL },
#endif /* WBXML_TABLES_SEPARATE_WML_VERSIONS */
    { WBXML_LANG_WML13,             &sv_wml13_public_id,            sv_wml13_tag_table,             NULL,                           sv_wml13_attr_table,        sv_wml13_attr_value_table,      NULL },
#endif /* WBXML_SUPPORT_WML */

#if defined( WBXML_SUPPORT_WTA )
    { WBXML_LANG_WTA10,             &sv_wta10_public_id,            sv_wta10_tag_table,             NULL,                           sv_wta10_attr_table,        NULL,                           NULL },
    { WBXML_LANG_WTAWML12,          &sv_wtawml12_public_id,         sv_wtawml12_tag_table,          NULL,                           sv_wtawml12_attr_table,     sv_wtawml12_attr_value_table,   NULL },
    { WBXML_LANG_CHANNEL11,         &sv_channel11_public_id,        sv_channel11_tag_table,         NULL,                           sv_channel11_attr_table,    NULL,                           NULL },
    { WBXML_LANG_CHANNEL12,         &sv_channel12_public_id,        sv_channel12_tag_table,         NULL,                           sv_channel12_attr_table,    NULL,                           NULL },
#endif /* WBXML_SUPPORT_WTA */

#if defined( WBXML_SUPPORT_SI )
    { WBXML_LANG_SI10,              &sv_si10_public_id,             sv_si10_tag_table,              NULL,                           sv_si10_attr_table,         sv_si10_attr_value_table,       NULL },
#endif /* WBXML_SUPPORT_SI */

#if defined( WBXML_SUPPORT_SL )
    { WBXML_LANG_SL10,              &sv_sl10_public_id,             sv_sl10_tag_table,              NULL,                           sv_sl10_attr_table,         sv_sl10_attr_value_table,       NULL },
#endif /* WBXML_SUPPORT_SL */

#if defined( WBXML_SUPPORT_CO )
    { WBXML_LANG_CO10,              &sv_co10_public_id,             sv_co10_tag_table,              NULL,                           sv_co10_attr_table,         sv_co10_attr_value_table,       NULL },
#endif /* WBXML_SUPPORT_CO */

#if defined( WBXML_SUPPORT_PROV )
    { WBXML_LANG_PROV10,            &sv_prov10_public_id,           sv_prov10_tag_table,            NULL,                           sv_prov10_attr_table,       sv_prov10_attr_value_table,     NULL }, 
#endif /* WBXML_SUPPORT_PROV */

#if defined( WBXML_SUPPORT_EMN )
    { WBXML_LANG_EMN10,             &sv_emn10_public_id,            sv_emn10_tag_table,             NULL,                           sv_emn10_attr_table,        sv_emn10_attr_value_table,      NULL },
#endif /* WBXML_SUPPORT_EMN */

#if defined( WBXML_SUPPORT_DRMREL )
    { WBXML_LANG_DRMREL10,          &sv_drmrel10_public_id,         sv_drmrel10_tag_table,          NULL,                           sv_drmrel10_attr_table,     sv_drmrel10_attr_value_table,   NULL },
#endif /* WBXML_SUPPORT_DRMREL */

#if defined( WBXML_SUPPORT_OTA_SETTINGS )
    { WBXML_LANG_OTA_SETTINGS,      &sv_ota_settings_public_id,     sv_ota_settings_tag_table,      NULL,                           sv_ota_settings_attr_table, NULL,                           NULL },
#endif /* WBXML_SUPPORT_OTA_SETTINGS */

#if defined( WBXML_SUPPORT_SYNCML )
    /* SyncML 1.2 */
    { WBXML_LANG_SYNCML_SYNCML12,   &sv_syncml_syncml12_public_id,  sv_syncml_syncml12_tag_table,   sv_syncml_syncml12_ns_table,    NULL,                       NULL,                           NULL },
    { WBXML_LANG_SYNCML_DEVINF12,   &sv_syncml_devinf12_public_id,  sv_syncml_devinf12_tag_table,   sv_syncml_devinf12_ns_table,    NULL,                       NULL,                           NULL },
    { WBXML_LANG_SYNCML_METINF12,   &sv_syncml_metinf12_public_id,  sv_syncml_metinf12_tag_table,   NULL,                           NULL,                       NULL,                           NULL },
    { WBXML_LANG_SYNCML_DMDDF12,    &sv_syncml_dmddf12_public_id,   sv_syncml_dmddf12_tag_table,    sv_syncml_dmddf12_ns_table,     NULL,                       NULL,                           NULL },

    /* SyncML 1.1 */
    { WBXML_LANG_SYNCML_SYNCML11,   &sv_syncml_syncml11_public_id,  sv_syncml_syncml11_tag_table,   sv_syncml_syncml11_ns_table,    NULL,                       NULL,                           NULL },
    { WBXML_LANG_SYNCML_DEVINF11,   &sv_syncml_devinf11_public_id,  sv_syncml_devinf11_tag_table,   sv_syncml_devinf11_ns_table,    NULL,                       NULL,                           NULL },
    { WBXML_LANG_SYNCML_METINF11,   &sv_syncml_metinf11_public_id,  sv_syncml_metinf11_tag_table,   NULL,                           NULL,                       NULL,                           NULL },
    
    /** @todo Check if Tag Tables are exactly with SyncML 1.0 */
    { WBXML_LANG_SYNCML_SYNCML10,   &sv_syncml_syncml10_public_id,  sv_syncml_syncml11_tag_table,   sv_syncml_syncml10_ns_table,    NULL,                       NULL,                           NULL },
    { WBXML_LANG_SYNCML_DEVINF10,   &sv_syncml_devinf10_public_id,  sv_syncml_devinf11_tag_table,   sv_syncml_devinf11_ns_table,    NULL,                       NULL,                           NULL },   
#endif /* WBXML_SUPPORT_SYNCML */

#if defined( WBXML_SUPPORT_WV )
    { WBXML_LANG_WV_CSP11,          &sv_wv_csp11_public_id,         sv_wv_csp_tag_table,            NULL,                           sv_wv_csp_attr_table,       NULL,                           sv_wv_csp_ext_table },
    { WBXML_LANG_WV_CSP12,          &sv_wv_csp12_public_id,         sv_wv_csp_tag_table,            NULL,                           sv_wv_csp_attr_table,       NULL,                           sv_wv_csp_ext_table },
#endif /* WBXML_SUPPORT_WV */

#if defined( WBXML_SUPPORT_AIRSYNC )
    { WBXML_LANG_AIRSYNC,           &sv_airsync_public_id,          sv_airsync_tag_table,           sv_airsync_ns_table,            sv_airsync_attr_table,                       NULL,                           NULL },
    { WBXML_LANG_ACTIVESYNC,        &sv_activesync_public_id,       sv_airsync_tag_table,           sv_activesync_ns_table,         sv_airsync_attr_table,                       NULL,                           NULL },
#endif /* WBXML_SUPPORT_AIRSYNC */

#if defined( WBXML_SUPPORT_CONML )
    { WBXML_LANG_CONML,             &sv_conml_public_id,            sv_conml_tag_table,             NULL,                           NULL,                       NULL,                           NULL },
#endif /* WBXML_SUPPORT_CONML */

    { WBXML_LANG_UNKNOWN,           NULL,                           NULL,                           NULL,                           NULL,                       NULL,                           NULL }
};


/******************************
 * Public Functions
 */

/* Exported function to return pointer to WBXML Languages Main Table */
WBXML_DECLARE(const WBXMLLangEntry *) wbxml_tables_get_main(void)
{
    return sv_table_entry;
}


WBXML_DECLARE(const WBXMLLangEntry *) wbxml_tables_get_table(WBXMLLanguage lang)
{
    const WBXMLLangEntry *main_table = NULL;
    WB_ULONG index = 0;
    
    /* Get main tables array*/
    if ((lang == WBXML_LANG_UNKNOWN) || ((main_table = wbxml_tables_get_main()) == NULL))
        return NULL;
    
    /* Search language table */
    while (main_table[index].langID != WBXML_LANG_UNKNOWN) {
        if (main_table[index].langID == lang)
            return &main_table[index];
        index++;
    }

    return NULL;
}


WBXML_DECLARE(const WBXMLLangEntry *) wbxml_tables_search_table(const WBXMLLangEntry *main_table,
                                                                const WB_UTINY *public_id, 
                                                                const WB_UTINY *system_id,
                                                                const WB_UTINY *root)
{
    WB_ULONG index;
    const WB_UTINY *sep = NULL;

    if (main_table == NULL)
        return NULL;

    /* Search by XML Public ID  */
    if (public_id != NULL) {
        index = 0;

        while (main_table[index].publicID != NULL) {
            if (main_table[index].publicID->xmlPublicID && WBXML_STRCASECMP(main_table[index].publicID->xmlPublicID, public_id) == 0)
                return &main_table[index];
            index++;
        }
    }

    /* Search by XML System ID  */
    if (system_id != NULL) {
        index = 0;

        while (main_table[index].publicID != NULL) {
            if (main_table[index].publicID->xmlDTD && WBXML_STRCMP(main_table[index].publicID->xmlDTD, system_id) == 0) 
                return &main_table[index];
            index++;
        }
    }

    /* Search by XML Root Element  */
    if (root != NULL) {
        index = 0;

        /* table scan for matching namespace element */
        sep = (WB_UTINY *)strrchr((const WB_TINY *) root, WBXML_NAMESPACE_SEPARATOR);
        if (sep != NULL) {
            /* There is a namespace (from root to sep). */
            while (main_table[index].publicID != NULL) {
                /* It is only possible to evaluate the first entry in the table
                 * because the second code page has often no unique name space name.
                 * Example: SyncML Meta Information => syncml:metinf
                 */
                if (main_table[index].nsTable != NULL &&
                    main_table[index].nsTable[0].xmlNameSpace && 
                    WBXML_STRNCASECMP(main_table[index].nsTable[0].xmlNameSpace, root, WBXML_STRLEN(main_table[index].nsTable[0].xmlNameSpace)) == 0) 
                    return &main_table[index];
                index++;
            }
        }

        /* table scan for matching root element */
        while (main_table[index].publicID != NULL) {
            if (main_table[index].publicID->xmlRootElt && WBXML_STRCMP(main_table[index].publicID->xmlRootElt, root) == 0) 
                return &main_table[index];
            index++;
        }
    }

    return NULL;
}


WBXML_DECLARE(WB_ULONG) wbxml_tables_get_wbxml_publicid(const WBXMLLangEntry *main_table, WBXMLLanguage lang_id)
{
    WB_ULONG i = 0;

    if (main_table == NULL)
        return WBXML_PUBLIC_ID_UNKNOWN;

    while (main_table[i].langID != WBXML_LANG_UNKNOWN) {
        if (main_table[i].langID == lang_id) {
            if (main_table[i].publicID != NULL)
                return main_table[i].publicID->wbxmlPublicID;
            else
                return WBXML_PUBLIC_ID_UNKNOWN;
        }
        i++;
    }

    return WBXML_PUBLIC_ID_UNKNOWN;
}


WBXML_DECLARE(const WBXMLTagEntry *) wbxml_tables_get_tag_from_xml(const WBXMLLangEntry *lang_table,
                                                                   const int cur_code_page,
                                                                   const WB_UTINY *xml_name)
{
    WB_ULONG i;
    WB_BOOL found_current = FALSE;

    if ((lang_table == NULL) || (lang_table->tagTable == NULL) || (xml_name == NULL))
        return NULL;

    /* First off, try to find it in the current code page, if provided */
    for (i = 0; cur_code_page >= 0 && lang_table->tagTable[i].xmlName != NULL; i++) {
        const WBXMLTagEntry *entry = &lang_table->tagTable[i];

        if (entry->wbxmlCodePage == cur_code_page) {
            found_current = TRUE;

            if (WBXML_STRCMP(entry->xmlName, xml_name) == 0)
                return entry;
        } else {
            if (found_current)
              break;
        }
    }

    /* Then try all others */
    for (i = 0; lang_table->tagTable[i].xmlName != NULL; i++) {
        const WBXMLTagEntry *entry = &lang_table->tagTable[i];

        /* We've already searched the current code page */
        if (cur_code_page >= 0 && entry->wbxmlCodePage == cur_code_page)
          continue;

        if (WBXML_STRCMP(entry->xmlName, xml_name) == 0)
            return entry;
    }

    return NULL;
}


WBXML_DECLARE(const WBXMLAttrEntry *) wbxml_tables_get_attr_from_xml(const WBXMLLangEntry *lang_table,
                                                                     WB_UTINY *xml_name,
                                                                     WB_UTINY *xml_value,
                                                                     WB_UTINY **value_left)
{
    WB_ULONG i = 0;
    WB_ULONG found_index = 0, found_comp = 0;
    WB_BOOL found = FALSE;

    if ((lang_table == NULL) || (lang_table->attrTable == NULL) || (xml_name == NULL))
        return NULL;

    if (value_left != NULL)
        *value_left = xml_value;

    /* Iterate in Attribute Table */
    while (lang_table->attrTable[i].xmlName != NULL) {
        /* Search for Attribute Name */
        if (WBXML_STRCMP(lang_table->attrTable[i].xmlName, xml_name) == 0) 
        {
            if (lang_table->attrTable[i].xmlValue == NULL) {
                /* This is the token with a NULL Attribute Value */
                if (xml_value == NULL) {
                    /* Well, we got it */
                    return &(lang_table->attrTable[i]);
                }
                else {
                    if (!found) {
                        /* We haven't found yet a better Attribute Token */
                        found = TRUE;
                        found_index = i;
                    }

                    /* Else: We already have found a better Attribute Token, so let's forget this one */
                }
            }
            else {
                /* Check the Attribute Value */
                if (xml_value != NULL)
                {
                    if (WBXML_STRCMP(lang_table->attrTable[i].xmlValue, xml_value) == 0) 
                    {
                        /* We have found the EXACT Attribute Name / Value pair we are searching, well done boy */
                        if (value_left != NULL)
                            *value_left = NULL;

                        return &(lang_table->attrTable[i]);
                    }
                    else {
                        if ((WBXML_STRLEN(lang_table->attrTable[i].xmlValue) < WBXML_STRLEN(xml_value)) &&
                            (found_comp < WBXML_STRLEN(lang_table->attrTable[i].xmlValue)) &&
                            (WBXML_STRNCMP(lang_table->attrTable[i].xmlValue, xml_value, WBXML_STRLEN(lang_table->attrTable[i].xmlValue)) == 0))
                        {
                            /* We have found a better Attribute Value */
                            found = TRUE;
                            found_index = i;
                            found_comp = WBXML_STRLEN(lang_table->attrTable[i].xmlValue);
                        }
                    }
                }

                /* Else: We are searching for the Attribute Token with a NULL Attribute Value associated, so forget this one  */
            }
        }
        i++;
    }

    /* Attribute Name / Value pair not found, but an entry with this Attribute Name, 
     * and (maybe) start of this Attribute Value was found */
    if (found) {
        if (value_left != NULL)
            *value_left = xml_value + found_comp;

        return &(lang_table->attrTable[found_index]);
    }

    /* Attribute Name NOT found */
    return NULL;
}


WBXML_DECLARE(const WBXMLExtValueEntry *) wbxml_tables_get_ext_from_xml(const WBXMLLangEntry *lang_table,
                                                                        WB_UTINY *xml_value)
{
    WB_ULONG i = 0;

    if ((lang_table == NULL) || (lang_table->extValueTable == NULL) || (xml_value == NULL))
        return NULL;

    while (lang_table->extValueTable[i].xmlName != NULL) {
        if (WBXML_STRCMP(lang_table->extValueTable[i].xmlName, xml_value) == 0)
            return &(lang_table->extValueTable[i]);
        i++;
    }

    return NULL;
}


WBXML_DECLARE(WB_BOOL) wbxml_tables_contains_attr_value_from_xml(const WBXMLLangEntry *lang_table,
                                                                 WB_UTINY *xml_value)
{
    WB_ULONG i = 0;

    if ((lang_table == NULL) || (lang_table->attrValueTable == NULL) || (xml_value == NULL))
        return FALSE;

    while (lang_table->attrValueTable[i].xmlName != NULL)
    {
        /* Is this Attribute Value contained in this XML Buffer ? */
        if (WBXML_STRSTR(xml_value, lang_table->attrValueTable[i].xmlName) != NULL)
            return TRUE;

        i++;
    }

    return FALSE;
}


WBXML_DECLARE(const WB_TINY *) wbxml_tables_get_xmlns(const WBXMLNameSpaceEntry *ns_table, WB_UTINY code_page)
{
    WB_ULONG i = 0;

    if (ns_table == NULL)
        return NULL;

    while (ns_table[i].xmlNameSpace != NULL)
    {
        if (ns_table[i].wbxmlCodePage == code_page)
            return ns_table[i].xmlNameSpace;

        i++;
    }

    return NULL;
}

WBXML_DECLARE(WB_UTINY) wbxml_tables_get_code_page(const WBXMLNameSpaceEntry *ns_table, const WB_TINY* xmlns)
{
    WB_ULONG i = 0;

    if (ns_table == NULL)
        return 0;

    while (ns_table[i].xmlNameSpace != NULL)
    {
        if (strcmp(ns_table[i].xmlNameSpace, xmlns) == 0)
            return ns_table[i].wbxmlCodePage;

        i++;
    }

    return 0;
}

