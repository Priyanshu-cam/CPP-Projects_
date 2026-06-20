// Rock-paper scissor game
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
    cout << "==============================" << endl;
    cout << "Welcome to Rock-Paper-Scissors Game! " << endl;
    cout << "==============================" << endl;
    cout << "Let's play the Game!" << endl;

    int playerScore = 0;   // to store the player's score
    int computerScore = 0; // to store the computer's score

    int round = 0; // to keep track of the number of rounds played
    int maxRounds = 3;

    while (round < maxRounds)
    {
        // to show the number of rounds played 
        if (round == 0)
            cout << "Round 1" << endl;
        else if (round == 1)
            cout << "Round 2" << endl;
        else
            cout << "Round 3" << endl;


        int playerChoice; // to store the player's choice 
        cout << "Enter your choice: 1.Rock, 2.Paper, 3.Scissors: " << endl;
        cin >> playerChoice;

        int computerChoice = rand() % 3 + 1; // this will generate a random choice from the computer

        // showing the computer's choice
        cout << "Computer's choice: ";
        if (computerChoice == 1)
            cout << "Computer chose Rock" << endl;
        else if (computerChoice == 2)
            cout << "Computer chose Paper" << endl;
        else
            cout << "Computer chose Scissors" << endl;

        if (playerChoice == computerChoice)
        { // Tie condition
            cout << "It's a tie!" << endl;
        }
        else if (playerChoice == 1 && computerChoice == 3)
        { // Rock vs Scissor -> Rock wins
            cout << "You win!" << endl;
            playerScore++;
        }
        else if (playerChoice == 2 && computerChoice == 1)
        { // Paper vs Rock -> Paper wins
            cout << "You Win!" << endl;
            playerScore++;
        }
        else
        { // Scissors vs Paper -> Scissors wins
            cout << "Computer Wins!" << endl;
            computerScore++;
        }
        if (playerScore > computerScore)
        {
            cout << "Congratulations! You won the game!" << endl;
            cout << "You have defeated the computer with a score of " << playerScore - computerScore << endl;
        }
        else
        {
            cout << "Computer won the game!" << endl;
            cout << "Better luck next time! Computer has defeated you with a score of " << computerScore - playerScore << endl;
        }
        round++;
    }
    return 0;
}