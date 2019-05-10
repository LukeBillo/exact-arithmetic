#include <catch2/catch.hpp>
#include "rational.h"
#include "../helpers/RandomRationalGenerator.h"
#include "dividebyzeroerror.h"

using ExactArithmetic::Rational;
using ExactArithmetic::DivideByZeroError;
using SpecHelpers::randomRational;

SCENARIO("Rationals can be subtracted", "[rational]") {
    GIVEN("Rational has operator- overloaded and two rationals exist") {
        Rational rational1 = GENERATE(take(20, randomRational(-100, 100)));
        Rational rational2 = GENERATE(take(20, randomRational(-100, 100)));

        WHEN("dividing rationals") {
            INFO("Subtracting rationals: " << rational1 << " - " << rational2)

            // Subtracting Rationals:
            // (a * d) - (b * d) / (b * d)

            long long int expectedNumerator =
                    (rational1.getNumerator() * rational2.getDenominator()) -
                    (rational1.getDenominator() * rational2.getNumerator());
            long long int expectedDenominator = rational1.getDenominator() * rational2.getDenominator();

            THEN("The rationals are divided as expected") {
                if (expectedDenominator == 0)
                {
                    REQUIRE_THROWS_AS((rational1 - rational2), DivideByZeroError);
                }
                else
                {
                    auto dividedRational = rational1 - rational2;
                    Rational expectedRational = Rational(expectedNumerator, expectedDenominator);

                    REQUIRE(expectedRational == dividedRational);
                }
            }
        }
    }
}
