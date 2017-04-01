
#include "people.h"

using namespace std;

Student stud;
Professor prof;
Administrative_Worker adm_worker;
Course course;
Enrolled enrl;

vector < Student > s;
vector < Professor > p;
vector < Administrative_Worker > aw;
vector < Course > c;
vector < Enrolled > e;

void showAllStud() {
	cout << "\n\nPESEL\t\tFirst name\tLast name\tGender\tDate of birth\tStudentID\tEmail" << endl;
	for (int i = 0; i<s.size(); i++) s[i].showStud();
	cout << endl << endl;
}


void loadDatabase() {

	stud.load(s);
	prof.load(p);
	adm_worker.load(aw);
	course.load(c);
	
	cout << "\nLoaded " << s.size() << " students.\n";
	cout << "\nLoaded " << p.size() << " professors.\n";
	cout << "\nLoaded " << aw.size() << " administrative workers.\n";
	cout << "\nLoaded " << c.size() << " courses.\n";

	// assignProfCourses();
	// loadEnrolled();
}

int main()
{
/* * /
	DB_Gen db;
	db.test();
	cout << "Hi!" << endl;

	//menu m;
    //Student s;
	//cout << "Student: " << s.getFName();
	//m.loadDatabase();
   // m.login();
/* */
	loadDatabase();
	//showAllStud();
	course.showCourse(c);
	system("pause");
    return 0;
}
