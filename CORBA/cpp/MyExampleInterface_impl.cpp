#include "MyExampleInterface_impl.h"
#include <iostream>
#include <vector>
#include <string> 
#include <stdlib.h>
#include <time.h>
using namespace std;

/**
 * A function for sending a message to the server and to return a message back to the client
 * */
char * MyExampleInterface_impl::send_message(const char * message)
{
	cout << "C++ (omniORB) server : " << message << endl; //shows in server 
	char * server = CORBA::string_alloc(1024);
//	strncpy(server, "Message from C++ (omniORB) server:", 1024); //shows in client 
	strncpy(server, "Message from C++ (omniORB) server: The game is over now", 1024); 
	return server;
}
/**
 * Stores the question and answer into their respective vectors 
 * */
void  MyExampleInterface_impl::question_answer(const char* question, const char* answer){

	questions.push_back(question); //push the question into the question vector 
	answers.push_back(answer); //push the answer into the answer vector 
	cout<< "Q:"<<questions.size() <<":"<<questions.back()<<endl; //print out the question information 
	cout<<"A:"<<answers.size()<<":"<<answers.back()<<endl; //print out the answer along with what number answer it is 
	
}
/**
 * Get a rnadom question from the server and return the question to the client
 * */
char * MyExampleInterface_impl::getRandomQuestion(){
	if(questions.size()==0){ //if there are no question 
		char *msg =CORBA::string_alloc(1024);
	strncpy(msg, "Error, there are no more questions left", 1024); //return an error message 
		return msg;
	}
	srand(time(NULL)); //ensure random seed 
	int RandomNum = rand() % questions.size(); //get a random number that is within the range of the vector size 
	string s = to_string(RandomNum); //turn the random number to a string 
	trackQuestion = CORBA::string_alloc(1024); 
	strncpy(trackQuestion,s.c_str(),1024); //transfer the index number of the question into our variable for later use 
	char * result = CORBA::string_alloc(1024);
     //char * result = (questions.at(RandomNum)).c_str();
	 strncpy(result,(questions.at(RandomNum)).c_str(),1024); //put the question into our char* result variable and return it to the client 
	return result;
}
/**
 * Function to determine if the clients answer is the correct answer to the question 
 * */
char * MyExampleInterface_impl::answerQuestion(const char * clientResponse){
int answerIndex =atoi(trackQuestion); //convert the index number of the random question to an int 
string clientAns(clientResponse);//convert the clientResponse into a string 
char * serverResponse= CORBA::string_alloc(1024);
if(!answers.at(answerIndex).compare(clientAns)){	 //if the clients response matches the answer 
	strncpy(serverResponse,"Your answer is correct! Congratulations!",1024);
	return serverResponse; //return the output that they are correct 
}
else{
strncpy(serverResponse,"Your answer was incorrect!",1024);
return serverResponse; //otherwise tell them that they were wrong 
}

}
/**
 * Remove a question at the question number specified by the user 
 * */
char * MyExampleInterface_impl::removeQuestion(const char* theIndex){ //add error handling to check if they entered an string instead of int

int i = atoi(theIndex); //store client request into int variable 
i--; //indexes of a vector start at 0, if they were to enter 1 for question 1, we need to go to index 0 in the vector 
questions.erase(questions.begin()+i);//remove that index from the question vector 
answers.erase(answers.begin()+i); //remove that index from the answer vector 

char *confirmation = CORBA::string_alloc(1024);
strncpy(confirmation,"The question has been removed",1024);
return confirmation; //return a confirmation that the question has been removed 
}