/*
 * records.cpp
 *
 *  Created on: 10 Mar 2014
 *  Author: James Feli
 *  studentNumber: FLXJAM001
 *
 */


#include <iostream>
#include <fstream>
#include <sstream>
#include "records.h"
#include <string>
#include <list>
#include <vector>

namespace flxjam001 {
	//Constructor for studentRecords that takes in the necessary records
	StudentRecord::StudentRecord(std::string newName, std::string newSurname, std::string newStudentNumber, std::string newClassRecord){
		name = newName; 
		surname = newSurname, 
		studentNumber = newStudentNumber; 
		classRecord = newClassRecord;
	}

	//Constructor for Database class that takes fileName as argument
	Database::Database (std::string fileName){
		//convert filename to char since open file takes char argument
		const char* databaseFile = fileName.c_str();
		std::ifstream inputFile;
		inputFile.open(databaseFile);  //takes in char argument
		std::string line;    //stores lines from the file

		//Initially extracting the data in the file into a list before executing further database functions
		while(std::getline(inputFile,line)){


			int pos = line.find("|");  //since records are seperated by "|" then seperate records by "|"


			std::vector<std::string> tokens; //stores the individual records of a student

			//the below code does the job of seperating the records and pushing them into the vector tokens
			int startPos = 0;

			std::string data = line.substr(startPos, pos);
			tokens.push_back(data);
			line = line.substr(pos+1);


			pos = line.find("|");
			data = line.substr(startPos,pos);
			tokens.push_back(data);
			line = line.substr(pos+1);


			pos = line.find("|");
			data = line.substr(startPos,pos);
			tokens.push_back(data);
			line = line.substr(pos+1);


			data = line;  //pushing the last record which is classRecords
			tokens.push_back(data);

			//create a student obje to push into a list
			StudentRecord student(tokens[0],tokens[1],tokens[2],tokens[3]);

			studentList.push_back(student);
		}
		inputFile.close(); //close file

	}

	//Method that adds student to the database and checks for same student Numbers to modify
	void Database::addStudent(StudentRecord newStudent){

		std::list<StudentRecord>::iterator it1 = studentList.begin(); //iterator into the list
		StudentRecord stud = *it1;

		while(it1!=studentList.end()){
			//checking for similar student numbers and modify the existing one
			if (((newStudent.studentNumber).compare(stud.studentNumber))==0){
				studentList.erase(it1);
				studentList.push_back(newStudent);
				return;
					}
			it1++;
			if(it1!=studentList.end()) //making sure the iterator doesn't point outside the list
				stud = *it1;  //capturing the actual student object

		}
		studentList.push_back(newStudent);  //pushing into the list

	}


	//Method to delete students from list
	void Database::deleteStudent(std::string studNumber){
		//Check if list is empty
		if(studentList.empty())
		{
			std::cout<<"Database is empty!!";
			return;
		}

		//otherwise proceed with deletion by using iterators to find the student to be deleted by studentNumber
		std::list<StudentRecord>::iterator it1 = studentList.begin();
		StudentRecord stud = *it1;

		while(it1!=studentList.end()){

			if ((studNumber.compare(stud.studentNumber))==0){
				studentList.erase(it1);std::cout<<"deleted";
				break;
			}
			it1++;
			if(it1!=studentList.end())
				stud = *it1;
		}

	}

	//Method to read the database
	void Database::readDatabase(){
		//If database list is not empyt implying database not empty then output records
		if(!studentList.empty()){
			std::cout<<"Database records are:\n\n";
			std::list<StudentRecord>::iterator it1 = studentList.begin();
			StudentRecord stud = *it1;
			while(it1!=studentList.end()){
				std::string line = stud.name+ "|"+stud.surname+"|"+stud.studentNumber+"|"+stud.classRecord;
				std::cout<<line<<"\n";
				it1++;
				if(it1!=studentList.end())
					stud = *it1;
			}
		}else{
			//otherwise Database is empty
			std::cout<<"Database is empty";
		}

	}

	//method to save the Database to the passed fileName
	void Database::saveDatabase(std::string fileName){
		//converts the string filename to char type
		const char* databaseFile = fileName.c_str();
		std::ofstream outputFile;
		outputFile.open(databaseFile); //open file

		//iterate through list to save each record by seperation of | for each record
		std::list<StudentRecord>::iterator it1 = studentList.begin();
		StudentRecord stud = *it1;
		while(it1!=studentList.end()){

			std::string line = stud.name+ "|"+stud.surname+"|"+stud.studentNumber+"|"+stud.classRecord;
			outputFile<<line<<"\n";
			it1++;
			if(it1!=studentList.end())
				stud = *it1;
		}
		outputFile.close(); //close file

	}

	//Method to display single student record baased on the student Number
	void Database::displayStudent(std::string studentNumber){
		//If initially list is empty don't display
		if(studentList.empty()){
			std::cout<<"Database is empty";
			return;
		}

		std::list<StudentRecord>::iterator it1 = studentList.begin();
		StudentRecord stud = *it1;
		while(it1!=studentList.end()){
			if ((stud.studentNumber.compare(studentNumber))==0){
				std::cout<<stud.name<<" | "<<stud.surname<<" | "<<stud.studentNumber<<" | " <<stud.classRecord;
			}
			it1++;
			if(it1!=studentList.end())
				stud = *it1;
		}

	}

	//method to grade student
	void Database::gradeStudent(std::string studentNumber){
		//Initially check if database is empty
		if (studentList.empty()){
			std::cout<<"Database is empty!!";
			return;
		}

		//Find student and grade student
		std::list<StudentRecord>::iterator it1 = studentList.begin();
		StudentRecord stud = *it1;
		while(it1!=studentList.end()){
			if ((stud.studentNumber.compare(studentNumber))==0){

				std::istringstream iss(stud.classRecord);
				int count=0;
				float total = 0;
				float average = 0;
				while(!iss.eof()){
					std::string s;
					iss>>s>>std::ws;
					int num;
					std::istringstream(s)>>num;
					count=count +1;
					total = total + num;
			}
			average = total/count;

			std::cout<<"Grade: "<<average<<"\n"; //ouput student grade
			}
			it1++;
			if(it1!=studentList.end())
				stud = *it1;
		}
	}

	//method to display all students with their grades
	void Database::displayDatabase(){
		if (studentList.empty()){
			std::cout<<"Da//processing the classRecords into tabase is empty!!";
			return;
		}
		std::list<StudentRecord>::iterator it1 = studentList.begin();
		StudentRecord stud = *it1;
		while(it1!=studentList.end()){

			std::cout<<stud.name<<" | "<<stud.surname<<" | "<<stud.studentNumber<<" | " <<stud.classRecord;

			it1++;
			if(it1!=studentList.end())
				stud = *it1;
		}

	}
	
	void Database::winningStudent(){
		float grade = 0;
		std::string stNo ="";
			
		if (studentList.empty()){
			std::cout<<"Database is empty!!";
			return;
		}
		
		else{
			
			
		std::list<StudentRecord>::iterator it1 = studentList.begin();
		StudentRecord stud = *it1;
		while(it1!=studentList.end()){

			std::istringstream iss(stud.classRecord);
			int count=0;
			float total = 0;
			float average = 0;
			while(!iss.eof()){
				std::string s;
				iss>>s>>std::ws;
				int num;
				std::istringstream(s)>>num;
				count=count +1;
				total = total + num;
			}
			average = total/count;
				
			if(grade < average){
				grade = average;
				stNo = stud.studentNumber;
			}
				
			it1++;
			if(it1!=studentList.end()){
				stud = *it1;
			}
		}
	}
				std::cout<< "The winning student is " << stNo<<"\n";
}

};


