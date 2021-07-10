//Ivan Goncharov  && Denis Tsymbalenko
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "morse.h"
#pragma warning (disable: 4996)
/********** MAIN **********
Description:
Function main in programm with switch(if-else) to exequte different functions(functional)  
Arguments:
void
Return value:
void
*/
void main()
{	
	int flag = 1;                    //flag=0 if we quit from programm
	char tmp[COMMAND_LENTH];         // temporary array(buffer) for all user input 
	//commands
	do {                            //loop do-while that roll program(EOP)
		char* cmd[CMD_LENTH] = { 0 };// array of pointers
		gets(tmp);                    //get string from user 
		commands_input(tmp, cmd);      //call Function commands_input 

		if (cmd[0])                //if cmd[0] exist(not NULL)
		{
			if (!strcmp(cmd[0], "load_cmf_and_print_text") && cmd[1]) // if user enter load_cmf_and_print_text command && cmd[1] parametr exist
			{
				first_cmd(cmd); //call first_cmd function  
			}

			else if (!strcmp(cmd[0], "load_cmf_and_save_text") && (cmd[1] && cmd[2]))// if user enter load_cmf_and_save_text command && cmd[1] paramert exist && cmd[2] parametr exist
			{
				second_cmd(cmd); //call second_cmd function
			}

			else if (!strcmp(cmd[0], "load_text_and_print_cmf") && cmd[1]) // if user enter load_text_and_print_cmf command && cmd[1] parametr exist
			{
				third_cmd(cmd); //call third_cmd function
			}

			else if (!strcmp(cmd[0], "load_text_and_save_cmf") && (cmd[1] && cmd[2]))// if user enter load_text_and_print_cmf command && cmd[1] parametr exist && cmd[2] parametr exist
			{
				fourth_cmd(cmd); //call fourth_cmd function
			}

			else if (!strcmp(cmd[0], "translate_text_and_print_cmf") && cmd[1])   // if user enter translate_text_and_print_cmf command && string exist
			{
				Translate_text_and_print_cmf(cmd[1], morse_translate);			//call Translate_text_and_print_cmf function 	
			}

			else if (!strcmp(cmd[0], "translate_cmf_and_print_text") && cmd[1])    // if user enter translate_cmf_and_print_text command && string exist
			{
				Load_cmf_and_print_text(morse_translate, NULL, cmd[1], 0);	//call Load_cmf_and_print_text function 
			}

			else if (!strcmp(cmd[0], "print_format_name") && cmd[1])  // if user enter print_format_name command && cmd[1] parametr exist
			{
				seventh_cmd(cmd);		//call seven_cmd function		
			}
			else if (!strcmp(cmd[0], "quit")) flag = 0; // if user enter quit command
			
			else printf("wrong command\n");  // wrong input format 

			printf("\n");
			free_cmd(cmd);  // free memory func 
		}
		else printf("wrong command\n"); // wrong input format 
	} while (flag);  
}

/**** Input of commands and files names ****/
/*
   variables:
	sep[] - is array with char for division of string tmp on command and arguments
	tmp[] - string from main with user inputs
	*str - divised part of tmp
	*cmd - ponters array, where saving command and arguments
	temp[]- auxiliary array for copying to cmd[i]
	i - index of cmd
*/
int commands_input(char tmp[COMMAND_LENTH], char* cmd[CMD_LENTH])
{
	int i ;
	char sep[3] = " ";// division by "space"
	char* str;
	char temp[COMMAND_LENTH];
	
	str = strtok(tmp, sep);// function for string division
	for (i = 0; i < CMD_LENTH && str; i++)
	{
		if (i > 0)// if we work with files, we are use this block
		{		//in this block we are copy file path to 'temp', create array cmd[i],add to 'temp' file name and copy all this to cmd[i]
			strcpy(temp, FILE_WAY);
			if (cmd[i] = (char*)malloc(((strlen(str) + strlen(FILE_WAY) + 1)) * sizeof(char))) {
				strcat(temp, str);
				strcpy(cmd[i], temp);
				str = strtok(NULL, sep);//continue to next part of string 'tmp' and copy of this part to 'str'
			}
			else return 0;
		}

		else if (i == 0)		// if i=0, it means, that we work with cmd[0](include command string)
		{		
			
			if (cmd[i] = (char*)malloc((strlen(str) + 1) * sizeof(char))) {
				strcpy(cmd[i], str);
				
				if (!strcmp(cmd[0], "translate_text_and_print_cmf") || !strcmp(cmd[0], "translate_cmf_and_print_text"))//this 'IF' we need for solution,how to continue the code.
				{																									//true - only tranclate,without files, false-we work with files
					sep[0] = "\0";
					str = strtok(NULL, sep);//copy string until end of string
					if (str&&((str[0]>='0'&&str[0]<='9')|| (str[0] >='A' && str[0] <= 'Z')|| str[0]!='*'|| str[0]!='-')); // checking for cotection of input characters
					else return 0;
					if (cmd[1] = (char*)malloc((strlen(str) + 1) * sizeof(char))) {
						strcpy(cmd[1], str);
						return 1;
					}
					else return 0;
					
				}
				str = strtok(NULL, sep);//continue to next part of string 'tmp' and copy of this part to 'str'
			}
			else return 0;

		}

	}
	return 1;
}

/********** Free_cmd **********
Description:
Function freeing allocated memory to OS
Arguments:
cmd - array of pointers 
return value:
void
*/
void free_cmd(char* cmd[CMD_LENTH])
{
	int i;
	for (i = 0; i < CMD_LENTH; i++)   // loop for free mem 
		free(cmd[i]);
}
