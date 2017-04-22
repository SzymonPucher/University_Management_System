#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include <cstdlib>
#include <time.h>
#include <algorithm>
#include <vector>

using namespace std;

class Student;
class Professor;
class Administrative_Worker;
class Course;
class Enrolled;

class Person {
protected:
    long long int pesel;
    string fName;
    string lName;
    string gender;
    string dateOfBirth;
	int ID;
	string Email;
public:
    Person();
    ~Person();
	 // SETTERS
    void setPesel(long long int x);
    void setFName(string x);
    void setLName(string x);
    void setGender(string x);
    void setDateOfBirth(string x);
	void setID(int x);
	// GETTERS
    long long int getPesel();
    string getFName();
    string getLName();
    string getGender();
    string getDateOfBirth();
	int getID();
	// OTHER
	bool create();
	bool updatePerson(int input);
};

class Student: public Person {
public:
    Student();
    ~Student();
	// SETTERS
	// GETTERS
	string getEmail();
	// DATABASE
	void load(vector<Student>& s);
	void generate(vector<Student>& s, int howMany);
	void save(vector<Student>& vec);
	// SHOW
	void showStud();
	void showStud(vector<Student>& vec);
	void showMyCourses(vector<Course>& c, vector<Enrolled>& e);
	void showMyProfessors(vector<Professor>& p, vector<Course>& c, vector<Enrolled>& e);
	// UPDATE
	void update();
	// COURSE METHODS
	void courseEnroll(vector<Course>& c, vector<Enrolled>& e);
	void courseDisenroll(vector<Course>& c, vector<Enrolled>& e);
	// LOGIN
	void logged(vector<Student>& s, vector<Professor>& p, vector<Administrative_Worker>& a, vector<Course>& c, vector<Enrolled>& e);
};

class Professor: public Person {
protected:
    string title;
public:
    Professor();
    ~Professor();
	// SETTERS
	void setTitle(string x);
	//GETTERS
	string getEmail();
	string getTitle();
	// DATEBASE
	void load(vector<Professor>& p);
	void generate(vector<Professor>& vec, int howMany);
	void save(vector<Professor>& vec);
	// OTHER
	void showProf();
	void showProf(vector<Professor>& vec, int ID);
	void showProf(vector<Professor>& vec);
	void showMyCourses(vector<Course>& c);
	void showMyStudents(vector<Student>& s, vector<Course>& c, vector<Enrolled>& e);
	// UPDATE
	void update();
	// LOGIN
	void logged(vector<Student>& s, vector<Professor>& p, vector<Administrative_Worker>& a, vector<Course>& c, vector<Enrolled>& e);
};

class Administrative_Worker: public Person {
protected:
    string title;
public:
    Administrative_Worker();
    ~Administrative_Worker();
	// SETTERS
	void setTitle(string x);
	// GETTERS
	string getEmail();
	string getTitle();
	// DATABASE
	void load(vector<Administrative_Worker>& a);
	void generate(vector<Administrative_Worker>& vec, int howMany);
	void save(vector<Administrative_Worker>& vec);
	// SHOW
	void showAW();
	void showAW(vector<Administrative_Worker>& vec);
	void showAccount(vector<Student>& s, vector<Professor>& p, vector<Administrative_Worker>& a, vector<Course>& c, vector<Enrolled>& e);
	bool showAccountByID(vector<Student>& s, vector<Professor>& p, vector<Administrative_Worker>& a, vector<Course>& c, vector<Enrolled>& e);
	// CREATE
	void createAccount(vector<Student>& s, vector<Professor>& p, vector<Administrative_Worker>& a, vector<Course>& c, vector<Enrolled>& e);
	void createStudent(vector<Student>& s);
	void createProfessor(vector<Professor>& p);
	void createAdmWor(vector<Administrative_Worker>& a);
	void createCourse(vector<Course>& c);
	// UPDATE
	void update();
	void updateAccount(vector<Student>& s, vector<Professor>& p, vector<Administrative_Worker>& a, vector<Course>& c, vector<Enrolled>& e);
	void updateStudent(vector<Student>& s);
	void updateProfessor(vector<Professor>& p);
	void updateAdmWor(vector<Administrative_Worker>& a);
	void updateCourse(vector<Course>& vec, vector<Professor>& p);
	// DELETE
	void deleteAccount(vector<Student>& s, vector<Professor>& p, vector<Administrative_Worker>& a, vector<Course>& c, vector<Enrolled>& e);
	void deleteStudent(vector<Student>& s);
	void deleteProfessor(vector<Professor>& p);
	void deleteAdmWor(vector<Administrative_Worker>& a);
	void deleteCourse(vector<Course>& c);
	// LOGIN
	void logged(vector<Student>& s, vector<Professor>& p, vector<Administrative_Worker>& a, vector<Course>& c, vector<Enrolled>& e);
};

class Course {
protected:

    int CourseID;
    int pID;
    string name;
    string examDate;
public:
    Course();
    ~Course();
	// SETTERS
	void setCID(int x);
	void setPID(int x);
	void setName(string x);
	void setExamDate(string x);
	// GETTERS
	int getCID();
	int getPID();
	string getName();
	string getExamDate();
	// ASSIGN PROFESSOR
	void assignProf(vector<Course>& c, vector<Professor>& p);
	void assignProf(vector<Professor>& p, int x);
	// DATABASE
	void load(vector<Course>& c);
	void generate(vector<Course>& vec, int howMany, vector<Professor>& p);
	void save(vector<Course>& vec);
	// SHOW
    void showCourse();
	void showCourse(vector<Course>& c);
	// UPDATE
	void update(vector<Professor>& p);
};

class Enrolled {
protected:
    int CourseID;
    long int ID;
    float grade;
public:
    Enrolled();
    ~Enrolled();
	// SETTERS
	void setCourseID(int x);
	void setStudID(long int x);
	void setGrade(float x);
	// GETTERS
	int getCID();
	long int getStudID();
	float getGrade();
	// DATABASE
	void load(vector<Enrolled>& vec);
	void generate(vector<Student>& s, vector<Course>& c, vector<Enrolled>& e);
	void save(vector<Enrolled>& vec);
	// SHOW
	void showEnrolled(vector<Enrolled>& vec);

    
    
};
class menu {
public:
	menu();
	~menu();

	int intInput();

	void loadDatabase(vector<Student>& s, vector<Professor>& p, vector<Administrative_Worker>& a, vector<Course>& c, vector<Enrolled>& e);
	void generateAll(vector<Student>& s, vector<Professor>& p, vector<Administrative_Worker>& a, vector<Course>& c, vector<Enrolled>& e, unsigned int howMany);
	void saveAll(vector<Student>& s, vector<Professor>& p, vector<Administrative_Worker>& a, vector<Course>& c, vector<Enrolled>& e);
	void login(vector<Student>& s, vector<Professor>& p, vector<Administrative_Worker>& a, vector<Course>& c, vector<Enrolled>& e);
};





