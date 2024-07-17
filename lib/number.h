#pragma once
#include <cinttypes>
#include <iostream>


class int2024_t {
    // implement
};

static_assert(sizeof(int2024_t) <= 253, "Size of int2024_t must be no higher than 253 bytes");

int2024_t from_int(int i);

int2024_t from_string(const char* buff);

int2024_t operator+(const int2024_t& lhs, const int2024_t& rhs);

int2024_t operator-(const int2024_t& lhs, const int2024_t& rhs);

int2024_t operator*(const int2024_t& lhs, const int2024_t& rhs);

int2024_t operator/(const int2024_t& lhs, const int2024_t& rhs);

bool operator==(const int2024_t& lhs, const int2024_t& rhs);

bool operator!=(const int2024_t& lhs, const int2024_t& rhs);

std::ostream& operator<<(std::ostream& stream, const int2024_t& value);