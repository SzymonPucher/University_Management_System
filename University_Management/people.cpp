#include "people.h"



using namespace std;

 // --------------------------------------- PERSON METHODS ------------------------------------------
Person::Person(){ 
    pesel = 11111111111;
    fName = "No Fname";
    lName = "No Lname";
    gender = "Male";
    dateOfBirth = "00.00.0000";
}
Person::~Person(){} 

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
long long int Person::getPesel(){
    return pesel;
}
string Person::getFName(){
    return fName;
}
string Person::getLName(){
    return lName;
}
string Person::getDateOfBirth(){
    return dateOfBirth;
}
string Person::getGender(){
    return gender;
}
 // --------------------------------------- STUDENT METHODS ------------------------------------------
Student::Student(){ // constructor;
    StudentID = 0;
    sEmail = "0@student.email.com";
	//vector<Course*> coursesTaken(10);
	Course* ct;
}
Student::~Student(){}

void Student::load(vector<Student>& s){
	fstream studDB;
	studDB.open("database/Students.txt",ios::in);

    if(studDB.good()==false){
        cout<<"Cannot open students database!";
        exit(0);
    }
	string line;
	for(int i = 0; i < 7; i++)
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
		stud.StudentID = atoi(line.c_str());
		studDB >> stud.sEmail;
		
		s.push_back(stud);
	}
	s.pop_back();

	studDB.close();
}
void Student::generate(vector<Student>& s, int howMany) {
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

		stud.setStudentID(sid);
		temp = to_string(sid++);
		temp.append("@student.email.com");
		stud.setsEmail(temp);
		temp.clear();



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
	ofstream file;
	file.open("database/Students.txt");
	
	file << "PESEL\t\tFirst_name\tLast_name\tGender\t\tDate_of_birth\tStudentID\tEmail\n" << endl;
	int size = vec.size();
	
	for (int i = 0; i < size; i++) {
		file << vec[i].pesel << "\t" << vec[i].fName << "\t";
		if (vec[i].fName.length() < 8) file << "\t";
		file << vec[i].lName << "\t";
		if (vec[i].lName.length() < 8) file << "\t";
		file << vec[i].gender << "\t\t" << vec[i].dateOfBirth << "\t" << vec[i].StudentID << "\t\t" << vec[i].sEmail << endl;
	}
	file.close();
}
void Student::showStud(vector<Student>& vec){
	int size = vec.size();
	cout << "\n\nPESEL\t\tFirst name\tLast name\tGender\tDate of birth\tStudentID\tEmail" << endl;
	for (int i = 0; i < size; i++) {
		cout << vec[i].pesel << "\t" << vec[i].fName << "\t";
		if (vec[i].fName.length() < 8) cout << "\t";
		cout << vec[i].lName << "\t";
		if (vec[i].lName.length() < 8) cout << "\t";
		cout << vec[i].gender << "\t" << vec[i].dateOfBirth << "\t" << vec[i].StudentID << "\t\t" << vec[i].sEmail << endl;
	}
}
void Student::setStudentID(long int x){
    StudentID = x;
}
void Student::setsEmail(string x){
    sEmail = x;
}
long int Student::getStudentID(){
    return StudentID;
}
string Student::getsEmail(){
    return sEmail;
}
// --------------------------------- PROFESSOR METHODS -----------------------------
Professor::Professor(){ // constructor
    ProfessorID = 0;
    pEmail = "0@professor.email.com";
}
Professor::~Professor(){} // destructor

void Professor::load(vector<Professor>& p){
    fstream profDB;
	profDB.open("database/Professors.txt",ios::in);

    if(profDB.good()==false){
        cout<<"Cannot open professors database!";
        exit(0);
    }


    string line;
	for (int i = 0; i < 8; i++)
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
		prof.ProfessorID = atoi(line.c_str());
		profDB >> prof.pEmail;

		p.push_back(prof);
	}
	p.pop_back();
	profDB.close();
}
void Professor::generate(vector<Professor>& vec, int howMany) {
	if (howMany > 8990) howMany = 8990;
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

	Professor prof;
	int y, m, d, pes5dig, sid = 1000;
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

		prof.setProfessorID(sid);
		temp = to_string(sid++);
		temp.append("@professor.email.com");
		prof.setpEmail(temp);
		temp.clear();

		prof.setTitle("No title");

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
	ofstream file;
	file.open("database/Professors.txt");

	int size = vec.size();
	file << "PESEL\t\tTitle\t\t\tFirst_name\tLast_name\tGender\t\tDate_of_birth\tProfessorID\tEmail\n" << endl;
	for (int i = 0; i < size; i++) {
		file << vec[i].pesel << "\t" << vec[i].title << "\t";
		if (vec[i].title.length() < 16) file << "\t";
		if (vec[i].title.length() < 8) file << "\t";
		file << vec[i].fName << "\t";
		if (vec[i].fName.length() < 8) file << "\t";
		file << vec[i].lName << "\t";
		if (vec[i].lName.length() < 8) file << "\t";
		file << vec[i].gender << "\t\t" << vec[i].dateOfBirth << "\t" << vec[i].ProfessorID << "\t\t" << vec[i].pEmail << endl;
	}
	file.close();
}
void Professor::showProf(vector<Professor>& vec){
	int size = vec.size();
	cout << "PESEL\t\tTitle\t\t\tFirst name\tLast name\tGender\tDate of birth\tProfessorID\tEmail" << endl;
	for (int i = 0; i < size; i++) {
		cout << vec[i].pesel << "\t" << vec[i].title << "\t";
		if (vec[i].title.length() < 16) cout << "\t";
		if (vec[i].title.length() < 8) cout << "\t";
		cout << vec[i].fName << "\t";
		if (vec[i].fName.length() < 8) cout << "\t";
		cout << vec[i].lName << "\t";
		if (vec[i].lName.length() < 8) cout << "\t";
		cout << vec[i].gender << "\t" << vec[i].dateOfBirth << "\t" << vec[i].ProfessorID << "\t\t" << vec[i].pEmail << endl;
	}
}
void Professor::setProfessorID(long int x){
    ProfessorID = x;
}
void Professor::setpEmail(string x){
    pEmail = x;
}
void Professor::setTitle(string x){
    title = x;
}
long int Professor::getProfessorID(){
    return ProfessorID;
}
string Professor::getpEmail(){
    return pEmail;
}
string Professor::getTitle(){
    return title;
}
// ----------------------------- ADMINISTRATIVE WORKERS ----------------------------
Administrative_Worker::Administrative_Worker(){ // constructor
    AWID = 0;
    awEmail = "0@aw.email.com";
}
Administrative_Worker::~Administrative_Worker(){} // destructor

void Administrative_Worker::load(vector<Administrative_Worker>& a){
    fstream aw;
    aw.open("database/Administrative_Workers.txt",ios::in);

    if(aw.good()==false){
        cout<<"Cannot open administrative workers database!";
        exit(0);
    }


    string line;
	Administrative_Worker awork;
	for (int i = 0; i < 8; i++)
		aw >> line;
	while (!aw.eof()) {
		aw >> line;
		awork.pesel = atoll(line.c_str());
		aw >> awork.jobTitle;
		aw >> awork.fName;
		aw >> awork.lName;
		aw >> awork.gender;
		aw >> awork.dateOfBirth;
		aw >> line;
		awork.AWID = atoi(line.c_str());
		aw >> awork.awEmail;

		a.push_back(awork);
	}
	a.pop_back();
    aw.close();
}
void Administrative_Worker::generate(vector<Administrative_Worker>& vec, int howMany) {
	if (howMany > 89900) howMany = 89900;
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

	Administrative_Worker aw;
	int y, m, d, pes5dig, sid = 10000;
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

		aw.setAWID(sid);
		temp = to_string(sid++);
		temp.append("@aw.email.com");
		aw.setawEmail(temp);
		temp.clear();

		aw.setJobTitle("No title");

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
	ofstream file;
	file.open("database/Administrative_Workers.txt");

	int size = vec.size();
	file << "PESEL\t\tJob_Title\t\tFirst_name\tLast_name\tGender\t\tDate_of_birth\tAWID\t\tEmail\n" << endl;
	for (int i = 0; i < size; i++) {
		file << vec[i].pesel << "\t" << vec[i].jobTitle << "\t";
		if (vec[i].jobTitle.length() < 16) file << "\t";
		if (vec[i].jobTitle.length() < 8) file << "\t";
		file << vec[i].fName << "\t";
		if (vec[i].fName.length() < 8) file << "\t";
		file << vec[i].lName << "\t";
		if (vec[i].lName.length() < 8) file << "\t";
		file << vec[i].gender << "\t\t" << vec[i].dateOfBirth << "\t" << vec[i].AWID << "\t\t" << vec[i].awEmail << endl;
	}
	file.close();
}
void Administrative_Worker::showAW(vector<Administrative_Worker>& vec){
	int size = vec.size();
	cout << "PESEL\t\tJob Title\t\tFirst name\tLast name\tGender\tDate of birth\tAdm. Worker ID\tEmail" << endl;
	for (int i = 0; i < size; i++) {
		cout << vec[i].pesel << "\t" << vec[i].jobTitle << "\t";
		if (vec[i].jobTitle.length() < 16) cout << "\t";
		if (vec[i].jobTitle.length() < 8) cout << "\t";
		cout << vec[i].fName << "\t";
		if (vec[i].fName.length() < 8) cout << "\t";
		cout << vec[i].lName << "\t";
		if (vec[i].lName.length() < 8) cout << "\t";
		cout << vec[i].gender << "\t" << vec[i].dateOfBirth << "\t" << vec[i].AWID << "\t\t" << vec[i].awEmail << endl;
	}
}
void Administrative_Worker::setAWID(long int x){
    AWID = x;
}
void Administrative_Worker::setawEmail(string x){
    awEmail = x;
}
void Administrative_Worker::setJobTitle(string x){
    jobTitle = x;
}
long int Administrative_Worker::getAWID(){
    return AWID;
}
string Administrative_Worker::getawEmail(){
    return awEmail;
}
string Administrative_Worker::getJobTitle(){
    return jobTitle;
}
// ---------------------------- COURSE METHODS ----------------------------------
Course::Course(){ // constructor
    semester = 0;
    CourseID = 0;
    name = "Nie wybrano nazwy kursu";
    examDate = "00.00.0000";
    pID = 1000;
}
Course::~Course(){} 

void Course::load(vector<Course>& c){
    fstream couDB;
	couDB.open("database/Courses.txt",ios::in);

    if(couDB.good()==false){
        cout<<"Cannot open courses database!";
        exit(0);
    }


	string line;
	for (int i = 0; i < 5; i++)
		couDB >> line;
	Course co;
	while (!couDB.eof()) {
		couDB >> line;
		co.CourseID = atoll(line.c_str());
		couDB >> line;
		co.semester = atoll(line.c_str());
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
		cour.setSemester(rand()%10+1);
		if (p.size() > 0) 
			cour.setPID(p[rand() % p.size()].getProfessorID());

		vec.push_back(cour);

	}
}
void Course::save(vector<Course>& vec) {
	ofstream file;
	file.open("database/Courses.txt");

	int size = vec.size();
	file << "CourseID\tSemester\tName\t\t\t\t\tpID\tExam_date\n" << endl;
	for (int i = 0; i < size; i++) {
		file << vec[i].CourseID << "\t\t" << vec[i].semester << "\t\t" << vec[i].name << "\t";
		if (vec[i].name.length() < 32) file << "\t";
		if (vec[i].name.length() < 24) file << "\t";
		if (vec[i].name.length() < 16) file << "\t";
		if (vec[i].name.length() < 8) file << "\t";
		file << vec[i].pID << "\t" << vec[i].examDate << endl;
	}
	file.close();
}
void Course::showCourse(){
    cout << CourseID << "\t\t" << semester << "\t\t" << name << "\t";
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
		cout << vec[i].CourseID << "\t\t" << vec[i].semester << "\t\t" << vec[i].name << "\t";
		if (vec[i].name.length() < 32) cout << "\t";
		if (vec[i].name.length() < 24) cout << "\t";
		if (vec[i].name.length() < 16) cout << "\t";
		if (vec[i].name.length() < 8) cout << "\t";
		cout << vec[i].pID << "\t" << vec[i].examDate << endl;
	}
}
void Course::setCID(int x){
    CourseID = x;
}
void Course::setPID(int x){
    pID = x;
}
void Course::setSemester(int x){
    semester = x;
}
void Course::setName(string x){
    name = x;
}
void Course::setExamDate(string x){
    examDate = x;
}
int Course::getCID(){
    return CourseID;
}
int Course::getPID(){
    return pID;
}
int Course::getSemester(){
    return semester;
}
string Course::getName(){
    return name;
}
string Course::getExamDate(){
    return examDate;
}
void Course::assignProf(vector<Course>& c, vector<Professor>& p) {
	for (int i = 0; i < c.size(); i++)
		c[i].setPID(p[i%p.size()].getProfessorID());
}
// ---------------------------- ENROLLED METHODS ---------------------------------
Enrolled::Enrolled(){
    CourseID = 0;
    StudentID = 100000;
    grade = 3;
}
Enrolled::~Enrolled(){}

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
		enrl.StudentID = atoll(line.c_str());
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
	for (int i = 0; i<c.size(); i++) {
		CID = c[i].getCID();
		x1 = rand() % 100 + 15;
		x3 = rand() % s.size();
		for (int j = 0; j < x1; j++) {
			x3 += (rand() % 5 + 1);
			SID = s[x3 % s.size()].getStudentID();
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
		file << vec[i].CourseID << "\t\t" << vec[i].StudentID << "\t\t" << vec[i].grade << endl;
	}

	file.close();
}
void Enrolled::showEnrolled(vector<Enrolled>& vec){
	int size = vec.size();
	cout << "CourseID\tStudentID\t\Grade\n" << endl;
	for (int i = 0; i < size; i++) {
		cout << vec[i].CourseID << "\t\t" << vec[i].StudentID << "\t\t" << vec[i].grade << endl;
	}
}
void Enrolled::setCourseID(int x){
    CourseID = x;
}
void Enrolled::setStudID(long int x){
    StudentID = x;
}
void Enrolled::setGrade(float x){
    grade = x;
}
int Enrolled::getCID(){
    return CourseID;
}
long int Enrolled::getStudID(){
    return StudentID;
}
float Enrolled::getGrade(){
    return grade;
}
// ---------------------------- MENU METHODS ---------------------------------
menu::menu(){}
menu::~menu(){}

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

	cout << "\nLoaded " << s.size() << " students.\n";
	cout << "Loaded " << p.size() << " professors.\n";
	cout << "Loaded " << a.size() << " administrative workers.\n";
	cout << "Loaded " << c.size() << " courses.\n";
}
void menu::gen(vector<Student>& vec) {
	ofstream file;
	file.open("database/generatorDB/First_names_male.txt");
	vector<string> vec2;
	bool test = true;
	int size = vec.size();
	for (int i = 0; i < size; i++) {
		test = true;
		if (vec[i].getGender() == "Female") continue;
		for (int j = 0; j < vec2.size(); j++)
			if (vec2[j] == vec[i].getFName()) test = false;
		if (test) {
			vec2.push_back(vec[i].getFName());
			cout << vec2[vec2.size() - 1] << endl;
		}
	}

	
	int size2 = vec2.size();
	sort(vec2.begin(), vec2.end());
	for (int i = 0; i < size2; i++) {
		file << vec2[i] << endl;
	}

	file.close();
}


/* * /
template <typename T> bool myMaxBool(T x, T y) {
return x > y;
}
void menu::addStud(){
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
int x;
cout << "Give me ID of a student you want to delete: ";
cin >> x;

for(int i=0; i<s.size();i++)
if(s[i].getStudentID() == x)
s.erase(s.begin() + i);
}
void menu::select(){
//char* word[];
int x;
string s1,s2;
cout << "From which table: \n1. Students\n2. Professors\n3. Administrative workers\n4. Courses\n\nYour choice: ";
cin >> x;
if (x==1){/* * /

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
}/* * /
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
cout <<"CourseID\tSemester\tName\t\t\t\t\tpID\tExam date"<<endl;
for(int i=0; i<c.size(); i++)
for(int j=0; j<e.size(); j++)
if(ID == e[j].getStudID() && c[i].getCID() == e[j].getCID())
c[i].showCourse();
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

*/