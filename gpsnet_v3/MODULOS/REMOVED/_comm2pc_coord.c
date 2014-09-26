/**********************************************************************************
@file   comm2pc.c
@brief  Functions to communicate with a PC
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
*********************************************************************************/


#include "comm2pc.h"
#include "drivers.h"
#include "app.h"
#include "gpsnet_api.h"

/* List of supported commands */
static const INT16U ListOfCommands[] = {
  HELP, SND_CMD, CPU, VER, LED, NGB, NNB, UPT, RPK, GAD, SNIF, C_ON, C_OFF, 
};

#define HELP_DESCRIPTION 1
#if (HELP_DESCRIPTION == 1)
static const INT8U* ListOfDesc[] = {
"This Help",
"Send Command",
"Cpu usage",
"Version",
"On/off LED",
"Get neighbors",
"Num. of neighbors",
"Uptime",
"Get packets",
"Get GPS address",
"Sniffer",
"Command ON",
"Command OFF"
};
#endif

/* Variables of state machine terminal command  */
static UCHAR_WORD cmd = {0,0};
static INT8U  currentstate = 0;
static INT16U cmd_to_send = 0; 
static INT8U  SMIndex = 0;
static UINT_DWORD GPS_X = {0,0,0,0};
static UINT_DWORD GPS_Y = {0,0,0,0};
static UINT_DWORD GPS_X_tmp = {0,0,0,0};
static UINT_DWORD GPS_Y_tmp = {0,0,0,0};


/* Queue for network packets */
static INT8U  PacketsCnt = 0;   // Contador de pacotes na fila
OS_QUEUE      PacketsBuffer;    // Declara uma estrutura de fila
BRTOS_Queue  *Pkt;
BRTOS_Mutex  *PktQueueMutex;

/* Function to send one byte via USB CDC */
void USB_putchar(char c);

void USB_putchar(char c)
{
  while(c != (char)cdc_putch(c)){};
}
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
#define CMD_PROCESS() 
#endif

/* Finite state machine code to handle communication with PC */
/* Get commands via USB or UART */
/* Commands are named with two letters. 
E.g. CP for 'CPU Usage command', 'HP' for Help Command, etc... 
*/

INT8U Comm2PC_FSM (INT8U message) 
{        
    
    switch (currentstate) 
    {
        /* get start byte */
        case BEGIN:            
          if (message == MSG_START) 
          {
            currentstate = COMMAND;
            SMIndex = 0;     
          } 
          else 
          {
            currentstate = BEGIN;
            CMD_ERROR();
            return COMMAND_INVALID;
          }
        break;
        
        /* get command */
        case COMMAND:
          if(SMIndex < 1){            
            cmd.int8u[0] = message;
            SMIndex++;  
          }else{
            cmd.int8u[1] = message;
            SMIndex = 0;
            /* if command is to be sent */
            switch(cmd.int16u){
              case SND_CMD:
              case GAD:                
                currentstate = GPS_ADDRESS;
                break;
              default:
                currentstate = END;
                break;
            }
          }       
        break;

        /* get destination address */
        case GPS_ADDRESS:
          if (SMIndex < 4)
          {
            GPS_X_tmp.int8u[SMIndex] = message;
            SMIndex++;
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
              switch(cmd.int16u){
                case GAD:
                  currentstate = END;
                  break;
                default:
                  currentstate = CMD_ARGS;
                  break;
              }
              
            }
          }
          break;  
                                      
        /* get command */
        case CMD_ARGS:
          if (SMIndex < 1){
             cmd_to_send = message;
             SMIndex++;
          }else{
            cmd_to_send = (INT16U)((cmd_to_send << 8) | message);
            SMIndex = 0;
            currentstate = END;
          }
         break;
          
        /* exec. command */  
        case END:
          if (message == MSG_END) 
          {
            switch (cmd.int16u)
            {
              case HELP:
                CMD_HELP();
              break;
              case VER:
                CMD_VER();
              break;
              case CPU:
                CMD_CPU();
              break;
              case UPT:
                CMD_UPT();
              break;              
              case LED:
                CMD_LED();
              break;
              case NGB:
                CMD_NEIGHBORS();
              break;
              case NNB:
                CMD_NUMBER_OF_NEIGHBORS();
              break;
              case RPK:
                CMD_REQ_PACKETS();
              break;
              case GAD:
                CMD_GPS_ADDRESS();
              break; 
              
              case SND_CMD:
                switch(cmd_to_send){
                  case SNIF:
                    CMD_SNIF();
                  break;
                  case C_ON:
                    CMD_ON();
                  break;
                  case C_OFF:
                    CMD_OFF();
                  break; 
                  default:
                    CMD_ERROR();
                    return COMMAND_UNKNOWN;
                  break; 
                
                }
              break;
              default:
                 CMD_ERROR();
                 return COMMAND_UNKNOWN;
              break;                               
             
            }

            currentstate = BEGIN;
            
          } 
          else 
          {
            currentstate = BEGIN;
            return COMMAND_INVALID;  
            
          }
        break;
        
        default:
          currentstate = BEGIN;
          SMIndex = 0;
          break;
        
      }
     
      return 0;
}

/* Error message for unknown or invalid command */
void CMD_ERROR(void){
   PUTCHAR(MSG_START);
   PUTCHAR('E');
   PUTCHAR('R');
   PUTCHAR(MSG_END);
           
   CMD_PROCESS();  
}

/* List supported commands */
void CMD_HELP(void){
   INT8U i=0;
   
   /* confirmation */
   PUTCHAR(MSG_START);

   for(i=0;i<(sizeof(ListOfCommands) >> 1);i++){      
      PUTCHAR((INT8U)((ListOfCommands[i]>>8) & 0xFF));
      PUTCHAR((INT8U)(ListOfCommands[i] & 0xFF));
#if (HELP_DESCRIPTION == 1)
      PUTCHAR('-');
      PRINT(ListOfDesc[i]);
#endif      
      PUTCHAR(CR);
      PUTCHAR(LF);
   }
   
   PUTCHAR(MSG_END);
           
   CMD_PROCESS();

}


void CMD_ON(void){ 

   NetSimpleCommand(UP_ROUTE, GENERAL_ONOFF, ON, 0);
  
   /* confirmation */
   PUTCHAR(MSG_START);
   PUTCHAR('O');
   PUTCHAR('N');
   PUTCHAR(MSG_END);
           
   CMD_PROCESS(); 

}

void CMD_OFF(void){ 

   NetSimpleCommand(UP_ROUTE, GENERAL_ONOFF, OFF, 0);
  
   /* confirmation */
   PUTCHAR(MSG_START);
   PUTCHAR('O');
   PUTCHAR('F');
   PUTCHAR(MSG_END);
           
   CMD_PROCESS(); 

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


void CMD_CPU (void) 
{
    INT16U percent = 0;
   
    UserEnterCritical();
    percent = LastOSDuty;
    percent = (INT16U)((percent*100)/TIMER_MODULE);
    UserExitCritical();  
  
  
    PUTCHAR(MSG_START);
    PUTCHAR('C');
    PUTCHAR('P');
    if (percent >= 100)
    {
      PUTCHAR(100);       
    }
    else
    {
      PUTCHAR((INT8U)(percent));
    }
    PUTCHAR(MSG_END);
    CMD_PROCESS();
  }
  
void CMD_SNIF (void) 
{
    
    extern GPS_NEIGHBOURHOOD_TABLE nb_table[NEIGHBOURHOOD_SIZE];     
    INT8U c = 0;
    
    LATITUDE   lat;
    LONGITUDE  lon;
    
    /* get destination */
    RequestGPSAddress(&(lat.x),&(lon.y));

/*    
    lat.x =  GPS_X.int32u;
    lon.y =  GPS_Y.int32u;
*/
    
    /* send the request */
    SniferReq(UP_ROUTE, &lat, &lon); 
    
    PUTCHAR(MSG_START);
    PUTCHAR('S');
    PUTCHAR('N');
    for (c=0;c<NEIGHBOURHOOD_SIZE;c++) 
    {
      PUTCHAR((CHAR8)nb_table[c].Addr_16b_1);    
      PUTCHAR((CHAR8)nb_table[c].Addr_16b_2);    
      PUTCHAR(nb_table[c].NeighborRSSI); 
      PUTCHAR(nb_table[c].Symmetric);    
         
    }   
    PUTCHAR(MSG_END);
    CMD_PROCESS();  
}
    
      
  
void CMD_VER (void) 
{
    INT8U *p = BRTOS_VERSION; 
       
    PUTCHAR(MSG_START);
    PUTCHAR('V');
    PUTCHAR('E');
    PUTCHAR(' ');
    
    while(*p){      
      PUTCHAR((INT8U)(*p++));
    }

    PUTCHAR(MSG_END);
    CMD_PROCESS();
}
  
  
void CMD_UPT (void) 
{
  OSTime time;
  OSDate date;
  
  UserEnterCritical();
  time = OSUptime();
  date = OSUpDate();
  UserExitCritical();
  
  PUTCHAR(MSG_START);
  PUTCHAR('U');
  PUTCHAR('P');
  PUTCHAR((CHAR8)date.RTC_Day);
  PUTCHAR((CHAR8)time.RTC_Hour);
  PUTCHAR((CHAR8)time.RTC_Minute);
  PUTCHAR((CHAR8)time.RTC_Second);
  PUTCHAR(MSG_END);
  CMD_PROCESS();
}
  
  
void CMD_LED (void) 
{
  PUTCHAR(MSG_START);
  PUTCHAR('L');
  PUTCHAR('E');
  PUTCHAR(MSG_END);
  
  PTGD_PTGD0 = ~PTGD_PTGD0;
  
  CMD_PROCESS();
  
}
  
void CMD_GPS_ADDRESS (void) 
{
  PUTCHAR(MSG_START);
  PUTCHAR('G');
  PUTCHAR('A');
  PUTCHAR(MSG_END);
         
  CMD_PROCESS();
  
}  
 
void CMD_NEIGHBORS (void)   
{
    INT8U AddrHigh;
    INT8U AddrLow;
    INT8U cnt = 0;
    
    PUTCHAR(MSG_START);
    PUTCHAR('N');
    PUTCHAR('B');
    
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

    PUTCHAR(MSG_END); 
    
    CMD_PROCESS();
    
}
  
  
void CMD_NUMBER_OF_NEIGHBORS (void) 
{
    INT8U number_of_neighbors = 0;
    INT8U cnt = 0;
    
    for (cnt=0;cnt<NEIGHBOURHOOD_SIZE;cnt++) 
    {
      if (gpsnet_neighbourhood[cnt].Addr_16b != 0xFFFE) 
      {
        number_of_neighbors++;     
      }
    }

    PUTCHAR(MSG_START);
    PUTCHAR('N');
    PUTCHAR('N');        
    PUTCHAR(number_of_neighbors);    
    PUTCHAR(MSG_END);    
     
    CMD_PROCESS();    
}
 
void CMD_REQ_PACKETS (void)
{
    INT8U cnt = 0;
    INT8U i   = 0;
    INT8U c   = 0;
    INT8U app_payload   = 0;
    INT8U number_of_packets = 0;
    
    // OSMutexAcquire(PktQueueMutex);
    
    UserEnterCritical();
      number_of_packets = PacketsCnt;
    UserExitCritical();
    
    // Inicia a mensagem
    PUTCHAR(MSG_START);
    
    // Envia o comando
    PUTCHAR('R');
    PUTCHAR('P');    
    
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

    // Termina a mensagem
    PUTCHAR(MSG_END);    
    
    // Retira os pacotes transmitidos da contagem de pacotes no buffer
    UserEnterCritical();
    if (number_of_packets > 0) 
    {
      PacketsCnt -= number_of_packets;
    }
    UserExitCritical();    
    
    // OSMutexRelease(PktQueueMutex);
    
    CMD_PROCESS();
}

/* Used to log received packets */
void SendPacketToQueue(void)
{
    INT8U i      = 0;
    INT8U status = 0;
         
    OSMutexAcquire(PktQueueMutex);

    if(PacketsBuffer.OSQEntries + 16 + app_packet.APP_Command_Size <= PacketsBuffer.OSQSize){
          
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
   
    OSMutexRelease(PktQueueMutex);
}
