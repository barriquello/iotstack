/***********************************************************************************
@file   comm2pc.c
@brief  Task for PC communication
@authors: Gustavo Weber Denardin
          Carlos Henrique Barriquello

Copyright (c) <2009-2013> <Universidade Federal de Santa Maria>

  * Software License Agreement
  *
  * The Software is owned by the authors, and is protected under 
  * applicable copyright laws. All rights are reserved.
  *
  * The above copyright notice shall be included in
  * all copies or substantial portions of the Software.
  *  
  * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  * THE SOFTWARE.
**********************************************************************************/

#include "comm2pc.h"
#include "app.h"
#include "gpsnet_api.h"
#include "drivers.h"

static UINT_DWORD GPS_X = {0,0,0,0};
static UINT_DWORD GPS_Y = {0,0,0,0};
static UINT_DWORD GPS_X_tmp = {0,0,0,0};
static UINT_DWORD GPS_Y_tmp = {0,0,0,0}; 

static INT16U node_id_received = 0xFFFF;
static INT16U node_id_received_tmp = 0;              


static INT8U  PacketsCnt = 0;   // Packets counter
OS_QUEUE      PacketsBuffer;   // Packets queue struct
BRTOS_Queue  *Pkt;

const cmd_t cmds[NUMBER_OF_COMMANDS] = {
    COMMAND_TABLE(EXPAND_AS_JUMPTABLE)
};


/* search command index in command table by command name */
static INT8U search_cmd (INT16U c);
static INT8U search_cmd (INT16U c) {

  INT8U inf = 0;  // inferior limit
  INT8U sup = NUMBER_OF_COMMANDS-1; // superior limit
  INT8U meio;
  while(inf <= sup){
    meio = (INT8U)((inf + sup) >> 1);
    if (cmds[meio].cmd < c) {
      inf = (INT8U)(meio + 1);
    }else{
      if (cmds[meio].cmd > c){
        sup = (INT8U)(meio-1);
      }else{
        return meio; // command index found
      }
    }
  } 
  return 0; // command index not found, return default index
}

/* Function to send one byte via USB CDC */
void USB_putchar(char c);

void USB_putchar(char c)
{
  while(c != (char)cdc_putch(c)){};
}

/* Function to print a string via USB CDC */
void USB_print(char *s);

void USB_print(char *s)
{
  while(*s){    
    while((*s) != (char)cdc_putch(*s)){};
    s++;    
  }
}


#if (DEBUG == 1)
#define PUTCHAR(c)    USB_putchar(c)
#define PRINT(s)      USB_print(s)
#define CMD_PROCESS() cdc_process()
#else
#define PUTCHAR(c)    UART_putchar(c)
#define PRINT(s)      UART_print(s)
#define CMD_PROCESS() UART_putchar('\n');
#endif


#define CMD_BEGIN(x)      PUTCHAR(MSG_START);           \
                          PUTCHAR((INT8U)((x)>>8));     \
                          PUTCHAR((INT8U)((x)&0xFF)); 
                          
                          
#define CMD_END(x)        PUTCHAR(MSG_END);         \
                          CMD_PROCESS();            \
                          return END;
                                               

static INT16U      cmd = 0;
static INT8U       SMIndex = 0;
static INT8U       cmdIndex = 0;
static COMM2PC_ST  currentstate = BEGIN;    
    
/* Finite state machine code to handle communication with PC */
INT8U Comm2PC_FSM (INT8U message) 
{                
    switch (currentstate) 
    {
        case BEGIN:
        restart:
          SMIndex = 0;
          if (message == MSG_START) 
          {
            currentstate = COMMAND;     
          } 
          else 
          {
            currentstate = BEGIN;
            return COMMAND_INVALID;  
          }
        break;
        
        case COMMAND:
          if(message == MSG_START){
            currentstate = BEGIN;
            goto restart;       // restart FSM 
          }
          if (SMIndex == 0)
          {
            cmd = (INT16U)(message); 
            SMIndex++;                               
          }else
          {   
              cmd = (INT16U)((cmd << 8) | message);
              cmdIndex = search_cmd(cmd);
              currentstate = CMD_ARG;
          }        
        break;
        
        case CMD_ARG:
          currentstate = cmds[cmdIndex].cmd_func(message);                             
        break;                 
        
        case END:          
          currentstate = BEGIN;
          goto restart;         // restart FSM          
          break;
        
        default:
          currentstate = BEGIN;
          return COMMAND_INVALID;        
      }
     
      return COMMAND_OK;
}

CMD_FUNC(ERR){
  CMD_FUNC_UNUSED_ARG();
  CMD_BEGIN(ERR); 
  CMD_END();
}

CMD_FUNC(SEND){
  CMD_FUNC_UNUSED_ARG();
  CMD_END(); 
}

CMD_FUNC(HELP){
  
  INT8U i = 0;
  CMD_FUNC_UNUSED_ARG();
  
  /* confirmation */
  CMD_BEGIN(HELP);
  
#if (defined HELP_COMMAND_ENABLED && HELP_COMMAND_ENABLED == 1) 
  PUTCHAR(CR);
  PUTCHAR(LF);
  for(i=1;i< (NUMBER_OF_COMMANDS);i++){      
    PUTCHAR((INT8U)((cmds[i].cmd >>8) & 0xFF));
    PUTCHAR((INT8U)(cmds[i].cmd & 0xFF));    
  #if (HELP_DESCRIPTION == 1)
    PUTCHAR('-');
    PRINT(ListOfCmdDesc[i]);
  #endif      
    PUTCHAR(CR);
    PUTCHAR(LF);
  }
#endif

  CMD_END();
}

CMD_FUNC(M64)
{  
  
  CMD_FUNC_UNUSED_ARG();
  extern const INT8U mac64Address[];
  
  INT8U i;
  
  CMD_BEGIN(M64);  
    for(i=0;i<8;i++){
        PUTCHAR(mac64Address[i]); 
    }   
  CMD_END();
}

CMD_FUNC(M16) 
{  
  
  CMD_FUNC_UNUSED_ARG();
  extern volatile INT16U macAddr;
  
  CMD_BEGIN(M16);
    PUTCHAR((INT8U)(macAddr >> 8));
    PUTCHAR((INT8U)(macAddr & 0xFF));
  CMD_END();
}


CMD_FUNC(C_ON){ 

    CMD_FUNC_UNUSED_ARG();
    
    NetSimpleCommand(UP_ROUTE, GENERAL_ONOFF, ON, 0);
  
    /* confirmation */
    CMD_BEGIN(C_ON);
    CMD_END();
}

CMD_FUNC(C_OFF){ 
   
    CMD_FUNC_UNUSED_ARG();
   
    NetSimpleCommand(UP_ROUTE, GENERAL_ONOFF, OFF, 0);
  
    /* confirmation */
    CMD_BEGIN(C_OFF);
    CMD_END();
}

/* Get the GPS position logged */
void RequestGPSAddress(INT32U *x, INT32U *y)
{
  OS_SR_SAVE_VAR;
  OSEnterCritical();
    *x = GPS_X.int32u;
    GPS_X.int32u = 0;
    *y = GPS_Y.int32u;
    GPS_Y.int32u = 0;
  OSExitCritical();
}

INT16U RequestNodeID(void){
  
  INT16U id;  
  OS_SR_SAVE_VAR;
  OSEnterCritical();
    id = node_id_received;
  OSExitCritical();
  return id;
}

CMD_FUNC(CPU) 
{
  
  CMD_FUNC_UNUSED_ARG();
  INT16U percent = 0;
 
  UserEnterCritical();
  percent = LastOSDuty;
  percent = (INT16U)((percent*100)/TIMER_MODULE);
  UserExitCritical();    

  CMD_BEGIN(CPU);
  
  if (percent >= 100)  percent = 100;

  PUTCHAR((INT8U)(percent));
  
  CMD_END();  
}
  
CMD_FUNC(SNIF) 
{
  
  extern GPSNET_NEIGHBOURHOOD_TABLE nb_table[NEIGHBOURHOOD_SIZE];  
  INT8U i = 0;
    
  if (SMIndex == 0)
  {
    node_id_received_tmp = (INT16U)(message << 8); 
    SMIndex++; 
    return CMD_ARG;                               
  }else
  {            
    SMIndex = 0;     
    node_id_received_tmp = (INT16U)(node_id_received_tmp + message);                                   
    UserEnterCritical();
      node_id_received = node_id_received_tmp;
      node_id_received_tmp = 0;
    UserExitCritical();              
  }   
    
  /* execute command */
  CMD_BEGIN(SNIF);
  
  for (i=0;i<NEIGHBOURHOOD_SIZE;i++) 
  {
    PUTCHAR((CHAR8)nb_table[i].Addr_16b_1);    
    PUTCHAR((CHAR8)nb_table[i].Addr_16b_2);    
    PUTCHAR(nb_table[i].NeighborRSSI); 
    PUTCHAR(nb_table[i].Symmetric); 
    PUTCHAR(nb_table[i].ParentCnt);          
  }   
  
  CMD_END();
}
    
      
  
CMD_FUNC(VER) 
{
  CMD_FUNC_UNUSED_ARG();
  CMD_BEGIN(VER);
  PRINT(BRTOS_VERSION);
  PRINT(GPSNET_VERSION);
  CMD_END();
}
  
  
CMD_FUNC(UPT) 
{
  CMD_FUNC_UNUSED_ARG();
  OSTime time;
  OSDate date;
  
  UserEnterCritical();
  time = OSUptime();
  date = OSUpDate();
  UserExitCritical();
  
  CMD_BEGIN(UPT);
  PUTCHAR((CHAR8)date.RTC_Day);
  PUTCHAR((CHAR8)time.RTC_Hour);
  PUTCHAR((CHAR8)time.RTC_Minute);
  PUTCHAR((CHAR8)time.RTC_Second);
  CMD_END();
}
  
  
CMD_FUNC(LED) 
{
  
  CMD_FUNC_UNUSED_ARG();
  CMD_BEGIN(LED);
  CMD_END();
  
  #ifdef LED_HEARTBEAT_TOGGLE
    LED_HEARTBEAT_TOGGLE();
  #endif  
  
}

CMD_FUNC(GPSADDR)
{
    
    if (SMIndex < 4)
    {
      GPS_X_tmp.int8u[SMIndex] = message;
      SMIndex++;
      return CMD_ARG;
    }else
    {
      GPS_Y_tmp.int8u[(SMIndex-4)] = message;
      SMIndex++;
      if (SMIndex >= 8) 
      {
        SMIndex = 0;              
        /* It is safe to log the value. */
        UserEnterCritical();
          GPS_X.int32u = GPS_X_tmp.int32u;
          GPS_Y.int32u = GPS_Y_tmp.int32u;
        UserExitCritical();
        
        CMD_BEGIN(GPSADDR);  
        CMD_END();                       
      }
    }
}  
   
CMD_FUNC(NGB)   
{
  
  CMD_FUNC_UNUSED_ARG();
  
  INT8U AddrHigh;
  INT8U AddrLow;
  INT8U cnt = 0;
  
  CMD_BEGIN(NGB);
  
  for (cnt=0;cnt<NEIGHBOURHOOD_SIZE;cnt++) 
  {  
    
    if (gpsnet_neighbourhood[cnt].Addr_16b != 0xFFFE) 
    {
        
      AddrHigh  = (INT8U)(gpsnet_neighbourhood[cnt].Addr_16b >> 8);
      AddrLow   = (INT8U)((gpsnet_neighbourhood[cnt].Addr_16b) & 0xFF);
      
      PUTCHAR(AddrHigh);
      PUTCHAR(AddrLow);
      
      PUTCHAR(gpsnet_neighbourhood[cnt].NeighborStatus.bits.Symmetric);
      PUTCHAR(gpsnet_neighbourhood[cnt].NeighborLQI);
      PUTCHAR(gpsnet_neighbourhood[cnt].NeighborRSSI);
                                     
      PUTCHAR(gpsnet_neighbourhood[cnt].NeighborGPS_Lat[0]);
      PUTCHAR(gpsnet_neighbourhood[cnt].NeighborGPS_Lat[1]);
      PUTCHAR(gpsnet_neighbourhood[cnt].NeighborGPS_Lat[2]);
      PUTCHAR(gpsnet_neighbourhood[cnt].NeighborGPS_Lat[3]);
      
      PUTCHAR(gpsnet_neighbourhood[cnt].NeighborGPS_Long[0]);
      PUTCHAR(gpsnet_neighbourhood[cnt].NeighborGPS_Long[1]);
      PUTCHAR(gpsnet_neighbourhood[cnt].NeighborGPS_Long[2]);
      PUTCHAR(gpsnet_neighbourhood[cnt].NeighborGPS_Long[3]);              
      
      PUTCHAR(gpsnet_neighbourhood[cnt].BaseDepth[0]);
      PUTCHAR(gpsnet_neighbourhood[cnt].BaseDepth[1]);
      PUTCHAR(gpsnet_neighbourhood[cnt].BaseDepth[2]);
      PUTCHAR(gpsnet_neighbourhood[cnt].BaseDepth[3]);
      PUTCHAR(gpsnet_neighbourhood[cnt].BaseDepth[4]);
      PUTCHAR(gpsnet_neighbourhood[cnt].BaseDepth[5]);
    } 
  }

  CMD_END();
  
}
  
  
CMD_FUNC(NNB) 
{
  CMD_FUNC_UNUSED_ARG();
  INT8U number_of_neighbors = 0;
  INT8U cnt = 0;

  for (cnt=0;cnt<NEIGHBOURHOOD_SIZE;cnt++) 
  {
    if (gpsnet_neighbourhood[cnt].Addr_16b != 0xFFFE) 
    {
      number_of_neighbors++;     
    }
  }

  CMD_BEGIN(NNB);      
  PUTCHAR(number_of_neighbors);    
  CMD_END();   
}  

CMD_FUNC(RPK)
{
    CMD_FUNC_UNUSED_ARG();
    INT8U cnt = 0;
    INT8U i   = 0;
    INT8U c   = 0;
    INT8U app_payload   = 0;
    INT8U number_of_packets = 0;
    
    UserEnterCritical();
    number_of_packets = PacketsCnt;
    UserExitCritical();
    
    // Inicia a mensagem
    CMD_BEGIN(RPK); 
    
    // Define quantos pacotes serao enviados
    PUTCHAR(number_of_packets);
        
    // Envia pacotes
    for (cnt=0;cnt<number_of_packets;cnt++) 
    {  
        // Envia cabecalho padrao dos pacotes
        for(i=0;i<16;i++)
        {
            OSRQueue(&PacketsBuffer,&c);
            PUTCHAR(c);
        }
        
        app_payload = c;
        
        // Envia dados adicionais da camada de aplicacao
        for(i=0;i<app_payload;i++)
        {
            OSRQueue(&PacketsBuffer,&c);
            PUTCHAR(c);
        }

    }
    
    // Retira os pacotes transmitidos da contagem de pacotes no buffer
    UserEnterCritical();
    if (number_of_packets > 0) 
    {
      PacketsCnt -= number_of_packets;
    }
    UserExitCritical();    

    // Termina a mensagem
    CMD_END();  
    
}

void SendPacketToQueue(void)
{
    INT8U i      = 0;
    INT8U status = 0;       
    
    // Endereço MAC do nó fonte
    (void)OSWQueue(&PacketsBuffer,(INT8U)(mac_packet.SrcAddr_16b >> 8));
    (void)OSWQueue(&PacketsBuffer,(INT8U)(mac_packet.SrcAddr_16b & 0xFF));
    
    // Numero de saltos do pacote
    (void)OSWQueue(&PacketsBuffer,nwk_packet.NWK_Packet_Life);
    
    // Endereço GPS do nó fonte
    (void)OSWQueue(&PacketsBuffer,nwk_packet.NWK_Src_Lat[0]);
    (void)OSWQueue(&PacketsBuffer,nwk_packet.NWK_Src_Lat[1]);
    (void)OSWQueue(&PacketsBuffer,nwk_packet.NWK_Src_Lat[2]);
    (void)OSWQueue(&PacketsBuffer,nwk_packet.NWK_Src_Lat[3]);
    
    (void)OSWQueue(&PacketsBuffer,nwk_packet.NWK_Src_Long[0]);
    (void)OSWQueue(&PacketsBuffer,nwk_packet.NWK_Src_Long[1]);
    (void)OSWQueue(&PacketsBuffer,nwk_packet.NWK_Src_Long[2]);
    (void)OSWQueue(&PacketsBuffer,nwk_packet.NWK_Src_Long[3]);
    
    // Cabecalho da aplicação
    (void)OSWQueue(&PacketsBuffer,app_packet.APP_Identify);
    (void)OSWQueue(&PacketsBuffer,app_packet.APP_Profile);
    (void)OSWQueue(&PacketsBuffer,app_packet.APP_Command);
    (void)OSWQueue(&PacketsBuffer,app_packet.APP_Command_Attribute);
    (void)OSWQueue(&PacketsBuffer,app_packet.APP_Command_Size);
    
    for(i=0;i<app_packet.APP_Command_Size;i++)
    {
      status = OSWQueue(&PacketsBuffer,app_packet.APP_Payload[i]);
    }        
    
    if (status != WRITE_BUFFER_OK)
    {
      (void)OSCleanQueue(Pkt);
      UserEnterCritical();
      PacketsCnt = 0;
      UserExitCritical();
    }else 
    {
      UserEnterCritical();
      PacketsCnt++;
      UserExitCritical();
    }
}


  

