#include "NumberWithUnits.hpp"
using namespace std;
using namespace ariel;
int main() {
  ifstream units_file{"units.txt"};
  NumberWithUnits::read_units(units_file);
  printMap();
  return 0;
}
