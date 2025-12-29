// creating a mini library management system where a student can issue and return a book with dues dates, fine calculation,
// searching by author name, book id,title.

#include <bits/stdc++.h>
#include <iostream>
#include <unordered_map>
#include <string>
#include <ctime>
#include <algorithm>
#include <limits>

using namespace std;

// Book class
class Book
{
private:
    int bookId;
    string bookName;
    string bookAuthor;
    bool isIssued;

public:
    Book() : bookId(-1), bookName(""), bookAuthor(""), isIssued(false) {}

    Book(int id, string title, string author) // constructor
        : bookId(id), bookName(title), bookAuthor(author), isIssued(false) {};

    // read only
    int getId() const { return bookId; }
    string getTitle() const { return bookName; }
    string getAuthor() const { return bookAuthor; }
    bool issued() const { return isIssued; }

    void issuedBook()
    {
        isIssued = true;
    }
    void returnedBook()
    {
        isIssued = false;
    }
};

// Student class
class Student
{
    int stuId;
    string stuName;

public:
    unordered_map<int, time_t> issuedBook; // will store the data of issued book along with date
    Student() : stuId(-1), stuName("") {}
    Student(int id, string name)
    { // constructor
        stuId = id;
        stuName = name;
    }
};

// library management class
class LibraryManagement
{
    unordered_map<int, int> bookToStudent; // bookId -> studentId
    unordered_map<int, Book> books;        // help to store book data
    unordered_map<int, Student> students;  // help to student data
    const int perDayFine = 10;             // fine per day on late submission
    const int allowedDays = 7;

public:
    void addBook(int id, string name, string author)
    {
        // what if the book already exist in their system
        if (books.find(id) != books.end())
        {
            cout << "Book already exist\n"
                 << endl;
            return;
        }

        string newTitle = toLower(name);
        string newAuthor = toLower(author);

        // Check duplicate title + author
        for (const auto &pair : books)
        {
            const Book &b = pair.second;
            if (toLower(b.getTitle()) == newTitle &&
                toLower(b.getAuthor()) == newAuthor)
            {
                cout << "This book already exists in the library\n";
                return;
            }
        }

        books.emplace(id, Book{id, name, author});
    };

    void removeBook(int id)
    {
        auto it = books.find(id);
        if (it == books.end())
        {
            cout << "We don't have this book\n";
            return;
        }
        if (it->second.issued())
        {
            cout << "Book is currently issued\n";
            return;
        }
        books.erase(id);
        cout << "Book Removed Successfully!\n";
    }

    // Student
    void issuedBook(int stuId, int bookId)
    {
        // 1. Check if book exists
        if (books.find(bookId) == books.end())
        {
            cout << "Book is not available, Sorry!" << endl;
            return;
        }

        // 2. Check if student exists
        if (students.find(stuId) == students.end())
        {
            cout << "Student not found. Please add student first." << endl;
            return;
        }

        Book &book = books[bookId];
        Student &student = students[stuId];

        // 3. Check if book is already out
        if (book.issued())
        {
            cout << "Book already issued!" << endl;
            return;
        }

        // 4. Check limit
        if (student.issuedBook.size() >= 3)
        {
            cout << "Book limit exceeded (Max 3)\n";
            return;
        }

        // SUCCESS: Mark as issued (Corrected function call here)
        book.issuedBook();

        student.issuedBook[bookId] = time(nullptr);
        bookToStudent[bookId] = stuId;

        cout << "Book Issued Successfully!" << endl;
        time_t issueTime = student.issuedBook[bookId];
        cout << "Book issued on: " << ctime(&issueTime);
        time_t due = issueTime + (long)allowedDays * 24 * 60 * 60;
        cout << "Due date: " << ctime(&due);
    }

    void returnBook(int bookId, int stuId)
    {
        if (books.find(bookId) == books.end() || students.find(stuId) == students.end())
        {
            cout << "Invalid Book or Student ID\n";
            return;
        }

        Student &student = students[stuId];
        if (student.issuedBook.find(bookId) == student.issuedBook.end())
        {
            cout << "This book was not issued by this student\n";
            return;
        }

        int fine = calculateFine(student.issuedBook[bookId]);
        if (fine > 0)
            cout << "Late fine: Rs. " << fine << endl;

        books[bookId].returnedBook();
        student.issuedBook.erase(bookId);
        bookToStudent.erase(bookId); // Clean up the mapping
        cout << "Book returned successfully!\n";
    }

    int calculateFine(time_t issueDate)
    {
        time_t currentDate = time(nullptr);

        int overDays = (currentDate - issueDate) / (60 * 60 * 24);

        if (overDays <= allowedDays)
        {
            return 0;
        }

        return (overDays - allowedDays) * perDayFine;
    }

    void searchByTitle(string title)
    {
        bool found = false;

        for (const auto &pair : books)
        {
            const Book &b = pair.second;
            string search = toLower(title);

            if (toLower(b.getTitle()) == search)
            {
                cout << "Found: " << b.getTitle()
                     << " by " << b.getAuthor() << endl;
                cout << (b.issued() ? " [Issued]\n" : " [Available]\n");
                found = true;
            }
        }

        if (!found)
            cout << "No book found with this title" << endl;
    }

    void searchByBookId(int bookID)
    {
        auto it = books.find(bookID);
        if (it == books.end())
        {
            cout << "Book not found\n"
                 << endl;
            return;
        }

        const Book &b = it->second;
        cout << b.getTitle() << " by " << b.getAuthor() << endl;
        cout << (b.issued() ? " [Issued]" : " [Available]");
    }

    void searchByAuthor(const string &author)
    {
        bool found = false;

        for (const auto &pair : books)
        {
            const Book &b = pair.second;
            string search = toLower(author);

            if (toLower(b.getAuthor()) == search)
            {
                cout << "Book Id: " << b.getId()
                     << " | " << b.getTitle();
                cout << (b.issued() ? " [Issued]\n" : " [Available]\n");
                found = true;
            }
        }

        if (!found)
            cout << "No book found for this author" << endl;
    }
    void addStudent(int stuId, string name)
    {
        if (students.find(stuId) != students.end())
        {
            cout << "Student already exists\n";
            return;
        }
        students.emplace(stuId, Student(stuId, name));
    }

    string toLower(string s)
    {
        transform(s.begin(), s.end(), s.begin(),
                  [](unsigned char c)
                  { return tolower(c); });
        return s;
    }
};

int main()
{
    LibraryManagement lm;
    int stuId, bookId;
    string bookName, authorName, stuName;

    while (true)
    {
        cout << "<------------------ Menu ---------------->" << endl;
        cout << "1. Issue a Book" << endl;
        cout << "2. Return a Book" << endl;
        cout << "3. Search a book(by Book name)" << endl;
        cout << "4. Search a book(by author name)" << endl;
        cout << "5. Search a book(by Book Id )" << endl;
        cout << "6. Add Book" << endl;
        cout << "7. Remove a Book" << endl;
        cout << "8. add Student" << endl;
        cout << "9. Exit" << endl;
        int choice;
        cin >> choice;
        if (!cin)
        {
            cin.clear(); // reset fail state
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Try again.\n";
            continue;
        }

        if (choice == 9)
        {
            cout << "Thank you for visiting. Happy Learning " << endl;
            return 0;
        }

        switch (choice)
        {
        case 1:
            cout << "Enter book Id:" << endl;
            cin >> bookId;

            cout << "enter student Id:\n";
            cin >> stuId;

            lm.issuedBook(stuId, bookId);
            break;

        case 2:
            cout << "Enter Book Id: " << endl;
            cin >> bookId;
            cout << "enter student Id:\n";
            cin >> stuId;

            lm.returnBook(bookId, stuId);
            break;

        case 3:
            cout << "Enter Book name:" << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, bookName);

            lm.searchByTitle(bookName);
            break;
        case 4:
            cout << "Enter Author name:" << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, authorName);

            lm.searchByAuthor(authorName);
            break;
        case 5:
            cout << "Enter Book Id" << endl;
            cin >> bookId;

            lm.searchByBookId(bookId);
            break;

        case 6:
            cout << "Enter book id:" << endl;
            cin >> bookId;
            cout << "Enter book name:" << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, bookName);
            cout << "Enter author name" << endl;
            getline(cin, authorName);

            lm.addBook(bookId, bookName, authorName);

            break;

        case 7:
            cout << "Enter book id:" << endl;
            cin >> bookId;

            lm.removeBook(bookId);
            break;
        case 8:
            cout << "Enter student Id" << endl;
            cin >> stuId;
            cout << "Enter student Name:" << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, stuName);
            lm.addStudent(stuId, stuName);
            break;
        default:
            cout << "Invalid choice, Bye Bye!" << endl;
        }
    }
}
