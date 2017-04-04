#include "classes.h"

using namespace std;

int main()
{
	Student stud;
	Professor prof;
	Administrative_Worker adw;
	Course course;
	Enrolled enrl;
	menu m;

	vector < Student > s;
	vector < Professor > p;
	vector < Administrative_Worker > a;
	vector < Course > c;
	vector < Enrolled > e;
	//
	/* */
	m.loadDatabase(s,p,a,c,e);
	//course.showCourse(c);
	m.login();
	system("pause");
    return 0;
}
