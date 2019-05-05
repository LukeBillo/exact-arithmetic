#include <memory>
#include "RandomRationalGenerator.h"

Rational const &SpecHelpers::RandomRationalGenerator::get() const {
    return current_rational;
}

bool SpecHelpers::RandomRationalGenerator::next() {
    int numerator = distribution(generator);
    int denominator = distribution(generator);

    while (denominator == 0) {
        denominator = distribution(generator);
    }

    current_rational = Rational(numerator, denominator);
    return true;
}


GeneratorWrapper<Rational> SpecHelpers::randomRational(int low, int high) {
    return GeneratorWrapper<Rational>(
            std::unique_ptr<IGenerator<Rational>>(new RandomRationalGenerator(low, high))
    );
}
