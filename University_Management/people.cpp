#include "people.h"


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
string Person::getFName(){
    return fName;
}
string Person::getLName(){
    return lName;
}
string Person::getDateOfBirth(){
    return dateOfBirth;
}
string Person::getGender(){
    return gender;
}
 // --------------------------------------- STUDENT METHODS ------------------------------------------
Student::Student(){ // constructor;
    StudentID = 0;
    sEmail = "0@student.email.com";
}
Student::~Student(){} // destructor

void Student::load(vector<Student>& s){
	fstream studDB;
	studDB.open("database/Students.txt",ios::in);

    if(studDB.good()==false){
        cout<<"Cannot open students database!";
        exit(0);
    }
	string line;
	for(int i = 0; i < 7; i++)
		studDB >> line;
	Student stud;
	while (!studDB.eof()) {
		studDB >> line;
		stud.pesel = atoll(line.c_str());
		studDB >> stud.fName;
		studDB >> stud.lName;
		studDB >> stud.gender;
		studDB >> stud.dateOfBirth;
		studDB >> line;
		stud.StudentID = atoi(line.c_str());
		studDB >> stud.sEmail;
		
		s.push_back(stud);
	}
	s.pop_back();

	studDB.close();
}
void Student::showStud(){
    cout << pesel << "\t" << fName << "\t";
    if(fName.length() < 8) cout << "\t";
    cout << lName << "\t";
	if (lName.length() < 8) cout << "\t";
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
string Student::getsEmail(){
    return sEmail;
}
// --------------------------------- PROFESSOR METHODS -----------------------------
Professor::Professor(){ // constructor
    ProfessorID = 0;
    pEmail = "0@professor.email.com";
}
Professor::~Professor(){} // destructor

void Professor::load(vector<Professor>& p){
    fstream profDB;
	profDB.open("database/Professors.txt",ios::in);

    if(profDB.good()==false){
        cout<<"Cannot open professors database!";
        exit(0);
    }


    string line;
	for (int i = 0; i < 8; i++)
		profDB >> line;
	Professor prof;
	while (!profDB.eof()) {
		profDB >> line;
		prof.pesel = atoll(line.c_str());
		profDB >> prof.title;
		profDB >> prof.fName;
		profDB >> prof.lName;
		profDB >> prof.gender;
		profDB >> prof.dateOfBirth;
		profDB >> line;
		prof.ProfessorID = atoi(line.c_str());
		profDB >> prof.pEmail;

		p.push_back(prof);
	}
	p.pop_back();
	profDB.close();
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
string Professor::getpEmail(){
    return pEmail;
}
string Professor::getTitle(){
    return title;
}
// ----------------------------- ADMINISTRATIVE WORKERS ----------------------------
Administrative_Worker::Administrative_Worker(){ // constructor
    AWID = 0;
    awEmail = "0@aw.email.com";
}
Administrative_Worker::~Administrative_Worker(){} // destructor

void Administrative_Worker::load(vector<Administrative_Worker>& a){
    fstream aw;
    aw.open("database/Administrative_Workers.txt",ios::in);

    if(aw.good()==false){
        cout<<"Cannot open administrative workers database!";
        exit(0);
    }


    string line;
	Administrative_Worker awork;
	for (int i = 0; i < 8; i++)
		aw >> line;
	while (!aw.eof()) {
		aw >> line;
		awork.pesel = atoll(line.c_str());
		aw >> awork.jobTitle;
		aw >> awork.fName;
		aw >> awork.lName;
		aw >> awork.gender;
		aw >> awork.dateOfBirth;
		aw >> line;
		awork.AWID = atoi(line.c_str());
		aw >> awork.awEmail;

		a.push_back(awork);
	}
	a.pop_back();
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
string Administrative_Worker::getawEmail(){
    return awEmail;
}
string Administrative_Worker::getJobTitle(){
    return jobTitle;
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

void Course::load(vector<Course>& c){
    fstream couDB;
	couDB.open("database/Courses.txt",ios::in);

    if(couDB.good()==false){
        cout<<"Cannot open courses database!";
        exit(0);
    }


	string line;
	for (int i = 0; i < 5; i++)
		couDB >> line;
	Course co;
	while (!couDB.eof()) {
		couDB >> line;
		co.CourseID = atoll(line.c_str());
		couDB >> line;
		co.semester = atoll(line.c_str());
		couDB >> co.name;
		couDB >> line;
		co.pID = atoll(line.c_str());
		couDB >> co.examDate;

		c.push_back(co);
	}
	c.pop_back();
	couDB.close();
}
void Course::showCourse(){
    cout << CourseID << "\t\t" << semester << "\t\t" << name << "\t";
    if(name.length() < 32) cout << "\t";
    if(name.length() < 24) cout << "\t";
    if(name.length() < 16) cout << "\t";
    if(name.length() < 8) cout << "\t";
    cout << pID << "\t" << examDate << endl;
}
void Course::showCourse(vector<Course>& c) {
	int size = c.size();
	for (int i = 0; i < size; i++) {
		cout << c[i].CourseID << "\t\t" << c[i].semester << "\t\t" << c[i].name << "\t";
		if (name.length() < 32) cout << "\t";
		if (name.length() < 24) cout << "\t";
		if (name.length() < 16) cout << "\t";
		if (name.length() < 8) cout << "\t";
		cout << c[i].pID << "\t" << c[i].examDate << endl;
	}
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
string Course::getExamDate(){
    return examDate;
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

