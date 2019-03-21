#include <catch2/catch.hpp>
#include <sstream>
#include <dividebyzeroerror.h>
#include "rational.h"

using ExactArithmetic::Rational;
using ExactArithmetic::DivideByZeroError;

SCENARIO("Rationals can be constructed") {
    GIVEN("Rational has a default constructor") {
        WHEN("Constructing a default Rational") {
            Rational defaultRational = Rational();

            /*
             * Assumes that operator<< is
             * overloaded for Rational and that
             * this functions correctly.
             * Tested in rationals-can-be-output.
             */
            std::stringstream ss;
            ss << defaultRational;

            THEN("0/1 is constructed") {
                REQUIRE(defaultRational == Rational(0,1));
                REQUIRE(ss.str() == "0");
            }
        }
    }

    GIVEN("Rationals can be constructed with a given denominator and numerator") {
        WHEN("Constructing the rational 2/3") {
            Rational twoThirds = Rational(2, 3);

            std::stringstream ss;
            ss << twoThirds;

            THEN("2/3 is constructed") {
                REQUIRE(ss.str() == "2/3");
            }
        }

        WHEN("Constructing the rational 0/0") {
            THEN("An error is thrown") {
                REQUIRE_THROWS_AS(Rational(0, 0), DivideByZeroError);
            }
        }
    }
}