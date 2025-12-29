// creating a mini library management system where a student can issue and return a book with dues dates, fine calculation,
// searching by author name, book id,title.

#include <bits/stdc++.h>
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
    Student(int id, string name)
    { // constructor
        stuId = id;
        stuName = name;
    }
};

// library management class
class LibraryManagement
{
    unordered_map<int, Book> books;       // help to store book data
    unordered_map<int, Student> students; // help to student data
    const int perDayFine = 10;            // fine per day on late submission
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

        books.emplace(id, Book{id, name, author});
    };

    void removeBook(int id)
    {
        if (books.find(id) == books.end())
        {
            cout << "We don't have this book\n";
            return;
        }
        if (books[id].issued())
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
        if (books.find(bookId) == books.end())
        {
            cout << "Book is not available, Sorry!" << endl;
            return;
        }

        if (students.find(stuId) == students.end())
        {
            cout << "Student is not found" << endl;
            return;
        }

        Book &book = books[bookId];

        if (book.issued())
        {
            cout << "Book already issued!" << endl;
            return;
        }

        book.issued();

        students[stuId].issuedBook[bookId] = time(nullptr);

        cout << "Book Issued successFully!" << endl;
        cout << "Book issued on: " << ctime(&students[stuId].issuedBook[bookId]);
        time_t due = students[stuId].issuedBook[bookId] + allowedDays * 24 * 60 * 60;
        cout << "Due date: " << ctime(&due);
    }

    void returnBook(int bookId, int stuId)
    {

        if (books.find(bookId) == books.end())
            return;
        if (students.find(stuId) == students.end())
            return;

        auto &issued = students[stuId].issuedBook;

        Book &book = books[bookId];
        if (issued.find(bookId) == issued.end())
        {
            cout << "This book was not issued by the student\n";
            return;
        }

        int fine = calculateFine(issued[bookId]);
        if (fine > 0)
            cout << "Late fine: Rs. " << fine << endl;

        book.returnedBook();

        students[stuId].issuedBook.erase(bookId);
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

            if (b.getTitle() == title)
            {
                cout << "Found: " << b.getTitle() << " by " << b.getAuthor() << endl;
                cout << (b.issued() ? " [Issued]" : " [Available]");
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
            if (b.getAuthor() == author)
            {
                cout << "Book Id: " << b.getId() << " | " << b.getTitle() << endl;
                cout << (b.issued() ? " [Issued]" : " [Available]");

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
};

int main()
{
    LibraryManagement lm;
    int stuId, bookId;
    string bookName, authorName, stuName;

    while (true)
    {
        cout << "<------------------ Menu ---------------->" << endl;
        cout << "1.Issue a Book" << endl;
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
