#include	<iostream>
#include	<cstdlib>
#include	<cstdio>
#include    <fstream>
#include	<iomanip>
#include    <string>
#include    <sstream>
#include	"List.h"
#include    "LibStudent.h"
#include    "LibBook.h"

#define MAX_CHOOSE 9
#define ID_LENGTH 7
#define ID_MIN 1000000
#define ID_MAX 9999999
#define JUDIAN_DAY 29;
#define JUDIAN_MONTH 3;
#define JUDIAN_YEAR 2020;
using namespace std;

bool ReadFile(string, List*);
bool DeleteRecord(List*, char*);
bool Display(List *, int, int);
bool InsertBook(string, List*);
bool SearchStudent(List*, char* id, LibStudent&);
bool updateStudent(List* list, LibStudent& stu);
bool computeAndDisplayStatistics(List*);
bool printStuWithSameBook(List*, char*);
bool displayWarnedStudent(List*, List*, List*);

void menu(int*);
bool readBookFile(List *, string filename);
double calculateFine(LibBook& book);
bool isInt(string& input);
int getInputInRange(int minRange, int maxRange);
void split(const string& string1, string arr1[]);
int days_in_month(int month, int year);
int leap(int year);
bool isDuplicateID(List*, string);

int main() {
	int choose;
	bool exit = false;
	List stdList;
	string stuId;
	menu(&choose);
	int stuID;
	char stuIDStr[8];
	LibStudent stu;
	string bookId;
	List type1;
	List type2;


	while (!exit) {
		switch (choose) {
		case 1:
			//Guan Yuan (done)
			system("cls");
			cout << "Read File" << endl;
			if (!ReadFile("student.txt", &stdList))
				cout << "Read file can't open!\n";
			menu(&choose);
			break;
		case 2:
			//Guan Yuan (done)
			system("cls");
			cout << "Delete record" << endl;
			cout << "Please give the student ID" << endl;
			stuID = getInputInRange(ID_MIN, ID_MAX);
			if (DeleteRecord(&stdList, &(to_string(stuID)[0]))) {
				cout << "Successfully Deleted!\n";
			}
			menu(&choose);
			break;
		case 3:
			//Ethan (done)
			system("cls");
			cout << "Search student" << endl;
			cout << "Please give the student ID" << endl;
			stuID = getInputInRange(ID_MIN, ID_MAX);
			if (SearchStudent(&stdList, &(to_string(stuID)[0]), stu)) {
				cout << "\nHere is the student with ID " << stuID;
				stu.print(cout);
				cout << endl;
			}
			else {
				cout << "Student with ID " << stuID << " not found!" << endl;
			}
			menu(&choose);
			break;
		case 4:
			//Ethan in prograss
			system("cls");
			cout << "Insert book" << endl;
			InsertBook("book.txt", &stdList);
			menu(&choose);
			break;
		case 5:
			//Eng Yi in prograss
			system("cls");
			int source, detail;
			cout << "Displaying output..." << "\n\n";
			cout << "Where do you want to display the output (1 - File / 2 - Screen):"<<endl;
			source = getInputInRange(1, 2);
			cout << endl;
			cout << "Do you want to display book list for every student (1 - YES / 2 - NO):"<<endl;
			detail = getInputInRange(1, 2);
			if (!Display(&stdList, source, detail)) {
				cout << "There is no student and their history of borrow in record!" << endl;
			}
			menu(&choose);
			break;
		case 6:
			//Eng Yi in prograss
			system("cls");
			cout << "Compute and Display Statictics" << endl;
			computeAndDisplayStatistics(&stdList);
			menu(&choose);
			break;

		case 7:
			//Huan Qian in prograss
			
			system("cls");
			cout << "Please enter a book to Serach:";
			getline(cin, bookId);

			while (bookId.length() > 20 || bookId == "") {
				cout << "Please enter a correct book Id:";
				getline(cin, bookId);
			}
			printStuWithSameBook(&stdList, &bookId[0]);
			menu(&choose);

			break;

		case 8:
			//Huan Qian in prograss
			system("cls");
			cout << "Display Warned Student" << endl;
			cout << "================================================================" << endl;
			displayWarnedStudent(&stdList, &type1, &type2);
			menu(&choose);

			break;
		case 9:
			exit = true;
			break;
		default:
			exit = true;
			continue;
		}
	}


	cout << "\n\n";
	system("pause");
	return 0;
}


void menu(int* choose) {
	string selection[MAX_CHOOSE] = { "Read file","Delete record","Search student","Insert book","Display output","Compute and Display Statistics","Student with Same Book","Display Warned Student","Exit" };
	for (int i = 0; i < MAX_CHOOSE;i ++) {
		cout << i + 1 << "." << selection[i] << "\n";
	}
	*choose = getInputInRange(1, MAX_CHOOSE);
}

int getInputInRange(int minRange, int maxRange) {
	int input;
	string string_input;

	cout << "Please enter your choice from " << minRange << " to " << maxRange << ": ";
	getline(cin, string_input);

	while (true) {

		if(!isInt(string_input)) {  //convert to string so can check character by character, solving situation like "3j"
			cout << "Invalid input, please enter a valid integer: ";
		}
		else {
			input = stoi(string_input);  //convert to integer for range checking
			if (input >= minRange && input <= maxRange) {
				return input;
			}
			else {
				cout << "Invalid range, please enter integer from " << minRange << " to " << maxRange << ": ";
			}
		}
		getline(cin, string_input);
	}
	
}

bool ReadFile(string filename, List* list) {
	char s[256];
	ifstream read;
	string test;
	read.open(filename);
	LibStudent student;

	if (!read.is_open()) {
		cout << "The student.txt is not find!\n";
	}
	
	if (list->empty()) {
		while (!read.eof()) {
			for (int i = 0; i < 3; i++) read >> s;
			read >> student.id;
			cout << "Student Id:" << student.id << endl;

			for (int i = 0; i < 2; i++) read >> s;
			read >> student.name;
			read.getline(s, 256);
			strcat_s(student.name, s);

			for (int i = 0; i < 2; i++) read >> s;
			read >> student.course;

			for (int i = 0; i < 3; i++) read >> s;
			read >> student.phone_no;

			list->insert(student);
		}

	}
	else {
		while (!read.eof()) {
			while (!read.eof()) {
				for (int i = 0; i < 3; i++) read >> s;
				read >> student.id;

				for (int i = 0; i < 2; i++) read >> s;
				read >> student.name;
				read.getline(s, 256);
				strcat_s(student.name, s);

				for (int i = 0; i < 2; i++) read >> s;
				read >> student.course;

				for (int i = 0; i < 3; i++) read >> s;
				read >> student.phone_no;

				if (isDuplicateID(list, student.id)) {
					cout << "This student " << student.id << " is already in the list\n";
				}
				else {
					cout << "Student " << student.id << " has been created\n";
					list->insert(student);
				}
			}
		}
	}
	cout << "\nThe file has been readed!!\n\n";
	read.close();
	return true;
}

bool isDuplicateID(List *list, string id) {
	Node* cur = list->head;
	while (cur != nullptr) {
		if (cur->item.id == id) {
			return true;
		}
		cur = cur->next;
	}
	return false;
}

bool SearchStudent(List* list, char* id, LibStudent &stu) {
        Node* cur = list->head;
        while (cur != nullptr) {
            if (strcmp(cur->item.id,id)==0) {
                stu = cur->item; 
				cout << "\n";
                return true;
            }
            cur = cur->next;
        }
        return false;
}

bool readBookFile(List* list, string filename) {
	ifstream inputFile;
	inputFile.open(filename);
	if (!inputFile.is_open()) {
		cout << filename << " not found!" << endl;
		return false;
	}
	if (list->empty()) {
		if (!ReadFile("student.txt", list))
			cout << "There is no student in student.txt!\n";
	}
	LibStudent stu;
	LibBook book;
	string stuID, title, author, publisher, ISBN, yearPublished, callNum, borrow, due, temp;
	while (getline(inputFile, stuID, '\t')) {
		getline(inputFile, temp, ' ');
		getline(inputFile, author, ' ');
		getline(inputFile, title, ' ');
		getline(inputFile, publisher, ' ');
		getline(inputFile, ISBN, ' ');
		getline(inputFile, yearPublished, ' ');
		getline(inputFile, callNum, ' ');
		getline(inputFile, borrow, ' ');
		getline(inputFile, due);
		getline(inputFile, temp);
		getline(inputFile, temp);
		const char* tmp = &stuID[0];
		SearchStudent(list, (char*)tmp, stu);
		strcpy_s(book.title, (char*)title.c_str());
		strcpy_s(book.publisher, (char*)publisher.c_str());
		strcpy_s(book.ISBN, (char*)ISBN.c_str());
		strcpy_s(book.callNum, (char*)callNum.c_str());
		book.yearPublished = stoi(yearPublished);
		cout << yearPublished << endl;
		string datePart[3];
		Date date;
		split(borrow, datePart);
		book.borrow = Date(stoi(datePart[0]), stoi(datePart[1]), stoi(datePart[2]));
		split(due, datePart);
		book.due = Date(stoi(datePart[0]), stoi(datePart[1]), stoi(datePart[2]));
		string name[10];
		split(author, name);
		int i = 0;
		while (i < 10 && !name[i].empty()) {
			book.author[i] = new char[name[i].length() + 1];
			strcpy_s(book.author[i], name[i].length() + 1, name[i].c_str());
			cout << book.author[i] << endl;
			i++;
		}
		book.fine = calculateFine(book);
		cout << book.fine;
		stu.totalbook++;
		stu.book[stu.totalbook-1] = book;
		stu.calculateTotalFine();
		updateStudent(list, stu);
		stu.print(cout);
	}
	return true;
}

bool updateStudent(List* list, LibStudent& stu) {
	Node* cur = list->head;
	while (cur != nullptr) {
		if (cur->item.compareName2(stu)) {
			cur->item = stu;
			return true;
		}
		cur = cur->next;
		
	}
	return false; // Student not found
}

bool InsertBook(string filename, List* list) {
	ofstream outFile;
	outFile.open(filename);
	if (list->empty()) {
		cout << "Reading student info..." << endl;
		if (!ReadFile("student.txt", list)) {
			cout << "Quit Insertion" << endl;
		}
		readBookFile(list, filename);
	}
	LibStudent stu;
	LibBook book;
	string temp;
	int num;
	string borrow_date_part[3], due_date_part[3];
	cout << "Give the ID of the student you want to insert the book,\n";
	const char* stuID = &(to_string(getInputInRange(ID_MIN, ID_MAX))[0]);
	cout << stuID << endl;
	if (!SearchStudent(list, (char*)stuID, stu)) {
		cout << "Quit Insertion" << endl;
		return false;
	}
	cout << "Input book information(remember to replace space with '_'" << endl << "Book: ";
	cin >> book.title;
	cout << "The number of author(s): ";
	cin >> num;
	for (int i = 0; i < num; i++) {
		cout << "Authors " << i << ": ";
		cin >> book.author[i];
	}
	cout << "Publisher: ";
	cin >> book.publisher;
	cout << "ISBN: ";
	cin >> book.ISBN;
	cout << "Published year: " << endl;
	cin >> book.yearPublished;
	cout << "callNum: " << endl;
	cin >> book.callNum;
	cout << "borrow date(DD/MM/YYYY): ";
	cin >> temp;
	split(temp, borrow_date_part);
	book.borrow = Date(stoi(borrow_date_part[0]), stoi(borrow_date_part[1]), stoi(borrow_date_part[2]));
	cout << "due date(DD/MM/YYYY): ";
	cin >> temp;
	split(temp, due_date_part);
	book.due = Date(stoi(due_date_part[0]), stoi(due_date_part[1]), stoi(due_date_part[2]));
	stu.book[stu.totalbook] = book;
	stu.totalbook++;
	stu.calculateTotalFine();
	outFile << stuID << "\t " << book.title << " ";
	for (char* name : book.author) {
		outFile << name << "/";
	}
	outFile << book.publisher << " " << book.ISBN << " " << book.yearPublished << " " << book.callNum << " " << borrow_date_part[0] << "/" << borrow_date_part[1] << "/" << borrow_date_part[2]<< " " << due_date_part << "/"<<due_date_part<<"/"<<due_date_part<<endl;
	outFile.close();
	return true;
}

//no need & before array because array is passed as pointer
void split(const string& string1, string arr1[]) {
	if (string1.find('/')) {
		stringstream ss(string1);
		string token;
		int index = 0;

		while (getline(ss, token, '/')) { 
			arr1[index++] = token;
		}
	}
	else { 
		arr1[0] = string1;
	}
}

double calculateFine(LibBook &book) {
	    Date currentDate(29,3,2020);
		
		int dueDays = 0, currentDays=0;
		for (int i = 1; i <= book.due.month; i++) {
			dueDays += days_in_month(i, book.due.year);
		}
		for (int i = 2019; i <= book.due.year; i++) {
			dueDays += 365;
		}
		for (int i = 1; i <= currentDate.month; i++) {
			currentDays += days_in_month(i, currentDate.year);
		}
		for (int i = 2019; i <= currentDate.year; i++) {
			currentDays += 365;
		}

		int daysOverdue = currentDays+currentDate.day-dueDays+book.due.day;

		if (daysOverdue > 0)
			return book.fine = 0.50 * daysOverdue;
		
		return book.fine = 0.0;
}

int days_in_month(int month, int year) {

	int days = 0;

	if (month == 2) {
		days = 28 + leap(year);
	}
	else if (month == 4 || month == 6 || month == 9 || month == 11) {
		days = 30;
	}
	else {
		days = 31;
	}

	return days;
}

int leap(int year)
{
	if (year % 400 == 0)
		return 1;
	else if (year % 100 != 0 && year % 4 == 0)
		return 1;

	else
		return 0;
}

bool DeleteRecord(List* list, char* stuId) {

	Node* cur;
	cur = list->head;

	//check 
	if (list->empty()) {
		cout << "No shudent in the record!\n";
		return false;
	}

	//loop all the element in link list to find student
	for (int i = 1; i < list->size(); i++) {
		if (cur->item.id == static_cast<string>(stuId)) {
			list->remove(i);
			return true;
		}
		else
			cur = cur->next;
	}

	return false;
}

bool Display(List* list, int source, int detail) {
	//source determine where to print the output
	//detail determine what info to print
	LibStudent stu;
	
	//list is a pointer for list, we can modify the object
	if (list->empty()) {
		if (!ReadFile("student.txt", list)) {
			return false;
		}
		else {
			cout << "Reading from student.txt success..." << endl;
		}
		if (!readBookFile(list, "book.txt")&&detail==1) {
			cout << "No record for detail display! " << endl;
			return false;
		}
	}

	if (source == 2) {
		for (int i = 1; i < list->count; i++) {
			
			list->get(i, stu);
			cout << "\nSTUDENT " << i;
			stu.print(cout);


			if (detail == 1) {
				cout << "\nBOOK LIST:" << "\n";
				for (int i = 0; i < stu.totalbook;i++) {
					stu.book[i].print(cout);
				}
				
			}
			cout << "\n**************************************************************" << "\n";
		}
	}
	else if (source == 1) {
		ofstream outputFile;
		string filename;
		if(detail==1){
			filename = "student_bl.txt";
		}
		else if (detail == 2) {
			filename = "student_if.txt";
		}
		outputFile.open(filename, fstream::app);
		//If filename does not exist, the file is created. Otherwise, the fstream::app
		//If file filename already exists, append the data to the file instead of overwriting it.

		for (int i = 1; i < list->count; i++) {
			list->get(i, stu);
			stu.print(outputFile);

			if (detail == 1) {
				for (int i = 0; i < stu.totalbook; i++) {
					stu.book[i].print(outputFile);
				}
			}
		}
		cout << "Student record has been printed to file " << filename << "!" << endl;
		outputFile.close();
	}
	return true;
}
	
bool computeAndDisplayStatistics(List* list) {
	if (list->empty()) {
		return false;
	}
	LibStudent stu;
	const int courses = 5;
	string course[courses] = { " CS", " IA", " IB", " CN", " CT" };
	int numOfStu[courses] = { 0,0,0,0,0 };
	int numOfBook[courses] = { 0,0,0,0,0 };
	int numOfOverdue[courses] = { 0,0,0,0,0 };
	double total[courses] = { 0.00,0.00,0.00,0.00,0.00 };
	for (int i = 0; i < list->count; i++) {
		list->get(i, stu);
		for (int j = 0; j < courses; j++) {
			if (stu.course == course[j]) {
				numOfStu[j]++;
				numOfBook[j] += stu.totalbook;
				for (int k=0; k < stu.totalbook; k++) {
					if (stu.book[k].fine) {
						numOfOverdue[j]++;
						total[j] += stu.book[k].fine;
					}
				}
			}
		}
	}
	for (int i = 0; i < courses; i++) {
		if (i == 0 || i == list->count - 1) {
			cout << "----------------------------------------------------------------" << endl;
			if (i == 0) {
				cout << "| Course\t| Number of Students\t| Total Books Borrowed\t| Total Overdue Books \t|Total Overdue Fine (RM)|\n";
			}
		}
		 
		cout <<"|" << course[i] << "\t\t| " << numOfStu[i] << "\t\t\t| " << numOfBook[i] << "\t\t\t| " << numOfOverdue[i] << " \t\t\t| " << total[i] << "\n";
	}
	return true;
}

//CHECKING IF USER INPUT AN INTEGER
bool isInt(string &input) {
	for (char s: input) {
		//iterate each character
		if (!isdigit(s)) {
			//isdigit takes "int" or "unsigned char" as parameters
			//strlen can also be used to calculate string length
			//for (int i = 0; i < strlen(str); i++) 
			return false;
		}
	}
	return true;
}

//huanQian
bool printStuWithSameBook(List* list, char* callNum)
{
	List sameBook;
	int numOfStud = 0;//number of Student
	//int count = 0;
	LibStudent info;
	Node* ptr = list->head;

	if (!list->empty()) {

		while (ptr != NULL) {

			info = ptr->item;

			for (int i = 0; i < 15; i++) {
				//Student who did not borrow any book
				if (strlen(info.book[i].callNum) == 1) {

					break;
				}

				else {
					if (strcmp(info.book[i].callNum, callNum)) {
						sameBook.insert(info);
						numOfStud += 1;
						break;
					}
				}
			}
			ptr = ptr->next;
		}

		cout << "***********************************************************************" << endl;
		cout << "There are " << numOfStud << " students borrow the book with call number " << callNum << " as shown below: " << endl << endl;

		if (numOfStud != 0) {

			ptr = sameBook.head;
			while (ptr != NULL) {
				cout << "Student ID = " << ptr->item.id << endl;
				cout << "Name = " << ptr->item.name << endl;
				cout << "Course = " << ptr->item.course << endl;
				cout << "Phone Number = " << ptr->item.phone_no << endl;
				cout << "Borrow Date = "; ptr->item.book[0].borrow.print(cout); cout << endl;
				cout << "Due Date = "; ptr->item.book[0].due.print(cout); cout << endl;
				cout << endl;
				ptr = ptr->next;
			}
		}
		cout << "*************************************************************************" << endl;
		return true;
	}
	else {
		cout << "No student borrow this book." << endl;
		return false;
	}

}

bool displayWarnedStudent(List* list, List* type1, List* type2)
{
	if (list->empty())
	{
		cout << "No student in the record.\n";
		return false;
	}
	else
	{
		Date currentDate;
		currentDate.day = 29;
		currentDate.month = 3;
		currentDate.year = 2020;
		cout << "Current Date : ", currentDate.print(cout);
		cout << endl;

		LibStudent studInfo;
		Node* listPtr = list->head;
		int count = 1;

		while (listPtr != NULL)
		{
			list->get(count, studInfo);
			int overDue = 0;
			int checkDueBook = 0;
			for (int i = 0; i < listPtr->item.totalbook; i++) {
				if (listPtr->item.total_fine > 5) {
					overDue = overDue + 1;
				}
			}
			if (overDue > 2) {
				type1->insert(studInfo);
			}

			for (int i = 0; i < listPtr->item.totalbook; i++) {
				if (listPtr->item.book[i].fine != 0) {
					checkDueBook = checkDueBook + 1;
				}
			}
			if ((checkDueBook == listPtr->item.totalbook) && (listPtr->item.total_fine > 50)) {
				type2->insert(studInfo);
			}
			listPtr = listPtr->next;
			count++;

		}

		//display student and book of type1 and type2
		if (type1->empty()) {
			cout << "No type 1 List" << endl;

		}
		else {
			cout << "\nType 1 warning: " << endl;
			Node* ptr = type1->head;
			int stuCounter = 1;

			while (ptr != NULL)
			{
				cout << "Student " << stuCounter << endl;
				cout << "Student Id = " << ptr->item.id << endl;
				cout << "Name = " << ptr->item.name << endl;
				cout << "Course =" << ptr->item.course << endl;

				ptr = ptr->next;
				stuCounter++;
			}
		}

		if (!type2->empty())
		{
			cout << "\nType 2 warning: " << endl;
			Node* ptr = type2->head;
			int stuCounter = 1;

			while (ptr != NULL) {
				cout << "Student " << stuCounter << endl;
				cout << "Student Id = " << ptr->item.id << endl;
				cout << "Name = " << ptr->item.name << endl;
				cout << "Course =" << ptr->item.course << endl;

				ptr = ptr->next;
				stuCounter++;
			}
		}
		return true;
	}
}