#include <sstream>
#include <dividebyzeroerror.h>
#include "integer.h"

//region Constructors
#pragma region Constructors

ExactArithmetic::Integer::Integer() {
    digits->push_front(0);
}

ExactArithmetic::Integer::Integer(unsigned long long int i) {
    // if already 0, just push 0 and return
    if (i == 0) {
        digits->push_front(0);
        return;
    }

    intToDigits(i);
}

ExactArithmetic::Integer::Integer(const std::string& stringInt) {
    // since this is iterated over in reverse, i.e. from most
    // significant bit to least, need to push_back here.

    for (char i : stringInt) {
        // converts ASCII characters to short
        // numbers 1-9 are 48-57 in ASCII DEC, hence
        // ASCII_NUMBERS_START = 48.

        short converted = i - ASCII_NUMBERS_START;

        // if this isn't a number 1-9, throws exception
        if (converted < 0 || converted > 9)
            throw std::invalid_argument("Invalid argument constructing Integer with string: " + stringInt + ", not a valid number.");

        digits->push_back(converted);
    }

    removeLeadingZeros();

    if (digits->empty()) {
        digits->push_back(0);
    }
}

ExactArithmetic::Integer::Integer(const ExactArithmetic::Integer& existing) {
    digits = std::make_unique<DigitList>(*existing.digits);
}

#pragma endregion Constructors
//endregion constructors

//region ArithmeticOperators
#pragma region ArithmeticOperators

ExactArithmetic::Integer ExactArithmetic::Integer::operator+(const ExactArithmetic::Integer& addition) const {
    // makes a copy of this to be used as a result
    Integer result = *this;
    result += addition;
    return result;
}

ExactArithmetic::Integer ExactArithmetic::Integer::operator-(const ExactArithmetic::Integer& subtraction) const {
    Integer result = *this;
    result -= subtraction;
    return result;
}

ExactArithmetic::Integer ExactArithmetic::Integer::operator/(const ExactArithmetic::Integer& divider) const {
    Integer result = Integer(*this);
    result /= divider;
    return result;
}

ExactArithmetic::Integer ExactArithmetic::Integer::operator%(const ExactArithmetic::Integer& divider) const {
    Integer result = Integer(*this);
    result %= divider;
    return result;
}

#pragma endregion ArithmeticOperators
//endregion ArithmeticOperators

//region ComparisonOperators
#pragma region ComparisonOperators

bool ExactArithmetic::Integer::operator<(const ExactArithmetic::Integer& other) const {
    return compare(other) == LT;
}

bool ExactArithmetic::Integer::operator>(const ExactArithmetic::Integer& other) const {
    return compare(other) == GT;
}

bool ExactArithmetic::Integer::operator<=(const ExactArithmetic::Integer& other) const {
    return compare(other) != GT;
}

bool ExactArithmetic::Integer::operator>=(const ExactArithmetic::Integer& other) const {
    return compare(other) != LT;
}

bool ExactArithmetic::Integer::operator==(const ExactArithmetic::Integer& other) const {
    return compare(other) == EQ;
}

bool ExactArithmetic::Integer::operator!=(const ExactArithmetic::Integer& other) const {
    return !operator==(other);
}

#pragma endregion ComparisonOperators
//endregion ComparisonOperators

//region CompoundAssignmentOperators
#pragma region CompoundAssignmentOperators

ExactArithmetic::Integer& ExactArithmetic::Integer::operator+=(const ExactArithmetic::Integer& addition) {
    auto thisIterator = digits->rbegin();
    auto additionIterator = addition.digits->rbegin();

    int carry = 0;

    while (additionIterator != addition.digits->rend()) {
        if (thisIterator == digits->rend())
        {
            digits->push_front(*additionIterator);
            thisIterator = --digits->rend();
        }
        else
        {
            *thisIterator += *additionIterator;
        }

        *thisIterator += carry;
        carry = 0;

        if (*thisIterator > MAX_DIGIT) {
            // carry is always 1 (*thisIterator / 10)
            carry = 1;
            *thisIterator %= 10;
        }

        ++additionIterator;
        ++thisIterator;
    }

    while (carry != 0) {
        if (thisIterator == digits->rend())
        {
            digits->push_front(carry);
            carry = 0;
        }
        else
        {
            *thisIterator += carry;
            carry = 0;

            if (*thisIterator > MAX_DIGIT)
            {
                carry = 1;
                *thisIterator %= 10;
            }

            ++thisIterator;
        }
    }

    return *this;
}

ExactArithmetic::Integer& ExactArithmetic::Integer::operator-=(const ExactArithmetic::Integer& subtraction) {
    // check if result would be -ve or 0
    if (subtraction >= *this) {
        digits->clear();
        digits->push_front(0);

        return *this;
    }

    // else, need to subtract...
    auto thisIterator = digits->rbegin();
    auto subIterator = subtraction.digits->rbegin();

    while (subIterator != subtraction.digits->rend()) {
        if (*thisIterator >= *subIterator)
        {
            *thisIterator -= *subIterator;
        }
        else
        {
            // else, it is smaller...

            // copy iterator
            std::reverse_iterator next = thisIterator;
            next++;

            while (*next == 0) {
                *next = MAX_DIGIT;
                ++next;
            }

            *next -= 1;

            *thisIterator += 10;
            *thisIterator -= *subIterator;
        }

        ++thisIterator;
        ++subIterator;
    }

    removeLeadingZeros();

    return *this;
}

ExactArithmetic::Integer &ExactArithmetic::Integer::operator/=(const ExactArithmetic::Integer& divider) {
    // pair<quotient, remainder>
    std::pair<Integer, Integer> result = divide(divider);

    digits = std::move(result.first.digits);
    return *this;
}

ExactArithmetic::Integer &ExactArithmetic::Integer::operator%=(const ExactArithmetic::Integer& divider) {
    // pair<quotient, remainder>
    std::pair<Integer, Integer> result = divide(divider);

    digits = std::move(result.second.digits);
    return *this;
}

#pragma endregion CompoundAssignmentOperators
//endregion CompoundAssignmentOperators

//region IncrementDecrementOperators
#pragma region IncrementDecrementOperators

// pre-increment
ExactArithmetic::Integer& ExactArithmetic::Integer::operator++() {
    auto digitIterator = digits->rbegin();
    bool incremented = false;

    while (!incremented) {
        if (*digitIterator < MAX_DIGIT)
        {
            *digitIterator += 1;
            incremented = true;
        }
        else
        {
            *digitIterator = 0;

            if (digitIterator == digits->rend()) {
                digits->push_front(1);
                incremented = true;
            }
        }

        ++digitIterator;
    }

    return *this;
}

// post-increment
ExactArithmetic::Integer ExactArithmetic::Integer::operator++(int) {
    auto copy = Integer(toString());
    operator++();
    return copy;
}

// pre-decrement
ExactArithmetic::Integer &ExactArithmetic::Integer::operator--() {
    auto digitIterator = digits->rbegin();
    bool decremented = false;

    if (digits->size() == 1 && *digitIterator == 0)
        return *this;

    while(!decremented) {
        if (*digitIterator > 0)
        {
            *digitIterator -= 1;
            decremented = true;
        }
        else
        {
            *digitIterator = MAX_DIGIT;

            if (digitIterator == digits->rend()) {
                digits->pop_front();
                decremented = true;
            }
        }

        ++digitIterator;
    }

    return *this;
}

// post-decrement
ExactArithmetic::Integer ExactArithmetic::Integer::operator--(int) {
    auto copy = Integer(toString());
    operator--();
    return copy;
}

#pragma endregion IncrementDecrementOperators
//endregion IncrementDecrementOperators

//region UtilityConversionFunctions
#pragma region UtilityConversionFunctions

std::string ExactArithmetic::Integer::toString() const {
    std::stringstream ss;

    ss << *this;

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

#pragma endregion UtilityConversionFunctions
//endregion UtilityConversionFunctions

//region FriendStreamOperators
#pragma region FriendStreamOperators

std::ostream& ExactArithmetic::operator<<(std::ostream& os, const ExactArithmetic::Integer& integer) {
    // since most significant bit is at the front, can just
    // iterate through the digits in order like so..

    for (Integer::Digit& d : *integer.digits) {
        os << d;
    }

    return os;
}

std::istream &ExactArithmetic::operator>>(std::istream& is, ExactArithmetic::Integer& integer) {
    // erases contents of existing integer and
    // overwrites with read-in digits.
    integer.digits->clear();

    char next;
    is >> next;

    while (!is.eof()) {
        short converted = next - ASCII_NUMBERS_START;

        if (converted < 0 || converted > 9) {
            std::string errorMessage = "Invalid argument constructing Integer, reached invalid character ";
            errorMessage.push_back(next);
            errorMessage.append(" in operator>>(std::istream&, Integer).");

            throw std::invalid_argument(errorMessage);
        }

        integer.digits->push_back(converted);

        is >> next;
    }

    return is;
}

#pragma region FriendStreamOperators
//endregion FriendStreamOperators

//region PrivateFunctions
#pragma region PrivateFunctions

ExactArithmetic::Integer::ComparisonResult ExactArithmetic::Integer::compare(const ExactArithmetic::Integer& other) const {
    auto mismatch = std::mismatch(
            digits->begin(), digits->end(),
            other.digits->begin(), other.digits->end(),
            [](Digit first, Digit second) {
                return first == second;
            }
    );

    // how far are each of these from the end / least significant digit?
    auto distanceFromEnd = std::distance(mismatch.first, digits->end());
    auto distanceFromEndOther = std::distance(mismatch.second, other.digits->end());

    // if of equal magnitude, i.e. equal distance from end of list
    // then just compare digits...
    if (distanceFromEnd == distanceFromEndOther) {
        auto thisDigit = *mismatch.first;
        auto otherDigit = *mismatch.second;

        if (thisDigit == otherDigit) {
            return EQ;
        }

        return thisDigit < otherDigit ?
            LT :
            GT;
    }

    // otherwise, find which is of larger magnitude;
    // if index is larger, it is a less significant
    // digit than the other.
    return distanceFromEnd < distanceFromEndOther ?
            LT :
            GT;
}

void ExactArithmetic::Integer::removeLeadingZeros() {
    while(!digits->empty() && digits->front() == 0) {
        digits->pop_front();
    }
}

void ExactArithmetic::Integer::intToDigits(unsigned long long i) {
    // iterates in orders of 10, extracting the current digit
    // with modulo and dividing; pushes to front so that the
    // array of digits has most significant digit at the front.
    digits->clear();

    while (i > 0) {
        auto nextDigit = i % 10;
        digits->push_front(nextDigit);

        i /= 10;
    }
}

std::pair<ExactArithmetic::Integer, ExactArithmetic::Integer> ExactArithmetic::Integer::divide(
        const ExactArithmetic::Integer& divider) {
    if (divider == 0) {
        throw ExactArithmetic::DivideByZeroError();
    }

    if (*this < divider) {
        return std::make_pair(0, *this);
    }

    int iterations = 0;
    while (*this > divider) {
        *this -= divider;
        iterations++;
    }

    return std::make_pair(iterations, *this);
}

#pragma endregion PrivateFunctions
//endregion PrivateFunctions
