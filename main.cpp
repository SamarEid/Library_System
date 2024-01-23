#include <bits/stdc++.h>
using namespace std;
map <string,vector<string>> borrow;
map<string,int> name_id;
map<string,vector<int>> user_books;
int added = 0;
map<string,vector<string>> mp;
map<string,int> total_quantity;
struct book{
    int id;
    string name;
    int quantity;

    void read(){
        cout << "Enter book info: id & name & quantity: ";
        cin >> id >> name >> quantity;
    }
    void print(){
        cout <<"id = " <<  id << " name = " << name << " total_quantity =  " << quantity << " total_borrowed = " << quantity - total_quantity[name]<< endl;
    }
};
vector<book> books;

void add_book(){
    book newBook;
    newBook.read();
    total_quantity[newBook.name] = newBook.quantity;
    name_id[newBook.name] = newBook.id;
    books.push_back(newBook);
    string cur = "";
    for(auto c:books[added].name)
        cur += c,mp[cur].push_back(books[added].name);
    added++;
}
void search_by_prefix(){
    cout << "Enter book name prefix: ";
    string x;
    cin >> x;
    int flag = 0;
    for (auto c:mp[x])
        cout << c << endl, flag++;
    if (flag == 0)
        cout << "NO books with such prefix" << endl;
}

struct user{
    int id;
    string name;
    void read(){
        cout << "Enter user info: name & id: ";
        cin >> name >> id;
    }
    void print(){
        cout << "user: " << name << " id: " << id << " borrowed books ids: ";
        for(auto c: user_books[name])
            cout << c << " ";
        cout << endl;
    }
};
vector<user> users;
void add_user(){
    user newUser;
    newUser.read();
    users.push_back(newUser);

}
void print_users(){
    for (int i = 0; i < users.size(); i++)
        users[i].print();
}
void print_who_borrowed_book_by_name(){
    cout << "Enter book name: ";
    string x;
    cin >> x;
    int flag = 0;
    for(auto cur: borrow[x])
        cout << cur << endl, flag++;
    if (flag == 0)
        cout << "Invalid book name" << endl;
}

bool cmp_by_id(book &a, book &b){
    return a.id < b.id;
}
bool cmp_by_name(book &a, book &b){
    return a.name < b.name;
}
void print_books_by_id(){
    sort(books.begin(),books.end(), cmp_by_id);
    cout << "\n";
    for (int i = 0; i < books.size(); i++)
         books[i].print();
    cout << endl;
}
void print_books_by_name(){
    sort(books.begin(),books.end(), cmp_by_name);
    cout << "\n";
    for (int i = 0; i < books.size(); i++)
        books[i].print();
    cout << endl;
}
void user_borrow_book(){
    cout << "Enter user name and book name: ";
    string userName, bookName;
    cin >> userName >> bookName;

    if (total_quantity[bookName] > 0) {
        total_quantity[bookName]--;
        user_books[userName].push_back(name_id[bookName]);
    }
    else
        cout << "All copies are borrowed!!" << endl;
    borrow[bookName].push_back(userName);
}
void user_return_book() {
    cout << "Enter book name & user name: ";
    string userName, bookName;
    cin >> userName >> bookName;

    auto user_books_it = std:: find(user_books[userName].begin(), user_books[userName].end(),name_id[bookName]);
    if (user_books_it != user_books[userName].end()) {
        user_books[userName].erase(user_books_it);
        total_quantity[bookName]++;

        auto borrow_it = std::find(borrow[bookName].begin(), borrow[bookName].end(), userName);
        if (borrow_it != borrow[bookName].end())
            borrow[bookName].erase(borrow_it);
    }
    else
        cout << "Book was never borrowed by user!!" << endl;
}


int main() {
    cout << "\nLibrary Menu;\n";
    cout << "1) add_book\n";
    cout << "2) search_books_by_prefix\n";
    cout << "3) print_who_borrowed_book_by_name\n";
    cout << "4) print_library_by_id\n";
    cout << "5) print_library_by_name\n";
    cout << "6) add_user\n";
    cout << "7) user_borrow_book\n";
    cout << "8) user_return_book\n";
    cout << "9) print_users\n";
    cout << "10) Exit\n";
    cout << "________________________________________" << endl;

    while(true){
        cout << "Enter your choice [1 - 10]: ";
        int choice;
        cin >> choice;
        if (choice == 1)
            add_book();
        else if (choice == 2)
            search_by_prefix();
        else if (choice == 3)
            print_who_borrowed_book_by_name();
        else if (choice == 4)
            print_books_by_id();
        else if (choice == 5)
            print_books_by_name();
        else if (choice == 6)
            add_user();
        else if (choice == 7)
            user_borrow_book();
        else if (choice == 8)
            user_return_book();
        else if (choice == 9)
            print_users();
        else if (choice == 10)
            break;
        else
            cout << "INVALID CHOICE!!!!";
    }


    return 0;
}

