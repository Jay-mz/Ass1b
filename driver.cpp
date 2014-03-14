/*
 * driver.cpp
 *
 *  Created on: 10 Mar 2014
 *  Author: James Feli
 *  studentNumber: FLXJAM001
 *
 */

#include <iostream>

#include <algorithm>
#include "cmdline_parser.h"
#include "records.h"
#include <string>


using namespace flxjam001;
using namespace std;
void clear(void);
// Run this program to see how the cmdline_parser class works.
int main(int argc, char* argv[])
{
	using namespace std;
	using namespace flxjam001;

	cmdline_parser parser;

	if(!parser.process_cmdline(argc, argv))
	{
		std::cerr << "Couldn't process command line arguments" << std::endl;
		return 1;
	}

	if(parser.should_print_help())
		{ parser.print_help(std::cout);	}

	string filename = parser.get_filename();
	cout << "Using file located at "+ filename << endl;
	cout << "-----------------------------------------" << endl;



	char userChoice;  //holds users inputs
	Database record(filename);  //starting up the database with the passed file name
	//Loop event to display the menu and excute the user choice
	while(true){
		//diplaying the menu interface
			std::cout<< "1: Add student\n" << "2: Delete given student\n" << "3: Read database\n" << "4: Save database\n";
			std::cout<<"5: Display given student data\n"<<"6: Grade student\n" << "7: Display all student data\n"; 
			std::cout<< "8: Display the winning student\n" <<"q: Quit\n\n";
			std::cout<< "Enter a number (or q to quit) and press return: ";
 
    		  //stores the user choice as char
			std::cin>>userChoice;  //
			std::cout<<"\n";

			//first check if choice is quit
			if (userChoice=='q'){
				std::cout<<"Closing program....\n";
				std::cout<<"closed!!\n";
				break; //break from the loop
			}else if(userChoice=='1'){
				//variables to hold student records
				std::string fName;
				std::string surname;
				std::string studNo;
				std::string grade1;
				std::string grade2;



				//all records are converted to uppercase
				std::cout<< "Enter first name:\n";
				std::cin>>fName;
				std::transform(fName.begin(), fName.end(),fName.begin(), ::toupper);

				std::cout<<"Enter surname:\n";
				std::cin>>surname;
				std::transform(surname.begin(), surname.end(),surname.begin(), ::toupper);

				std::cout<<"Enter student Number:\n";
				std::cin>>studNo;
				std::transform(studNo.begin(), studNo.end(),studNo.begin(), ::toupper);

				std::cout<<"Enter grades(separated by space):\n";
				std::cin>>grade1;
				std::getline(std::cin,grade2);  //this caters for space seperation on grades since cin
				std::string grades = grade1+grade2;//		stops at spaces


				//here we assume the data is in complete set as required and create a student record
				StudentRecord student(fName, surname, studNo, grades);

				record.addStudent(student);  //adding student
				clear();  // clears terminal

			}else if(userChoice=='2'){
				//get studentNumber of student to delete and transform to uppercase
				std::string studNumber;
				std::cout<<"Enter student's number: \n";
				std::cin>>studNumber;
				std::transform(studNumber.begin(), studNumber.end(),studNumber.begin(), ::toupper);



				record.deleteStudent(studNumber); //delete student
				clear(); // clears terminal

			}else if(userChoice=='3'){
				//readDatabase with current and previous records shown
				record.readDatabase();
				clear();

			}else if(userChoice=='4'){
				//save database with
				record.saveDatabase(filename);
				std::cout<<"Database saved.";
				clear();

			}else if(userChoice=='5'){
				//get student Number to display records and transform to uppercase
				std::cout<<"Enter student's Number:\n";
				std::string studNumber;
				std::cin>>studNumber;
				std::transform(studNumber.begin(), studNumber.end(),studNumber.begin(), ::toupper);

				record.displayStudent(studNumber);//display records
				clear();

			}else if(userChoice=='6'){
				//get student number to grade student and transfrom it to upper case
				std::cout<<"Enter student's Number:\n";
				std::string studNumber;
				std::cin>>studNumber;
				std::transform(studNumber.begin(), studNumber.end(),studNumber.begin(), ::toupper);
				record.gradeStudent(studNumber); //grading student
				clear();

			}else if(userChoice=='7'){
				//diplay all records in the database
				record.displayDatabase();
				clear();
					
			}else if(userChoice == '8'){
				record.winningStudent();
				clear();}
			
			else{
				//in case user inputs non char character or wrong choice
				std::cout<<"chooser available choices.\n";
				clear();
					}

		}
	return 0;
}

//method that clears the terminal
void clear(void) {
		std::cout<<std::string(10,'\n');
	}
