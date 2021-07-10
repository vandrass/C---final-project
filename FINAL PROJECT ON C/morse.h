#pragma once
#define N 38  // quantity of alphabet chars + digits in struct 
#define CMD_LENTH 3
#define COMMAND_LENTH 2000
#define FILE_WAY "E:\\Study\\Ivan\\Lang\\C\\works\\FINAL PROJECT ON C\\"  // this is path for .txt and .cmf files, for reading and saving
struct morse_code
{
	char* morse;
	char symbol;
};
struct morse_code morse_translate[N];
char Translate_Morse_To_TEXT(char* string_morse, struct morse_code* morse_translate);
void Load_cmf_and_print_text(struct morse_code* morse_translate, FILE* file, char *str, int parametr);
char* add_char(char* ptr_buffer_word, char buffer_string, int size);
void Load_text_and_print_cmf(struct morse_code* morse_translate, FILE* file);
char* Translate_Text_To_Morse(char* buffer_word, char string_text, struct morse_code* morse_translate);
char* add_morse(char* ptr_buffer_word, char* buffer_string, int size);
void Translate_String_to_morse(char *str, struct morse_code *morse_translate);
void Translate_text_and_print_cmf(char *str, struct morse_code *morse_translate);
int Format_name_search(char *buff, struct morse_code * morse_translate);
void  Format_name(FILE * file, struct morse_code * morse_translate);
void Load_cmf_and_save_text(struct morse_code* morse_translate, FILE* file1, FILE* file2);
void Load_text_and_save_cmf(struct morse_code* morse_translate, FILE* file1, FILE* file2);