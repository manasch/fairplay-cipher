#include<stdio.h>
#include<string.h>

#include"cipher.h"

int main()
{
    int user_choice;
    char key[50];
    char message[1000];
    char output_message[1000] = "";
    char grid[5][5];

    printf("\n--------PLAYFAIR CIPHER---------\n");

    //Loop until user enters the correct input
    do
    {
        printf("\nWhich operation do you want to perform ?\n");
        printf("\n1) Encryption\n2) Decryption\n3) Exit\n");
        printf("\nSelect Option(1/2/3): ");
        scanf("%d", &user_choice);
        fflush(stdin);
        
        if(user_choice == 3)
        {
            printf("\nExiting Program...");
            exit(0);
        }
    } while(user_choice != 1 && user_choice != 2 && user_choice != 3);

    printf("\nEnter the keyword: ");
    scanf("%s", key);
    fflush(stdin);

    //formatting the keyword to remove repeating characters
    format_key(key);

    //inserting values to 2D array 5x5 grid
    make_grid(key, grid);

    printf("\nKey Grid:\n\n");
    for (int i = 0; i < 5; i++)
    {
        printf("\t");
        for (int j = 0; j < 5; j++)
        {
            printf("%2c ", grid[i][j]);
        }
        printf("\n");
    }
    
    printf("\nEnter the message to encrypt / decrypt:\n\n");
    scanf("%[^\n]s", message);

    switch (user_choice)
    {
    case 1:
        encryption(grid, message, output_message);

        printf("\nEncrypted message: %s\n", output_message);
        break;
    
    case 2:
        decryption(grid, message, output_message);

        printf("\nDecrypted message: %s\n", output_message);
        break;
    
    default:
        printf("\nInvalid Input");
        break;
    }
}
