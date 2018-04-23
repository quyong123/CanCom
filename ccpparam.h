#ifndef CCPPARAM_H
#define CCPPARAM_H


#define CCP_STATION_ADDR 0x0034

#define CCP_DTO_ID 0x101
#define CCP_CRO_ID 0x100

/* Broadcast Station Address */
#define CCP_BROADCAST_STATION_ADDR 0


#define CCP_MAX_ODT 3
#define CCP_MAX_DAQ 2

#define CCP_CAN_ID   0x7BB



#define CCP_SEED_KEY 0x00
#define CCP_DAQ 	 0x01

#define CCP_DWORD quint32
#define CCP_WORD  quint16

/* Declare CCP-protocol version */
#define CCP_VERSION_MAJOR   0x02
#define CCP_VERSION_MINOR   0x01


/* Declare module implementation version number */
#define CCP_DRIVER_VERSION 142
#define CCP_DRIVER_BUGFIX_VERSION 0

/* Basic */
#define CC_CONNECT           0x01
#define CC_SET_MTA           0x02
#define CC_DNLOAD            0x03
#define CC_UPLOAD            0x04
#define CC_TEST              0x05
#define CC_START_STOP        0x06
#define CC_DISCONNECT        0x07
#define CC_START_STOP_ALL    0x08
#define CC_SHORT_UPLOAD      0x0F
#define CC_GET_DAQ_SIZE      0x14
#define CC_SET_DAQ_PTR       0x15
#define CC_WRITE_DAQ         0x16
#define CC_EXCHANGE_ID       0x17
#define CC_GET_CCP_VERSION   0x1B
#define CC_DNLOAD6           0x23


/* Optional */
#define CC_GET_CAL_PAGE      0x09
#define CC_SET_S_STATUS      0x0C
#define CC_GET_S_STATUS      0x0D
#define CC_BUILD_CHKSUM      0x0E
#define CC_CLEAR_MEMORY      0x10
#define CC_SET_CAL_PAGE      0x11
#define CC_GET_SEED          0x12
#define CC_UNLOCK            0x13
#define CC_PROGRAM           0x18
#define CC_MOVE_MEMORY       0x19
#define CC_DIAG_SERVICE      0x20
#define CC_ACTION_SERVICE    0x21
#define CC_PROGRAM6          0x22

/* Vector extensions */
#define CC_PROGRAM_PREPARE   0x1E   /* Prepare for flash kernel download */
#define CC_PROGRAM_START     0x1F   /* Start flash kernel at MTA[0] */

/* Returncodes */
#define CRC_OK                 0x00

/* C1 */
#define CRC_CMD_BUSY           0x10
#define CRC_DAQ_BUSY           0x11
#define CRC_KEY_REQUEST        0x18
#define CRC_STATUS_REQUEST     0x19

/* C2 */
#define CRC_COLD_START_REQUEST 0x20
#define CRC_CAL_INIT_REQUEST   0x21
#define CRC_DAQ_INIT_REQUEST   0x22
#define CRC_CODE_REQUEST       0x23

/* C3 (Errors) */
#define CRC_CMD_UNKNOWN        0x30
#define CRC_CMD_SYNTAX         0x31
#define CRC_OUT_OF_RANGE       0x32
#define CRC_ACCESS_DENIED      0x33
#define CRC_OVERLOAD           0x34
#define CRC_ACCESS_LOCKED      0x35


/* Session Status */
#define SS_CAL                0x01
#define SS_DAQ                0x02
#define SS_RESUME             0x04
#define SS_TMP_DISCONNECTED   0x10
#define SS_CONNECTED          0x20
#define SS_STORE              0x40
#define SS_RUN                0x80

/* Priviledge Level */
#define PL_CAL 0x01
#define PL_DAQ 0x02
#define PL_PGM 0x40

#define CCP_MAX_MTA 2
#define CCP_INTERNAL_MTA (CCP_MAX_MTA-1)

/* Return values for ccpWriteMTA and ccpCheckWriteEEPROM */
#define CCP_WRITE_DENIED  0
#define CCP_WRITE_OK      1
#define CCP_WRITE_PENDING 2
#define CCP_WRITE_ERROR   3

/* Bitmasks for ccp.SendStatus */
#define CCP_CRM_REQUEST  0x01
#define CCP_DTM_REQUEST  0x02
#define CCP_USR_REQUEST  0x04
#define CCP_CMD_PENDING  0x08
#define CCP_CRM_PENDING  0x10
#define CCP_DTM_PENDING  0x20
#define CCP_USR_PENDING  0x40
#define CCP_TX_PENDING   0x80
#define CCP_SEND_PENDING (CCP_DTM_PENDING|CCP_CRM_PENDING|CCP_USR_PENDING)

/* ODT entry */
typedef struct
{
    quint32 ulAddress[7];			// Max ODT Entries is 7 for CAN
    quint8 ucLastUsedODTEntry;	// Last used ODT Entry for this ODT
} ODT;

/* DAQ list */
#define DAQ_FLAG_START    0x01
#define DAQ_FLAG_SEND     0x02
#define DAQ_FLAG_PREPARED 0x04
#define DAQ_FLAG_OVERRUN  0x80

typedef struct ccpDaqList {
  ODT			odt[CCP_MAX_ODT];
  quint16        prescaler;
  quint16        cycle;
  quint8        	eventChannel;
  quint8        	LastUsedODT;
  quint8        	flags;
} DaqList;

typedef struct{

    quint8 Crm[8];                           /* CRM Command Return Message buffer */

    quint8 SessionStatus;
    quint8 SendStatus;

    quint8 * MTA[2];           				/* Memory Transfer Address */

    #ifdef CCP_SEND_QUEUE
      ccpQueue_t Queue;
    #else
      quint8 Dtm[8];                       /* DTM Data Transmission Message buffer */
    #endif

    #ifdef CCP_SEND_SINGLE
      quint8 CurrentDaq;
      quint8 CurrentOdt;
    #endif

    /* Selected DAQ_LIST_NUMBER, ODT_NUMBER, ODT_ENTRY_NUMBER for the SET_DAQ_PTR command */
    quint16	DAQNum;
    quint8	ODTNum;
    quint8	ODTEntryNum;

    quint8  *DaqListPtr;               /* Pointer for SET_DAQ_PTR, make it near to save RAM  */

    DaqList	DaqList[CCP_MAX_DAQ];     /* DAQ list */

    quint8 UserSessionStatus;                /* Used for GET/SET_SESSION_STATUS */

    quint8 ProtectionStatus;               	/* Resource Protection Status */

  #ifdef CCP_CHECKSUM
    #if defined( CCP_CPUTYPE_32BIT )
      CCP_DWORD CheckSumSize;                /* Counter for checksum calculation */
    #else
      CCP_WORD CheckSumSize;                 /* Counter for checksum calculation */
    #endif
  #endif

}CCP;
#endif // CCPPARAM_H
