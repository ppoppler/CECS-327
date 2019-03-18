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
		vector <string> questions;
		vector <string> answers;
		//static short trackQuestion;
		 char * trackQuestion;
		virtual char * send_message(const char * message);
		//
		virtual void question_answer(const char * question, const char * answer);
		virtual char * getRandomQuestion();
		virtual char * answerQuestion(const char * clientAnswer);
		virtual char * removeQuestion(const char * theIndex);
};




#endif // __MY_EXAMPLE_INTERFACE_IMPL_H__
