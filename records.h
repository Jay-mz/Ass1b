/*
 * records.h
 *
 *  Created on: 10 Mar 2014
 *  Author: James Feli
 *  studentNumber: FLXJAM001
 *
 */

#ifndef _RECORDS_H
#define _RECORDS_H

#include <string>
#include <list>

namespace flxjam001{

	class StudentRecord{
		public:
			StudentRecord(std::string name, std::string surname, std::string studentNumber, std::string classRecord);

			std::string name, surname, studentNumber, classRecord;
	};



	class Database{
		private:
			std::list<StudentRecord> studentList;

		public:
			Database(std::string fileName);

	void addStudent(StudentRecord newStudent);
	void deleteStudent(std::string studentNumber);
	void readDatabase();
	void saveDatabase(std::string fileName);
	void displayStudent(std::string studentNumber);
	void gradeStudent(std::string studentNumber);
	void displayDatabase();
	void winningStudent();
};
}

#endif
