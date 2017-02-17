#ifndef ALGORITHM_BIT_BASED_ON_VECTOR_H
#define ALGORITHM_BIT_BASED_ON_VECTOR_H

#include <fstream>

#include <iostream>
#include <vector>
#include <stdexcept>

namespace myalgorithm {
    using std::fstream;
    using std::ostream;
    using std::vector;
    using std::range_error;

    // 位向量
    class Bit {
    public:
        Bit(int numBits = 16);
        Bit(int bits[], int numBits);
        Bit(const Bit &obj);
        virtual ~Bit();

        // 将 rhs 的二进制位赋值给位向量
        Bit& operator=(Bit bit);
        Bit& operator=(int rhs);
        Bit& operator=(char rhs);

        int size() const;
        // 返回位 index 的值
        int bit(int index) const;
        // 设置位 index 的值
        void set(int index);
        // 清除位 index
        void clear(int index);
        // 清除所有位
        void clear();

        friend bool operator==(const Bit &lhs, const Bit &rhs);

        friend Bit operator|(const Bit &lhs, const Bit &rhs);  // 按位或
        friend Bit operator&(const Bit &lhs, const Bit &rhs);  // 按位与
        friend Bit operator^(const Bit &lhs, const Bit &rhs);  // 按位异或

        friend Bit operator<<(const Bit &lhs, int n);  // 位左移
        friend Bit operator>>(const Bit &lhs, int n);  // 位右移

        Bit operator~();  // 按位取反

        void write(fstream &out);
        void read(fstream &in, int numBits);

        // 以 ASCII 格式输出位向量
        friend ostream& operator<<(ostream &out, const Bit &rhs);

    private:
        int numBits;  // 向量中的位数
        int vectorSize;  // 位向量中的字节数

        // 位向量，一个 member 元素提供 8 位存储空间，
        // member 中的每位都与范围 0 ~ numBits 之间的数一一对应
        vector<unsigned char> member;

        // 返回包含位 index 的向量元素的下标
        int vectorIndex(int index) const;

        // 位掩码
        // 返回无符号字符值，在表示位 index 的 2 进制位值为 1
        unsigned char bitMask(int index) const;
    };

    int Bit::vectorIndex(int index) const
    {
        return index >> 3;  // index / 8
    }

    unsigned char Bit::bitMask(int index) const
    {
        return 1 << (7 - (index & 7));  // index & 7 求得 index / 8 的余数
    }

    Bit::Bit(int numBits) : numBits(numBits)
    {
        vectorSize = (numBits + 7) >> 3;
        member.resize(vectorSize);
    }

    Bit::Bit(int bits[], int numBits) : numBits(numBits)
    {
        vectorSize = (numBits + 7) >> 3;
        member.resize(vectorSize);
        for (int i = 0; i < numBits; ++i) {
            if (bits[i] != 0) {
                set(i);
            }
        }
    }

    Bit::Bit(const Bit &obj) : numBits(obj.numBits), vectorSize(obj.vectorSize)
    {
        member.resize(vectorSize);
        for (int i = 0; i < vectorSize; ++i) {
            member[i] = obj.member[i];
        }
    }

    Bit::~Bit()
    {}

    Bit& Bit::operator=(Bit rhs)
    {
        if (this != &rhs) {
            vectorSize = rhs.vectorSize;
            numBits = rhs.numBits;
            member.resize(vectorSize);
            for (int i = 0; i < vectorSize; ++i) {
                member[i] = rhs.member[i];
            }
        }

        return *this;
    }

    Bit& Bit::operator=(int rhs)
    {
        vectorSize = sizeof(int);
        numBits = sizeof(int) * 8;
        member.resize(vectorSize);

        unsigned int mask = ~(((unsigned int) ~0) >> 1);
        for (int i = 0; i < numBits; ++i) {
            if (mask & rhs) {
                set(i);
            } else {
                clear(i);
            }

            mask >>= 1;
        }

        return *this;
    }

    Bit& Bit::operator=(char rhs)
    {
        vectorSize = sizeof(char);
        numBits = sizeof(char) * 8;

        member.resize(vectorSize);

        unsigned char mask = ~(((unsigned char) ~0) >> 1);
        for (int i = 0; i < numBits; ++i) {
            if (mask & rhs) {
                set(i);
            } else {
                clear(i);
            }

            mask >>= 1;
        }

        return *this;
    }

    int Bit::size() const
    {
        return numBits;
    }

    int Bit::bit(int index) const
    {
        if (index < 0 || index >= numBits) {
            throw out_of_range("Bit.bit(): bit index is out of range");
        }

        if ((bitMask(index) & member[vectorIndex(index)]) != 0) {
            return 1;
        } else {
            return 0;
        }
    }

    void Bit::set(int index)
    {
        if (index < 0 || index >= numBits) {
            throw out_of_range("Bit.bit(): bit index is out of range");
        }

        member[vectorIndex(index)] |= bitMask(index);
    }

    void Bit::clear(int index)
    {
        if (index < 0 || index >= numBits) {
            throw out_of_range("Bit.bit(): bit index is out of range");
        }

        member[vectorIndex(index)] &= ~bitMask(index);
    }

    void Bit::clear()
    {
        for (int i = 0; i < vectorSize; ++i) {
            member[i] = 0;
        }
    }

    bool operator==(const Bit &lhs, const Bit &rhs)
    {
        if (lhs.numBits == rhs.numBits) {
            for (int i = 0; i < lhs.vectorSize; ++i) {
                if (lhs.member[i] != rhs.member[i]) {
                    return false;
                }
            }

            return true;
        } else {
            return false;
        }
    }

    Bit operator|(const Bit &lhs, const Bit &rhs)
    {
        if (lhs.numBits != rhs.numBits) {
            throw range_error("Bit.operator |: two Bits are not the same size");
        }

        Bit bit(lhs.numBits);
        for (int i = 0; i < lhs.vectorSize; ++i) {
            bit.member[i] = lhs.member[i] | rhs.member[i];
        }

        return bit;
    }

    Bit operator&(const Bit &lhs, const Bit &rhs)
    {
        if (lhs.numBits != rhs.numBits) {
            throw range_error("Bit.operator &: two Bits are not the same size");
        }

        Bit bit(lhs.numBits);
        for (int i = 0; i < lhs.vectorSize; ++i) {
            bit.member[i] = lhs.member[i] & rhs.member[i];
        }

        return bit;
    }

    Bit operator^(const Bit &lhs, const Bit &rhs)
    {
        if (lhs.numBits != rhs.numBits) {
            throw range_error("Bit.operator ^: two Bits are not the same size");
        }

        Bit bit(lhs.numBits);
        for (int i = 0; i < lhs.vectorSize; ++i) {
            bit.member[i] = lhs.member[i] ^ rhs.member[i];
        }

        return bit;
    }

    Bit operator<<(const Bit &lhs, int n)
    {
        Bit bit = lhs;

        for (int i = n; i < bit.numBits; ++i) {
            if (bit.bit(i) == 1) {
                bit.set(i - n);
            } else {
                bit.clear(i - n);
            }
        }

        for (int i = 0; i < n; ++i) {
            bit.clear(bit.numBits - 1 - i);
        }

        return bit;
    }

    Bit operator>>(const Bit &lhs, int n)
    {
        Bit bit = lhs;

        for (int i = bit.numBits - 1 - n; i >= 0; --i) {
            if (bit.bit(i) == 1) {
                bit.set(i + n);
            } else {
                bit.clear(i + n);
            }
        }

        for (int i = 0; i < n; ++i) {
            bit.clear(i);
        }

        return bit;
    }

    Bit Bit::operator~()
    {
        Bit bit(numBits);
        for (int i = 0; i < vectorSize; ++i) {
            bit.member[i] = ~member[i];
        }

        return bit;
    }

    void Bit::write(fstream &out)
    {
        out.write((char*) &member[0], vectorSize);
        out.flush();
    }

    void Bit::read(fstream &in, int numBits)
    {
        this->numBits = numBits;
        vectorSize = (numBits + 7) >> 3;
        member.resize(vectorSize);

        in.read((char*) &member[0], vectorSize);
    }

    ostream& operator<<(ostream &out, const Bit &rhs)
    {
        for (int i = 0; i < rhs.numBits; ++i) {
            if (rhs.bit(i) != 0) {
                out << 1;
            } else {
                cout << 0;
            }
        }

        return out;
    }
}

#endif  // ALGORITHM_BIT_BASED_ON_VECTOR_H