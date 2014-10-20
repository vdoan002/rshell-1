#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <boost/tokenizer.hpp>
#include <string>
#include <string.h>
#include <vector>

using namespace std;
using namespace boost;

int main(int argc, char* argv[]) {

   int pid = fork();

   if(pid == -1)//fork’s return value for an error is -1
   {
      perror("There was an error with fork(). ");
      exit(1);//there was an error with fork
   }
   else if(pid == 0)//when pid is 0 you are in the child process
   {
		//variables
      string userInput;
      vector<string> inputVector;

		//prompt for user input
      cout << "$$ ";
		getline(cin, userInput);

		//Parse the input add store in vector
		typedef tokenizer< char_separator<char> > 
    		tokenizer;
  		char_separator<char> sep(" ");
 		tokenizer tokens(userInput, sep);

      //tokenizer<> tok(userInput);
      //for(tokenizer<>::iterator beg=tok.begin(); beg!=tok.end();++beg)
		for (tokenizer::iterator tok_iter = tokens.begin();
      		 tok_iter != tokens.end(); ++tok_iter)
      {
         inputVector.push_back(*tok_iter);
			//cout << *beg << "\n";         
      }

		/*Test to see whats in the vector
		while(inputVector.size()!= 0)
		{
			cout << inputVector.back() << endl;
			inputVector.pop_back();
		} 

		*/
		//start loading inputVector into argv...
		int count = 0;
		for (vector<string>::iterator it = inputVector.begin() ; it != inputVector.end(); ++it)
		{
			string s = *it;
			//check to see if || or && connector
			//if((s.at(0) == "|") || s.at(0) == "&")
			//{
				
			//}
			char *str = new char[s.length()+1];
			strcpy(str, s.c_str());
			argv[count] = str;
			++count;
		}
		argv[count] = NULL;	 
		  

      /*-------------------------------------------------
		string s = "ls";
		char *str = new char[3];
		strcpy(str,s.c_str());
		string x = "-a";
		char *str1 = new char[3];
		strcpy(str1,x.c_str());

		argv[0] = str;
		argv[1] = str1;
		argv[2] = NULL;
      if(-1 == execvp(argv[0], argv)) 
         perror("There was an error in execvp. ");

	
		//-------------------------------------------------
      */
	
      if(-1 == execvp(argv[0], argv)) 
         perror("There was an error in execvp. ");

      exit(1); 
   }
   //if pid is not 0 then we’re in the parent
   else if(pid > 0) //parent function
   {
      if( -1 == wait(0)) //wait for the child process to finish
     	 	perror("There was an error with wait().");
	
		cout << "This is the parent process! " << endl;
   }

}

