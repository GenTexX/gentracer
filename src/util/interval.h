#pragma once

#include <algorithm>
#include <limits>
#include <ostream>

class Interval {
public:
    float min;
    float max;

    Interval();

    Interval(float minVal, float maxVal);

    // Common static intervals
    static Interval empty(); 

    static Interval universe(); 

    // Check if a value is within the interval
    bool contains(float x) const; 

    bool surrounds(float x) const; 

    // Clamp a value to the interval
    float clamp(float x) const; 

    // Expand this interval to include a value
    void expandToInclude(float x); 

    // Expand this interval to include another interval
    void expandToInclude(const Interval& other); 

    // Length of the interval
    float size() const; 

    // Is this interval empty or invalid?
    bool isEmpty() const; 

    // Intersection of two intervals
    static Interval intersect(const Interval& a, const Interval& b); 

    // Overlap check
    static bool overlaps(const Interval& a, const Interval& b); 

    friend std::ostream& operator<<(std::ostream& os, const Interval& interval); 
};
