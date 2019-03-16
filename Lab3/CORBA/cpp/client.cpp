#include "example.hh"
#include <iostream>
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
		if (!CORBA::is_nil(service_server)) {
		//
		cout<<"Enter the number of questions that you want to create";
		string n;
		getline(cin,n);
		cin.ignore();
		int numberOfQuestions=atoi(n.c_str());
	//	cin>>numberOfQuestions;
		//cin.ignore(1000,'\n');
		for(int i=0;i<numberOfQuestions;i++){
			string Q;
			string A;
			cout<<"\nEnter a question";
			getline(cin,Q);
		cin.ignore();
			cout<<"\nEnter an answer";
			getline(cin,A);
			cin.ignore();
			service_server ->question_answer(Q.c_str(), A.c_str());

			//cout<<service_server ->question_answer(Q.c_str(),A.c_str())<<endl; //.c_str is used to turn a string into a *char
  
		}
			//
			char * server = service_server->send_message("Message from C++ (omniORB) client");
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