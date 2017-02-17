#ifndef ALGORITHM_STACK_BASED_ON_VECTOR_H
#define ALGORITHM_STACK_BASED_ON_VECTOR_H

#include <vector>
#include <stdexcept>

namespace myalgorithm {
    using std::vector;

    // 基于向量的栈的简单实现
    template<typename T, typename Container = vector<T>>
    class Stack {
    public:
        Stack();
        virtual ~Stack();

        void push(const T &item);
        void pop();

        T& top();
        const T& top() const;

        size_t size() const { return container.size(); }
        bool empty() const { return size() == 0; }

    private:
        Container container;
    };

    template<typename T, typename Container>
    Stack<T, Container>::Stack()
    {}

    template <typename T, typename Container>
    Stack<T, Container>::~Stack()
    {}

    template<typename T, typename Container>
    void Stack<T, Container>::push(const T &item)
    {
        container.push_back(item);
    }

    template<typename T, typename Container>
    void Stack<T, Container>::pop()
    {
        if (empty()) {
            throw std::underflow_error("Stack.pop(): stack is empty");
        }

        container.pop_back();
    }

    template<typename T, typename Container>
    T &Stack<T, Container>::top()
    {
        if (empty()) {
            throw underflow_error("Stack.top(): stack is empty");
        }

        return container.back();
    }

    template<typename T, typename Container>
    const T &Stack<T, Container>::top() const
    {
        if (empty()) {
            throw underflow_error("Stack.top(): stack is empty");
        }

        return container.back();
    }
}

#endif  // ALGORITHM_STACK_BASED_ON_VECTOR_H