#include "../headers/SimpleDate.h"

#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstring>
#include <string>
#include <vector>


// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
SimpleDate::SimpleDate()
{
  this->clear();
  this->initFromString("0000-01-01");
}

// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
SimpleDate::SimpleDate(const char *date)
{
  this->clear();
  this->initFromString(date);
}

// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
SimpleDate::~SimpleDate()
{
  this->clear();
}

// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
void SimpleDate::set(std::string date)
{
  this->initFromString(date);
}

// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
std::string SimpleDate::formatDateString(const std::string &date) const
{
  std::vector<std::string> dateToken = tokenizeDate(date);

  std::string year = dateToken[YEAR].length() < 4 ?
    std::string(4 - dateToken[YEAR].length(), '0') + dateToken[YEAR] : dateToken[YEAR];
  std::string month = std::string(2 - dateToken[MONTH].length(), '0') + dateToken[MONTH];
  std::string day = std::string(2 - dateToken[DAY].length(), '0') + dateToken[DAY];

  return year + "-" + month + "-" + day;
}

// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
std::string SimpleDate::get() const
{
  std::ostringstream oss;
  oss << std::put_time(&tm, "%F");

  return formatDateString(oss.str());
}

// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
std::vector<std::string> SimpleDate::tokenizeDate(const std::string &date) const
{
  std::vector<std::string> dateTokens;
  std::string temp = "";
  std::stringstream dateStream(date);

  while(std::getline(dateStream, temp, '-'))
    dateTokens.push_back(temp);

  return dateTokens;
}

// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
bool SimpleDate::isLeapYear(unsigned int year)
{
  return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
bool SimpleDate::isValidDate(const std::string &date)
{
  usi daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  std::vector<std::string> dateToken = tokenizeDate(date);

  usi iYear = std::stoi(dateToken[YEAR]);
  usi iMonth = std::stoi(dateToken[MONTH]);
  usi iDay = std::stoi(dateToken[DAY]);

  if (dateToken[MONTH].length() != 2 || dateToken[DAY].length() != 2)
    return false;

  if (dateToken.size() != 3) return false;
  if (iMonth <= 0 || iMonth > 12) return false;
  if (isLeapYear(iYear)) daysInMonth[1]++;
  if (iDay <= 0 || iDay > daysInMonth[iMonth - 1]) return false;

  return true;
}

// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
void SimpleDate::initFromString(const std::string &date)
{
  std::string d = formatDateString(date);
  std::istringstream(d) >> std::get_time(&tm, "%Y-%m-%d");

  if (!isValidDate(d))
	  throw std::invalid_argument("INVALID DATE: " + date);
}

// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
void SimpleDate::clear()
{
  std::memset(&tm, 0, sizeof(std::tm));
}

// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
std::time_t SimpleDate::toTimeType()
{
  return std::mktime(&tm);
}

// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
std::ostream& operator<<(std::ostream &os, const SimpleDate &dh)
{
  os << dh.get();
  return os;
}

// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
void SimpleDate::operator=(const char *date_str)
{
  initFromString(date_str);
}

// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
bool operator==(const SimpleDate &lhs, const SimpleDate &rhs)
{
  return
      std::mktime(const_cast<std::tm*>(&(lhs.tm))) ==
        std::mktime(const_cast<std::tm*>(&(rhs.tm)));
}

// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
bool operator<(const SimpleDate &lhs, const SimpleDate &rhs)
{
  return
      std::mktime(const_cast<std::tm*>(&(lhs.tm))) <
        std::mktime(const_cast<std::tm*>(&(rhs.tm)));
}

// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
bool operator>(const SimpleDate &lhs, const SimpleDate &rhs)
{
  return
      std::mktime(const_cast<std::tm*>(&(lhs.tm))) >
        std::mktime(const_cast<std::tm*>(&(rhs.tm)));
}

// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
bool operator<=(const SimpleDate &lhs, const SimpleDate &rhs)
{
  return
      std::mktime(const_cast<std::tm*>(&(lhs.tm))) <=
        std::mktime(const_cast<std::tm*>(&(rhs.tm)));
}

// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
bool operator>=(const SimpleDate &lhs, const SimpleDate &rhs)
{
  return
      std::mktime(const_cast<std::tm*>(&(lhs.tm))) >=
        std::mktime(const_cast<std::tm*>(&(rhs.tm)));
}

// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
bool operator<(const SimpleDate &lhs, const char *date_str)
{
  return lhs < SimpleDate(date_str);
}

// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
bool operator>(const SimpleDate &lhs, const char *date_str)
{
  return lhs > SimpleDate(date_str);
}

// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
bool operator<=(const SimpleDate &lhs, const char *date_str)
{
  return lhs <= SimpleDate(date_str);
}

// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
bool operator>=(const SimpleDate &lhs, const char *date_str)
{
  return lhs >= SimpleDate(date_str);
}

// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
bool operator==(const SimpleDate &lhs, const char *date_str)
{
  return lhs == SimpleDate(date_str);
}

// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
SimpleDate SimpleDate::operator++(int)
{
  SimpleDate tmp = *this;
  this->tm.tm_mday++;
  std::mktime(&(this->tm));

  return tmp;
}

// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
SimpleDate SimpleDate::operator--(int)
{
  SimpleDate tmp = *this;
  this->tm.tm_mday--;
  std::mktime(&(this->tm));

  return tmp;
}

// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
SimpleDate& SimpleDate::operator+=(const std::string &a)
{
  std::string type = a.substr(a.length() - 1);
  type = std::toupper(type[0]);

  int x = std::stoi(a);

  if (type == "D") this->tm.tm_mday += x;
  else if (type == "M") this->tm.tm_mon += x;
  else if (type == "Y") this->tm.tm_year += x;

  std::mktime(&(this->tm));

  return *this;
}

// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
SimpleDate& SimpleDate::operator-=(const std::string &a)
{
  std::string type = a.substr(a.length() - 1);
  type = std::toupper(type[0]);

  int x = std::stoi(a);

  if (type == "D") this->tm.tm_mday -= x;
  else if (type == "M") this->tm.tm_mon -= x;
  else if (type == "Y") this->tm.tm_year -= x;

  std::mktime(&(this->tm));

  return *this;
}

// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
SimpleDate operator+(SimpleDate lhs, const std::string &rhs)
{
  lhs += rhs;
  return lhs;
}

// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
SimpleDate operator-(SimpleDate lhs, const char *rhs)
{
  lhs -= rhs;
  return lhs;
}

// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
int operator-(SimpleDate &lhs, SimpleDate &rhs)
{
  return (lhs.toTimeType() - rhs.toTimeType()) / 60 / 60 / 24;
}



