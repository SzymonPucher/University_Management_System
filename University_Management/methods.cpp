#include "classes.h"
using namespace std;
 // --------------------------------------- PERSON METHODS ------------------------------------------
Person::Person(){ 
    pesel = 11111111111;
    fName = "No Fname";
    lName = "No Lname";
    gender = "Male";
    dateOfBirth = "00.00.0000";
	ID = 0;
}
Person::~Person(){} 
// SETTERS
void Person::setPesel(long long int x){
    pesel = x;
}
void Person::setFName(string x){
    fName = x;
}
void Person::setLName(string x){
    lName = x;
}
void Person::setGender(string x){
    gender = x;
}
void Person::setDateOfBirth(string x){
    dateOfBirth = x;
}
void Person::setID(int x) {
	ID = x;
}
// GETTERS
long long int Person::getPesel(){
    return pesel;
}
string Person::getFName(){
    return fName;
}
string Person::getLName(){
    return lName;
}
string Person::getGender() {
	return gender;
}
string Person::getDateOfBirth(){
    return dateOfBirth;
}
int Person::getID() {
	return ID;
}
// CREATE
bool Person::create(){
	/* 
	Fuction takes data from user Input about Pesel, Name and Gender of a person for which new account is about to be created.
	Used in created methods of derived classes.
	*/
	string ts;
	long long int ti;
	try {
		cout << "\n\nAdding new account.\n\nPESEL: ";
		cin >> ts;
		if (!all_of(ts.begin(), ts.end(), ::isdigit))
			throw "Given input is not a number!";
		ti = stoll(ts);
		if (ti < 10000000000 || ti > 100000000000)
			throw "Wrong pesel format!";
		setPesel(ti);

		ts.erase(ts.begin() + 6, ts.end());
		ts.append(".");
		ts.append(ts.begin() + 2, ts.begin() + 4);
		ts.append(".19");
		ts.append(ts.begin(), ts.begin() + 2);
		ts.erase(ts.begin(), ts.begin() + 4);
		setDateOfBirth(ts);

		cout << "\nFirst name: ";
		cin >> ts;
		if (ts.length() > 23)
			throw "First name is too long!";
		setFName(ts);

		cout << "\nLast name: ";
		cin >> ts;
		if (ts.length() > 23)
			throw "Last name is too long!";
		setLName(ts);

		cout << "\nGender (M/F): ";
		cin >> ts;
		if (ts != "M" && ts != "F")
			throw "Gender should be equal to M or F!";
		if (ts == "M") ts = "Male";
		if (ts == "F") ts = "Female";
		setGender(ts);
	}
	catch (const char *s) { cout << s << endl; return false; }
	return true;
}
// UPDATE
bool Person::updatePerson(int input) {
	/*
	Funciton changes data about one of the users.
	Used in update methods of classes of derived classes.
	*/
	string ts;
	long long int ti;
	try {
		cout << "New ";

		if (input == 1) {
			cout << "\nFirst name: ";
			cin >> ts;
			if (ts.length() > 23)
				throw "First name is too long!";
			setFName(ts);
		}
		if (input == 2) {
			cout << "\nLast name: ";
			cin >> ts;
			if (ts.length() > 23)
				throw "Last name is too long!";
			setLName(ts);
		}
		if (input == 3) {
			cout << "\nGender (M/F): ";
			cin >> ts;
			if (ts != "M" && ts != "F")
				throw "Gender should be equal to M or F!";
			if (ts == "M") ts = "Male";
			if (ts == "F") ts = "Female";
			setGender(ts);
		}
	}
	catch (const char *s) { cout << s << endl; return false; }
	return true;
}
 // --------------------------------------- STUDENT METHODS ------------------------------------------
Student::Student(){}
Student::~Student(){}
// GETTERS
string Student::getEmail() {
	string email;
	email = to_string(ID);
	email.append("@student.email.com");
	return email;
}
// DATABASE
void Student::load(vector<Student>& s){
	/*
	Funciton loads list of students from file in directory: database/Students.txt
	Data is saved in vector of objects with name "s".
	*/
	fstream studDB;
	studDB.open("database/Students.txt",ios::in);

    if(studDB.good()==false){
        cout<<"Cannot open students database!";
        exit(0);
    }
	string line;
	for(int i = 0; i < 6; i++)
		studDB >> line;
	Student stud;
	while (!studDB.eof()) {
		studDB >> line;
		stud.pesel = atoll(line.c_str());
		studDB >> stud.fName;
		studDB >> stud.lName;
		studDB >> stud.gender;
		studDB >> stud.dateOfBirth;
		studDB >> line;
		stud.ID = atoi(line.c_str());
		
		s.push_back(stud);
	}
	s.pop_back();

	studDB.close();
}
void Student::generate(vector<Student>& s, int howMany) {
	/*
	Function used for generating random list of students (amount of generated student is given by "howMany" variable).
	Database of possible names of students is saved in directory database/generatorDB/*.txt
	*/

	if (howMany > 899000) howMany = 899000;
	fstream fmn_file, ffn_file, ln_file;
	fmn_file.open("database/generatorDB/First_names_male.txt", ios::in);
	if (fmn_file.good() == false) {
		cout << "Cannot open first male names database!";
		exit(0);
	}
	ffn_file.open("database/generatorDB/First_names_female.txt", ios::in);
	if (ffn_file.good() == false) {
		cout << "Cannot open first female names database!";
		exit(0);
	}
	ln_file.open("database/generatorDB/Last_names.txt", ios::in);
	if (ln_file.good() == false) {
		cout << "Cannot open last names database!";
		exit(0);
	}
	string line;
	vector<string> fmn, ffn, ln;
	while (!fmn_file.eof()) {
		fmn_file >> line;
		fmn.push_back(line);
	}
	while (!ffn_file.eof()) {
		ffn_file >> line;
		ffn.push_back(line);
	}
	while (!ln_file.eof()) {
		ln_file >> line;
		ln.push_back(line);
	}
	fmn.pop_back();
	ffn.pop_back();
	ln.pop_back();

	fmn_file.close();
	ffn_file.close();
	ln_file.close();

	Student stud;
	int y, m, d, pes5dig, sid = 100000;
	string temp;
	srand(time(NULL));
	for (int i = 0; i < howMany; i++) {
		if (rand() % 2) {
			stud.setGender("Male");
			stud.setFName(fmn[rand() % fmn.size()]);
		}
		else {
			stud.setGender("Female");
			stud.setFName(ffn[rand() % ffn.size()]);
		}
		stud.setLName( ln[ rand() % ln.size() ] );
		
		y = rand() % 15 + 1985;
		m = rand() % 12 + 1;
		if (m == 2) {
			if (y % 4) d = rand() % 28 + 1;
			else d = rand() % 29 + 1;
		}
		else if (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12) d = rand() % 31 + 1;
		else d = rand() % 30 + 1;
		
		temp.append(to_string(y % 100));
		if (m < 10) temp.append(to_string(0));
		temp.append(to_string(m));
		if (d < 10) temp.append(to_string(0));
		temp.append(to_string(d));
		for (int j = 0; j < 5; j++) {
			temp.append(to_string(rand() % 10));
		}
		stud.setPesel(stoll(temp));
		temp.clear();

		if (d < 10) temp.append(to_string(0));
		temp.append(to_string(d));
		temp.append(".");
		if (m < 10) temp.append(to_string(0));
		temp.append(to_string(m));
		temp.append(".");
		temp.append(to_string(y));
		stud.setDateOfBirth(temp);
		temp.clear();

		stud.setID(sid++);
		s.push_back(stud);
		
	}
	sort(s.begin(),s.end(), [](const Student& lhs, const Student& rhs)
	{
		return lhs.pesel < rhs.pesel;
	});
	int count = 0;
	for (int i = 0; i < s.size()-1; i++) {
		if (s[i].getPesel() == s[i + 1].getPesel()) {
			count++;
			s.erase(s.begin()+i);
		}
	}
	if (count != 0) stud.generate(s, count);
}
void Student::save(vector<Student>& vec) {
	/*
	Function saves database of students stored in vector "s" to a file with directory: database/Students.txt
	*/
	ofstream file;
	file.open("database/Students.txt");
	
	file << "PESEL\t\tFirst_name\tLast_name\tGender\t\tDate_of_birth\tStudentID\n" << endl;
	int size = vec.size();
	
	for (int i = 0; i < size; i++) {
		file << vec[i].pesel << "\t" << vec[i].fName << "\t";
		if (vec[i].fName.length() < 8) file << "\t";
		file << vec[i].lName << "\t";
		if (vec[i].lName.length() < 8) file << "\t";
		file << vec[i].gender << "\t\t" << vec[i].dateOfBirth << "\t" << vec[i].ID << endl;
	}
	file.close();
}
// SHOW
void Student::showStud() {
	/*
	Function shows information about one student.
	*/
	//cout << "\n\nPESEL\t\tFirst name\tLast name\tGender\tDate of birth\tStudentID\tEmail" << endl;
	cout << pesel << "\t" << fName << "\t";
	if (fName.length() < 8) cout << "\t";
	cout << lName << "\t";
	if (lName.length() < 8) cout << "\t";
	cout << gender << "\t" << dateOfBirth << "\t" << ID << "\t\t" << getEmail() << endl;
}
void Student::showStud(vector<Student>& vec){
	/*
	Function shows whole list of students saved in vector "s".
	*/
	int size = vec.size();
	cout << "\n\nPESEL\t\tFirst name\tLast name\tGender\tDate of birth\tStudentID\tEmail" << endl;
	for (int i = 0; i < size; i++)
		vec[i].showStud();
}
void Student::showMyCourses(vector<Course>& c, vector<Enrolled>& e) {
	/*
	Method shows all courses a student is enrolled to.
	*/
	cout << "\nCourseID\tSemester\tName\t\t\t\t\tpID\tExam date" << endl;
	for (int i = 0; i<c.size(); i++)
		for (int j = 0; j<e.size(); j++)
			if (ID == e[j].getStudID() && c[i].getCID() == e[j].getCID())
				c[i].showCourse();
}
void Student::showMyProfessors(vector<Professor>& p, vector<Course>& c, vector<Enrolled>& e) {
	/*
	Method shows all professors that students has classes with.
	*/
	cout << "PESEL\t\tTitle\t\t\tFirst name\tLast name\tGender\tDate of birth\tProfessorID\tEmail" << endl;
	Professor prof;
	for (int i = 0; i<c.size(); i++)
		for (int j = 0; j<e.size(); j++)
			if (getID() == e[j].getStudID() && c[i].getCID() == e[j].getCID())
				prof.showProf(p, c[i].getPID());
}
// UPDATE
void Student::update() {
	// Changes informatuon about student
	int input;
	cout << "\n1. Change first name.\n2. Change last name.\n3. Change gender.\nInput: ";
	cin >> input;

	if (input >= 1 && input <= 3) {
		updatePerson(input);
	}
	else cout << "Error!";
}
// COURSE METHODS
void Student::courseEnroll(vector<Course>& c, vector<Enrolled>& e) {
	/*
	Method enrolls student for a particural course.
	Adds this enrollment to Enrolled Database, where all enrollment pairs (student + course) are stored.
	*/
	int input;
	cin >> input;
	try {
		for (int j = 0; j < e.size(); j++)
			if (ID == e[j].getStudID() && input == e[j].getCID())
				throw "You are already enrolled for this course";
		/* * /
		for (int i = 0; i < c.size(); i++)
			if (c[i].getCID() == input)
				throw "Course with such ID does not exist!";
		/* */
	}
	catch (const char* s) {
		cout << s << endl;
		return;
	}
	Enrolled enrl;
	enrl.setCourseID(input);
	enrl.setStudID(getID());
	e.push_back(enrl);
	cout << "You successfully enrolled to a course with ID = " << input << endl;
}
void Student::courseDisenroll(vector<Course>& c, vector<Enrolled>& e) {
	/*
	Method cancels enrollment for a course done by student.
	It deletes erollment pair from Enrollment Database.
	*/
	int input;
	cin >> input;

	for (int j = 0; j < e.size(); j++)
		if (getID() == e[j].getStudID() && input == e[j].getCID()) {
			e.erase(e.begin()+j);
			cout << "Enrollment to a course with ID " << input << " was deleted." << endl;
			return;
		}
	cout << "You aren't enrolled for this course." << endl;
}
// LOGIN
void Student::logged(vector<Student>& s, vector<Professor>& p, vector<Administrative_Worker>& a, vector<Course>& c, vector<Enrolled>& e) {
	/*
	Method displayed when student successfully logs in.
	It's a menu for user-program interaction.
	*/
	int input;
	
	system("cls");
	cout << "Logged as student with ID: " << getID() << endl;
	cout << "1. Show my info.\n2. Show my courses\n3. Enroll to a course.\n4. Disenroll from a course.\n5. Show my professors.\n6. Logout\n7. Exit.\nInput: ";
	cin >> input;
	if (input == 1) {
		showStud();
	}
	if (input == 2) {
		showMyCourses(c, e);
	}
	if (input == 3) {
		courseEnroll(c, e);
	}
	if (input == 4) {
		courseDisenroll(c, e);
	}
	if (input == 5) {
		showMyProfessors(p, c, e);
	}
	if (input == 6) {
		menu m;
		m.login(s, p, a, c, e);
	}
	if (input == 7) {
		exit(0);
	}
	cout << endl << endl;
	system("pause");
	logged(s, p, a, c, e);
}

// --------------------------------- PROFESSOR METHODS -----------------------------
Professor::Professor(){}
Professor::~Professor(){}
// SETTERS
void Professor::setTitle(string x) {
	title = x;
}
// GETTERS
string Professor::getEmail() {
	string email;
	email = to_string(ID);
	email.append("@professor.email.com");
	return email;
}
string Professor::getTitle() {
	return title;
}
// DATABASE
void Professor::load(vector<Professor>& p){
	/*
	Funciton loads list of professors from file in directory: database/Professors.txt
	Data is saved in vector of objects with name "p".
	*/
    fstream profDB;
	profDB.open("database/Professors.txt",ios::in);

    if(profDB.good()==false){
        cout<<"Cannot open professors database!";
        exit(0);
    }


    string line;
	for (int i = 0; i < 7; i++)
		profDB >> line;
	Professor prof;
	while (!profDB.eof()) {
		profDB >> line;
		prof.pesel = atoll(line.c_str());
		profDB >> prof.title;
		profDB >> prof.fName;
		profDB >> prof.lName;
		profDB >> prof.gender;
		profDB >> prof.dateOfBirth;
		profDB >> line;
		prof.ID = atoi(line.c_str());

		p.push_back(prof);
	}
	p.pop_back();
	profDB.close();
}
void Professor::generate(vector<Professor>& vec, int howMany) {
	/*
	Function used for generating random list of professors (amount of generated professors is given by "howMany" variable).
	Database of possible names of professors is saved in directory database/generatorDB/*.txt
	*/
	if (howMany > 8990) howMany = 8990;
	fstream fmn_file, ffn_file, ln_file, t_file;
	fmn_file.open("database/generatorDB/First_names_male.txt", ios::in);
	if (fmn_file.good() == false) {
		cout << "Cannot open first male names database!";
		exit(0);
	}
	ffn_file.open("database/generatorDB/First_names_female.txt", ios::in);
	if (ffn_file.good() == false) {
		cout << "Cannot open first female names database!";
		exit(0);
	}
	ln_file.open("database/generatorDB/Last_names.txt", ios::in);
	if (ln_file.good() == false) {
		cout << "Cannot open last names database!";
		exit(0);
	}
	t_file.open("database/generatorDB/Job_titles_professors.txt", ios::in);
	if (t_file.good() == false) {
		cout << "Cannot open last names database!";
		exit(0);
	}
	string line;
	vector<string> fmn, ffn, ln, t;
	while (!fmn_file.eof()) {
		fmn_file >> line;
		fmn.push_back(line);
	}
	while (!ffn_file.eof()) {
		ffn_file >> line;
		ffn.push_back(line);
	}
	while (!ln_file.eof()) {
		ln_file >> line;
		ln.push_back(line);
	}
	while (!t_file.eof()) {
		t_file >> line;
		t.push_back(line);
	}
	fmn.pop_back();
	ffn.pop_back();
	ln.pop_back();
	t.pop_back();

	fmn_file.close();
	ffn_file.close();
	ln_file.close();
	t_file.close();

	Professor prof;
	int y, m, d, pes5dig, sid = 10000;
	string temp;
	srand(time(NULL));
	for (int i = 0; i < howMany; i++) {
		if (rand() % 2) {
			prof.setGender("Male");
			prof.setFName(fmn[rand() % fmn.size()]);
		}
		else {
			prof.setGender("Female");
			prof.setFName(ffn[rand() % ffn.size()]);
		}
		prof.setLName(ln[rand() % ln.size()]);

		y = rand() % 35 + 1945;
		m = rand() % 12 + 1;
		if (m == 2) {
			if (y % 4) d = rand() % 28 + 1;
			else d = rand() % 29 + 1;
		}
		else if (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12) d = rand() % 31 + 1;
		else d = rand() % 30 + 1;

		temp.append(to_string(y % 100));
		if (m < 10) temp.append(to_string(0));
		temp.append(to_string(m));
		if (d < 10) temp.append(to_string(0));
		temp.append(to_string(d));
		for (int j = 0; j < 5; j++) {
			temp.append(to_string(rand() % 10));
		}
		prof.setPesel(stoll(temp));
		temp.clear();

		if (d < 10) temp.append(to_string(0));
		temp.append(to_string(d));
		temp.append(".");
		if (m < 10) temp.append(to_string(0));
		temp.append(to_string(m));
		temp.append(".");
		temp.append(to_string(y));
		prof.setDateOfBirth(temp);
		temp.clear();

		prof.setID(sid++);

		prof.setTitle(t[rand()%t.size()]);

		vec.push_back(prof);

	}
	sort(vec.begin(), vec.end(), [](const Professor& lhs, const Professor& rhs)
	{
		return lhs.pesel < rhs.pesel;
	});
	int count = 0;
	for (int i = 0; i < vec.size() - 1; i++) {
		if (vec[i].getPesel() == vec[i + 1].getPesel()) {
			count++;
			vec.erase(vec.begin() + i);
		}
	}
	if (count != 0) prof.generate(vec, count);
}
void Professor::save(vector<Professor>& vec) {
	/*
	Function saves database of professors stored in vector "p" to a file with directory: database/Professors.txt
	*/
	ofstream file;
	file.open("database/Professors.txt");

	int size = vec.size();
	file << "PESEL\t\tTitle\t\t\tFirst_name\tLast_name\tGender\t\tDate_of_birth\tProfessorID\n" << endl;
	for (int i = 0; i < size; i++) {
		file << vec[i].pesel << "\t" << vec[i].title << "\t";
		if (vec[i].title.length() < 16) file << "\t";
		if (vec[i].title.length() < 8) file << "\t";
		file << vec[i].fName << "\t";
		if (vec[i].fName.length() < 8) file << "\t";
		file << vec[i].lName << "\t";
		if (vec[i].lName.length() < 8) file << "\t";
		file << vec[i].gender << "\t\t" << vec[i].dateOfBirth << "\t" << vec[i].ID << endl;
	}
	file.close();
}
// SHOW
void Professor::showProf() {
	/*
	Function shows information about one professor.
	*/
	//cout << "PESEL\t\tTitle\t\t\tFirst name\tLast name\tGender\tDate of birth\tProfessorID\tEmail" << endl;
	cout << pesel << "\t" << title << "\t";
	if (title.length() < 16) cout << "\t";
	if (title.length() < 8) cout << "\t";
	cout << fName << "\t";
	if (fName.length() < 8) cout << "\t";
	cout << lName << "\t";
	if (lName.length() < 8) cout << "\t";
	cout << gender << "\t" << dateOfBirth << "\t" << ID << "\t\t" << getEmail() << endl;

}
void Professor::showProf(vector<Professor>& vec, int PID) {
	/*
	Function shows a professor with ID given by argument passed to the function "PID".
	*/
	int size = vec.size();
	//cout << "PESEL\t\tTitle\t\t\tFirst name\tLast name\tGender\tDate of birth\tProfessorID\tEmail" << endl;
	for (int i = 0; i < size; i++)
		if (PID == vec[i].getID()) 
			vec[i].showProf();
}
void Professor::showProf(vector<Professor>& vec) {
	/*
	Function shows whole list of professors saved in vector "p".
	*/
	int size = vec.size();
	cout << "PESEL\t\tTitle\t\t\tFirst name\tLast name\tGender\tDate of birth\tProfessorID\tEmail" << endl;
	for (int i = 0; i < size; i++) 
		vec[i].showProf();
}
void Professor::showMyCourses(vector<Course>& c) {
	/*
	Shows all the courses this professor leads.
	*/
	cout << "\nCourseID\tName\t\t\t\t\tpID\tExam date" << endl;
	for (int i = 0; i<c.size(); i++)
		if (c[i].getPID() == getID())
			c[i].showCourse();
}
void Professor::showMyStudents(vector<Student>& s, vector<Course>& c, vector<Enrolled>& e) {
	/*
	Shows list of all students who participate in this professor's courses. For every course there is seperate list provided.
	*/
	for (int i = 0; i < c.size(); i++) {
		if (c[i].getPID() == getID()) { // finds courses professor has
			cout << "----------------------------------------------------------\n\nCourseID\tName\t\t\t\t\tpID\tExam date" << endl;
			c[i].showCourse();
			cout << "\n\nPESEL\t\tFirst name\tLast name\tGender\tDate of birth\tStudentID\tEmail" << endl;
			for (int j = 0; j < s.size(); j++) // finds all the students that enrolled to professors course
				for (int k = 0; k < e.size(); k++)
					if (e[k].getStudID() == s[j].getID() && c[i].getCID() == e[k].getCID())
						s[j].showStud();
		}
	}
}
// UPDATE
void Professor::update() {
	/*
	Method changes informaton about course.
	*/
	int input;
	cout << "\n1. Change first name.\n2. Change last name.\n3. Change gender.\n4. Change title.\nInput: ";
	cin >> input;

	if (input >= 1 && input <= 4) {
		updatePerson(input);
	}
	if (input == 5) {
		string ts;
		cout << "\nNew name for course with ID " << getID() << " is: ";
		cin >> ts;
		setTitle(ts);
	}

}
// LOGIN
void Professor::logged(vector<Student>& s, vector<Professor>& p, vector<Administrative_Worker>& a, vector<Course>& c, vector<Enrolled>& e) {
	/*
	Mehtod is a type of a menu.
	Displayed when professor logins successfully.
	*/
	int input;

	system("cls");
	cout << "Logged as professor with ID: " << getID() << endl;
	cout << "1. Show my info.\n2. Show my courses\n3. Show my students.\n4. Logout\n5. Exit.\nInput: ";
	cin >> input;

	if (input == 1) {
		showProf();
	}
	if (input == 2) {
		showMyCourses(c);
	}
	if (input == 3) {
		showMyStudents(s, c, e);
	}
	if (input == 4) {
		menu m;
		m.login(s, p, a, c, e);
	}
	if (input == 5) {
		exit(0);
	}
	cout << endl << endl;
	system("pause");
	logged(s, p, a, c, e);
}

// ----------------------------- ADMINISTRATIVE WORKERS ----------------------------
Administrative_Worker::Administrative_Worker(){}
Administrative_Worker::~Administrative_Worker(){} // destructor
// SETTERS
void Administrative_Worker::setTitle(string x) {
	title = x;
}
// GETTERS
string Administrative_Worker::getEmail() {
	string email;
	email = to_string(ID);
	email.append("@admwor.email.com");
	return email;
}
string Administrative_Worker::getTitle() {
	return title;
}
// DATABASE
void Administrative_Worker::load(vector<Administrative_Worker>& a){
	/*
	Funciton loads list of administrative workers from file in directory: database/Administrative_Workers.txt
	Data is saved in vector of objects with name "a".
	*/
    fstream aw;
    aw.open("database/Administrative_Workers.txt",ios::in);

    if(aw.good()==false){
        cout<<"Cannot open administrative workers database!";
        exit(0);
    }


    string line;
	Administrative_Worker awork;
	for (int i = 0; i < 7; i++)
		aw >> line;
	while (!aw.eof()) {
		aw >> line;
		awork.pesel = atoll(line.c_str());
		aw >> awork.title;
		aw >> awork.fName;
		aw >> awork.lName;
		aw >> awork.gender;
		aw >> awork.dateOfBirth;
		aw >> line;
		awork.ID = atoi(line.c_str());

		a.push_back(awork);
	}
	a.pop_back();
    aw.close();
}
void Administrative_Worker::generate(vector<Administrative_Worker>& vec, int howMany) {
	/*
	Function used for generating random list of administrative workers (amount of generated administrative workers is given by "howMany" variable).
	Database of possible names of administrative workers is saved in directory database/generatorDB/*.txt
	*/
	if (howMany > 89900) howMany = 89900;
	fstream fmn_file, ffn_file, ln_file, t_file;
	fmn_file.open("database/generatorDB/First_names_male.txt", ios::in);
	if (fmn_file.good() == false) {
		cout << "Cannot open first male names database!";
		exit(0);
	}
	ffn_file.open("database/generatorDB/First_names_female.txt", ios::in);
	if (ffn_file.good() == false) {
		cout << "Cannot open first female names database!";
		exit(0);
	}
	ln_file.open("database/generatorDB/Last_names.txt", ios::in);
	if (ln_file.good() == false) {
		cout << "Cannot open last names database!";
		exit(0);
	}
	t_file.open("database/generatorDB/Job_titles_workers.txt", ios::in);
	if (t_file.good() == false) {
		cout << "Cannot open last names database!";
		exit(0);
	}
	string line;
	vector<string> fmn, ffn, ln, t;
	while (!fmn_file.eof()) {
		fmn_file >> line;
		fmn.push_back(line);
	}
	while (!ffn_file.eof()) {
		ffn_file >> line;
		ffn.push_back(line);
	}
	while (!ln_file.eof()) {
		ln_file >> line;
		ln.push_back(line);
	}
	while (!t_file.eof()) {
		t_file >> line;
		t.push_back(line);
	}
	fmn.pop_back();
	ffn.pop_back();
	ln.pop_back();
	t.pop_back();

	fmn_file.close();
	ffn_file.close();
	ln_file.close();
	t_file.close();

	Administrative_Worker aw;
	int y, m, d, pes5dig, sid = 1000;
	string temp;
	srand(time(NULL));
	for (int i = 0; i < howMany; i++) {
		if (rand() % 2) {
			aw.setGender("Male");
			aw.setFName(fmn[rand() % fmn.size()]);
		}
		else {
			aw.setGender("Female");
			aw.setFName(ffn[rand() % ffn.size()]);
		}
		aw.setLName(ln[rand() % ln.size()]);

		y = rand() % 35 + 1945;
		m = rand() % 12 + 1;
		if (m == 2) {
			if (y % 4) d = rand() % 28 + 1;
			else d = rand() % 29 + 1;
		}
		else if (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12) d = rand() % 31 + 1;
		else d = rand() % 30 + 1;

		temp.append(to_string(y % 100));
		if (m < 10) temp.append(to_string(0));
		temp.append(to_string(m));
		if (d < 10) temp.append(to_string(0));
		temp.append(to_string(d));
		for (int j = 0; j < 5; j++) {
			temp.append(to_string(rand() % 10));
		}
		aw.setPesel(stoll(temp));
		temp.clear();

		if (d < 10) temp.append(to_string(0));
		temp.append(to_string(d));
		temp.append(".");
		if (m < 10) temp.append(to_string(0));
		temp.append(to_string(m));
		temp.append(".");
		temp.append(to_string(y));
		aw.setDateOfBirth(temp);
		temp.clear();

		aw.setID(sid++);

		aw.setTitle(t[rand()%t.size()]);

		vec.push_back(aw);

	}
	sort(vec.begin(), vec.end(), [](const Administrative_Worker& lhs, const Administrative_Worker& rhs)
	{
		return lhs.pesel < rhs.pesel;
	});
	int count = 0;
	for (int i = 0; i < vec.size() - 1; i++) {
		if (vec[i].getPesel() == vec[i + 1].getPesel()) {
			count++;
			vec.erase(vec.begin() + i);
		}
	}
	if (count != 0) aw.generate(vec, count);
}
void Administrative_Worker::save(vector<Administrative_Worker>& vec) {
	/*
	Function saves database of administrative workers stored in vector "a" to a file with directory: database/Administrative_Workers.txt
	*/
	ofstream file;
	file.open("database/Administrative_Workers.txt");

	int size = vec.size();
	file << "PESEL\t\tJob_Title\t\tFirst_name\tLast_name\tGender\t\tDate_of_birth\tID\n" << endl;
	for (int i = 0; i < size; i++) {
		file << vec[i].pesel << "\t" << vec[i].title << "\t";
		if (vec[i].title.length() < 16) file << "\t";
		if (vec[i].title.length() < 8) file << "\t";
		file << vec[i].fName << "\t";
		if (vec[i].fName.length() < 8) file << "\t";
		file << vec[i].lName << "\t";
		if (vec[i].lName.length() < 8) file << "\t";
		file << vec[i].gender << "\t\t" << vec[i].dateOfBirth << "\t" << vec[i].ID << endl;
	}
	file.close();
}
// SHOW
void Administrative_Worker::showAW() {
	/*
	Function shows information about one administrative worker.
	*/
	//cout << "PESEL\t\tJob Title\t\tFirst name\tLast name\tGender\tDate of birth\tAdm. Worker ID\tEmail" << endl;
	cout << pesel << "\t" << title << "\t";
	if (title.length() < 16) cout << "\t";
	if (title.length() < 8) cout << "\t";
	cout << fName << "\t";
	if (fName.length() < 8) cout << "\t";
	cout << lName << "\t";
	if (lName.length() < 8) cout << "\t";
	cout << gender << "\t" << dateOfBirth << "\t" << ID << "\t\t" << getEmail() << endl;

}
void Administrative_Worker::showAW(vector<Administrative_Worker>& vec){
	/*
	Function shows whole list of administrative workers saved in vector "a".
	*/
	int size = vec.size();
	cout << "PESEL\t\tJob Title\t\tFirst name\tLast name\tGender\tDate of birth\tAdm. Worker ID\tEmail" << endl;
	for (int i = 0; i < size; i++)
		vec[i].showAW();
}
void Administrative_Worker::showAccount(vector<Student>& s, vector<Professor>& p, vector<Administrative_Worker>& a, vector<Course>& c, vector<Enrolled>& e) {
	/*
	Method for showing information about one or all of the accounts of one type in the system.
	*/
	int input;
	cout << "1. Show all students.\n2. Show all professors.\n3. Show all administrative workers.\n4. Show all courses.\n5. Show all enrollments." << endl;
	cout << "6. Show person or course by ID.\n7. Back.\nInput: ";
	cin >> input;

	if (input == 1)
		s[0].showStud(s);

	if (input == 2)
		p[0].showProf(p);

	if (input == 3)
		a[0].showAW(a);

	if (input == 4)
		c[0].showCourse(c);

	if (input == 5)
		e[0].showEnrolled(e);

	if (input == 6)
		if (showAccountByID(s, p, a, c, e))
			cout << "\n\nError! Wrong ID!";

	if (input == 7)
		return;
	logged(s, p, a, c, e);
}
bool Administrative_Worker::showAccountByID(vector<Student>& s, vector<Professor>& p, vector<Administrative_Worker>& a, vector<Course>& c, vector<Enrolled>& e) {
	/*
	Method displays after choosing to show information about particural account in method: "showAccount".
	It puprose is to get an ID and search for a person or a course with such in the database.
	*/
	int input;
	cout << "You are searching for particural record in database. Input ID: ";
	cin >> input;

	if (input >= 100000 && input < 1000000) {
		for (int i = 0; i < s.size(); i++) {
			if (s[i].getID() == input) {
				s[i].showStud();
				return false;
			}
		}
	}
	else if (input >= 10000) {
		for (int i = 0; i < p.size(); i++) {
			if (p[i].getID() == input) {
				p[i].showProf();
				return false;
			}
		}
	}
	else if (input >= 1000) {
		for (int i = 0; i < a.size(); i++) {
			if (a[i].getID() == input) {
				a[i].showAW();
				return false;
			}
		}
	}
	else if (input >= 100) {
		for (int i = 0; i < c.size(); i++) {
			if (c[i].getCID() == input) {
				c[i].showCourse();
				return false;
			}
		}
	}
	return true;
}
// CREATE
void Administrative_Worker::createAccount(vector<Student>& s, vector<Professor>& p, vector<Administrative_Worker>& a, vector<Course>& c, vector<Enrolled>& e) {
	/*
	Menu-method for choosing the type of account to be created.
	*/
	int input;
	system("cls");
	cout << "What type of account would you like to create?" << endl;
	cout << "1. Student.\n2. Professor.\n3. Administrator.\n4. Create new course.\n5. Exit.\nInput: ";
	cin >> input;

	if (input == 1) {
		createStudent(s);
	}
	if (input == 2) {
		createProfessor(p);
	}
	if (input == 3) {
		createAdmWor(a);
	}
	if (input == 4) {
		createCourse(c);
	}
	if (input == 5) {
		logged(s, p, a, c, e);
	}
}
void Administrative_Worker::createStudent(vector<Student>& s) {
	/*
	Method creates new student and puts him in vector of all students in the system.
	*/
	long int ti;
	string ts;
	try {
		Person person;
		person.create();

		Student stud;
		stud.setPesel(person.getPesel());
		stud.setFName(person.getFName());
		stud.setLName(person.getLName());
		stud.setGender(person.getGender());
		stud.setDateOfBirth(person.getDateOfBirth());

		cout << "\nStudentID: ";
		cin >> ti;
	
		if (ti > 999999 || ti < 100000)
			throw "Wrong number, student ID has 6 digits!";
		for (int i = 0; i < s.size(); i++)
			if (s[i].getID() == ti)
				throw "Student with this ID already exists!";
		stud.setID(ti);
		s.push_back(stud);
	}
	catch (const char* s) { cout << "Error! " << s << endl; }
}
void Administrative_Worker::createProfessor(vector<Professor>& p) {
	/*
	Method creates new professor and puts him in vector of all professors in the system.
	*/
	long int ti;
	string ts;
	try{
		Person person;
		person.create();

		Professor prof;
		prof.setPesel(person.getPesel());
		prof.setFName(person.getFName());
		prof.setLName(person.getLName());
		prof.setGender(person.getGender());
		prof.setDateOfBirth(person.getDateOfBirth());

		cout << "\nProfessorID: ";
		cin >> ti;

		if (ti > 99999 || ti < 10000)
			throw "Wrong number, professor ID has 5 digits!";
		for (int i = 0; i < p.size(); i++)
			if (p[i].getID() == ti)
				throw "Professor with this ID already exists!";

		prof.setID(ti);

		cout << "\nTitle: ";
		cin >> ts;
		prof.setTitle(ts);

		p.push_back(prof);
	}
	catch (const char* s) { cout << "Error! " << s << endl; }
}
void Administrative_Worker::createAdmWor(vector<Administrative_Worker>& a) {
	/*
	Method creates new administrative worker and puts him in vector of all administrative worker in the system.
	*/
	long int ti;
	string ts;
	try {
		Person person;
		person.create();

		Administrative_Worker admw;
		admw.setPesel(person.getPesel());
		admw.setFName(person.getFName());
		admw.setLName(person.getLName());
		admw.setGender(person.getGender());
		admw.setDateOfBirth(person.getDateOfBirth());
		
		cout << "\nAdministrative Workers' ID: ";
		cin >> ti;

		if (ti > 9999 || ti < 1000)
			throw "Wrong number, Administrative Worker's ID has 4 digits!";
		for (int i = 0; i < a.size(); i++)
			if (a[i].getID() == ti)
				throw "Administrative Worker with this ID already exists!";

		admw.setID(ti);

		cout << "\nTitle: ";
		cin >> ts;
		admw.setTitle(ts);

		a.push_back(admw);
	}
	catch (const char* s) { cout << "Error! " << s << endl; }
}
void Administrative_Worker::createCourse(vector<Course>& c) {
	/*
	Method creates new course and puts him in vector of all course in the system.
	*/
	int ti;
	string ts;
	Course course;
	try {
		cout << "Adding new course!\nCourse ID: ";
		cin >> ti;
		course.setCID(ti);

		for (int i = 0; i < c.size(); i++)
			if (c[i].getCID() == ti)
				throw "Course with such ID already exists.";

		cout << "\nName: ";
		cin >> ts;
		course.setName(ts);

		cout << "\nExam date: ";
		cin >> ts;
		course.setExamDate(ts);
		c.push_back(course);
	}
	catch (const char * s) { cout << s << endl; }
}
// UPDATE
void Administrative_Worker::update() {
	/*
	Method changes information about currently logged in administrative worker.
	*/
	int input;
	cout << "\n1. Change first name.\n2. Change last name.\n3. Change gender.\n4. Change title.\nInput: ";
	cin >> input;

	if (input >= 1 && input <= 3) {
		updatePerson(input);
	}
	if (input == 4) {
		string ts;
		cout << "\nNew title for Administrative Worker with ID " << getID() << " is: ";
		cin >> ts;
		setTitle(ts);
	}
}
void Administrative_Worker::updateAccount(vector<Student>& s, vector<Professor>& p, vector<Administrative_Worker>& a, vector<Course>& c, vector<Enrolled>& e) {
	/*
	Menu-method for choosing the type of account to be updated.
	*/
	int input;
	cout << "1. Update student.\n2. Update professor.\n3. Update administrative worker.\n4. Update course.\nInput: ";
	cin >> input;

	if (input == 1) {
		updateStudent(s);
	}
	if (input == 2) {
		updateProfessor(p);
	}
	if (input == 3) {
		updateAdmWor(a);
	}
	if (input == 4) {
		updateCourse(c, p);
	}
}
void Administrative_Worker::updateStudent(vector<Student>& vec) {
	/*
	Method gets ID and changes information about student with such.
	*/
	int x;
	cout << "ID of a student you want to update: ";
	cin >> x;
	for (int i = 0; i < vec.size(); i++)
		if (vec[i].getID() == x)
			vec[i].update();
}
void Administrative_Worker::updateProfessor(vector<Professor>& vec) {
	/*
	Method gets ID and changes information about professor with such.
	*/
	int x;
	cout << "ID of a student you want to update: ";
	cin >> x;
	for (int i = 0; i < vec.size(); i++)
		if (vec[i].getID() == x)
			vec[i].update();
}
void Administrative_Worker::updateAdmWor(vector<Administrative_Worker>& vec) {
	/*
	Method gets ID and changes information about administrative worker with such.
	*/
	int x;
	cout << "ID of a student you want to update: ";
	cin >> x;
	for (int i = 0; i < vec.size(); i++)
		if (vec[i].getID() == x)
			vec[i].update();
}
void Administrative_Worker::updateCourse(vector<Course>& vec, vector<Professor>& p) {
	/*
	Method gets ID and changes information about course with such.
	*/
	int x;
	cout << "ID of a student you want to update: ";
	cin >> x;
	for (int i = 0; i < vec.size(); i++)
		if (vec[i].getCID() == x)
			vec[i].update(p);
}
// DELETE
void Administrative_Worker::deleteAccount(vector<Student>& s, vector<Professor>& p, vector<Administrative_Worker>& a, vector<Course>& c, vector<Enrolled>& e) {
	/*
	Menu-method for choosing the type of account to be deleted.
	*/
	int input;
	cout << "1. Delete student.\n2. Delete professor.\n3. Delete administrative worker.\n4. Delete course.\nInput: ";
	cin >> input;

	if (input == 1) {
		deleteStudent(s);
	}
	if (input == 2) {
		deleteProfessor(p);
	}
	if (input == 3) {
		deleteAdmWor(a);
	}
	if (input == 4) {
		deleteCourse(c);
	}
}
void Administrative_Worker::deleteStudent(vector<Student>& vec) {
	/*
	Method gets ID and deletes student with such.
	*/
	int x;
	cout << "ID of a student you want to delete: ";
	cin >> x;
	for (int i = 0; i<vec.size(); i++)
		if (vec[i].getID() == x)
			vec.erase(vec.begin() + i);
}
void Administrative_Worker::deleteProfessor(vector<Professor>& vec) {
	/*
	Method gets ID and deletes professor with such.
	*/
	int x;
	cout << "ID of a professor you want to delete: ";
	cin >> x;
	for (int i = 0; i<vec.size(); i++)
		if (vec[i].getID() == x)
			vec.erase(vec.begin() + i);
}
void Administrative_Worker::deleteAdmWor(vector<Administrative_Worker>& vec) {
	/*
	Method gets ID and deletes administrative worker with such.
	*/
	int x;
	cout << "ID of a administrative worker you want to delete: ";
	cin >> x;
	for (int i = 0; i<vec.size(); i++)
		if (vec[i].getID() == x)
			vec.erase(vec.begin() + i);
}
void Administrative_Worker::deleteCourse(vector<Course>& vec) {
	/*
	Method gets ID and deletes course with such.
	*/
	int x;
	cout << "ID of a course you want to delete: ";
	cin >> x;
	for (int i = 0; i<vec.size(); i++)
		if (vec[i].getCID() == x)
			vec.erase(vec.begin() + i);
}
// LOGIN
void Administrative_Worker::logged(vector<Student>& s, vector<Professor>& p, vector<Administrative_Worker>& a, vector<Course>& c, vector<Enrolled>& e) {
	/*
	Mehtod is a type of a menu.
	Displayed when administrative worker logs in successfully.
	*/
	int input;
	system("pause");
	system("cls");
	cout << "Logged as administrative workers with ID: " << getID() << endl;
	cout << "1. Show my info.\n2. Create new account or a course.\n3. Show account or a course.\n4. Update account or a course.\n5. Delete account or a course.\n6. Logout\n7. Exit.\nInput: ";
	cin >> input;
	if (input == 1) {
		showAW();
	}
	if (input == 2) {
		createAccount(s, p, a, c, e);
	}
	if (input == 3) {
		showAccount(s, p, a, c, e);
	}
	if (input == 4) {
		updateAccount(s, p, a, c, e);
	}
	if (input == 5) {
		deleteAccount(s, p, a, c, e);
	}
	if (input == 6) {
		menu m;
		m.login(s, p, a, c, e);
	}
	if (input == 7) {
		exit(0);
	}
	cout << endl << endl;
	system("pause");
	logged(s, p, a, c, e);
}
// ---------------------------- COURSE METHODS ----------------------------------
Course::Course(){ // constructor
    CourseID = 0;
    name = "No_name";
    examDate = "00.00.0000";
    pID = 9999;
}
Course::~Course(){} 
// SETTERS
void Course::setCID(int x) {
	CourseID = x;
}
void Course::setPID(int x) {
	pID = x;
}
void Course::setName(string x) {
	name = x;
}
void Course::setExamDate(string x) {
	examDate = x;
}
// GETTERS
int Course::getCID() {
	return CourseID;
}
int Course::getPID() {
	return pID;
}
string Course::getName() {
	return name;
}
string Course::getExamDate() {
	return examDate;
}
// DATABASE
void Course::load(vector<Course>& c){
    fstream couDB;
	couDB.open("database/Courses.txt",ios::in);

    if(couDB.good()==false){
        cout<<"Cannot open courses database!";
        exit(0);
    }


	string line;
	for (int i = 0; i < 4; i++)
		couDB >> line;
	Course co;
	while (!couDB.eof()) {
		couDB >> line;
		co.CourseID = atoll(line.c_str());
		couDB >> co.name;
		couDB >> line;
		co.pID = atoll(line.c_str());
		couDB >> co.examDate;

		c.push_back(co);
	}
	c.pop_back();
	couDB.close();
}
void Course::generate(vector<Course>& vec, int howMany, vector<Professor>& p) {
	if (howMany > 899) howMany = 899;
	

	Course cour;
	int y, m, d, sid = 100;
	string temp;
	srand(time(NULL));
	for (int i = 0; i < howMany; i++) {

		y = 2017;
		m = rand() % 12 + 1;
		if (m == 2) {
			if (y % 4) d = rand() % 28 + 1;
			else d = rand() % 29 + 1;
		}
		else if (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12) d = rand() % 31 + 1;
		else d = rand() % 30 + 1;

		if (d < 10) temp.append(to_string(0));
		temp.append(to_string(d));
		temp.append(".");
		if (m < 10) temp.append(to_string(0));
		temp.append(to_string(m));
		temp.append(".");
		temp.append(to_string(y));
		cour.setExamDate(temp);
		temp.clear();

		cour.setCID(sid++);
		if (p.size() > 0) 
			cour.setPID(p[rand() % p.size()].getID());

		vec.push_back(cour);

	}
}
void Course::save(vector<Course>& vec) {
	ofstream file;
	file.open("database/Courses.txt");

	int size = vec.size();
	file << "CourseID\tName\t\t\t\t\tpID\tExam_date\n" << endl;
	for (int i = 0; i < size; i++) {
		file << vec[i].CourseID << "\t\t" << vec[i].name << "\t";
		if (vec[i].name.length() < 32) file << "\t";
		if (vec[i].name.length() < 24) file << "\t";
		if (vec[i].name.length() < 16) file << "\t";
		if (vec[i].name.length() < 8) file << "\t";
		file << vec[i].pID << "\t" << vec[i].examDate << endl;
	}
	file.close();
}
// SHOW
void Course::showCourse(){
    cout << CourseID << "\t\t" << name << "\t";
    if(name.length() < 32) cout << "\t";
    if(name.length() < 24) cout << "\t";
    if(name.length() < 16) cout << "\t";
    if(name.length() < 8) cout << "\t";
    cout << pID << "\t" << examDate << endl;
}
void Course::showCourse(vector<Course>& vec) {
	int size = vec.size();
	cout << "CourseID\tSemester\tName\t\t\t\t\tpID\tExam date" << endl;
	for (int i = 0; i < size; i++) {
		cout << vec[i].CourseID << "\t\t" << vec[i].name << "\t";
		if (vec[i].name.length() < 32) cout << "\t";
		if (vec[i].name.length() < 24) cout << "\t";
		if (vec[i].name.length() < 16) cout << "\t";
		if (vec[i].name.length() < 8) cout << "\t";
		cout << vec[i].pID << "\t" << vec[i].examDate << endl;
	}
}
// ASSIGN PROFESSOR
void Course::assignProf(vector<Course>& c, vector<Professor>& p) {
	for (int i = 0; i < c.size(); i++)
		c[i].setPID(p[i%p.size()].getID());
}
void Course::assignProf(vector<Professor>& p, int x) {
	for (int i = 0; i < p.size(); i++) {
		if (p[i].getID() == x) {
			setPID(x);
			return;
		}
	}
	cout << "\n\nError! Professor with that ID doesn't exist!\n\n";
}
// LOGIN
void Course::update(vector<Professor>& p) {
	int input;
	string ts;
	cout << "\n1. Change name.\n2. Change course professor.\n3. Change exam date.\nInput: ";
	cin >> input;

	if (input == 1) {
		cout << "\nNew name for course with ID " << getCID() << " is: ";
		cin >> ts;
		setName(ts);
	}
	if (input == 2) {
		cout << "\nNew professor for course with ID " << getCID() << " has ID: ";
		cin >> input;
		assignProf(p, input);
	}
	if (input == 3) {
		cout << "\nNew exam date for course with ID " << getCID() << " is: ";
		cin >> ts;
		setExamDate(ts);
	}
}

// ---------------------------- ENROLLED METHODS ---------------------------------
Enrolled::Enrolled(){
    CourseID = 0;
    ID = 0;
    grade = 0;
}
Enrolled::~Enrolled(){}
// SETTERS
void Enrolled::setCourseID(int x) {
	CourseID = x;
}
void Enrolled::setStudID(long int x) {
	ID = x;
}
void Enrolled::setGrade(float x) {
	grade = x;
}
// GETTERS
int Enrolled::getCID() {
	return CourseID;
}
long int Enrolled::getStudID() {
	return ID;
}
float Enrolled::getGrade() {
	return grade;
}
// DATABASE
void Enrolled::load(vector<Enrolled>& vec) {
	fstream file;
	file.open("database/Enrolled.txt", ios::in);

	if (file.good() == false) {
		cout << "Cannot open courses database!";
		exit(0);
	}


	string line;
	for (int i = 0; i < 3; i++) file >> line;
	Enrolled enrl;
	while (!file.eof()) {
		file >> line;
		enrl.CourseID = atoll(line.c_str());
		file >> line;
		enrl.ID = atoll(line.c_str());
		file >> line;
		enrl.grade = atoll(line.c_str());

		vec.push_back(enrl);
	}
	vec.pop_back();
	file.close();
}
void Enrolled::generate(vector<Student>& s, vector<Course>& c, vector<Enrolled>& e) {
	srand(time(NULL));
	int CID, x1, x2, x3;
	long int SID;
	int grade;
	Enrolled enrl;
	int ratio = s.size()/50;
	for (int i = 0; i<c.size(); i++) {
		CID = c[i].getCID();
		x1 = rand() % ratio + 15;
		x3 = rand() % s.size();
		for (int j = 0; j < x1; j++) {
			x3 += (rand() % 5 + 1);
			SID = s[x3 % s.size()].getID();
			grade = (rand() % 5 + 6) / 2;
			enrl.setCourseID(CID);
			enrl.setStudID(SID);
			enrl.setGrade(grade);
			e.push_back(enrl);
		}
	}
}
void Enrolled::save(vector<Enrolled>& vec) {
	ofstream file;
	file.open("database/Enrolled.txt");

	int size = vec.size();
	file << "CourseID\tStudentID\t\Grade\n" << endl;
	for (int i = 0; i < size; i++) {
		file << vec[i].CourseID << "\t\t" << vec[i].ID << "\t\t" << vec[i].grade << endl;
	}

	file.close();
}
// SHOW
void Enrolled::showEnrolled(vector<Enrolled>& vec){
	int size = vec.size();
	cout << "CourseID\tStudentID\t\Grade\n" << endl;
	for (int i = 0; i < size; i++) {
		cout << vec[i].CourseID << "\t\t" << vec[i].ID << "\t\t" << vec[i].grade << endl;
	}
}

// ---------------------------- MENU METHODS ---------------------------------
menu::menu(){}
menu::~menu(){}

int menu::intInput() {
	// Function checks if an input is a number. If yes then returns it.
	string s;
	cin >> s;
	if (all_of(s.begin(), s.end(), ::isdigit))
		return stoi(s);
	else cout << "\n\nGiven input is not a number! Enter a number!\n\nInput: ";
	intInput();
}
void menu::loadDatabase(vector<Student>& s, vector<Professor>& p, vector<Administrative_Worker>& a, vector<Course>& c, vector<Enrolled>& e) {

	Student stud;
	Professor prof;
	Administrative_Worker adm_worker;
	Course course;
	Enrolled enrl;

	stud.load(s);
	prof.load(p);
	adm_worker.load(a);
	course.load(c);
	enrl.load(e);

	cout << "Loaded " << s.size() << " students.\n";
	cout << "Loaded " << p.size() << " professors.\n";
	cout << "Loaded " << a.size() << " administrative workers.\n";
	cout << "Loaded " << c.size() << " courses.\n";
	cout << "Loaded " << e.size() << " enrolled pairs.\n" << endl;
	system("pause");
}
void menu::generateAll(vector<Student>& s, vector<Professor>& p, vector<Administrative_Worker>& a, vector<Course>& c, vector<Enrolled>& e, unsigned int howMany) {
	Student stud;
	Professor prof;
	Administrative_Worker adw;
	Course course;
	Enrolled enrl;
	if (howMany > 1000000) howMany = 1000000;
	if (howMany < 100) howMany = 100;
	stud.generate(s, howMany);
	prof.generate(p, howMany/16);
	adw.generate(a, howMany/100);
	course.generate(c, 700, p);
	enrl.generate(s, c, e);
}
void menu::saveAll(vector<Student>& s, vector<Professor>& p, vector<Administrative_Worker>& a, vector<Course>& c, vector<Enrolled>& e) {
	s[0].save(s);
	p[0].save(p);
	a[0].save(a);
	c[0].save(c);
	e[0].save(e);

}
void menu::login(vector<Student>& s, vector<Professor>& p, vector<Administrative_Worker>& a, vector<Course>& c, vector<Enrolled>& e) {
	system("cls");
	cout << "Hi! Welcome to Univesrity Management System?\nLogin: ";
	long int input = 0, i;
	bool test = true;
	string sinput;

	cin >> sinput;
	int n = sinput.size()-1;
	while (n--) {
		if (!isdigit(sinput[n])) {
			test = false;
			login(s, p, a, c, e);
		}
	}

	if (sinput.size() > 3  && sinput.size() < 7 && test) input = stoi(sinput);
	else login(s, p, a, c, e);
	test = false;
	if (input >= 100000 && input < 1000000) {
		for (i = 0; i < s.size(); i++) {
			if (s[i].getID() == input) {
				test = true;
				break;
			}
		}
		if (test) {
			Student stud = s[i];
			stud.logged(s,p,a,c,e);
		}
		else login(s, p, a, c, e);
	}
	else if (input > 10000) {
		for (i = 0; i < p.size(); i++) {
			if (p[i].getID() == input) {
				test = true;
				break;
			}
		}
		if (test) {
			Professor prof = p[i];
			prof.logged(s, p, a, c, e);
		}
		else login(s, p, a, c, e);
	}
	else if (input > 1000) {
		for (i = 0; i < a.size(); i++) {
			if (a[i].getID() == input) {
				test = true;
				break;
			}
		}
		if (test) {
			Administrative_Worker aw = a[i];
			aw.logged(s, p, a, c, e);
		}
		else login(s, p, a, c, e);
	}
	else login(s,p,a,c,e);
}

/* * /

void menu::addStud(){

}

ostringstream stream;
stream << ti << "@student.email.com";
ts = stream.str();
stud.setsEmail(ts);
s.push_back(stud);
}
void menu::addProf(){


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
void menu::addAW(){


string ts;
long long int ti;
cout << "\n\nAdding new professor.\n\nPESEL: ";
cin >> ti;

try {
if (ti < 10000000000){
throw "Wrong pesel format!";
}
adm_worker.setPesel(ti);
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
adm_worker.setFName(ts);
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
adm_worker.setLName(ts);
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
adm_worker.setJobTitle(ts);
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
adm_worker.setGender(ts);
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
adm_worker.setDateOfBirth(ts);
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
adm_worker.setAWID(ti);
} catch (const char* msg) {
cerr << msg << endl;
return;
}

ostringstream stream;
stream << ti << "@aw.email.com";
ts = stream.str();
adm_worker.setawEmail(ts);
aw.push_back(adm_worker);
}
void menu::addCourse(){

string ts;
long long int ti;
cout << "\n\nAdding new course.\n\nSemester: ";
cin >> ti;
course.setCID(c.size()+101);
try {
if (ti > 10){
throw "There is no such semester (1-10)!";
}
course.setSemester(ti);
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
course.setName(ts);
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
course.setExamDate(ts);
} catch (const char* msg) {
cerr << msg << endl;
return;
}

c.push_back(course);
}
void menu::deleteStud(){

}
void menu::select(){
//char* word[];
int x;
string s1,s2;
cout << "From which table: \n1. Students\n2. Professors\n3. Administrative workers\n4. Courses\n\nYour choice: ";
cin >> x;
if (x==1){

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

if (s1 == "Fname=Katie"){
cout <<"\n\nPESEL\t\tFirst name\tLast name\tGender\tDate of birth\tStudentID\tEmail"<<endl;

for(int i=0; i<s.size(); i++){
if(s[i].getFName() == "Katie") s[i].showStud();
}
cout << endl << endl;
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
void menu::showStudSorted(){
//std::sort(s.begin(), s.end(), )
}
void menu::menuStud(int ID){
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

}
else if(x==3){
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
void menu::menuProf(int ID){
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
void menu::menuAW(int ID){
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
void menu::login(){
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
/* */