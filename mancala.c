/*
  Mancala in C
  By Kyler Clark and Tyler Freberg
*/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

int board[14] = {4, 4, 4, 4, 4, 4, 0, 4, 4, 4, 4, 4, 4, 0};
int total1 = 0;
int total2 = 0;
bool running = true;
bool p1Skip = false;
bool p2Skip = false;

void printBoard() {
    if (total1 < 10) {
        printf("|0%d|", total1);
    }
    else {
        printf("|%d|", total1);
    }

    for (int i = 5; i >= 0; i--) {
        if (board[i] < 10) {
          printf("(0%d)", board[i]);
        }
        else {
          printf("(%d)", board[i]);
        }
    }

    printf("%c    ", '\n');

    for (int i = 7; i < 13; i++) {
        if (board[i] < 10) {
          printf("(0%d)", board[i]);
        }
        else {
          printf("(%d)", board[i]);
        }
    }

    if (total2 < 10) {
        printf("|0%d|\n", total2);
    }
    else {
        printf("|%d|\n", total2);
    }
}

void move(int player) {
    int choice = 0;
    printf("Please enter a number (1-6): ");
    scanf("%d", &choice);

    if (player == 1) {
        choice = 6-choice;
    }
    else {
        choice += 6;
    }
    int stones = board[choice];
    int stones2 = board[choice];
    board[choice] = 0;

    for(int i=choice+1; stones > 0; i++) {
        if (i > 13) {
            i = 0;
        }
        board[i]++;
        stones--;
    }

    total1 = board[6];
    total2 = board[13];

    if (player == 1 && 6-choice-stones2 == 0) {
        system("cls");
        printBoard();
        printf("%s\n", "Player 1's Turn Again");
        move(player);
        return;
    }
    if (player == 2 && choice+stones2 == 13) {
        system("cls");
        printBoard();
        printf("%s\n", "Player 2's Turn Again");
        move(player);
        return;
    }

}

void checkBoard() {
    int count1 = 0;
    int count2 = 0;
    running = true;
    p1Skip = false;
    p2Skip = false;

    for (int i = 0; i < 6;i++) {
        if (board[i] == 0) {
          count1++;
        }
    }
    for (int i = 7; i < 13; i++) {
        if (board[i] == 0) {
          count2++;
        }
    }

    if (count1 == 6 && count2 == 6) {
      running = false;
    }
    if (count1 == 6) {
      p1Skip = true;
    }
    if (count2 == 6) {
      p2Skip = true;
    }
}

int main() {
    system("cls");
    printBoard();
    while (running) {
        checkBoard();
        printf("%s\n", "Player 1's Turn");
        move(1);
        system("cls");
        printBoard();
        printf("%s\n", "Player 2's Turn");
        move(2);
        system("cls");
        printBoard();
    }

    if (total1 > total2) {
        printf("%s", "Player 1 Wins!");
    }
    else {
        printf("%s", "Player 2 Wins!");
    }
}
