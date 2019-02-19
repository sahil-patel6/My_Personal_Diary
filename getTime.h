//
// Created by Sahil Patel on 11/21/2018.
//
#include <stdio.h>
#include <time.h>
#include <string.h>

#ifndef MY_PERSONAL_DIARY_GETTIME_H
#define MY_PERSONAL_DIARY_GETTIME_H

#endif //MY_PERSONAL_DIARY_GETTIME_H
char date[20];
char* getSystemTime() {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char year[5] = "";
    char month[5] = "";
    char day[5] = "";
    sprintf(year,"%d",tm.tm_year+1900);
    sprintf(month,"%d",tm.tm_mon +1);
    sprintf(day,"%d",tm.tm_mday);
    memset(date, 0, sizeof(date));
    strcat(date,strcat(day,"."));
    strcat(date,strcat(month,"."));
    strcat(date,year);
    return date;
}
