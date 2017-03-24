#ifndef ALGORITHM_VECTOR_BASED_ON_DYNAMIC_ARRAY_H
#define ALGORITHM_VECTOR_BASED_ON_DYNAMIC_ARRAY_H

#include <stdexcept>

namespace myalgorithm {
    using std::underflow_error;
    using std::out_of_range;
    
    // vector 的简单实现
    template <typename T>
    class Vector {
    public:
        explicit Vector(int size = 0);
        Vector(const Vector &obj);
        virtual ~Vector();

        Vector& operator=(const Vector &rhs);
        T& operator[](int index);
        const T& operator[](int index) const;

        int size() const { return _size; }
        int capacity() const { return _capacity; }
        bool empty() const { return _size == 0; }
        
        void resize(int newSize);

        void push_back(const T &newValue);
        void pop_back();

        T& back();
        const T& back() const;

        void insert(int index, const T &item);
        void erase(int index);

        typedef T* Iterator;
        typedef const T* ConstIterator;

        Iterator begin() { return &array[0]; }
        ConstIterator begin() const { return &array[0]; }
        Iterator end() { return &array[_size]; }
        ConstIterator end() const { return &array[_size]; }

    private:
        T *array;
        int _size;
        int _capacity;

        // 扩展向量的容量到 newCapactiy 个元素，将现有元素复制到新空间，删除旧的动态数组
        void reserve(int newCapacity);
    };

    template <typename T>
    void Vector<T>::reserve(int newCapacity)
    {
        if (newCapacity < _size) {
            return;
        }

        T *newArray = new T[newCapacity];
        for (int i = 0; i < _size; ++i) {
            newArray[i] = array[i];
        }

        if (array != nullptr) {
            delete [] array;
        }

        array = newArray;
        _capacity = newCapacity;
    }

    template <typename T>
    Vector<T>::Vector(int size) :
        _size(size), _capacity(size * 2 + 1)
    {
        array = new T[_capacity];
        for (int i = 0; i < _size; ++i) {
            array[i] = T();
        }
    }

    template <typename T>
    Vector<T>::Vector(const Vector<T> &obj) :
        _size(0), _capacity(0), array(nullptr)
    {
        if (obj._size == 0) {
            return;
        }

        reserve(obj._size);
    }

    template <typename T>
    Vector<T>::~Vector()
    {
        if (array != nullptr) {
            delete [] array;
        }
    }

    template <typename T>
    T& Vector<T>::operator[](int index)
    {
        if (index < 0 || index >= _size) {
            throw out_of_range("Vector.[]: index out of range");
        }

        return array[index];
    }

    template <typename T>
    const T& Vector<T>::operator[](int index) const
    {
        if (index < 0 || index >= _size) {
            throw out_of_range("Vector.[]: index out of range");
        }
    }

    template <typename T>
    Vector<T>& Vector<T>::operator=(const Vector<T> &rhs)
    {
        if (this != &rhs) {
            if (_capacity < rhs._size) {
                _size = rhs._size;
                reserve(rhs._size);
            }
        }

        return *this;
    }

    template <typename T>
    void Vector<T>::resize(int newSize)
    {
        if (newSize > _capacity) {
            reserve(newSize * 2 + 1);
        }
        _size = newSize;
    }

    template <typename T>
    void Vector<T>::push_back(const T &newValue)
    {
        if (_size == _capacity) {
            reserve(_size * 2 + 1);
        }

        array[_size++] = newValue;
    }

    template <typename T>
    void Vector<T>::pop_back()
    {
        if (empty()) {
            throw underflow_error("Vector.pop_back(): Vector is empty");
        }
        --_size;
    }

    template <typename T>
    T& Vector<T>::back()
    {
        if (empty()) {
            throw underflow_error("Vector.back(): Vector is empty");
        }

        return array[_size - 1];
    }

    template <typename T>
    const T& Vector<T>::back() const
    {
        if (empty()) {
            throw underflow_error("Vector.back(): Vector is empty");
        }

        return array[_size - 1];
    }

    template <typename T>
    void Vector<T>::insert(int index, const T &item)
    {
        if (index < 0 || index > _size) {
            throw out_of_range("index out of range");
        }

        if (_size == _capacity) {
            reserve(2 * _capacity + 1);
        }

        int i = ++_size;
        for (; i >= 0 && i > index; --i) {
            array[i] = array[i - 1];
        }
        array[i] = item;
    }

    template <typename T>
    void Vector<T>::erase(int index)
    {
        if (index < 0 || index >= _size) {
            throw out_of_range("index out of range");
        }

        for (int i = index; i < _size - 1; ++i) {
            array[i] = array[i + 1];
        }
        --_size;
    }
}

#endif  // ALGORITHM_VECTOR_BASED_ON_DYNAMIC_ARRAY_H