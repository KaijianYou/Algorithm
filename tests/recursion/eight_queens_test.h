#ifndef ALGORITHM_EIGHT_QUEENS_TEST_H
#define ALGORITHM_EIGHT_QUEENS_TEST_H

#include <iostream>

#include "../../algorithm/recursion/eight_queens.h"

namespace myalgorithm {
    using std::cin;
    using std::cout;
    using std::endl;

    void testEightQueens()
    {
        vector<int> queenVec(8);
        ChessBoard board;

        cout << "Enter row for queen in column 1: ";
        int row = 0;
        cin >> row;

        cout << endl;

        if (queens(queenVec, row - 1)) {
            board.setQueens(queenVec);
            board.drawBoard();
        } else {
            cout << "No solution" << endl;
        }
    }
}

#endif  // ALGORITHM_EIGHT_QUEENS_TEST_H
