#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string>

#define FLAG_a 1
#define FLAG_l 2
#define FLAG_R 4

using namespace std;

//function declarations
void listAllContent(string);
void listContent(string);


int main (int argc, char*argv[]) {

//check argv for flags
//------------------------------------------------------	
	int flags = 0;
	for( unsigned i = 1; i < argc; i++ )
	{
		//Don't continue check if first param not flag
		if( argv[1][0] != '-' )
			break;
		if( argv[i][0] == '-' )
		{
			for( unsigned j = 1; argv[i][j] != 0; ++j )
			{
				if( argv[i][j] == 'a' )
					flags |= FLAG_a;
				else if( argv[i][j] == 'l' )
					flags |= FLAG_l;
				else if( argv[i][j] == 'R' )
					flags |= FLAG_R;
			}
		}
	}
//------------------------------------------------------
//No flags
	if( flags == 0 )
	{	
		if( argc > 2 )
		{		
			cout << "Invalid expression" << endl;
			return 1;
		}	
		else if( argc == 2 )
		{
			listContent(argv[1]);
		}	
		else
		{
			string pathToDir = ".";
			listContent(pathToDir);
		}
	}
//-a
	else if( flags == 1 )
	{
		if( argc > 3 )
		{		
			cout << "Invalid expression" << endl;
			return 1;
		}
		else if( argc == 3 )
		{		
			listAllContent(argv[2]);
		}
		else
		{
			string pathToDir = ".";
			listAllContent(pathToDir);
		}
	}

	return 0;
}

//function definitions
void listAllContent(string pathToDir) {
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir (pathToDir.c_str())) != NULL) 
	{
  		// print all the files and directories 
  		while ((ent = readdir (dir)) != NULL)
		{
    		cout <<  ent->d_name << endl;
  		}
  		closedir (dir);
	}else 
	{
  		perror ("There was an error with readdir() ");
  		exit(1);
	}
}
void listContent(string pathToDir) {
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir (pathToDir.c_str())) != NULL) 
	{
  		// print all the files and directories 
  		while ((ent = readdir (dir)) != NULL)
		{
			if( ent->d_name[0] != '.')
    			cout <<  ent->d_name << endl;
  		}
  		closedir (dir);
	}else 
	{
  		perror ("There was an error with readdir() ");
  		exit(1);
	}
}
