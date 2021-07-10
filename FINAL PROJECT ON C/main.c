//Ivan Goncharov  && Denis Tsembalenko//dev

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "morse.h"
#pragma warning (disable: 4996)




void free_cmd(char* cmd[CMD_LENTH]);
int commands_input(char tmp[COMMAND_LENTH], char*cmd[CMD_LENTH]);
void first_cmd(char** cmd);
void second_cmd(char** cmd);
void third_cmd(char** cmd);
void fourth_cmd(char** cmd);
void seventh_cmd(char** cmd);

void main()
{	
	int flag = 1;
	char tmp[COMMAND_LENTH];
	//commands
	do {
		char* cmd[CMD_LENTH] = { 0 };// array of pointers
		gets(tmp);
		commands_input(tmp, cmd);

		if (cmd[0]) 
		{
			if (!strcmp(cmd[0], "load_cmf_and_print_text") && cmd[1]) //good
			{
				first_cmd(cmd);
			}

			else if (!strcmp(cmd[0], "load_cmf_and_save_text") && (cmd[1] && cmd[2]))//good
			{
				second_cmd(cmd);
			}

			else if (!strcmp(cmd[0], "load_text_and_print_cmf") && cmd[1]) //good
			{
				third_cmd(cmd);
			}

			else if (!strcmp(cmd[0], "load_text_and_save_cmf") && (cmd[1] && cmd[2]))//good
			{
				fourth_cmd(cmd);
			}

			else if (!strcmp(cmd[0], "translate_text_and_print_cmf") && cmd[1])   //good
			{
				Translate_text_and_print_cmf(cmd[1], morse_translate);				
			}

			else if (!strcmp(cmd[0], "translate_cmf_and_print_text") && cmd[1])//good
			{
				Load_cmf_and_print_text(morse_translate, NULL, cmd[1], 0);				
			}

			else if (!strcmp(cmd[0], "print_format_name") && cmd[1])  //good
			{
				seventh_cmd(cmd);				
			}
			else if (!strcmp(cmd[0], "quit")) flag = 0;
			
			else printf("wrong command\n");

			printf("\n");
			free_cmd(cmd);
		}
		else printf("wrong command\n");
	} while (flag);
}



void first_cmd(char** cmd)
{
	FILE* file_morse;
	if (file_morse = fopen(cmd[1], "r"))
				{
					Load_cmf_and_print_text(morse_translate, file_morse, NULL, 1);
					fclose(file_morse);
				}
				else printf("file not exist\n");
}
void second_cmd(char** cmd)
{
	FILE* file_morse;
	FILE* file_text;
	if ((file_morse = fopen(cmd[1], "r")) && (file_text = fopen(cmd[2], "w")))
	{
		Load_cmf_and_save_text(morse_translate, file_morse, file_text);
		fclose(file_morse);
		fclose(file_text);
	}
	else if (!file_morse)
		printf("Morse file not exist\n");
	else printf("Text file not created\n");
}
void third_cmd(char** cmd)
{
	FILE* file_text;
	if (file_text = fopen(cmd[1], "r"))
	{
		Load_text_and_print_cmf(morse_translate, file_text);
		fclose(file_text);
	}
	else printf("file not exist\n");
}
void fourth_cmd(char** cmd)
{
	FILE* file_morse;
	FILE* file_text;
	if ((file_text = fopen(cmd[1], "r")) && (file_morse = fopen(cmd[2], "w")))
	{
		Load_text_and_save_cmf(morse_translate, file_text, file_morse);
		fclose(file_morse);
		fclose(file_text);
	}
	else if (!file_text)
		printf("Text file not exist\n");
	else printf("Morse file not created\n");
}
void seventh_cmd(char** cmd)
{
	FILE* file_text;
	if (file_text = fopen(cmd[1], "r"))
	{
		Format_name(file_text, morse_translate);
		fclose(file_text);
	}
	else printf("file not exist\n");
}


/**** Input of commands and files names ****/
int commands_input(char tmp[COMMAND_LENTH], char* cmd[CMD_LENTH])
{
	int i ;
	char sep[3] = " ";
	char* str;
	char temp[COMMAND_LENTH];
	
	str = strtok(tmp, sep);
	for (i = 0; i < CMD_LENTH && str; i++)
	{
		if (i > 0)
		{
			strcpy(temp, FILE_WAY);
			if (cmd[i] = (char*)malloc(((strlen(str) + strlen(FILE_WAY) + 1)) * sizeof(char))) {
				strcat(temp, str);
				strcpy(cmd[i], temp);
				str = strtok(NULL, sep);
			}
			else return 0;
		}

		else if (i == 0)
		{		
			
			if (cmd[i] = (char*)malloc((strlen(str) + 1) * sizeof(char))) {
				strcpy(cmd[i], str);
				
				if (!strcmp(cmd[0], "translate_text_and_print_cmf") || !strcmp(cmd[0], "translate_cmf_and_print_text"))// for normal output of this function,which we compare
				{
					sep[0] = "\0";
					str = strtok(NULL, sep);
					if (str&&((str[0]>='0'&&str[0]<='9')|| (str[0] >='A' && str[0] <= 'Z')|| str[0]!='*'|| str[0]!='-')); 
					else return 0;
					if (cmd[1] = (char*)malloc((strlen(str) + 1) * sizeof(char))) {
						strcpy(cmd[1], str);
						return 1;
					}
					else return 0;
					
				}
				str = strtok(NULL, sep);
			}
			else return 0;

		}

	}
	return 1;
}





/*** free memory***/
void free_cmd(char* cmd[CMD_LENTH])
{
	int i;
	for (i = 0; i < CMD_LENTH; i++)
		free(cmd[i]);
}
