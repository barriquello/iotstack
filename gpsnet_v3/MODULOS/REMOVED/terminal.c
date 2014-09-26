/****************************************************************************
 *
 *            Copyright (c) 2006-2007 by CMX Systems, Inc.
 *
 * This software is copyrighted by and is the sole property of
 * CMX.  All rights, title, ownership, or other interests
 * in the software remain the property of CMX.  This
 * software may only be used in accordance with the corresponding
 * license agreement.  Any unauthorized use, duplication, transmission,
 * distribution, or disclosure of this software is expressly forbidden.
 *
 * This Copyright notice may not be removed or modified without prior
 * written consent of CMX.
 *
 * CMX reserves the right to modify this software without notice.
 *
 * CMX Systems, Inc.
 * 12276 San Jose Blvd. #511
 * Jacksonville, FL 32223
 * USA
 *
 * Tel:  (904) 880-1840
 * Fax:  (904) 880-1632
 * http: www.cmx.com
 * email: cmx@cmx.com
 *
 ***************************************************************************/
#include "hcc_types.h"
#include "terminal.h"
#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
 * Macro definitions
 *****************************************************************************/
/* This function shall send one character over the communication interface.
   Shall be compatibile with the following definition:
      void func(char) */
#define put_char cdc_putch

/* This function shall return one character received over the communication
   interface. Shall be compatibile with the following definition:
      char func(void) */

#define get_char cdc_getch
/* This function shall return nonzero if there is an unread character in the
   bufer of the communication interface. Shall be compatibile with the following
   definition:
      <integer type> func(void)
   integer type is char, int, etc...*/
#define has_input cdc_input_ready

/*****************************************************************************
 * Local types.
 *****************************************************************************/
typedef void (cmd_func)(char *params);

typedef struct {
  const char *txt;
  cmd_func * func;
  const char *help_txt;
} command;

/*****************************************************************************
 * External references.
 *****************************************************************************/
extern char cdc_getch(void);
extern int cdc_input_ready(void);
extern void cdc_putch(char c);

/*****************************************************************************
 * Function predefinitions.
 *****************************************************************************/
static void print_greeting(void);
static void cmd_help(char *param);
static void print_prompt(void);
static void print_greeting(void);
static int find_command(char *name);

static cmd_func cmd_help;
static cmd_func cmd_greet;

/*****************************************************************************
 * Module variables.
 *****************************************************************************/
static const command commands[] = {
  { "help", cmd_help, "Prints help about commands. " },
  { "greet", cmd_greet, "Prints a nice greeting message."}
};

static char cmd_line[0xff];
static hcc_u8 cmd_line_ndx;


/*****************************************************************************
 * Name:
 *    skipp_space
 * In:
 *    ep - endpoint number
 * Out:
 *    0 - it was disabled
 *    1 - it was enabled
 *
 * Description:
 *    Will disable interrupt generation of an endpoint.
 *
 * Assumptions:
 *
 *****************************************************************************/
int skipp_space(char *cmd_line, int start)
{
  /* Skip leading whitespace. */
  while(cmd_line[start] == ' ' || cmd_line[start] == '\t')
  {
    start++;
  }
  return(start);
}

/*****************************************************************************
 * Name:
 *    find_word
 * In:
 *    cmd_line - pointer to string to be processed
 *    start    - start offset of word
 *
 * Out:
 *    Index of end of word.
 *
 * Description:
 *    Will find the end of a word (first space, tab or end of line).
 *
 * Assumptions:
 *    --
 *****************************************************************************/
int find_word(char *cmd_line, int start)
{
  /* Find end of this word. */
  while(cmd_line[start] != ' ' && cmd_line[start] != '\t'
        && cmd_line[start] != '\n' && cmd_line[start] != '\0')
  {
    start++;
  }

  return(start);
}

/*****************************************************************************
 * Name:
 *    cmp_str
 * In:
 *    a - pointer to string one
 *    b - pointer to string two
 * Out:
 *    0 - strings differ
 *    1 - strings are the same
 * Description:
 *    Compare two strings.
 *
 * Assumptions:
 *    --
 *****************************************************************************/
int cmp_str(char *a, char *b)
{
  int x=0;
  while(a[x] != '\0' && b[x] != '\0' && a[x] == b[x])
  {
    x++;
  }

  if (a[x] == b[x])
  {
    return(1);
  }
  return(0);
}

/*****************************************************************************
 * Name:
 *    print
 * In:
 *    text - pointer to string to be printed
 *
 * Out:
 *    N/A
 *
 * Description:
 *    Print the suplied string on the output stream.
 *
 * Assumptions:
 *    --
 *****************************************************************************/
void print(char *text)
{
  int x=0;
  while(text[x] != '\0')
  {
    put_char(text[x++]);
  }
}

/*****************************************************************************
* Name:
*    cmd_help
* In:
*    param - pointer to string containing parameters
*
* Out:
*    N/A
*
* Description:
*    Will print greeting message, and name and help text of all commands.
*
* Assumptions:
*    --
*****************************************************************************/
static void cmd_help(char *param)
{
  int x;

  print_greeting();
  print("It supports the following commands:\r\n");

  for(x=0; x < sizeof(commands)/sizeof(commands[0]); x++)
  {
    print("  ");
    print((char *)commands[x].txt);
    print(":\t");
    print((char *)commands[x].help_txt);
    print("\r\n");
  }
  print("\r\n");
}

/*****************************************************************************
* Name:
*    cmd_greet
* In:
*    N/A
*
* Out:
*    N/A
*
* Description:
*    Print a nice greeting message.
*
* Assumptions:
*    --
*****************************************************************************/
void cmd_greet(char *param)
{
  print("**************************************\r\n");
  print(" Hello! This is a simple USB CDC\r\n");
  print(" demo application from CMX-Embedded.\r\n");
  print(" You may execute simple commands on\r\n");
  print(" the target. \r\n");
  print(" You can list the avaiable\r\n");
  print(" commands command by issuing help.\r\n");
  print(" \r\n");
  print(" Have a nice day! \r\n");
  print("**************************************\r\n");
}


/*****************************************************************************
* Name:
*    print_prompt
* In:
*    N/A
*
* Out:
*    N/A
*
* Description:
*    Prints the prompt string.
*
* Assumptions:
*    --
*****************************************************************************/
static void print_prompt(void)
{
  print(">");
}

/*****************************************************************************
* Name:
*    print_greeting
* In:
*    N/A
*
* Out:
*    N/A
*
* Description:
*    --
*
* Assumptions:
*    --
*****************************************************************************/
static void print_greeting(void)
{
  print("This is the simple terminal version 1.0\r\n");
}

/*****************************************************************************
* Name:
*    find_command
* In:
*    name - pointer to command name string
*
* Out:
*    number - Index of command in "commands" array.
*    -1     - Command not found.
*
* Description:
*    Find a command by its name.
*
* Assumptions:
*    --
*****************************************************************************/
static int find_command(char *name)
{
  int x;
  for(x=0; x < sizeof(commands)/sizeof(commands[0]); x++)
  { /* If command found, execute it. */
    if (cmp_str(name, (char *) commands[x].txt))
    {
      return(x);
    }
  }
  return(-1);
}

/*****************************************************************************
* Name:
*    terminal_init
* In:
*    N/A
*
* Out:
*    N/A
*
* Description:
*    Inicialise the terminal. Set local varaibles to a default value, print
*    greeting message and prompt.
*
* Assumptions:
*    --
*****************************************************************************/
void terminal_init(void)
{
  cmd_line[sizeof(cmd_line)-1]='\0';
  cmd_line_ndx=0;

  print_greeting();
  print_prompt();
}

/*****************************************************************************
* Name:
*    terminal_proces
* In:
*    N/A
*
* Out:
*    N/A
*
* Description:
*    Main loop of terminal application. gathers input, and executes commands.
*
* Assumptions:
*    --
*****************************************************************************/
void terminal_process(void)
{
  while(has_input())
  {
    char c;
    c=get_char();
    put_char(c);
    if (c=='\r')
    {
      put_char('\n');
    }
    /* Execute command if enter is received, or cmd_line is full. */
    if ((c=='\r') || (cmd_line_ndx == sizeof(cmd_line)-2))
    {
      int start=skipp_space(cmd_line, 0);
      int end=find_word(cmd_line, start);
      int x;

      /* Separate command string from parameters, and close
         parameters string. */
      cmd_line[end]=cmd_line[cmd_line_ndx]='\0';

      /* Identify command. */
      x=find_command(cmd_line+start);
      /* Command not found. */
      if (x == -1)
      {
        print("Unknown command!\r\n");
      }
      else
      {
        (*commands[x].func)(cmd_line+end+1);
      }
      cmd_line_ndx=0;
      print_prompt();
    }
    else
    { /* Put character to cmd_line. */
      cmd_line[cmd_line_ndx++]=c;
    }
  }
}

#ifdef __cplusplus
}
#endif
/****************************** END OF FILE **********************************/
