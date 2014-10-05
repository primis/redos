#ifndef __COMMAND_H
#define __COMMAND_H
extern int findCMD(char *cmd);

/* SHELL.C */ 
typedef struct
{
	char command[64];	//command string
	char description[256];	//brief description
	void *address;		//the function it associates with
} commandEntry;
extern int atoi(const char *nptr);
extern int Command(char *command, char *description, void *address);
extern void init_shell();			/* Populates the command list. 			*/
extern void run_shell();				/* Runs one command on the shell. 		*/
extern void clearCommands();		/* Clear all entry's on the jump table. */

extern void help();
extern void ahelp();
extern void version();
extern void example();
extern void outputMe();
extern void addMe();
extern void subtractMe();
extern void exponentMe();
extern void defcon();

#endif
