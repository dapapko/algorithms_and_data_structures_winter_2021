#pragma once
#include <iostream>
#include <array>
#include <limits>
#include <map>
#include<math.h>
using namespace std;

template<typename T>
class Binnum {
    static const int radix = sizeof(T) * 8;
    array<bool, radix> bin;

public:
    static void check_range(T number) {
        if (number < numeric_limits<T>::min() || number > numeric_limits<T>::max()) {
            throw runtime_error("number is out of range");
        }
    }

    Binnum() :
        bin({}) {}

    explicit Binnum(T num) :
        bin(to_bin(num)) {
    }

    explicit Binnum(array<bool, radix> bin) :
        bin(bin) {}


    size_t size() const {
        return  bin.size();
    }


    array<bool, radix> to_bin(T num) {
        check_range(num);
        array<bool, radix> bin;
        map<int, int> masks = { {8,0100}, {16, 040000},
        {32, 010000000000} };
        T mask = masks[radix];

        bin[0] = (num < 0 ? 1 : 0);
        unsigned int absval = abs(num);
        for (int i = 1; i < radix; ++i) {
            bin[i] = (absval & mask ? 1 : 0);
            mask >>= 1;
        }
        return bin;
    }

    Binnum additional_code() const {
        Binnum res = *this;
        bool temp = res.bin[0];
        for (int k = 0; k < radix; k++) {
            res.bin[k] = !res.bin[k];
        }
        Binnum comp;
        comp.bin[size() - 1] = true;
        res = res + comp;
        res.bin[0] = temp;
        return res;
    }

    Binnum operator+(const Binnum& other) const {
        array<bool, radix> res;

        Binnum A = *this;
        Binnum B = other;

        if (A.bin[0]) {
            A = A.additional_code();
        }

        if (B.bin[0]) {
            B = B.additional_code();
        }

        bool carry = false;
        bool carryOut;
        for (int i = size() - 1; i >= 0; i--) {
            auto a = A.bin[i];
            auto b = B.bin[i];
            res[i] = ((a ^ b) ^ carry);
            carry = ((a & b) | (a & carry)) | (b & carry);
            if (i == 1) carryOut = carry;
        }
        if (carryOut ^ carry) {
            throw runtime_error("Overflow error");
        }


        return Binnum(res);
    }


    Binnum shift() {
        Binnum res = *this;
        auto temp = res.bin[0];
        int k = 0;
        for (k = 0; k < size() - 1; k++) {
            res.bin[k] = res.bin[k + 1];
        }
        res.bin[k] = temp;
        return res;
    }

    Binnum operator*(const Binnum<T>& other) const {
        auto sign = bin[0] ^ other.bin[0];
        Binnum res;
        Binnum a = *this;
        Binnum b = other;
        a.bin[0] = false;
        b.bin[0] = false;

        for (int k = radix - 1; k > 0; k--) {
            if (b.bin[k]) {
                if (a.bin[0]) {
                    throw runtime_error("Overflow error");
                }
                res = res + a;
            }
            a = a.shift();
            if (res.bin[0]) {
                throw runtime_error("Overflow error");
            }
        }
        res.bin[0] = sign;
        if (sign) {
            return res.additional_code();
        }
        else {
            return  res;
        }

    }

    T to_dec() {
        int k = 0;
        int dec = 0;

        for (int i = radix - 1; i >= 0; i--) {
            dec += bin[i] * pow(2, k);
            k++;
        }

        return dec;
    }

    friend ostream& operator<<(ostream& stream, const Binnum& binary_num) {
        for (auto element : binary_num.bin) {
            stream << element;
        }
        stream << endl;
        return stream;
    }

    Binnum operator-(const Binnum<T>& other) const {
        auto B = other;
        B.bin[0] = !bin[0];
        return *this + B;
    }
};





