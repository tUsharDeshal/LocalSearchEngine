/************************************************************************************
**
**        DESCRIPTION    :    Sprint (Local Search Engine)
**
**       last updated    :    09-04-2023
**
************************************************************************************/

#include<localSearchEngine.h>

/************************************************************************************
**     FUNCTION NAME     :     main
**
**    DESCRIPTION        :     Displaying the user interface /providing options and
**                             calling operation functions
**
**     RETURNS           :     Returns an integer(EXIT_SUCCESS)
**
**     Created by        :     Team
************************************************************************************/
using namespace std;
int main(void)
{
	localSearchEngine s;
    int flag = 1;
    char * username = getlogin();
    do{
        //for user interface details/design
        LINE
        cout<<"\t\t\tWelcome to Local Search Engine(LSE)\t\n\n";

        LINE
                cout<<"\t\t1. Search by word(s)\n";
                cout<<"\t\t2. Search by filename\n";
                cout<<"\t\t3. Open file with absolute path\n";
                cout<<"\t\t4. Quit\n";
                LINE
                cout<<"\t\tChoose an option(1-4):";

                char ch[MAX_LENGTH];
                //for taking the input choice among the options provided
                cin>>ch;

                getchar();//for clearing next line from buffer
                cout<<endl;

                if(strlen(ch) > 1){
                    ch[0] = '6';
                }

		strcpy(s.path,"/home2/");
		strcat(s.path,username);
		strcat(s.path,"/");
                //handeling user cases
                switch (ch[0])
                {
                    case '1':
                        //function call to search by word or sentence in our file system
                        s.searchByWord();
                        break;

                    case '2':
                        // function call to search by file name in our file system
                        s.searchByFilename();
                        break;

                    case '3':
                        //function call to open file with given absolute file path
                        s.openFileByPath();
                        break;
                    case '4':
                        // for exit
                        exit(EXIT_SUCCESS);

                    default:
                        //to handle unwanted choices
                        cout<<"\t\tInvalid choice please select among(1-4) only..\n\n";
                        flag=1;
                        break;
                }

    }while(flag==1);//to recur among the choices

    return(EXIT_SUCCESS);
}





