#include <iostream>
#include "classes.h"
#include <fstream>
#include <cstdlib>

using namespace std;


 // --------------------------------------- PERSON METHODS ------------------------------------------
Person::Person(){ // constructor
    pesel = 11111111111;
    fName = "No Fname";
    lName = "No Lname";
    gender = "Male";
    dateOfBirth = "00.00.0000";
}
Person::~Person(){} // destructor
void Person::setIndex(int x){
    index = x;
}
void Person::setPesel(long long int x){
    pesel = x;
}
void Person::setFName(string x){
    fName = x;
}
void Person::setLName(string x){
    lName = x;
}
void Person::setGender(string x){
    gender = x;
}
void Person::setDateOfBirth(string x){
    dateOfBirth = x;
}
long long int Person::getPesel(){
    return pesel;
}
string& Person::getFName(){
    string mystring(fName);
    return mystring;
}
string& Person::getLName(){
    string mystring(lName);
    return mystring;
}
string& Person::getDateOfBirth(){
    string mystring(dateOfBirth);
    return mystring;
}
string& Person::getGender(){
    string mystring(gender);
    return mystring;
}
 // --------------------------------------- STUDENT METHODS ------------------------------------------
Student::Student(){ // constructor;
    StudentID = 0;
    sEmail = "0@student.email.com";
}
Student::~Student(){} // destructor
void Student::load(){
    fstream stud;
    stud.open("database/Students.txt",ios::in);

    if(stud.good()==false){
        cout<<"Cannot open students database!";
        exit(0);
    }
    int line_num = (index)*7+1;
    int test_num = 1;
    string line;
    while(stud >> line){
        if(test_num==line_num) pesel=atoll(line.c_str());
        if(test_num==line_num+1) fName=line;
        if(test_num==line_num+2) lName=line;
        if(test_num==line_num+3) gender=line;
        if(test_num==line_num+4) dateOfBirth=line;
        if(test_num==line_num+5) StudentID=atoi(line.c_str());
        if(test_num==line_num+6) { sEmail=line; break; }
        test_num++;
    }
    stud.close();
}
void Student::showStud(){
    cout << pesel << "\t" << fName << "\t";
    if(fName.length() < 8) cout << "\t";
    cout << lName << "\t";
    if(lName.length() < 8) cout << "\t";
    cout << gender << "\t" << dateOfBirth << "\t" << StudentID << "\t\t" << sEmail << endl;
}
void Student::setStudentID(long int x){
    StudentID = x;
}
void Student::setsEmail(string x){
    sEmail = x;
}
long int Student::getStudentID(){
    return StudentID;
}
string& Student::getsEmail(){
    string mystring(sEmail);
    return mystring;
}
// --------------------------------- PROFESSOR METHODS -----------------------------
Professor::Professor(){ // constructor
    ProfessorID = 0;
    pEmail = "0@professor.email.com";
}
Professor::~Professor(){} // destructor
void Professor::load(){
    fstream prof;
    prof.open("database/Professors.txt",ios::in);

    if(prof.good()==false){
        cout<<"Cannot open professors database!";
        exit(0);
    }

    int line_num = index*8+1;
    int test_num = 1;
    string line;

    while(prof >> line){
        if(test_num==line_num) pesel=atoll(line.c_str());
        if(test_num==line_num+1) title=line;
        if(test_num==line_num+2) fName=line;
        if(test_num==line_num+3) lName=line;
        if(test_num==line_num+4) gender=line;
        if(test_num==line_num+5) dateOfBirth=line;
        if(test_num==line_num+6) ProfessorID=atoi(line.c_str());
        if(test_num==line_num+7) { pEmail=line; break; }
        test_num++;
    }
    prof.close();
}
void Professor::showProf(){
    cout << pesel << "\t" << title <<"\t";
    if(title.length() < 16) cout << "\t";
    if(title.length() < 8) cout << "\t";
    cout << fName << "\t";
    if(fName.length() < 8) cout << "\t";
    cout << lName << "\t";
    if(lName.length() < 8) cout << "\t";
    cout << gender << "\t" << dateOfBirth << "\t" << ProfessorID << "\t\t" << pEmail << endl;
}
void Professor::setProfessorID(long int x){
    ProfessorID = x;
}
void Professor::setpEmail(string x){
    pEmail = x;
}
void Professor::setTitle(string x){
    title = x;
}
long int Professor::getProfessorID(){
    return ProfessorID;
}
string& Professor::getpEmail(){
    string mystring(pEmail);
    return mystring;
}
string& Professor::getTitle(){
    string mystring(title);
    return mystring;
}
// ----------------------------- ADMINISTRATIVE WORKERS ----------------------------
Administrative_Worker::Administrative_Worker(){ // constructor
    AWID = 0;
    awEmail = "0@aw.email.com";
}
Administrative_Worker::~Administrative_Worker(){} // destructor
void Administrative_Worker::load(){
    fstream aw;
    aw.open("database/Administrative_Workers.txt",ios::in);

    if(aw.good()==false){
        cout<<"Cannot open administrative workers database!";
        exit(0);
    }

    int line_num = (index)*8+1;
    int test_num = 1;
    string line;

    while(aw >> line){
        if(test_num==line_num) pesel=atoll(line.c_str());
        if(test_num==line_num+1) jobTitle=line;
        if(test_num==line_num+2) fName=line;
        if(test_num==line_num+3) lName=line;
        if(test_num==line_num+4) gender=line;
        if(test_num==line_num+5) dateOfBirth=line;
        if(test_num==line_num+6) AWID=atoi(line.c_str());
        if(test_num==line_num+7) { awEmail=line; break; }
        test_num++;
    }
    aw.close();
}
void Administrative_Worker::showAW(){
    cout << pesel << "\t" << jobTitle <<"\t";
    if(jobTitle.length() < 16) cout << "\t";
    if(jobTitle.length() < 8) cout << "\t";
    cout << fName << "\t";
    if(fName.length() < 8) cout << "\t";
    cout << lName << "\t";
    if(lName.length() < 8) cout << "\t";
    cout << gender << "\t" << dateOfBirth << "\t" << AWID << "\t\t" << awEmail << endl;
}
void Administrative_Worker::setAWID(long int x){
    AWID = x;
}
void Administrative_Worker::setawEmail(string x){
    awEmail = x;
}
void Administrative_Worker::setJobTitle(string x){
    jobTitle = x;
}
long int Administrative_Worker::getAWID(){
    return AWID;
}
string& Administrative_Worker::getawEmail(){
    string mystring(awEmail);
    return mystring;
}
string& Administrative_Worker::getJobTitle(){
    string mystring(jobTitle);
    return mystring;
}
// ---------------------------- COURSE METHODS ----------------------------------
Course::Course(){ // constructor
    semester = 0;
    CourseID = 0;
    name = "Nie wybrano nazwy kursu";
    examDate = "00.00.0000";
    pID = 1000;
}
Course::~Course(){} // destructor
void Course::load(){
    fstream cou;
    cou.open("database/Courses.txt",ios::in);

    if(cou.good()==false){
        cout<<"Cannot open courses database!";
        exit(0);
    }

    int line_num = (index)*5+1;
    int test_num = 1;
    string line;

    while(cou >> line){
        if(test_num==line_num) CourseID=atoll(line.c_str());
        if(test_num==line_num+1) semester=atoll(line.c_str());
        if(test_num==line_num+2) name=line;
        if(test_num==line_num+3) pID=atoll(line.c_str());
        if(test_num==line_num+4) { examDate=line; break; }
        test_num++;
    }
    cou.close();
}
void Course::showCourse(){
    cout << CourseID << "\t\t" << semester << "\t\t" << name << "\t";
    if(name.length() < 32) cout << "\t";
    if(name.length() < 24) cout << "\t";
    if(name.length() < 16) cout << "\t";
    if(name.length() < 8) cout << "\t";
    cout << pID << "\t" << examDate << endl;
}
void Course::setIndex(int x){
    index = x;
}
void Course::setCID(int x){
    CourseID = x;
}
void Course::setPID(int x){
    pID = x;
}
void Course::setSemester(int x){
    semester = x;
}
void Course::setName(string x){
    name = x;
}
void Course::setExamDate(string x){
    examDate = x;
}
int Course::getCID(){
    return CourseID;
}
int Course::getPID(){
    return pID;
}
int Course::getSemester(){
    return semester;
}
string Course::getName(){
    return name;
}
string& Course::getExamDate(){
    string mystring(examDate);
    return mystring;
}
// ---------------------------- ENROLLED METHODS ---------------------------------
Enrolled::Enrolled(){ // constructor
    CourseID = 0;
    StudentID = 100000;
    grade = 3;
}
Enrolled::~Enrolled(){} // destructor
void Enrolled::showEnrolled(){
    cout << CourseID << "\t\t" << StudentID << "\t\t" << grade << endl;
}
void Enrolled::setCourseID(int x){
    CourseID = x;
}
void Enrolled::setStudID(long int x){
    StudentID = x;
}
void Enrolled::setGrade(float x){
    grade = x;
}
int Enrolled::getCID(){
    return CourseID;
}
long int Enrolled::getStudID(){
    return StudentID;
}
float Enrolled::getGrade(){
    return grade;
}

