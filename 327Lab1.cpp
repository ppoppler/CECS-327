/**
 @author Rayhaan Shaikh
 @author Philip Poppler
 CECS 327
 Assignment 1
 Purpose: To demonstrate our knowledge of threads, pointers, and C++.
 */
#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <unistd.h> //important includes that will be used in our program
#include <string.h>

using namespace std;

 #include "../Utilities/Utils.h"


int firstMatrix[3][3];
int secondMatrix[3][3]; //declaring our 3x3 matrices 
int finalMatrix[3][3];
const int MAT_ELEMENTS = 9; //9 elements in our matrix because it is 3x3
#define NUM_THREADS 9
struct mat_args //struct that contains two int variables for row and col
 {
	int row;
	int col;
};
/**
 * A function that multiplies the two matrices respective rows and columns and creates a third matrix with the resulting calculations
 * It also deltes our structure and calls pthread exit 
 */
void *matrix_mult(void* arguments) {

	struct mat_args *args = (mat_args*)arguments; // assign a struct pointer equal to the arguments passed to the function 
	int row = (*args).row; //store the row information into the local integer row variable 
	int col = (*args).col; //stor the col info into the local integer col variable 
	for (int k = 0; k < 3; k++) {
		finalMatrix[row][col] += firstMatrix[row][k] * secondMatrix[k][col];
		//multiply the two cells and add that result to index [i][j] of our new matrix
	}
	delete args; //delete is used to delete the memory allocated to our mat_args structure 
	pthread_exit(NULL); //used to terminate the thread 

}

int main(int argc, char *argv[]) {


string inFileName1 = "";
  string inFileName2 = "";
  ofstream outStream;

  string element = "";
 
  Utils::CheckArgs(2, argc, argv, "infilename (first matrix) outfilename (second matrix)");
  inFileName1 = static_cast<string>(argv[1]);
  inFileName2 = static_cast<string>(argv[2]);


  ifstream fin(inFileName1);
  ifstream fin2(inFileName2);  
  
  for(int i=0;i<3;i++){
	  for(int j=0;j<3;j++){
		  fin >> firstMatrix[i][j];
		  fin2 >> secondMatrix[i][j];
	  }
  }

// ifstream fin("../Project1/inputA1.in");

// for(int i =0;i<3;i++){
// 	for(int j =0;j<3;j++){
// 		fin >> firstMatrix[i][j];
// 	}
// }
// ifstream fin2("../Project1/inputA2.in");
// for(int i =0;i<3;i++){
// 	for(int j =0;j<3;j++){
// 		fin2 >> secondMatrix[i][j];
// 	}
// }
	// for (int i = 0; i < 3; i++) {
	// 	for (int j = 0; j < 3; j++) {
	// 		firstMatrix[i][j] = rand() % 10; //for test purposes, populating the two matrices with random numbers 
	// 		secondMatrix[i][j] = rand() % 10;
	// 	}
	// }

	pthread_t threads[NUM_THREADS];//9 threads, one thread per result from multiplying 1st and 2nd matrix 

	 int trackThreads=0; //counter for our number of threads 
	for (int i = 0; i < 3; i++) { //row
		for(int j=0;j<3;j++){ //column 
			mat_args* matStruct = new mat_args(); //declare our struct and make it a pointer 
			(*matStruct).row  = i; //make the row variable equal to i so it can be equal to the row we are currently on 
			(*matStruct).col = j; //make the col variable equal to j so it can be equal to the col we are currently on 
			int holdThread=pthread_create(&threads[trackThreads],NULL,matrix_mult,(void*)matStruct); //creating a thread for the calculatation of a cell in the new matrix 
			if(holdThread){
				cout<<"There was a problem with trying to create a thread "<<holdThread<<endl; //print out error message 
				exit(1);//the program exited with a failure 
			}
			trackThreads++;//increase this variable to use for making the next thread
		}

	}

	for (int i = 0; i < MAT_ELEMENTS; i++) {
		int holdJoin = pthread_join(threads[i], NULL);//used in order to wait for the threads to terminate 
		if(holdJoin){
			cout<<"There was a problem with trying to join "<<holdJoin<<endl; //print out error message 
			exit(1); //the program exited with a failure 
		}
	}
	/*
	code for reading a text file once he gives us a sample input file
	ifstream file(input.txt);
	string readIt;
	string fileInfo;
	while(getline(file,readIt)){
		fileInfo+=readIt;
		fileInfo.push_back('\n');   //source : https://stackoverflow.com/questions/13035674/how-to-read-line-by-line-or-a-whole-text-file-at-once
	}
	*/



	cout << "First matrix" << endl; //printing out the first matrix 
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << firstMatrix[i][j] << " "; //print out the contents of the first matrix that we populated 
			if (j == 2) {
				cout << endl; // if we have reached the end of the row, start a new line to print the next row on
			}
		}
	}
	cout << endl; //blank line to make first and second matrix more spaced out to each other to make it easier to read 
	cout << "Second matrix" << endl; //printing out the second matrix 
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << secondMatrix[i][j] << " ";
			if (j == 2) { //if it's the end of the row, start a new line for the next row 
				cout << endl;
			}
		}
	}

	cout<<"The result of the third matrix is:"<<endl;
	 for(int i=0;i<3;i++){
	     for(int j=0;j<3;j++){
	         cout<<finalMatrix[i][j]<<" "; //print out the result of the two matrices that were multiplied 
	         if(j==2){ //used to format the matrix to print only three numbers per row 
	             cout<<endl;
			 }
		 }
	 }

	return 0;
}

