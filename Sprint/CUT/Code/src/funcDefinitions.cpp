#include <localSearchEngine.h>

/************************************************************************************
**     FUNCTION NAME     :      allocateMemory
**
**    DESCRIPTION        :      creates a pointer to an array of pointers of File structure
**                              and stores the pointer to every node for quick access and
**                              calls the function printLinkedList
**
**     RETURNS           :      returns EXIT_SUCCESS/EXIT_FAILURE
**
************************************************************************************/

int localSearchEngine::allocateMemory(){
    //allocating memory for array to store address of nodes
    File **ptr = new File*[fileCount];
    //checking if memory is allocated or not
    if(ptr == NULL){

        return EXIT_FAILURE;
    }

    if(head != NULL){//checking if linked list is not empty
        File * tmp = head;
        int c = 0;
        //storing address of each node in array
        while(tmp != NULL){
            *(ptr + c) = tmp;
            tmp = tmp->next;
            c++;
        }
    }
    //calling function to print the linked list
    printLinkedList(ptr);

    int res = freeMemory(ptr);
    if(res == EXIT_FAILURE){
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}


/************************************************************************************
**     FUNCTION NAME     :     createFileNode
**
**    DESCRIPTION        :    function to create a node in a Linked List
**
**     RETURNS           :    returns EXIT_SUCCESS/EXIT_FAILURE
**
************************************************************************************/

int localSearchEngine::createFileNode(char *path){
    //making a copy of original path
    char copyPath[MAX_PATH_LENGTH];
    strcpy(copyPath, path);
    //if linked list is empty
    if(head == NULL){
        head = new File;
        if(head==NULL)//if allocating memory for node is failed
        {
            fprintf(stderr,"%s","Memory Allocation Failed...!!\n");
            return EXIT_FAILURE;
        }
        strcpy(head->f_path, copyPath);//storing path in node
        //calling function to get the file name from the path
        char * str = returnFileName(path);
        strcpy(head->f_name, str);//storing file name in the node
        counter=0;
        //printf("File %d --> %s path:[%s]\n",counter, head->f_name, head->f_path);
        cout<<"File "<<counter<<" --> "<<head->f_name<<" path:["<<head->f_path<<"]\n";
        free(str);
        //making adjustments to linked list
        head->next = NULL;
        curr = head;
    }
    //when linked list is not empty so adding new node to the last of the list
    else{
        curr->next = new File;
        if(curr->next==NULL)//if memory allocation for new node is failed
        {
            fprintf(stderr,"%s","Memory Allocation Failed...!!\n");
            return EXIT_FAILURE;
        }
        //adjustments to linked list
        curr = curr->next;
        strcpy(curr->f_path, copyPath);
        char * str = returnFileName(path);//calling function to get the file name from the path
        strcpy(curr->f_name, str);
        counter+=1;
        //printf("File %d --> %s path:[%s]\n",counter, curr->f_name, curr->f_path);
        cout<<"File "<<counter<<" --> "<<curr->f_name<<" path:["<<curr->f_path<<"]\n";
        free(str);
        curr->next = NULL;
    }
    return EXIT_SUCCESS;
}
/************************************************************************************
**     FUNCTION NAME     :      freeMemory
**
**    DESCRIPTION        :      free all the memory created dynamically till now
**
**     RETURNS           :      returns EXIT_SUCCESS/EXIT_FAILURE
**
************************************************************************************/

int localSearchEngine::freeMemory(File **ptr){

    if(ptr == NULL){
        return EXIT_SUCCESS;
    }
    //freeing all the dyamically allocated memory traversing through the array of pointers
    for(int i = 0; i<fileCount; i++){
        if(*(ptr+i) != NULL){
            free(*(ptr+i));//free each node
            *(ptr+i)=NULL;
        }
    }
    head = NULL;
    curr = NULL;
    free(ptr);
    ptr=NULL;
    if(ptr != NULL){
        return EXIT_FAILURE;
    }else{
        return EXIT_SUCCESS;
    }
}
/************************************************************************************
**     FUNCTION NAME     :     isFile
**
**    DESCRIPTION        :    function to find whether given path is a directory or
**                            a file
**
**     RETURNS           :    return an integer (0=directory,1=file ,-1 =elsewise)
**
**
************************************************************************************/

int localSearchEngine::isFile(char* name)
{
    //decalared a variable directory to store contents of a directory using opendir() funciton
    DIR* directory = opendir(name);//open directory
    if(directory != NULL){
     closedir(directory);//close opened directory
     return 0;
    }
    if(errno == ENOTDIR){//when the entry is not a dir "1" will be returned
     return 1;
    }
    return -1;//when the given name is neither directory nor file
}
/************************************************************************************
**     FUNCTION NAME     :      openFile
**
**    DESCRIPTION        :      it is a utility function which takes the file path and prints its
**                              contents on the console
**
**     RETURNS           :      returns EXIT_SUCCESS/EXIT_FAILURE
**
************************************************************************************/

int localSearchEngine::openFile(char * fpath){
    FILE * fptr = fopen(fpath, "r");//opening file in read mode only
    if(fptr == NULL){//if the pointer to file is not assigned
        fprintf(stderr,"%s","File not Found...!!\n");
        if(fptr){
            fclose(fptr);
        }
        return EXIT_FAILURE;
    }
    if(isFile(fpath) == 0){//checking if the given path is a file or a directory
        fprintf(stderr,"%s","Given path is a directory...!!\n");

        if(fptr){
            fclose(fptr);
        }

        return EXIT_FAILURE;
    }

    cout<<"File opened!\n\n";
    LINE//macro
    char c = fgetc(fptr);
    while (c != EOF)//looping and printing until the end of the file is encountered
    {
        printf ("%c", c);
        c = fgetc(fptr);
    }

    cout<<"\n";
    fclose(fptr);//close the opened file

    return EXIT_SUCCESS;
}
/************************************************************************************
**     FUNCTION NAME     :      openFileByPath
**
**    DESCRIPTION        :      function to get the absolute file path and displays all the
**                              contents of the given file path using openFile function
**
**     RETURNS           :      returns EXIT_SUCCESS/EXIT_FAILURE
**
************************************************************************************/

int localSearchEngine::openFileByPath(){
    //taking absolute path as input
    cout<<"Enter abolute path to the file:\n";
    cout<<"$:"<<path;
    char pathInput[MAX_LENGTH];//array to store input
    fgets(pathInput, MAX_LENGTH, stdin);//input
    pathInput[strlen(pathInput) - 1] = '\0';
    strcat(path, pathInput);//concatenating input and path
    openFile(path);//calling function to open file and display file's contents
    return EXIT_SUCCESS;
}

/************************************************************************************
**    FUNCTION NAME     :      printLinkedList
**
**    DESCRIPTION        :     prints the Link List
**
**     RETURNS           :    returns EXIT_SUCCESS/EXIT_FAILURE
**
**
************************************************************************************/

int localSearchEngine::printLinkedList(File **ptr){
    //checking if files are found or not
    if(fileCount == 0 || ptr==NULL){
        fprintf(stderr,"%s","No files Found for the searched word(s)...!!\n");
        return EXIT_FAILURE;
    }
    //taking input from user to open any file
    int flag = 0;
    char mychoice[MAX_LENGTH];
    LINE//macro
    //taking input
    cout<<"\tDo you want to open any file!!(y/n) : ";
    cin>>mychoice;
	cout<<endl;
    getchar();
    //if input is y or Y
    if(mychoice[0]=='y'||mychoice[0]=='Y')
    {

    do
    {
        cout<<"\n"<<fileCount<<" file(s) found\n\n";
        LINE//macro
            //input for file number
            cout<<"\tSelect the file number which you want to open : ";
            cout<<endl;
            char option[MAX_LENGTH];
            int myflag = 0;
            int num = 0;
            do
            {
                cout<<"\tPlease enter file index number (Index starts from \"0\"): ";
                cin>>option;
                cout<<endl;
                getchar();
                myflag=0;
                num=0;
                //cross checking if the given input is a valid index or not
                for(int i=0;option[i]!='\0';i++)
                {
                    if(isdigit(option[i])==0)
                    {
                        myflag=1;
                        break;
                    }
                    else
                    {
                        num=num*10+(option[i]-48);
                    }
                }
                if(myflag==1||num<0||num>fileCount-1)
                    fprintf(stderr,"%s","File index does not exist...!!\n");


            } while (num < 0 || num > fileCount-1||myflag==1);
            //when given input is valid index
            File *tmp = *(ptr+num);//assigning address of node
            LINE
            openFile(tmp->f_path);//calling function to open and display the contents of the file
            num= -1;
            LINE//macro
            cout<<"\tDo you want to open other file?(y/n) : ";
            char ch[MAX_LENGTH];
            cin>>ch;
            cout<<endl;
            getchar();
            if(strlen(ch) > 1){
                ch[0] = '5';
            }

            switch (ch[0])
            {
            case 'y':
            case 'Y':
                flag = 0;
                break;
            case 'N':
            case 'n':
                flag = 1;
                break;
            default:
                fprintf(stderr,"%s","Invalid Choice...!!\n");
                flag = 1;
                break;
            }

    } while (flag == 0);
    }
    else if((mychoice[0]!='n' && mychoice[0]!='N' )||strlen(mychoice)>1)
    {
        fprintf(stderr,"%s","Invalid choice!!\n");
    }

    return EXIT_SUCCESS;
}
/************************************************************************************
**     FUNCTION NAME     :     extractFileName
**
**    DESCRIPTION        :    function to extract the File name from given path
**
**     RETURNS           :    return a pointer to char
**
**************************************************************************************/
char* localSearchEngine::returnFileName(char * path){
	char r[]="Memory Allocation Failed!!";
	char *rr=new char[MAX_LENGTH];
	strcpy(rr,r);
   char *token = strtok(path, "/");//making token of string from the path
    char *prev =new char[MAX_LENGTH];
    if(prev==NULL){//if memory allocation for prev is failed
        return rr;
    }
    while(token != NULL){//looping through the until the last token is stored in prev
        strcpy(prev, token);
        token = strtok(NULL, "/");
    }
    //return prev which contains file name
    return prev;
}
/************************************************************************************
**     FUNCTION NAME     :      searchFileName
**
**    DESCRIPTION        :      function to get the search string(file Name) and call the file
**                              system(searchLocalSystem) to find the given file name
**
**     RETURNS           :      returns EXIT_SUCCESS/EXIT_FAILURE
**
************************************************************************************/

int localSearchEngine::searchByFilename(){
    search=SEARCH_WITH_FILENAME;
    int flag = 0;
    cout<<"Enter filename to be searched:\n";
    fgets(filename,MAX_LENGTH, stdin);
    cout<<"Searching "<<filename<<endl;
    LINE//macro
    filename[strlen(filename) - 1] = '\0';

    cout<<"Do you want to provide any absolute directory path?(y/n)\n";

    char userPath[MAX_LENGTH];
    char c[10];
    fgets(c, 10, stdin);//input from user
    c[strlen(c) - 1]='\0';

    if(strlen(c) > 1){
        c[0] = 'k';
    }
    //checkng user input
    switch (c[0])
    {
        //when user wants to provide absolute path
        case 'y':
        case 'Y':
            flag = 1;
            cout<<"Enter absolute path:\n";
            cout<<"$:"<<path;
            fgets(userPath, MAX_LENGTH, stdin);
            userPath[strlen(userPath)-1] = '\0';
            //concatenating input with path
            strcat(path, userPath);
            strcat(path, "/");
            cout<<"\n";
            LINE
            searchLocalSystem(path);//calling function to search in given path

            break;
        //when user does not provide absolute path
        case 'n':
        case 'N':
            flag = 1;
            searchLocalSystem(path);//calling function to start search
            break;
        default:
             fprintf(stderr,"%s","Innvalid Choice.\n");
            break;
    }

    if(flag == 1){
        int res = allocateMemory();//calling function to get the array of pointers and print linked list
        if(res == EXIT_FAILURE){
            fprintf(stderr,"%s","Cannot list files.\n");
            fileCount = 0;

            return EXIT_FAILURE;
        }
    }
    fileCount = 0;

   return EXIT_SUCCESS;
}

/************************************************************************************
**     FUNCTION NAME     :      searchByWord
**
**    DESCRIPTION        :      function to get the search string and call the file system(searchLocalSystem)
**                              to find the given word
**
**     RETURNS           :      returns EXIT_SUCCESS/EXIT_FAILURE
**
************************************************************************************/

int localSearchEngine::searchByWord(){

    search = SEARCH_WITH_WORD;
    int flag = 0;
    //asking input from user
    cout<<"Enter search string/word:\n";
    fgets(input,MAX_LENGTH, stdin);
    input[strlen(input) - 1] = '\0';
    LINE
    //Asking user for path (optional)
    cout<<"Do you want to search at any specific locations?(y/n)\n";

    char c[MAX_LENGTH];
    fgets(c, MAX_LENGTH, stdin);
    c[strlen(c) - 1] = '\0';

    if(strlen(c) > 1){
        c[0] = 'k';
    }

    //Checking user inpu
    char userPath[MAX_LENGTH];
    switch (c[0])
    {
        //if user wants to search string using a particular path
        case 'y':
        case 'Y':
            flag = 1;
            cout<<"Please provide path\n";
            cout<<path;
            fgets(userPath, 50, stdin);
            userPath[strlen(userPath) - 1] = '\0';
            strcat(path, userPath);
            strcat(path, "/");

            //calling function to start search in given path
            LINE
            cout<<"Searching..\n";
            searchLocalSystem(path);
            break;

        //if user wants to search string using a particular path
        case 'n':
        case 'N':
            cout<<"Searching..\n";
            cout<<"%s\n";
            flag = 1;
            //calling function to start search without any particular path
            searchLocalSystem(path);
            break;
        //message for wrong choice
        default:
            fprintf(stderr,"%s","Wrong Choice...!!\n");
            break;
    }

    if(flag == 1){
        //calling function to store addresses of nodes of linked list in an array of pointers
        int res = allocateMemory();
        //checking is files' names and path name is store or not
        if(res == EXIT_FAILURE){
            fileCount = 0;
            fprintf(stderr,"%s","Cannot list files.\n");
        return EXIT_FAILURE;
        }
    }

    fileCount = 0;

    return EXIT_SUCCESS;
}

/************************************************************************************
**     FUNCTION NAME     :     searchInFile
**
**    DESCRIPTION        :      it takes a single argument a pointer to char (path of file )
**                              opens the file and check whether givem search argument(string)
**                              is present inside the file. If present create a file node add it
**                              to the Linked List and increment file counter else skip the file.
**
**     RETURNS           :      returns EXIT_SUCCESS/EXIT_FAILURE
*************************************************************************************/

int localSearchEngine::searchInFile(char *path){
    FILE *f = fopen(path, "r");//opening the file in read mode only
    if( access( path, F_OK ) != 0) {
        //File doesn't have read permission
        return EXIT_FAILURE;
    }
    if(f == NULL){//if file is empty
        return EXIT_FAILURE;
    }
    char temp[MAX_LENGTH];//to store file's content
    //going in loop until file's content ends or string is found
    while (fgets(temp, MAX_LENGTH, f) != NULL)
    {
        if(strstr(temp, input) != NULL){ //Match found
            fileCount++;
            int res = createFileNode(path);//calling function to create a node which will store file name and path
            if(res == EXIT_FAILURE){
                return EXIT_FAILURE;
            }
            break;
        }
    }
    if(f){
        fclose(f);//close the opened file
    }
    return EXIT_SUCCESS;

}
/************************************************************************************
**     FUNCTION NAME      :      searchLocalSytem
**
**     DESCRIPTION        :      search the system recursively in all the directories for
**                              the given path
**
**     RETURNS            :      returns EXIT_SUCCESS/EXIT_FAILURE.
**
**
************************************************************************************/

int localSearchEngine::searchLocalSystem(const char * path){

    DIR *d;//DIR representing a directory stream
    //struct dirent contains directory access operations
    //Provides directory access
    struct dirent *dir;
    //opendir() opens a directory
    //returns a pointer to an object of type DIR on successful opening a dir
    d = opendir(path);
    if (d)//checking if directory is open or not
    {
        //readdir() represents all entries in a dir in an ordered sequence
        //readdir() returns a pointer to a structure representing dir entry
        while ((dir = readdir(d)) != NULL)
        {
            //if the entries in a directory starts with these given below characters
            //ignore such entries
            if(strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0 || dir->d_name[0] == '.'){
                continue;
            }
            //checking each entry of dir, if the entry is a file or a directory/folder
            char *currPath = (char *) calloc(1000, sizeof(char));
            strcat(currPath, path);
            strcat(currPath, dir->d_name);
            strcat(currPath, "/");
            //calling the function isFile to check if the entry is a file or a directory/folder
            if(isFile(currPath) == 0){
                searchLocalSystem(currPath); // Recursive call to the new appended path
            }else{
                //checking if files extensions match or not
                if(strstr(dir->d_name,".txt")==NULL && strstr(dir->d_name,".c")==NULL && strstr(dir->d_name,".h")==NULL && strstr(dir->d_name,".cpp")==NULL){
                    free(currPath);
                    continue;
                }
                //when file extensions are .txt or .c or .cpp or .h
                //open a file and search for given string using searchInFile()
                currPath[strlen(currPath) - 1] = '\0';
                if(search == SEARCH_WITH_WORD){
                    int res = searchInFile(currPath);
                    if(res == EXIT_FAILURE){
                        free(currPath);
                        return EXIT_FAILURE;
                    }
                }else{
                    if(strcmp(dir->d_name, filename) == 0 || strstr(dir->d_name,filename)!=NULL){
                        fileCount++;
                        int res = createFileNode(currPath);
                        if(res == EXIT_FAILURE){
                            free(currPath);
                            return EXIT_FAILURE;
                        }
                    }
                }
            }
            free(currPath);
        }
        closedir(d);//closing the open directory
    }
    else
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}


