// Simple Game using C++ 
#include<iostream>
#include <cstdlib>
#include <ctime> 

using namespace std; 

int main(){

  srand(time(0)); // seeding the random number generator with the current time 
  // Srand() is used to seed the random number where time is the base condition for that --> means every time program is run, it will generate a random number based on the current time 

  int number = rand() % 100 + 1; // generate a random number between 1 to 100 

  int guess; // this will store the user input 
  int attempts = 0;  // number of attempts made by the user 
  int maxAttempts = 5; // maximum number of attempts allowed 

  cout<<"<====================================================>"<<endl; 
  cout<<"Welcome to the Number guessing game!"<<endl; 
  cout<<"<====================================================>"<<endl; 
  cout<<"The number has been selected between 1 and 100. Can you Guess it? "<<endl;

  while(attempts < maxAttempts){
    cout<<"Enter your number: "; 
    cin>>guess; 
    attempts++; 

    if(guess == number){
      cout<<"Congratulations! You guessed the number in "<<attempts<<" attemps!"<<endl;
      cout<<"<====================================================>"<<endl; 
      return 0;
    }else if(guess < number){
      cout<<"Too Low! try again. "<<endl;
      cout<<"<====================================================>"<<endl; 
      cout<<"Attempts left: "<<maxAttempts - attempts<<endl;
    }else{
      cout<<"Too High! try again."<<endl;
      cout<<"<====================================================>"<<endl; 
      cout<<"Attempts left: "<<maxAttempts - attempts<<endl;
    }
    }
    if(attempts == maxAttempts){

      cout<<"Sorry! You've used all your attempts. The number was: "<<number<<endl;
      cout<<"<====================================================>"<<endl; 
    }
    return 0; 
  }
