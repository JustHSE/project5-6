#ifndef BOOK_H
#define BOOK_H
#include <string>
class Book {
private:
    std::string title;
    std::string author;
    int year;
    std::string isbn;
    bool available;
    std::string borrowedBy;
public:
    Book(std::string t, std::string a, int y, std::string i);
    std::string getTitle() const;
    std::string getAuthor() const;
    int getYear() const;
    std::string getIsbn() const;
    bool getAvailable() const;
    std::string getBorrowedBy() const;
    void borrowBook(std::string userName);
    void returnBook();
    void displayInfo() const;
};
#endif