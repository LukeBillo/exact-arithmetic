#include <sstream>
#include "integer.h"

ExactArithmetic::Integer::Integer() {
    digits->push_front(0);
}

ExactArithmetic::Integer::Integer(unsigned long long int i) {
    // if already 0, just push 0 and return
    if (i == 0) {
        digits->push_front(0);
        return;
    }

    // iterates in orders of 10, extracting the current digit
    // with modulo and dividing; pushes to front so that the
    // array of digits has most significant digit at the front.
    while (i > 0) {
        auto nextDigit = i % 10;
        digits->push_front(nextDigit);

        i /= 10;
    }
}

ExactArithmetic::Integer::Integer(const std::string& stringInt) {
    // since this is iterated over in reverse, i.e. from most
    // significant bit to least, need to push_back here.

    for (char i : stringInt) {
        // converts ASCII characters to short
        // numbers 1-9 are 48-57 in ASCII DEC.

        short converted = i - 48;

        // if this isn't a number 1-9, throws exception
        if (converted < 0 || converted > 9)
            throw std::invalid_argument("Invalid argument constructing Integer with string: " + stringInt + ", not a valid number.");

        digits->push_back(converted);
    }
}

std::string ExactArithmetic::Integer::toString() const {
    std::stringstream ss;

    // since most significant bit is at the front, can just
    // iterate through the digits in order like so..

    for (Digit& i : *digits) {
        ss << i;
    }

    return ss.str();
}

int ExactArithmetic::Integer::toInt() {
    // utility methods, rarely used...
    // should be used for testing only, hence
    // lack of attention to performance.

    auto stringified = toString();
    return std::stoi(stringified);
}

unsigned long long ExactArithmetic::Integer::toInt64() {
    auto stringified = toString();
    return std::stoull(stringified);
}

bool ExactArithmetic::Integer::operator==(const ExactArithmetic::Integer& other) const {
    // can skip checking each digit if sizes differ
    if (digits->size() != other.digits->size())
        return false;

    // otherwise, check each digit...
    auto thisDigit = digits->begin();
    auto otherDigit = other.digits->begin();

    while (thisDigit != digits->end()) {
        if (*thisDigit != *otherDigit) {
            return false;
        }

        ++thisDigit;
        ++otherDigit;
    }

    return true;
}

bool ExactArithmetic::Integer::operator!=(const ExactArithmetic::Integer& other) const {
    return !operator==(other);
}

bool ExactArithmetic::Integer::operator<(const ExactArithmetic::Integer& other) const {
    auto mismatch = std::mismatch(digits->begin(), digits->end(), other.digits->begin(), other.digits->end(),
        [](Digit first, Digit second) {
            return first == second;
        }
    );

    auto stringThis = toString();
    auto stringOther = other.toString();

    // how far are each of these from the end / least significant digit?
    auto distanceFromEnd = std::distance(mismatch.first, digits->end());
    auto distanceFromEndOther = std::distance(mismatch.second, other.digits->end());

    // if of equal magnitude, i.e. equal distance from end of list
    // then just compare digits...
    if (distanceFromEnd == distanceFromEndOther) {
        return *mismatch.first < *mismatch.second;
    }

    // otherwise, find which is of larger magnitude;
    // if index is larger, it is a less significant
    // digit than the other.
    return distanceFromEnd < distanceFromEndOther;
}
