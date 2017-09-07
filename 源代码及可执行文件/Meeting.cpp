#include <iostream>
#include <vector>
#include "Meeting.hpp"
using namespace std;


/*
  std::string m_sponsor;
  std::vector<std::string> m_participators;
  Date m_startDate;
  Date m_endDate;
  std::string m_title;

*/



/**
  *   @brief constructor with argument
  */
Meeting::Meeting(const string &t_sponsor,
          const vector<string> &t_participator,
          const Date &t_startTime, const Date &t_endTime,
          const string &t_title)
{
	m_sponsor = t_sponsor;
	for (auto i : t_participator)
	{
		m_participators.push_back(i);
	}
	m_startDate = t_startTime;
	m_endDate = t_endTime;
	m_title = t_title;
}

  /**
  * @brief copy constructor of left value
  */
Meeting::Meeting(const Meeting &t_meeting)
{
	m_sponsor = t_meeting.m_sponsor;
	for (auto i : t_meeting.m_participators)
	{
		m_participators.push_back(i);
	}
	m_startDate = t_meeting.m_startDate;
	m_endDate = t_meeting.m_endDate;
	m_title = t_meeting.m_title;
}

  /**
  *   @brief get the meeting's sponsor
  *   @return a string indicate sponsor
  */
string Meeting::getSponsor(void) const
{
	return m_sponsor;
}

  /**
  * @brief set the sponsor of a meeting
  * @param  the new sponsor string
  */
void Meeting::setSponsor(const std::string &t_sponsor)
{
	m_sponsor = t_sponsor;
}

  /**
  * @brief  get the participators of a meeting
  * @return return a string vector indicate participators
  */
vector<string> Meeting::getParticipator(void) const
{
	return m_participators;
}

  /**
  *   @brief set the new participators of a meeting
  *   @param the new participators vector
  */
void Meeting::setParticipator(const vector<string> &t_participators)
{
	m_participators.clear();
	for (auto i : t_participators)
	{
		m_participators.push_back(i);
	}
}

  /**
  * @brief add a new participator to the meeting
  * @param the new participator
  */
void Meeting::addParticipator(const string &t_participator)
{
	m_participators.push_back(t_participator);
}

  /**
  * @brief remove a participator of the meeting
  * @param the participator to be removed
  */
void Meeting::removeParticipator(const string &t_participator)
{
	//auto be = m_participators.begin();
	for (auto be = m_participators.begin() ;be != m_participators.end(); ++be)
	{
		if (*be == t_participator)
		{
			m_participators.erase(be);
		}
	}
}

  /**
  * @brief get the startDate of a meeting
  * @return return a string indicate startDate
  */
Date Meeting::getStartDate(void) const
{
	return m_startDate;
}

  /**
  * @brief  set the startDate of a meeting
  * @param  the new startdate of a meeting
  */
void Meeting::setStartDate(const Date &t_startTime)
{
	m_startDate = t_startTime;
}

  /**
  * @brief get the endDate of a meeting
  * @return a date indicate the endDate
  */
Date Meeting::getEndDate(void) const
{
	return m_endDate;
}

  /**
  * @brief  set the endDate of a meeting
  * @param  the new enddate of a meeting
  */
void Meeting::setEndDate(const Date &t_endTime)
{
	m_endDate = t_endTime;
}

  /**
  * @brief get the title of a meeting
  * @return a date title the endDate
  */
string Meeting::getTitle(void) const
{
	return m_title;
}

  /**
  * @brief  set the title of a meeting
  * @param  the new title of a meeting
  */
void Meeting::setTitle(const std::string &t_title)
{
	m_title = t_title;
}

  /**
  * @brief check if the user take part in this meeting
  * @param t_username the source username
  * @return if the user take part in this meeting
  */
bool Meeting::isParticipator(const string &t_username) const
{
  if (m_sponsor == t_username)
    return true;

	for (auto i : m_participators)
	{
		if (i == t_username)
		{
			return true;
		}
	}	
	return false;
}