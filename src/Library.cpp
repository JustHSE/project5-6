#include "Library.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
Library::Library(std::string filePath) : dataFile(filePath) {
    loadFromFile();
}
void Library::addBook(const Book& book) {
    if (findBookByISBN(book.getIsbn()) != nullptr) {
        throw std::runtime_error("Книга с таким ISBN уже есть");
    }
    books.push_back(book);
}
void Library::addUser(const User& user) {
    if (findUserByName(user.getName()) != nullptr) {
        throw std::runtime_error("Пользователь с такой фамилией уже есть");
    }
    users.push_back(user);
}
void Library::borrowBook(std::string userName, std::string isbn) {
    Book* book = findBookByISBN(isbn);
    User* user = findUserByName(userName);
    if (book == nullptr) throw std::runtime_error("Книга не найдена");
    if (user == nullptr) throw std::runtime_error("Пользователь не найден");
    if (!user->canBorrowMore()) throw std::runtime_error("Достигнут лимит книг");
    if (!book->getAvailable()) throw std::runtime_error("Книга уже выдана");
    book->borrowBook(userName);
    user->addBook(isbn);
}
void Library::returnBook(std::string isbn) {
    Book* book = findBookByISBN(isbn);
    if (book == nullptr) throw std::runtime_error("Книга не найдена");
    if (book->getAvailable()) throw std::runtime_error("Книга уже доступна");
    std::string userName = book->getBorrowedBy();
    User* user = findUserByName(userName);
    if (user != nullptr) {
        user->removeBook(isbn);
    }
    book->returnBook();
}
Book* Library::findBookByISBN(std::string isbn) {
    for (size_t i = 0; i < books.size(); i++) {
        if (books[i].getIsbn() == isbn) {
            return &books[i];
        }
    }
    return nullptr;
}
User* Library::findUserByName(std::string name) {
    for (size_t i = 0; i < users.size(); i++) {
        if (users[i].getName() == name) {
            return &users[i];
        }
    }
    return nullptr;
}
void Library::displayAllBooks() const {
    if (books.empty()) {
        std::cout << "Библиотека пуста" << std::endl;
        return;
    }
    for (const Book& book : books) {
        book.displayInfo();
        std::cout << "-------------------" << std::endl;
    }
}
void Library::displayAllUsers() const {
    if (users.empty()) {
        std::cout << "Нет пользователей" << std::endl;
        return;
    }
    for (const User& user : users) {
        user.displayProfile();
        std::cout << "-------------------" << std::endl;
    }
}
void Library::saveToFile() const {
    std::ofstream file(dataFile);
    if (!file) {
        throw std::runtime_error("Не удалось открыть файл");
    }
    for (const Book& book : books) {
        file << "BOOK\n";
        file << "Title: " << book.getTitle() << "\n";
        file << "Author: " << book.getAuthor() << "\n";
        file << "Year: " << book.getYear() << "\n";
        file << "ISBN: " << book.getIsbn() << "\n";
        file << "Available: " << (book.getAvailable() ? "yes" : "no") << "\n";
        file << "BorrowedBy: " << book.getBorrowedBy() << "\n\n";
    }
    file << "---USERS---\n\n";
    for (const User& user : users) {
        file << "USER\n";
        file << "Name: " << user.getName() << "\n";
        file << "UserID: " << user.getUserId() << "\n";
        file << "BorrowedBooks: ";
        std::vector<std::string> borrowed = user.getBorrowedBooks();
        for (size_t i = 0; i < borrowed.size(); i++) {
            file << borrowed[i];
            if (i != borrowed.size() - 1) file << "|";
        }
        file << "\n";
        file << "MaxBooks: " << user.getMaxBooks() << "\n\n"; 
    }
    file.close();
}
void Library::loadFromFile() {
    std::ifstream file(dataFile);
    if (!file.is_open()) {
        return;
    }
    books.clear();
    users.clear();
    std::string line;
    std::string currentSection = "BOOKS";
    while (getline(file, line)) {
        if (line == "---USERS---") {
            currentSection = "USERS";
            continue;
        }
        if (line == "BOOK") {
            std::string title, author, isbn, borrowedBy;
            int year;
            bool available;
            getline(file, line);
            title = line.substr(7);
            getline(file, line);
            author = line.substr(8);
            getline(file, line);
            year = stoi(line.substr(6));
            getline(file, line);
            isbn = line.substr(6);
            getline(file, line);
            std::string availableStatus = line.substr(10);
            available = (availableStatus == "yes");
            getline(file, line);
            borrowedBy = line.substr(12);
            if (!available && borrowedBy.empty()) {
                available = true;
            }
            getline(file, line);
            try {
                Book book(title, author, year, isbn);
                if (!available && !borrowedBy.empty()) {
                    book.borrowBook(borrowedBy);
                }
                books.push_back(book);
            } catch (...) {
            }
        }
        else if (line == "USER") {
            std::string name, userId, borrowedBooksStr;
            int maxBooks;
            getline(file, line);
            name = line.substr(6);
            getline(file, line);
            userId = line.substr(8);
            getline(file, line);
            borrowedBooksStr = line.substr(15);
            getline(file, line);
            maxBooks = stoi(line.substr(10));
            getline(file, line); 
            User user(name, userId, maxBooks);
            if (!borrowedBooksStr.empty()) {
                std::string isbn;
                std::stringstream bookStream(borrowedBooksStr);
                while (getline(bookStream, isbn, '|')) {
                    if (!isbn.empty()) {
                        try {
                            user.addBook(isbn);
                        } catch (...) {
                        }
                    }
                }
            }
            users.push_back(user);
        }
    }
    file.close();
}