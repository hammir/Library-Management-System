#include <iostream>
#include <fstream>
#include<windows.h>
#include <cstring>
#include <string>
#include <iomanip>
#include <cstdlib> 
#include<conio.h>
extern "C" 
{
    void setCentre()    
	{    
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    
    int centerX = (csbi.dwSize.X - 1) / 2;
    int centerY = (csbi.dwSize.Y - 1) / 2;
    COORD centerCoord;
    centerCoord.X = centerX;
    centerCoord.Y = centerY;
    SetConsoleCursorPosition(hConsole, centerCoord);
	}
    
}

using namespace std;

class Book 
{
    char ISBN[20];
    char bname[50];
    char author[20];

public:
    void createBook() {
        cout << "\nNEW BOOK ENTRY...\n";
        cout << "\nEnter The ISBN: ";
        cin >> ISBN;
        cin.ignore(); 
        cout << "\nEnter The Name of The Book: ";
        cin.getline(bname, sizeof(bname));
        cout << "\nEnter The Author's Name: ";
        cin.getline(author, sizeof(author));
        cout << "\n\n\nBook Created.." << endl;
    }

    void showBook() {
        cout << "\nISBN: " << ISBN;
        cout << "\nBook Name: " << bname;
        cout << "\nAuthor Name: " << author << endl;
    }

    void modifyBook() {
        cout << "\nISBN: " << ISBN;
        cout << "\nModify Book Name: ";
        cin.ignore();
        cin.getline(bname, sizeof(bname));
        cout << "\nModify Author's Name of Book: ";
        cin.getline(author, sizeof(author));
    }

    const char* retISBN() {
        return ISBN;
    }

    void report() {
        cout << left << setw(10) << ISBN << setw(50) << bname << setw(25) << author << endl;
    }
};

class Student 
{
    char admno[15];
    char name[20];
    char stream[35];
    char year[10];
    char course[35];
    char stISBN[20];
	int token;

public:
    void createStudent() 
	{
        cout << "\nNEW STUDENT ENTRY...\n";
        cout << "\nEnter The admission no.: ";
        cin >> admno;
        
        cin.ignore(); 
        cout << "\nEnter The Name of The Student: ";
        cin.getline(name, sizeof(name));
        
        cout << "\nEnter The Course of The Student: ";
        cin.getline(course, sizeof(course));
        
        
		cout << "\nEnter The Stream of The Student: ";
        cin.getline(stream, sizeof(stream));
        
        
        cout << "\nEnter The Year of The Student: ";
        cin.getline(year, sizeof(year));
        
        
        token = 0;
        stISBN[0] = '\0'; 
        cout << "\nStudent Record Created.." << endl;
    }

    void showStudent() 
	{
        cout << "\nAdmission no.: " << admno<<endl;
        cout << "\nStudent Name: " << name<<endl;
        cout << "\nCourse: " << course<<endl;
        cout << "\nStream: " << stream<<endl;
        cout << "\nYear: " << year<<endl;
        cout << "\nNo of Books issued: " << token<<endl;
        if (token == 1)
        cout << "\nBook ISBN: " << stISBN<<endl;;
    }

    void modifyStudent() 
	{
        cout << "\nAdmission no.: " << admno;
        cout << "\nModify Student Name: ";
        cin.ignore(); 
        cin.getline(name, sizeof(name));
    }

    const char* retAdmno() 
	{
        return admno;
    }

    const char* retStISBN() 
	{
        return stISBN;
    }

    int retToken() 
	{
        return token;
    }

    void addToken() 
	{
        token = 1;
    }

    void resetToken() 
	{
        token = 0;
    }

    void getStISBN(const char t[]) 
	{
        strcpy(stISBN, t);
    }

    void report() 
	{
        cout << left << setw(20) << admno << setw(30) << name<< setw(35) << course << setw(35) << stream<< setw(15) << year << setw(15) << token << endl;
        //cin.get();
    }
};

fstream fp;
Book bk;
Student st;

void writeBook() 
{
    char ch;
    fp.open("book.dat", ios::out | ios::app);
    do {
        cin.ignore(); 
        system("cls");
        bk.createBook();
        fp.write(reinterpret_cast<char*>(&bk), sizeof(Book));
        cout << "\n\nDo you want to add more records? (y/n): ";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');
    fp.close();
}

void writeStudent() 
{
    char ch;
    fp.open("student.dat", ios::out | ios::app);
    do 
	{
        system("cls");
        st.createStudent();
        fp.write(reinterpret_cast<char*>(&st), sizeof(Student));
        cout << "\n\ndo you want to add more records? (y/n): ";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');
    fp.close();
}

void displaySpecificBook(char n[]) 
{
    cout << "\nBOOK DETAILS\n";
    int isbnPresent = 0;
    fp.open("book.dat", ios::in);
    while (fp.read(reinterpret_cast<char*>(&bk), sizeof(Book))) 
	{
        if (strcmpi(bk.retISBN(), n) == 0) 
		{
            bk.showBook();
            isbnPresent = 1;
        }
    }
    system("pause");
    fp.close();
    if (isbnPresent == 0)
        cout << "\n\nBook does not exist";
    
}

void displaySpecificStudent(char n[]) 
{
    cout << "\nSTUDENT DETAILS\n";
    int stPresent = 0;
    fp.open("student.dat", ios::in);
    while (fp.read(reinterpret_cast<char*>(&st), sizeof(Student))) 
	{
        if ((strcmpi(st.retAdmno(), n) == 0)) 
		{
            st.showStudent();
            stPresent = 1;
        }
    }
    system("pause");
    fp.close();
    if (stPresent == 0)
        cout << "\n\nStudent does not exist";
}

void modifyBook() 
{
    char n[20];
    int stPresent = 0;
    system("cls");
    cout << "\n\n\tMODIFY BOOK RECORD.... ";
    cout << "\n\n\tEnter The ISBN of The book: ";
    cin >> n;
    fp.open("book.dat", ios::in | ios::out);
    while (fp.read(reinterpret_cast<char*>(&bk), sizeof(Book)) && stPresent == 0) 
	{
        if (strcmpi(bk.retISBN(), n) == 0) 
		{
            bk.showBook();
            cout << "\nEnter The New Details of book" << endl;
            bk.modifyBook();
            int pos = -1 * static_cast<int>(sizeof(bk));
            fp.seekp(pos, ios::cur);
            fp.write(reinterpret_cast<char*>(&bk), sizeof(Book));
            cout << "\n\n\t Record Updated";
            stPresent = 1;
        }
    }
    fp.close();
    if (stPresent == 0)
        cout << "\n\n Record Not stPresent ";
    char ch=getchar();
}

void modifyStudent() 
{
    char n[15];
    int stPresent = 0;
    system("cls");
    cout << "\n\n\tMODIFY STUDENT RECORD... ";
    cout << "\n\n\tEnter The admission no. of The student: ";
    cin >> n;
    fp.open("student.dat", ios::in | ios::out);
    while (fp.read(reinterpret_cast<char*>(&st), sizeof(Student)) && stPresent == 0) 
	{
        if (strcmpi(st.retAdmno(), n) == 0) 
		{
            st.showStudent();
            cout << "\nEnter The New Details of student" << endl;
            st.modifyStudent();
            int pos = -1 * static_cast<int>(sizeof(st));
            fp.seekp(pos, ios::cur);
            fp.write(reinterpret_cast<char*>(&st), sizeof(Student));
            cout << "\n\n\t Record Updated";
            stPresent = 1;
        }
    }
    fp.close();
    if (stPresent == 0)
        cout << "\n\n Record Not stPresent ";
    char ch=getchar();
}

void deleteStudent() 
{
    fstream fp1;
	char n[15];
    int stPresent = 0;
    system("cls");
    cout << "\n\n\n\tDELETE STUDENT...";
    cout << "\n\nEnter The admission no. of the Student You Want To Delete:  ";
    cin >> n;
    fp.open("student.dat", ios::in | ios::out); 
    fp1.open("Temp.dat", ios::out);
    fp.seekg(0, ios::beg);
    while (fp.read(reinterpret_cast<char*>(&st), sizeof(Student))) 
	{
        if (strcmpi(st.retAdmno(), n) != 0)
            fp1.write(reinterpret_cast<char*>(&st), sizeof(Student));
        else
            stPresent = 1;
    }
    fp1.close();
    fp.close();
    remove("student.dat");
    rename("Temp.dat", "student.dat");
    if (stPresent == 1)
        cout << "\n\n\tRecord Deleted ..";
    else
        cout << "\n\nRecord not Present";
        system("pause");
}

void deleteBook() 
{
    fstream fp1;
    fstream fp3;
    int isbnPresent = 0;
	char n[20];
    system("cls");
    cout << "\n\n\n\tDELETE BOOK ...";
    cout << "\n\nEnter The ISBN of the Book You Want To Delete: ";
    cin >> n;
    fp3.open("student.dat",ios::in);
    while(fp3.read(reinterpret_cast<char*>(&st), sizeof(Student))&& (strcmpi(st.retStISBN(),n) == 0) && (st.retToken()==1))
	{
	cout<<"Book is issued , cannot be deleted"<<endl;
	fp3.close();
	system("pause");	
	return ;
	}
		fp.open("book.dat", ios::in | ios::out);
		    fp1.open("Temp.dat", ios::out);
    fp.seekg(0, ios::beg);
    while (fp.read(reinterpret_cast<char*>(&bk), sizeof(Book))) 
	{
        if (strcmpi(bk.retISBN(), n) != 0)
            fp1.write(reinterpret_cast<char*>(&bk), sizeof(Book));
     else
            isbnPresent = 1;
	}
    fp1.close();
    fp.close();
    
    remove("book.dat");
    rename("Temp.dat", "book.dat");
    if (isbnPresent == 1)
        cout << "\n\n\tRecord Deleted ..";
    else
        cout << "\n\nRecord not Present";
    system("pause");
}

void displayAllStudents() 
{
    system("cls");
    fp.open("student.dat", ios::in);
    if (!fp) {
        cout << "ERROR!!! FILE COULD NOT BE OPEN ";
        getch();
        return;
    }

    cout << "\n\n\t\tSTUDENT LIST\n\n";
    cout << left << setw(20) << "Admission No. " << setw(30) << "Name "<< setw(35) << "Course " << setw(35) << "Stream "<< setw(15) << "Year " << setw(15) << "Book Issued " << endl;
    while (fp.read((char*)&st,sizeof(Student))) 
	{
        st.report();
        
    }
    system("pause");
	fp.close();
}

void displayAllBooks() 
{
    system("cls");
    fp.open("book.dat", ios::in);
    if (!fp) 
	{
        cout << "ERROR!!! FILE COULD NOT BE OPEN ";
        getch();
        return ;
    }

    cout << "\n\n\t\tBook LIST\n\n";
    cout << left << setw(10) << "ISBN " << setw(50) << "Book Name " << setw(25) << "Author " << endl;
   
		while(fp.read((char*)&bk,sizeof(Book)))
	{
		bk.report();               
	}
	getch();
	fp.close();
}
fstream fp2;
void bookIssue() 
{
    char sn[20], bn[20];  //student no. and book no.
    int stPresent = 0;  //student hai ki nhi
	int isbnPresent = 0; //iss ISBN ki book hai yaa nhi
    system("cls");
    cout << "\n\nBOOK ISSUE ...";
    cout << "\n\n\tEnter The student's admission no.: ";
    cin >> sn;
    fp.open("student.dat", ios::in | ios::out);
    fp2.open("book.dat", ios::in | ios::out);
    while (fp.read(reinterpret_cast<char*>(&st), sizeof(Student)) && stPresent == 0) 
	{
        if (strcmpi(st.retAdmno(), sn) == 0) 
		{
            stPresent = 1;
            if (st.retToken() == 0) 
			{
                cout << "\n\n\tEnter the ISBN: ";
                cin >> bn;
                while (fp2.read(reinterpret_cast<char*>(&bk), sizeof(Book)) && isbnPresent == 0) 
				{
                    if (strcmpi(bk.retISBN(), bn) == 0) 
					{
                        bk.showBook();
                        isbnPresent = 1;
                        st.addToken();
                        st.getStISBN(bk.retISBN());
                        int pos = -1 * static_cast<int>(sizeof(st));
                        fp.seekp(pos, ios::cur);
                        fp.write(reinterpret_cast<char*>(&st), sizeof(Student));
                        cout << "\n\n\t Book issued successfully\n\nPlease Note: Write the current date in backside of your book and submit within 15 days fine Rs. 1 for each day after 15 days period"<<endl;
                    }
                }
                if (isbnPresent == 0)
                    cout << "This ISBN book does not exist"<<endl;
            } else
                cout << "You have not returned the last book "<<endl;
        }
    }
    if (stPresent == 0)
        cout << "Student record not exist..."<<endl;
    system("pause");
    fp.close();
    fp2.close();
}

void bookDeposit() 
{
    char sn[6], bn[6];
    int stPresent = 0, isbnPresent = 0, day, fine;
    system("cls");
    cout << "\n\nBOOK DEPOSIT ...";
    cout << "\n\n\tEnter The student’s admission no.: ";
    cin >> sn;
    fp.open("student.dat", ios::in | ios::out);
    fp2.open("book.dat", ios::in | ios::out);
    while (fp.read(reinterpret_cast<char*>(&st), sizeof(Student)) && stPresent == 0) 
	{
        if (strcmpi(st.retAdmno(), sn) == 0) 
		{
            stPresent = 1;
            if (st.retToken() == 1) 
			{
                while (fp2.read(reinterpret_cast<char*>(&bk), sizeof(Book)) && isbnPresent == 0) 
				{
                    if (strcmpi(bk.retISBN(), st.retStISBN()) == 0) 
					{
                        bk.showBook();
                        isbnPresent = 1;
                        cout << "\n\nBook deposited in no. of days:  ";
                        cin >> day;
                        if (day > 15) 
						{
                            fine = (day - 15) * 1;
                            cout << "\n\nFine has to deposited Rs. " << fine;
                        }
                        st.resetToken();
                        int pos = -1 * static_cast<int>(sizeof(st));
                        fp.seekp(pos, ios::cur);
                        fp.write(reinterpret_cast<char*>(&st), sizeof(Student));
                        cout << "\n\n\t Book deposited successfully"<<endl;
                    }
                }
                if (isbnPresent == 0){
				cout << "Book no. does not exist or book record has been deleted"<<endl;
				}
                    
            } else
                cout << "No book is issued..please check!!"<<endl;
        }
    }
    if (stPresent == 0)
        cout << "Student record not exist..."<<endl;
    system("pause");
    fp.close();
    fp2.close();
}

void intro() 
{
    system("cls");
    setCentre();
    cout << "Welcome to LIBRARY MANAGEMENT SYSTEM"<<endl;
    cout << "\n\nMADE BY : Hammir Chaturvedi"<<endl;
    cout<<"\n\nCOURSE and BRANCH : B.tech. Electronics & Communication"<<endl;
    cout << "\n\nCollege : SKIT";
	cin.get();
}

void bookSection()
{
	system("cls");
	int ch5;
	cout << "\n\n\nWelcome to Book Section ";
	cout << "\n\n\t01.Create Book ";
    cout << "\n\n\t02.Display All Books ";
    cout << "\n\n\t03.Search Specific Book ";
    cout << "\n\n\t04.Modify Book ";
    cout << "\n\n\t05.Delete Book ";
	cout << "\n\n\t06.Go Back ";
	cout << "\n\n\tPlease Enter Your Choice: ";
	cin>>ch5;
	switch(ch5)
	{
		case 1:
			system("cls");
            writeBook();
            break;
        case 2:
            displayAllBooks();
            break;
		case 3:
            char num[15];
            system("cls");
            cout << "\n\n\tPlease Enter The ISBN No.: ";
            cin >> num;
            displaySpecificBook(num);
            break;
        case 4:
            modifyBook();
            break;
        case 5:
            deleteBook();
            break;
		case 6:
			return;
		default:
            cout <<"Invalid choice\n";
            system("pause");
	}
	bookSection();
}

void studentSection()
{
	system("cls");
	int ch4;
	cout << "\n\n\n Welcome to Student Section ";
	cout << "\n\n\t01.Create Student Record";
    cout << "\n\n\t02.Display All Students Record";
    cout << "\n\n\t03.Search Specific Student Record ";
    cout << "\n\n\t04.Modify Student Record";
    cout << "\n\n\t05.Delete Student Record";
    cout << "\n\n\t06.Go Back ";
    cout << "\n\n\tPlease Enter Your Choice: ";
    cin>>ch4;
	switch(ch4)
	{
		case 1:
			system("cls");
            writeStudent();
            break;
        case 2:
            displayAllStudents();
            break;
		case 3:
            char num[15];
            system("cls");
            cout << "\n\n\tPlease Enter The Admission No.: ";
            cin >> num;
            displaySpecificStudent(num);
            break;
        case 4:
            modifyStudent();
            break;
        case 5:
            deleteStudent();
            break;
		case 6:
			return;
		default:
            cout <<"Invalid choice\n";
            system("pause");
	}
	studentSection();
}

void libWindow() 
{
    system("cls");
    int ch2;
    cout << "\n\n\n\tLIBRARIAN WINDOW";
    cout << "\n\n\t01.STUDENT SECTION";
    cout << "\n\n\t02.BOOKS SECTION";
    cout << "\n\n\t03.BACK TO MAIN MENU";
    cout << "\n\n\tPlease Enter Your Choice: ";
    cin >> ch2;
    switch (ch2) 
	{
        case 1:
            system("cls");
            studentSection();
            break;
        case 2:
            bookSection();
            break;
        case 3:
            return;
        default:
            cout <<"Invalid choice\n";
            system("pause");
    }
    libWindow();
}

void studentCorner()
{
	system("cls");
	int ch3;
	cout << "\n\n\n\tSTUDENT CORNER"<<endl;
	cout << "\n\n\t01. Issue New Book";
    cout << "\n\n\t02. Deposit Book";
    cout << "\n\n\t03. Back To Main Menu";
    cout << "\n\n\tPlease Enter Your Choice: ";
	cin>>ch3;
    switch(ch3)
    {
    	case 1:
    		system("cls");
                bookIssue();
                break;
        case 2:
                bookDeposit();
                break;        
    	case 3:
            return;
		default:
                cout <<"Invalid choice\n";
                system("pause");
	}
	studentCorner();	
}

int main() 
{
    int ch;
    intro();
    do 
	{
        system("cls");
        cout << "\n\n\n\tMAIN MENU"<<endl;
        cout << "\n\n\t01. STUDENT CORNER";
        cout << "\n\n\t02. LIBRARIAN WINDOW";
        cout << "\n\n\t03. EXIT";
        cout << "\n\n\tPlease Enter Your Choice: ";
        cin>>ch;
        switch (ch) 
		{
            case 1:
                system("cls");
                studentCorner();
                break;
            case 2:
                libWindow();
                break;
            case 3:
                exit(0);
                break;
            default:
                cout <<"Invalid choice\n";
                system("pause");
        }
    } while (ch != 3);
    
    return 0;
}

