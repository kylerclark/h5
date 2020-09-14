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

void mainmenu() {
    int num;

    system("clear");
    printf("Welcome to Mancala\nBy Kyler Clark and Tyler Freberg\n\n1) Rules\n2) Play\n3) Exit\n\nPlease enter an option (1-3): ");
    scanf("%d", &num);

    if (num == 1) {
        system("clear");

        printf("Player 1 is the top row.\nPlayer 2 is the bottom row.\n\nPlayer 1 goes first.\n\nA player enters a number 1-6. The stones in that pot (This is a pot (04)) will go around the board counter clockwise\nfor the number of stones, dropping a stone in each pot along the way. If the last stone ends in the storage (|04|),\nthat same player gets to go another turn. Otherwise, the next player goes. The game ends when both sides have 0\nstones in each pot. The player with the highest total number in their storage wins.\n\nP1    1   2   3   4   5   6\n|00|(04)(04)(04)(04)(04)(04)\n    (04)(04)(04)(04)(04)(04)|00|\n      1   2   3   4   5   6  P2\n\nPress Enter to continue to the main menu: ");
        getchar();
        while(getchar() != '\n') {
            getchar();
        }
        mainmenu();
        return;
    }
    else if (num == 2) {
    }
    else if (num == 3) {
        exit(0);
    }
    else {
        mainmenu();
    }
}

void printBoard() {
    printf(" P1   1   2   3   4   5   6\n");
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
    printf("      1   2   3   4   5   6  P2\n");
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
        system("clear");
        printBoard();
        printf("%s\n", "Player 1's Turn Again");
        checkBoard();
        if (!p1Skip) {
            move(player);
        }
        return;
    }
    if (player == 2 && choice+stones2 == 13) {
        system("clear");
        printBoard();
        printf("%s\n", "Player 2's Turn Again");
        checkBoard();
        if (!p2Skip) {
            move(player);
        }
        return;
    }
}



int main() {
    mainmenu();
    system("clear");
    printBoard();
    while (running) {
        if (!p1Skip) {
            printf("%s\n", "Player 1's Turn");
            move(1);
        }
        system("clear");
        printBoard();
        if (!p2Skip) {
            printf("%s\n", "Player 2's Turn");
            move(2);
        }
        checkBoard();
        system("clear");
        printBoard();
    }

    if (total1 > total2) {
        printf("%s", "Player 1 Wins!");
    }
    else {
        printf("%s", "Player 2 Wins!");
    }
}
