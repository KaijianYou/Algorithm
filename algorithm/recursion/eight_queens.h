#ifndef ALGORITHM_EIGHT_QUEENS_H
#define ALGORITHM_EIGHT_QUEENS_H

#include <iostream>
#include <vector>

#include "../../util/matrix.h"

namespace myalgorithm {
    using std::cout;
    using std::endl;
    using std::vector;

    // 棋盘
    class ChessBoard {
    public:
        ChessBoard();

        // 将棋盘上的皇后设置到 (queenVec[col], col) 格
        void setQueens(const vector<int> &queenVec);
        // 清棋盘
        void clearBoard();
        // 使用符号 'Q' 或 '-' 画出棋盘
        void drawBoard() const;

    private:
        Matrix<bool> board;  // 模拟国际象棋棋盘
    };

    ChessBoard::ChessBoard() : board(8, 8)
    {
        clearBoard();
    }

    void ChessBoard::setQueens(const vector<int> &queenVec)
    {
        clearBoard();

        for (int col = 0; col < 8; ++col) {
            board[queenVec[col]][col] = true;
        }
    }

    void ChessBoard::clearBoard()
    {
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                board[i][j] = false;
            }
        }
    }

    void ChessBoard::drawBoard() const
    {
        cout << "   1 2 3 4 5 6 7 8" << endl;
        for (int i = 0; i < 8; ++i) {
            cout << i + 1 << " ";
            for (int j = 0; j < 8; ++j) {
                if (board[i][j] == true) {
                    cout << " Q";
                } else {
                    cout << " -";
                }
            }
            cout << endl;
        }
    }


    // 判断是否是安全的位置
    bool safeLocation(int row, int col, const vector<int> &queenVec)
    {
        for (int qCol = 0; qCol < col; ++qCol) {
            int qRow = queenVec[qCol];
            if (qRow == row) {  // 在同一行，不安全
                return false;
            } else if (qCol == col) {  // 在同一列，不安全
                return false;
            } else if ((qCol - qRow == col - row) ||
                       (qRow + qCol == row + col)) {  // 在对角线方向上，不安全
                return false;
            }
        }

        return true;
    }

    // 如果能完整解决八皇后问题，就返回 true，否则返回 false
    bool placeQueens(vector<int> &queenVec, int col)
    {
        bool foundLocation = false;
        if (col == 8) {  // 终止查找
            foundLocation = true;
        } else {
            foundLocation = false;
            int row = 0;
            while (row < 8 && !foundLocation) {
                if (safeLocation(row, col, queenVec)) {
                    queenVec[col] = row;
                    foundLocation = placeQueens(queenVec, col + 1);
                    // 当前行没有安全位置，在下一行进行查找
                    if (!foundLocation) {
                        ++row;
                    }
                } else {  // 当前行没有安全位置，在下一行进行查找
                    ++row;
                }
            }
        }

        return foundLocation;
    }

    // 将第 1 个皇后放在方格 (row, 0) 中，
    // 再调用 placeQueens() 来确定第 1 列到第 7 列是否可以放下 7 个皇后
    bool queens(vector<int> &queenVec, int row)
    {
        queenVec[0] = row;
        if (placeQueens(queenVec, 1)) {
            return true;
        } else {
            return false;
        }
    }
}

#endif  // ALGORITHM_EIGHT_QUEENS_H