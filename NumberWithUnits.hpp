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
  NumberWithUnits(double number, const string &unit);
  static void read_units(ifstream &units_file); //*Reads from a text file.
  friend double
  convert(const NumberWithUnits &a,
          const NumberWithUnits &b); //*Convert from one unit to other in case
                                     // they are in the same field .
  //*Arithmetic operators overload.
  NumberWithUnits operator+(const NumberWithUnits &b);
  NumberWithUnits operator+();
  NumberWithUnits &operator+=(const NumberWithUnits &b);
  NumberWithUnits operator-(const NumberWithUnits &b);
  NumberWithUnits operator-();
  NumberWithUnits &operator-=(const NumberWithUnits &b);
  NumberWithUnits &operator++();
  NumberWithUnits operator++(int);
  NumberWithUnits &operator--();
  NumberWithUnits operator--(int);
  friend NumberWithUnits operator*(const NumberWithUnits &a, const double b);
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
bool isConnected(string &unit1, string &unit2, double cof);
void put(string &unit1, string &unit2, double cof);
bool contains(const string &unit);
bool contains(string &unit1, string &unit2);
void printMap();
} // namespace ariel
