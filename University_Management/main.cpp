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

	//m.loadDatabase(s,p,a,c,e);
	m.generateAll(s, p, a, c, e, 100);
	cout << s.size() << endl;
	//prof.generate(p,2000);
	//course.generate(c,100,p);
	//course.showCourse(c);
	//enrl.showEnrolled(e);

	system("pause");
    return 0;
}
