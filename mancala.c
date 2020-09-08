/*
  Mancala in C
  By Kyler Clark and Tyler Freberg
*/

#include <stdio.h>
#include <string.h>

void printBoard(int board[2][6], int total1, int total2) {
    printf("|%d|", total1);
    for (int i = 0; i < 2; i++) {
      for (int j = 0; j < 6; j++) {
          printf("(%d)", board[i][j]);
      }
      if (i == 1) {
          printf("|%d|\n   ", total2);
      }
      else {
        printf("%s", "\n   ");
      }
    }
}

void move(int player, int choice, int board[2][6]) {
    choice--;
    player--;
    int numStones = board[player][choice];
    board[player][choice] = 0;
    //player 1
    if (player == 0) {
      if (choice-numStones == -1) {
        // extra turn
        total1++;
      }
      else if (choice-numStones < -1) {
        total1++;
      }
    }

    //player 2
    else if (player == 1) {

    }
    for (int i = choice+numStones; i > choice; i--) {
      if (board[player][i] == )
      board[player][i]++;
    }
}

int main() {

    int board[2][6] = {
      {4, 4, 4, 4, 4, 4},
      {4, 4, 4, 4, 4, 4}
      };

    int total1 = 0;
    int total2 = 0;

    printBoard(board, total1, total2);

}
