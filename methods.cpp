#include <iostream>
#include "classes.h"
#include <fstream>
#include <cstdlib>

using namespace std;

Person::Person(){ // constructor
    pesel = 11111111111;
    fName = "Nie wybrano imienia";
    lName = "Nie wybrano nazwiska";
}
Person::~Person(){} // destructor

Person::show(){
    cout << pesel << "\t" << fName << "\t" << lName << endl;
}

Student::Student(){ // constructor
    pesel = 11111111111;
    fName = "Nie wybrano imienia";
    lName = "Nie wybrano nazwiska";
    StudentID = 0;
}
Student::~Student(){} // destructor

Student::showStud(){
    cout << pesel << "\t" << fName << "\t" << lName << "\t" << StudentID << endl;
}

Professor::Professor(){ // constructor
    pesel = 11111111111;
    fName = "Nie wybrano imienia";
    lName = "Nie wybrano nazwiska";
    ProfessorID = 0;
}
Professor::~Professor(){} // destructor

Professor::showProf(){
    cout << pesel << "\t" << fName << "\t" << lName << "\t" << ProfessorID << endl;
}

Administrive_Worker::Administrive_Worker(){ // constructor
    pesel = 11111111111;
    fName = "Nie wybrano imienia";
    lName = "Nie wybrano nazwiska";
    AWID = 0;
}
Administrive_Worker::~Administrive_Worker(){} // destructor

Administrive_Worker::showAW(){
    cout << pesel << "\t" << fName << "\t" << lName << "\t" << AWID << endl;
}

Course::Course(){ // constructor
    semester = 0;
    CourseID = 0;
    name = "Nie wybrano nazwy kursu";
    exam_date = "01.01.2001";
}
Course::~Course(){} // destructor

Course::showCourse(){
    cout << CourseID << "\t" << semester << "\t" << name << "\t" << exam_date << endl;
}
