#include	<iostream>
#include	<cstdlib>
#include	<cstdio>
#include    <fstream>
#include    <string>
#include	"List.h"
#include    "LibStudent.h"
#include    "LibBook.h"



using namespace std;

bool ReadFile(string, List *);
bool DeleteRecord(List *, char *);
bool Display(List *, int, int);
bool InsertBook(string, List *);
bool SearchStudent(List *, char *id, LibStudent &);
bool computeAndDisplayStatistics(List *);
bool printStuWithSameBook(List *, char *);
bool displayWarnedStudent(List *, List *, List *);
int menu();

int main() {

	List* list = new List();
	List* type1 = new List();
	List* type2 = new List();
	LibStudent stu;
	string readStu = "student.txt";
	string readBook = "book.txt";
	char id[10];
	char callNum[20];
	int choice, source, detail;

	cout << "UTAR STUDENT&BOOK SYSTEM\n\nMade by\nKum Wing Kit\nLim Zi Yang\nUzair\nYong Wei Bang\n\n";

	while (true)
	{
		choice = menu();

		if (choice == 1) {
			if (ReadFile(readStu, list))
				cout << list->count << " records have been successfully read.\n\n";
		}
		else if (choice == 2) {
			cout << "Enter the id: ";
			cin >> id;
			cout << endl;
			DeleteRecord(list, id);
		}
		else if (choice == 3) {
			cout << "Enter the id: ";
			cin >> id;
			cout << endl;
			SearchStudent(list, id, stu);
		}
		else if (choice == 4) {
			if (InsertBook(readBook, list))
				cout << "Insert books success!\n\n";
		}
		else if (choice == 5) {
			cout << "Where do you want to display the output (1 - File / 2 - Screen): ";
			cin >> source;
			cout << endl;
			cout << "Do you want to display book list for every student (1 - YES / 2 - NO): ";
			cin >> detail;
			cout << endl;
			if (!Display(list, source, detail))
				cout << "Failed to display output!\n\n";
		}
		else if (choice == 6) {
			computeAndDisplayStatistics(list);
		}
		else if (choice == 7) {
			cout << "Enter the call number: ";
			cin >> callNum;
			cout << endl;
			printStuWithSameBook(list, callNum);
		}
		else if (choice == 8) {
			if (displayWarnedStudent(list, type1, type2))
			{
				type item;
				cout << "Student that has more than 2 and overdue for >= 10 days!\n\n";
				for (int i = 1; i <= type1->count; i++) {

					type1->get(i, item);
					cout << "STUDENT " << i << "\n\n";
					cout << "Name: " << item.name << endl;
					cout << "ID: " << item.id << endl;
					cout << "Course: " << item.course << endl;
					cout << "Phone No: " << item.phone_no << endl;
					cout << "Total Fine: RM" << item.total_fine << "\n\n";

					for (int j = 0; j < item.totalbook; j++) {

						cout << "BOOK " << j + 1 << "\n\n";
						cout << "Title: " << item.book[j].title << endl;
						cout << "Author: ";
						for (int k = 0; k < 10; k++) {
							if (item.book[j].author[k] != NULL)
								cout << item.book[j].author[k] << "\t";
							else
								break;
						}
						cout << endl;
						cout << "Publisher: " << item.book[j].publisher << endl;
						cout << "Year Published: " << item.book[j].yearPublished << endl;
						cout << "ISBN: " << item.book[j].ISBN << endl;
						cout << "Borrow Date: " << item.book[j].borrow.day << "/" << item.book[j].borrow.month << "/" << item.book[j].borrow.year << endl;
						cout << "Due Date: " << item.book[j].due.day << "/" << item.book[j].due.month << "/" << item.book[j].due.year << endl;
						cout << "Fine: " << item.book[j].fine << endl;
						cout << endl;
					}
					cout << "*****************************************************************\n\n";
				}

				cout << "Total fine for a student is more than RM50.00 and every book in the student’s book list are overdue!\n\n";
				for (int i = 1; i <= type2->count; i++) {

					type2->get(i, item);
					cout << "STUDENT " << i << "\n\n";
					cout << "Name: " << item.name << endl;
					cout << "ID: " << item.id << endl;
					cout << "Course: " << item.course << endl;
					cout << "Phone No: " << item.phone_no << endl;
					cout << "Total Fine: RM" << item.total_fine << "\n\n";

					for (int j = 0; j < item.totalbook; j++) {

						cout << "BOOK " << j + 1 << "\n\n";
						cout << "Title: " << item.book[j].title << endl;
						cout << "Author: ";
						for (int k = 0; k < 10; k++) {
							if (item.book[j].author[k] != NULL)
								cout << item.book[j].author[k] << "\t";
							else
								break;
						}
						cout << endl;
						cout << "Publisher: " << item.book[j].publisher << endl;
						cout << "Year Published: " << item.book[j].yearPublished << endl;
						cout << "ISBN: " << item.book[j].ISBN << endl;
						cout << "Borrow Date: " << item.book[j].borrow.day << "/" << item.book[j].borrow.month << "/" << item.book[j].borrow.year << endl;
						cout << "Due Date: " << item.book[j].due.day << "/" << item.book[j].due.month << "/" << item.book[j].due.year << endl;
						cout << "Fine: " << item.book[j].fine << endl;
						cout << endl;
					}
					cout << "*****************************************************************\n\n";
				}
			}
		}
		else if (choice == 9) {
			cout << "Exitting...\n";
			break;
		}
		else cout << "Please enter the correct choice!\n\n";
	}

	cout << "\n\n";
	system("pause");
	return 0;
}

bool ReadFile(string filename, List *list) {

	int count = 1;
	string temp;

	ifstream input;
	input.open(filename);

	if (!input.is_open()) {
		cout << "No such file\n" << endl;
		return false;
	}
	else {
		while (!input.eof()) {
			bool check = false;
			LibStudent* student = new LibStudent();
			char name[30] = "";
			char id[10] = "";
			char course[3] = "";
			char phone_no[10] = "";

			getline(input, temp);
			if (!temp.empty()) {
				temp = temp.substr(temp.find("=") + 2, temp.length());
				strcpy(student->id, temp.c_str());
			}

			getline(input, temp);
			if (!temp.empty()) {
				temp = temp.substr(temp.find("=") + 2, temp.length());
				strcpy(student->name, temp.c_str());
			}

			getline(input, temp);
			if (!temp.empty()) {
				temp = temp.substr(temp.find("=") + 2, temp.length());
				strcpy(student->course, temp.c_str());
			}

			getline(input, temp);
			if (!temp.empty()) {
				temp = temp.substr(temp.find("=") + 2, temp.length());
				 strcpy(student->phone_no, temp.c_str());
			}
			//two empty lines
			getline(input, temp);
			getline(input, temp);
			//find if duplicated or not
			for (int i = 1; i <= list->size(); i++) {

				type item;
				list->get(i, item);

				if ((string)item.name == (string)student->name) {
					cout << "Duplicate student found!\n" << endl;
					check = true;
					break;
				}
			}
			if (student->id != NULL && student->name != NULL && student->phone_no != NULL && student->course != NULL) {
				if (!check)
				{
					list->insert(count, *student);
					count++;
				}
			}
			else
			{
				cout << "Unable insert\n" << endl;
				return false;
			}
		}
	}
	return true;
}

bool DeleteRecord(List* list, char* id) {

	type temp;

	if (list->empty()) {
		cout << "List empty!\n" << endl;
		return false;
	}

	for (int i = 1; i <= list->size(); i++) {

		list->get(i, temp);
		if ((string)temp.id == (string)id) {
			list->remove(i);
			cout << "Student with ID " << id << " has been deleted!" << endl << endl;
			return true;
		}
		if ((string)temp.id != (string)id && i == list->size()) {
			cout << "Student with ID " << id << " not found!" << endl << endl;
			return false;
		}
	}
}

bool SearchStudent(List* list, char* id, LibStudent& stu) {

	type temp;

	if (list->empty()) {
		cout << "List empty!\n" << endl;
		return false;
	}
	//find item.id == id
	for (int i = 1; i <= list->count; i++) {

		list->get(i, temp);
		if ((string)temp.id == (string)id) {
			stu = temp;
			cout << "Student ID :" << stu.id << endl;
			cout << "Student Name :" << stu.name << endl;
			cout << "Course :" << stu.course << endl;
			cout << "Student Phone.No :" << stu.phone_no << endl;
			cout << endl;
			return true;
		}
	}
	//false if out of loop(not found)
	cout << "Student with ID " << id << " not found!\n" << endl;
	return false;
}

bool InsertBook(string filename, List* list) {

	//Student_id  author/authors  title  publisher  ISBN  yearPublished  callNum  date_borrow  date_due 

	Date borrow;
	Date due;
	char id[10];

	string moreTemp[9], tempAuthor = "";
	type item;

	ifstream input;
	input.open(filename);

	if (list->empty()) {
		cout << "List empty!\n" << endl;
		return false;
	}

	if (!input.is_open()) {
		cout << "Failed to open the file!\n" << endl;
		return false;
	}
	//input data from file
	while (input >> moreTemp[0] >> moreTemp[1] >> moreTemp[2] >> moreTemp[3] >> moreTemp[4] >> moreTemp[5] >> moreTemp[6] >> moreTemp[7] >> moreTemp[8]) {

		LibBook book;
		//save the input to id
		strcpy(id, moreTemp[0].c_str());

		int checkAuthor = 0;
		//save the input to author
		while (moreTemp[1].find("/") != string::npos) {

			tempAuthor = moreTemp[1].substr(0,moreTemp[1].find("/"));
			book.author[checkAuthor] = _strdup(tempAuthor.c_str());
			moreTemp[1] = moreTemp[1].substr(moreTemp[1].find("/") + 1, moreTemp[1].length());
			checkAuthor++;
		}

		book.author[checkAuthor] = _strdup(moreTemp[1].c_str());
		//save the input to title
		strcpy(book.title, moreTemp[2].c_str());
		//save the input to publisher
		strcpy(book.publisher, moreTemp[3].c_str());
		//save the input to ISBN
		strcpy(book.ISBN, moreTemp[4].c_str());
		//save the input to year published
		book.yearPublished = stoi(moreTemp[5]);
		//save the input to call number
		strcpy(book.callNum, moreTemp[6].c_str());
		//save the input to borrow date
		borrow.day = stoi(moreTemp[7].substr(0, moreTemp->find("/")));
		moreTemp[7] = moreTemp[7].substr(moreTemp[7].find("/") + 1, moreTemp[7].length());
		borrow.month = stoi(moreTemp[7].substr(0, moreTemp->find("/")));
		moreTemp[7] = moreTemp[7].substr(moreTemp[7].find("/") + 1, moreTemp[7].length());
		borrow.year = stoi(moreTemp[7].substr(0, moreTemp->find("/")));
		book.borrow.day = borrow.day;
		book.borrow.month = borrow.month;
		book.borrow.year = borrow.year;
		//save the input to due date
		due.day = stoi(moreTemp[8].substr(0, moreTemp->find("/")));
		moreTemp[8] = moreTemp[8].substr(moreTemp[8].find("/") + 1, moreTemp[8].length());
		due.month = stoi(moreTemp[8].substr(0, moreTemp->find("/")));
		moreTemp[8] = moreTemp[8].substr(moreTemp[8].find("/") + 1, moreTemp[8].length());
		due.year = stoi(moreTemp[8].substr(0, moreTemp->find("/")));
		book.due.day = due.day;
		book.due.month = due.month;
		book.due.year = due.year;
		//calculate the total day since 1/1/0000
		//29-3-2020
		int dayy = 29, monthh = 3, yearr = 2020, totalDay = 0, totalDays = 0, leapCheck = 0, fine = 0;
		int days[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

		if (monthh <= 12) {

			for (int i = 0; i < monthh - 1; i++) {

				totalDay += days[i];

			}
			totalDay += dayy;
			totalDay += (yearr * 365 + (yearr/ 4));
			if (monthh > 2 && yearr % 4 == 0) {
				totalDay += 1;
			}
		}
		
		if (book.due.month <= 12) {

			for (int i = 0; i < book.due.month - 1; i++) {

				totalDays += days[i];

			}
			totalDays += book.due.day;
			totalDays += (book.due.year * 365 + (book.due.year / 4));
			if (book.due.month > 2 && book.due.year % 4 == 0) {
				totalDays += 1;
			}
		}
		//fine the different
		fine = totalDay - totalDays;
		if (fine > 0) {
			book.fine = fine * 0.50;
		}
		else
			book.fine = 0;
		//save item.book = book and save it to list
		for (int i = 1; i <= list->count; i++) {

			list->get(i, item);
			
			if ((string)item.id == (string)id) {
				item.book[item.totalbook] = book;
				item.totalbook++;
				item.calculateTotalFine();
				if (!list->set(i, item)) {
					cout << "Failed to save book into the list!\n" << endl;
					return false;
				}
				break;
			}
		}
	}
	input.close();
	return true;
}

bool Display(List* list, int source, int detail) {

	ofstream output;
	type item;

	if (list->empty()) {
		cout << "List empty!\n" << endl;
		return false;
	}

	if (source == 1) {
		
		if (detail == 1) {

			output.open("student_booklist.txt");

			for (int i = 1; i <= list->count; i++) {

				output << "Student " << i;
				list->get(i, item);
				item.print(output);
				output << "\nBook list: \n";
				for (int j = 0; j < item.totalbook; j++) {
					output << "\nBOOK " << j + 1 << endl;
					item.book[j].print(output);
				}
				output << "\n***********************************\n\n";
			}
			cout << "Successfully display output to student_booklist.txt\n\nSuccessfully display output\n" << endl;
			return true;
		}
		else if (detail == 2) {

			output.open("student_info.txt");

			for (int i = 1; i <= list->count; i++) {

				output << "Student " << i;
				list->get(i, item);
				item.print(output);
				output << "\n***********************************\n\n";
			}
			cout << "Successfully display output to student_info.txt\n\nSuccessfully display output\n" << endl;
			return true;
		}
	}
	else if (source == 2) {

		if (detail == 1) {

			for (int i = 1; i <= list->count; i++) {

				list->get(i, item);
				cout << "STUDENT " << i << "\n\n";
				cout << "Name: " << item.name << endl;
				cout << "ID: " << item.id << endl;
				cout << "Course: " << item.course << endl;
				cout << "Phone No: " << item.phone_no << endl;
				cout << "Total Fine: RM" << item.total_fine << "\n\n";
				cout << "Book list: \n\n";
				for (int j = 0; j < item.totalbook; j++) {

					cout << "BOOK " << j + 1 << "\n\n";
					cout << "Title: " << item.book[j].title << endl;
					cout << "Author: ";
					for (int k = 0; k < 10; k++) {
						if (item.book[j].author[k] != NULL)
							cout << item.book[j].author[k] << "\t";
						else
							break;
					}
					cout << endl;
					cout << "Publisher: " << item.book[j].publisher << endl;
					cout << "Year Published: " << item.book[j].yearPublished << endl;
					cout << "ISBN: " << item.book[j].ISBN << endl;
					cout << "Borrow Date: " << item.book[j].borrow.day << "/" << item.book[j].borrow.month << "/" << item.book[j].borrow.year << endl;
					cout << "Due Date: " << item.book[j].due.day << "/" << item.book[j].due.month << "/" << item.book[j].due.year << endl;
					cout << "Fine: " << item.book[j].fine << endl;
					cout << endl;
				}
				cout << "*****************************************************************\n\n";	
			}
			cout << "Successfully display output!\n\n";
			return true;
		}
		else if (detail == 2) {

			for (int i = 1; i <= list->count; i++) {

				list->get(i, item);
				cout << "STUDENT " << i << "\n\n";
				cout << "Name: " << item.name << endl;
				cout << "ID: " << item.id << endl;
				cout << "Course: " << item.course << endl;
				cout << "Phone No: " << item.phone_no << endl;
				cout << "Total Fine: RM" << item.total_fine << "\n\n";
				cout << "*****************************************************************\n\n";
			}
			cout << "Successfully display output!\n\n";
			return true;
		}
	}
		return false;
}

bool computeAndDisplayStatistics(List* list) {

	if (list->empty()) {
		cout << "List empty!\n" << endl;
		return false;
	}

	int cs = 0, ia = 0, ib = 0, cn = 0, ct = 0;
	int csBook = 0, iaBook = 0, ibBook = 0, cnBook = 0, ctBook = 0;
	int csBookDue = 0, iaBookDue = 0, ibBookDue = 0, cnBookDue = 0, ctBookDue = 0;
	double csFine = 0, iaFine = 0, ibFine = 0, cnFine = 0, ctFine = 0;
	type item;

	for (int i = 1; i <= list->count; i++) {

		list->get(i, item);
		if ((string)item.course == "CS") { 
			cs++;
			csBook += item.totalbook;
			for (int j = 0; j < item.totalbook; j++) {
				if (item.book[j].fine > 0) {
					csBookDue++;
					csFine += item.book[j].fine;
				}
			}
		}
		else if ((string)item.course == "IA") {
			ia++; 
			iaBook += item.totalbook;
			for (int j = 0; j < item.totalbook; j++) {
				if (item.book[j].fine > 0) {
					iaBookDue++;
					iaFine += item.book[j].fine;
				}
			}
		}
		else if ((string)item.course == "IB"){
			ib++; 
			ibBook += item.totalbook;
			for (int j = 0; j < item.totalbook; j++) {
				if (item.book[j].fine > 0) {
					ibBookDue++;
					ibFine += item.book[j].fine;
				}
			}
		}
		else if ((string)item.course == "CN") {
			cn++;
			cnBook += item.totalbook;
			for (int j = 0; j < item.totalbook; j++) {
				if (item.book[j].fine > 0) {
					cnBookDue++;
					cnFine += item.book[j].fine;
				}
			}
		}
		else if ((string)item.course == "CT") {
			ct++; 
			ctBook += item.totalbook;
			for (int j = 0; j < item.totalbook; j++) {
				if (item.book[j].fine > 0) {
					ctBookDue++;
					ctFine += item.book[j].fine;
				}
			}
		}
	}
	cout << "Course(First Column)	Number of Students(Second Column)	Total Books Borrowed(Third Column)	Total Overdue Books(Fourth Column) 	Total Overdue Fine(RM)(Fifth Column)" << endl;
	cout << "CS" << "\t" << cs << "\t" << csBook << "\t" << csBookDue << "\t" << csFine << endl;
	cout << "IA" << "\t" << ia << "\t" << iaBook << "\t" << iaBookDue << "\t" << iaFine << endl;
	cout << "IB" << "\t" << ib << "\t" << ibBook << "\t" << ibBookDue << "\t" << ibFine << endl;
	cout << "CN" << "\t" << cn << "\t" << cnBook << "\t" << cnBookDue << "\t" << cnFine << endl;
	cout << "CT" << "\t" << ct << "\t" << ctBook << "\t" << ctBookDue << "\t" << ctFine << endl;
	cout << endl;

	return true;
}

bool printStuWithSameBook(List* list, char* callNum) {

	if (list->empty()) {
		cout << "List empty!\n" << endl;
		return false;
	}

	Node* current = list->head;
	int foundStudents = 0;


	while (current != nullptr) {
		LibStudent student = current->item;
		for (int i = 0; i < student.totalbook; i++) {
			if (strcmp(student.book[i].callNum, callNum) == 0) {
				foundStudents++;
			}
		}
		current = current->next;
	}

	if (foundStudents > 0) {
		cout << "There are " << foundStudents << " student(s) that borrow the book with call number " << callNum << " as shown below:\n\n";
		current = list->head; // Reset the current pointer to traverse again
		while (current != nullptr) {
			LibStudent student = current->item;
			for (int i = 0; i < student.totalbook; i++) {
				if (strcmp(student.book[i].callNum, callNum) == 0) {
					cout << "Student Id = " << student.id << endl;
					cout << "Name = " << student.name << endl;
					cout << "Course = " << student.course << endl;
					cout << "Phone Number = " << student.phone_no << endl;
					cout << "Borrow Date: ";
					student.book[i].borrow.print(cout);
					cout << endl;
					cout << "Due Date: ";
					student.book[i].due.print(cout);
					cout << endl << endl;
				}
			}
			current = current->next;
		}
	}
	else {
		cout << "No students found who borrowed the book with call number " << callNum << endl << endl;
	}
	return true;

}

bool displayWarnedStudent(List* list, List* type1, List* type2) {

	if (list->empty()) {
		cout << "List empty!\n" << endl;
		return false;
	}

	type item, item2;
	int preventPush = 1, preventPush2 = 1;

	for (int f = 1; f <= list->count; f++) {

		list->get(f, item);
		int checkBook = 0;
		
		for (int j = 0; j < item.totalbook; j++) {

			if(item.book[j].fine >= 5) checkBook++;

			if (checkBook > 2 && j + 1 == item.totalbook) {
				
				if (type1->count == 0)
					type1->insert(item);
				else {
					for (int l = 1; l <= type1->count; l++) {
						if ((string)type1->find(l)->item.name == (string)item.name) {
							type1->remove(l);
						}
					}
					type1->insert(item);
				}
			}
		}
		int checkIfEveryBookDue = 0;
		if (item.total_fine > 50) {
			for (int i = 0; i < item.totalbook; i++){

				if (item.book[i].fine > 0) {
					checkIfEveryBookDue++;
					if (checkIfEveryBookDue == item.totalbook) {
						
						if (type2->count == 0)
							type2->insert(item);
						else {
							for (int l = 1; l <= type2->count; l++) {
								if ((string)type2->find(l)->item.name == (string)item.name) {
									type2->remove(l);
								}
							}
							type2->insert(item);
						}
					}
				}
			}
		}
	}
	//If the person is deleted, delete it in these two list as well
	bool check = false;
	for (int k = 1; k <= type1->count; k++) {
		for (int i = 1; i <= list->count; i++) {
			if ((string)type1->find(k)->item.name == (string)list->find(i)->item.name) {
				check = true;
			}
		}
		if (!check) {
			type1->remove(k);
		}
		check = false;
	}
	for (int k = 1; k <= type2->count; k++) {
		for (int i = 1; i <= list->count; i++) {
			if ((string)type2->find(k)->item.name == (string)list->find(i)->item.name) {
				check = true;
			}
		}
		if (!check) {
			type2->remove(k);
		}
		check = false;
	}

	return true;
}

int menu() {

	int choice;
	cout << "Menu\n\n1. Read file \n2. Delete record \n3. Search student\n4. Insert book\n5. Display output\n6. Compute and Display Statistics\n7. Student with Same Book\n8. Display Warned Student\n9. Exit\nEnter Your Choice: ";
	cin >> choice;
	cout << endl;
	
	return choice;
}