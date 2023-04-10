#ifndef CLASS_H
#define CLASS_H

#include <header.h>

/************************************************************************************
**     CLASS NAME        :      lsee
**
**    DESCRIPTION        :	Contains Declaration of all the variable and functions
**
**     RETURNS           :      NOT APPLIED
************************************************************************************/

class localSearchEngine{
    //struct to make a  linked list
    //linked list will be used to store file names and path names of those which came as a result after a search was done
    typedef struct struct_File{
    char f_name[MAX_LENGTH];//To contain filename
    char f_path[MAX_PATH_LENGTH];//to contain path of the file
    struct struct_File* next;//To point to the next node in the linked list
    }File;
    //pointers to nodes of linked list
    File *head = NULL;//Will point to the start of the linked list
    File *curr = NULL;//will point to the current node of the linked list

    int search = SEARCH_WITH_FILENAME;//act as a flag to search with filename or word/string in our local system
    char filename[MAX_FILENAME];//to take filename
    char input[MAX_LENGTH];//to take string or word
    //char path[MAX_PATH_LENGTH] = "/home2/";//Deafult path of user directory
    int fileCount = 0;//file increment counter
    int counter=0;

public:
	char path[MAX_PATH_LENGTH]="home2/";//Default path of user directory
    int isFile(char *);//To check if the current path is leads to a file / directory /
    char *returnFileName(char *);//To extract the filename from the path taken as input
				//Last token in the path will be considered as the file name
    int createFileNode(char *);//To Create Node in the linked list and initialise the newly created node
    int searchInFile(char *);//To open a file and search for searched word/string
    int openFile(char *);//To print or display the contents of the file
    int printLinkedList(File **);//To print the complete linked list
    int freeMemory(File **);//To free all the nodes of the linked list
    int allocateMemory();//To store the pointer to every node of linked list for easy access
    int searchLocalSystem(const char *);//To search all the directories in the given path
    int searchByWord();//To search files containing the given word / sentence / string
    int searchByFilename();//To search a file just by using the filename
    int openFileByPath();//To search and display the contents of a file by providing file's absolute path
};
#endif
