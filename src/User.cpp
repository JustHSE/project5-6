#include "User.h"
#include <iostream>
#include <stdexcept>
User::User(std::string n, std::string id, int max) 
    : name(n), userId(id), maxBooks(max) {}
std::string User::getName() const { return name; }
std::string User::getUserId() const { return userId; }
std::vector<std::string> User::getBorrowedBooks() const { return borrowedBooks; }
int User::getMaxBooks() const { return maxBooks; }
bool User::canBorrowMore() const {
    return borrowedBooks.size() < (size_t)maxBooks;
}
void User::addBook(std::string isbn) {
    if (!canBorrowMore()) {
        throw std::runtime_error("Достигнут лимит книг");
    }
    borrowedBooks.push_back(isbn);
}
void User::removeBook(std::string isbn) {
    for (size_t i = 0; i < borrowedBooks.size(); i++) {
        if (borrowedBooks[i] == isbn) {
            borrowedBooks.erase(borrowedBooks.begin() + i);
            return;
        }
    }
}
void User::displayProfile() const {
    std::cout << "Фамилия: " << name << std::endl;
    std::cout << "ID: " << userId << std::endl;
    std::cout << "Взятые книги: ";
    if (borrowedBooks.empty()) {
        std::cout << "нет";
    } else {
        for (std::string book : borrowedBooks) {
            std::cout << book << " ";
        }
    }
    std::cout << std::endl;
    std::cout << "Лимит: " << maxBooks << std::endl;
}