//
// Created by Sahil Patel on 11/21/2018.
//

#ifndef MY_PERSONAL_DIARY_FILE_HANDLING_H
#define MY_PERSONAL_DIARY_FILE_HANDLING_H

#endif //MY_PERSONAL_DIARY_FILE_HANDLING_H
#include <dirent.h>
#include <errno.h>
#include "getTime.h"
#include <string.h>
/*
 checkUserExistOrNot function check whether the user exists or not,
 if exists then it returns 0 as code,
 if not exists then it return 1 as code,
 else error code and quits program
 */

int checkUserExistOrNot(char Name[]){
    DIR* dir = opendir(Name);
    if (dir)
    {
        return 0;
    }
    else if (ENOENT == errno)
    {
        return 1;
    }
    else
    {
        printf("An error occured, please try again!!");
        exit(0);
    }
}

void createUser(char username[],char *password){
    char command[50] = "mkdir ";
    strcat(command,username);
    system(command);
    char commandForHiding[20] = "";
    strcat(commandForHiding,"attrib +h ");
    strcat(commandForHiding,username);
    system(commandForHiding);
    FILE *file;
    char commandToCreatePasswordFile[50] = "";
    strcat(commandToCreatePasswordFile,username);
    strcat(commandToCreatePasswordFile,"/");
    strcat(commandToCreatePasswordFile,"password.txt");
    file = fopen(commandToCreatePasswordFile,"w");
    fputs(password,file);
    fclose(file);
}
int loginUser(char Username[], char password[]){
    FILE *file;
    char commandToReadPasswordFile[20] = "";
    strcat(commandToReadPasswordFile,Username);
    strcat(commandToReadPasswordFile,"/");
    strcat(commandToReadPasswordFile,"password.txt");
    file = fopen(commandToReadPasswordFile,"r");
    char data[50];
    char s;
    int i=0;
    while((s = fgetc(file)) != EOF){
        data[i]=s;
        i++;
    }
    int flag = 1;
    for (int j = 0; j < i; ++j) {
        if(data[j] != password[j]){
            flag = 0;
        }
    }
    fclose(file);
    if(flag == 1){
        return 1;
    }else{
        return 0;
    }
}

void addDiary(char nam[],char *diary){
    printf("\n%s\n",nam);
    char commandToAddDiary[20] = "";
    strcat(commandToAddDiary,nam);
    strcat(commandToAddDiary,"/");
    strcat(commandToAddDiary,getSystemTime());
    strcat(commandToAddDiary,".txt");
    FILE *file;
    file = fopen(commandToAddDiary,"a");
    fprintf(file,diary);
    fprintf(file,"\n===========================================================\n");
    fclose(file);
    printf("Successfully added\n");
}

void viewDiary(char name[]){
    DIR *dir;
    struct dirent *ent;
    char nameOfUser[20] = "";
    strcat(nameOfUser,name);
    if ((dir = opendir (nameOfUser)) != NULL) {
        /* print all the files and directories within directory */
        while ((ent = readdir (dir)) != NULL) {
            if(strcmp(ent->d_name,"password.txt") != 0 && strcmp(ent->d_name,".") != 0 && strcmp(ent->d_name,"..") != 0){
                char nameOfFile[20]="";
                strcat(nameOfFile,ent->d_name);
                char fileName[20];
                for (int i = 0; i < strlen(nameOfFile) - 4; ++i) {
                    fileName[i] = nameOfFile[i];
                }
                printf("%s",fileName);
                printf(" :\n");
                FILE *file;
                char directory[20]="";
                strcat(directory,name);
                strcat(directory,"/");
                strcat(directory,nameOfFile);
                file = fopen(directory,"r");
                char c = fgetc(file);
                while (c != EOF)
                {
                    if (c >= 0 && c<=256)
                        printf ("%c", c);
                    c = fgetc(file);
                }
                fclose(file);
            }
        }
        closedir (dir);
    } else {
        /* could not open directory */
        printf("Error occured");
    }
}