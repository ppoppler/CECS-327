#include "example.hh"
#include <iostream>
#include <string>
#include <sstream>
#include <CORBA.h>
#include <Naming.hh>

/** Name is defined in the server.cpp */
#define SERVER_NAME		"MyServerName"

using namespace std;

int main(int argc, char ** argv)
{
	try {
		//------------------------------------------------------------------------
		// Initialize ORB object.
		//------------------------------------------------------------------------
		CORBA::ORB_ptr orb = CORBA::ORB_init(argc, argv);

		//------------------------------------------------------------------------
		// Resolve service
		//------------------------------------------------------------------------
		ExampleInterface_ptr service_server = 0;

		try {

			//------------------------------------------------------------------------
			// Bind ORB object to name service object.
			// (Reference to Name service root context.)
			//------------------------------------------------------------------------
			CORBA::Object_var ns_obj = orb->resolve_initial_references("NameService");

			if (!CORBA::is_nil(ns_obj)) {
				//------------------------------------------------------------------------
				// Bind ORB object to name service object.
				// (Reference to Name service root context.)
				//------------------------------------------------------------------------
				CosNaming::NamingContext_ptr nc = CosNaming::NamingContext::_narrow(ns_obj);
				
				//------------------------------------------------------------------------
				// The "name text" put forth by CORBA server in name service.
				// This same name ("MyServerName") is used by the CORBA server when
				// binding to the name server (CosNaming::Name).
				//------------------------------------------------------------------------
				CosNaming::Name name;
				name.length(1);
				name[0].id = CORBA::string_dup(SERVER_NAME);
				name[0].kind = CORBA::string_dup("");

				//------------------------------------------------------------------------
				// Resolve "name text" identifier to an object reference.
				//------------------------------------------------------------------------
				CORBA::Object_ptr obj = nc->resolve(name);

				if (!CORBA::is_nil(obj)) {
					service_server = ExampleInterface::_narrow(obj);
				}
			}
		} catch (CosNaming::NamingContext::NotFound &) {
			cerr << "Caught corba not found" << endl;
		} catch (CosNaming::NamingContext::InvalidName &) {
			cerr << "Caught corba invalid name" << endl;
		} catch (CosNaming::NamingContext::CannotProceed &) {
			cerr << "Caught corba cannot proceed" << endl;
		}

		//------------------------------------------------------------------------
		// Do stuff
		//------------------------------------------------------------------------
		int numberOfQuestions;
		if (!CORBA::is_nil(service_server)) {
		//
		cout<<"Enter the number of questions that you want to create"<<endl;
		string n;
		getline(cin,n);
	//	cin.ignore();
		
		 numberOfQuestions = stoi(n);
		
		//int numberOfQuestions=atoi(n.c_str());
	//	cin>>numberOfQuestions;
		//cin.ignore(1000,'\n');
		for(int i=0;i<numberOfQuestions;i++){
			string Q;
			string A;
			cout<<"\nEnter a question"<<endl;
			getline(cin,Q);
		//cin.ignore();
			cout<<"\nEnter an answer"<<endl;
			getline(cin,A);
		//	cin.ignore();
		//	service_server ->question_answer(Q.c_str(), A.c_str());
			service_server ->question_answer(Q.c_str(), A.c_str());
		// service_server ->question_answer(Q, A);
			//cout<<service_server ->question_answer(Q.c_str(),A.c_str())<<endl; //.c_str is used to turn a string into a *char
  
		}
		cout<<"\nWe have now finished creating "<<numberOfQuestions<<" questions for the game "<<endl;
		bool keepGoing = true;
		int questionPool =numberOfQuestions;
		while(keepGoing){
			cout<<"Please choose one of the menu items"<<endl;
			cout<<"1. Get random question and try to answer it "<<endl;
			cout<<"2. Remove a question by entering a number between one and the number of questions that you created"<<endl;
			cout<<"3. Exit the program"<<endl;
			string userChoice;
			getline(cin,userChoice);
			int choiceInt =stoi(userChoice);
			//cin>>choiceInt;
			//cin.ignore();
			
			switch(choiceInt){
				case 1:{
						
						char * serverQuestion = service_server->getRandomQuestion();
						string theQuestion(serverQuestion);
						cout<<"The question from the server is: "+theQuestion<<endl;
						cout<<"Please enter your answer"<<endl;
						string clientAnswer;
						getline(cin,clientAnswer);
						char * correctOrNot = service_server -> answerQuestion(clientAnswer.c_str());
						cout<<"The server said: "<<correctOrNot<<endl;
				break;
				}
				case 2:
				{
						cout<<"Please enter a number between 1 and the number of questions that you created ("<<questionPool<<")"<<endl;
						//cout<<"Remove a question by entering an int that is between 1 and "<< service_server->questions.size()<<endl;
						string removeIndex;
						getline(cin,removeIndex);
						cout<<"Question number "<<removeIndex<<" has now been removed"<<endl;
					//	int questionIndex = stoi(removeIndex);
				//	String serverConfirmation;
						questionPool--;
						char * serverConfirmation= service_server->removeQuestion(removeIndex.c_str());						
				break;
				}
				case 3:
				{
				cout<<"Exiting the program"<<endl;
				keepGoing = false;
				break;
				}
				default: {
					cout<<"error"<<endl;
				break;
				}
			}
		}
			//
		//	char * server = service_server->send_message("Message from C++ (omniORB) client");
			char * server = service_server->send_message("Client: Thanks for letting me play the game!");
			cout << "response from Server: " << server << endl;
			CORBA::string_free(server);
		}

		//------------------------------------------------------------------------
		// Destroy OBR
   		//------------------------------------------------------------------------
		orb->destroy();

	} catch (CORBA::UNKNOWN) {
		cerr << "Caught CORBA exception: unknown exception" << endl;
	}
}