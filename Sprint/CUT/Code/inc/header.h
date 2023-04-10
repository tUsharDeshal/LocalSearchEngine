#ifndef HEADERS_H
#define HEADERS_H

/************************************************************************************
**    HEADER FILES
************************************************************************************/
#include <iostream>
#include <cstdio>
#include <dirent.h>
#include <string>
#include <cstring>
#include <sys/stat.h>
#include <cstdlib>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>
/************************************************************************************
**    MACROS
************************************************************************************/
using namespace std;
#define MAX_LENGTH 50
#define MAX_FILENAME 20
#define MAX_PATH_LENGTH 1000
#define SEARCH_WITH_WORD 0
#define SEARCH_WITH_FILENAME 1
#define LINE for(int i = 0;i < 150;i++) cout<<":";cout<<endl;

#endif
