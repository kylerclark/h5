/*
  Mancala in C
  By Kyler Clark and Tyler Freberg
*/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int board1[6] = {4, 4, 4, 4, 4, 4};
int board2[6] = {4, 4, 4, 4, 4, 4};
int total1 = 0;
int total2 = 0;
bool running = true;
bool p1Skip = false;
bool p2Skip = false;

void printBoard() {
    printf("|%d|", total1);
    for (int i = 0; i < 6; i++) {
      printf("(%d)", board1[i]);
    }

    printf("%c   ", '\n');

    for (int i = 0; i < 6; i++) {
      printf("(%d)", board2[i]);
    }
    printf("|%d|\n", total2);
}

void move(int player) {

    //player 1
    if (player == 1) {
      if (p1Skip) {
        printf("%s\n", "P1 Skipped");
      }
      else {
        int choice = 0;
        printf("%s", "Player 1's turn. Enter choice(1-6): ");
        scanf("%d", &choice);
        choice--;
        int numStones = board1[choice];
        board1[choice] = 0;
        int extra = numStones-choice;
        extra--;
        if (extra == 0) {
          total1++;
          for(int i = choice-1; i >= choice-numStones+1; i--) {
            board1[i]++;
          }
          printBoard();
          move(player);
        }
        else if (extra == -1) {
          total1++;
          for(int i = choice; i > choice-numStones+1; i--) {
            board1[i]++;
          }
        }
        else if (extra < -1) {
          for(int i = choice-1; i >= choice-numStones; i--) {
            board1[i]++;
          }
        }
        else if (extra > -1) {
          total1++;
          extra--;
          for(int i = choice-1; i >= 0; i--) {
            board1[i]++;
          }
          if (extra < 5) {
            for(int i = 0; i <= extra; i++) {
              board2[i]++;
            }
          }
          else if (extra > 5) {
            total2++;
            extra--;
          }
        }
      }
    }

    //player 2
    if (player == 2) {
      if (p1Skip) {
        printf("%s\n", "P2 Skipped");
      }
      else {
        int choice = 0;
        printf("%s", "Player 2's turn. Enter choice(1-6): ");
        scanf("%d", &choice);
        choice--;
        int numStones = board2[choice];
        board2[choice] = 0;
        int extra = numStones-choice;
        if (extra == 0) {
          total2++;
          for(int i = choice; i > choice-numStones+1; i--) {
            board2[i]++;
          }
          move(player);
        }
        else if (extra < 0) {
          for(int i = choice; i > choice-numStones; i--) {
            board2[i]++;
          }
        }
        else if (extra > 0) {
          total2++;
          extra--;
          if (extra < 6) {
            for(int i = 0; i < extra; i++) {
              board1[i]++;
            }
          }
          else if (extra > 6) {
            total1++;
            extra--;
          }
        }
      }
    }
}

void checkBoard() {
    running = false;
    p1Skip = true;
    p2Skip = true;
      for(int i = 0; i < 6;i++) {
        if (board1[i] != 0) {
          running = true;
          p1Skip = false;
          break;
        }
        else if (board2[i] != 0) {
          running = true;
          p2Skip = false;
          break;
        }
      }
}


int main() {
    printBoard();
    while (running) {
      checkBoard();
      move(1);
      printBoard();
      move(2);
      printBoard();
    }

}
