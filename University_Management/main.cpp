#include "classes.h"

using namespace std;

int main()
{
	vector < Student > s;
	vector < Professor > p;
	vector < Administrative_Worker > a;
	vector < Course > c;
	vector < Enrolled > e;

	menu m;

	/* * /
	m.generateAll(s, p, a, c, e, 35000);
	m.saveAll(s, p, a, c, e);
	/* */

	m.loadDatabase(s, p, a, c, e);
	m.login(s,p,a,c,e);
	//s[0].showStud(s);
	/* */

	system("pause");
    return 0;
}
