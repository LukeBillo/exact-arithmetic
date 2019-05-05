#include <catch2/catch.hpp>
#include "rational.h"
#include "helpers/RandomRationalGenerator.h"

using ExactArithmetic::Rational;
using SpecHelpers::randomRational;

SCENARIO("Rationals can be multiplied", "[rational]") {
    GIVEN("Rational has operator* overloaded and two rationals exist") {
        Rational rational1 = GENERATE(take(20, randomRational(-100, 100)));
        Rational rational2 = GENERATE(take(20, randomRational(-100, 100)));

        WHEN("Multiplying rationals together") {
            INFO("Multiplying rationals: " << rational1 << " * " << rational2);
            Rational multipliedRational = rational1 * rational2;

            long long int expectedNumerator = rational1.getNumerator() * rational2.getNumerator();
            long long int expectedDenominator = rational1.getDenominator() * rational2.getDenominator();

            Rational expectedRational = Rational(expectedNumerator, expectedDenominator);

            THEN("The rationals are multiplied as expected") {
                REQUIRE(expectedRational == multipliedRational);
            }
        }
    }
}