#include	<iostream>
#include	<cstdlib>
#include	<cstdio>
#include    <fstream>
#include	<iomanip>
#include    <string>
#include	"List.h"
#include    "LibStudent.h"
#include    "LibBook.h"


using namespace std;

bool ReadFile(string, List*);
bool DeleteRecord(List*, char*);
bool Display(List, int, int);
bool InsertBook(string, List*);
bool SearchStudent(List*, char* id, LibStudent&);
bool computeAndDisplayStatistics(List*);
bool printStuWithSameBook(List*, char*);
bool displayWarnedStudent(List*, List*, List*);
int menu(int);


int main() {
	int choose{};
	bool exit = false;
	choose = menu(choose);
	List stdList;
	string stuId;

	while (!exit) {
		switch (choose) {
		case 1:
			cout << "Read File" << endl;
			if (!ReadFile("student.txt", &stdList))
				cout << "Read file can't open!\n";
			choose = menu(choose);
			break;
		case 2:
			
			bool check = false;
			cout << "Delete record" << endl;
			while (!check) {	

				//input student Id
				cout << "Enter the student id: ";
				getline(cin, stuId);
				
				if (stuId.length()>9||stuId.length()<0) {
					cout << "Pleace enter valid student Id,type again!!";
					check = false;
				}
				else
					check = true;
			}

			if (DeleteRecord(&stdList, &stuId[0])) {
				cout << "Successfully Deleted!\n";
			}
			else
				cout << "Student cannot be found\n";
			choose = menu(choose);
			break;
		case 3:
			cout << "Search student" << endl;
			choose = menu(choose);

			break;
		case 4:
			cout << "Insert book" << endl;
			choose = menu(choose);

			break;
		case 5:
			cout << "Display output" << endl;
			choose = menu(choose);
			break;
		case 6:
			cout << "Compute and Display Statictics" << endl;
			choose = menu(choose);
			break;
		case 7:
			cout << "Student with Same Book" << endl;
			choose = menu(choose);

			break;
		case 8:
			cout << "Display Warned Student" << endl;
			choose = menu(choose);

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

int menu(int choose) {
	string selection[9] = { "Read file","Delete record","Search student","Insert book","Display output","Compute and Display Statistics","Student with Same Book","Display Warned Student","Exit" };
	for (int i = 0; i < sizeof(selection) / sizeof(selection[0]); i++) {
		cout << i + 1 << "." << selection[i] << "\n";
	}
	cout << "Enter your choice\t: ";

	while (true) {
		if (cin >> choose && choose < 9 && choose>0) {
			break;
		}
		else {
			cin.clear();
			string invalidInput;
			getline(cin, invalidInput);
			cout << "Please enter a valid choice\t: ";
		}
	}

	return choose;
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
		read.getline(s, 265);
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
                stu = current->item; 
                return true;
            }
            current = current->next;
        }
        return false;
    }

bool InsertBook(string filename, List* list) {
	ifstream inFile;
	inFile.open("book.txt");

	if (!inFile.is_open()) {
		cout << "Failed to open the file: " << endl;
		return false;
	}

	LibBook book;
	char id[10];
	int currentDay, currentMonth, currentYear;
	currentDay = 29;
	currentMonth = 3;
	currentYear = 2020;
	Date currentDate(currentDay, currentMonth, currentYear);


	while (!inFile.eof()) {
		// Read book information from the file
		inFile.getline(book.title, sizeof(book.title));
		inFile.getline(book.publisher, sizeof(book.publisher));
		inFile.getline(book.ISBN, sizeof(book.ISBN));
		inFile >> book.yearPublished;

		for (int i = 0; i < 10; i++)
			book.author[i] = NULL;
		for (int i = 0; i < 10; i++) {
			char author[100];
			inFile.getline(author, sizeof(author));
			if (strlen(author) > 0)
				book.author[i] = new char[strlen(author) + 1];
			strcpy(book.author[i], author);
		}

		inFile >> book.borrow.day >> book.borrow.month >> book.borrow.year;
		inFile >> book.due.day >> book.due.month >> book.due.year;
		inFile >> book.callNum;

		// Calculate the fine for the book
		int dueJulian = book.due.day + 30 * book.due.month + 365 * book.due.year;
		int currentJulian = currentDate.day + 30 * currentDate.month + 365 * currentDate.year;
		int daysOverdue = currentJulian - dueJulian;

		if (daysOverdue > 0)
			book.fine = 0.50 * daysOverdue;
		else
			book.fine = 0.0;

		// Read the student ID to insert the book for that student
		inFile >> id;

		LibStudent student;
		if (SearchStudent(list, id, student)) {
			student.book[student.totalbook] = book;
			student.totalbook++;
			student.calculateTotalFine();
		}
		else {
			cout << "Student with ID " << id << " not found. Skipping book insertion." << endl;
		}
	}

	inFile.close();
	return true;
}

bool DeleteRecord(List* list, char* stuId) {

	//check 
	if (list->empty()) {
		cout << "No shudent in the record!\n";
		return false;
	}
	
	Node* cur;
	cur = list->head;

	//loop all the element in link list to find student
	for (int i = 1; i <= list->size(); i++) {


		if (cur->item.id == stuId) {
			list->remove(i);

			//open file to show the info make sure the student has been remove
			ofstream output;
			output.open("student.txt");

			Node* show;
			show = list->head;

			for (int i = 1; i <= list->size(); i++) {
				output << "Student Id\t= " << show->item.id << endl;
				output << "Name\t= " << show->item.name << endl;
				output << "Course\t= " << show->item.course << endl;
				output << "Phone Number\t= " << show->item.phone_no << endl;

				show = show->next;
			}

			//delete student in bookk.txt record
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
				remove("book.txt"); //delet book.txt 

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
