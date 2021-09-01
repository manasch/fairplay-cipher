#include<stdio.h>
#include<string.h>

#include"cipher.h"

#define alphabet "ABCDEFGHIJKLMNOPQRSTUVWXYZ"

void format_key(char *key)
{
    key = string_upper(key);

    char string[1000];
    strcpy(string, key);
    strcat(string, alphabet);

    //Removes repeating characters
    int i, j, k = 0;
    for(i = 0; i < strlen(string); i++)
    {
        for(j = 0; j < i; j++)
        {
            if(string[j] == string[i])
                break;
        }
        if(j == i && string[j] != 'J')
            string[k++] = string[i];
    }

    strcpy(key, string);
    //Truncate last junk values
    key[25] = '\0';
}

void make_grid(char *key, char grid[][5])
{
    for(int row = 0; row < 5; row++)
    {
        for(int col = 0; col < 5; col++)
            grid[row][col] = *(key++);
    }
}

//Convert lower case words to upper case
char *string_upper(char *string)
{
    char ch;
    for (int i = 0; i < strlen(string); i++)
    {
        ch = string[i];
        string[i] = toupper(ch);
    }
    return string;
}

//Split sentence at after space and store it in a list
void string_2_list(char *string, char string_list[][100], int *elements)
{
    char *ptr;

    ptr = strtok(string, " ");
    int index = 0;

    while (ptr != NULL)
    {
        strcpy(string_list[index++], ptr);
        ptr = strtok(NULL, " ");
    }
    *elements = index;
}

//Code formatting to begin encryption
void message_formatting(char *string)
{
    for (int i = 0; i < (strlen(string)); i++)
    {
        if (string[i] == 'J')
        {
            string[i] = 'I';
        }
    }

    int size = strlen(string);
    int i = 0;
    while (i < size){
        if (string[i] == string[i+1])
        {
            for (int k = size; k > i; k--)
                string[k] = string[k-1];
            
            //Using Q as the buffer character for X, else X
            if (string[i] == 'X')
                string[i+1] = 'Q';
            else
                string[i+1] = 'X';
            size++;
            string[size] = '\0';
        }
        i = i + 2;
    }

    //If even number of letters, buffer character X used, Q if it ends with X
    int len = strlen(string); 
    if ((len%2) !=  0)
    {
        if (string[len - 1] == 'X')
            string[len] = 'Q';
        else
            string[len] = 'X';
        string[len+1] = '\0';
        len++;
    }
}

//Making grid output readable
void output_formatting(char *string)
{
    int size = strlen(string);
    int len = size;
    for (int i = 0; i < strlen(string); i++)
    {
        if ((string[i] == 'X' && string[i - 1] == string[i + 1])\
            || (string[i] == 'Q' && string[i - 1] == 'X'))
        {
            for (int j = i + 1; j < size; j++)
                string[j - 1] = string[j];
            len--;
            string[len] = '\0';
        }
    }

    if (((len % 2 == 0) || (len != size)) && (string[len - 1] == 'X' || string[len - 1] == 'Q'))
        string[len - 1] = '\0';
}

//Search for the position of the letter pair
void search(char grid[5][5], char a, char b, int arr[])
{ 
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (grid[i][j] == a)
            {
                arr[0] = i;
                arr[1] = j;
            }
            else if (grid[i][j] == b)
            {
                arr[2] = i;
                arr[3] = j;
            }
        }
    }
}


void encrypt_message(char grid[][5], char formatted_string[])
{
    int arr[4];
 
    for (int i = 0; i < strlen(formatted_string); i += 2) {
        search(grid, formatted_string[i], formatted_string[i + 1], arr);
        if (arr[0] == arr[2])
        {
            formatted_string[i] = grid[arr[0]][(arr[1] + 1) % 5];
            formatted_string[i + 1] = grid[arr[0]][(arr[3] + 1) % 5];
        }
        else if (arr[1] == arr[3])
        {
            formatted_string[i] = grid[(arr[0] + 1) % 5][arr[1]];
            formatted_string[i + 1] = grid[(arr[2] + 1) % 5][arr[1]];
        }
        else
        {
            formatted_string[i] = grid[arr[0]][arr[3]];
            formatted_string[i + 1] = grid[arr[2]][arr[1]];
        }
    }
}

void decrypt_message(char grid[][5], char encrypted_string[])
{
    int arr[4];
    
    //Letters taken in pairs, incremented by 2
    for (int i = 0; i < strlen(encrypted_string); i += 2)
    {
        search(grid, encrypted_string[i], encrypted_string[i + 1], arr);
        if (arr[0] == arr[2])
        {
            if (arr[1] == 0 && arr[3] == 0)
            {
                encrypted_string[i] = grid[arr[0]][4];
                encrypted_string[i + 1] = grid[arr[0]][4];
            }
            else if (arr[1] == 0)
            {
                encrypted_string[i] = grid[arr[0]][4];
                encrypted_string[i + 1] = grid[arr[0]][(arr[3] - 1) % 5];
            }
            else if (arr[3] == 0)
            {
                encrypted_string[i] = grid[arr[0]][(arr[1] - 1) % 5];
                encrypted_string[i + 1] = grid[arr[0]][4];
            }
            else
            {
                encrypted_string[i] = grid[arr[0]][(arr[1] - 1) % 5];
                encrypted_string[i + 1] = grid[arr[0]][(arr[3] - 1) % 5];
            }
        }
        else if (arr[1] == arr[3])
        {
            if (arr[2] == 0 && arr[4] == 0)
            {
                encrypted_string[i] = grid[4][arr[1]];
                encrypted_string[i + 1] = grid[4][arr[1]];
            }
            else if (arr[0] == 0)
            {
                encrypted_string[i] = grid[4][arr[1]];
                encrypted_string[i + 1] = grid[(arr[2] - 1) % 5][arr[1]];
            }
            else if (arr[2] == 0)
            {
                encrypted_string[i] = grid[(arr[0] - 1) % 5][arr[1]];
                encrypted_string[i + 1] = grid[4][arr[1]];
            }
            else
            {
                encrypted_string[i] = grid[(arr[0] - 1) % 5][arr[1]];
                encrypted_string[i + 1] = grid[(arr[2] - 1) % 5][arr[1]];
            }
        }
        else
        {
            encrypted_string[i] = grid[arr[0]][arr[3]];
            encrypted_string[i + 1] = grid[arr[2]][arr[1]];
        }
    }
}


void encryption(char grid[][5], char *message, char *output_message)
{
    char *temp;
    temp = string_upper(message);
    printf("\nMessage: %s\n", temp);

    int no_elements = 0;
    char string_list[100][100];

    string_2_list(temp, string_list, &no_elements);

    printf("\nFormatted Message: ");
    for (int i = 0; i < no_elements; i++)
    {
        message_formatting(string_list[i]);
        printf("%s ", string_list[i]);
        encrypt_message(grid, string_list[i]);
        strcat(strcat(output_message, string_list[i]), " ");
    }
}

void decryption(char grid[][5], char *message, char *output_message)
{
    char *temp;
    temp = string_upper(message);
    printf("\nMessage: %s\n", temp);

    int no_elements = 0;
    char string_list[100][100];

    string_2_list(temp, string_list, &no_elements);

    printf("\nBefore formatting: ");
    for (int i = 0; i < no_elements; i++)
    {
        decrypt_message(grid, string_list[i]);
        printf("%s ", string_list[i]);
        output_formatting(string_list[i]);
        strcat(output_message, string_list[i]);
        strcat(output_message, " ");
    }
}

//Working
/* Key
Enter keyword (preferably without repeated letters): qwerty
Formatted key: QWERTY

Enter keyword (preferably without repeated letters): hello
Formatted key: HELO
*/

/* Grid
Formatted key: QWERTY
Q   W   E   R   T
Y   A   B   C   D
F   G   H   I   K
L   M   N   O   P
S   U   V   X   Z

Formatted key: HELO
H   E   L   O   A
B   C   D   F   G
I   K   M   N   P
Q   R   S   T   U
V   W   X   Y   Z
*/

/* Input
Enter string to be encrypted: qwerty
Formatted string: QWERTY

Enter string to be encrypted: hell
Formatted string: HELXLX

Enter string to be encrypted: james
Formatted string: JAMESX

Enter string to be encrypted: hello
Formatted string: HELXLO

Enter string to be encrypted: helllo
Formatted string: HELXLXLO

Enter string to be encrypted: haxx
Formatted string: HAXQXQ

Enter string to be encrypted: haxxo
Formatted string: HAXQXO

Enter string to be encrypted: hello world
Formatted string: HELXLOWORLDX
*/

/* Encryption
Take key input and format it using the above algorithm for keys, removing repeated characters.
Form a grid using the above algorithm.
Take input to be encrypted and format it using the above algorithm for strings.

1> take letters in pairs from formatted input
ex: QWERTY --> QW ER TY

2> if the pair of letters is in the same column in the grid, shift down
ex: QS --> YQ
Q
Y
F
L
S

3> if the pair of letters is in the same row in the grid, shift right
ex: KP --> MI
I   K   M   N   P

4> if the pair of letters is the diagonal of a rectangle, switch to the other diagonal horizontally
ex: DS --> GQ
D   F   G
I   K   M
Q   R   S

5> join all pairs and return encrypted string
*/

/* Decryption
Take key input and format it using the above algorithm for keys, removing repeated characters
Form a grid using the above algorithm
Take encrypted input

1> take letters in pairs from formatted input
ex: QWERTY --> QW ER TY

2> if the pair of letters is in the same column in the grid, shift up
ex: YQ --> QS
Q
Y
F
L
S

3> if the pair of letters is in the same row in the grid, shift left
ex: MI --> KP
I   K   M   N   P

4> if the pair of letters is the diagonal of a rectangle, switch to the other diagonal horizontally
ex: GQ --> DS
D   F   G
I   K   M
Q   R   S

5> join all pairs and return encrypted string
*/