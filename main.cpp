#include <iostream>
#include "classes.h"
#include <fstream>
#include <cstdlib>
#include <vector>

using namespace std;

vector < Student > s;
vector < Professor > p;
vector < Administrative_Worker > aw;
vector < Course > c;

Student stud;
Professor prof;
Administrative_Worker adm_worker;
Course course;

void loadDatabase(){

     while(true){ // Load students
        stud.setIndex(s.size() + 1);
        stud.load();
        s.push_back(stud);
        if(s[s.size()-1].getPesel() == s[s.size()-2].getPesel()){ s.pop_back(); break; }
    }

    for(int i=0; i<s.size(); i++) s[i].showStud();

     cout << "\nLoaded " << s.size() << " students.\n\n";

    while(true){ // Load professors
        prof.setIndex(p.size() + 1);
        prof.load();
        p.push_back(prof);
        if(p[p.size()-1].getPesel() == p[p.size()-2].getPesel()){ p.pop_back(); break; }
    }

    for(int i=0; i<p.size(); i++) p[i].showProf();

     cout << "\nLoaded " << p.size() << " professors.\n\n";

    while(true){ // Load administrative workers
        adm_worker.setIndex(aw.size() + 1);
        adm_worker.load();
        aw.push_back(adm_worker);
        if(aw[aw.size()-1].getPesel() == aw[aw.size()-2].getPesel()){ aw.pop_back(); break; }
    }

    for(int i=0; i<aw.size(); i++) aw[i].showAW();

    cout << "\nLoaded " << aw.size() << " administrative workers.\n\n";

    while(true){ // Load courses
        course.setIndex(c.size() + 1);
        course.load();
        c.push_back(course);
        if(c[c.size()-1].getCID() == c[c.size()-2].getCID()){ c.pop_back(); break; }
    }

    for(int i=0; i<c.size(); i++) c[i].showCourse();

    cout << "\nLoaded " << c.size() << " courses.\n\n";
}

int main()
{

    loadDatabase();
    return 0;
}
