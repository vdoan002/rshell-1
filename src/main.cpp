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

string getInput();
vector<string> parse(string userInput);
void printVectorBackwards(vector<string> a);
vector<char*> parseArg(vector<string> inputVector);
void execute(string str);

int main(int argc, char* argv[]) {

		//get user input
		string userInput = getInput();
		if(userInput == "exit")
		{
			exit(1);
		}
		//returns a tokenized vector and gets rid of the comments if any
		vector<string> inputVector = parse(userInput);	

		//make sure vector has the right content
		//printVectorBackwards(inputVector);
		//vector<char*> argVect;
   	//argVect = parseArg(inputVector);
		//pwd || cd ; ls
		string str;
		int count = 0;
		bool found = false;
		for (vector<string>::iterator it = inputVector.begin() ; it != inputVector.end(); ++it)
 		{
			//found connector
			if(*it == "&&" || *it == ";")
			{
				execute(str);
				found = true;
				str="";
				++it;
				//cout << "hi";
			}
 			str += *it;
			str += " ";
    	}
		if(found == false)
		{
			//cout << "hey";
			execute(str);
		}
	main(argc, argv);
	return 0;
}

string getInput(){

	//variables
   string input;
	string modInput;
	int hashPos = -1;
	int hashCount = 0;
	vector<int> colonVector;

	//prompt for user input
   cout << "$ ";
	getline(cin, input);

	bool hash = false;
	//put space before semi-colons and get rid of #
	for(int i = 0; i < input.length(); ++i)
	{
		if(input.at(i) == ';' && hash == false)
		{
			colonVector.push_back(i);
		}
		if(input.at(i) == '#')
		{
			hashPos = i;
			hash = true;
		}
		if(hash == true)
		{
			++hashCount;
		}
	}

	if(hashPos >= 0)
	{
		input.erase(hashPos, hashCount);
	}
	//set modInput read to modify
	modInput = input;
	int pos = 0;
	while(!colonVector.empty())
	{
		pos = colonVector.back();
		modInput.insert(pos," ");
		colonVector.pop_back();
	}

	//convert back
	input = modInput;
	return input;
}

vector<string> parse(string userInput){
	
	//variables
	vector<string> inputVector;

	//Parse the input add store in vector
	typedef tokenizer< char_separator<char> > 
    	tokenizer;
  	char_separator<char> sep(" ");
 	tokenizer tokens(userInput, sep);

	for (tokenizer::iterator tok_iter = tokens.begin();
          tok_iter != tokens.end(); ++tok_iter)
   {
      inputVector.push_back(*tok_iter);       
   }
	return inputVector;
}

void printVectorBackwards(vector<string> a){
	//Test to see whats in the vector
	while(a.size()!= 0)
	{
		cout << a.back() << endl;
		a.pop_back();
	} 
}

vector<char*> parseArg(vector<string> inputVector){
	int count = 0;
	vector<char*>argVect;
	//start loading inputVector into argv type array 
	for (vector<string>::iterator it = inputVector.begin() ; it != inputVector.end(); ++it)
	{
		string s = *it;
		char *str = new char[s.length()+1];
		strcpy(str, s.c_str());
		argVect.push_back(str);
	}
	argVect.push_back(NULL);
	return argVect;	 
}

void execute(string str){
	//cout << str;
	//get the argument vector
	char* argv[100];
	vector<string> a = parse(str);
	vector<char*> b = parseArg(a);
	int count = 0;
	for (vector<char*>::iterator it = b.begin() ; it != b.end(); ++it)
	{
		argv[count] = *it;
		count ++;
	}

	int pid = fork();
   if(pid == -1)//fork’s return value for an error is -1
   {
      perror("There was an error with fork(). ");
      exit(1);//there was an error with fork
   }
   else if(pid == 0)//when pid is 0 you are in the child process
   {
		if(-1 == execvp(argv[0], argv)) 
		{
         perror("There was an error in execvp. ");
      	exit(1); 
   	}
	}
	//if pid is not 0 then we’re in the parent
   else if(pid > 0) //parent function
   {
      if( -1 == wait(0)) //wait for the child process to finish
     	 	perror("There was an error with wait().");
	//	cout << "This is the parent process! " << endl;
		return;
   }

}

