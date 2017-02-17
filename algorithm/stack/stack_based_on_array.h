#ifndef ALGORITHM_STACK_BASED_ON_ARRAY_H
#define ALGORITHM_STACK_BASED_ON_ARRAY_H

#define NDEBUG

#include <cassert>

namespace myalgorithm  {
    const int MAX_STACK_SIZE = 20;

    // 基于数组的栈的简单实现
    template <typename T>
    class Stack {
    public:
        Stack();
        virtual ~Stack();

        void push(const T &item);
        void pop();

        T& top();
        const T& top() const;

        size_t size() const { return _top; }
        bool empty() const { return size() == 0; }

    private:
        T arr[MAX_STACK_SIZE];
        size_t _top;
    };

    template <typename T>
    Stack<T>::Stack() : _top(0)
    {}

    template <typename T>
    Stack<T>::~Stack()
    {}

    template <typename T>
    void Stack<T>::push(const T &item)
    {
        assert(_top < MAX_STACK_SIZE);
        arr[_top] = item;
        ++_top;
    }

    template <typename T>
    void Stack<T>::pop()
    {
        assert(_top > 0);
        --_top;
    }

    template <typename T>
    T& Stack<T>::top()
    {
        assert(_top > 0);
        return arr[_top - 1];
    }

    template <typename T>
    const T& Stack<T>::top() const
    {
        assert(_top > 0);
        return arr[_top - 1];
    }
}

#endif  // ALGORITHM_STACK_BASED_ON_ARRAY_H