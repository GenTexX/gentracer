#include "interval.h"

Interval::Interval() : min(+std::numeric_limits<float>::infinity()), max(-std::numeric_limits<float>::infinity()) {}


Interval::Interval(float minVal, float maxVal) : min(minVal), max(maxVal) {

}

Interval Interval::empty() {
    return Interval(+std::numeric_limits<float>::infinity(), -std::numeric_limits<float>::infinity());
}

Interval Interval::universe() {
    return Interval(-std::numeric_limits<float>::infinity(),
            +std::numeric_limits<float>::infinity());
}

bool Interval::contains(float x) const {
    return x >= min && x <= max;
}


bool Interval::surrounds(float x) const {
    return x > min && x < max;
}

float Interval::clamp(float x) const {
    return std::clamp(x, min, max);
}

void Interval::expandToInclude(float x) {
    if (x < min) min = x;
    if (x > max) max = x;
}


void Interval::expandToInclude(const Interval& other) {
    min = std::min(min, other.min);
    max = std::max(max, other.max);
}


float Interval::size() const {
    return max - min;
}


bool Interval::isEmpty() const {
    return min > max;
}


Interval Interval::intersect(const Interval& a, const Interval& b) {
    return Interval(std::max(a.min, b.min), std::min(a.max, b.max));
}

bool Interval::overlaps(const Interval& a, const Interval& b) {
    return a.max >= b.min && b.max >= a.min;
}

std::ostream& operator<<(std::ostream& os, const Interval& interval) {
    return os << "[" << interval.min << ", " << interval.max << "]";
}
