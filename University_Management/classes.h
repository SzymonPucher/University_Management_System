#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include <cstdlib>
#include <time.h>
#include <algorithm>
#include <vector>

using namespace std;

class Person {
protected:
    long long int pesel;
    string fName;
    string lName;
    string gender;
    string dateOfBirth;
public:
    Person();
    ~Person();
    void setPesel(long long int x);
    void setFName(string x);
    void setLName(string x);
    void setGender(string x);
    void setDateOfBirth(string x);
    long long int getPesel();
    string getFName();
    string getLName();
    string getGender();
    string getDateOfBirth();

};

class Student: public Person {
protected:
    long int StudentID;
    string sEmail;
public:
    Student();
    ~Student();
	void load(vector<Student>& s);
	void generate(vector<Student>& s, int howMany);
	void save(vector<Student>& vec);
	void showStud(vector<Student>& vec);
    void setStudentID(long int x);
    void setsEmail(string x);
    long int getStudentID();
    string getsEmail();
	void logged();
};

class Professor: public Person {
protected:
    long int ProfessorID;
    string pEmail;
    string title;
public:
    Professor();
    ~Professor();
	void load(vector<Professor>& p);
	void generate(vector<Professor>& vec, int howMany);
	void save(vector<Professor>& vec);
	void showProf(vector<Professor>& vec);
    void setProfessorID(long int x);
    void setpEmail(string x);
    void setTitle(string x);
    long int getProfessorID();
    string getpEmail();
    string getTitle();
	void logged();
};

class Administrative_Worker: public Person {
protected:
    long int AWID;
    string awEmail;
    string jobTitle;
public:
    Administrative_Worker();
    ~Administrative_Worker();
	void load(vector<Administrative_Worker>& a);
	void generate(vector<Administrative_Worker>& vec, int howMany);
	void save(vector<Administrative_Worker>& vec);
	void showAW(vector<Administrative_Worker>& vec);
    void setAWID(long int x);
    void setawEmail(string x);
    void setJobTitle(string x);
    long int getAWID();
    string getawEmail();
    string getJobTitle();
	void logged();
};

class Course {
protected:

    int CourseID;
    int pID;
    int semester;
    string name;
    string examDate;
public:
    Course();
    ~Course();
	void load(vector<Course>& c);
	void generate(vector<Course>& vec, int howMany, vector<Professor>& p);
	void save(vector<Course>& vec);
    void showCourse();
	void showCourse(vector<Course>& c);
    void setCID(int x);
    void setPID(int x);
    void setSemester(int x);
    void setName(string x);
    void setExamDate(string x);
    int getCID();
    int getPID();
    int getSemester();
    string getName();
    string getExamDate();
	void assignProf(vector<Course>& c, vector<Professor>& p);
};

class Enrolled {
protected:
    int CourseID;
    long int StudentID;
    float grade;
public:
    Enrolled();
    ~Enrolled();
	void load(vector<Enrolled>& vec);
	void generate(vector<Student>& s, vector<Course>& c, vector<Enrolled>& e);
	void save(vector<Enrolled>& vec);
	void showEnrolled(vector<Enrolled>& vec);
    void setCourseID(int x);
    void setStudID(long int x);
    void setGrade(float x);
    int getCID();
    long int getStudID();
    float getGrade();
};
class menu
{
public:
	menu();
	~menu();
	void loadDatabase(vector<Student>& s, vector<Professor>& p, vector<Administrative_Worker>& a, vector<Course>& c, vector<Enrolled>& e);
	void gen(vector<Professor>& s);
	void generateAll(vector<Student>& s, vector<Professor>& p, vector<Administrative_Worker>& a, vector<Course>& c, vector<Enrolled>& e, unsigned int howMany);
	void login();
private:

};





