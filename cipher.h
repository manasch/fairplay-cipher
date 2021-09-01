#include<stdlib.h>
#include<ctype.h>

void format_key(char *);
void make_grid(char *, char [][5]);
char *string_upper(char *);
void string_2_list(char *, char [][100], int *);
void message_formatting(char *);
void output_formatting(char *);
void search(char [][5], char , char , int []);
void encrypt_message(char [][5], char []);
void decrypt_message(char [][5], char []);
void encryption(char [][5], char *, char *);
void decryption(char [][5], char *, char *);