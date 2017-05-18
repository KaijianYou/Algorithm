#ifndef ALGORITHM_HANOI_PROBLEM_H
#define ALGORITHM_HANOI_PROBLEM_H

#include <iostream>
#include <string>

namespace myalgorithm {
    using std::cout;
    using std::endl;
    using std::string;

    // 递归解决汉诺塔问题
    // 从 src 移动 n 个盘子到 dst，将 buf 作为辅助
    void hanoi(int n, const string &src, const string &dst, const string &buf)
    {
        if (n == 1) {
            cout << "move from " << src << " to " << dst << endl;
        }
        // 从 src 到 buf 移动 n - 1 个盘子，将 dst 作为辅助
        hanoi(n - 1, src, buf, dst);

        // 移动最大的盘子到 dst
        hanoi(1, src, dst, buf);

        // 从 buf 到 dst 移动 n - 1 个盘子，将 src 作为辅助
        hanoi(n - 1, buf, dst, src);
    }
}

#endif  // ALGORITHM_HANOI_PROBLEM_H