#line 1 "usb_prop.c"













 

 
#line 1 ".\\usb_library\\inc\\usb_lib.h"













 

 



 
#line 1 ".\\usb_library\\inc\\usb_type.h"













 

 



 
#line 1 ".\\usb_library\\inc\\usb_conf.h"













 

 



 
 
 
 
 
 
 
 
 
 


 
 
 
 
 


 
 



 
 



 
 
 
 
 
 



 
 
#line 67 ".\\usb_library\\inc\\usb_conf.h"

#line 75 ".\\usb_library\\inc\\usb_conf.h"



 

#line 22 ".\\usb_library\\inc\\usb_type.h"

 
 






typedef signed long      s32;
typedef signed short     s16;
typedef signed char      s8;

typedef volatile signed long      vs32;
typedef volatile signed short     vs16;
typedef volatile signed char      vs8;

typedef unsigned long       u32;
typedef unsigned short      u16;
typedef unsigned char       u8;

typedef unsigned long  const    uc32;   
typedef unsigned short const    uc16;   
typedef unsigned char  const    uc8;    

typedef volatile unsigned long      vu32;
typedef volatile unsigned short     vu16;
typedef volatile unsigned char      vu8;

typedef volatile unsigned long  const    vuc32;   
typedef volatile unsigned short const    vuc16;   
typedef volatile unsigned char  const    vuc8;    


typedef enum
{
  FALSE = 0, TRUE  = !FALSE
}
bool;

typedef enum { RESET = 0, SET   = !RESET } FlagStatus, ITStatus;

typedef enum { DISABLE = 0, ENABLE  = !DISABLE} FunctionalState;

typedef enum { ERROR = 0, SUCCESS  = !ERROR} ErrorStatus;


 
 
 



 
#line 22 ".\\usb_library\\inc\\usb_lib.h"
#line 1 ".\\usb_library\\inc\\usb_regs.h"













 

 



 
 
typedef enum _EP_DBUF_DIR
{
   
  EP_DBUF_ERR,
  EP_DBUF_OUT,
  EP_DBUF_IN
}EP_DBUF_DIR;

 
enum EP_BUF_NUM
{
  EP_NOBUF,
  EP_BUF0,
  EP_BUF1
};

 



 
 
 

 

 

 

 

 

 
 
 


 
#line 70 ".\\usb_library\\inc\\usb_regs.h"
 
 
 
#line 81 ".\\usb_library\\inc\\usb_regs.h"





#line 94 ".\\usb_library\\inc\\usb_regs.h"

 
 
 
#line 106 ".\\usb_library\\inc\\usb_regs.h"








 
 
 





 
 
 


 
 
 
 
#line 141 ".\\usb_library\\inc\\usb_regs.h"

 


 
#line 152 ".\\usb_library\\inc\\usb_regs.h"


 


 
#line 165 ".\\usb_library\\inc\\usb_regs.h"

 
#line 174 ".\\usb_library\\inc\\usb_regs.h"
 
 


 


 


 


 


 


 


 


 


 



 









 









 









 
#line 248 ".\\usb_library\\inc\\usb_regs.h"








 
#line 269 ".\\usb_library\\inc\\usb_regs.h"







 










 










 











 











 









 









 











 











 











 









 














 









 










 
#line 431 ".\\usb_library\\inc\\usb_regs.h"

#line 438 ".\\usb_library\\inc\\usb_regs.h"




















 











 










 











 











 












 
#line 527 ".\\usb_library\\inc\\usb_regs.h"

#line 536 ".\\usb_library\\inc\\usb_regs.h"












 




 
extern volatile u16 wIstr;   

 
void SetCNTR(u16  );
void SetISTR(u16  );
void SetDADDR(u16  );
void SetBTABLE(u16  );
void SetBTABLE(u16  );
u16 GetCNTR(void);
u16 GetISTR(void);
u16 GetFNR(void);
u16 GetDADDR(void);
u16 GetBTABLE(void);
void SetENDPOINT(u8  , u16  );
u16 GetENDPOINT(u8  );
void SetEPType(u8  , u16  );
u16 GetEPType(u8  );
void SetEPTxStatus(u8  , u16  );
void SetEPRxStatus(u8  , u16  );
void SetDouBleBuffEPStall(u8  , u8 bDir);
u16 GetEPTxStatus(u8  );
u16 GetEPRxStatus(u8  );
void SetEPTxValid(u8  );
void SetEPRxValid(u8  );
u16 GetTxStallStatus(u8  );
u16 GetRxStallStatus(u8  );
void SetEP_KIND(u8  );
void ClearEP_KIND(u8  );
void Set_Status_Out(u8  );
void Clear_Status_Out(u8  );
void SetEPDoubleBuff(u8  );
void ClearEPDoubleBuff(u8  );
void ClearEP_CTR_RX(u8  );
void ClearEP_CTR_TX(u8  );
void ToggleDTOG_RX(u8  );
void ToggleDTOG_TX(u8  );
void ClearDTOG_RX(u8  );
void ClearDTOG_TX(u8  );
void SetEPAddress(u8  , u8  );
u8 GetEPAddress(u8  );
void SetEPTxAddr(u8  , u16  );
void SetEPRxAddr(u8  , u16  );
u16 GetEPTxAddr(u8  );
u16 GetEPRxAddr(u8  );
void SetEPCountRxReg(u32 *  , u16  );
void SetEPTxCount(u8  , u16  );
void SetEPRxCount(u8  , u16  );
u16 GetEPTxCount(u8  );
u16 GetEPRxCount(u8  );
void SetEPDblBuf0Addr(u8  , u16  );
void SetEPDblBuf1Addr(u8  , u16  );
void SetEPDblBuffAddr(u8  , u16  , u16  );
u16 GetEPDblBuf0Addr(u8  );
u16 GetEPDblBuf1Addr(u8  );
void SetEPDblBuffCount(u8  , u8  , u16  );
void SetEPDblBuf0Count(u8  , u8  , u16  );
void SetEPDblBuf1Count(u8  , u8  , u16  );
u16 GetEPDblBuf0Count(u8  );
u16 GetEPDblBuf1Count(u8  );
EP_DBUF_DIR GetEPDblBufDir(u8  );
void FreeUserBuffer(u8 bEpNum , u8 bDir);
u16 ToWord(u8, u8);
u16 ByteSwap(u16);



 
#line 23 ".\\usb_library\\inc\\usb_lib.h"
#line 1 ".\\usb_library\\inc\\usb_def.h"













 

 



 
 
typedef enum _RECIPIENT_TYPE
{
  DEVICE_RECIPIENT,      
  INTERFACE_RECIPIENT,   
  ENDPOINT_RECIPIENT,    
  OTHER_RECIPIENT
} RECIPIENT_TYPE;


typedef enum _STANDARD_REQUESTS
{
  GET_STATUS = 0,
  CLEAR_FEATURE,
  RESERVED1,
  SET_FEATURE,
  RESERVED2,
  SET_ADDRESS,
  GET_DESCRIPTOR,
  SET_DESCRIPTOR,
  GET_CONFIGURATION,
  SET_CONFIGURATION,
  GET_INTERFACE,
  SET_INTERFACE,
  TOTAL_sREQUEST,   
  SYNCH_FRAME = 12
} STANDARD_REQUESTS;

 
typedef enum _DESCRIPTOR_TYPE
{
  DEVICE_DESCRIPTOR = 1,
  CONFIG_DESCRIPTOR,
  STRING_DESCRIPTOR,
  INTERFACE_DESCRIPTOR,
  ENDPOINT_DESCRIPTOR
} DESCRIPTOR_TYPE;

 
typedef enum _FEATURE_SELECTOR
{
  ENDPOINT_STALL,
  DEVICE_REMOTE_WAKEUP
} FEATURE_SELECTOR;

 
 







 
 



 
#line 24 ".\\usb_library\\inc\\usb_lib.h"
#line 1 ".\\usb_library\\inc\\usb_core.h"













 

 



 
 
typedef enum _CONTROL_STATE
{
  WAIT_SETUP,        
  SETTING_UP,        
  IN_DATA,           
  OUT_DATA,          
  LAST_IN_DATA,      
  LAST_OUT_DATA,     
  WAIT_STATUS_IN,    
  WAIT_STATUS_OUT,   
  STALLED,           
  PAUSE              
} CONTROL_STATE;     

typedef struct OneDescriptor
{
  u8 *Descriptor;
  u16 Descriptor_Size;
}
ONE_DESCRIPTOR, *PONE_DESCRIPTOR;


 
typedef enum _RESULT
{
  USB_SUCCESS = 0,     
  USB_ERROR,
  USB_UNSUPPORT,
  USB_NOT_READY       
 
} RESULT;


 
typedef struct _ENDPOINT_INFO
{
  




















 
  u16  Usb_wLength;
  u16  Usb_wOffset;
  u16  PacketSize;
  u8   *(*CopyData)(u16 Length);
}
ENDPOINT_INFO;

 

typedef struct _DEVICE
{
  u8 Total_Endpoint;      
  u8 Total_Configuration; 
}
DEVICE;

typedef union
{
  u16 w;
  struct BW
  {
    u8 bb1;
    u8 bb0;
  }
  bw;
} u16_u8;

typedef struct _DEVICE_INFO
{
  u8 USBbmRequestType;        
  u8 USBbRequest;             
  u16_u8 USBwValues;          
  u16_u8 USBwIndexs;          
  u16_u8 USBwLengths;         

  u8 ControlState;            
  u8 Current_Feature;
  u8 Current_Configuration;    
  u8 Current_Interface;        
  u8 Current_AlternateSetting;
 

  ENDPOINT_INFO Ctrl_Info;
}
DEVICE_INFO;

typedef struct _DEVICE_PROP
{
  void (*Init)(void);         
  void (*Reset)(void);        

   
  void (*Process_Status_IN)(void);
  void (*Process_Status_OUT)(void);

   
  













 
  RESULT (*Class_Data_Setup)(u8 RequestNo);

   
  






 
  RESULT (*Class_NoData_Setup)(u8 RequestNo);

  





 

  RESULT  (*Class_Get_Interface_Setting)(u8 Interface, u8 AlternateSetting);

  u8* (*GetDeviceDescriptor)(u16 Length);
  u8* (*GetConfigDescriptor)(u16 Length);
  u8* (*GetStringDescriptor)(u16 Length);

  u8* RxEP_buffer;
  u8 MaxPacketSize;

}
DEVICE_PROP;

typedef struct _USER_STANDARD_REQUESTS
{
  void (*User_GetConfiguration)(void);        
  void (*User_SetConfiguration)(void);        
  void (*User_GetInterface)(void);            
  void (*User_SetInterface)(void);            
  void (*User_GetStatus)(void);               
  void (*User_ClearFeature)(void);            
  void (*User_SetEndPointFeature)(void);      
  void (*User_SetDeviceFeature)(void);        
  void (*User_SetDeviceAddress)(void);        
}
USER_STANDARD_REQUESTS;

 





#line 213 ".\\usb_library\\inc\\usb_core.h"

 
 
u8 Setup0_Process(void);
u8 Post0_Process(void);
u8 Out0_Process(void);
u8 In0_Process(void);

RESULT Standard_SetEndPointFeature(void);
RESULT Standard_SetDeviceFeature(void);

u8 *Standard_GetConfiguration(u16 Length);
RESULT Standard_SetConfiguration(void);
u8 *Standard_GetInterface(u16 Length);
RESULT Standard_SetInterface(void);
u8 *Standard_GetDescriptorData(u16 Length, PONE_DESCRIPTOR pDesc);

u8 *Standard_GetStatus(u16 Length);
RESULT Standard_ClearFeature(void);
void SetDeviceAddress(u8);
void NOP_Process(void);

extern DEVICE_PROP Device_Property;
extern  USER_STANDARD_REQUESTS User_Standard_Requests;
extern  DEVICE  Device_Table;
extern DEVICE_INFO Device_Info;

 
extern u16 SaveRState;
extern u16 SaveTState;



 
#line 25 ".\\usb_library\\inc\\usb_lib.h"
#line 1 ".\\usb_library\\inc\\usb_init.h"













 

 



 
 
 
 
 
void USB_Init(void);

 
 
extern u8	EPindex;
 
 
 
 
extern DEVICE_INFO*	pInformation;
 
 
extern DEVICE_PROP*	pProperty;
 
 
 
 
extern USER_STANDARD_REQUESTS *pUser_Standard_Requests;

extern u16	SaveState ;
extern u16 wInterrupt_Mask;



 
#line 26 ".\\usb_library\\inc\\usb_lib.h"
#line 1 ".\\usb_library\\inc\\usb_mem.h"













 

 



 
 
 
 
 
void UserToPMABufferCopy(u8 *pbUsrBuf, u16 wPMABufAddr, u16 wNBytes);
void PMAToUserBufferCopy(u8 *pbUsrBuf, u16 wPMABufAddr, u16 wNBytes);

 



 
#line 27 ".\\usb_library\\inc\\usb_lib.h"
#line 1 ".\\usb_library\\inc\\usb_int.h"














 

 



 
 
 
 
 
void CTR_LP(void);
void CTR_HP(void);

 



 
#line 28 ".\\usb_library\\inc\\usb_lib.h"

 
 
 
 
 



 
#line 18 "usb_prop.c"
#line 19 "usb_prop.c"
#line 1 ".\\usb_library\\inc\\usb_prop.h"













 

 



 
 
typedef enum _HID_REQUESTS
{
  GET_REPORT = 1,
  GET_IDLE,
  GET_PROTOCOL,

  SET_REPORT = 9,
  SET_IDLE,
  SET_PROTOCOL
} HID_REQUESTS;

 
 
 
void Joystick_init(void);
void Joystick_Reset(void);
void Joystick_Status_In (void);
void Joystick_Status_Out (void);
RESULT Joystick_Data_Setup(u8);
RESULT Joystick_NoData_Setup(u8);
RESULT Joystick_Get_Interface_Setting(u8 Interface, u8 AlternateSetting);
u8 *Joystick_GetDeviceDescriptor(u16 );
u8 *Joystick_GetConfigDescriptor(u16);
u8 *Joystick_GetStringDescriptor(u16);
RESULT Joystick_SetProtocol(void);
u8 *Joystick_GetProtocolValue(u16 Length);
RESULT Joystick_SetProtocol(void);
u8 *Joystick_GetReportDescriptor(u16 Length);
u8 *Joystick_GetHIDDescriptor(u16 Length);

 
#line 62 ".\\usb_library\\inc\\usb_prop.h"





 
#line 20 "usb_prop.c"
#line 1 ".\\usb_library\\inc\\usb_desc.h"













 

 



 
 
 
 
 










#line 42 ".\\usb_library\\inc\\usb_desc.h"



 
extern const u8 Joystick_DeviceDescriptor[18];
extern const u8 Joystick_ConfigDescriptor[34];
extern const u8 Joystick_ReportDescriptor[74];
extern const u8 Joystick_StringLangID[4];
extern const u8 Joystick_StringVendor[38];
extern const u8 Joystick_StringProduct[30];
extern const u8 Joystick_StringSerial[26];



 
#line 21 "usb_prop.c"
#line 1 ".\\usb_library\\inc\\usb_pwr.h"













 

 



 
 
typedef enum _RESUME_STATE
{
  RESUME_EXTERNAL,
  RESUME_INTERNAL,
  RESUME_LATER,
  RESUME_WAIT,
  RESUME_START,
  RESUME_ON,
  RESUME_OFF,
  RESUME_ESOF
} RESUME_STATE;

typedef enum _DEVICE_STATE
{
  UNCONNECTED,
  ATTACHED,
  POWERED,
  DEFAULT,
  ADDRESSED,
  CONFIGURED
} DEVICE_STATE;

 
 
 
void Suspend(void);
void Resume_Init(void);
void Resume(RESUME_STATE eResumeSetVal);
RESULT PowerOn(void);
RESULT PowerOff(void);
 
extern  vu8 bDeviceState;  
extern volatile bool fSuspendEnabled;   



 
#line 22 "usb_prop.c"
#line 1 ".\\usb_library\\inc\\hw_config.h"













 

 



 
#line 22 ".\\usb_library\\inc\\hw_config.h"

 
 
 
 
#line 34 ".\\usb_library\\inc\\hw_config.h"

 
void Set_System(void);
void Set_USBClock(void);
void Enter_LowPowerMode(void);
void Leave_LowPowerMode(void);
void USB_Interrupts_Config(void);
void USB_Cable_Config (FunctionalState NewState);
void Joystick_Send(u8 Keys);
u8 JoyState(void);



 
#line 23 "usb_prop.c"

 
 
 
 
u32 ProtocolValue;

 
 
 

DEVICE Device_Table =
  {
    (2),
    1
  };

DEVICE_PROP Device_Property =
  {
    Joystick_init,
    Joystick_Reset,
    Joystick_Status_In,
    Joystick_Status_Out,
    Joystick_Data_Setup,
    Joystick_NoData_Setup,
    Joystick_Get_Interface_Setting,
    Joystick_GetDeviceDescriptor,
    Joystick_GetConfigDescriptor,
    Joystick_GetStringDescriptor,
    0,
    0x40  
  };
USER_STANDARD_REQUESTS User_Standard_Requests =
  {
    NOP_Process,
    NOP_Process,
    NOP_Process,
    NOP_Process,
    NOP_Process,
    NOP_Process,
    NOP_Process,
    NOP_Process,
    NOP_Process
  };

ONE_DESCRIPTOR Device_Descriptor =
  {
    (u8*)Joystick_DeviceDescriptor,
    18
  };

ONE_DESCRIPTOR Config_Descriptor =
  {
    (u8*)Joystick_ConfigDescriptor,
    34
  };

ONE_DESCRIPTOR Joystick_Report_Descriptor =
  {
    (u8 *)Joystick_ReportDescriptor,
    74
  };

ONE_DESCRIPTOR Mouse_Hid_Descriptor =
  {
    (u8*)Joystick_ConfigDescriptor + 0x12,
    0x09
  };

ONE_DESCRIPTOR String_Descriptor[4] =
  {
    {(u8*)Joystick_StringLangID, 4},
    {(u8*)Joystick_StringVendor, 38},
    {(u8*)Joystick_StringProduct, 30},
    {(u8*)Joystick_StringSerial, 26}
  };

 
 
 
 







 
void Joystick_init(void)
{
  pInformation->Current_Configuration = 0;
   
  PowerOn();
   
  (*((volatile unsigned *)((0x40005C00L) + 0x44)) = (u16)0);                
  wInterrupt_Mask = ((0x8000) | (0x1000) | (0x0800) | (0x2000) | (0x0200) | (0x0100) | (0x0400) );
  (*((volatile unsigned *)((0x40005C00L) + 0x40)) = (u16)wInterrupt_Mask);  
  pInformation->Current_Feature = Joystick_ConfigDescriptor[7];
   
  while (pInformation->Current_Configuration == 0)
  {
    NOP_Process();
  }

  bDeviceState = CONFIGURED;
}







 
void Joystick_Reset(void)
{
   
  pInformation->Current_Configuration = 0;
  pInformation->Current_Interface = 0; 
  SetBTABLE((0x00));

   
  SetEPType(((u8)0), (0x0200));
  SetEPTxStatus(((u8)0), (0x0010));
  SetEPRxAddr(((u8)0), (0x18));
  SetEPTxAddr(((u8)0), (0x58));
  Clear_Status_Out(((u8)0));
  SetEPRxCount(((u8)0), Device_Property.MaxPacketSize);
  SetEPRxValid(((u8)0));

   
  SetEPType(((u8)1), (0x0600));
  SetEPTxAddr(((u8)1), (0x100));
  SetEPTxCount(((u8)1), 4);
  SetEPRxStatus(((u8)1), (0x0000));
  SetEPTxStatus(((u8)1), (0x0020));

   
  SetDeviceAddress(0);
}







 
void Joystick_Status_In(void)
{
}







 
void Joystick_Status_Out (void)
{
}







 
RESULT Joystick_Data_Setup(u8 RequestNo)
{
  u8 *(*CopyRoutine)(u16);

  CopyRoutine = ((void *)0);

  if ((RequestNo == GET_DESCRIPTOR)
      && ((pInformation->USBbmRequestType & (0x60 | 0x1F)) == (0x00 | INTERFACE_RECIPIENT))
      && (pInformation->USBwIndexs . bw . bb0 == 0))
  {

    if (pInformation->USBwValues . bw . bb1 == 0x22)
    {
      CopyRoutine = Joystick_GetReportDescriptor;
    }
    else if (pInformation->USBwValues . bw . bb1 == 0x21)
    {
      CopyRoutine = Joystick_GetHIDDescriptor;
    }

  }  

   
  else if (((pInformation->USBbmRequestType & (0x60 | 0x1F)) == (0x20 | INTERFACE_RECIPIENT))
           && RequestNo == GET_PROTOCOL)
  {
    CopyRoutine = Joystick_GetProtocolValue;
  }

  if (CopyRoutine == ((void *)0))
  {
    return USB_UNSUPPORT;
  }

  pInformation->Ctrl_Info.CopyData = CopyRoutine;
  pInformation->Ctrl_Info.Usb_wOffset = 0;
  (*CopyRoutine)(0);
  return USB_SUCCESS;
}







 
RESULT Joystick_NoData_Setup(u8 RequestNo)
{
  if (((pInformation->USBbmRequestType & (0x60 | 0x1F)) == (0x20 | INTERFACE_RECIPIENT))
      && (RequestNo == SET_PROTOCOL))
  {
    return Joystick_SetProtocol();
  }

  else
  {
    return USB_UNSUPPORT;
  }
}







 
u8 *Joystick_GetDeviceDescriptor(u16 Length)
{
  return Standard_GetDescriptorData(Length, &Device_Descriptor);
}







 
u8 *Joystick_GetConfigDescriptor(u16 Length)
{
  return Standard_GetDescriptorData(Length, &Config_Descriptor);
}







 
u8 *Joystick_GetStringDescriptor(u16 Length)
{
  u8 wValue0 = pInformation->USBwValues . bw . bb0;
  return Standard_GetDescriptorData(Length, &String_Descriptor[wValue0]);
}







 
u8 *Joystick_GetReportDescriptor(u16 Length)
{
  return Standard_GetDescriptorData(Length, &Joystick_Report_Descriptor);
}







 
u8 *Joystick_GetHIDDescriptor(u16 Length)
{
  return Standard_GetDescriptorData(Length, &Mouse_Hid_Descriptor);
}









 
RESULT Joystick_Get_Interface_Setting(u8 Interface, u8 AlternateSetting)
{
  if (AlternateSetting > 0)
  {
    return USB_UNSUPPORT;
  }
  else if (Interface > 0)
  {
    return USB_UNSUPPORT;
  }
  return USB_SUCCESS;
}







 
RESULT Joystick_SetProtocol(void)
{
  u8 wValue0 = pInformation->USBwValues . bw . bb0;
  ProtocolValue = wValue0;
  return USB_SUCCESS;
}







 
u8 *Joystick_GetProtocolValue(u16 Length)
{
  if (Length == 0)
  {
    pInformation->Ctrl_Info.Usb_wLength = 1;
    return ((void *)0);
  }
  else
  {
    return (u8 *)(&ProtocolValue);
  }
}

 
