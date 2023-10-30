#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

void updatePassword(char* username){
    FILE *fp1, *fp2;
    int targetAccount;//the account no. that will be updated.
    int accountIterator = 1;//the file that is pointed by the pointer at a certain moment. 
    char websiteAddress[30];
    char emailAddress[50];
    char *password;
    char takePass[53];
    char line[100];
    int lineNumber = 1;
    int flag = 0;
    int choice;
    //viewing the information
    if((fp1 = fopen(username,"r")) == NULL){
        perror("error occured while opening the file!\n\n");
        exit(1);
    }
    while(fgets(line,sizeof(line),fp1)){
        if(lineNumber > 1){
            printf("%s",line);
        }
        lineNumber++;
    }
    fclose(fp1);
    lineNumber = 1;//because it will be needed further and it is necessary its value is one

    printf("Account you want to upgrade: ");
    scanf("%d",&targetAccount);
    getchar();
    printf("\n");

    printf("Updated website address: ");
    scanf("%s",websiteAddress);
    getchar();
    printf("\n");

    printf("Updated email address: ");
    scanf("%s",emailAddress);
    getchar();
    printf("\n");
    


    printf("1) give password\n\n2) generate password\n\nchoice = ");
    scanf("%d",&choice);
    getchar();
    printf("\n");


    if(choice == 1){
        again:
        scanf("%s",takePass);
        getchar();
        
        if(checkStrength(takePass,strlen(takePass))){
            password = takePass;
        }
        else{
            goto again;
        }
    }
    else{
        password = generatePassword(password);
    }

    //now starts the new file loading phase.
    fp1 = fopen(username,"r");
    if(fp1 == NULL){
        printf("Cann't find the file.\n\n");
        exit(1);
    }
    fp2 = fopen("temp.txt","a");
    if(fp2 == NULL){
        printf("Cann't create the file.\n\n");
        exit(1);
    }
    while(fgets(line, sizeof(line), fp1)){
        if((lineNumber-2)%5 == 0 && atoi(line) != 0){
            accountIterator = atoi(line);
        }
        if(accountIterator == targetAccount && !flag){
            fprintf(fp2,"%d.\n",accountIterator);
            fprintf(fp2,"Website address: %s\n",websiteAddress);
            fprintf(fp2,"Email Address: %s\n",emailAddress);
            fprintf(fp2,"Password: %s\n",password);
            fprintf(fp2,"---------------------------------------------------------------------\n");
            flag = 1;
        }
        else if(accountIterator != targetAccount){
            fprintf(fp2,"%s",line);
        }

        lineNumber++;
    }

    fclose(fp1);
    fclose(fp2);

    if(remove(username)){//false if successful
        perror("Error deleting the file!\n\n");
        exit(1);
    }
    // removed the the file with the backdated data.

    if(rename("temp.txt",username)){//false if successful
        perror("Erron occured while renaming!\n\n");
        exit(1);
    }
}
