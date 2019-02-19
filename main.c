#include <time.h>
#include <stdio.h>
#include <string.h>
#include <process.h>
#include <stdlib.h>

#include "file_handling.h"
void getDiaryContentsFromUser();
void login();
void showOptions();
void createOrViewDiariesAgain();
char diary[1024];
char name[50];
char password[50];
int main() {
    printf("Welcome to My Personal Diary!!!\n");
    printf("Enter you name(without spaces):\n");
    gets(name);
    /*
     checkUserExistOrNot function check whether the user exists or not,
     if exists then it returns 0 as code,
     if not exists then it return 1 as code,
     else error code and quits program
     and resultCode stores the code that is returned by the function
    */
    int resultCode = checkUserExistOrNot(name);
    // 0 - user exists
    // 1 - user doesn't exist
    switch(resultCode) {
        case 0:
            printf("You have already created account\n");
            login();
            showOptions();
            createOrViewDiariesAgain();
            break;
        case 1:
            printf("Enter Password:\n");
            gets(password);
            createUser(name,password);
            getDiaryContentsFromUser();
            addDiary(name,diary);
            showOptions();
        default:
            printf("Something went wrong, please try again");
            exit(0);
    }
    return 0;
}
int options;
void showOptions(){
    printf("Enter the options given below:\n");
    printf("1 - View Diaries\n");
    printf("2 - Add Diary\n");
    printf("3 - quit\n");
    scanf("%d",&options);
    switch (options){
        case 1:
            viewDiary(name);
            break;
        case 2:
            getDiaryContentsFromUser();
            addDiary(name,diary);
            break;
        case 3:
            exit(0);
        default:
            printf("Please enter valid choice\n");
            showOptions();
    }
}
int choice;
void createOrViewDiariesAgain(){
    printf("Do you want to view or create diaries again (0-no/1-yes)\n");
    scanf("%i",&choice);
    switch (choice){
        case 0:
            exit(0);
        case 1:
            showOptions();
        default:
            printf("Invalid choice\n");
            createOrViewDiariesAgain();
    }
}

void login(){
    printf("Please enter password:\n");
    gets(password);
    int result = loginUser(name,password);
    if (result == 0){
        printf("Wrong Password, Please Try Again!!\n");
        login();
    }else{
        printf("Correct Password\n");
    }
}

void getDiaryContentsFromUser(){
    printf("Enter the contents for Today's diary\n");
    int i=0;
    char s;
    printf("Enter only '/' keyword to the end of your diary and then hit enter to stop entering your diary\n");
    do{
        scanf("%c",&s);
        diary[i++] = s;
    }while (s != '/');
}