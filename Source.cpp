#include <conio.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <dos.h>
#include <time.h>
#include <cstdlib>
#include <locale.h>
#include <Windows.h>

using namespace std;

#define FIELD_WIDTH 6
#define FIELD_HEIGHT 5

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ENTER 13

int cursorX, cursorY;
bool quit = false;

char charGen();
void boardChecker();
char replacement;

//Board of the GAME
char board[5][6];
char boardCheckerR[5][6];

int main() {
	
	//Create board
	for (int x = 0; x < FIELD_HEIGHT; x++) {
		for (int y = 0; y < FIELD_WIDTH; y++) {
			char string = charGen();
			board[x][y] = string;
			boardCheckerR[x][y] = string;
		}
	}
	//endBoardCreate

	while (quit == false) {
		//Print Board
		for (int i = 0; i < FIELD_HEIGHT; i++) {
			for (int y = 0; y < FIELD_WIDTH; y++) {
				if (i == cursorX && y == cursorY) {
					printf("◎");
				}
				else
				{
					switch (board[i][y]) {
					case 'A': printf("■"); break;
					case 'B': printf("△"); break;
					case 'C': printf("○"); break;
					case 'D': printf("★"); break;
					case 'E': printf("●"); break;
					case 'F': printf("□"); break;
					case 'G': printf("☆"); break;
					case 'X': printf("・"); break;
					case 'N': printf("_"); break;
					}
				}
			}
			if (i == cursorX) {
				printf("←");
			}
			printf("\n");
		}

		for (int x = 0; x < cursorY; x++) {
			printf("  ");
		}
		printf("↑");

		switch (_getch()) {
				case 's': if (cursorX < FIELD_HEIGHT - 1) {
					swap(board[cursorX][cursorY], board[cursorX + 1][cursorY]);
					cursorX++;
				}
						  break;
				case 'a': if (cursorY >= 1) {
					swap(board[cursorX][cursorY], board[cursorX][cursorY - 1]);
					cursorY--;
				}
						  break;
				case 'w': if (cursorX >= 1) {
					swap(board[cursorX][cursorY], board[cursorX - 1][cursorY]);
					cursorX--;
				}
						  break;
				case 'd': if (cursorY < FIELD_WIDTH - 1) {
					swap(board[cursorX][cursorY], board[cursorX][cursorY + 1]);
					cursorY++;
				}
						  break;
				case 'q': quit = true; break;
				case 'r':	for (int x = 0; x < FIELD_HEIGHT; x++) {
								for (int y = 0; y < FIELD_WIDTH; y++) {
									char string = charGen();
									board[x][y] = string;
								}
							} 
						  break;
				case KEY_ENTER: for (int x = 0; x < FIELD_HEIGHT; x++) {
									for (int y = 0; y < FIELD_WIDTH; y++) {
										boardCheckerR[x][y] = board[x][y];
									}
								}		
								for (int i = 0; i < 12; i++) {
									boardChecker();
								}
								boardChecker();
								
								break;
			}
		
		system("CLS");
	}
}

char charGen() {
	switch ((rand() % 7 + 1)) {
	case 1:	return 'A';	break;
	case 2:	return 'B';	break;
	case 3:	return 'C';	break;
	case 4:	return 'D';	break;
	case 5:	return 'E';	break;
	case 6:	return 'F';	break;
	case 7:	return 'G';	break;
	case 8: return 'X'; break;
	}
}

void drop() {
	//drop
	bool clear = false;

	for (int i = 0; i < FIELD_HEIGHT; i++) {
		for (int y = 0; y < FIELD_WIDTH; y++) {
			if (board[i][y] == 'X') {
				clear = true;
				break;
			}
		}
	}

	while (clear) {
		//filling the missing tops
		for (int x = 0; x < FIELD_WIDTH; x++) {
			if (board[0][x] == 'X') {
				board[0][x] = charGen();
			}
		}

		for (int x = 0; x < FIELD_HEIGHT; x++) {
			for (int y = 0; y < FIELD_WIDTH; y++) {
				if (board[x][y] == 'X') {
					swap(board[x][y], board[x - 1][y]);
					system("CLS");
					for (int i = 0; i < FIELD_HEIGHT; i++) {
						for (int y = 0; y < FIELD_WIDTH; y++) {
							if (i == cursorX && y == cursorY) {
								printf("◎");
							}
							else
							{
								switch (board[i][y]) {
								case 'A': printf("■"); break;
								case 'B': printf("△"); break;
								case 'C': printf("○"); break;
								case 'D': printf("★"); break;
								case 'E': printf("●"); break;
								case 'F': printf("□"); break;
								case 'G': printf("☆"); break;
								case 'X': printf("・"); break;
								case 'N': printf("_"); break;
								}
							}
						}
						if (i == cursorX) {
							printf("←");
						}
						printf("\n");
					}
					Sleep(75);
					break;
				}
			}
		}

		clear = false;

		for (int i = 0; i < FIELD_HEIGHT; i++) {
			for (int y = 0; y < FIELD_WIDTH; y++) {
				if (board[i][y] == 'X') {
					clear = true;
					break;
				}
			}
		}
	}

	for (int i = 0; i < FIELD_HEIGHT; i++) {
		for (int y = 0; y < FIELD_WIDTH; y++) {
			boardCheckerR[i][y] = board[i][y];
		}
	}

}
void boardChecker() {
	//check for X Plots
	for (int x = 0; x < FIELD_HEIGHT; x++) {
		for (int y = 0; y < FIELD_WIDTH; y++) {
			//Check for Y
			//check for 6
			//check wether there is 6 in the a row in X Graph
			if (y == 0 && board[x][y] == board[x][y + 1] && board[x][y] == board[x][y + 2] && board[x][y] == board[x][y + 3] && board[x][y] == board[x][y + 4] && board[x][y] == board[x][y + 5]) {
				boardCheckerR[x][y] = 'X';
				boardCheckerR[x][y + 1] = 'X';
				boardCheckerR[x][y + 2] = 'X';
				boardCheckerR[x][y + 3] = 'X';
				boardCheckerR[x][y + 4] = 'X';
				boardCheckerR[x][y + 5] = 'X';
			}
			//check for 5
			//check wether there is 5 in the a row in X Graph
			if (y <=1 && board[x][y] == board[x][y + 1] && board[x][y] == board[x][y + 2] && board[x][y] == board[x][y + 3] && board[x][y] == board[x][y + 4]) {
				board[x][y] = 'X';
				board[x][y + 1] = 'X';
				board[x][y + 2] = 'X';
				board[x][y + 3] = 'X';
				board[x][y + 4] = 'X';
			}
			//check for 4
			//check wether there is 4 in the a row in X Graph
			if (y <= 2 && board[x][y] == board[x][y + 1] && board[x][y] == board[x][y + 2] && board[x][y] == board[x][y + 3]) {
				boardCheckerR[x][y] = 'X';
				boardCheckerR[x][y + 1] = 'X';
				boardCheckerR[x][y + 2] = 'X';
				boardCheckerR[x][y + 3] = 'X';
			}
			//check for 3
			//check wether there is 3 in the a row in X Graph
			if (y <= 3 && board[x][y] == board[x][y + 1] && board[x][y] == board[x][y + 2]) {
				boardCheckerR[x][y] = 'X';
				boardCheckerR[x][y + 1] = 'X';
				boardCheckerR[x][y + 2] = 'X';
			}
		}
	}

	//check for Y lots
	for (int x = 0; x < FIELD_HEIGHT; x++) {
		for (int y = 0; y < FIELD_WIDTH; y++) {
			//check for Y
			//check for 5
			if (board[x][y] == board[x + 1][y] && board[x][y] == board[x + 2][y] && board[x][y] == board[x + 3][y] && board[x][y] == board[x + 4][y]) {
				boardCheckerR[x][y] = 'X';
				boardCheckerR[x + 1][y] = 'X';
				boardCheckerR[x + 2][y] = 'X';
				boardCheckerR[x + 3][y] = 'X';
				boardCheckerR[x + 4][y] = 'X';
			}
			

			//check for 4
			if (board[x][y] == board[x + 1][y] && board[x][y] == board[x + 2][y] && board[x][y] == board[x + 3][y]) {
				boardCheckerR[x][y] = 'X';
				boardCheckerR[x + 1][y] = 'X';
				boardCheckerR[x + 2][y] = 'X';
				boardCheckerR[x + 3][y] = 'X';
			}
			//check for 3
			if (board[x][y] == board[x + 1][y] && board[x][y] == board[x + 2][y]) {
				boardCheckerR[x][y] = 'X';
				boardCheckerR[x + 1][y] = 'X';
				boardCheckerR[x + 2][y] = 'X';
			}
		}
	}

	//Change
	for (int x = 0; x < FIELD_HEIGHT; x++) {
		for (int y = 0; y < FIELD_WIDTH; y++) {
			
			if (boardCheckerR[x][y] != board[x][y]) {
				board[x][y] = 'X';
			}
		}
	}


	for (int i = 0; i < 12; i++) {
		drop();
	}

}
	



