#include	<iostream>
#include	<cstdlib>
#include	<cstdio>
#include    <fstream>
#include	<iomanip>
#include    <string>
#include	"List.h"
#include    "LibStudent.h"
#include    "LibBook.h"

#define MAX_CHOOSE 9
#define ID_LENGTH 7
#define ID_MIN 1000000
#define ID_MAX 9999999
using namespace std;

bool ReadFile(string, List*);
//bool DeleteRecord(List*, char*);
bool Display(List *, int, int);
bool DeleteRecord(List* list, char* stuId);
bool InsertBook(string, List*);
bool SearchStudent(List*, char* id, LibStudent&);
bool computeAndDisplayStatistics(List*);
bool printStuWithSameBook(List*, char*);
bool displayWarnedStudent(List*, List*, List*);
void menu(int*);

//input validation
bool isInt(string& input);
int getInputInRange(int minRange, int maxRange);

int main() {
	int choose;
	bool exit = false;
	List stdList;
	string stuId;
	menu(&choose);

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
			menu(&choose);

			break;
		case 4:
			cout << "Insert book" << endl;
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
                stu = current->item; 
                return true;
            }
            current = current->next;
        }
        return false;
    }

//bool InsertBook(string filename, List* list) {
//    ifstream inFile(filename);
//    if (!inFile.is_open()) {
//        cout << "Error opening file: " << filename << endl;
//        return false;
//    }
//
//    LibStudent newStudent;
//    while (inFile >> newStudent.name >> newStudent.id >> newStudent.course >> newStudent.phone_no) {
//        int numOfBooks;
//        inFile >> newStudent.total_fine >> newStudent.totalbook >> numOfBooks;
//
//        if (numOfBooks > 15) {
//            cout << "Number of books exceeds the maximum limit (15) for student " << newStudent.name << " (ID: " << newStudent.id << ")" << endl;
//            continue;
//        }
//
//        for (int i = 0; i < numOfBooks; i++) {
//            inFile >> newStudent.book[i].title >> newStudent.book[i].author >> newStudent.book[i].ISBN;
//        }
//
//        // Insert the new student with their book information into the list
//        if (!list->insert(newStudent)) {
//            cout << "Error inserting student " << newStudent.name << " (ID: " << newStudent.id << ") into the list." << endl;
//        }
//    }
//
//    inFile.close();
//    return true;
//}

bool DeleteRecord(List* list, char* stuId) {

	//check 
	if (list->empty()) {
		cout << "No shudent in list yet!\n";
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
			cout << "\nSTUDENT " << i << "\n";
			stu.print(cout);

			if (detail == 1) {
				bookCount = 0;
				cout << "\nBOOK LIST:" << "\n";

				while (stu.book[bookCount].title != nullptr) {
					LibBook book = stu.book[bookCount];
					cout << "\nBook " << bookCount+1 << "\n";
					book.print(cout);
					bookCount++;
				}
				
			}
			else if (detail == 2) {
				break;
			}
			cout << "\n**************************************************************"<<"\n";
			
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
		//if (!outputFile.is_open()) {
		//	cout << filename << " not found, creating new file..." << endl;
		//}
		for (int i = 0; i < list->count; i++) {
			bookCount = 0;
			list->get(i, stu);
			stu.print(outputFile);
			if (detail == 1) {
				LibBook book = stu.book[bookCount];
				
				for (int i = 0; i < stu.totalbook; i++) {
					book.print(outputFile);
				}
				bookCount++;
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
	LibStudent* cur;
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
				for (int k; k < stu.totalbook; i++) {
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
			cout << "------------------------------------------------------------" << endl;
			if (i == 0) {
				cout << "| Course | Number of Students | Total Books Borrowed | Total Overdue Books |Total Overdue Fine (RM)|";
			}
		}
		 
		cout << course[i] << " | " << numOfStu << " | " << numOfBook << " | " << numOfOverdue << " | " << total;
	}
	
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
