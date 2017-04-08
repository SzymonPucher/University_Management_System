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
	m.loadDatabase(s,p,a,c,e);
	m.login(s,p,a,c,e);

    return 0;
}
