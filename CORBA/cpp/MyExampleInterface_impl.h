#ifndef __MY_EXAMPLE_INTERFACE_IMPL_H__
#define __MY_EXAMPLE_INTERFACE_IMPL_H__

#include "example.hh"
#include <vector>
#include <string> 
#include <stdlib.h>
#include <time.h>
using namespace std;
class MyExampleInterface_impl : public POA_ExampleInterface
{
	public:
		vector <string> questions; //vectors to store the questions and answers 
		vector <string> answers;	
		 char * trackQuestion; //used for tracking the question that the user is going to answer 
		virtual char * send_message(const char * message);
		virtual void question_answer(const char * question, const char * answer); //creates a question and answer 
		virtual char * getRandomQuestion(); //returns a random question 
		virtual char * answerQuestion(const char * clientAnswer); //checks to see if the client got the right answer 
		virtual char * removeQuestion(const char * theIndex); //removes the question at the index number the client specifies
};




#endif // __MY_EXAMPLE_INTERFACE_IMPL_H__
