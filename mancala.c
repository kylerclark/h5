/*
  Mancala in C
  By Kyler Clark and Tyler Freberg
*/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

int board1[6] = {4, 4, 4, 4, 4, 4};
int board2[6] = {4, 4, 4, 4, 4, 4};
int total1 = 0;
int total2 = 0;
bool running = true;
bool p1Skip = false;
bool p2Skip = false;

void printBoard() {
    if (total1 < 9) {
      printf("|0%d|", total1);
    }
    else {
      printf("|%d|", total1);
    }
    for (int i = 0; i < 6; i++) {
      if (board1[i] < 9) {
        printf("(0%d)", board1[i]);
      }
      else {
        printf("(%d)", board1[i]);
      }
    }

    printf("%c    ", '\n');

    for (int i = 0; i < 6; i++) {
      if (board2[i] < 9) {
        printf("(0%d)", board2[i]);
      }
      else {
        printf("(%d)", board2[i]);
      }
    }
    if (total2 < 9) {
      printf("|0%d|\n", total2);
    }
    else {
      printf("|%d|\n", total2);
    }
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
        if (numStones == 0) {
          move(1);
        }
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
        else if (extra <= -1) {
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
          if (extra <= 5) {
            for(int i = 0; i <= extra; i++) {
              board2[i]++;
            }
          }
          else if (extra > 5) {
            total2++;
            extra--;
            for(int i = 0; i < extra; i++) {
              board2[i]++;
            }
            if (extra > 11) {
              total2++;
              extra--;
              for(int i = 6; i >= 6-extra; i--) {
                board1[i]++;
              }
            }
            else {
              for (int i = 6; i >= 11-extra; i--) {
                board1[i]++;
              }
            }
          }
        }
      }
    }

    //player 2
    if (player == 2) {
      if (p2Skip) {
        printf("%s\n", "P2 Skipped");
      }
      else {
        int choice = 0;
        printf("%s", "Player 2's turn. Enter choice(1-6): ");
        scanf("%d", &choice);
        choice--;
        int numStones = board2[choice];
        if (numStones == 0) {
          move(2);
        }
        board2[choice] = 0;
        int extra = numStones-(6-choice)+1;
        if (extra == 1) {
          total2++;
          for(int i = choice+1; i < choice+numStones+1; i++) {
            board2[i]++;
          }
          printBoard();
          move(player);
        }
        else if (extra < 1) {
          for(int i = choice+1; i < choice+numStones+1; i++) {
            board2[i]++;
          }
        }
        else if (extra > 1) {
          total2++;
          extra--;
          for(int i = choice+1; i < 6; i++) {
            board2[i]++;
          }
          if (extra < 6) {
            for(int i = 6; i >= 6-extra; i--) {
              board1[i]++;
            }
          }
          else if (extra > 6) {
            total1++;
            extra--;
            for(int i = 6; i > 6-extra; i--) {
              board1[i]++;
            }
            if (extra > 12) {
              total2++;
              extra--;
              for(int i = 6; i >= 6-extra; i--) {
                board1[i]++;
              }
            }
          }
        }
      }
    }
}

void checkBoard() {
    int count1 = 0;
    int count2 = 0;
    running = true;
    p1Skip = false;
    p2Skip = false;
      for(int i = 0; i < 6;i++) {
        if (board1[i] == 0) {
          count1++;
        }
        else if (board2[i] == 0) {
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
    printBoard();
    while (running) {
      checkBoard();
      move(1);
      system("cls");
      printBoard();
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
