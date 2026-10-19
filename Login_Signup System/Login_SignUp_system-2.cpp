// build an login/signup system using cpp and file handling
// 1 update: want that the password should be visible in dotted form only 
// 2 Update: that data should be stored in an organized format like username category contains usernames and password category contains passwords.

#include<iostream>
#include<fstream>
#include<string>
#include<conio.h>
#include<cctype>

using namespace std; 

const string FILENAME = "usercredentials.txt"; 

// // function declarations
// bool userNameExists(string userName);   
// bool login(); 
// void signUp(); 
// bool forgetPassword(); 

// password input function
string getPassword(){
    string password; 
    int ch; 

    while(true){
        ch = _getch(); // read key without displaying it 

        if(ch == '\r') break; // enter key pressed, brea the loop 
        else if(ch == '\b'){
            if(!password.empty()){
                password.pop_back(); 
                cout<<"\b \b"; // erase the last character from console
            }
        }
        else if(ch == 0 || ch == 224) _getch(); // handle special keys 
        else if(isprint(static_cast<unsigned char>(ch))){
            password += static_cast<char>(ch); 
            cout<<"*"; // display asterisk for each character entered
        }
    }

    cout<<endl; // move to the next line after password input
    return password;
}

// Check User (already exist or not)'
bool userNameExists(string userName){
    string savedUsername, savedPassword; 

    ifstream file(FILENAME); 
    string header; 
    getline(file, header); // read and ignore the header line 
    while(file>>savedUsername>>savedPassword){
        if(userName == savedUsername){
            return true;
        }
    } 
    return false;
}
// forget password section

bool forgetPassword(){
    cout<<"Enter your username: "<<endl;
    string userName; 
    cin>>userName; 

    string savedUsername, savedPassword; 

    ifstream file(FILENAME); 
    string header; 
    getline(file, header); // read and ignore the header line 

    while(file>>savedUsername>>savedPassword){
        if(userName == savedUsername){
            cout<<"Your password is: "<<savedPassword<<endl;
            return true; 
        }
    }
    cout<<"Username not found. Please sign up first."<<endl;
    return false;
}

// Login section 
bool login(){
    string username, password;
    cout<<"Enter username: "<<endl;
    cin>>username;
    cout<<"Enter password: "<<endl;
    password = getPassword();

    ifstream file(FILENAME);

    if(!file){
        cout<<" No registered user found. Please sign up first."<<endl;
        return false;
    }

    string savedUsername, savedPassword; 

    string header;

    getline(file, header); // read and ignore the header line 
    while(file>>savedUsername>>savedPassword){
        if(username == savedUsername && password == savedPassword){
            return true;
        }
    }
    return false;
}
// signup section
void signUp(){
    string userName, password; 
    cout<<"Enter username: "<<endl;
    cin>>userName; 
    // what if the username already exists? 
    if(userNameExists(userName)){
        cout<<"Username already exists. Please choose a different username. "<<endl;
        return;
    }

    cout<<"Enter password: "<<endl;
    password = getPassword();

    // file already contains data 
    ifstream checkFile(FILENAME);
    bool isEmpty = checkFile.peek() == ifstream::traits_type::eof(); 
    checkFile.close(); // close the check file stream

    ofstream file(FILENAME, ios::app); 

    if(!file){
        cout<<"Error opening file"<<endl;
        return;
    }
    // heading 
    if(isEmpty){
        file<<"Username\tPassword\n"<<endl; // write heading if file is empty
    }

    file<<userName<<" "<<password<<endl; 

    if(!file){
        cout<<"Error saving account. Please try again."<<endl;
        return;
    }
    
    file.close();
    cout<<"Account created successfully"<<endl;
}



// MAIN function 
int main(){
   cout<<"Welcome to the login/Signup system"<<endl;
   int choice; 

   do{
    cout<<"1. Login"<<endl;
    cout<<"2. Signup"<<endl;
    cout<<"3. Forget Password"<<endl;
    cout<<"4. Exit"<<endl;
    cout<<"Enter your choice: ";
    cin>>choice;

    switch(choice){
        case 1: 
        // Login Section
        if(login()){
            cout<<"Login Successful"<<endl;
        }else{
            cout<<"Login Failed"<<endl;
        }
        break;

        case 2: 
        //signup Section
        signUp(); 
        break;

        case 3: 
        // Forget Password section
        forgetPassword(); 
        break;

        case 4: 
        cout<<"Exiting the system"<<endl;
        break;
    }
   }while(choice!=4);

   return 0; 

}


