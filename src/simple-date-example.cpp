#include <SimpleDate.h>
#include <iostream>
#include <ctime>
#include <sstream>
#include <iomanip>


int main()
{
  SimpleDate minDate = "0000-01-01";
  SimpleDate maxDate = "9999-12-31";
  std::cout << "Min date: " << minDate << ", Max date: " << maxDate << std::endl;
  std::cout << "maxDate - minDate (days between min/max): " << maxDate - minDate << std::endl;

  std::cout << "\nfor (SimpleDate d = \"2020-02-27\"; d < \"2020-03-04\"; d++):\n" << std::endl;
  for (SimpleDate d = "2020-02-27"; d < "2020-03-04"; d++)
    std::cout << "   " << d << std::endl;

  SimpleDate d1 = "2020-01-01";
  std::cout << "\nSimpleDate d1 = " << d1 << std::endl;
  d1 += "5y";
  std::cout << "d1 += \"5y\":     " << d1 << std::endl;
  d1 += "18m";
  std::cout << "d1 += \"18m\":    " << d1 << std::endl;
  d1 += "3d";
  std::cout << "d1 += \"3d\":     " << d1 << std::endl;
  d1 -= "6y";
  std::cout << "d1 -= \"5y\":     " << d1 << std::endl;
  d1++;
  std::cout << "d1++:           " << d1 << std::endl;

  return 0;
}
