#include "example.hh"
#include <iostream>
#include <string>
#include <sstream>
#include <CORBA.h>
#include <Naming.hh>

/**
 * Rayhaan Shaikh
 * Philip Poppler 
 * A program that uses corba and a client server architecture to develop a quiz game 
 * /
/** Name is defined in the server.cpp */
#define SERVER_NAME		"MyServerName"

using namespace std;
/**
 * A function to check if a string can be converted to an int
 * */
bool is_number(string s){
	if(s.size() ==0) return false;
	for(int i=0;i<s.size();i++){ //loop until we have reached the end of the string 
		if((s[i]>='0' && s[i]<='9') == false){ //check if the index is a digit 
			return false;
		}
	}
	return true;
}
/**
 * Main method where the menu will be presented and the client will send and recive data 
 * */
int main(int argc, char ** argv)
{
	try {
		//------------------------------------------------------------------------
		// Initialize ORB object.
		//------------------------------------------------------------------------
		CORBA::ORB_ptr orb = CORBA::ORB_init(argc, argv); //this is how the ORB object is initialized 

		//------------------------------------------------------------------------
		// Resolve service
		//------------------------------------------------------------------------
		ExampleInterface_ptr service_server = 0; //the service_server will be used to interact with the interface

		try {

			//------------------------------------------------------------------------
			// Bind ORB object to name service object.
			// (Reference to Name service root context.)
			//------------------------------------------------------------------------
			CORBA::Object_var ns_obj = orb->resolve_initial_references("NameService"); //binding the ORB object to our name service object 

			if (!CORBA::is_nil(ns_obj)) { //is nil is used to see if an object exists for that specific object type.
			//it returns true if the object reference contains the special value for a nil object referene as defined by the ORB.
				//------------------------------------------------------------------------
				// Bind ORB object to name service object.
				// (Reference to Name service root context.)
				//------------------------------------------------------------------------
				CosNaming::NamingContext_ptr nc = CosNaming::NamingContext::_narrow(ns_obj); //binding orb object to the name servie object 
				
				//------------------------------------------------------------------------
				// The "name text" put forth by CORBA server in name service.
				// This same name ("MyServerName") is used by the CORBA server when
				// binding to the name server (CosNaming::Name).
				//------------------------------------------------------------------------
				CosNaming::Name name; //used for binding purposes 
				name.length(1);
				name[0].id = CORBA::string_dup(SERVER_NAME);
				name[0].kind = CORBA::string_dup("");

				//------------------------------------------------------------------------
				// Resolve "name text" identifier to an object reference.
				//------------------------------------------------------------------------
				CORBA::Object_ptr obj = nc->resolve(name);

				if (!CORBA::is_nil(obj)) { //is nil returns a nil object reference, it is used to see if an object exists for that specific object type
					service_server = ExampleInterface::_narrow(obj);
				}
			}
		} catch (CosNaming::NamingContext::NotFound &) {
			cerr << "Caught corba not found" << endl; //if we can't find the name
		} catch (CosNaming::NamingContext::InvalidName &) {
			cerr << "Caught corba invalid name" << endl; //if the name is not valid 
		} catch (CosNaming::NamingContext::CannotProceed &) {
			cerr << "Caught corba cannot proceed" << endl; //unable to proceed 
		}

		//------------------------------------------------------------------------
		// Do stuff
		//------------------------------------------------------------------------
		int numberOfQuestions;
		if (!CORBA::is_nil(service_server)) { //returns a nil object reference 
		//
		string n;	
		cout<<"Enter the number of questions that you want to create"<<endl; //add error checking if they do not enter an int 
		getline(cin,n); //get the user input 
		bool check = is_number(n); //see if it is a number 
		while(check == false){ //while it is not a number 
	 check = is_number(n);	//check if it is a number 
	if(check == false){ //if is not a number 
		n.clear();//clear the string 
		cout<<"input needs to be a number, and it needs to be a positive number, please try again by entering a positive number"<<endl;
		getline(cin,n); //get user input 
	}
		}	
	int numberOfQuestions = stoi(n); //we now know that the string can be converted to an int 
	
		for(int i=0;i<numberOfQuestions;i++){//loop up to n times 
			string Q;
			string A;
			cout<<"\nEnter a question"<<endl;
			getline(cin,Q); //user input for question
		
			cout<<"\nEnter an answer"<<endl;
			getline(cin,A); //user input for answer 

			service_server ->question_answer(Q.c_str(), A.c_str());	//send the question and answer to he interface so it can store the information into the vectors 
		}
		cout<<"\nWe have now finished creating "<<numberOfQuestions<<" questions for the game "<<endl;
		bool keepGoing = true; //used for looping our menu 
		int questionPool =numberOfQuestions; //used to keep track of the number of questions that are in the game 
		while(keepGoing){
			cout<<"Please choose one of the menu items"<<endl;
			cout<<"1. Ask me a question"<<endl;
			cout<<"2. Remove a question by entering a number between one and the number of questions that you created"<<endl;
			cout<<"3. Exit the program"<<endl;
			string userChoice;
			getline(cin,userChoice); //get user choice to execute the feature that they want to run 
			bool check1 = is_number(userChoice); //check if they entered a number 
			while(check1 == false){ //while it is not a number 
	 		check1 = is_number(userChoice);	
			if(check1 == false){ //if it is not a number 
			userChoice.clear();
			cout<<"input needs to be a number, and that number needs to be within the range, please try again by entering a number"<<endl;
			cout<<"Please choose one of the menu items"<<endl;
			cout<<"1. Ask me a question "<<endl;
			cout<<"2. Remove a question by entering a number between one and the number of questions that you created"<<endl;
			cout<<"3. Exit the program"<<endl;
			getline(cin,userChoice); //get user input for the menu 
	}	
		}
			int choiceInt =stoi(userChoice);//convert the user input string to an int to use it for our switch statement 
		
			switch(choiceInt){
				case 1:{ //the user wants to get a random question and answer it 
						
						char * serverQuestion = service_server->getRandomQuestion(); //store the returned question into our char* variable 
						string theQuestion(serverQuestion);
						if(!theQuestion.compare("Error, there are no more questions left")){ //see if an error message was returned saying that no more questions are left 
							cout<<"The server said: "<<theQuestion<<endl;
							break;
						}
						cout<<"The question from the server is: "<<theQuestion<<endl; //print out the question from the question vector 
						cout<<"Please enter your answer"<<endl;
						string clientAnswer;
						getline(cin,clientAnswer); //get the clients answer to the question 
						char * correctOrNot = service_server -> answerQuestion(clientAnswer.c_str()); //send the client answer to the interface and store the result if it was correct or not 
						cout<<"The server said: "<<correctOrNot<<endl; //print out if the client was correct or not 
				break;
				}
				case 2:
				{
					if(questionPool ==0){ //if there are no more questions left 
						cout<<"There are no more questions left in the game"<<endl;
						break;
					}
					int holdPool = questionPool; //used to hold number of questions that are left 
						cout<<"Please enter a number between 1 and the number of questions that you created ("<<questionPool<<")"<<endl;
						
						string removeIndex;
						getline(cin,removeIndex); //get user input for which question they want to remove 
						bool check2 = is_number(removeIndex); //check if it is a number 
						if(check2 ==true ){ //if it is a number we now need to check if it is in range 
							int inRange = stoi(removeIndex);
							while(inRange<1 || inRange>holdPool){ //while it is not in range 
								removeIndex.clear(); //clear the string 
								cout<<"Please enter a number between 1 and the number of questions that you created ("<<questionPool<<")"<<endl; //print out 1 to how many questions are in the vector 
					
						getline(cin,removeIndex); //get the input for the index they want to remove 
						check2 = is_number(removeIndex); //see if it is a number 
						if(check2){ //if it is then run this next line of code 
							inRange=stoi(removeIndex); //convert it to an int, if the int is out of bounds the while loop will reloop the user input again
						}
							}
						}
						while(check2 == false ){ //if the input is not a number 
	 					check2 = is_number(removeIndex);	//used to see if it is a number
						if(check2 == false){ //if it is not a number 
						removeIndex.clear(); //clear the string 
						cout<<"input needs to be a number, and that number needs to be within the range, please try again by entering a number"<<endl;
						getline(cin,removeIndex); //get the input of the index they want to remove 
						}
						else if(check2 == true ){ //if it is a number 
						int x = stoi(removeIndex);	//store it in int variable 	
		 				if(x<1 || x>holdPool){ //check if the number is within the bounds 
						cout<<"That number is out of the range, please enter a number that is within the range"<<endl;			
						check2=false; //if it is out of bounds set it to false so we can reloop 
						removeIndex.clear(); //clear the string 
						getline(cin,removeIndex); //get user input 
						}
						}
	
						}
						cout<<"Question number "<<removeIndex<<" has now been removed"<<endl;//print out that the question at that index has been removed 			
						questionPool--; //reduce the number of questions that are int he question pool now 
						char * serverConfirmation= service_server->removeQuestion(removeIndex.c_str());	//remove the question at that specified index 					
				break;
				}
				case 3:
				{
				cout<<"Exiting the program"<<endl; //exit the program 
				keepGoing = false; //set the boolean to false to break out of while loop 
				break;
				}
				default: {
					cout<<"Error, please enter a number that is shown on the menu"<<endl; //default case if they enter an input that is not one of the options listed 
				break;
				}
			}
		}
			//
		//	char * server = service_server->send_message("Message from C++ (omniORB) client");
			char * server = service_server->send_message("Message from C++ (omniORB) client: Thanks for letting me play the game!");
			cout << "response from Server: " << server << endl;
			CORBA::string_free(server); //frees the memory that is allocated to this string 
			for(int i =1;i<=questionPool;i++){
				string s = to_string(i);
				char*removeIt = service_server ->removeQuestion(s.c_str()); //clearing the vectors once the client is done so if a new client starts the old questions won't be there anymore
			}
		}

		//------------------------------------------------------------------------
		// Destroy OBR
   		//------------------------------------------------------------------------
		orb->destroy();

	} catch (CORBA::UNKNOWN) { //catch an unknown exception 
		cerr << "Caught CORBA exception: unknown exception" << endl;
	}
}
