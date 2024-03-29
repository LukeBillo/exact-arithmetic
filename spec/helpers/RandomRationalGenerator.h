#ifndef EXACT_ARITHMETIC_RANDOMRATIONALGENERATOR_H
#define EXACT_ARITHMETIC_RANDOMRATIONALGENERATOR_H

#include <catch2/catch.hpp>
#include <rational.h>

using ExactArithmetic::Rational;
using Catch::Generators::IGenerator;
using Catch::Generators::GeneratorWrapper;

namespace SpecHelpers {
    class RandomRationalGenerator : public IGenerator<Rational> {
    public:
        RandomRationalGenerator(int lowest, int highest) :
                generator(std::random_device{}()),
                distribution(lowest, highest)
        {
            static_cast<void>(next());
        }

        Rational const& get() const override;
        bool next() override;

    private:
        // Random number generator
        std::minstd_rand generator;
        std::uniform_int_distribution<> distribution;

        Rational current_rational;
    };

    GeneratorWrapper<Rational> randomRational(int low, int high);
}

#endif
