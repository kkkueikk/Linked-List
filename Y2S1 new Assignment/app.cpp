#include	<iostream>
#include	<cstdlib>
#include	<cstdio>
#include    <fstream>
#include	<iomanip>
#include    <string>
#include <sstream>
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
//bool InsertBook(string, List*);
bool SearchStudent(List*, char* id, LibStudent&);
void split(const string& string1, string arr1[]);
bool computeAndDisplayStatistics(List*);
bool printStuWithSameBook(List*, char*);
bool displayWarnedStudent(List*, List*, List*);
void menu(int*);
bool readBookFile(List *, string filename);
void calculateFine(LibBook& book);
//input validation
bool isInt(string& input);
int getInputInRange(int minRange, int maxRange);

int main() {
	int choose;
	bool exit = false;
	List stdList;
	string stuId;
	menu(&choose);
	//for SearchStudent
	int stuID;
	char stuIDStr[8];
	LibStudent stu;


	while (!exit) {
		switch (choose) {
		case 1:
			cout << "Read File" << endl;
			if (!ReadFile("student.txt", &stdList))
				cout << "Read file can't open!\n";
			menu(&choose);
			break;
		case 2:
			cout << "Delete record" << endl;
			getInputInRange(ID_MIN, ID_MAX);
			if (DeleteRecord(&stdList, &stuId[0])) {
				cout << "Successfully Deleted!\n";
			}
			else
				cout << "Student cannot be found\n";
			menu(&choose);
			break;
		case 3:
			cout << "Search student" << endl;
			cout << "Give the ID of the student you want to search: ";
			stuID = getInputInRange(1000000, 9999999);
			snprintf(stuIDStr, sizeof(stuIDStr), "%d", stuID);
			SearchStudent(&stdList, stuIDStr, stu);
			menu(&choose);

			break;
		case 4:
			cout << "Insert book" << endl;
			readBookFile(&stdList, "book.txt");
			menu(&choose);

			break;
		case 5:
			int source, detail;
			cout << "Display output" << endl;
			cout << "Where do you want to display the output (1 - File / 2 - Screen):"<<endl;

			source = getInputInRange(1, 2);
			cout << "Do you want to display book list for every student (1 - YES / 2 - NO):"<<endl;
			detail = getInputInRange(1, 2);
			Display(&stdList, source, detail);
			menu(&choose);
			break;
		case 6:
			cout << "Compute and Display Statictics" << endl;
			computeAndDisplayStatistics(&stdList);
			menu(&choose);
			break;
		case 7:
			cout << "Student with Same Book" << endl;
			menu(&choose);

			break;
		case 8:
			cout << "Display Warned Student" << endl;
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
	int j;
	char s[256];
	ifstream read;
	read.open(filename);
	LibStudent student;

	if (!read.is_open()) {
		cout << "The student.txt is not find!\n";
	}
	j = 0;
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

		list->insert(student);

	}
	cout << "\nThe file has been readed!!\n\n";
	read.close();
	return true;
}

bool SearchStudent(List* list, char* id, LibStudent &stu) {
        Node* current = list->head;
        while (current != nullptr) {
            if (strcmp(current->item.id, id) == 0) {
				cout << "\nHere is the student with ID " << *id;
                stu = current->item; 
				stu.print(cout);
				cout << "\n";
                return true;
            }
            current = current->next;
        }
		cout << "Student with ID " << *id << "not found!" << endl;
        return false;
    }


//bool InsertBook(string filename, List* list) {
//	ifstream inFile;
//	inFile.open("book.txt");
//
//	if (!inFile.is_open()) {
//		cout << "Failed to open the file: " << endl;
//		return false;
//	}
//
//	LibBook book;
//	char id[10];
//	int currentDay, currentMonth, currentYear;

//	currentDay = 29;
//	currentMonth = 3;
//	currentYear = 2020;
//	Date currentDate(currentDay, currentMonth, currentYear);
//
//
//	while (!inFile.eof()) {
//		// Read book information from the file
// 
// --------------------------------where is your student id?-----------------------
// --------------------------------correct format of book.txt: studentId author( if there are multiple author, they will be separated by "/") bookTitle publisher ISBN publishYear callNum borrow due
// --------------------------------for author you should use delimiter! go online and search getline() for infor of delimiter
// --------------------------------after reading the data, you should also store it in the list(your second argument), I personally suggest you to do the reading and storing of data from book.txt in another function, Ex:readBookFile()
//		inFile.getline(book.title, sizeof(book.title));
//		inFile.getline(book.publisher, sizeof(book.publisher));
//		inFile.getline(book.ISBN, sizeof(book.ISBN));
//		inFile >> book.yearPublished;
//
//		for (int i = 0; i < 10; i++)
//			book.author[i] = NULL;
//		for (int i = 0; i < 10; i++) {
//			char author[100];
//			inFile.getline(author, sizeof(author));
//			if (strlen(author) > 0)
//				book.author[i] = new char[strlen(author) + 1];
//			strcpy(book.author[i], author);
// 
// ----------------------------------------I think strcpy is not good enough to be used? Like what we learn in cybersecurity class, it is not secure enough ya
//		}
//
//		inFile >> book.borrow.day >> book.borrow.month >> book.borrow.year;
//		inFile >> book.due.day >> book.due.month >> book.due.year;
//		inFile >> book.callNum;
//
// ----------------------------------------use Julian library ---------------------------

//		// Read the student ID to insert the book for that student
//		inFile >> id;
//
// --------------------------this checking should be on top of your function, then you return false if insertion cannot be done, continue insertion if student is found!
//		LibStudent student;
//		if (SearchStudent(list, id, student)) {
//			student.book[student.totalbook] = book;
//			student.totalbook++;
//			student.calculateTotalFine();
//		}
//		else {
//			cout << "Student with ID " << id << " not found. Skipping book insertion." << endl;
//		}
//	}
//
//	inFile.close();
//	return true;
//}

bool readBookFile(List* list, string filename) {
	ifstream inputFile;
	inputFile.open(filename);
	if (!inputFile.is_open()) {
		cout << filename << " not found!" << endl;
		return false;
	}
	LibStudent stu;
	LibBook book;
	string stuID, title, author, publisher, ISBN, yearPublished, callNum, borrow, due, temp;
	while (true){
	//Student_id  author/authors  title  publisher  ISBN  yearPublished  callNum  date_borrow  date_due 
		getline(inputFile, stuID, '\t');
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
		cout << stuID << endl;
		if (inputFile.eof()) {
				break;
		}

		const char* tmp = &stuID[0];
		SearchStudent(list, (char*)tmp, stu);
		strcpy_s(book.title, (char*)title.c_str());
		strcpy_s(book.publisher, (char*)publisher.c_str());
		strcpy_s(book.ISBN, (char*)ISBN.c_str());
		strcpy_s(book.callNum, (char*)callNum.c_str());
		book.yearPublished=stoi(yearPublished);
		cout << yearPublished << endl;
		//for converting borrow and due into Date
		string datePart[3];
		Date date;
		split(borrow, datePart);
		book.borrow = Date(stoi(datePart[0]), stoi(datePart[1]), stoi(datePart[2]));
		
		split(due, datePart);
		book.due = Date(stoi(datePart[0]), stoi(datePart[1]), stoi(datePart[2]));
		
		//for splitting authors
		string name[10];
		split(author, name);
		int i = 0;

		while (i < 10 && !name[i].empty()) { //assign name to author one by one
			book.author[i] = new char[name[i].length() + 1];
			strcpy_s(book.author[i], name[i].length() + 1, name[i].c_str());
			cout << book.author[i] << endl;
			i++;
		}
		calculateFine(book);

		i = 0;
		while (stu.book[i].title.length()!=0) {
			i++;
		}
		if (i >= 15) {
			return false;
		}
		else {
			book[i]
		}
		int bookCount = sizeof(stu.book)/sizeof(book);
		if (bookCount <= 15) {
			stu.book[bookCount] = book;
		}
		else {
			cout << "This student "<< stu.id << " has borrow more than 15 books!" << endl;
			return false;
		}
		
		stu.calculateTotalFine();
	}
	return true;
}

//no need & before array because array is passed as pointer
void split(const string& string1, string arr1[]) {
	if (string1.find('/')) {
		stringstream ss(string1);
		string token;
		int index = 0;

		while (getline(ss, token, '/')) { //if there is no need of splitting
			arr1[index++] = token;
		}
	}
	else {
		arr1[0] = string1;
	}
}

void calculateFine(LibBook &book) {
	    Date currentDate(29,3,2020);
		// Calculate the fine for the book
		int dueJulian = book.due.day + 30 * book.due.month + 365 * book.due.year;
		int currentJulian = currentDate.day + 30 * currentDate.month + 365 * currentDate.year;
		int daysOverdue = currentJulian - dueJulian;

		if (daysOverdue > 0)
			book.fine = 0.50 * daysOverdue;
		else
			book.fine = 0.0;
}
bool DeleteRecord(List* list, char* stuId) {

	//check 
	if (list->empty()) {
		cout << "No shudent in list yet!\n";
		return false;
	}
	
	Node* cur;
	cur = list->head;

//-----------------------------later can change to searchStudent in main function---remember to return false if student not found
	//loop all the element in link list to find student
	for (int i = 1; i <= list->size(); i++) {

		if (cur->item.id == stuId) {
			list->remove(i);

			//open file to show the info make sure the student has been remove
			ofstream output;
			output.open("student.txt");

			Node* show;
			show = list->head;

//---------------------can use function in LibStudent, print()---------------
			for (int i = 1; i <= list->size(); i++) {
				output << "Student Id\t= " << show->item.id << endl;
				output << "Name\t= " << show->item.name << endl;
				output << "Course\t= " << show->item.course << endl;
				output << "Phone Number\t= " << show->item.phone_no << endl;

				show = show->next;
			}

			//delete student in book.txt record
			ofstream read;
			ifstream input;

			input.open("book.txt");
			read.open("newbook.txt");
			char id[10];
			string line;

			while (!input.eof()) {
				input >> id;
				getline(input, line);

				if (id == stuId) {
					read << id << " ";
					read << line << "\n\n";
				} 
				input.close();
				output.close();
				read.close();
//-------------------------------------------I don't think the record is from "book.txt", the "book.txt store book, not student record"
				remove("book.txt"); //delete book.txt 

				rename("newbook.txt", "book.txt");

				return true;
			}

			cur = cur->next;
		}
		else {
			cout << "No student in the record.\n";
			return false;
		}
	}

}

bool Display(List* list, int source, int detail) {
	//source determine where to print the output
	//detail determine what info to print
	LibStudent stu;
	int bookCount;
	//list is a pointer for list, we can modify the object
	if (source == 1) {
		for (int i = 0; i < list->count; i++) {
			
			list->get(i, stu);
			cout << "\nSTUDENT " << i+1;
			stu.print(cout);

			if (detail == 1) {
				bookCount = 0;
				cout << "\nBOOK LIST:" << "\n";

				while (stu.book[i].title[0] != '\0') {
					//empty check whether the size is 0
					LibBook book = stu.book[bookCount];
					cout << "\nBook " << bookCount+1 << "\n";
					book.print(cout);
					bookCount++;
				}
				
			}
			cout << "\n**************************************************************" << "\n";
		}
	}
	else if (source == 2) {
		ofstream outputFile;
		string filename;
		if(detail==1){
			filename = "student_booklist.txt";
		}
		else if (detail == 2) {
			filename = "student_info.txt";
		}
		outputFile.open(filename, fstream::app);
		//If filename does not exist, the file is created. Otherwise, the fstream::app
		//If file filename already exists, append the data to the file instead of overwriting it.
		if (!outputFile.is_open()) {
			cout << filename << " not found!" << endl;
			return false;
		}
		for (int i = 0; i < list->count; i++) {
			bookCount = 0;
			list->get(i, stu);
			stu.print(outputFile);

			if (detail == 1) {
				LibBook book = stu.book[bookCount];
				
				while (stu.book[i].title[0] != '\0') {
					LibBook book = stu.book[bookCount];
					book.print(outputFile);
					bookCount++;
				}
			}
		}
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
	string course[courses] = { "CS", "IA", "IB", "CN", "CT" };
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
				cout << "| Course | Number of Students | Total Books Borrowed | Total Overdue Books |Total Overdue Fine (RM)|\n ";
			}
		}
		 
		cout << course[i] << " | " << numOfStu[i] << " | " << numOfBook[i] << " | " << numOfOverdue[i] << " | " << total[i]<<"\n";
	}
	return true;
}

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
