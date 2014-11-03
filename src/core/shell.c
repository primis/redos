#include <stdio.h>
#include <string.h>
#include <kernel/arch/x86/ps2.h>
#include <kernel/command.h>
#include <time.h>

#define SHELL_VER "0.1" // Version of the Shell
#define MaxCommands 16  // Maximum alloted command slots since we're not using malloc
#define KERN_API 1      // The API of the Kernel

int numCommands = -1;   /* Number of Registered Commands, we start at -1 so the first one registered is 0. */
char *cmdString;
char *cmdSwitch0;
char *cmdSwitch1;
char *cmdSwitch2;
char *cmdSwitch3;
char *cmdSwitch4;
char *cmdSwitch5;
char *cmdSwitch6;
commandEntry CommandTable[MaxCommands];
char prompt [32];

int atoi(const char *nptr)
{
  int c;
  int total;
  int sign;

  c = (int)(unsigned char) *nptr++;
  sign = c;
  if (c == '-' || c == '+') c = (int)(unsigned char) *nptr++;

  total = 0;
  while (('0'<= c) && (c <='9'))
  {
    total = 10 * total + (c - '0');
    c = (int)(unsigned char) *nptr++;
  }

  if (sign == '-')
    return -total;
  else
    return total;
}

void run_shell()
{
	int i;
	char inputstring[512];
	putchar('\n');
	printf("%s",prompt);
	gets(inputstring);
	cmdString = strtok(inputstring, " ");
	cmdSwitch0 = strtok(NULL, " ");
	cmdSwitch1 = strtok(NULL, " ");
	cmdSwitch2 = strtok(NULL, " ");
	cmdSwitch3 = strtok(NULL, " ");
	cmdSwitch4 = strtok(NULL, " ");
	cmdSwitch5 = strtok(NULL, " ");
	cmdSwitch6 = strtok(NULL, " ");
	void (*commandJump)(void);
	i = findCMD(cmdString);
	if(i >= 0)
	{
		commandJump = CommandTable[i].address;
		commandJump();
	}
	return;
}

int findCMD(char *cmd)
{
	int i;
	int c;
	for(i=0; i < numCommands + 1; i++)
	{
		c = strcmp(CommandTable[i].command, cmd);
		if (c == 0)
		{
			return i;
		}
	}
	return -1;
}

void clearCommands() /* Clear all address pointers of our Commands. */
{
	int i;
	for(i=0;i<MaxCommands;i++)
	{
		CommandTable[i].address = NULL;
		numCommands = -1;
	}
}

int addCommand(char *command, char *description, void *address)
{
	if(numCommands < MaxCommands)
	{
		numCommands++;
		strcpy(CommandTable[numCommands].command, command);
		strcpy(CommandTable[numCommands].description, description);
		CommandTable[numCommands].address = address;
		return numCommands;
	}
	return -1;
}


void help()
{
	int i;
	printf("\nCommand List: ");
	for(i=0;i<=numCommands;i++)
	{
		if(CommandTable[i].address != NULL)
		{
			printf(CommandTable[i].command);
			putchar(',');
			putchar(' ');
		}
	}
	putchar('\n');
}

void time()
{
    printf("%d",getTime());
}

void date()
{
    readRTC();
    printf("%d/%d/%d %d:%d", day, month, year, hour, minute);
}

void ahelp()
{
	int i;
	for(i=0; i <= numCommands; i++)
	{
		printf(CommandTable[i].command);
		printf(" - ");
		printf(CommandTable[i].description);
		putchar('\n');
	}
	return;
}

void version()
{
	printf("Shell Version:\t%s", SHELL_VER);
}

void example()
{
	char a[9], b[9];
	int c,d;
	printf("Input a number(1): ");
	gets(a);
	printf("Input a number(2): ");
	gets(b);
	c = atoi(a);
	d = atoi(b);
	printf("Addition: ");
	printf("%d", c+d);
	printf("\nSubtraction: ");
	printf("%d", c-d);
	printf("\nMultiply: ");
	printf("%d", c*d);
	printf("\nDivide: ");
	printf("%d", c/d);
	putchar('\n');
}

void outputMe()
{
	printf("\nYou typed:");
	putchar('\n');
	printf(cmdSwitch0);
    putchar(' ');
	printf(cmdSwitch1);
	putchar(' ');
	printf(cmdSwitch2);
	putchar(' ');
	printf(cmdSwitch3);
	putchar(' ');
	printf(cmdSwitch4);
	putchar(' ');
	printf(cmdSwitch5);
	putchar(' ');
	printf(cmdSwitch6);
}


void exponentMe()
{
	int a, b, c;
	a = atoi(cmdSwitch0);
	b = atoi(cmdSwitch0);
	c = atoi(cmdSwitch1);

	if (c == 0)
	{
		printf("%d", 1);
	}
	else
	{
		for (; c > 1; c--)
		{
			a = a * b;
		}
		printf("%d", a);
	}
}

void addMe()
{
	int a, b;
	a = atoi(cmdSwitch0);
	b = atoi(cmdSwitch1);
	putchar('\n');
	printf(cmdSwitch0);
	printf(" + ");
	printf(cmdSwitch1);
	printf(" = ");
	printf("%d", a+b);
}

void subtractMe()
{
	int a, b;
	a = atoi(cmdSwitch0);
	b = atoi(cmdSwitch1);
	putchar('\n');
	printf(cmdSwitch0);
	printf(" - ");
	printf(cmdSwitch1);
	printf(" = ");
	printf("%d", a-b);
}

void init_shell()
{
    printf("\nConfiguring Shell Subsystem... \n");
	clearCommands();
    cmdString[0] = 0;
	cmdSwitch0[0] = 0;
	cmdSwitch1[0] = 0;
	cmdSwitch2[0] = 0;
	cmdSwitch3[0] = 0;
	cmdSwitch4[0] = 0;
	cmdSwitch5[0] = 0;
	cmdSwitch6[0] = 0;
	addCommand("help", "Lists all available commands.", help);
	addCommand("ahelp", "Lists all available commands with descriptions", ahelp);
	addCommand("print", "Outprintf your chosen text", outputMe);
	addCommand("version", "Displays version information for the shell", version);
	addCommand("example", "Quick string to int conversion demo", example);
	addCommand("add", "Adds two numbers together", addMe);
	addCommand("sub", "Subtracts one number from another", subtractMe);
	addCommand("exp", "Multiplies a number against itself an exponential amount of times", exponentMe);
	addCommand("time", "Shows Unix Time",time);
    addCommand("date", "Shows Calendar date in DD/MM/YYYY HH:MM format", date);
    addCommand("reset", "Reset shell", init_shell);
	printf("Username: ");
	gets(prompt);
	strcat(prompt, "$ ");
	putchar('\f');                     // Clear the Screen
	printf("RedOS Shell Version %s\n", SHELL_VER);
}
