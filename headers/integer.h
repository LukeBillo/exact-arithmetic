#ifndef INTEGER_H_161217
#define INTEGER_H_161217

#include <list>
#include <string>
#include <iostream>
#include <memory>

#define ASCII_NUMBERS_START 48
#define MAX_DIGIT 9

namespace ExactArithmetic
{
  /*  The Integer class provides integers of unbounded size.
   *
   *  Note that the declarations in this header file currently only support
   *  natural numbers; the class will need adapting to support negative integers.
   */
  class Integer
  {
    public:
      //  Default constructor, creates an Integer with value 0.
      Integer();

      //  Converting constructor.
      Integer(unsigned long long int);

      // Accepts a sequence of digits.
      // For any other input, throws a std::invalid_argument exception.
      // (For full integers, it should also allow an optional initial  '+' or '-' character.)
      explicit Integer(const std::string &);

      // Copy constructor
      Integer(const Integer&);

      //  Arithmetic Operators
      Integer operator+(const Integer &) const;
      Integer operator-(const Integer &) const;
      Integer operator*(const Integer &) const;
      Integer operator/(const Integer &) const; // Throws a DivideByZeroError for a 0 divisor.
      Integer operator%(const Integer &) const; // Throws a DivideByZeroError for a 0 divisor.

      // Comparison operators
      bool operator<(const Integer &) const;
      bool operator>(const Integer &) const;
      bool operator<=(const Integer &) const;
      bool operator>=(const Integer &) const;
      bool operator==(const Integer &) const;
      bool operator!=(const Integer &) const;

      // Compound Assignment operators
      Integer & operator+=(const Integer &);
      Integer & operator-=(const Integer &);
      Integer & operator*=(const Integer &);
      Integer & operator/=(const Integer &); // Throws a DivideByZeroError for a 0 divisor.
      Integer & operator%=(const Integer &); // Throws a DivideByZeroError for a 0 divisor.

      // Increment and Decrement operators
      Integer & operator++();  // pre-increment
      Integer operator++(int); // post-increment
      Integer & operator--();  // pre-decrement
      Integer operator--(int); // post-decrement

      // Utility methods for conversion
      std::string toString() const;
      int toInt();
      unsigned long long toInt64();

      // Friend declarations
      friend std::ostream & operator<<(std::ostream &, const Integer &);
      friend std::istream & operator>>(std::istream &, Integer &);

    private:
      using Digit = short int;
      using DigitList = std::list<Digit>;

      enum ComparisonResult {
          LT,
          EQ,
          GT
      };

      // Generic comparison function
      ComparisonResult compare(const Integer&) const;

      // Converts an integer and puts it into digits.
      void intToDigits(unsigned long long);

      // Removes leading zeros in the digits
      // e.g. 0001 -> 1
      void removeLeadingZeros();

      // Division that returns both quotient and remainder
      // returns std::pair<quotient, remainder>
      std::pair<Integer, Integer> divide(const Integer &);

      // The integer is represented as a list of digits.
      std::unique_ptr<DigitList> digits = std::make_unique<std::list<Digit>>();
  };

  std::ostream & operator<<(std::ostream &, const Integer &);
  std::istream & operator>>(std::istream &, Integer &);
}

#endif
