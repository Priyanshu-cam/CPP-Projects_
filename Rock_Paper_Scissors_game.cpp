#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

class RockPaperScissorsGame
{
private:
    int playerScore = 0;
    int computerScore = 0;
    int maxRounds = 3;
    int round = 0;

public:
    int getPlayerChoice()
    {
        int choice;
        while (true) // Keep asking until valid input
        {
            cout << "Enter your choice: 1.Rock, 2.Paper, 3.Scissors: ";
            cin >> choice;

            if (cin.fail()) // Non-integer input
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input! Please enter a number.\n";
                continue; // Ask again
            }

            if (choice < 1 || choice > 3) // Out-of-range input
            {
                cout << "Invalid choice! Please choose 1, 2, or 3.\n";
                continue; // Ask again
            }

            break; // Valid input, exit loop
        }

        cout << "You chose ";
        if (choice == 1)      cout << "Rock\n";
        else if (choice == 2) cout << "Paper\n";
        else                  cout << "Scissors\n";

        return choice;
    }

    int getComputerChoice()
    {
        int computerChoice = rand() % 3 + 1;

        cout << "Computer chose ";
        if (computerChoice == 1)      cout << "Rock\n";
        else if (computerChoice == 2) cout << "Paper\n";
        else                          cout << "Scissors\n";

        return computerChoice;
    }

    void playGame()
    {
        round = 0;
        playerScore = 0;
        computerScore = 0;

        while (round < maxRounds)
        {
            cout << "\n--- Round " << round + 1 << " ---\n";

            int playerChoice   = getPlayerChoice();
            int computerChoice = getComputerChoice();

            if (playerChoice == computerChoice)
            {
                cout << "It's a tie!\n";
            }
            else if ((playerChoice == 1 && computerChoice == 3) ||
                     (playerChoice == 2 && computerChoice == 1) ||
                     (playerChoice == 3 && computerChoice == 2))
            {
                cout << "You win this round!\n";
                playerScore++;
            }
            else
            {
                cout << "Computer wins this round!\n";
                computerScore++;
            }

            cout << "Score => Player: " << playerScore
                 << " | Computer: " << computerScore << "\n";
            round++;
        }
    }

    void displayScore()
    {
        cout << "\n==============================\n";
        cout << "       FINAL RESULTS\n";
        cout << "==============================\n";
        cout << "Player: " << playerScore << " | Computer: " << computerScore << "\n\n";

        if (playerScore > computerScore)
            cout << "Congratulations! You won the game!\n";
        else if (computerScore > playerScore)
            cout << "Computer won the game! Better luck next time!\n";
        else
            cout << "The match ended in a tie!\n";
    }
};

int main()
{
    srand(time(0));
    RockPaperScissorsGame game;

    cout << "==============================\n";
    cout << "  Welcome to Rock-Paper-Scissors!\n";
    cout << "==============================\n";
    cout << "Rules: Rock beats Scissors | Scissors beats Paper | Paper beats Rock\n";
    cout << "Best of 3 rounds. Good luck!\n\n";

    game.playGame();
    game.displayScore();

    return 0;
}