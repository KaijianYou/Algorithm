#ifndef ALGORITHM_HANOI_PROBLEM_H
#define ALGORITHM_HANOI_PROBLEM_H

#include <iostream>
#include <string>

namespace myalgorithm {
    using std::cout;
    using std::endl;
    using std::string;

    // 递归解决汉诺塔问题
    // 从 srcNeedle 移动 n 个盘子到 dstNeedle，将 tempNeedle 作为辅助
    void hanoi(int n, const string &srcNeedle,
               const string &dstNeedle, const string &tempNeedle)
    {
        if (n == 1) {
            cout << "move " << srcNeedle << " to " << dstNeedle << endl;
        } else {
            // 从 firstNeedle 到 tempNeedle 移动 n - 1 个盘子，将 dstNeedle 作为辅助
            hanoi(n - 1, srcNeedle, tempNeedle, dstNeedle);

            // 移动最大的盘子到 dstNeedle
            cout << "move " << srcNeedle << " to " << dstNeedle << endl;

            // 从 tempNeedle 到 dstNeedle 移动 n - 1 个盘子，将 srcNeedle 作为辅助
            hanoi(n - 1, tempNeedle, dstNeedle, srcNeedle);
        }
    }
}

#endif  // ALGORITHM_HANOI_PROBLEM_H