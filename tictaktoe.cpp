//Aamina Bokhari
//tik tak toe game AI
#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include<iomanip>
#include<string>

using namespace std;

char board[3][3]; // i am creating a 3x3 matrix

// i am checking if any row has a winning combo in this function....
bool rowcheck() {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ')
            return true;//this function checks if all three cells in that row are equal and not empty
    }
    return false;
}

//same checking for columns here...
bool columncheck() {
    for (int i = 0; i < 3; i++) {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ')
            return true;
    }
    return false;
}

// same check for diagonal....
bool diagonalcheck() {
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ')//dig 1
        return true;
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ')//dig 2
        return true;
    return false;
}

// this function checks if winner is found
bool checkwinner() {
    return rowcheck() || columncheck() || diagonalcheck();
}

// vheck if game is a draw
bool checkdraw() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == ' ')
                return false;
    return true;
}

// handling user turn here... user is X and Comp is O
void usermove() {
    cout << endl;
    cout << "User Turn.........>" << endl;
    int x, y;
    cout << "Enter your move (row and then column): ";
    cin >> x >> y;
    x--; y--;//because array start from 0
    if (board[x][y] != ' ') {
        cout << "wrong move, try again." << endl;//IF the space is already occupied
        usermove();
    }
    else {
        board[x][y] = 'X';
    }
}

// Minimax function algo here...

int minimax(char board[3][3], int depth, bool isMaximizing) {
    // If the game has a winner, return -1 for minimizing player and 1 for maximizing player
    if (checkwinner()) {
        return isMaximizing ? -1 : 1;
    }
    // If the game is a draw, return 0
    if (checkdraw()) {
        return 0;
    }

    // Maximizing player,here i am trying to find the maximum score possible
    if (isMaximizing) {
        int bestScore = -9999993; // Initialize to a very low value
        // Iteate...
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                // Check if acell is empty
                if (board[i][j] == ' ') {
                    // Make the move
                    board[i][j] = 'O';
                    // Call minimax recursively, increasing depth and switching to min player
                    int score = minimax(board, depth + 1, false);
                    // Undo the move
                    board[i][j] = ' ';
                    // replace the best score if current score is higher
                    bestScore = max(score, bestScore);
                }
            }
        }
      
        return bestScore;
    }
    //  i am trying to find the minimum score possible
    else {
        int bestScore = 9999; // Initialize to a very high value
        // Iterate......
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                // Cif cell is empty
                if (board[i][j] == ' ') {
                    // do move
                    board[i][j] = 'X';
                    // Call minimax recursively, increasing depth and switching to maximizing player
                    int score = minimax(board, depth + 1, true);
                    // Undo the move
                    board[i][j] = ' ';
                    // Update the best score if current score is lower
                    bestScore = min(score, bestScore);
                }
            }
        }
       
        return bestScore;
    }
}


// do  computer's move using Minimax
void computermove() {
    cout << endl;
    cout << " Computer Turn.........> " << endl<<endl;
    int bestScore = -109999;
    int move[2] = { -1, -1 };
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = 'O';
                int score = minimax(board, 0, false);
                board[i][j] = ' ';
                if (score > bestScore) {
                    bestScore = score;
                    move[0] = i;
                    move[1] = j;
                }
            }
        }
    }
    board[move[0]][move[1]] = 'O';
}

// Function to display the tic-tac-toe board
void display() {
    cout << "  1 2 3 \n";
    for (int i = 0; i < 3; i++) {
        cout << i + 1 << " ";
        for (int j = 0; j < 3; j++) {
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }
}

int main() {
    cout << "<<<<<<< TIC TAC TOE >>>>>>> " << endl<<endl;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = ' ';
    display();
    while (true) {
        usermove();
        display();
        if (checkwinner()) {
            cout << "Congrats!!!! You win!\n";
            break;
        }
        if (checkdraw()) {
            cout << "It's a draw.\n";
            break;
        }
        computermove();
        display();
        if (checkwinner()) {
            cout << "Oh no,Computer wins!\n";
            break;
        }
        if (checkdraw()) {
            cout << "It's a draw.\n";
            break;
        }
    }
    return 0;
}
