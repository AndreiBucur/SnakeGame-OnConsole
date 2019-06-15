#include <iostream>
#include <conio.h>
#include <ctime>
#include <windows.h>
#include <fstream>

using namespace std;

bool gameOver;
int fruitX, fruitY, x, y, score;
int width, height;
int tailX[100], tailY[100];
int nTail;
enum Dir { UP, DOWN, LEFT, RIGHT, STOP = 0 };
char Speed;
int SPEED;
Dir dir;

void Menu() 
{
	SetConsoleTitle(TEXT("Snake / Controls"));
	system("cls");
	cout << "\nControls: \n";
	cout << "ESC - finish the game\n";
	cout << " W  - move UP\n";
	cout << " S  - move DOWN\n";
	cout << " A  - move LEFT\n";
	cout << " D  - move RIGHT\n\n";
	system("pause");
}

void Setup()
{
	char mapSize;
	char speed;

	system("cls");

	cout << "\n\tNotes that the larger the map, the slower the snake speed\n";
	cout << "\n\tWhat map size do you want?\n\t  > Big [b]\n\t  > Medium [m]\n\t  > Small [s]\n\t    ";
	cin >> mapSize;
	switch (mapSize)
	{
	case 'b':
	case 'B':
		SetConsoleTitle(TEXT("Snake / Big"));
		system("MODE 80, 35");
		width = 60;
		height = 30;
		break;
	case 'm':
	case 'M':
		SetConsoleTitle(TEXT("Snake / Medium"));
		system("MODE 70, 30");
		width = 50;
		height = 25;
		break;
	case 's':
	case 'S':
		SetConsoleTitle(TEXT("Snake / Small"));
		system("MODE 60, 25");
		width = 40;
		height = 20;
		break;
	default:
		cout << "Please enter valid options!\n";
		system("pause");
		Setup();
		break;
	}

speeD:
	system("cls");

	cout << "\n\tDo you want do adjust the speed? [y/n]\n\t";
	cin >> speed;
	switch (speed)
	{
	case 'y':
	case 'Y':
	speeD2:
		cout << "\n\tNotes that the bigger the number,\n\tthe slower the snake speed\n";
		cout << "\n\tPlease enter a number from 1 to 5\n\t";
		cin >> Speed;
		switch (Speed)
		{
		case '1':	SPEED = 1; break;
		case '2':	SPEED = 2; break;
		case '3':	SPEED = 3; break;
		case '4':	SPEED = 4; break;
		case '5':	SPEED = 5; break;
		default:
			system("cls");
			cout << "Please enter valid options!\n";
			system("pause");
			goto speeD2;
			break;
		}
		break;
	case 'n':
	case 'N':
		break;
	default:
		cout << "Please enter valid options!\n";
		system("pause");
		goto speeD;
		break;
	}

	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	srand(time(0));
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
}

void Draw() 
{
	for(int i = 0; i<=SPEED; i++){
		Sleep(10);
	}

	system("cls");
	for (int i = 0; i < width + 2; i++) {
		cout << '-';
	}
	cout << endl;

	for (int i = 0; i < height + 2; i++) {
		for (int j = 0; j < width + 2; j++) {
			if (j == 0) {
				cout << '|';
			}
			if (i == y && j == x) {
				cout << "O";
			}
			else if (i == fruitY && j == fruitX) {
				cout << "$";
			}
			else {
				bool print = false;
				for (int p = 0; p < nTail; p++) {

					if (tailX[p] == j && tailY[p] == i) {
						cout << "o";
						print = true;
					}
				}
				if (!print) {
					cout << " ";
				}
			}
				
			if (j == width - 1) {
				cout << '|';
			}
			if (j == width + 1 && i == 1) {
				cout << "Score: " << score;
			}
		}
		cout << endl;
	}

	for (int i = 0; i < width + 2; i++) {
		cout << '-';
	}
	cout << endl;
}

void Input() 
{
	if (_kbhit()) {
		switch(_getch()) {
		case 'a':
		case 'A':
		case 75:
			dir = LEFT; 	break;

		case 'd':
		case 'D':
		case 77:
			dir = RIGHT; 	break;

		case 'w':
		case 'W':
		case 72:
			dir = UP; 		break;

		case 's':
		case 'S':
		case 80:
			dir = DOWN; 	break;

		case 27:
			gameOver = true;break;
		}
	}
}

void Logic() {
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;

	for (int i = 1; i < nTail; i++) {
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}

	switch (dir)
	{
	case UP:
		Sleep(10);
		y--;
		break;
	case DOWN:
		Sleep(10);
		y++;
		break;
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;

	default:
		break;
	}
	if (x > width || x < 0 || y > height || y < 0) {
		gameOver = true;
	}

	for (int i = 0; i < nTail; i++) {
		if (tailX[i] == x && tailY[i] == y) {
			gameOver = true;
		}
	}

	if (x == fruitX && y == fruitY) {
		score += 1;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++;
	}
}

int main() 
{
	char rasp , reload;
	bool save1 = false;
	bool createFile;
	char menu;
	string scoreID;

	SetConsoleTitle(TEXT("Snake / Menu"));
	system("MODE 70, 10");
Menu:
	cout << "\n\tWhat you want to do?\n\n";
	cout << "\tc (if you want to see the controls)\n";
	cout << "\tp (if you want to play the game)\n\n\t";
	cin >> menu;
	switch (menu)
	{
	case 'c':
	case 'C':
		Menu(); break;
	case 'P':
	case 'p':
		break;
	default:
		cout << "\nPlease enter a valid option!\n";
		system("pause");
		goto Menu;
		break;
	}
	Setup();
	while (!gameOver) {
		Draw();
		Input();
		Logic();
	}
	system("pause");
	system("cls");
	system("MODE 40, 6");
	cout << "\n\tYou LOSE!\n";
	system("pause");
	system("cls");
saveScore1:
	cout << "\nDo you want to save this score? score:" << score << "\t [y/n]\n\t";
	cin >> rasp;
	switch (rasp)
	{
	case 'y':
	case 'Y':
		save1 = true;
		break;
	case 'n':
	case 'N':
		save1 = false;
		break;
	default:
		cout << "\nPlease enter a valid option!\n";
		system("pause");
		goto saveScore1;
		break;
	}
	if (save1 == true) {
		system("cls");
			cout << "   What is your score id\n   ( only 3 characters! )\n   ( example: ABI, SUR, YES ... )\n\n\t";
			cin >> scoreID;
			scoreID.resize(3);
			ofstream ScoreOut("Score-Snake.txt", ios::out | ios::app);
			ScoreOut << "\n" << scoreID << "  score: " << score;
			ScoreOut.close();
	}
	return 0;
}