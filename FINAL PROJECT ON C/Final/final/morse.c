#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include"morse.h"
#pragma warning (disable: 4996)
#define THREE_UNIT 3   //  3 spaces  
#define SEVEN_UNIT 7   // 7 spaces 
#define LENG_BUFFER 2000  //buffer leng 



struct morse_code morse_translate[N] =
{
	{"* ---", 'A'},{"--- * * *",'B'},{"--- * --- *",'C'}, {"--- * *", 'D'},
	{"*", 'E'}, {"* * --- *", 'F'},{"--- --- *", 'G'},{"* * * *", 'H'},
	{"* *", 'I'}, {"* --- --- ---", 'J'},{"--- * ---", 'K'},{"* --- * *", 'L'},
	{"--- ---", 'M'},{"--- *", 'N'},{"--- --- ---", 'O'}, {"* --- --- *", 'P'},
	{"--- --- * ---", 'Q'}, {"* --- *", 'R'},{"* * *", 'S'},{"---", 'T'},
	{"* * ---", 'U'},{"* * * ---", 'V'},{"* --- ---", 'W'}, {"--- * * ---", 'X'},
	{"--- * --- ---", 'Y'}, {"--- --- * *", 'Z'},

	{"* --- --- --- ---", '1'},{"* * --- --- ---", '2'},{"* * * --- ---", '3'},
	{"* * * * ---", '4'},{"* * * * *", '5'},
	{"--- * * * *", '6'},{"--- --- * * *", '7'},{"--- --- --- * *", '8'},
	{"--- --- --- --- *", '9'},{"--- --- --- --- ----", '0'},{"       ", ' '}

};
/**********first_cmd**********
Description:
Function open file and call Load_cmf_and_print_text function 
Arguments:
cmd - array of pointers 
Return value:
void
*/
void first_cmd(char** cmd)
{
	FILE* file_morse;  //file ptr
	if (file_morse = fopen(cmd[1], "r"))  // if file for read open  
	{
		Load_cmf_and_print_text(morse_translate, file_morse, NULL, 1);
		fclose(file_morse);  // close file 
	}
	else printf("file not exist\n");
}
/**********second_cmd**********
Description:
Function open  2 files  and call Load_cmf_and_save_text function
Arguments:
cmd - array of pointers
Return value:
void
*/
void second_cmd(char** cmd)
{
	FILE* file_morse;  //ptr on file 
	FILE* file_text;   //ptr on file 
	if ((file_morse = fopen(cmd[1], "r")) && (file_text = fopen(cmd[2], "w"))) //if 1 file open for read and second file open for write
	{
		Load_cmf_and_save_text(morse_translate, file_morse, file_text);  //call Load_cmf_and_save_text function 
		fclose(file_morse);
		fclose(file_text);   //close files 
	}
	else if (!file_morse)  // if morse_file dont exist 
		printf("Morse file not exist\n");
	else printf("Text file not created\n");
}
/**********third_cmd**********
Description:
Function open file  and call Load_text_and_print_cmf function
Arguments:
cmd - array of pointers
Return value:
void
*/
void third_cmd(char** cmd)
{
	FILE* file_text;  //ptr on file 
	if (file_text = fopen(cmd[1], "r"))  // if open file for read 
	{
		Load_text_and_print_cmf(morse_translate, file_text); // call Load_text_and_print_cmf func 
		fclose(file_text);
	}
	else printf("file not exist\n");
}
/**********fourth_cmd**********
Description:
Function open 2 files and call Load_text_and_save_cmf function
Arguments:
cmd - array of pointers
Return value:
void
*/
void fourth_cmd(char** cmd)
{
	FILE* file_morse;  //ptr on file 
	FILE* file_text;
	if ((file_text = fopen(cmd[1], "r")) && (file_morse = fopen(cmd[2], "w")))  // if first_file is opened succsesful for read and second file opend for write 
	{
		Load_text_and_save_cmf(morse_translate, file_text, file_morse); // call Load_text_and_save_cmf func 
		fclose(file_morse);
		fclose(file_text);  // close files 
	}
	else if (!file_text)  // if file_text not exist 
		printf("Text file not exist\n");
	else printf("Morse file not created\n");
}
/**********third_cmd**********
Description:
Function open file  and call Format_name function
Arguments:
cmd - array of pointers
Return value:
void
*/
void seventh_cmd(char** cmd)
{
	FILE* file_text;  //ptr on file 
	if (file_text = fopen(cmd[1], "r")) //if  open file for read succsesfull
	{
		Format_name(file_text, morse_translate); // call Format_name func 
		fclose(file_text); // close file 
	}
	else printf("file not exist\n");
}

/********** Translate_Morse_To_TEXT **********
Description:
Function search in struct chars and translate them to morse string 
Arguments:
string_morse	- pointer on input string
morse_translate	- pointer on struct morse
Return value:
char_from_morse - string of morse code if exist 
if char not exist return 0 and print "wrong format"
*/
char Translate_Morse_To_TEXT(char* string_morse, struct morse_code* morse_translate)     
{
	int i, flag = 1;                         //i-counter for loop , flag - for find value 
	char char_from_morse;                     //variable we save morse code 
	struct morse_code* p = morse_translate;   //p- ptr on struct 
	for (i = 0; i < N-1 && flag; i++)       // loop run in struct & search equal char 
	{
		if (!strcmp(string_morse, p->morse))  // if find equal char 
		{
			char_from_morse = p->symbol;     
			flag--;
		}
		p++; // address run
	}
	    if (flag)                             //check if char exist or wrong format 
		{	
		printf("wrong format");
		return 0;
		}

	return char_from_morse;
}




/**********  Load_cmf_and_print_text**********
Description:
Complex Function 2 in 1
[if int parametr = 1]-(take code morse  from client  and translate it to string, than print text on the screen)
[if int parametr = 2]-(load code morse from file.cmf and translate it to string, than print text string on the screen)
Function call another functions for adding char and translating:
-add_char(ptr_buffer_word, buffer_string[i], s) and
-Translate_Morse_To_TEXT(ptr_buffer_word, morse_translate)
Arguments:
str	- pointer on input string
morse_translate	- pointer on struct morse
file - file with code morse
parametr - switch
parametr = 1: Load_cmf_and_print_tet;
parametr = 0: Translate_cmf_and_print_text;
Return value: Void
*/
void Load_cmf_and_print_text(struct morse_code* morse_translate, FILE* file, char *str, int parametr) //parametr 1- Load_cmf_and_print_tet 
{                                                                                                   //parametr 0- Translate_cmf_and_print_text 
	int i = 0, counter_revah = 1, s = 1;   //counters // s-count of size
	char character;                       //var for save data 
	char buffer_string[LENG_BUFFER] = { NULL };    //main buffer for save input  
	char* ptr_buffer_word = (char*)malloc(s * sizeof(char));  // memory allocation 

	if (parametr)    // parametr - true - GO in this way (Load_cmf_and_print_text)
	{
		while (!feof(file))
		{
			fgets(buffer_string, LENG_BUFFER, file); 
			
		}
	}
	else         // parametr - false Go in way (Translate_cmf_and_print_text)
	{
		strcpy(buffer_string, str);
	}
	while (buffer_string[i])   // while  buffer string exist 
	{
		while (buffer_string[i] == ' ' && buffer_string[i + 1] == ' ')  // block count spaces
		{
			counter_revah++;
			i++;
		}
		if (buffer_string[i + 1] == '\0')   //  end of string  
		{
			ptr_buffer_word = add_char(ptr_buffer_word, buffer_string[i], s);
			counter_revah = 3;
		}
		if (counter_revah >= THREE_UNIT)    //in  block we call function  what compare char per char in struct morse and translate char
		{
			character = Translate_Morse_To_TEXT(ptr_buffer_word, morse_translate); //call func   
			printf("%c", character);   // print char 
			if (counter_revah == SEVEN_UNIT)printf(" "); //if we find 7 spaces that means 1 space between words or chars 
			s = counter_revah = 1;  // restart counter spaces
			ptr_buffer_word = NULL; // restart pointer on our string 
		}
		else {
			ptr_buffer_word = add_char(ptr_buffer_word, buffer_string[i], s);
			s++;
		}
		
		i++;
	}

}

/*********** add_char ********************
This function build array of cmf for tranclating to text,
every iteration function add to "ptr_buffer_word" symbol of cmf
until to stop condition
	Arguments:
	ptr_buffer_word - string of cmf symbols
	buffer_string - single cmf symbol
	size - needed lenth of ptr_buffer_word,for including of string
*/
char* add_char(char* ptr_buffer_word, char buffer_string, int size)
{
	char* ptr_buffer_word2 = ptr_buffer_word;
	if (ptr_buffer_word = (char*)realloc(ptr_buffer_word2, size * sizeof(char))) {
		ptr_buffer_word[size - 1] = buffer_string;
		ptr_buffer_word[size] = '\0';
		return ptr_buffer_word;
	}
	else {
		printf(" memory error\n");
		return ptr_buffer_word2;
	}
		
	
}

/********** Load_text_and_print_cmf **********
Description:
Function take text file than translate text t omorse code & print on screen tesult 
Function Load_text_and_print_cmf call another function Translate_Text_To_Morse that help in search elements in struct & translate 
Arguments:
file - pointer to text file 
morse_translate - pointer on struct 
Return value:
Void
*/

void Load_text_and_print_cmf(struct morse_code* morse_translate, FILE* file)
{
	int i = 0, counter_revah = 1, s = 1;   //counters // s-count of size
	char buffer_string[LENG_BUFFER] = { NULL };
	char* ptr_buffer_word = (char*)malloc(s * sizeof(char));
	char temp[LENG_BUFFER] = {NULL}; //temp buffer 
	while (!feof(file))   
	{ 
		fgets(temp, LENG_BUFFER, file);
		strcat (buffer_string, temp);
		 
	}
	while (buffer_string[i])
	{
		if ((buffer_string[i] != ' ' || buffer_string[i + 1] == '\0') && (buffer_string[i]!='\n'))
		{
			if (ptr_buffer_word = Translate_Text_To_Morse(ptr_buffer_word, buffer_string[i], morse_translate));   
			else return;                              // if char not exist,return to main function
			printf("%s   ", ptr_buffer_word);       //print morse code string  and  3 spaces between code characters
		}
		else if (buffer_string[i] == ' ') printf("       ");// 7 spaces between morse code words
		else  printf("\n"); //new line 
		i++;
	}
	
}

/********** Translate_Text_To_Morse **********
Description:
Function search and compare morse code for find right char in struct
Function Translate_Text_To_Morse call another function add_morse 
Arguments:
buffer_word -  pointer on void  morse string in whitch we save 1 string morse code(1 char )                           
string_text -   var type char (contain 1 char from input )
morse_translate - pointer on struct 
Return value:
buffer_word - pointer on string with chars that we need
if character not exist, return 0
*/
char* Translate_Text_To_Morse(char* buffer_word, char string_text, struct morse_code* morse_translate)// take a character and translate to morse
{
	int i, flag = 1, s;
	struct morse_code* p = morse_translate;
	for (i = 0; i < N - 1 && flag; i++)
	{
		if (string_text == p->symbol)
		{
			s = strlen(p->morse) + 1;
			buffer_word = add_morse(buffer_word, p->morse, s);
			flag--;
		}
		p++;
	}
	if (flag)   //check if format is good 
	{
		printf("wrong format");
		return 0;
	}
	return buffer_word;
}

/*********** add_morse ********************
This function save array of cmf symbols was tranclated from text,
eeach entering to function saving 1 string of cmf which equal to charcter of text

	Arguments:
	ptr_buffer_word - string for saving trancleted character
	buffer_string - trancleted character from text to cmf
	size - needed lenth of ptr_buffer_word,for including of string
*/
char* add_morse(char* ptr_buffer_word, char* buffer_string, int size)
{
	char* ptr_buffer_word2 = ptr_buffer_word;

	if (ptr_buffer_word = (char*)realloc(ptr_buffer_word2, size * sizeof(char)))
	{
		strcpy(ptr_buffer_word, buffer_string);
		ptr_buffer_word[size] = '\0';
		return ptr_buffer_word;
	}
	else
	{
		printf(" memory error\n");
		return ptr_buffer_word2;
	}
	
}

/********** Translate_String_to_morse **********
Description:
Function search and compare chars for find right code morse in struct
Than return string code morse
Arguments:
str - pointer on client string
morse_translate - pointer on struct morse
buff - pointer on array buffer
Return value:
buff - adress of string with code morse that we need
*/
void Translate_String_to_morse(char *str, struct morse_code *morse_translate)
{
	char buff[30];
	int i, flag = 1;  //counters //flag 0 if find value, 1 - if not  

	for (i = 0; i < N && flag; i++)                  // loop for run & search value in struct  
	{
		if (*str == morse_translate[i].symbol)       // if true 
		{

			strcpy(buff, (morse_translate + i)->morse);  // copy value in buffer 
			flag--;
		}
		else if (i == N - 1)      // check if char exist in struct 
		{
			printf("Wrong Symbol");
			return;
		}
	}



	printf("%s", buff);  // display string on screen 

}

/********** Translate_text_and_print_cmf**********
Description:
Function take string from client and call another function  Translate_String_to_morse
Two these functions translate string in morse code and print the result on screen
Arguments:
str	- pointer on input string
morse_translate	- pointer on struct morse
Return value:
Void
*/
void Translate_text_and_print_cmf(char *str, struct morse_code *morse_translate)
{


	while (*str)  // while eos(end of string)
	{
		if ((*str >= 'A' && *str <= 'Z') || (*str >= '0' && *str <= '9') || *str == ' ')  //check if string is ok 
		{
			Translate_String_to_morse(str, morse_translate);  //call func translate whitch search && print result

		}
		else  // string has wrong symbols 
		{
			printf("\nWrong symbols, dont translate\n");
			return;
		}

		if (*(str + 1) == '\0') printf("\n");  // new line if eos 
		else if (*str != ' ' && *(str + 1) != ' ') 	printf("   ");  // spaces between morse code 
		str++; // run in string 

	}

}

/********** Format_name_search **********
Description:
Function Format_name_search search in struct values morse code format 
Arguments :
buff - pointer to buffer (first string from file)
morse_translate - pointer on struct morse
Return value :
int flag (if TRUE - symbol don"t exist, if FALSE - find symbol)
*/

int Format_name_search(char *buff, struct morse_code * morse_translate)
{
	int i, flag = 1;  //counter // flag if find val or no 
	struct morse_code* p = morse_translate;  // help pointer on struct 
	for (i = 0; i < N && flag; i++, p++)  // loop run on struct and search values 
	{
		if (!strcmp(buff, p->morse))  // if find morse code copy in buffer  
		{
			flag--;
		}

	}
	return flag;

}

/********** Format_name **********
Description:
Function check if file is morse format or text format 
Function call another function Format_name_search whitch search in struct values morse code format 
Arguments :
file - pointer on file 
morse_translate - pointer on struct morse
Return value :Void
*/ 
void  Format_name(FILE * file, struct morse_code * morse_translate)
{
	char buffer[LENG_BUFFER];  //buffer memory 
	int counter = 1, i = 0;  // counters 
	fgets(buffer, LENG_BUFFER, file);  // save first line of file in buffer 
	while (buffer[i])  //while eob(end of buffer)
	{
		if ((buffer[i] >= 'A' && buffer[i] <= 'Z') || (buffer[i] >= '0' && buffer[i] <= '9')) // check if text file 
		{
			printf("It is Text file .TXT");
			return;
		}


		while (buffer[i] == ' ' && buffer[i + 1] == ' ')   // loop while for count spaces 
		{
			counter++;  //count spaces 
			i++;
		}

		if (counter == THREE_UNIT)  // if 3 spaces 
		{
			buffer[i - 2] = '\0';  // divide morse string 
			if (!(Format_name_search(buffer, morse_translate))) // if Format_name_search return 0 - is find symbol if 1 - dont find 
			{
				printf("It is Morse file .cmf");
				return;
			}

		}

		i++; //run on buffer 
		counter = 1;  //restart space counter 
	}

	printf("Unknown format!\n");
}

/************* Load_cmf_and_save_text ************
This function take 2 file, first file is source, second file is destination(saving file).
Function tranclate first file from cmf to text, and save to second file.
Using function - add_char,Translate_Morse_To_TEXT
	Arguments:
morse_translate	- pointer on struct morse
file1 - file with code morse
file2 - file for saving(txt)
Return value: Void
*/
void Load_cmf_and_save_text(struct morse_code* morse_translate, FILE* file1, FILE* file2)
{
	int i = 0, counter_revah = 1, s = 1;   //counters // s-count of size  string 
	char character;
	char buffer_string[LENG_BUFFER] = { NULL };
	char* ptr_buffer_word = (char*)malloc(s * sizeof(char));

	while (!feof(file1))		
		fgets(buffer_string, LENG_BUFFER, file1);

	while (buffer_string[i])// while buffer string exist
	{
		while (buffer_string[i] == ' ' && buffer_string[i + 1] == ' ') // block count spaces
		{
			counter_revah++;
			i++;
		}
		if (buffer_string[i + 1] == '\0')//  end of string  
		{
			ptr_buffer_word = add_char(ptr_buffer_word, buffer_string[i], s);
			counter_revah = 3;
		}
		if (counter_revah >= THREE_UNIT)//in  block we call function  what compare char per char in struct morse and translate char
		{
			if (character = Translate_Morse_To_TEXT(ptr_buffer_word, morse_translate)); //call func 2 args(string from buffer, ptr to struct)  
			else return;
			fprintf(file2, "%c", character);//save char to file txt
			if (counter_revah == SEVEN_UNIT) fprintf(file2, " ");//if we find 7 spaces that means 1 space between words or chars 
			s = counter_revah = 1;// restart counter spaces
			ptr_buffer_word = NULL;// restart pointer on our string 
		}

		else {
			ptr_buffer_word = add_char(ptr_buffer_word, buffer_string[i], s);
			s++;
		}
		i++;
	}
	
}

/************* Load_text_and_save_cmf ************
Thise function take 2 file, first file is source, second file is destination(saving file).
Function tranclate first file from txt to cmf, and save to second file.
Using function -Translate_Text_To_Morse
	Arguments:
morse_translate	- pointer on struct morse
file1 - file with text
file2 - file for saving(cmf)
Return value: Void
*/
void Load_text_and_save_cmf(struct morse_code* morse_translate, FILE* file1, FILE* file2)
{
	int i = 0, counter_revah = 1, s = 1;   //counters // s-count of size
	char buffer_string[LENG_BUFFER] = { NULL };
	char temp[LENG_BUFFER] = { NULL };
	char* ptr_buffer_word = (char*)malloc(s * sizeof(char));

	while (!feof(file1))
	{
		fgets(temp, LENG_BUFFER, file1);
		strcat(buffer_string, temp);
	}
	while (buffer_string[i])
	{
		if (buffer_string[i] == '\n')
		{
			fprintf(file2, "\n");
			buffer_string[i] = ' ';
		}
		else if (buffer_string[i] != ' ' && buffer_string[i + 1] != '\0' && buffer_string[i + 1] != ' ')
		{
			if	(ptr_buffer_word = Translate_Text_To_Morse(ptr_buffer_word, buffer_string[i], morse_translate));// if char not exist,return to main function
			else return; // if char not exist,return to main function
			fprintf(file2, "%s   ", ptr_buffer_word);//morse code and space between code characters
		}
		else if (buffer_string[i] == ' ')
			fprintf(file2, "       ");//space between morse code words
		
		else
		{
			if (ptr_buffer_word = Translate_Text_To_Morse(ptr_buffer_word, buffer_string[i], morse_translate));// if char not exist,return to main function
			else return;
			fprintf(file2, "%s", ptr_buffer_word);//save morse string to file2
		}
		i++;
	}

}