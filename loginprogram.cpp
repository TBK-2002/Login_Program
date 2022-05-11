// FCI – Programming 1 – 2022 - Assignment 4
// Program Name: loginprogram.cpp
// Last Modification Date: 4/5/2022
// Author 1: Nour El-Din Ahmed Hussein - 20210430 - Group A - s5
// Author 2: Mohanad Hisham El-Tahawy - 20210413 - Group A - s5
// Author 3: Nour Omar - -
// Teaching Assistant: Hagar Ali
// Purpose: Login program.

#include <iostream>
#include <fstream>
#include <vector>
#include <conio.h>
#include <regex>

using namespace std;

struct user
{
    int id;
    string name, username, password, email, mobile;
    user(int i, string n = " ",string u = " ", string p = " ", string e = " ", string m = " "){
        id = i;
        name = n;
        username = u;
        password = p;
        email = e;
        mobile = m;
    }
};

void read(), write(user user1), get_name(string& n), get_user(string& u), get_pass(string& p), get_email(string& e), get_mobile(string& m), register_new_user(), login(), change_pass(), write_all();
char action();
bool check_pass();
string encrypt(string p), decrypt(string p);

int users_count, id, tries;
bool isLoggedIn = false;
vector<user> users;
const char BACKSPACE = 127;
const char RETURN = 10;


int main(){
    read();
    char input;
    while(input != '4'){
        input = action(); // Letting the user choose the action he wants to do.
        tries = 0;
        switch (input)
        {
        case '1':
            register_new_user();
            break;
        
        case '2':
            login();
            break;
        
        case '3':
            change_pass();
            break;
        
        case '4':
            cout << "Thanks for using our program. \n";
            break;

        default:
            cout << "Invalid input! \n";
            break;
        }
    }
    return 0;
}

void read(){
    int id, i = 0;
    string n, u, p, e, m;
    fstream data_file;
    data_file.open("users_data.txt", ios::in);
    while(!data_file.eof()){
        if (i % 5 == 0){
            id = i/5;
            getline(data_file, n);
        }
        else if (i % 5 == 1){
            getline(data_file, u);
        }
        else if (i % 5 == 2){
            getline(data_file, p);
        }
        else if (i % 5 == 3){
            getline(data_file, e);
        }
        else if (i % 5 == 4){
            getline(data_file, m);
            users.push_back(user(id, n, u, decrypt(p), e, m));
        }
        i++;
    }
    users_count = i / 5;
    data_file.close();
}

char action(){
    char input;
    cout << "Please choose one of the following actions: \n"
         << "1 - Register new user. \n"
         << "2 - Login. \n"
         << "3 - Change password. \n"
         << "4 - Exit. \n";
    cin >> input;
    return input;
}

void register_new_user(){
    string n, u, p, e, m;
    get_name(n);
    get_user(u);
    get_pass(p);
    get_email(e);
    get_mobile(m);
    users.push_back(user(users_count, n, u, p, e, m));
    write(users[users_count]);
    cout << "Your account has been created succesfully your id is: " << users_count << endl;
    users_count++;
}

void get_name(string& n){
    cout << "Please enter your name: ";
    cin.ignore(256, '\n');
    getline(cin, n);
    regex valid_name("[a-zA-Z-]+");
    if (!(regex_match(n,valid_name))){
        cout << "Please enter a valid name that contains characters and '-' only " << endl;
        get_name(n);
    }
}

void get_user(string& u){
    cout << "Please choose your username: ";
    cin >> u;
    cin.ignore(256, '\n');
    for(int i = 0; i < users_count; i++){
        if(u == users[i].username){
            cout << "This username does already exist, try again.\n";
            get_user(u);
            break;
        }
    }
}

void get_pass(string& p){
    char ch;
    string again;
    cout << "Please choose a password: "; // Write the conditons of strong password to the user.
    while((ch = getch()) != RETURN){
        if(ch == BACKSPACE){
            if(p.length() != 0){
                cout << "\b \b";
                p.resize(p.length()-1);
            }
        }
        else{
            p+= ch;
            cout << '*';
        }
    }
    // Strong password conditions use string.find(char).
    cout << "\nEnter your password again: ";
    while((ch = getch()) != RETURN){
        if(ch == BACKSPACE){
            if(again.length() != 0){
                cout << "\b \b";
                again.resize(again.length()-1);
            }
        }
        else{
            again+= ch;
            cout << '*';
        }
    }
    cout << endl;
    if(p != again){
        cout << "\nPassword does not match, Please try again.\n";
        p = "";
        get_pass(p);
    }
}

void get_email(string& e){
    cout << "\nPlease enter your email: ";
    cin >> e;
    cin.ignore(256, '\n');
    for(int i = 0; i < users_count; i++){
        if(e == users[i].email){
            cout << "This email does already exist, try again.\n";
            get_user(e);
            break;
        }
    }
    regex valid_email("([\\w!#$%&'*+/=?^_`{|}~-]+[\\w!#$%&'.*+/=?^_`{|}~-]*[\\w!#$%&'*+/=?^_`{|}~-]+)@[\\w]+[\\w-]*(\\.[\\w-]+)+[\\w]+");
    if(regex_match(e,valid_email) == true){
        cout << "Succesfull Email !! " << endl;

    }
    else{
        cout << "Please enter a valid email ";
        get_email(e);
    }
}

void get_mobile(string& m){
    cout << "Please enter your mobile: ";
    cin >> m;
    // Right mobile conditions use regex bardo.
}

void write(user user1){
    fstream data_file("users_data.txt", ios::app);
    data_file << user1.name << '\n';
    data_file << user1.username << '\n';
    string pass = encrypt(user1.password);
    data_file << pass << '\n';
    data_file << user1.email << '\n';
    data_file << user1.mobile << '\n';
	data_file.close();
}

string encrypt(string p){
    string enc = "";
    for(char c: p){
        int x = c - 'A';
        x = (5 * x + 8) % 26;
        enc+= (char) x + 'A';
    }
    return enc;
}

string decrypt(string p){
    string dec = "";
    for(char c: p){
        int y = c - 'A';
        y = 21 * (y - 8);
        y = ((y % 26) + 26) % 26;
        dec+= (char) y + 'A';
    }
    return p;
}

void login(){
    isLoggedIn = false;
    char ch;
    while(!isLoggedIn){
        string p = "";
        cout << "Please enter your ID: ";
        cin >> ch;
        id = ch - '0';
        cin.ignore(256, '\n');
        if(id >= users_count){
            cout << "There is no registered user with this ID.\n";
        }
        else{
            if(check_pass()){
                cout << "Login Succesful\n";
                isLoggedIn = true;
            }
            else{
                break;
            }
        }
    }
}

void change_pass(){
    string p;
    cout << "Please login first.\n";
    login();
    if(isLoggedIn && check_pass()){
        get_pass(p);
        users[id].password = p;
        write_all();
    }
}

bool check_pass(){
    char ch;
    string p;
    cout << "Please enter your password: ";
    while((ch = getch()) != RETURN){
        if(ch == BACKSPACE){
            if(p.length() != 0){
                cout << "\b \b";
                p.resize(p.length()-1);
            }
        }
        else{
            p+= ch;
            cout << '*';
        }
    }
    cout << endl;
    if(p == users[id].password){
        return true;
    }
    else{
        cout << "\nIcorrect password please try again.\n";
        tries++;
        if(tries == 3){
            cout << "You are denied to access system\n";
            return false;
        }
        return check_pass();
    }
}

void write_all(){
    fstream data_file("users_data.txt", ios::out);
    for(int i = 0; i < users_count; i++){
        data_file << users[i].name << '\n';
        data_file << users[i].username << '\n';
        string pass = encrypt(users[i].password);
        data_file << pass << '\n';
        data_file << users[i].email << '\n';
        data_file << users[i].mobile << '\n';
    }
	data_file.close();
}
