#include "Book.h"
#include <iostream>
#include <stdexcept>
Book::Book(std::string t, std::string a, int y, std::string i) 
    : title(t), author(a), year(y), isbn(i), available(true), borrowedBy("") {
    if (year < 1450 || year > 2025) {
        throw std::invalid_argument("Год должен быть между 1450 и 2025");
    }
    if (isbn.empty()) {
        throw std::invalid_argument("ISBN не может быть пустым");
    }
}
std::string Book::getTitle() const { return title; }
std::string Book::getAuthor() const { return author; }
int Book::getYear() const { return year; }
std::string Book::getIsbn() const { return isbn; }
bool Book::getAvailable() const { return available; }
std::string Book::getBorrowedBy() const { return borrowedBy; }
void Book::borrowBook(std::string userName) {
    if (!available) {
        throw std::runtime_error("Книга уже выдана");
    }
    available = false;
    borrowedBy = userName;
}
void Book::returnBook() {
    if (available) {
        throw std::runtime_error("Книга уже доступна");
    }
    available = true;
    borrowedBy = "";
}
void Book::displayInfo() const {
    std::cout << "Название: " << title << std::endl;
    std::cout << "Автор: " << author << std::endl;
    std::cout << "Год: " << year << std::endl;
    std::cout << "ISBN: " << isbn << std::endl;
    if (available) {
        std::cout << "Статус: Доступна" << std::endl;
    } else {
        std::cout << "Статус: Выдана: " << borrowedBy << std::endl;
    }
}
