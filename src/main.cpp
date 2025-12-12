#include "Library.h"
#include <iostream>
#include <limits>
void showMenu() {
    std::cout << "\n=== БИБЛИОТЕКА ===" << std::endl;
    std::cout << "1. Просмотреть все книги" << std::endl;
    std::cout << "2. Просмотреть всех пользователей" << std::endl;
    std::cout << "3. Добавить новую книгу" << std::endl;
    std::cout << "4. Зарегистрировать пользователя" << std::endl;
    std::cout << "5. Выдать книгу пользователю" << std::endl;
    std::cout << "6. Принять книгу от пользователя" << std::endl;
    std::cout << "7. Поиск книги по ISBN" << std::endl;
    std::cout << "8. Просмотреть профиль пользователя" << std::endl;
    std::cout << "9. Сохранить данные в файл" << std::endl;
    std::cout << "10. Выход" << std::endl;
    std::cout << "Ваш выбор: ";
}
int getNumber() {
    int num;
    std::cin >> num;
    std::cin.ignore();
    return num;
}
int main() {
    #ifdef _WIN32
        system("chcp 65001 > nul");
    #endif
    Library library("../data/library_data.txt");
    int choice = 0;
    while (choice != 10) {
        showMenu();
        std::cin >> choice;
        std::cin.ignore();
        try {
            if (choice == 1) {
                std::cout << "\n--- КНИГИ ---" << std::endl;
                library.displayAllBooks();
            } else if (choice == 2) {
                std::cout << "\n--- ПОЛЬЗОВАТЕЛИ ---" << std::endl;
                library.displayAllUsers();
            } else if (choice == 3) {
                std::string title, author, isbn;
                int year;
                std::cout << "Введите название книги: ";
                getline(std::cin, title);
                std::cout << "Введите автора: ";
                getline(std::cin, author);
                std::cout << "Введите год издания: ";
                year = getNumber();
                std::cout << "Введите ISBN: ";
                getline(std::cin, isbn);
                Book newBook(title, author, year, isbn);
                library.addBook(newBook);
                std::cout << "Книга добавлена!" << std::endl;
            } else if (choice == 4) {
                std::string name, userId;
                int maxBooks;
                std::cout << "Введите фамилию пользователя: ";
                getline(std::cin, name);
                std::cout << "Введите ID пользователя: ";
                getline(std::cin, userId);
                std::cout << "Введите лимит книг: ";
                std::cin >> maxBooks;
                std::cin.ignore();
                if (maxBooks <= 0) maxBooks = 3;
                User newUser(name, userId, maxBooks);
                library.addUser(newUser);
                std::cout << "Пользователь добавлен!" << std::endl;
            } else if (choice == 5) {
                std::string userName, isbn;
                std::cout << "Введите фамилию пользователя: ";
                getline(std::cin, userName);
                std::cout << "Введите ISBN книги: ";
                getline(std::cin, isbn);
                library.borrowBook(userName, isbn);
                std::cout << "Книга выдана!" << std::endl;
            } else if (choice == 6) {
                std::string isbn;
                std::cout << "Введите ISBN книги: ";
                getline(std::cin, isbn);
                library.returnBook(isbn);
                std::cout << "Книга возвращена!" << std::endl;
            } else if (choice == 7) {
                std::string isbn;
                std::cout << "Введите ISBN книги: ";
                getline(std::cin, isbn);
                Book* book = library.findBookByISBN(isbn);
                if (book != nullptr) {
                    std::cout << "\n--- НАЙДЕНА КНИГА ---" << std::endl;
                    book->displayInfo();
                else {
                    std::cout << "Пользователь не найден" << std::endl;
                }
                } else {
                    std::cout << "Книга не найдена" << std::endl;
                }
            } else if (choice == 8) {
                std::string userName;
                std::cout << "Введите фамилию пользователя: ";
                getline(std::cin, userName);
                User* user = library.findUserByName(userName);
                if (user != nullptr) {
                    std::cout << "\n--- ПРОФИЛЬ ---" << std::endl;
                    user->displayProfile();
                }
            } else if (choice == 9) {
                library.saveToFile();
                std::cout << "Данные сохранены!" << std::endl;
            } else if (choice == 10) {
                std::cout << "Выход" << std::endl;
            } else {
                std::cout << "Неверный выбор" << std::endl;
            }
        } catch (const std::exception& e) {
            std::cout << "Ошибка: " << e.what() << std::endl;
        }
    }
    return 0;
}
