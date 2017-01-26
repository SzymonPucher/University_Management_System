#include <iostream>

using namespace std;

class Person {
protected:
    long long int pesel;
    string fName;
    string lName;
    char gender;
public:
    Person();
    ~Person();
    show();
};

class Student: Person {
protected:
    long int StudentID;
    string s_email;
public:
    Student();
    ~Student();
    showStud();
};

class Professor: Person {
protected:
    long int ProfessorID;
    string p_email;
public:
    Professor();
    ~Professor();
    showProf();
};

class Administrive_Worker: Person {
protected:
    long int AWID;
    string aw_email;
public:
    Administrive_Worker();
    ~Administrive_Worker();
    showAW();
};

class Course {
protected:
    int semester;
    long int CourseID;
    string name;
    string exam_date;
public:
    Course();
    ~Course();
    showCourse();
};




