#include <iostream>
#include <cctype>
#include <ctime>
#include <cstdlib>
#include <map>
#include <bits/stdc++.h>
#include <limits>

static char array[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
static int option;
static char playerchoice;
static int a;
static int b;
static char computerchoice;

// smart computer logic using minimax algorithm

int max(int a, int b) {
    if (a > b) return a;
    else return b;
}

int min(int a, int b) {
    if (a < b) return a;
    else return b;
}

void writer() {
    char* pc = &array[0][0];
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (j != 2) std::cout << *pc << " | ";
            else if (j == 2) std::cout << *pc;
            pc++;
        }
        if (i != 2) std::cout << "\n----------\n";
    }
}

// answer = 0 nobody wins
// answer = 1 user wins
// answer = 2 computer wins
int checker(char c) {
    // row checker
    for (int i = 0; i < 3; i++) {
        if (array[i][0] == c && array[i][1] == c && array[i][2] == c) {
            return (c == playerchoice) ? 1 : 2;
        }
    }

    // column checker
    for (int j = 0; j < 3; j++) {
        if (array[0][j] == c && array[1][j] == c && array[2][j] == c) {
            return (c == playerchoice) ? 1 : 2;
        }
    }

    // diagonal checker
    if (array[0][0] == c && array[1][1] == c && array[2][2] == c) {
        return (c == playerchoice) ? 1 : 2;
    }

    // opposite diagonal checker
    if (array[0][2] == c && array[1][1] == c && array[2][0] == c) {
        return (c == playerchoice) ? 1 : 2;
    }

    return 0;  // No winner yet
}

void userinput() {
    std::cout << "\nEnter row-column (1-3): ";
    std::cin >> a >> b;
    a--;
    b--;
    while (a < 0 || a >= 3 || b < 0 || b >= 3 || isalpha(array[a][b])) {
        std::cout << "\nInvalid move. Try again: ";
        std::cin >> a >> b;
        a--;
        b--;
    }
    array[a][b] = playerchoice;
}

bool isBoardFull() {
    int count = 0;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (isalpha(array[i][j])) count++;
        }
    }
    return (count == 9);
}

int minimax(int depth, bool isMaximizing) {
    // Check for winning condition
    int result1 = checker(playerchoice);  // Player win
    int result2 = checker(computerchoice); // Computer win

    if (result1 == 1) return -10;  // Player wins, return negative score
    if (result2 == 2) return 10;   // Computer wins, return positive score
    if (isBoardFull()) return 0;   // Draw if the board is full

    if (isMaximizing) {
        int bestScore = std::numeric_limits<int>::min();
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (array[i][j] == ' ') {
                    array[i][j] = computerchoice;  // Try computer's move
                    int score = minimax(depth + 1, false);  // Minimize for the player
                    array[i][j] = ' ';  // Undo the move
                    bestScore = max(bestScore, score);
                }
            }
        }
        return bestScore;
    } else {
        int bestScore = std::numeric_limits<int>::max();
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (array[i][j] == ' ') {
                    array[i][j] = playerchoice;  // Try player's move
                    int score = minimax(depth + 1, true);  // Maximize for the computer
                    array[i][j] = ' ';  // Undo the move
                    bestScore = min(bestScore, score);
                }
            }
        }
        return bestScore;
    }
}

void computerplay() {
    int bestScore = std::numeric_limits<int>::min();
    int bestMove[2] = {-1, -1};

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (array[i][j] == ' ') {
                array[i][j] = computerchoice;  // Try computer's move
                int score = minimax(0, false);  // Find best score using minimax
                array[i][j] = ' ';  // Undo the move

                if (score > bestScore) {
                    bestScore = score;
                    bestMove[0] = i;
                    bestMove[1] = j;
                }
            }
        }
    }
    array[bestMove[0]][bestMove[1]] = computerchoice;  // Make the best move
}

int main() {
    std::cout << "TIC TAC TOE\n";
    std::cout << "Do you want to start first (1) or the computer (0)? ";
    std::cin >> option;
    std::cout << "X or O? ";
    std::cin >> playerchoice;
    computerchoice = (playerchoice == 'X') ? 'O' : 'X';

    int result = 0;
    while (result == 0 && !isBoardFull()) {
        if (option == 1) {
            userinput();
            result = checker(playerchoice);
            writer();
            if (result != 0) break;

            computerplay();
            result = checker(computerchoice);
            writer();
        } else if (option == 0) {
            computerplay();
            result = checker(computerchoice);
            writer();
            if (result != 0) break;

            userinput();
            result = checker(playerchoice);
            writer();
        }
    }

    if (result == 1) std::cout << "\nUser Won!";
    else if (result == 2) std::cout << "\nUser Lost!";
    else std::cout << "\nDraw!";
}
