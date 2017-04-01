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
    int index;
    long long int pesel;
    string fName;
    string lName;
    string gender;
    string dateOfBirth;
public:
    Person();
    ~Person();
    void setIndex(int x);
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
    void showStud();
    void setStudentID(long int x);
    void setsEmail(string x);
    long int getStudentID();
    string getsEmail();
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
    void showProf();
    void setProfessorID(long int x);
    void setpEmail(string x);
    void setTitle(string x);
    long int getProfessorID();
    string getpEmail();
    string getTitle();
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
    void showAW();
    void setAWID(long int x);
    void setawEmail(string x);
    void setJobTitle(string x);
    long int getAWID();
    string getawEmail();
    string getJobTitle();
};

class Course {
protected:
    int index;
    int CourseID;
    int pID;
    int semester;
    string name;
    string examDate;
public:
    Course();
    ~Course();
	void load(vector<Course>& c);
    void showCourse();
	void showCourse(vector<Course>& c);
    void setIndex(int x);
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
};

class Enrolled {
protected:
    int CourseID;
    long int StudentID;
    float grade;
public:
    Enrolled();
    ~Enrolled();
    void showEnrolled();
    void setCourseID(int x);
    void setStudID(long int x);
    void setGrade(float x);
    int getCID();
    long int getStudID();
    float getGrade();
};




