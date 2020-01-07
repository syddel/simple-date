#ifndef SIMPLEDATE_H
#define SIMPLEDATE_H

#include <string>
#include <ctime>
#include <vector>

typedef unsigned short usi;

#define YEAR    0
#define MONTH   1
#define DAY     2

class SimpleDate
{
  private:

    std::tm tm = {};

    bool isLeapYear(unsigned int year);
    bool isValidDate(const std::string &date);
    void initFromString(const std::string &date);
    std::vector<std::string> tokenizeDate(const std::string &date) const;
    std::string formatDateString(const std::string &date) const;

  public:

    SimpleDate();
    SimpleDate(const char *date);
    ~SimpleDate();

    friend std::ostream& operator<<(std::ostream &os, const SimpleDate &dh);
    void operator=(const char *date_str);
    friend bool operator==(const SimpleDate &lhs, const SimpleDate &rhs);
    friend bool operator<(const SimpleDate &lhs, const SimpleDate &rhs);
    friend bool operator>(const SimpleDate &lhs, const SimpleDate &rhs);
    friend bool operator<=(const SimpleDate &lhs, const SimpleDate &rhs);
    friend bool operator>=(const SimpleDate &lhs, const SimpleDate &rhs);

    friend bool operator<(const SimpleDate &lhs, const char *date_str);
    friend bool operator>(const SimpleDate &lhs, const char *date_str);
    friend bool operator<=(const SimpleDate &lhs, const char *date_str);
    friend bool operator>=(const SimpleDate &lhs, const char *date_str);

    friend bool operator==(const SimpleDate &lhs, const char *date_str);

    SimpleDate operator++(int);
    SimpleDate operator--(int);
    SimpleDate& operator+=(const std::string &a);
    SimpleDate& operator-=(const std::string &a);
    friend SimpleDate operator+(SimpleDate lhs, const std::string &rhs);
    friend SimpleDate operator-(SimpleDate lhs, const char *rhs);
    friend int operator-(SimpleDate &lhs, SimpleDate &rhs);

    void set(std::string date);
    std::string get() const;
    void clear();
    std::time_t toTimeType();
};

#endif
