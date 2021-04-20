#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
using namespace std;
namespace ariel {
class NumberWithUnits {
private:
  double number; //*Represents the digit part of the number.
  string unit;   //*Represents the unit specification part of the number .
public:
  NumberWithUnits(double number, string unit) {
    (*this).number = number;
    (*this).unit = unit;
  }
  static void read_units(ifstream &units_file); //*Reads from a text file.
  friend int
  convert(const NumberWithUnits &a,
          const NumberWithUnits &b); //*Convert from one unit to other in case
                                     //they are in the same field .
  //*Arithmetic operators overload.
  friend NumberWithUnits operator+(const NumberWithUnits &a,
                                   const NumberWithUnits &b);
  friend NumberWithUnits operator+(const NumberWithUnits &a);
  friend NumberWithUnits operator+=(const NumberWithUnits &a,
                                    const NumberWithUnits &b);
  friend NumberWithUnits operator-(const NumberWithUnits &a,
                                   const NumberWithUnits &b);
  friend NumberWithUnits operator-(const NumberWithUnits &a);
  friend NumberWithUnits operator-=(const NumberWithUnits &a,
                                    const NumberWithUnits &b);
  friend NumberWithUnits operator++(const NumberWithUnits &a);
  friend NumberWithUnits operator++(const NumberWithUnits &a, int);
  friend NumberWithUnits operator--(const NumberWithUnits &a);
  friend NumberWithUnits operator--(const NumberWithUnits &a, int);
  friend NumberWithUnits operator*(const NumberWithUnits &a, const double b);
  friend NumberWithUnits operator*(const double a, const NumberWithUnits &b);
  friend NumberWithUnits operator*(const double a, const NumberWithUnits &b);
  //*Logical operators overload.
  friend bool operator<(const NumberWithUnits &a, const NumberWithUnits &b);
  friend bool operator<=(const NumberWithUnits &a, const NumberWithUnits &b);
  friend bool operator>(const NumberWithUnits &a, const NumberWithUnits &b);
  friend bool operator>=(const NumberWithUnits &a, const NumberWithUnits &b);
  friend bool operator==(const NumberWithUnits &a, const NumberWithUnits &b);
  friend bool operator!=(const NumberWithUnits &a, const NumberWithUnits &b);
  //*Printing operators overload.
  friend ostream &operator<<(ostream &os, const NumberWithUnits &a);
  friend istream &operator>>(istream &is, NumberWithUnits &a);
};
} // namespace ariel