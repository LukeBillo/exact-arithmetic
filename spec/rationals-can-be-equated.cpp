#include <catch2/catch.hpp>
#include "rational.h"
#include "helpers/RandomRationalGenerator.h"

using ExactArithmetic::Rational;
using SpecHelpers::RandomRationalGenerator;
using SpecHelpers::randomRational;

SCENARIO("Rationals can be equated", "[rational]") {
    Rational rational1 = GENERATE(take(20, randomRational(-10, 10)));

    GIVEN("Two equal rationals exist") {
        Rational rational2 = rational1;

        WHEN("Equating them using operator==") {
            bool firstEqualsSecond = rational1 == rational2;
            bool secondEqualsFirst = rational2 == rational1;

            THEN("True is returned") {
                REQUIRE(firstEqualsSecond);
                REQUIRE(secondEqualsFirst);
            }
        }
    }

    GIVEN("Two non-equal rationals exist") {
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