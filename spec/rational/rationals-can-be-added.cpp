#include <catch2/catch.hpp>
#include "rational.h"
#include "../helpers/RandomRationalGenerator.h"

using ExactArithmetic::Rational;
using SpecHelpers::randomRational;

SCENARIO("Rationals can be added", "[rational]") {
    GIVEN("Rational has operator+ overloaded and two rationals exist") {
        Rational rational1 = GENERATE(take(20, randomRational(-100, 100)));
        Rational rational2 = GENERATE(take(20, randomRational(-100, 100)));


        WHEN("Adding rationals together") {
            INFO("Added rationals: " << rational1 << " + " << rational2)
            Rational addedRational = rational1 + rational2;

            // Adding rationals:
            // (a * d) + (b * c) / (b * d)
            long long int expectedNumerator =
                    rational1.getNumerator() * rational2.getDenominator() +
                    rational1.getDenominator() * rational2.getNumerator();
            long long int expectedDenominator = rational1.getDenominator() * rational2.getDenominator();

            Rational expectedRational = Rational(expectedNumerator, expectedDenominator);

            THEN("The rationals are added as expected") {
                REQUIRE(expectedRational == addedRational);
            }
        }
    }
}