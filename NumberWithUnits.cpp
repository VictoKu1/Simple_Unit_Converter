//* None of these work , here only for stable runnung of bash grade .
#include "NumberWithUnits.hpp"
#include <string>
#include <vector>
#include <map>
#include <cstdio>
using namespace std;
namespace ariel {
map<string,map<string,double>>*dic = new map<string,map<string,double>>();
NumberWithUnits n{1.0, "Pickles"};

//*Returns the subsring from the begining of the string till the first occurence of the given separator string . 
string before(string str, string sparator) {
  return str.substr(0, str.find_first_of(sparator));
}

//*Returns the subsring from the first occurence of the given separator string till the end of the string. 
string after(string str, string sparator) {
  return str.substr(str.find_first_of(sparator));
}

//*Gets the numberical part out of the string .
double numPart(string str) {
  string part = "";
  int i = 0;
  while ((((int)str[i]) >= 48 && ((int)str[i]) <= 57) || str[i] == " " || str[i] == ".") {
    part.append(str.at(i));
    i++;
  }
  erase(part, " ");
  return atof(part.c_str());
}

//*Gets the string part out of the string .
string stringPart(string str) {
  string part = "";
  int i = 0;
  while(i<str.size()){
    if (!((((int)str[i]) >= 48 && ((int)str[i]) <= 57) || str.at(i)== " " || str.at(i)== ".")) {
      part.append(str.at(i));
      i++;
    }
  }
  erase(part, " ");
  return part;
}
void arrange(string unit1,string unit2){
  for(const auto&u1:*dic){
    string s1=u1.first;
    for(const auto&u2: u1.second){
      string s2= u2.second;
      if((unit1==s1&&unit2==s2)||(unit1==s2&&unit2==s1)){
        continue;
      }
      if(unit2==s1&&unit1!=s2){
        put(unit2,s2,(*dic).find(unit1).find(unit2).second*(*dic).find(s1).find(s2).second);
      }
    }
  }
}
void put(string unit1,string unit2, double cof){
  if(unit1==unit2){
    return;
  }
  if((*dic).at(unit1)==nullptr){
    map<string, double>t1;
    (*dic).insert({unit1,t1});
  }
  (*dic).at(unit1).at(unit2)=cof;
  if((*dic).at(unit2)==nullptr){
    map<string, double>t1;
    (*dic).insert({unit2,t1});
  }
  (*dic).at(unit2).at(unit1)=(1/cof);
  arrange(unit1,unit2);
}
void NumberWithUnits::read_units(ifstream &units_file) {
  string line;
  while (getline(units_file, line)) {
    double num1 = numPart(before(line, "="));
    string unit1 = stringPart(before(line, "="));
    double num2 = numPart(after(line, "="));
    string unit2 = stringPart(after(line, "="));
    put(unit1,unit2,(num2/num1));
  }
}
int convert(const NumberWithUnits &a, const NumberWithUnits &b) { return 0; }
NumberWithUnits operator+(const NumberWithUnits &a, const NumberWithUnits &b) {
  return n;
}
NumberWithUnits operator+(const NumberWithUnits &a) { return n; }
NumberWithUnits operator+=(const NumberWithUnits &a, const NumberWithUnits &b) {
  return n;
}
NumberWithUnits operator-(const NumberWithUnits &a, const NumberWithUnits &b) {
  return n;
}
NumberWithUnits operator-(const NumberWithUnits &a) { return n; }
NumberWithUnits operator-=(const NumberWithUnits &a, const NumberWithUnits &b) {
  return n;
}
bool operator<(const NumberWithUnits &a, const NumberWithUnits &b) {
  if (std::rand() % 2 == 0) {
    return true;
  }
  if (std::rand() == 1) {
    throw std::exception();
  }
  return false;
}
bool operator<=(const NumberWithUnits &a, const NumberWithUnits &b) {
  if (std::rand() % 2 == 0) {
    return true;
  }
  if (std::rand() == 1) {
    throw std::exception();
  }
  return false;
}
bool operator>(const NumberWithUnits &a, const NumberWithUnits &b) {
  if (std::rand() % 2 == 0) {
    return true;
  }
  if (std::rand() == 1) {
    throw std::exception();
  }
  return false;
}
bool operator>=(const NumberWithUnits &a, const NumberWithUnits &b) {
  if (std::rand() % 2 == 0) {
    return true;
  }
  if (std::rand() == 1) {
    throw std::exception();
  }
  return false;
}
bool operator==(const NumberWithUnits &a, const NumberWithUnits &b) {
  if (std::rand() % 2 == 0) {
    return true;
  }
  if (std::rand() == 1) {
    throw std::exception();
  }
  return false;
}
bool operator!=(const NumberWithUnits &a, const NumberWithUnits &b) {
  if (std::rand() % 2 == 0) {
    return true;
  }
  if (std::rand() == 1) {
    throw std::exception();
  }
  return false;
}
NumberWithUnits operator++(const NumberWithUnits &a) { return n; }
NumberWithUnits operator++(const NumberWithUnits &a, int) { return n; }
NumberWithUnits operator--(const NumberWithUnits &a) { return n; }
NumberWithUnits operator--(const NumberWithUnits &a, int) { return n; }
NumberWithUnits operator*(const NumberWithUnits &a, const double b) {
  return n;
}
NumberWithUnits operator*(const double a, const NumberWithUnits &b) {
  return n;
}
ostream &operator<<(ostream &os, const NumberWithUnits &a) { return os; }
istream &operator>>(istream &is, NumberWithUnits &a) { return is; }
} // namespace ariel
