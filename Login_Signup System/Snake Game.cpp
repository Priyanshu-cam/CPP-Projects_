#include<iostream>
#include<conio.h>
#include<windows.h>
#include <cstdlib>
#include <ctime>

using namespace std; 
bool gameOver; 
const int width = 20; 
const int height = 20; 
int x, y, fruitX, fruitY, score; 
int tailX[100], tailY[100]; // arrays to store the coordinates of the snake's tail
int nTail; // length of the snake's tail
enum eDirection {Stop = 0, LEFT, RIGHT, UP, DOWN}; // used to define the direction of the snake
eDirection dir;  // used for the direction of the snake

void SpawnFruit() {
    bool occupied;

    do {
        occupied = false;
        fruitX = rand() % width;
        fruitY = rand() % height;

        // Check the snake's head
        if (fruitX == x && fruitY == y) {
            occupied = true;
        }

        // Check every tail segment
        for (int i = 0; i < nTail; i++) {
            if (fruitX == tailX[i] &&
                fruitY == tailY[i]) {
                occupied = true;
                break;
            }
        }

    } while (occupied);
}
void Setup(){
    nTail = 0; 
    gameOver = false;
    dir = Stop; 
    x = width / 2; 
    y = height / 2; 
    SpawnFruit(); // spawn the first fruit
    
    score = 0; 
}
void Draw(){
    system("cls"); //system("clear"); for Linux
    for(int i = 0; i < width; i++){
        cout<<"#"; 
    }
    cout<<endl;

    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            if(j == 0) cout<<"#"; 
            if(i == y && j == x) cout<<"0"; 
            else if(i == fruitY && j == fruitX) cout<<"F"; 
            else{
                 bool print = false;
                for(int k = 0; k < nTail; k++){
                    if(tailX[k] == j && tailY[k] == i){
                        cout<<"o"; 
                        print = true;
                        break;
                    }
 
                }
                if(!print)
                cout<<" ";
            }
            if(j == width - 1) cout<<"#"; 
        }
        cout<<endl;
    }

    for(int i = 0; i < width; i++){
        cout<<"#"; 
    }
    cout<<endl;

    cout<<"Score: "<<score<<endl;
}

void Input(){
    if(_kbhit()){
        switch(_getch()){
            case 'a': // move left 
            if(dir != RIGHT)
                dir = LEFT; 
                break; 
            case 'd':
                if(dir != LEFT)
                    dir = RIGHT;  // move right
                break; 
            case 'w':
                if(dir != DOWN)
                dir = UP;  // move up 
                break; 
            case 's':
                if(dir != UP)
                dir = DOWN; // move down
                break; 
            case 'x':
                gameOver = true; // exit the game 
                break; 
        }
    }
}
void Logic(){
    int prevX = tailX[0]; 
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x; 
    tailY[0] = y;
    for(int i = 1; i < nTail; i++){
        prev2X = tailX[i]; 
        prev2Y = tailY[i]; 
        tailX[i] = prevX; 
        tailY[i] = prevY; 
        prevX = prev2X; 
        prevY = prev2Y; 
    }
    switch(dir){
        case LEFT:
            x--; 
            break; 
        case RIGHT: 
            x++; 
            break; 
        case UP: 
            y--; 
            break;
        case DOWN: 
            y++; 
            break;
        default:
            break;
    }

    // if the snake hits the wall, terminate the game 
    if(x < 0 || x >= width || y < 0 || y >= height){
        gameOver = true;
        return;
    }
    for(int i = 0; i < nTail; i++){
        if(tailX[i] == x && tailY[i] == y){
            gameOver = true;
        } 
    }

    if(x == fruitX && y == fruitY){
        score += 10; 
        if(nTail < 100)
        nTail++; // increase the length of the snake's tail by 1
        SpawnFruit(); // spawn a new fruit
    }

}

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    char choice;

    do {
        Setup();

        while (!gameOver) {
            Draw();
            Input();
            Logic();
            Sleep(100);
        }

        cout << "Game Over! Your Score: " << score << endl;
        cout << "Do you want to play again? (y/n): ";
        cin >> choice;

    } while (choice == 'y' || choice == 'Y');

    return 0;
}