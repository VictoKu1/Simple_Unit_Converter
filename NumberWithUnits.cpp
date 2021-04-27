//* None of these work , here only for stable runnung of bash grade .
#include "NumberWithUnits.hpp"
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>
using namespace std;
namespace ariel {
static map<string, map<string, double>> dic;
bool contains(const string &unit) { return (dic.count(unit) > 0); }

bool contains(string &unit1, string &unit2) {
  if (dic.find(unit1) != dic.end()) {
    return dic[unit1].find(unit2) != dic[unit1].end();
  }
  return false;
}
NumberWithUnits::NumberWithUnits(double number, const string &unit) {
  if (!contains(unit)) {
    throw invalid_argument{"Wrong unit ."};
  }
  (*this).number = number;
  (*this).unit = unit;
}

//*Returns the subsring from the begining of the string till the first occurence
// of the given separator string .
string before(string &str, string &sparator) {
  return str.substr(0, str.find_first_of(sparator));
}

//*Returns the subsring from the first occurence of the given separator string
// till the end of the string.
string after(string &str, string &sparator) {
  return str.substr(str.find_first_of(sparator));
}

//*Gets the numberical part out of the string .
double numPart(string str) {
  string part;
  int i = 0;
  char charAt = str.at(0);
  const int ZERO_ASCII_CODE = 48;
  const int NINE_ASCII_CODE = 57;
  while ((charAt >= ZERO_ASCII_CODE && charAt <= NINE_ASCII_CODE) ||
         charAt == ' ' || charAt == '.') {
    part.push_back(charAt);
    i++;
    charAt = str.at((unsigned long)i);
  }
  part.erase(remove(part.begin(), part.end(), ' '), part.end());
  return atof(part.c_str());
}

//*Gets the string part out of the string .
string stringPart(string str) {
  string part;
  int i = 0;
  char charAt = str.at(0);
  const int A_ASCII_CODE = 65;
  const int Z_ASCII_CODE = 90;
  const int CAPITAL_A_ASCII_CODE = 97;
  const int CAPITAL_Z_ASCII_CODE = 122;
  while ((charAt >= A_ASCII_CODE && charAt <= Z_ASCII_CODE) ||
         (charAt >= CAPITAL_A_ASCII_CODE && charAt <= CAPITAL_A_ASCII_CODE) ||
         charAt == ' ' || charAt == '.') {
    part.push_back(charAt);
    i++;

    charAt = str.at((unsigned long)i);
  }
  part.erase(remove(part.begin(), part.end(), ' '), part.end());
  return part;
}

bool isConnected(string &unit1, string &unit2, double cof) {
  return (contains(unit1, unit2));
}

void put(string &unit1, string &unit2, double cof) {
  if (unit1 == unit2) {
    return;
  }
  if (isConnected(unit1, unit2, cof)) {
    return;
  }

  if (cof != 0) {
    dic[unit1][unit2] = cof;
    dic[unit2][unit1] = (1 / cof);
    for (auto &u1 : dic[unit2]) {
      string su1 = u1.first;
      //*if (!isConnected(unit1, su1, cof * u1.second)) {
      put(unit1, su1, cof * u1.second);
      //*}
    }
    for (auto &u2 : dic[unit1]) {
      string su2 = u2.first;
      //*if (!isConnected(unit1, su2, (1 / cof) * u2.second)) {
      put(unit2, su2, (1 / cof) * u2.second);
      //*}
    }
  } else {
    dic[unit1][unit2] = 0;
    dic[unit2][unit1] = 0;
    for (auto &u1 : dic[unit2]) {
      string su1 = u1.first;
      //*if (!isConnected(unit1, su1, cof * u1.second)) {
      put(unit1, su1, 0);
      //*}
    }
    for (auto &u2 : dic[unit1]) {
      string su2 = u2.first;
      //*if (!isConnected(unit1, su2, (1 / cof) * u2.second)) {
      put(unit2, su2, 0);
      //*}
    }
  }
}

void NumberWithUnits::read_units(ifstream &units_file) {
  string mid;
  double num1;
  string unit1;
  double num2;
  string unit2;
  while (units_file >> num1 >> unit1 >> mid >> num2 >> unit2) {
    // string equals = "=";
    // string bef = before(line, equals);
    // double num1 = numPart(bef);
    // string unit1 = stringPart(bef);
    // string afr = after(line, equals);
    // double num2 = numPart(afr);
    // string unit2 = stringPart(afr);
    if (num1 != 0) {
      put(unit1, unit2, (num2 / num1));
    } else {
      put(unit1, unit2, 0);
    }
  }
}

double convert(const NumberWithUnits &a, const NumberWithUnits &b) {
  string au = a.unit;
  string bu = b.unit;
  if (au == bu) {
    return a.number;
  }
  if (!contains(au, bu)) {
    throw invalid_argument{"Units do not match - [" + au +
                           "] cannot be converted to [" + bu + "]"};
  }

  return b.number * dic[bu][au];
}

NumberWithUnits NumberWithUnits::operator+(const NumberWithUnits &b) {
  double cof = convert((*this), b);
  NumberWithUnits answer((*this).number + cof, (*this).unit);
  return answer;
}
NumberWithUnits NumberWithUnits::operator+() {
  NumberWithUnits answer(+(*this).number, (*this).unit);
  return answer;
}
NumberWithUnits &NumberWithUnits::operator+=(const NumberWithUnits &b) {
  double cof = convert((*this), b);
  (*this).number += cof;
  return (*this);
}
NumberWithUnits NumberWithUnits::operator-(const NumberWithUnits &b) {
  double cof = convert((*this), b);
  NumberWithUnits answer((*this).number - cof, (*this).unit);
  return answer;
}
NumberWithUnits NumberWithUnits::operator-() {
  NumberWithUnits answer(-(*this).number, (*this).unit);
  return answer;
}
NumberWithUnits &NumberWithUnits::operator-=(const NumberWithUnits &b) {
  double cof = convert((*this), b);
  (*this).number -= cof;
  return (*this);
}
NumberWithUnits &NumberWithUnits::operator++() {
  ++(*this).number;
  return (*this);
}
NumberWithUnits NumberWithUnits::operator++(int) {
  return NumberWithUnits((*this).number++, (*this).unit);
}
NumberWithUnits &NumberWithUnits::operator--() {
  --(*this).number;
  return (*this);
}
NumberWithUnits NumberWithUnits::operator--(int) {
  NumberWithUnits answer((*this).number--, (*this).unit);
  return answer;
}
NumberWithUnits operator*(const NumberWithUnits &a, const double b) {
  NumberWithUnits answer(a.number * b, a.unit);
  return answer;
}
NumberWithUnits operator*(const double a, const NumberWithUnits &b) {
  NumberWithUnits answer(b.number * a, b.unit);
  return answer;
}
bool operator<(const NumberWithUnits &a, const NumberWithUnits &b) {
  double value = convert(a, b);
  return a.number < value;
}
bool operator<=(const NumberWithUnits &a, const NumberWithUnits &b) {
  return a < b || a == b;
}

bool operator>(const NumberWithUnits &a, const NumberWithUnits &b) {
  double value = convert(a, b);
  return a.number > value;
}
bool operator>=(const NumberWithUnits &a, const NumberWithUnits &b) {
  return a > b || a == b;
}
const double TOLERANCE = 0.001;
bool operator==(const NumberWithUnits &a, const NumberWithUnits &b) {
  double value = convert(a, b);
  return (abs(a.number - value)) <= TOLERANCE;
}
bool operator!=(const NumberWithUnits &a, const NumberWithUnits &b) {
  return (!(a == b));
}
ostream &operator<<(ostream &os, const NumberWithUnits &a) {
  return os << a.number << "[" << a.unit << "]";
}
istream &operator>>(istream &is, NumberWithUnits &a) {
  string miscellaneous;
  is >> a.number >> miscellaneous >> a.unit;
  return is;
}
void printMap() {
  for (auto &u1 : dic) {
    for (auto &u2 : u1.second) {
      cout << "1 " << u1.first << "=" << u2.second << " " << u2.first << "."
           << endl;
    }
  }
}
} // namespace ariel
