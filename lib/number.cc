#include "number.h"
#include <bitset>
#include <string>
#include <cstring>
#include <cmath>

int2024_t from_int(long long i) {
    int2024_t number;
    if(i < 0) {
        number.number[0] |= 128;
        i *= -1;
    }
    number.number[252] = static_cast<char>(i);
    number.number[251] = static_cast<char>(i >> 8);
    number.number[250] = static_cast<char>(i >> 16);
    number.number[249] = static_cast<char>(i >> 24);
    number.number[248] = static_cast<char>(i >> 32);
    number.number[247] = static_cast<char>(i >> 40);
    number.number[246] = static_cast<char>(i >> 48);
    number.number[245] = static_cast<char>(i >> 56);
    return number;
}

int2024_t from_string(const char* buff) {
    int2024_t number;
    std::string s = {buff, buff+std::strlen(buff)};
    int id = 252;
    for (int i = static_cast<int>(s.size()) - 1; i >= 0; i -= 8) {
        auto cc = s.substr(i - 8 + 1, 8);
        int j = 7; 
        for (auto c : cc) {
            number.number[id] |= (int)(c - '0') << j;
            j--;
        }
        id--;
    }
    return number;
}

int2024_t operator+(const int2024_t& lhs, const int2024_t& rhs) {
    
    return int2024_t();
}

int2024_t operator-(const int2024_t& lhs, const int2024_t& rhs) {
    return int2024_t();
}

int2024_t operator*(const int2024_t& lhs, const int2024_t& rhs) {
    return int2024_t();
}

int2024_t operator/(const int2024_t& lhs, const int2024_t& rhs) {
    return int2024_t();
}

bool operator==(const int2024_t& lhs, const int2024_t& rhs) {
    return false;
}

bool operator!=(const int2024_t& lhs, const int2024_t& rhs) {
    return false;
}

std::ostream& operator<<(std::ostream& stream, const int2024_t& value) {
    for (int i = 0; i < 253; i++){
        stream << std::bitset<8>(value.number[i]) << " ";
    }
    return stream;
}