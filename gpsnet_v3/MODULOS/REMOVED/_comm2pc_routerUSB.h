/***********************************************************************************
@file   comm2pc.h
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

#include "BRTOS.h"  
#include "AppConfig.h"

// errors   
#define COMMAND_OK       0
#define COMMAND_INVALID  1  
#define COMMAND_UNKNOWN  2

// possible states                    
typedef enum Comm2PC_FSM_States 
{
  BEGIN,        // start ($) of a message
  COMMAND,      // command
  CMD_ARG,      // args
  END           // end of a message
}COMM2PC_ST;

typedef COMM2PC_ST (*pf_cmd)(INT8U);

typedef struct {
   INT16U cmd;
   pf_cmd cmd_func;
}cmd_t;
  
#define MSG_START '$'
#define MSG_END   '#'

/* Supported commands */
/* Must be listed in alphabetical order */
/*  ------ NAME ------- CODE --- */
#define COMMAND_TABLE(ENTRY) \
    ENTRY(ERR,  0,"Command not found") \
    ENTRY(M16, '16',"MAC address 16bits") \
    ENTRY(M64, '64', "MAC address 64bits") \
    ENTRY(CPU,  'CP',"Cpu usage") \
    ENTRY(GPSADDR, 'GA',"Set GPS address") \
    ENTRY(HELP, 'HP', "This Help") \
    ENTRY(LED,  'LE', "On/off LED") \
    ENTRY(NGB,  'NB',"Get neighbors") \
    ENTRY(NNB,  'NN',"Num. of neighbors") \
    ENTRY(C_OFF, 'OF',"Command OFF") \
    ENTRY(C_ON, 'ON',"Command ON") \
    ENTRY(RPK,  'RP',"Get packets") \
    ENTRY(SEND, 'SD',"Send Data") \
    ENTRY(SNIF, 'SN',"Sniffer") \
    ENTRY(UPT,  'UP',"Uptime") \
    ENTRY(VER,  'VE',"OS and NET versions")
     
   
    //ENTRY(ERASE_FLASH, 'EF', "Flash erase") \
    //ENTRY(STORE_FIRMWARE, 'SF', ""Flash load") \
    //ENTRY(LSNIF, 'LS', "Return sniffer values") \    
    //ENTRY(FOTA, 'FO', "Send firmware over the air") \       
    
#define EXPAND_AS_COMMAND_CODE_ENUM(a,b,c)    a = b,  
#define EXPAND_AS_STRUCT(a,b,c)               INT8U a;   
#define EXPAND_AS_JUMPTABLE(a,b,c)            {a, &CMD_##a},
#define EXPAND_AS_PROTOTYPES(a,b,c)           COMM2PC_ST CMD_##a(INT8U);
#define EXPAND_AS_DESCRIPTIONS(a,b,c)         c,

enum {
    COMMAND_TABLE(EXPAND_AS_COMMAND_CODE_ENUM)
};

typedef  struct{
    COMMAND_TABLE(EXPAND_AS_STRUCT)
} size_struct_t;

#define NUMBER_OF_COMMANDS sizeof(size_struct_t)

COMMAND_TABLE(EXPAND_AS_PROTOTYPES)


#define HELP_COMMAND_ENABLED     1
#define HELP_DESCRIPTION         1
#if (HELP_DESCRIPTION == 1)
static const INT8U* ListOfCmdDesc[NUMBER_OF_COMMANDS] = {
  COMMAND_TABLE(EXPAND_AS_DESCRIPTIONS)
};
#endif
   

#define STATIC_ASSERT(pred)      switch(0){case 0:case pred:;}

#define CMD_FUNC(x)              COMM2PC_ST CMD_##x(INT8U message)
#define CMD_FUNC_UNUSED_ARG()    (void)message;


INT8U  Comm2PC_FSM(INT8U message);

void   SendPacketToQueue(void);
void   RequestGPSAddress(INT32U *x, INT32U *y);
INT16U RequestNodeID(void); 


// Declara uma estrutura de fila
extern OS_QUEUE      PacketsBuffer;
extern BRTOS_Queue  *Pkt; 

    