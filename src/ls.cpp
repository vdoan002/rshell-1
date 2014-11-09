#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <time.h>
#include <fcntl.h>
#include <pwd.h>
#include <grp.h>

#define FLAG_a 1
#define FLAG_l 2
#define FLAG_R 4

using namespace std;

//function declarations
void listAllContent(string);
void listContent(string);
int flagCheck(int, char**);
void flag_no(int, char**);
void flag_a(int, char**);
void flag_l(int, char**);
void print_l(string);

int main (int argc, char** argv) {

	//check argv for flags
	int flags = flagCheck(argc, argv);

	//No flags
	if( flags == 0 )
	{	
		flag_no(argc, argv);
	}
	//-a
	else if( flags == FLAG_a )
	{
		flag_a(argc, argv);	
	}
	//-l
	else if( flags == FLAG_l )
	{
		flag_l(argc, argv);
	}

	return 0;
}

//function definitions
int flagCheck(int argCount, char** argVect) {
	int flags = 0;
	for( unsigned i = 1; i < argCount; i++ )
	{
		//Don't continue check if first param not flag
		if( argVect[1][0] != '-' )
			break;
		if( argVect[i][0] == '-' )
		{
			for( unsigned j = 1; argVect[i][j] != 0; ++j )
			{
				if( argVect[i][j] == 'a' )
					flags |= FLAG_a;
				else if( argVect[i][j] == 'l' )
					flags |= FLAG_l;
				else if( argVect[i][j] == 'R' )
					flags |= FLAG_R;
			}
		}
	}
	return flags;
}

void flag_no(int argCount, char** argVect) {
	if( argCount > 2 )
		{		
			cout << "Invalid expression" << endl;
			exit(1);
		}	
		else if( argCount == 2 )
		{
			listContent(argVect[1]);
		}	
		else
		{
			string pathToDir = ".";
			listContent(pathToDir);
		}
		return;
}

void listAllContent(string pathToDir) {
	DIR *dir;
	struct dirent *ent;
	int longestString = 0;
	int currentString = 0;
	vector<string>input;
	if ((dir = opendir (pathToDir.c_str())) != NULL) 
	{
  		// put files and directories into vector
  		while ((ent = readdir (dir)) != NULL)
		{
    		input.push_back(ent->d_name);
			currentString = input.back().size();
			if (currentString > longestString)
				longestString = currentString;
  		}
		//alpha sort
		sort(input.begin(),input.end());
		reverse(input.begin(),input.end());
		//print out vector
		int spacing = 0;
		while(!input.empty())
		{
			cout << left << setw(longestString+1)<< input.back() << " ";
			input.pop_back();
			++spacing;
			if ((spacing % 4) == 0)
				cout << endl;
		}
		if((spacing %4) != 0)
			cout << endl;
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
	int longestString = 0;
	int currentString = 0;
	vector<string>input;
	if ((dir = opendir (pathToDir.c_str())) != NULL) 
	{
  		// put files and directories into vector
  		while ((ent = readdir (dir)) != NULL)
		{	
			if(ent->d_name[0] != '.')
			{
    			input.push_back(ent->d_name);
				currentString = input.back().size();
				if (currentString > longestString)
					longestString = currentString;
			}
  		}
		//alpha sort
		sort(input.begin(),input.end());
		reverse(input.begin(),input.end());

		//print out vector
		int spacing = 0;
		while(!input.empty())
		{
			cout << left << setw(longestString+1)<< input.back() << " ";
			input.pop_back();
			++spacing;
			if ((spacing % 4) == 0)
				cout << endl;
		}

		if((spacing %4) != 0)
			cout << endl;
  		closedir (dir);
	}else 
	{
  		perror ("There was an error with readdir() ");
  		exit(1);
	}
}

void flag_a(int argCount, char** argVect) {
	int path = 0;
	for( unsigned i = 1; i < argCount; ++i )
	{
		if( argVect[i][0] != '-')
		{
			path = i;
			break;
		}
		if( argVect[i][1] != 'a')
		{
			cout << "Invalid expression" << endl;
			exit(1);
		}
	}	
	if( path == 0 )
	{
		string pathToDir = ".";
		listAllContent(pathToDir);
	}
	else if ( path != (argCount - 1) )
	{
		cout << "Invalid expression" << endl;
		exit(1);
	}else
	{
		listAllContent(argVect[path]);
	}
	
}

void flag_l(int argCount, char** argVect) {
	int path = 0;
	for( unsigned i = 1; i < argCount; ++i )
	{
		if( argVect[i][0] != '-')
		{
			path = i;
			break;
		}
		if( argVect[i][1] != 'l')
		{
			cout << "Invalid expression" << endl;
			exit(1);
		}
	}	
	if( path == 0 )
	{
		DIR *dir;
		struct dirent *ent;
		vector<string>input;
		if ((dir = opendir(".")) != NULL) 
		{
  			// put files and directories into vector
  			while ((ent = readdir (dir)) != NULL)
			{	
				if(ent->d_name[0] != '.')
    				input.push_back(ent->d_name);
  			}
			//alpha sort in reverse
			sort(input.begin(),input.end());
			reverse(input.begin(), input.end());
		}
		string curString;
		while (!input.empty())
		{	
			curString = input.back();
			print_l(curString);			
			input.pop_back();
			cout << endl;
		}

	}
	else if ( path != (argCount - 1) )
	{
		cout << "Invalid expression" << endl;
		exit(1);
	}else
	{
		DIR *dir;
		struct dirent *ent;
		vector<string>input;
		if ((dir = opendir(argVect[path])) != NULL) 
		{
  			// put files and directories into vector
  			while ((ent = readdir (dir)) != NULL)
			{	
    			input.push_back(ent->d_name);
  			}
			//alpha sort in reverse
			sort(input.begin(),input.end());
			reverse(input.begin(), input.end());
			string curString;
			while (!input.empty())
			{		
				curString = input.back();
				print_l(curString);			
				input.pop_back();
				cout << endl;
			}
			closedir (dir);
		}	
		else 
		{
  			perror ("There was an error with readdir() ");
  			exit(1);
		}
	}
}

void print_l(string cur) {
	struct stat sb;
	struct passwd *pwd;
	struct group *grp;
	if (stat(cur.c_str(), &sb) == -1) 
	{
   	perror("stat");
      exit(1);
   }
	printf( (S_ISDIR(sb.st_mode)) ? "d" : "-");
	printf( (sb.st_mode & S_IRUSR) ? "r" : "-");
   printf( (sb.st_mode & S_IWUSR) ? "w" : "-");
   printf( (sb.st_mode & S_IXUSR) ? "x" : "-");
   printf( (sb.st_mode & S_IRGRP) ? "r" : "-");
   printf( (sb.st_mode & S_IWGRP) ? "w" : "-");
   printf( (sb.st_mode & S_IXGRP) ? "x" : "-");
   printf( (sb.st_mode & S_IROTH) ? "r" : "-");
   printf( (sb.st_mode & S_IWOTH) ? "w" : "-");
   printf( (sb.st_mode & S_IXOTH) ? "x" : "-");
	cout << " " << sb.st_nlink;
 	if ((pwd = getpwuid(sb.st_uid)) != NULL)
   	cout << " " << pwd->pw_name;
   else
		cout << " " << sb.st_uid;
	if ((grp = getgrgid(sb.st_gid)) != NULL)
      cout << " " << grp->gr_name;
   else
		cout << " " << sb.st_gid;
   cout << " " << sb.st_size;
	string time = ctime(&sb.st_mtime);
	cout << " " << time.substr(4,3) << flush;	
	cout << " " << time.substr(8,2) << flush;
	cout << " " << time.substr(11,5) << flush;
	cout << " " << cur;
}

