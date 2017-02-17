#ifndef ALGORITHM_STRING_UTIL_H_H
#define ALGORITHM_STRING_UTIL_H_H

#include <vector>
#include <string>
#include <queue>
#include <stack>

namespace myalgorithm {
    using std::vector;
    using std::string;
    using std::queue;
    using std::stack;

    // 从后往前把字符数组中的空格替换成 "%20"
    /* length 为字符数组 str 的总容量 */
    void replaceBlank(char str[], int length)
    {
        if (str == nullptr && length < 0) {
            return;
        }

        /* origLength 为字符串 str 的实际长度 */
        int origLength = 0;
        int numOfBlank = 0;
        int i = 0;
        while (str[i] != '\0') {
            ++origLength;

            if (str[i] == ' ') {
                ++numOfBlank;
            }

            ++i;
        }

        /* newLength 为把空格替换成 '%20' 之后的长度 */
        int newLength = origLength + 2 * numOfBlank;
        if (newLength > length) {
            return;
        }

        int indexOfOrig = origLength;
        int indexOfNew = newLength;
        while (indexOfOrig > 0 && indexOfNew > indexOfOrig) {
            if (str[indexOfOrig] == ' ') {
                str[indexOfNew--] = '0';
                str[indexOfNew--] = '2';
                str[indexOfNew--] = '%';
            } else {
                str[indexOfNew--] = str[indexOfOrig];
            }
            --indexOfOrig;
        }
    }

    // 用分隔符分隔字符串
    void strSplit(vector<string> &vec, const string &splitString, const string &seperator)
    {
        string str(splitString);
        str = str + seperator;  // 在字符串前后加上分隔符，以避免特殊情况的判断
        int prevPos = -1;
        int currPos = 0;
        while (currPos < str.size()) {
            currPos = str.find(seperator, currPos);
            if (currPos != string::npos) {
                if (currPos != prevPos + 1) {
                    ++prevPos;
                    vec.push_back(str.substr(prevPos, currPos - prevPos));
                }
            } else {
                break;
            }
            prevPos = currPos;
            ++currPos;
        }
    }

    // 将 strA 中的所有 strB 用 strC 代替
    void strReplace(string &strA, const string &strB, const string &strC)
    {
        if (strA.size() == 0 || strB.size() == 0 || strC.size() == 0) {
            return;
        }

        size_t pos = 0;
        while (pos < strA.size()) {
            pos = strA.find(strB, pos);
            if (pos == string::npos) {
                break;
            }
            strA.erase(pos, strB.size());
            strA.insert(pos, strC);
            pos += strC.size();
        }
    }

    // 判断回文字符串
    bool isPalindrome(const string &str, int startIndex, int endIndex) {
        if (startIndex >= endIndex) {
            return true;
        }

        if (str[startIndex] != str[endIndex - 1]) {
            return false;
        } else {
            return isPalindrome(str, startIndex + 1, endIndex - 1);
        }
    }

    // 判断回文字符串
    bool isPalindrome(const string &str)
    {
        queue<char> charQueue;
        stack<char> charStack;
        for (auto ch : str) {
            charQueue.push(ch);
            charStack.push(ch);
        }

        while (!charQueue.empty()) {
            if (charQueue.front() != charStack.top()) {
                return false;
            }

            charQueue.pop();
            charStack.pop();
        }
        return true;
    }
}

#endif  // ALGORITHM_STRING_UTIL_H_H
