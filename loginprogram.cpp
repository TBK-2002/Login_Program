#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct user
{
    int id;
    string username, password, email, mobile;
    user(int i, string u = " ", string p = " ", string e = " ", string m = " "){
        id = i;
        username = u;
        password = p;
        email = e;
        mobile = m;
    }
};

void read(), write(user user1), register_new_user(), login(), change_pass();
char action();

int users_count;
vector<user> users;

int main(){
    read();
    char input;
    while(input != '4'){
        input = action(); // Letting the user choose the action he wants to do.
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
    string u, p, e, m;
    fstream data_file;
    data_file.open("users_data.txt", ios::in);
    while(!data_file.eof()){
        if (i % 4 == 0){
            id = i/4;
            getline(data_file, u);
        }
        else if (i % 4 == 1){
            getline(data_file, p);
        }
        else if (i % 4 == 2){
            getline(data_file, e);
        }
        else if (i % 4 == 3){
            getline(data_file, m);
            users.push_back(user(id, u, p, e, m));
        }
        i++;
    }
    users_count = i / 4;
    data_file.close();
    // cout << users[0].id << endl;
    // cout << users[0].username << endl;
    // cout << users[0].password << endl;
    // cout << users[0].email << endl;
    // cout << users[0].mobile << endl;
    // cout << users[1].id << endl;
    // cout << users[1].username << endl;
    // cout << users[1].password << endl;
    // cout << users[1].email << endl;
    // cout << users[1].mobile << endl;
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
    string u, p, e, m;
    cout << "Please choose your username: ";
    cin >> u;
    cout << "\nPlease choose a password: ";
    cin >> p;
    cout << "\nPlease enter your email: ";
    cin >> e;
    cout << "\nPlease enter your mobile: ";
    cin >> m;
    user user1(users_count, u, p, e, m);
    users.push_back(user1);
    write(user1);
}

void write(user user1){
    fstream data_file("users_data.txt", ios::app);
    data_file << '\n' << user1.username;
    data_file << '\n' << user1.password;
    data_file << '\n' << user1.email;
    data_file << '\n' << user1.mobile;
	data_file.close();
}

void login(){

}

void change_pass(){

}