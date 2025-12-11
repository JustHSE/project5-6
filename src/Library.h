#ifndef LIBRARY_H
#define LIBRARY_H
#include "Book.h"
#include "User.h"
#include <vector>
#include <string>
class Library {
private:
    std::vector<Book> books;
    std::vector<User> users;
    std::string dataFile; 
public:
    Library(std::string filePath);
    void addBook(const Book& book);
    void addUser(const User& user);
    void borrowBook(std::string userName, std::string isbn);
    void returnBook(std::string isbn);
    Book* findBookByISBN(std::string isbn);
    User* findUserByName(std::string name);
    void displayAllBooks() const;
    void displayAllUsers() const;
    void saveToFile() const;
    void loadFromFile();
};
#endif