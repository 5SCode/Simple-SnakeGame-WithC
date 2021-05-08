#include <iostream>
#include <stdlib.h> // or cstdlib
#include <time.h> // for time()
#include <conio.h> // for kbhit(), getch(), system("cls")
using namespace std;

// Prototype
void randomFood(int &foodX, int &foodY);
void rules_logic(int &foodX, int &foodY, int &tails, int *tailX, int *tailY, int &score, bool &gameOver);
void draw(int &foodX, int &foodY, int &tails, int *tailX, int *tailY, int &score);

// Global variabel
int width = 35, height = 15;
int x = width / 2, y = height /2;
enum snake{STOP = 1, UP, DOWN, LEFT, RIGHT};
snake snakeMove;

int main()
{
	int foodX, foodY; // cordinate snake food
	int score;
	int tails; // total tails
	int tailX[75], tailY[75]; // cordinate tail
	bool gameOver = false;
	randomFood(foodX, foodY);
	
	while(gameOver != true){
		system("cls");
		if(kbhit()){
			switch(getch()){
				case 'w': if(snakeMove != DOWN) snakeMove = UP; break;
				case 's': if(snakeMove != UP) snakeMove = DOWN; break;
				case 'a': if(snakeMove != RIGHT) snakeMove = LEFT; break;
				case 'd': if(snakeMove != LEFT) snakeMove = RIGHT; break;
				default: break;
			}
		}
		rules_logic(foodX, foodY, tails, tailX, tailY, score, gameOver);
		draw(foodX, foodY, tails, tailX, tailY, score);
	}
//	Sleep(10); // sleep 10ms/lopping
	if(gameOver) cout << "\nGame Over";
	
	return 0;
}

void randomFood(int &foodX, int &foodY){
	// generate random number (2 to (width-1)) | (2 to (height-1))
	srand(time(NULL));
	while(1){
		foodX = rand() % width;
		foodY = rand() % height;
		if(foodX >= 2 && foodY >= 2) break;
	}
}
void rules_logic(int &foodX, int &foodY, int &tails, int *tailX, int *tailY, int &score, bool &gameOver){
	// get cordinate tails
	tailX[0] = x; // tailX[0] && tailY[0] = Head of Snake (O)
	tailY[0] = y;
	
	for(int i=tails; i>0; i--){
		// tail[i] will take the cordinate of the previos tail[i-1]
		tailX[i] = tailX[i-1];
		tailY[i] = tailY[i-1];
	} 
	
	switch(snakeMove){
		case UP: y--; break;
		case DOWN: y++; break;
		case LEFT: x--; break;
		case RIGHT: x++; break;
		case STOP: gameOver = true ; break;
	}
	// snake through the arena
	if(x<=1) x = width; else if(x>=width) x = 1;
	if(y<=1) y = height; else if(y>=height) y = 1;
	
	// the snake eats
	if(x == foodX && y == foodY){
		score += 10;
		tails++;
		randomFood(foodX, foodY);
	}
	
	// the snake die (GameOver)
	for(int i=tails; i>0; i--){
		if(x == tailX[i] && y == tailY[i]) gameOver = true;
	}
}
void draw(int &foodX, int &foodY, int &tails, int *tailX, int *tailY, int &score){
	cout << "score: " << score << "\t";
	cout << "tails: " << tails << endl;
	for(int i=1; i<=height; i++){
		for(int j=1; j<=width; j++){
			// print arena
			if(i==1 || i==height || j==1 || j==width) cout << "#";
			// print snake
			else if(x==j && y==i) cout << "O";
			// print snake food
			else if(foodX == j && foodY == i) cout << "@";
			else{
				bool printSpace = true;
				for(int k=tails; k>0; k--){
					// print Tails
					if(tailX[k]==j && tailY[k]==i){
						printSpace = false;
						cout << "o";
					}
				}
				if(printSpace) cout << " ";
			}
		}
		cout << endl;
	}
}
