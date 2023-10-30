#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    FILE *fp1,*fp2;
    char line[100];
    int lineNumber = 1;
    int targetName;
    int accIterator;//account iterator.
    char updatedName[20];
    int flag = 0;


    if((fp1 = fopen("text.txt","r")) == NULL){//have some doubts.
        printf("error!\n\n");
        exit(1);
    }
    
    while(fgets(line,sizeof(line),fp1)){
        // removeNewLine(line,sizeof(line));
        printf("%s",line);
    }
    //info about the text.txt have been printed.
    fclose(fp1);

    //now comes the updating part.

    printf("What is your target name: ");
    scanf("%d",&targetName);
    getchar();
    printf("What is the name: ");
    scanf("%s",updatedName);
    getchar();
    // getchar();

    if((fp1 = fopen("text.txt","r")) == NULL){//have some doubts.
        printf("error!\n\n");
        exit(1);
    }
    if((fp2 = fopen("temp.txt","a")) == NULL){
        printf("error!\n\n");
        exit(1);
    }

    while(fgets(line,sizeof(line),fp1)){
        // removeNewLine(line,sizeof(line));
        if(lineNumber%2 && atoi(line)){
            accIterator = atoi(line);
        }
        if(accIterator == targetName && !flag){
            fprintf(fp2,"%d.\n%s\n",accIterator,updatedName);//
            // accIterator++;
            flag = 1;
        }
        else if(accIterator != targetName){
            fprintf(fp2,"%s",line);
        }
        lineNumber++;
    }
    fclose(fp2);
    fclose(fp1);
    if(remove("text.txt")){//false if successful
        perror("error while removing text.txt\n\n");
        exit(1);
    }
    if(rename("temp.txt","text.txt")){//false if successful.
        perror("error while renaming temp.txt to text.txt\n\n");
        exit(1);
    }

    return 0;
}