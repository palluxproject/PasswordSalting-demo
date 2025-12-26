#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// Generates a simple hash value from a given string
unsigned int simpleHash(char *str){
    unsigned int hash =0;
        for(int i=0; str[i]!= '\0'; i++){
            hash = hash * 31 + str[i];
        }
        return hash;
    }

// Generates a random salt string to be added to the password. Ensures same passwords produce different hashes
void generateSalt(char *salt){
    char set[]= "abcdefghijklmnopqrstuvwxyz0123456789";
    for(int i=0; i <6; i++){
        salt[i] = set[rand() % 36];
    }
    salt[6] = '\0';
}

// Handles new user registration
// takes username and password, generates salt.
// hashes (password + salt) and stores data in a file
void UserRegister(){
    char username[50];
    char password[20];
    char salt[7];
    unsigned int hash;

    printf("Set Username: ");
    scanf("%49s", username);

    printf("Set password: ");
    scanf("%19s", password);
    
    generateSalt(salt);

    char combine[70];
    strcpy(combine, password);
    strcat(combine, salt);

    hash = simpleHash(combine);

    FILE *fptr = fopen("users.txt", "a");
    if( fptr == NULL){
        printf("error opening file \n");
        return;
    }
    fprintf(fptr, "%s %s %u\n", username, salt, hash);
    fclose(fptr);

    printf("USER REGISTERED SUCCESSFULLY! \n");
}

// Handles user login
//Reads stored salt and hash from file.
// re-hashes entered password and verifies credentials.
void UserLogin(){
    char username[50];
    char password[20];
    char salt[7];
    char fileuser[50];
    unsigned int inputhash, storedhash;

    printf("Enter Username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%19s", password);

    FILE *fptr = fopen ("users.txt", "r");
    if( fptr == NULL){
        printf("error opening file \n");
        return;
    }
    while(fscanf (fptr, "%s %s %u", fileuser, salt, &storedhash) == 3){
        if(strcmp (username,fileuser) == 0){
            char combine[60];
            strcpy(combine, password);
            strcat(combine, salt);

            inputhash = simpleHash(combine);

            if (inputhash == storedhash){
                printf("LOGIN SUCCESSFUL:) \n");
            }else{
                printf("WRONG PASSWORD :( \n");

            }
            fclose(fptr);
            return;
        }

    }
    fclose(fptr);
    printf("USER NOT FOUND! PLEASE REGISTER\n");
}

// displays the main menu and choices.
int main(){
    srand(time(NULL));
    int choose;

    while(1){
        printf("\n 1) Register \n 2) Login \n 3)Exit \n CHOOSE: ");
        scanf("%d", &choose);

        if(choose == 1){
            UserRegister();
        }else if(choose == 2){
            UserLogin();
        }else{
            break;
        }
        }
        return 0;
         
    }




