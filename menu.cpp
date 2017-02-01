#include <iostream>
#include "classes.h"
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <string>
#include <time.h>
#include <algorithm>

class menu{

vector < Student > s;
vector < Professor > p;
vector < Administrative_Worker > aw;
vector < Course > c;
vector < Enrolled > e;

public:

template <typename T> bool myMaxBool(T x, T y) {
    return x > y;
}

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
    Course cour;
    string ts;
    long long int ti;
    cout << "\n\nAdding new course.\n\nSemester: ";
    cin >> ti;
    cour.setCID(c.size()+101);
    try {
        if (ti > 10){
            throw "There is no such semester (1-10)!";
        }
        cour.setSemester(ti);
    } catch (const char* msg) {
        cerr << msg << endl;
        return;
    }

    cout << "\nName: ";
    cin >> ts;
    try {
        if (ts.length() > 31){
            throw "Name is too long!";
        }
        cour.setName(ts);
    } catch (const char* msg) {
        cerr << msg << endl;
        return;
    }

    cout << "\nExam date: ";
    cin >> ts;
    try {
        if (ts.length() > 10 || ts.length() < 8){
            throw "Wrong format, too short or too long!";
        }
        cour.setExamDate(ts);
    } catch (const char* msg) {
        cerr << msg << endl;
        return;
    }

    c.push_back(cour);
}
void deleteStud(){
    int x;
    cout << "Give me ID of a student you want to delete: ";
    cin >> x;

    for(int i=0; i<s.size();i++)
        if(s[i].getStudentID() == x)
            s.erase(s.begin() + i);
}
void select(){
    //char* word[];
    int x;
    string s1,s2;
    cout << "From which table: \n1. Students\n2. Professors\n3. Administrative workers\n4. Courses\n\nYour choice: ";
    cin >> x;
    if (x==1){/* */

        cout << "Like which value: ";
        cin >> s1;
        const char * c1 = s1.c_str();
        int es;
        for(es=0;es<s1.size();es++){
            if(c1[es] == '=') break;
        }
        cout <<"\n\nPESEL\t\tFirst name\tLast name\tGender\tDate of birth\tStudentID\tEmail"<<endl;
       // c[0] = toupper(c[0]);
        if(c1[0] == 'F'){
            for(int i=0; i<s.size(); i++){
                s2 = s[i].getFName();
                const char * c2 = s2.c_str();
                if(c1[es+2] == c2[0])
                    s[i].showStud();
            }
        }
        if(c1[0] == 'L'){
            for(int i=0; i<s.size(); i++){
                s2 = s[i].getLName();
                const char * c2 = s2.c_str();
                if(c1[es+2] == c2[0])
                    s[i].showStud();
            }
        }
        if(c1[0] == 'G'){
            for(int i=0; i<s.size(); i++){
                s2 = s[i].getGender();
                const char * c2 = s2.c_str();
                if(c1[es+2] == c2[0])
                    s[i].showStud();
            }
        }
        cout << endl << endl;
        /* * /
        if (s1 == "Fname=Katie"){
             cout <<"\n\nPESEL\t\tFirst name\tLast name\tGender\tDate of birth\tStudentID\tEmail"<<endl;

            for(int i=0; i<s.size(); i++){
                    if(s[i].getFName() == "Katie") s[i].showStud();
            }
            cout << endl << endl;
        }/* */
    }
    if (x==2){
        string s3;
        int i1, i2;
        cout << "Column name: ";
        cin >> s1;
        cout << endl << "SELECT * FROM Professors WHERE " << s1 << " > ";
        cin >> s2;
        if(s1=="pID") i2 = atoi( s2.c_str() );
        cout <<"PESEL\t\tTitle\t\t\tFirst name\tLast name\tGender\tDate of birth\tProfessorID\tEmail"<<endl;
        for (int i=0;i<p.size();i++){
            if(s1=="pID") {
                i1 = p[i].getProfessorID();
                if (myMaxBool(i1,i2))
                    p[i].showProf();
            }
            if(s1=="FName"){
                s3 = p[i].getFName();
                if (s3>s2) p[i].showProf();
            }
        }
    }
    if (x==3){}
    if (x==4){}
}
void showStudSorted(){
    //std::sort(s.begin(), s.end(), )
}
void menuStud(int ID){
    int x;
    cout << "\nYou are logged as Student with ID: " << ID << endl;
    cout << "1. Show your data\n2. Show your courses\n3. Enroll to a course\n4. Logout\n5. Exit\nYour choice: ";
    cin >> x;
    if(x==1){
        for(int i = 0; i < s.size();i++){
            if(ID == s[i].getStudentID()){
                cout << "\nPesel: " << s[i].getPesel() << "\nName: ";
                cout << s[i].getFName() << " ";
                cout << s[i].getLName() << "\nGender: ";
                cout << s[i].getGender() << "\nDate of birth: ";
                cout << s[i].getDateOfBirth() << "\nStudentID: " << s[i].getStudentID() << "\nEmail: ";
                cout << s[i].getsEmail() << endl << endl;
                break;
            }
        }
    }
    else if(x==2){
        cout <<"CourseID\tSemester\tName\t\t\t\t\tpID\tExam date"<<endl;
        for(int i=0; i<c.size(); i++)
            for(int j=0; j<e.size(); j++)
                if(ID == e[j].getStudID() && c[i].getCID() == e[j].getCID())
                    c[i].showCourse();
    }
    else if(x==3){
        Enrolled enrl;
        int CID;
        cout << "Enroll to course with ID: ";
        cin >> CID;

        try {
            if (CID < 101 || CID > c.size()+100){
                throw "There is no such course!";
            }
            for(int i=0; i<c.size(); i++)
                for(int j=0; j<e.size(); j++)
                    if(ID == e[j].getStudID() && c[i].getCID() == e[j].getCID() && CID == e[j].getCID())
                        throw "You are already enrolled for this course!";

            enrl.setCourseID(CID);
            enrl.setStudID(ID);
            e.push_back(enrl);
        } catch (const char* msg) {
            cerr << msg << endl;
        }
    }
    else if(x==4){
        system("cls");
        login();
    }
    else if(x==5)
        exit(0);
    menuStud(ID);
}
void menuProf(int ID){
    int x;
    cout << "\nYou are logged as Professor with ID: " << ID << endl;
    cout << "1. Show your data\n2. Show your courses\n3. Show your students\n4. Grade a student\n5. Logout\n6. Exit\nYour choice: ";
    cin >> x;
    if(x==1){
        for(int i = 0; i < p.size();i++){
            if(ID == p[i].getProfessorID()){
                cout << "\nPesel: " << p[i].getPesel() << "\nName: ";
                cout << p[i].getFName() << " ";
                cout << p[i].getLName() << "\nGender: ";
                cout << p[i].getGender() << "\nDate of birth: ";
                cout << p[i].getDateOfBirth() << "\nProfessorID: " << p[i].getProfessorID() << "\nTitle: ";
                cout << p[i].getTitle() << "\nEmail: ";
                cout << p[i].getpEmail() << endl << endl;
                break;
            }
        }
    }
    else if(x==2){
        cout <<"CourseID\tSemester\tName\t\t\t\t\tpID\tExam date"<<endl;
        for(int i=0; i<c.size(); i++)
            if(ID == c[i].getPID())
                c[i].showCourse();
    }
    else if(x==3){
        for(int i=0; i<c.size(); i++){
            if(ID == c[i].getPID()){
                for(int j=0;j<e.size();j++){
                    if(c[i].getCID() == e[j].getCID()){
                        for(int k=0;k<s.size();k++)
                            if(e[j].getStudID() == s[k].getStudentID())
                                s[k].showStud();
                    }
                }
            }
        }
    }
    else if(x==4){
        int CID, SID;
        float grade;
        cout << "Grade student from course with ID: ";
        cin >> CID;
        cout << "List of all students attending this course: \n\n";
        for(int j=0;j<e.size();j++){
            if(CID == e[j].getCID()){
                for(int k=0;k<s.size();k++)
                    if(e[j].getStudID() == s[k].getStudentID())
                        s[k].showStud();
            }
        }
        cout << "\nWhich one you want to grade, input his StudentID: ";
        cin >> SID;
        cout << "\nAnd this student's grade is: ";
        cin >> grade;
        int i;
        for(i=0;i<e.size();i++){
            if(e[i].getStudID() == SID && e[i].getCID() == CID){
                e[i].setGrade(grade);
                break;
            }
        }
        cout << endl;
        e[i].showEnrolled();
    }
    else if(x==5){
        system("cls");
        login();
    }
    else if(x==6)
        exit(0);
    menuProf(ID);
}
void menuAW(int ID){
    int x;
    cout << "\nYou are logged as Administrative Worker with ID: " << ID << endl;
    cout << "1. Show your data\n2. Add new Student\n3. Add new Professor\n4. Add new Administrative Worker\n5. Add new Course\n";
    cout << "6. Delete student\n7. Show all students\n8. Show all professors\n9. Show all administrative workers\n10. Show all courses\n11. Sophisticated select\n12. Logout\n13. Exit\n\nYour choice: ";
    cin >> x;
    if(x==1){
        for(int i = 0; i < aw.size();i++){
            if(ID == aw[i].getAWID()){
                cout << "\nPesel: " << aw[i].getPesel() << "\nName: ";
                cout << aw[i].getFName() << " ";
                cout << aw[i].getLName() << "\nGender: ";
                cout << aw[i].getGender() << "\nDate of birth: ";
                cout << aw[i].getDateOfBirth() << "\nAWID: " << aw[i].getAWID() << "\nJob Title: ";
                cout << aw[i].getJobTitle() << "\nEmail: ";
                cout << aw[i].getawEmail() << endl << endl;
                break;
            }
        }
    }
    else if(x==2)
        addStud();
    else if(x==3)
        addProf();
    else if(x==4)
        addAW();
    else if(x==5)
        addCourse();
    else if(x==6)
        deleteStud();
    else if(x==7)
        showAllStud();
    else if(x==8)
        showAllProf();
    else if(x==9)
        showAllAdmWork();
    else if(x==10)
        showAllCourses();
    else if(x==11)
        select();
    else if(x==12){
        system("cls");
        login();
    }
    else if(x==13)
        exit(0);
    menuAW(ID);
}
void login(){
    srand(time(NULL));
    int x;

    cout << "\nLogin as:\n1. Random student\n2. Random professor\n3. Administrative worker with full authorization.\nYour choice: ";
    cin >> x;
    if(x==1)
        menuStud(s[rand() % s.size()].getStudentID());
    else if(x==2)
        menuProf(p[rand() % p.size()].getProfessorID());
    else if(x==3)
        menuAW(aw[rand() % aw.size()].getAWID());
    else { system("cls"); login(); }
}
};
