/*
 * libwbxml, the WBXML Library.
 * Copyright (C) 2002-2005 Aymerick Jehanne <aymerick@jehanne.org>
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
 * Contact: libwbxml@aymerick.com
 * Home: http://libwbxml.aymerick.com
 */
 
#if defined( WBXML_WRAPPERS ) && defined( WBXML_SUPPORT_SYNCML )
 
/**
 * @file wbxml_wrap_syncml.h
 * @ingroup wbxml_wrap
 *
 * @author Aymerick Jehanne <libwbxml@aymerick.com>
 * @date 05/03/08
 *
 * @brief SyncML Wrapper
 */

#ifndef WBXML_WRAP_SYNCML_H
#define WBXML_WRAP_SYNCML_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/** @addtogroup wbxml_wrap
 *  @{ 
 */

/****************************************************
 *  SyncML Constants
 */

/** SyncML VerDTD : 1.0 */
#define WBXML_SYNCML_VERDTD_STR_10 "1.0"

/** SyncML VerDTD : 1.1 */
#define WBXML_SYNCML_VERDTD_STR_11 "1.1"


/** SyncML VerProto : 1.0 */
#define WBXML_SYNCML_VERPROTO_STR_10 "SyncML/1.0"

/** SyncML VerProto : 1.1 */
#define WBXML_SYNCML_VERPROTO_STR_11 "SyncML/1.1"


/****************************************************
 *  SyncML Enums
 */

/** SyncML VerDTD */
typedef enum WBXMLSyncMLVerDTD_e {
    WBXML_SYNCML_VERDTD_UNKNOWN = 0, /**< UNKNOWN */
    WBXML_SYNCML_VERDTD_10,          /**< 1.0 */
    WBXML_SYNCML_VERDTD_11           /**< 1.1 */
} WBXMLSyncMLVerDTD;

/** SyncML VerProto */
typedef enum WBXMLSyncMLVerProto_e {
    WBXML_SYNCML_VERPROTO_UNKNOWN = 0, /**< UNKNOWN */
    WBXML_SYNCML_VERPROTO_10,          /**< SyncML/1.0 */
    WBXML_SYNCML_VERPROTO_11           /**< SyncML/1.1 */
} WBXMLSyncMLVerProto;

/** SyncML Command type */
typedef enum WBXMLSyncMLCmdType_e {
    WBXML_SYNCML_CMD_UNKNOWN = 0, /**< UNKNOWN */
    WBXML_SYNCML_CMD_ADD,         /**< Add */
    WBXML_SYNCML_CMD_ALERT,       /**< Alert */
    WBXML_SYNCML_CMD_ATOMIC,      /**< Atomic */
    WBXML_SYNCML_CMD_COPY,        /**< Copy */
    WBXML_SYNCML_CMD_DELETE,      /**< Delete */
    WBXML_SYNCML_CMD_EXEC,        /**< Exec */
    WBXML_SYNCML_CMD_GET,         /**< Get */
    WBXML_SYNCML_CMD_MAP,         /**< Map */
    WBXML_SYNCML_CMD_MOVE,        /**< Move */
    WBXML_SYNCML_CMD_PUT,         /**< Put */
    WBXML_SYNCML_CMD_REPLACE,     /**< Replace */
    WBXML_SYNCML_CMD_RESULTS,     /**< Results */
    WBXML_SYNCML_CMD_SEARCH,      /**< Search */
    WBXML_SYNCML_CMD_SEQUENCE,    /**< Sequence */
    WBXML_SYNCML_CMD_STATUS,      /**< Status */
    WBXML_SYNCML_CMD_SYNC         /**< Sync */
} WBXMLSyncMLCmdType;


/****************************************************
 *  SyncML Structures
 */

/**
 * @brief SyncML <Meta> element
 */
typedef struct WBXMLSyncMLMeta_s
{
    void *todo; /**< @todo Meta */
} WBXMLSyncMLMeta;

/**
 * @brief SyncML <Cred> element
 */
typedef struct WBXMLSyncMLCred_s
{
    WBXMLSyncMLMeta *Meta; /**< Meta? */
    WBXMLBuffer     *Data; /**< Data */
} WBXMLSyncMLCred;

/**
 * @brief SyncML <Chal> element
 */
typedef struct WBXMLSyncMLChal_s
{
    WBXMLSyncMLMeta *Meta; /**< Meta */
} WBXMLSyncMLChal;

/**
 * @brief SyncML <Item> element
 */
typedef struct WBXMLSyncMLItem_s {
    WBXMLBuffer     *Target;   /**< Target? */
    WBXMLBuffer     *Source;   /**< Source? */
    WBXMLSyncMLMeta *Meta;     /**< Meta? */
    WBXMLBuffer     *Data;     /**< Data? */
    WB_BOOL          MoreData; /**< MoreData? */
} WBXMLSyncMLItem;

/**
 * @brief SyncML <Add> element
 */
typedef struct WBXMLSyncMLAdd_s {
    WB_BOOL          NoResp; /**< NoResp? */
    WBXMLSyncMLCred *Cred;   /**< Cred? */
    WBXMLSyncMLMeta *Meta;   /**< Meta? */
    WBXMLList       *items;  /**< Item+ */
} WBXMLSyncMLAdd;

/**
 * @brief SyncML <Alert> element
 */
typedef struct WBXMLSyncMLAlert_s {
    WB_BOOL          NoResp; /**< NoResp? */
    WBXMLSyncMLCred *Cred;   /**< Cred? */
    WBXMLList       *items;  /**< Item* */
    WBXMLBuffer     *Data;   /**< Data? */
} WBXMLSyncMLAlert;

/**
 * @brief SyncML <Atomic> element
 */
typedef struct WBXMLSyncMLAtomic_s {
    WB_BOOL          NoResp;   /**< NoResp? */
    WBXMLSyncMLMeta *Meta;     /**< Meta? */
    WBXMLList       *commands; /**< (Add | Replace | Delete | Copy | Atomic | Map | Sequence | Sync | Get | Exec | Alert)+ */
} WBXMLSyncMLAtomic;

/**
 * @brief SyncML <Copy> element
 */
typedef struct WBXMLSyncMLCopy_s {
    WB_BOOL          NoResp; /**< NoResp? */
    WBXMLSyncMLCred *Cred;   /**< Cred? */
    WBXMLSyncMLMeta *Meta;   /**< Meta? */
    WBXMLList       *items;  /**< Item+ */
} WBXMLSyncMLCopy;

/**
 * @brief SyncML <Delete> element
 */
typedef struct WBXMLSyncMLDelete_s {
    WB_BOOL          NoResp;   /**< NoResp? */
    WBXMLSyncMLCred *Cred;     /**< Cred? */
    WBXMLSyncMLMeta *Meta;     /**< Meta? */
    WBXMLList       *items;    /**< Item+ */
    WB_BOOL          Archives; /**< Archive? */
    WB_BOOL          SftDel;   /**< SftDel? */
} WBXMLSyncMLDelete;

/**
 * @brief SyncML <Exec> element
 */
typedef struct WBXMLSyncMLExec_s {
    WB_BOOL          NoResp; /**< NoResp? */
    WBXMLSyncMLCred *Cred;   /**< Cred? */
    WBXMLSyncMLMeta *Meta;   /**< Meta? */
    WBXMLSyncMLItem  Item;   /**< Item */
} WBXMLSyncMLExec;

/**
 * @brief SyncML <Get> element
 */
typedef struct WBXMLSyncMLGet_s {
    WB_BOOL          NoResp; /**< NoResp? */
    WBXMLSyncMLCred *Cred;   /**< Cred? */
    WBXMLSyncMLMeta *Meta;   /**< Meta? */
    WBXMLList       *items;  /**< Item+ */
    WBXMLBuffer     *Lang;   /**< Lang? */
} WBXMLSyncMLGet;

/**
 * @brief SyncML <Map> element
 */
typedef struct WBXMLSyncMLMap_s {
    WBXMLSyncMLCred *Cred;   /**< Cred? */
    WBXMLSyncMLMeta *Meta;   /**< Meta? */
    WBXMLList       *maps;   /**< MapItem+ (WBXMLSyncMLMapItem) */
    WBXMLBuffer     *Target; /**< Target */
    WBXMLBuffer     *Source; /**< Source */
} WBXMLSyncMLMap;

/**
 * @brief SyncML <MapItem> element
 */
typedef struct WBXMLSyncMLMapItem_s {
    WBXMLBuffer *Target; /**< Target */
    WBXMLBuffer *Source; /**< Source */
} WBXMLSyncMLMapItem;

/**
 * @brief SyncML <Put> element
 */
typedef struct WBXMLSyncMLPut_s {
    WB_BOOL          NoResp; /**< NoResp? */
    WBXMLSyncMLCred *Cred;   /**< Cred? */
    WBXMLSyncMLMeta *Meta;   /**< Meta? */
    WBXMLList       *items;  /**< Item+ */
    WBXMLBuffer     *Lang;   /**< Lang? */
} WBXMLSyncMLPut;

/**
 * @brief SyncML <Replace> element
 */
typedef struct WBXMLSyncMLReplace_s {
    WB_BOOL          NoResp; /**< NoResp? */
    WBXMLSyncMLCred *Cred;   /**< Cred? */
    WBXMLSyncMLMeta *Meta;   /**< Meta? */
    WBXMLList       *items;  /**< Item+ */
} WBXMLSyncMLReplace;

/**
 * @brief SyncML <Results> element
 */
typedef struct WBXMLSyncMLResults_s {
    WBXMLSyncMLMeta *Meta;      /**< Meta? */
    WBXMLList       *items;     /**< Item+ */
    WBXMLBuffer     *TargetRef; /**< TargetRef? */
    WBXMLBuffer     *SourceRef; /**< SourceRef? */
    WBXMLBuffer     *MsgRef;    /**< MsgRef? */
    WBXMLBuffer     *CmdRef;    /**< CmdRef */
} WBXMLSyncMLResults;

/**
 * @brief SyncML <Search> element
 */
typedef struct WBXMLSyncMLSearch_s {
    WB_BOOL          NoResp;    /**< NoResp? */
    WB_BOOL          NoResults; /**< NoResults? */
    WBXMLSyncMLCred *Cred;      /**< Cred? */
    WBXMLBuffer     *Target;    /**< Target? */
    WBXMLList       *Source;    /**< Source+ */
    WBXMLBuffer     *lang;      /**< Lang? */
    WBXMLSyncMLMeta *Meta;      /**< Meta */
    WBXMLBuffer     *Data;      /**< Data */
} WBXMLSyncMLSearch;

/**
 * @brief SyncML <Sequence> element
 */
typedef struct WBXMLSyncMLSequence_s {
    WB_BOOL          NoResp;   /**< NoResp? */
    WBXMLSyncMLMeta *Meta;     /**< Meta? */
    WBXMLList       *commands; /**< (Add | Replace | Delete | Copy | Atomic | Map | Sync | Get | Alert | Exec)+ */
} WBXMLSyncMLSequence;

/**
 * @brief SyncML <Status> element
 */
typedef struct WBXMLSyncMLStatus_s {
    /* <!ELEMENT Status   (CmdID, MsgRef, CmdRef, Cmd, TargetRef*, SourceRef*, Cred?, Chal?, Data, Item*)> */
    WBXMLBuffer        *MsgRef;    /**< MsgRef */
    WBXMLBuffer        *CmdRef;    /**< CmdRef */
    WBXMLSyncMLCmdType  Cmd;       /**< Cmd */
    WBXMLList          *TargetRef; /**< TargetRef* */
    WBXMLList          *SourceRef; /**< SourceRef* */
    WBXMLSyncMLCred    *Cred;      /**< Cred? */
    WBXMLSyncMLChal    *Chal;      /**< Chal? */
    WBXMLBuffer        *Data;      /**< Data */
    WBXMLList          *items;     /**< Item* */
} WBXMLSyncMLStatus;

/**
 * @brief SyncML <Sync> element
 */
typedef struct WBXMLSyncMLSync_s {
    /* <!ELEMENT Sync     (CmdID, NoResp?, Cred?, Target?, Source?, Meta?, NumberOfChanges?, (Add | Atomic | Copy | Delete | Replace | Sequence)*)> */
    WB_BOOL          NoResp;          /**< NoResp? */
    WBXMLSyncMLCred *Cred;            /**< Cred? */
    WBXMLBuffer     *Target;          /**< Target? */
    WBXMLBuffer     *Source;          /**< Source? */
    WBXMLSyncMLMeta *Meta;            /**< Meta? */
    WB_ULONG         NumberOfChanges; /**< NumberOfChanges? */
    WBXMLList       *commands;        /**< (Add | Atomic | Copy | Delete | Replace | Sequence)* */
} WBXMLSyncMLSync;

/**
 * @brief SyncML command element
 */
typedef struct WBXMLSyncMLCommand_s {
    WBXMLSyncMLCmdType       type;     /**< Cf. WBXMLSyncMLCmdType */
    WBXMLBuffer             *CmdID;    /**< CmdId */

    union {
        WBXMLSyncMLAdd      *Add;      /**< Add */
        WBXMLSyncMLAlert    *Alert;    /**< Alert */
        WBXMLSyncMLAtomic   *Atomic;   /**< Atomic */
        WBXMLSyncMLCopy     *Copy;     /**< Copy */
        WBXMLSyncMLDelete   *Delete;   /**< Delete */
        WBXMLSyncMLExec     *Exec;     /**< Exec */
        WBXMLSyncMLGet      *Get;      /**< Get */
        WBXMLSyncMLMap      *Map;      /**< Map */
        WBXMLSyncMLPut      *Put;      /**< Put */
        WBXMLSyncMLReplace  *Replace;  /**< Replace */
        WBXMLSyncMLResults  *Results;  /**< Results */
        WBXMLSyncMLSearch   *Search;   /**< Search */
        WBXMLSyncMLSequence *Sequence; /**< Sequence */
        WBXMLSyncMLStatus   *Status;   /**< Status */
        WBXMLSyncMLSync     *Sync;     /**< Sync */
    } u;
} WBXMLSyncMLCommand;

/**
 * @brief SyncML <SyncBody> element
 */
typedef struct WBXMLSyncMLSyncBody_s
{
    WBXMLList *commands; /**< (Alert | Atomic | Copy | Exec | Get | Map | Put | Results | Search | Sequence | Status | Sync | Add | Replace | Delete)+ */
    WB_BOOL    Final;    /**< Final? */
} WBXMLSyncMLSyncBody;

/**
 * @brief SyncML <SyncHdr> element
 */
typedef struct WBXMLSyncMLSyncHdr_s
{
    WBXMLSyncMLVerDTD    VerDTD;    /**< VerDTD */
    WBXMLSyncMLVerProto  VerProto;  /**< VerProto */
    WBXMLBuffer         *SessionID; /**< SessionID */
    WBXMLBuffer         *MsgID;     /**< MsgID */
    WBXMLBuffer         *Target;    /**< Target */
    WBXMLBuffer         *Source;    /**< Source */
    WBXMLBuffer         *RespURI;   /**< RespURI? */
    WB_BOOL              NoResp;    /**< NoResp? */
    WBXMLSyncMLCred     *Cred;      /**< Cred? */
    WBXMLSyncMLMeta     *Meta;      /**< Meta? */
} WBXMLSyncMLSyncHdr;

/**
 * @brief SyncML <SyncML> element
 */
typedef struct WBXMLSyncMLSyncML_s
{
    WBXMLSyncMLSyncHdr  *SyncHdr;  /**< SyncHdr */
    WBXMLSyncMLSyncBody *SyncBody; /**< SyncBody */
} WBXMLSyncMLSyncML;


/****************************************************
 *  SyncML Structures Functions
 */

/* <Cred> */

/**
 * @brief Create a SyncML <Cred> element structure
 * @return Pointer to the newly created structure, or NULL if not enough memory
 */
WBXML_DECLARE(WBXMLSyncMLCred *) wbxml_syncml_Cred_create(void);

/**
 * @brief Destroy a SyncML <Cred> element structure
 * @param elt Pointer to the structure to destroy
 */
WBXML_DECLARE(void) wbxml_syncml_Cred_destroy(WBXMLSyncMLCred *elt);

/* <Chal> */

/**
 * @brief Create a SyncML <Chal> element structure
 * @return Pointer to the newly created structure, or NULL if not enough memory
 */
WBXML_DECLARE(WBXMLSyncMLChal *) wbxml_syncml_Chal_create(void);

/**
 * @brief Destroy a SyncML <Chal> element structure
 * @param elt Pointer to the structure to destroy
 */
WBXML_DECLARE(void) wbxml_syncml_Chal_destroy(WBXMLSyncMLChal *elt);

/* <Item> */

/**
 * @brief Create a SyncML <Item> element structure
 * @return Pointer to the newly created structure, or NULL if not enough memory
 */
WBXML_DECLARE(WBXMLSyncMLItem *) wbxml_syncml_Item_create(void);

/**
 * @brief Destroy a SyncML <Item> element structure
 * @param elt Pointer to the structure to destroy
 */
WBXML_DECLARE(void) wbxml_syncml_Item_destroy(WBXMLSyncMLItem *elt);

/* <Add> */

/**
 * @brief Create a SyncML <Add> element structure
 * @return Pointer to the newly created structure, or NULL if not enough memory
 */
WBXML_DECLARE(WBXMLSyncMLAdd *) wbxml_syncml_Add_create(void);

/**
 * @brief Destroy a SyncML <Add> element structure
 * @param elt Pointer to the structure to destroy
 */
WBXML_DECLARE(void) wbxml_syncml_Add_destroy(WBXMLSyncMLAdd *elt);

/* <Alert> */

/**
 * @brief Create a SyncML <Alert> element structure
 * @return Pointer to the newly created structure, or NULL if not enough memory
 */
WBXML_DECLARE(WBXMLSyncMLAlert *) wbxml_syncml_Alert_create(void);

/**
 * @brief Destroy a SyncML <Alert> element structure
 * @param elt Pointer to the structure to destroy
 */
WBXML_DECLARE(void) wbxml_syncml_Alert_destroy(WBXMLSyncMLAlert *elt);

/* <Atomic> */

/**
 * @brief Create a SyncML <Atomic> element structure
 * @return Pointer to the newly created structure, or NULL if not enough memory
 */
WBXML_DECLARE(WBXMLSyncMLAtomic *) wbxml_syncml_Atomic_create(void);

/**
 * @brief Destroy a SyncML <Atomic> element structure
 * @param elt Pointer to the structure to destroy
 */
WBXML_DECLARE(void) wbxml_syncml_Atomic_destroy(WBXMLSyncMLAtomic *elt);

/* <Copy> */

/**
 * @brief Create a SyncML <Copy> element structure
 * @return Pointer to the newly created structure, or NULL if not enough memory
 */
WBXML_DECLARE(WBXMLSyncMLCopy *) wbxml_syncml_Copy_create(void);

/**
 * @brief Destroy a SyncML <Copy> element structure
 * @param elt Pointer to the structure to destroy
 */
WBXML_DECLARE(void) wbxml_syncml_Copy_destroy(WBXMLSyncMLCopy *elt);

/* <Delete> */

/**
 * @brief Create a SyncML <Delete> element structure
 * @return Pointer to the newly created structure, or NULL if not enough memory
 */
WBXML_DECLARE(WBXMLSyncMLDelete *) wbxml_syncml_Delete_create(void);

/**
 * @brief Destroy a SyncML <Delete> element structure
 * @param elt Pointer to the structure to destroy
 */
WBXML_DECLARE(void) wbxml_syncml_Delete_destroy(WBXMLSyncMLDelete *elt);

/* <Exec> */

/**
 * @brief Create a SyncML <Exec> element structure
 * @return Pointer to the newly created structure, or NULL if not enough memory
 */
WBXML_DECLARE(WBXMLSyncMLExec *) wbxml_syncml_Exec_create(void);

/**
 * @brief Destroy a SyncML <Exec> element structure
 * @param elt Pointer to the structure to destroy
 */
WBXML_DECLARE(void) wbxml_syncml_Exec_destroy(WBXMLSyncMLExec *elt);

/* <Get> */

/**
 * @brief Create a SyncML <Get> element structure
 * @return Pointer to the newly created structure, or NULL if not enough memory
 */
WBXML_DECLARE(WBXMLSyncMLGet *) wbxml_syncml_Get_create(void);

/**
 * @brief Destroy a SyncML <Get> element structure
 * @param elt Pointer to the structure to destroy
 */
WBXML_DECLARE(void) wbxml_syncml_Get_destroy(WBXMLSyncMLGet *elt);

/* <Map> */

/**
 * @brief Create a SyncML <Map> element structure
 * @return Pointer to the newly created structure, or NULL if not enough memory
 */
WBXML_DECLARE(WBXMLSyncMLMap *) wbxml_syncml_Map_create(void);

/**
 * @brief Destroy a SyncML <Map> element structure
 * @param elt Pointer to the structure to destroy
 */
WBXML_DECLARE(void) wbxml_syncml_Map_destroy(WBXMLSyncMLMap *elt);

/* <MapItem> */

/**
 * @brief Create a SyncML <MapItem> element structure
 * @return Pointer to the newly created structure, or NULL if not enough memory
 */
WBXML_DECLARE(WBXMLSyncMLMapItem *) wbxml_syncml_MapItem_create(void);

/**
 * @brief Destroy a SyncML <MapItem> element structure
 * @param elt Pointer to the structure to destroy
 */
WBXML_DECLARE(void) wbxml_syncml_MapItem_destroy(WBXMLSyncMLMapItem *elt);

/* <Put> */

/**
 * @brief Create a SyncML <> element structure
 * @return Pointer to the newly created structure, or NULL if not enough memory
 */
WBXML_DECLARE(WBXMLSyncMLPut *) wbxml_syncml_Put_create(void);

/**
 * @brief Destroy a SyncML <Put> element structure
 * @param elt Pointer to the structure to destroy
 */
WBXML_DECLARE(void) wbxml_syncml_Put_destroy(WBXMLSyncMLPut *elt);

/* <Replace> */

/**
 * @brief Create a SyncML <Replace> element structure
 * @return Pointer to the newly created structure, or NULL if not enough memory
 */
WBXML_DECLARE(WBXMLSyncMLReplace *) wbxml_syncml_Replace_create(void);

/**
 * @brief Destroy a SyncML <Replace> element structure
 * @param elt Pointer to the structure to destroy
 */
WBXML_DECLARE(void) wbxml_syncml_Replace_destroy(WBXMLSyncMLReplace *elt);

/* <Results> */

/**
 * @brief Create a SyncML <Results> element structure
 * @return Pointer to the newly created structure, or NULL if not enough memory
 */
WBXML_DECLARE(WBXMLSyncMLResults *) wbxml_syncml_Results_create(void);

/**
 * @brief Destroy a SyncML <Results> element structure
 * @param elt Pointer to the structure to destroy
 */
WBXML_DECLARE(void) wbxml_syncml_Results_destroy(WBXMLSyncMLResults *elt);

/* <Search> */

/**
 * @brief Create a SyncML <Search> element structure
 * @return Pointer to the newly created structure, or NULL if not enough memory
 */
WBXML_DECLARE(WBXMLSyncMLSearch *) wbxml_syncml_Search_create(void);

/**
 * @brief Destroy a SyncML <Search> element structure
 * @param elt Pointer to the structure to destroy
 */
WBXML_DECLARE(void) wbxml_syncml_Search_destroy(WBXMLSyncMLSearch *elt);

/* <Sequence> */

/**
 * @brief Create a SyncML <Sequence> element structure
 * @return Pointer to the newly created structure, or NULL if not enough memory
 */
WBXML_DECLARE(WBXMLSyncMLSequence *) wbxml_syncml_Sequence_create(void);

/**
 * @brief Destroy a SyncML <Sequence> element structure
 * @param elt Pointer to the structure to destroy
 */
WBXML_DECLARE(void) wbxml_syncml_Sequence_destroy(WBXMLSyncMLSequence *elt);

/* <Status> */

/**
 * @brief Create a SyncML <Status> element structure
 * @return Pointer to the newly created structure, or NULL if not enough memory
 */
WBXML_DECLARE(WBXMLSyncMLStatus *) wbxml_syncml_Status_create(void);

/**
 * @brief Destroy a SyncML <Status> element structure
 * @param elt Pointer to the structure to destroy
 */
WBXML_DECLARE(void) wbxml_syncml_Status_destroy(WBXMLSyncMLStatus *elt);

/* <Sync> */

/**
 * @brief Create a SyncML <Sync> element structure
 * @return Pointer to the newly created structure, or NULL if not enough memory
 */
WBXML_DECLARE(WBXMLSyncMLSync *) wbxml_syncml_Sync_create(void);

/**
 * @brief Destroy a SyncML <Sync> element structure
 * @param elt Pointer to the structure to destroy
 */
WBXML_DECLARE(void) wbxml_syncml_Sync_destroy(WBXMLSyncMLSync *elt);

/* Command */

/**
 * @brief Create a SyncML Command structure
 * @return Pointer to the newly created structure, or NULL if not enough memory
 */
WBXML_DECLARE(WBXMLSyncMLCommand *) wbxml_syncml_command_create(void);

/**
 * @brief Destroy a SyncML Command structure
 * @param cmd Pointer to the Command to destroy
 */
WBXML_DECLARE(void) wbxml_syncml_command_destroy(WBXMLSyncMLCommand *cmd);

/* <SyncBody> */

/**
 * @brief Create a SyncML <SyncBody> element structure
 * @return Pointer to the newly created structure, or NULL if not enough memory
 */
WBXML_DECLARE(WBXMLSyncMLSyncBody *) wbxml_syncml_SyncBody_create(void);

/**
 * @brief Destroy a SyncML <SyncBody> element structure
 * @param elt Pointer to the structure to destroy
 */
WBXML_DECLARE(void) wbxml_syncml_SyncBody_destroy(WBXMLSyncMLSyncBody *elt);

/* <SyncHdr> */

/**
 * @brief Create a SyncML <SyncHdr> element structure
 * @return Pointer to the newly created structure, or NULL if not enough memory
 */
WBXML_DECLARE(WBXMLSyncMLSyncHdr *) wbxml_syncml_SyncHdr_create(void);

/**
 * @brief Destroy a SyncML <SyncHdr> element structure
 * @param elt Pointer to the structure to destroy
 */
WBXML_DECLARE(void) wbxml_syncml_SyncHdr_destroy(WBXMLSyncMLSyncHdr *elt);

/* <SyncML> */

/**
 * @brief Create a SyncML <SyncML> element structure
 * @return Pointer to the newly created structure, or NULL if not enough memory
 */
WBXML_DECLARE(WBXMLSyncMLSyncML *) wbxml_syncml_SyncML_create(void);

/**
 * @brief Destroy a SyncML <SyncML> element structure
 * @param elt Pointer to the structure to destroy
 */
WBXML_DECLARE(void) wbxml_syncml_SyncML_destroy(WBXMLSyncMLSyncML *elt);


/****************************************************
 *  SyncML Building Functions
 */

/**
 * @brief Create a SyncML Header tree node
 * @result Return the newly created tree node, or NULL if error
 */
WBXML_DECLARE(WBXMLTreeNode *) wbxml_syncml_SyncHdr_build(WBXMLSyncMLSyncHdr *elt);

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* WBXML_WRAP_SYNCML_H */

#endif /* WBXML_WRAPPERS && WBXML_SUPPORT_SYNCML */
