#include <sstream>
#include "integer.h"

ExactArithmetic::Integer::Integer() {
    digits->push_front(0);
}

std::string ExactArithmetic::Integer::toString() const {
    std::stringstream ss;

    for (Digit& i : *digits) {
        ss << i;
    }

    return ss.str();
}

int ExactArithmetic::Integer::toInt() {
    auto stringified = toString();
    return std::stoi(stringified);
}