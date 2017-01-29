#include <iostream>
#include "classes.h"
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <string>
#include <time.h>

using namespace std;

vector < Student > s;
vector < Professor > p;
vector < Administrative_Worker > aw;
vector < Course > c;
vector < Enrolled > e;

void loadEnrolled(){
    Enrolled enrl;
    srand(time(NULL));
    int CID, x1, x2, x3;
    long int SID;
    float grade;
    for(int i=0;i<c.size();i++){
        CID = c[i].getCID();
        x1 = rand() % 101 + 30;
        x3 = rand() % s.size();
        for(int j=0;j < x1;j++){
            x3 += (rand() % 25+1) ;
            SID = s[x3 % s.size()].getStudentID();
            grade = (rand() % 7 + 4)/2;
            if (grade == 2.5) grade = 2;
            enrl.setCourseID(CID);
            enrl.setStudID(SID);
            enrl.setGrade(grade);
            e.push_back(enrl);
        }
    }
}
void assignProfCourses(){
    for(int i=0;i<c.size();i++)
        c[i].setPID(p[i%p.size()].getProfessorID());
}
void loadDatabase(){

     while(true){ // Load students
        Student stud;
        stud.setIndex(s.size() + 1);
        stud.load();
        s.push_back(stud);
        if(s[s.size()-1].getPesel() == s[s.size()-2].getPesel()){ s.pop_back(); s.pop_back(); break; }
    }

     cout << "\nLoaded " << s.size() << " students.\n";

    while(true){ // Load professors
        Professor prof;
        prof.setIndex(p.size() + 1);
        prof.load();
        p.push_back(prof);
        if(p[p.size()-1].getPesel() == p[p.size()-2].getPesel()){ p.pop_back(); p.pop_back(); break; }
    }



     cout << "\nLoaded " << p.size() << " professors.\n";

    while(true){ // Load administrative workers
        Administrative_Worker adm_worker;
        adm_worker.setIndex(aw.size() + 1);
        adm_worker.load();
        aw.push_back(adm_worker);
        if(aw[aw.size()-1].getPesel() == aw[aw.size()-2].getPesel()){ aw.pop_back(); aw.pop_back(); break; }
    }



    cout << "\nLoaded " << aw.size() << " administrative workers.\n";

    while(true){ // Load courses
        Course course;
        course.setIndex(c.size() + 1);
        course.load();
        c.push_back(course);
        if(c[c.size()-1].getCID() == c[c.size()-2].getCID()){ c.pop_back(); c.pop_back(); break; }
    }



    cout << "\nLoaded " << c.size() << " courses.\n";

    assignProfCourses();
    loadEnrolled();
}
void showAllStud(){
    cout <<"\n\nPESEL\t\tFirst name\tLast name\tGender\tDate of birth\tStudentID\tEmail"<<endl;
    for(int i=0; i<s.size(); i++) s[i].showStud();
    cout << endl << endl;
}
void showAllProf(){
    cout <<"PESEL\t\tTitle\t\t\tFirst name\tLast name\tGender\tDate of birth\tProfessorID\tEmail"<<endl;
    for(int i=0; i<p.size(); i++) p[i].showProf();
    cout << endl << endl;
}
void showAllAdmWork(){
    cout <<"PESEL\t\tJob Title\t\tFirst name\tLast name\tGender\tDate of birth\tAdm. Worker ID\tEmail"<<endl;
    for(int i=0; i<aw.size(); i++) aw[i].showAW();
    cout << endl << endl;
}
void showAllCourses(){
    cout <<"CourseID\tSemester\tName\t\t\t\t\tpID\tExam date"<<endl;
    for(int i=0; i<c.size(); i++) c[i].showCourse();
    cout << endl << endl;
}
void showAllEnrolled(){
    cout <<"CourseID\t\tStudentID\t\tGrade"<<endl;
    for(int i=0; i<e.size(); i++) e[i].showEnrolled();
    cout << endl << endl;
}
void addStud(){

    Student stud;
    string ts;
    long long int ti;
    cout << "\n\nAdding new student.\n\nPESEL: ";
    cin >> ti;

    try {
        if (ti < 10000000000){
            throw "Wrong pesel format!";
        }
        stud.setPesel(ti);
    } catch (const char* msg) {
        cerr << msg << endl;
        return;
    }

    cout << "\nFirst name: ";
    cin >> ts;
    try {
        if (ts.length() > 23){
            throw "First name is too long!";
        }
        stud.setFName(ts);
    } catch (const char* msg) {
        cerr << msg << endl;
        return;
    }

    cout << "\nLast name: ";
    cin >> ts;
    try {
        if (ts.length() > 23){
            throw "Last name is too long!";
        }
        stud.setLName(ts);
    } catch (const char* msg) {
        cerr << msg << endl;
        return;
    }

    cout << "\nGender (M/F): ";
    cin >> ts;
    try {
        if (ts != "M" && ts != "F"){
            throw "Gender should be equal to M or F!";
        }
        if (ts == "M") ts = "Male";
        if (ts == "F") ts = "Female";
        stud.setGender(ts);
    } catch (const char* msg) {
        cerr << msg << endl;
        return;
    }

    cout << "\nDate of birth: ";
    cin >> ts;
    try {
        if (ts.length() > 10 || ts.length() < 8){
            throw "Wrong format, too short or too long!";
        }
        stud.setDateOfBirth(ts);
    } catch (const char* msg) {
        cerr << msg << endl;
        return;
    }

    cout << "\nStudentID: ";
    cin >> ti;
    try {
        if (ti > 999999 || ti < 100000){
            throw "Wrong number, student ID has 6 digits!";
        }
        stud.setStudentID(ti);
    } catch (const char* msg) {
        cerr << msg << endl;
        return;
    }

    ostringstream stream;
    stream << ti << "@student.email.com";
    ts = stream.str();
    stud.setsEmail(ts);
    s.push_back(stud);
}
void addProf(){

    Professor prof;
    string ts;
    long long int ti;
    cout << "\n\nAdding new professor.\n\nPESEL: ";
    cin >> ti;

    try {
        if (ti < 10000000000){
            throw "Wrong pesel format!";
        }
        prof.setPesel(ti);
    } catch (const char* msg) {
        cerr << msg << endl;
        return;
    }

    cout << "\nFirst name: ";
    cin >> ts;
    try {
        if (ts.length() > 23){
            throw "First name is too long!";
        }
        prof.setFName(ts);
    } catch (const char* msg) {
        cerr << msg << endl;
        return;
    }

    cout << "\nLast name: ";
    cin >> ts;
    try {
        if (ts.length() > 23){
            throw "Last name is too long!";
        }
        prof.setLName(ts);
    } catch (const char* msg) {
        cerr << msg << endl;
        return;
    }

    cout << "\nTitle: ";
    cin >> ts;
    try {
        if (ts.length() > 23){
            throw "Wrong format, too short or too long!";
        }
        prof.setTitle(ts);
    } catch (const char* msg) {
        cerr << msg << endl;
        return;
    }

    cout << "\nGender (M/F): ";
    cin >> ts;
    try {
        if (ts != "M" && ts != "F"){
            throw "Gender should be equal to M or F!";
        }
        if (ts == "M") ts = "Male";
        if (ts == "F") ts = "Female";
        prof.setGender(ts);
    } catch (const char* msg) {
        cerr << msg << endl;
        return;
    }

    cout << "\nDate of birth: ";
    cin >> ts;
    try {
        if (ts.length() > 10 || ts.length() < 8){
            throw "Wrong format, too short or too long!";
        }
        prof.setDateOfBirth(ts);
    } catch (const char* msg) {
        cerr << msg << endl;
        return;
    }

    cout << "\nProfessorID: ";
    cin >> ti;
    try {
        if (ti > 9999 || ti < 1000){
            throw "Wrong number, ProfessorID should have 4 digits!";
        }
        prof.setProfessorID(ti);
    } catch (const char* msg) {
        cerr << msg << endl;
        return;
    }

    ostringstream stream;
    stream << ti << "@professor.email.com";
    ts = stream.str();
    prof.setpEmail(ts);
    p.push_back(prof);
}
void addAW(){

    Administrative_Worker admWor;
    string ts;
    long long int ti;
    cout << "\n\nAdding new professor.\n\nPESEL: ";
    cin >> ti;

    try {
        if (ti < 10000000000){
            throw "Wrong pesel format!";
        }
        admWor.setPesel(ti);
    } catch (const char* msg) {
        cerr << msg << endl;
        return;
    }

    cout << "\nFirst name: ";
    cin >> ts;
    try {
        if (ts.length() > 23){
            throw "First name is too long!";
        }
        admWor.setFName(ts);
    } catch (const char* msg) {
        cerr << msg << endl;
        return;
    }

    cout << "\nLast name: ";
    cin >> ts;
    try {
        if (ts.length() > 23){
            throw "Last name is too long!";
        }
        admWor.setLName(ts);
    } catch (const char* msg) {
        cerr << msg << endl;
        return;
    }

    cout << "\nJob title: ";
    cin >> ts;
    try {
        if (ts.length() > 23){
            throw "Wrong format, too long!";
        }
        admWor.setJobTitle(ts);
    } catch (const char* msg) {
        cerr << msg << endl;
        return;
    }

    cout << "\nGender (M/F): ";
    cin >> ts;
    try {
        if (ts != "M" && ts != "F"){
            throw "Gender should be equal to M or F!";
        }
        if (ts == "M") ts = "Male";
        if (ts == "F") ts = "Female";
        admWor.setGender(ts);
    } catch (const char* msg) {
        cerr << msg << endl;
        return;
    }

    cout << "\nDate of birth: ";
    cin >> ts;
    try {
        if (ts.length() > 10 || ts.length() < 8){
            throw "Wrong format, too short or too long!";
        }
        admWor.setDateOfBirth(ts);
    } catch (const char* msg) {
        cerr << msg << endl;
        return;
    }

    cout << "\nAWID: ";
    cin >> ti;
    try {
        if (ti > 99999 || ti < 10000){
            throw "Wrong number, AWID should have 5 digits!";
        }
        admWor.setAWID(ti);
    } catch (const char* msg) {
        cerr << msg << endl;
        return;
    }

    ostringstream stream;
    stream << ti << "@aw.email.com";
    ts = stream.str();
    admWor.setawEmail(ts);
    aw.push_back(admWor);
}
void addCourse(){

}
void select(){ // trash testing function
    int x;
    cin >> x;
    for(int i=0; i<s.size(); i++) {
        for(int j=0; j<e.size(); j++){
            if(s[i].getStudentID() == e[j].getStudID() && x == e[j].getCID() && e[j].getGrade() == 5)
                s[i].showStud();
        }
    }
}
int main()
{
/* */
    loadDatabase();
    showAllStud();
    showAllEnrolled();
    select();

/* */
    return 0;
}
