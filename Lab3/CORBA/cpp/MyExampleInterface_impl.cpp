#include "MyExampleInterface_impl.h"
#include <iostream>
#include <vector>
#include <string> 
using namespace std;

char * MyExampleInterface_impl::send_message(const char * message)
{
	cout << "C++ (omniORB) server what: " << message << endl; //shows in server 
	char * server = CORBA::string_alloc(1024);
	strncpy(server, "Message from C++ (omniORB) server what yes", 1024); //shows in client 
	return server;
}

void  MyExampleInterface_impl::question_answer(const char * question, const char * answer){
//	string str(question);
//	string str2(answer);
	questions.push_back(question);
	answers.push_back(answer);
	cout<< "Q"<<questions.size() + 1 <<":"<<questions.at(questions.size());
	cout<<"A:"<<answers.size()+1<<":"<<answers.at(answers.size());
	
}