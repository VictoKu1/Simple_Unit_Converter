#include "NumberWithUnits.hpp"
#include "doctest.h"
using namespace std;
using namespace ariel;
ifstream units_file{"units.txt"};
TEST_CASE("Testing correct addition.") {
  NumberWithUnits::read_units(units_file);
  NumberWithUnits cm1{1, "cm"};
  NumberWithUnits cm2{2, "cm"};
  NumberWithUnits cm5{5, "cm"};
  NumberWithUnits m1{1, "m"};
  NumberWithUnits mpcm1{1.01, "m"};
  NumberWithUnits cmpm1{101, "cm"};
  NumberWithUnits wrong{159, "cm"};
  cm1++;
  CHECK(cm1 == cm2);
  cm1--;
  cm1 += cm2 * 2;
  CHECK(cm1 == cm5);
  cm1 -= cm2 * 2;
  CHECK((m1 + cm1) == mpcm1);
  CHECK((cm1 + m1) == cmpm1);
  CHECK((cm1 + m1) != wrong);
}
TEST_CASE("Testing incorrect addition.") {
  NumberWithUnits::read_units(units_file);
  NumberWithUnits min1{1, "min"};
  NumberWithUnits m1{1, "m"};
  CHECK_THROWS(m1 + min1);
  CHECK_THROWS(min1 + m1);
}
TEST_CASE("Testing correct subtraction.") {
  NumberWithUnits::read_units(units_file);
  NumberWithUnits cm1{1, "cm"};
  NumberWithUnits cm0{0, "cm"};
  NumberWithUnits m1{1, "m"};
  NumberWithUnits mmcm1{0.99, "m"};
  NumberWithUnits cmmm1{-99, "cm"};
  NumberWithUnits wrong{159, "cm"};
  cm1--;
  CHECK(cm1 == cm0);
  cm1++;
  cm1 -= m1;
  CHECK(cm1 == cmmm1);
  cm1 += m1;
  CHECK((m1 - cm1) == mmcm1);
  CHECK((cm1 - m1) == cmmm1);
  CHECK((cm1 - m1) != wrong);
}
TEST_CASE("Testing incorrect subtraction.") {
  NumberWithUnits::read_units(units_file);
  NumberWithUnits min1{1, "min"};
  NumberWithUnits m1{1, "m"};
  CHECK_THROWS(m1 - min1);
  CHECK_THROWS(min1 - m1);
}
TEST_CASE("Testing correct multiplication.") {
  NumberWithUnits::read_units(units_file);
  NumberWithUnits m5{5, "m"};
  NumberWithUnits m45{45, "m"};
  NumberWithUnits m0{0, "m"};
  CHECK((9 * m5) == m45);
  CHECK((1 * m5) == m5);
  CHECK((0 * m5) == m0);
  CHECK((m5 * 9) == m45);
  CHECK((m5 * 1) == m5);
  CHECK((m5 * 0) == m0);
  CHECK((m5 * 179) != m45);
}
TEST_CASE("Testing inequality signs.") {
  NumberWithUnits::read_units(units_file);
  NumberWithUnits m5{5, "m"};
  NumberWithUnits m45{45, "m"};
  NumberWithUnits ils5{5, "ILS"};
  CHECK(m5 < m45);
  CHECK(m5 <= m45);
  CHECK_FALSE(m5 < m5);
  CHECK(m5 <= m5);
  CHECK(m5 == m5);
  CHECK(m45 != m5);
  CHECK(m5 != m45);
  CHECK(m45 > m5);
  CHECK(m45 >= m5);
}
