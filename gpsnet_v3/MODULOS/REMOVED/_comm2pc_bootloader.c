#include "comm2pc.h"
#include "app.h"
#include "gpsnet_api.h"
#include "drivers.h"

#if (BOOTLOADER_ENABLE == 1)
  #include "MCF51_Bootloader.h"  
  #include "Bootloader_wireless.h"  
  #include "Bootloader_serial.h" 
#endif 


static UCHAR_WORD cmd = {0,0};
static INT8U  currentstate = 0;
static INT8U  SMIndex = 0;

static UINT_DWORD GPS_X = {0,0,0,0};
static UINT_DWORD GPS_Y = {0,0,0,0};
static UINT_DWORD GPS_X_tmp = {0,0,0,0};
static UINT_DWORD GPS_Y_tmp = {0,0,0,0}; 

static INT16U node_id_received = 0xFFFE;
static INT16U node_id_received_tmp = 0;              


static INT8U PacketsCnt = 0;   // Packets counter
OS_QUEUE      PacketsBuffer;   // Packets queue struct
BRTOS_Queue  *Pkt;

/* Function to send one byte via USB CDC */
void USB_putchar(char c)
{
  while(c != (char)cdc_putch(c)){};
}

/* Function to print a string via USB CDC */

void USB_print(char *s)
{
  while(*s++){    
    while((*s) != (char)cdc_putch(*s)){};    
  }
}

/* Finite state machine code to handle communication with PC */
INT8U Comm2PC_FSM (INT8U message) 
{        
    INT32U status = 0;
    INT8U i = 0;
    
    switch (currentstate) 
    {
        case BEGIN:
          
          if (message == MSG_START) 
          {
            currentstate = COMMAND_A;     
          } 
          else 
          {
            currentstate = BEGIN;
            return COMMAND_INVALID;  
          }
        break;
        case COMMAND_A:
          cmd.int8u[0] = message;
          currentstate = COMMAND_B;
        
        break;
        case COMMAND_B:                              
            cmd.int8u[1] = message;
            switch (cmd.int16u)
            {
              case CPU:
              case VER:
              case UPT: 
              case LED:              
              case NGB:              
              case NNB: 
              case RPK:
              case LSNIF:
                currentstate = END;
              break;
              
              case GAD:
                SMIndex = 0;
                currentstate = GPS_ADDRESS;
              break;
              
              case SNIF:
                SMIndex = 0;
                currentstate = NODE_ID;
              break;
              
              case ERASE_FLASH:
                  currentstate = END;
                  break;                
              break;
              
              case STORE_FIRMWARE:
                  estado_bootloader = PROG;
                  currentstate      = RECEIVE_FIRMWARE;
              break;              
              
              case FOTA:
                SMIndex = 0;
                currentstate = BOOT_NODE;
              break;                 
              
              default:
                currentstate = BEGIN;
                return COMMAND_UNKNOWN;
              break;

            }
        break;
        
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
              currentstate = END;
            }
          }
          break;
          
        case NODE_ID: 
        {
          if (SMIndex == 0)
          {
            node_id_received_tmp = (INT16U)(message << 8);
            SMIndex++;
            break;                 
          }
          if (SMIndex >= 1) 
          {            
            node_id_received_tmp = (INT16U)(node_id_received_tmp | message);
            currentstate = END;
            SMIndex = 0;
            
            UserEnterCritical();
              node_id_received = node_id_received_tmp;
              node_id_received_tmp = 0;
            UserExitCritical(); 
            break;             
          } 
        }        
        break;
          
        case BOOT_NODE:
          GPS_X_tmp.int8u[SMIndex++] = message;
          if (SMIndex == 2) 
          {
            boot_node_id = (INT16U)((GPS_X_tmp.int8u[0] << 8) | GPS_X_tmp.int8u[1]);
            GPS_X_tmp.int32u = 0;
            SMIndex = 0;
            currentstate = END;            
          }
          break;          
          
        case RECEIVE_FIRMWARE:
          
          status = Bootloader_FSM(message);
          if (status != DATA_OK) {            
              currentstate = END;
          }
          break;
        
        case END:
          if (message == MSG_END) 
          {
            switch (cmd.int16u)
            {
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
              case ERASE_FLASH:
                CMD_ERASE_FLASH();
              break;
              case STORE_FIRMWARE:
                CMD_STORE_FIRMWARE();
              break;
              case FOTA:
                CMD_FOTA();
              break;      
              case SNIF:
              case LSNIF:
                CMD_SNIF();               
              break;
              case C_ON:
                CMD_ON();
              case C_OFF:
                CMD_OFF();                
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

INT16U RequestNodeID(void){
  
  INT16U id;  
  OS_SR_SAVE_VAR;
  OSEnterCritical();
    id = node_id_received;
  OSExitCritical();
  return id;
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
  
  extern GPSNET_NEIGHBOURHOOD_TABLE nb_table[NEIGHBOURHOOD_SIZE];
  
  INT8U c = 0;
  PUTCHAR(MSG_START);
  PUTCHAR('S');
  PUTCHAR('N');
  for (c=0;c<NEIGHBOURHOOD_SIZE;c++) 
  {
    PUTCHAR((CHAR8)nb_table[c].Addr_16b_1);    
    PUTCHAR((CHAR8)nb_table[c].Addr_16b_2);    
    PUTCHAR(nb_table[c].NeighborRSSI); 
    PUTCHAR(nb_table[c].Symmetric); 
    PUTCHAR(nb_table[c].ParentCnt);
  }   
  PUTCHAR(MSG_END);
  CMD_PROCESS();  
}
    
      
  
void CMD_VER (void) 
{
  PUTCHAR(MSG_START);
  PUTCHAR('V');
  PUTCHAR('E');
  PUTCHAR(1);
  PUTCHAR(67);
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
  
  PTCD_PTCD0 = ~PTCD_PTCD0;
  
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
    
    CMD_PROCESS();
    
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


