// Rock-paper scissor game 
#include<iostream>
#include<cstdlib>
#include<ctime>

using namespace std; 

int main(){
    cout<<"==============================" <<endl;
    cout<<"Welcome to Rock-Paper-Scissors Game! "<<endl;
    cout<<"==============================" <<endl;
    cout<<"Let's play the Game!" <<endl;

    int playerScore = 0; 
    int computerScore = 0; 

    int playerChoice; 
    cout<<"Enter your choice: 1.Rock, 2.Paper, 3.Scissors: "<<endl;
    cin>>playerChoice; 

    int computerChoice = rand() % 3 + 1; // this will generate a random choice from the computer 

    if(computerChoice == 1)cout<<"Computer chose Rock"<<endl;
    else if(computerChoice == 2) cout<<"Computer chose Paper"<<endl;
    else cout<<"Computer chose Scissors"<<endl;

    if(playerChoice == computerChoice){ //Tie condition
        cout<<"It's a tie!"<<endl;
    }
    else if(playerChoice == 1 && computerChoice == 3){ // Rock vs Scissor -> Rock wins
        cout<<"You win!"<<endl;
        playerScore++;
    }
    else if(playerChoice == 2 && computerChoice == 1){ // Paper vs Rock -> Paper wins
        cout<<"You Win!"<<endl;
        playerScore++;
    }else{ // Scissors vs Paper -> Scissors wins
        cout<<"Computer Wins!"<<endl;
        computerScore++;
    }
    if(playerScore > computerScore){
        cout<<"Congratulations! You won the game!"<<endl;
        cout<<"You have defeated the computer with a score of "<<playerScore - computerScore<<endl;
    }
    else{
        cout<<"Computer won the game!"<<endl;
        cout<<"Better luck next time! Computer has defeated you with a score of "<<computerScore - playerScore<<endl;
    }

    return 0; 
}