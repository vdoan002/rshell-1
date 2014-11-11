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
void flag_al(int, char**);
void flag_r(int, char **);
void flag_ar(int, char**);
void flag_lr(int, char**);
void flag_alr(int, char**);
void recurse_List(string);
void recurse_lList(string);
void recurse_alList(string);
void recurse_allList(string);
int isDirectory(const char*);
//Helper function and struct to ignore case sensitive
struct case_insensitive_less : public std::binary_function< char,char,bool >
{
    bool operator () (char x, char y) const
    {
        return toupper( static_cast< unsigned char >(x)) < 
               toupper( static_cast< unsigned char >(y));
    }
};
bool NoCaseLess(const std::string &a, const std::string &b)
{
	return std::lexicographical_compare( a.begin(),a.end(),
   b.begin(),b.end(), case_insensitive_less() );
}


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
	//-al
	else if(flags == 3)
	{
		flag_al(argc, argv);
	}
	//-R
	else if(flags == FLAG_R)
	{
		flag_r(argc, argv);
	}
	//-aR
	else if(flags == 5)
	{
		flag_ar(argc, argv);
	}
	//-lR
	else if(flags == 6)
	{
		flag_lr(argc, argv);
	}
	//-alR
	else if (flags == 7)
	{
		flag_alr(argc, argv);
	}else
		cout << "I don't know how you managed to get this message to appear.." << endl;
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
		if( argCount == 1 )
		{		
			string pathToDir = ".";
			listContent(pathToDir);		
		}	
		else if( argCount > 1 )
		{
			int i = 1;
			while (i < argCount)
			{
				if(argCount > 2)
					cout << argVect[i] << ":" << endl;
				listContent(argVect[i]);
				if((i+1) != argCount)
					cout << endl;
				++i;
			}
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
		sort(input.begin(),input.end(),NoCaseLess);
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
		sort(input.begin(),input.end(),NoCaseLess);
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
	else
	{
		int i = path;
		while (i < argCount)
		{
			if(path != (argCount -1))
				cout << argVect[i] << ":" << endl;
			listAllContent(argVect[i]);
			if((i+1) != argCount)
				cout << endl;
			++i;
		}
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
		//cout << "h";
		if ((dir = opendir(".")) != NULL) 
		{
  			// put files and directories into vector
  			while ((ent = readdir (dir)) != NULL)
			{	
				if(ent->d_name[0] != '.')
    				input.push_back(ent->d_name);
  			}
			//alpha sort in reverse
			sort(input.begin(),input.end(), NoCaseLess);
			reverse(input.begin(), input.end());
		}
   	else 
		{
  			perror ("There was an error with readdir() ");
  			exit(1);
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
	else
	{
		int i = path;
		while (i < argCount)
		{
			if(path != (argCount -1))
				cout << argVect[i] << ":" << endl;
			//listAllContent(argVect[i]);
			DIR *dir;
			struct dirent *ent;
			vector<string>input;
			//cout << argVect[i];
			if ((dir = opendir(argVect[i])) != NULL) 
			{
  				// put files and directories into vector
  				while ((ent = readdir (dir)) != NULL)
				{	
					if(ent->d_name[0] != '.')
    					input.push_back(ent->d_name);
  				}
				//alpha sort in reverse
				sort(input.begin(),input.end(),NoCaseLess);
				reverse(input.begin(), input.end());
				string curString;
				string curPath;
				while (!input.empty())
				{		
					curPath = argVect[i];
					curString = "/";
					curString += input.back();
					curPath += curString;
					//cout << curPath;
					print_l(curPath);			
					input.pop_back();
					cout << endl;
				}
				closedir (dir);
			}else 
			{
  				perror ("There was an error with readdir() ");
  				exit(1);
			}
			if((i+1) != argCount)
				cout << endl;
			++i;
		}
	}
}

void print_l(string cur) {
	struct stat sb;
	struct passwd *pwd;
	struct group *grp;
	unsigned found = cur.find_last_of("/\\");
//	cerr << cur;
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
   cout << " " << setw(5) << right << sb.st_size;
	string time = ctime(&sb.st_mtime);
	cout << " " << time.substr(4,3) << flush;	
	cout << " " << time.substr(8,2) << flush;
	cout << " " << time.substr(11,5) << flush;
	cout << " " << cur.substr(found+1);
}
void flag_al(int argCount, char** argVect) {
	int path = 0;
	for( unsigned i = 1; i < argCount; ++i )
	{
		if( argVect[i][0] != '-')
		{
			path = i;
			break;
		}
		if( argVect[i][1] != 'l' && argVect[i][1] != 'a' )
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
		//cout << "h";
		if ((dir = opendir(".")) != NULL) 
		{
  			// put files and directories into vector
  			while ((ent = readdir (dir)) != NULL)
			{	
    			input.push_back(ent->d_name);
  			}
			//alpha sort in reverse
			sort(input.begin(),input.end(), NoCaseLess);
			reverse(input.begin(), input.end());
		}
   	else 
		{
  			perror ("There was an error with readdir() ");
  			exit(1);
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
	else
	{
		int i = path;
		while (i < argCount)
		{
			if(path != (argCount -1))
				cout << argVect[i] << ":" << endl;
			//listAllContent(argVect[i]);
			DIR *dir;
			struct dirent *ent;
			vector<string>input;
			//cout << argVect[i];
			if ((dir = opendir(argVect[i])) != NULL) 
			{
  				// put files and directories into vector
  				while ((ent = readdir (dir)) != NULL)
				{	
    				input.push_back(ent->d_name);
  				}
				//alpha sort in reverse
				sort(input.begin(),input.end(),NoCaseLess);
				reverse(input.begin(), input.end());
				string curString;
				string curPath;
				while (!input.empty())
				{		
					curPath = argVect[i];
					curString = "/";
					curString += input.back();
					curPath += curString;
					//cout << curPath;
					print_l(curPath);			
					input.pop_back();
					cout << endl;
				}
				closedir (dir);
			}else 
			{
  				perror ("There was an error with readdir() ");
  				exit(1);
			}
			if((i+1) != argCount)
				cout << endl;
			++i;
		}
	}
}

void flag_r(int argCount, char** argVect) {
	int path = 0;
	for( unsigned i = 1; i < argCount; ++i )
	{
		if( argVect[i][0] != '-')
		{
			path = i;
			break;
		}
		if( argVect[i][1] != 'R')
		{
			cout << "Invalid expression" << endl;
			exit(1);
		}
	}	
	if( path == 0 )
	{
		string pathToDir = ".";
		cout << pathToDir << ":" << endl;
		recurse_List(pathToDir);
	}
	else
	{
		//cout << "hi";
		int i = path;
		while (i < argCount)
		{
			if(path != (argCount -1))
				cout << argVect[i] << ":" << endl;
			recurse_List(argVect[i]);
			if((i+1) != argCount)
				cout << endl;
			++i;
		}
	}
	
}

void recurse_List(string pathToDir) {
    listContent(pathToDir);	 
	 cout << endl;
	 DIR *dir;
    struct dirent *ent;
    vector<string>input;
    if ((dir = opendir (pathToDir.c_str())) != NULL)
    {
       // put files and directories into vector
       while ((ent = readdir (dir)) != NULL)
       {
          if(ent->d_name[0] != '.')
          {
				 string newPath = pathToDir + '/';
				 newPath += ent->d_name;
             input.push_back(newPath);
				 //cout <<input.back() << endl;
          }
       }
       //alpha sort
       sort(input.begin(),input.end(),NoCaseLess);
       reverse(input.begin(),input.end());
		 struct stat sb;
		 if (stat(pathToDir.c_str(), &sb) == -1) 
		 {
       	perror("stat");
        	exit(1);
       }

       while(!input.empty())
       {
			 if(isDirectory(input.back().c_str()))
          {
				 cout << input.back() << ":" << endl;
             recurse_List(input.back());
          }
          input.pop_back();
       }
   }
	return;
	
}

int isDirectory(const char *path)
{
    struct stat buf;
    stat(path, &buf);
    return S_ISDIR(buf.st_mode);
}

void flag_ar(int argCount, char** argVect){
	int path = 0;
	for( unsigned i = 1; i < argCount; ++i )
	{
		if( argVect[i][0] != '-')
		{
			path = i;
			break;
		}
		if( argVect[i][1] != 'R' && argVect[i][1] != 'a' ) 
		{
			cout << "Invalid expression" << endl;
			exit(1);
		}
	}	
	if( path == 0 )
	{
		string pathToDir = ".";
		cout << pathToDir << ":" << endl;
		recurse_allList(pathToDir);
	}
	else
	{
		//cout << "hi";
		int i = path;
		while (i < argCount)
		{
			if(path != (argCount -1))
				cout << argVect[i] << ":" << endl;
			recurse_allList(argVect[i]);
			if((i+1) != argCount)
				cout << endl;
			++i;
		}
	}
}

void recurse_allList(string pathToDir) {
    listAllContent(pathToDir);	 
	 cout << endl;
	 DIR *dir;
    struct dirent *ent;
    vector<string>input;
    if ((dir = opendir (pathToDir.c_str())) != NULL)
    {
       // put files and directories into vector
       while ((ent = readdir (dir)) != NULL)
       {
			if((ent->d_name[0] != '.' || ent->d_name[1] != '.')&&(ent->d_name[0] != '.' || ent->d_name[1] != '\0'))
         {
				string newPath = pathToDir + '/';
				newPath += ent->d_name;
            input.push_back(newPath);
			}
		 }
       //alpha sort
       sort(input.begin(),input.end(),NoCaseLess);
       reverse(input.begin(),input.end());
		 struct stat sb;
		 if (stat(pathToDir.c_str(), &sb) == -1) 
		 {
       	perror("stat");
        	exit(1);
       }

       while(!input.empty())
       {
			 if(isDirectory(input.back().c_str()))
          {
				 cout << input.back() << ":" << endl;
             recurse_allList(input.back());
          }
          input.pop_back();
       }
   }
	return;
	
}

void flag_lr(int argCount, char** argVect) {

	int path = 0;
	for( unsigned i = 1; i < argCount; ++i )
	{
		if( argVect[i][0] != '-')
		{
			path = i;
			break;
		}
		if( argVect[i][1] != 'R' && argVect[i][1] != 'l')
		{
			cout << "Invalid expression" << endl;
			exit(1);
		}
	}	
	if( path == 0 )
	{
		string pathToDir = ".";
		cout << pathToDir << ":" << endl;
		recurse_lList(pathToDir);
	}
	else
	{
		//cout << "hi";
		int i = path;
		while (i < argCount)
		{
			if(path != (argCount -1))
				cout << argVect[i] << ":" << endl;
			recurse_lList(argVect[i]);
			if((i+1) != argCount)
				cout << endl;
			++i;
		}
	}

}

void recurse_lList(string pathToDir) {
	 DIR *dir;
    struct dirent *ent;
    vector<string>input1;
    if ((dir = opendir (pathToDir.c_str())) != NULL)
    {
       // put files and directories into vector
       while ((ent = readdir (dir)) != NULL)
       {
          if(ent->d_name[0] != '.')
          {
				 string newPath = pathToDir + '/';
				 newPath += ent->d_name;
             input1.push_back(newPath);
				 //cout <<input.back() << endl;
          }
       }
       //alpha sort
       sort(input1.begin(),input1.end(),NoCaseLess);
       reverse(input1.begin(),input1.end());
	 }

	   string curString;
		while (!input1.empty())
		{	
			curString = input1.back();
			print_l(curString);			
			input1.pop_back();
			cout << endl;
		}
	// DIR *dir;
    //struct dirent *ent;
    vector<string>input;
    if ((dir = opendir (pathToDir.c_str())) != NULL)
    {
       // put files and directories into vector
       while ((ent = readdir (dir)) != NULL)
       {
          if(ent->d_name[0] != '.')
          {
				 string newPath = pathToDir + '/';
				 newPath += ent->d_name;
             input.push_back(newPath);
				 //cout <<input.back() << endl;
          }
       }
       //alpha sort
       sort(input.begin(),input.end(),NoCaseLess);
       reverse(input.begin(),input.end());
		 struct stat sb;
		 if (stat(pathToDir.c_str(), &sb) == -1) 
		 {
       	perror("stat");
        	exit(1);
       }

       while(!input.empty())
       {
			 if(isDirectory(input.back().c_str()))
          {
				 cout << endl;
				 cout << input.back() << ":" << endl;
             recurse_lList(input.back());
          }
          input.pop_back();
       }
   }
	return;
	
}

void flag_alr(int argCount, char** argVect) {
	int path = 0;
	for( unsigned i = 1; i < argCount; ++i )
	{
		if( argVect[i][0] != '-')
		{
			path = i;
			break;
		}
		if( argVect[i][1] != 'R' && argVect[i][1] != 'l' && argVect[i][1] != 'a')
		{
			cout << "Invalid expression" << endl;
			exit(1);
		}
	}	
	if( path == 0 )
	{
		string pathToDir = ".";
		cout << pathToDir << ":" << endl;
		recurse_alList(pathToDir);
	}
	else
	{
		int i = path;
		while (i < argCount)
		{
			if(path != (argCount -1))
				cout << argVect[i] << ":" << endl;
			recurse_alList(argVect[i]);
			if((i+1) != argCount)
				cout << endl;
			++i;
		}
	}
}

void recurse_alList(string pathToDir) {
	 DIR *dir;
    struct dirent *ent;
    vector<string>input1;
    if ((dir = opendir (pathToDir.c_str())) != NULL)
    {
       // put files and directories into vector
       while ((ent = readdir (dir)) != NULL)
       {
		 		string newPath = pathToDir + '/';
				newPath += ent->d_name;
            input1.push_back(newPath);
       }
       //alpha sort
       sort(input1.begin(),input1.end(),NoCaseLess);
       reverse(input1.begin(),input1.end());
	 }

	   string curString;
		while (!input1.empty())
		{	
			curString = input1.back();
			print_l(curString);			
			input1.pop_back();
			cout << endl;
		}
    vector<string>input;
    if ((dir = opendir (pathToDir.c_str())) != NULL)
    {
       // put files and directories into vector
       while ((ent = readdir (dir)) != NULL)
       {
          if((ent->d_name[0] != '.' || ent->d_name[1] != '.')&&(ent->d_name[0] != '.' || ent->d_name[1] != '\0'))
          {
				 string newPath = pathToDir + '/';
				 newPath += ent->d_name;
             input.push_back(newPath);
          }
       }
       //alpha sort
       sort(input.begin(),input.end(),NoCaseLess);
       reverse(input.begin(),input.end());
		 struct stat sb;
		 if (stat(pathToDir.c_str(), &sb) == -1) 
		 {
       	perror("stat");
        	exit(1);
       }

       while(!input.empty())
       {
			 if(isDirectory(input.back().c_str()))
          {
				 cout << endl;
				 cout << input.back() << ":" << endl;
             recurse_alList(input.back());
          }
          input.pop_back();
       }
   }
	return;
}
