#include "MyExampleInterface_impl.h"
#include <iostream>
#include <vector>
#include <string> 
#include <stdlib.h>
#include <time.h>
using namespace std;

char * MyExampleInterface_impl::send_message(const char * message)
{
	cout << "C++ (omniORB) server : " << message << endl; //shows in server 
	char * server = CORBA::string_alloc(1024);
//	strncpy(server, "Message from C++ (omniORB) server:", 1024); //shows in client 
	strncpy(server, "Message from C++ (omniORB) server: you are welcome, the game is over now", 1024); 
	return server;
}

void  MyExampleInterface_impl::question_answer(const char* question, const char* answer){
//	string str(question);
//	string str2(answer);
	questions.push_back(question);
	answers.push_back(answer);
	cout<< "Q:"<<questions.size() <<":"<<questions.back()<<endl;
	cout<<"A:"<<answers.size()<<":"<<answers.back()<<endl;
	
}

char * MyExampleInterface_impl::getRandomQuestion(){
	srand(time(NULL));
	int RandomNum = rand() % questions.size();
	string s = to_string(RandomNum);
	trackQuestion = CORBA::string_alloc(1024);
	strncpy(trackQuestion,s.c_str(),1024);
	char * result = CORBA::string_alloc(1024);
     //char * result = (questions.at(RandomNum)).c_str();
	 strncpy(result,(questions.at(RandomNum)).c_str(),1024);
	return result;
}

char * MyExampleInterface_impl::answerQuestion(const char * clientResponse){
int answerIndex =atoi(trackQuestion);
string clientAns(clientResponse);
char * serverResponse= CORBA::string_alloc(1024);
if(!answers.at(answerIndex).compare(clientAns)){	
	strncpy(serverResponse,"Your answer is correct! Congratulations!",1024);
	return serverResponse;
}
else{
strncpy(serverResponse,"Your answer was incorrect!",1024);
return serverResponse;
}

}
char * MyExampleInterface_impl::removeQuestion(const char* theIndex){

int i = atoi(theIndex);
i--; //indexes of a vector start at 0, if they were to enter 1 for question 1, we need to go to index 0 in the vector 
questions.erase(questions.begin()+i);
answers.erase(answers.begin()+i);

char *confirmation = CORBA::string_alloc(1024);
strncpy(confirmation,"The question has been removed",1024);
return confirmation;
}