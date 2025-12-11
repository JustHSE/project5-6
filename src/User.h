#ifndef USER_H
#define USER_H
#include <string>
#include <vector>
class User {
private:
    std::string name;
    std::string userId;
    std::vector<std::string> borrowedBooks;
    int maxBooks;
public:
    User(std::string n, std::string id, int max = 3);
    std::string getName() const;
    std::string getUserId() const;
    std::vector<std::string> getBorrowedBooks() const;
    int getMaxBooks() const;  
    bool canBorrowMore() const;
    void addBook(std::string isbn);
    void removeBook(std::string isbn);
    void displayProfile() const;
};
#endif