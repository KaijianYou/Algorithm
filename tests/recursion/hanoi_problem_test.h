#ifndef ALGORITHM_HANOI_PROBLEM_TEST_H
#define ALGORITHM_HANOI_PROBLEM_TEST_H

#include <iostream>
#include <string>

#include "../../algorithm/recursion/hanoi_problem.h"

namespace myalgorithm {
    using std::cin;
    using std::cout;
    using std::endl;
    using std::string;

    void testHanoiProblem()
    {
        // 杆的名称
        string leftNeedle = "A";
        string middleNeedle = "B";
        string rightNeedle = "C";

        // 输入盘子数量
        cout << "Enter the number of disks: ";
        int numDisks;
        cin >> numDisks;

        hanoi(numDisks, leftNeedle, rightNeedle, middleNeedle);
    }
}

#endif  // ALGORITHM_HANOI_PROBLEM_TEST_H
