#include "BRTOS.h"  
#include "AppConfig.h"

// errors
#define COMMAND_UNKNOWN  1     
#define COMMAND_INVALID  2

typedef union _word
{
  unsigned char   int8u[2];
  unsigned short  int16u; 
} UCHAR_WORD;


// possible states                    
enum Comm2PC_FSM_States 
{
  BEGIN,        // start ($) of a message
  COMMAND_A,    // command
  COMMAND_B,    // command
  GPS_ADDRESS,  // GPS address
  NODE_ID,      // node ID
  BOOT_NODE,    // node ID for sending code
  RECEIVE_FIRMWARE,  
  END           // end of a message
};
  
#define MSG_START '$'
#define MSG_END   '#'

/* Supported commands */
#define CPU             ('C' << 8) | 'P'
#define VER             ('V' << 8) | 'E' 
#define LED             ('L' << 8) | 'E'
#define NGB             ('N' << 8) | 'B'
#define NNB             ('N' << 8) | 'N'
#define UPT             ('U' << 8) | 'P'
#define RPK             ('R' << 8) | 'P'
#define GAD             ('G' << 8) | 'A'
#define ERASE_FLASH     ('E' << 8) | 'F'
#define STORE_FIRMWARE  ('S' << 8) | 'F'
#define FOTA            ('F' << 8) | 'O'
#define SNIF            ('S' << 8) | 'N'
#define LSNIF           ('L' << 8) | 'S'
#define C_ON            ('O' << 8) | 'N'
#define C_OFF           ('O' << 8) | 'F'

 

INT8U  Comm2PC_FSM   (INT8U message);
INT16U RequestNodeID(void); 
void   SendPacketToQueue(void);
void   RequestGPSAddress(INT32U *x, INT32U *y);


void CMD_CPU (void);
void CMD_VER (void);
void CMD_UPT (void);
void CMD_LED (void);
void CMD_REQ_PACKETS(void);
void CMD_NEIGHBORS (void);
void CMD_NUMBER_OF_NEIGHBORS (void);
void CMD_GPS_ADDRESS (void);
void CMD_SNIF (void);
void CMD_ON(void);
void CMD_OFF(void);


void USB_putchar(char c);   /* Function to send one byte via USB CDC */
void USB_print(char *s);   /* Function to print a string via USB CDC */

#if (DEBUG == 1)
#define PUTCHAR(c)    USB_putchar(c)
#define PRINT(s)      USB_print(s)
#define CMD_PROCESS() cdc_process()
#else
#define PUTCHAR(c)    UART_putchar(c)
#define PRINT(s)      UART_print(s)
#define CMD_PROCESS() 
#endif



// Declara uma estrutura de fila
extern OS_QUEUE      PacketsBuffer;
extern BRTOS_Queue  *Pkt;

    