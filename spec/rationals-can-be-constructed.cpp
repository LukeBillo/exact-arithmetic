#include <catch2/catch.hpp>
#include <sstream>
#include <dividebyzeroerror.h>
#include "rational.h"

using ExactArithmetic::Rational;
using ExactArithmetic::DivideByZeroError;
using Catch::Generators::take;

struct TestRational {
    int numerator;
    int denominator;
    Rational expected;

    TestRational(int numerator, int denominator, Rational expected) : numerator(numerator),
                                                                    denominator(denominator),
                                                                    expected(expected) {}
};

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
            int numerator = GENERATE(take(10, random(1, 10)));
            int denominator = GENERATE(take(10, random(1, 10)));

            THEN("The rational is successfully constructed") {
                REQUIRE_NOTHROW(Rational(numerator, denominator));
            }
        }

        WHEN("Constructing rationals with a denominator of 0") {
            THEN("An error is thrown") {
                REQUIRE_THROWS_AS(Rational(0, 0), DivideByZeroError);
                REQUIRE_THROWS_AS(Rational(1, 0), DivideByZeroError);
                REQUIRE_THROWS_AS(Rational(-1, 0), DivideByZeroError);

            }
        }
    }

    GIVEN("Rationals can be constructed with std::string") {
        WHEN("Constructing a rational from a valid std::string") {
            auto convertFrom = GENERATE(as<std::string>{}, "2", "1", "0", "2/3", "1/5");

            Rational converted = Rational(convertFrom);

            std::stringstream ss;
            ss << converted;

            THEN("The correct rational is created") {
                REQUIRE(ss.str() == convertFrom);
            }
        }

        WHEN("Constructing a rational from an invalid std::string") {
            auto convertFrom = GENERATE(as<std::string>{}, "a/b", "1/a", "a/1", "a", "ff", "0xff");

            THEN("An exception is thrown") {
                REQUIRE_THROWS_AS(Rational(convertFrom), std::invalid_argument);
            }
        }
    }

    GIVEN("Rationals are normalised on construction") {
        TestRational testRational = GENERATE(
                TestRational(4, 6, Rational(2, 3)),
                TestRational(5, 10, Rational(1, 2)),
                TestRational(10, 10, Rational(1)),
                TestRational(-1, 1, Rational(-1)),
                TestRational(-1, -1, Rational(1)),
                TestRational(2, 1, Rational(2))
        );


        WHEN("The rational is constructed") {
            Rational constructed = Rational(testRational.numerator, testRational.denominator);

            THEN("The rational is normalised as expected") {
                REQUIRE(testRational.expected == constructed);
            }
        }
    }
}