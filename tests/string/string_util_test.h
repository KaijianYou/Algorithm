#ifndef ALGORITHM_STRING_UTIL_TEST_H
#define ALGORITHM_STRING_UTIL_TEST_H

#include <iostream>
#include <string>

#include "../../algorithm/string/string_util.h"

namespace myalgorithm {
    using std::cin;
    using std::cout;
    using std::endl;
    using std::string;

    void testReplaceSpaces()
    {
        const int MAX_STR_SIZE = 255;
        char testString[MAX_STR_SIZE] = "nothing is impossible to a willing heart";

        replaceSpaces(testString, MAX_STR_SIZE);
        cout << testString << endl;
    }

    void testStrSplit()
    {
        string testString = "nothing is impossible to a willing heart";
        vector<string> strVec;
        strSplit(strVec, testString, "i");

        for (auto str : strVec) {
            cout << str << endl;
        }
        cout << endl;
    }

    void testStrReplace()
    {
        string testString = "nothing is impossible to a willing heart";
        strReplace(testString, "i", "oo");
        cout << testString << endl;
    }

    void testIsPalindrome()
    {
        cout << "Enter a string: ";
        string str;
        getline(cin, str, '\n');

        if (isPalindrome(str)) {
            cout << " \"" << str << "\" is a palindrome" << endl;
        } else {
            cout << " \"" << str << "\" is not a palindrome" << endl;
        }

        cout << endl;

        if (isPalindrome(str, 0, str.size())) {
            cout << " \"" << str << "\" is a palindrome" << endl;
        } else {
            cout << " \"" << str << "\" is not a palindrome" << endl;
        }
    }

    void testReverse()
    {
        char str[] = "abcdefg";
        reverse(str);
        cout << str << endl;
    }
}

#endif  // ALGORITHM_STRING_UTIL_TEST_H
