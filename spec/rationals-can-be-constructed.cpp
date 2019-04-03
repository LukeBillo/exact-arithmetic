#include <catch2/catch.hpp>
#include <sstream>
#include <dividebyzeroerror.h>
#include "rational.h"

using ExactArithmetic::Rational;
using ExactArithmetic::DivideByZeroError;
using Catch::Generators::take;

SCENARIO("Rationals can be constructed", "[rational]") {
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
        WHEN("Constructing the rational") {
            int numerator = GENERATE(take(10, random(-10, 10)));
            int denominator = GENERATE(take(10, random(-10, 10)));

            Rational constructedRational = Rational(numerator, denominator);

            std::stringstream constructed;
            constructed << constructedRational;

            std::stringstream expected;
            expected << numerator << "/" << denominator;

            THEN("The correct rational is constructed") {
                REQUIRE(constructed.str() == expected.str());
            }
        }

        WHEN("Constructing rationals with a denominator of 0") {
            THEN("An error is thrown") {
                REQUIRE_THROWS_AS(Rational(0, 0), DivideByZeroError);
            }
        }
    }

    GIVEN("Rationals can be constructed with std::string") {
        auto convertFrom = GENERATE(as<std::string>{}, "2", "1", "0", "2/3", "1/5");

        WHEN("Constructing the rational from the std::string") {
            Rational twoThirds = Rational(convertFrom);

            std::stringstream ss;
            ss << twoThirds;

            THEN("The correct rational is created") {
                REQUIRE(ss.str() == convertFrom);
            }
        }
    }
}