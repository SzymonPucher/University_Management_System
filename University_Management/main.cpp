#include "people.h"

using namespace std;

int main()
{
	Student stud;
	Professor prof;
	Administrative_Worker adm_worker;
	Course course;
	Enrolled enrl;
	menu m;

	vector < Student > s;
	vector < Professor > p;
	vector < Administrative_Worker > a;
	vector < Course > c;
	vector < Enrolled > e;

	prof.generate(p,2000);
	course.generate(c,100,p);
	course.showCourse(c);
	//enrl.showEnrolled(e);

	system("pause");
    return 0;
}
