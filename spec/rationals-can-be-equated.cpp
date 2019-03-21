#include <catch2/catch.hpp>
#include "rational.h"

using ExactArithmetic::Rational;

SCENARIO("Rationals can be equated", "[rational]") {
    GIVEN("Two equal rationals exist") {
        Rational rational1 = Rational(2, 3);
        Rational rational2 = Rational(2, 3);

        WHEN("Equating them using operator==") {
            bool firstEqualsSecond = rational1 == rational2;
            bool secondEqualsFirst = rational2 == rational1;

            THEN("True is returned") {
                REQUIRE(firstEqualsSecond);
                REQUIRE(secondEqualsFirst);
            }
        }
    }

    GIVEN("Two inequal rationals exist") {
        Rational rational1 = Rational(2, 3);
        Rational rational2 = Rational(1, 5);

        WHEN("Equating them using operator==") {
            bool firstEqualsSecond = rational1 == rational2;
            bool secondEqualsFirst = rational2 == rational1;

            THEN("False is returned") {
                REQUIRE(!firstEqualsSecond);
                REQUIRE(!secondEqualsFirst);
            }
        }
    }
}