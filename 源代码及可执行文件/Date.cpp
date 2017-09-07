#include <iostream>
#include <string>
#include <cstring>
#include "Date.hpp"
using namespace std;

/*
  int m_year;
  int m_month;
  int m_day;
  int m_hour;
  int m_minute;
  */

Date::Date()
{
	m_year = 0;
	m_month = 0;
	m_day = 0;
	m_hour = 0;
	m_minute = 0;
}

Date::Date(int t_year, int t_month, int t_day, int t_hour, int t_minute)
{
	m_year = t_year;
	m_month = t_month;
	m_day = t_day;
	m_hour = t_hour;
	m_minute = t_minute;
}

Date::Date(const string &dateString)
{
	Date t_date = stringToDate(dateString);
	m_year = t_date.m_year;
	m_month = t_date.m_month;
	m_day = t_date.m_day;
	m_hour = t_date.m_hour;
	m_minute = t_date.m_minute;	

}

int Date::getYear(void) const
{
	return m_year;
}

void Date::setYear(const int t_year)
{
	m_year = t_year;
}

int Date::getMonth(void) const
{
	return m_month;
}

void Date::setMonth(const int t_month)
{
	m_month = t_month;
}

int Date::getDay(void) const
{
	return m_day;
}

void Date::setDay(const int t_day)
{
	m_day = t_day;
}

int Date::getHour(void) const
{
	return m_hour;
}

void Date::setHour(const int t_hour)
{
	m_hour = t_hour;
}

int Date::getMinute(void) const
{
	return m_minute;
}

void Date::setMinute(const int t_minute)
{
	m_minute = t_minute;
}

  /**
  *   @brief check whether the date is valid or not
  *   @return the bool indicate valid or not
  */
bool Date::isValid(const Date &t_date)
{
	bool isLeapYear = false;

	if (t_date.m_year > 9999 || t_date.m_year < 1000)
	{
		return false;
	}
	
	if (t_date.m_month > 12 || t_date.m_month < 1)
	{
		return false;
	}

	if ((t_date.m_year%400 == 0) 
		|| (t_date.m_year%4==0 && t_date.m_year%100!=0))
	{
		isLeapYear = true;
	}
	if (isLeapYear)
	{
		if (t_date.m_month == 1
			|| t_date.m_month == 3
			|| t_date.m_month == 5
			|| t_date.m_month == 7
			|| t_date.m_month == 8
			|| t_date.m_month == 10
			|| t_date.m_month == 12)
		{
			if (t_date.m_day > 31 || t_date.m_day < 1)
			{
				return false;
			}
		}
		else if (t_date.m_month == 4
				 || t_date.m_month == 6
				 || t_date.m_month == 9
				 || t_date.m_month == 11)
		{
			if (t_date.m_day > 30 || t_date.m_day < 1)
			{
				return false;
			}
		}
		else
		{
			if (t_date.m_day > 29 || t_date.m_day < 1)
			{
				return false;
			}
		}
	}
	else
	{
		if (t_date.m_month == 1
			|| t_date.m_month == 3
			|| t_date.m_month == 5
			|| t_date.m_month == 7
			|| t_date.m_month == 8
			|| t_date.m_month == 10
			|| t_date.m_month == 12)
		{
			if (t_date.m_day > 31 || t_date.m_day < 1)
			{
				return false;
			}
		}
		else if (t_date.m_month == 4
				 || t_date.m_month == 6
				 || t_date.m_month == 9
				 || t_date.m_month == 11)
		{
			if (t_date.m_day > 30 || t_date.m_day < 1)
			{
				return false;
			}
		}
		else
		{
			if (t_date.m_day > 28 || t_date.m_day < 1)
			{
				return false;
			}
		}
	}

	if (t_date.m_hour > 23 || t_date.m_hour < 0)
	{
		return false;
	}
	if (t_date.m_minute > 59 || t_date.m_minute < 0)
	{
		return false;
	}

	return true;
}

  /**
  * @brief convert a string to date, if the format is not correct return
  * 0000-00-00/00:00
  * @return a date
  */
Date Date::stringToDate(const string &t_dateString)
{
	Date res;
	auto be = t_dateString.begin();
	int mark = 0;//0-year 1-mon 2-day 3-hour 4-min
	int num = 0;
	bool isStrValid = true;
		
	if (t_dateString.size() != 16)
		return res;


	if ((*(be) > '9' || *(be) < '0')
		|| (*(be+1) > '9' || *(be+1) < '0')
		|| (*(be+2) > '9' || *(be+2) < '0')
		|| (*(be+3) > '9' || *(be+3) < '0')
		|| (*(be+5) > '9' || *(be+5) < '0')
		|| (*(be+6) > '9' || *(be+6) < '0')
		|| (*(be+8) > '9' || *(be+8) < '0')
		|| (*(be+9) > '9' || *(be+9) < '0')
		|| (*(be+11) > '9' || *(be+11) < '0')
		|| (*(be+12) > '9' || *(be+12) < '0')
		|| (*(be+14) > '9' || *(be+14) < '0')
		|| (*(be+15) > '9' || *(be+15) < '0')
		)
	{
		isStrValid = false;
	}
	else if ( *(be+4) != '-' 
			 || *(be+7) != '-'
			 || *(be+10) != '/'
			 || *(be+13) != ':'
 			 )
	{
		isStrValid = false;
	}


	if (isStrValid)
	{
		while (be != t_dateString.end())
		{
			if (*be == '-' || *be == '/' || *be == ':')
			{
				switch (mark)
				{
					case 0:
					{
						res.m_year = num;
	 					break;
					}
					case 1:
					{
						res.m_month = num;
						break;
					}
					case 2:
					{
						res.m_day = num;				
						break;
					}
					case 3:
					{
						res.m_hour = num;				
						break;
					}				
				}
				num = 0;
				++mark;
			}
			else
			{
				switch (mark)
				{
					case 0:
					{
						num *= 10;
						num += (*be - '0');
	 					break;
					}
					case 1:
					{
						num *= 10;
						num += (*be - '0');					
						break;
					}
					case 2:
					{
						num *= 10;
						num += (*be - '0');					
						break;
					}
					case 3:
					{
						num *= 10;
						num += (*be - '0');					
						break;
					}
					case 4:
					{
						num *= 10;
						num += (*be - '0');					
						break;
					}				
				}
			}
			res.m_minute = num;
			++be;
		}
	}
	Date temp;
	if (isValid(res))
		return res;
	else
		return temp;


	return res;
}

  /**
  * @brief convert a date to string, if the format is not correct return
  * 0000-00-00/00:00
  */
string Date::dateToString(const Date &t_date)
{
	if (isValid(t_date))
	{
		string res = "";
		string temp = "";
		int yea = t_date.m_year;
		int mon = t_date.m_month;
		int day= t_date.m_day;
		int hou = t_date.m_hour;
		int min = t_date.m_minute;


		res += ('0' + yea/1000); yea %= 1000;
		res += ('0' + yea/100); yea %= 100;
		res += ('0' + yea/10); yea %= 10;
		res += ('0' + yea);  


		res += "-";

		res += ('0' + mon/10);
		res += ('0' + mon%10); 
		res += "-";


		res += ('0' + day/10);
		res += ('0' + day%10);
		res += "/";

		res += ('0' + hou/10);
		res += ('0' + hou%10);
		res += ":";

		
		res += ('0' + min/10);
		res += ('0' + min%10);

		return res;
	}
	else
	{
		return "0000-00-00/00:00";
	}
}

  /**
  *  @brief overload the assign operator
  */
Date &Date::operator=(const Date &t_date)
{
	m_year = t_date.m_year;
	m_month = t_date.m_month;
	m_day = t_date.m_day;
	m_hour = t_date.m_hour;
	m_minute = t_date.m_minute;

	return *this;	
}

  /**
  * @brief check whether the CurrentDate is equal to the t_date
  */
bool Date::operator==(const Date &t_date) const
{
	if (m_year == t_date.m_year
		&& m_month == t_date.m_month
		&& m_day == t_date.m_day
		&& m_hour == t_date.m_hour
		&& m_minute == t_date.m_minute
		)
	{	
		return true;
	}
	else 
	{
		return false;
	}
}

  /**
  * @brief check whether the CurrentDate is  greater than the t_date
  */
bool Date::operator>(const Date &t_date) const
{
	if (m_year == t_date.m_year)
	{
		if (m_month == t_date.m_month)
		{
			if (m_day == t_date.m_day)
			{
				if (m_hour == t_date.m_hour)
				{
					if (m_minute > t_date.m_minute)
					{
						return true;
					}
					else
					{
						return false;
					}
				}
				else if (m_hour > t_date.m_hour)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			else if (m_day > t_date.m_day)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else if (m_month > t_date.m_month)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else if (m_year > t_date.m_year)
	{
		return true;
	}
	else
	{
		return false;
	}
}

  /**
  * @brief check whether the CurrentDate is  less than the t_date
  */
bool Date::operator<(const Date &t_date) const
{

	if (*this == t_date || *this > t_date)
		return false;
	else
		return true;
}

  /**
  * @brief check whether the CurrentDate is  greater or equal than the t_date
  */
bool Date::operator>=(const Date &t_date) const
{	
	if (*this < t_date)
		return false;
	else
		return true;
}

  /**
  * @brief check whether the CurrentDate is  less than or equal to the t_date
  */
bool Date::operator<=(const Date &t_date) const
{
	if (*this > t_date)
		return false;
	else
		return true;	
}