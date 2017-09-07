#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include "Storage.hpp"
#include "Path.hpp"
using namespace std;


shared_ptr<Storage> Storage::m_instance = nullptr;

/*
  static std::shared_ptr<Storage> m_instance;
  std::list<User> m_userList;
  std::list<Meeting> m_meetingList;
  bool m_dirty;
*/
void encode(string &buff){
    for (auto p = buff.begin(); p != buff.end(); ++p) {
        *p=255-*p;
    }
}

void deleteQuo(string& temp)
{
	string res = "";
	auto be = temp.begin();
	for (; be != temp.end(); ++be)
	{
		if (*be != '\"')
		{
			res.push_back(*be);
		}
	}
	temp = res;
}	

Storage::Storage()
{ 
	readFromFile();
	m_dirty = 0;
}

bool Storage::readFromFile(void)
{

	ifstream finUser, finMeeting;
	finUser.open(Path::userPath, ios::in);
	finMeeting.open(Path::meetingPath, ios::in);

	if (!finUser.is_open() || !finMeeting.is_open())
	{
		return false;
	}

	
	while (finUser.good())
	{
		User tu;
		string temp;
		getline(finUser, temp, ',');
		deleteQuo(temp);
		tu.setName(temp);
		if (temp == "")
			break;

		getline(finUser, temp, ',');
		deleteQuo(temp);
		encode(temp);
		tu.setPassword(temp);

		getline(finUser, temp, ',');
		deleteQuo(temp);
		tu.setEmail(temp);

		getline(finUser, temp, '\n');
		deleteQuo(temp);
		tu.setPhone(temp);

		m_userList.push_back(tu);
	}


	string tstring = "";
	string temp = "";
	while (finMeeting.good())
	{
		Meeting tm;
		getline(finMeeting, temp, ',');
		deleteQuo(temp);
		tm.setSponsor(temp);
		if (temp == "")
			break;
		getline(finMeeting, temp, ',');
		deleteQuo(temp);
		auto beS = temp.begin();

		vector<string> v;
		tstring = "";
		while (beS != temp.end())
		{
			if ((*beS) == '&')
			{
				v.push_back(tstring);

 				tstring = "";
			}
			else
			{
				tstring += *beS;
			}

			++beS;
		}
		v.push_back(tstring);
		//tm.setParticipator(v);
		for (auto i : v)
		{
			tm.addParticipator(i);
		}
		
		getline(finMeeting, temp, ',');
		deleteQuo(temp);
		Date td1(temp);
		tm.setStartDate(td1);
		
		getline(finMeeting, temp, ',');
		deleteQuo(temp);
		Date td2(temp);
		tm.setEndDate(td2);
		

		getline(finMeeting, temp, '\n');
		deleteQuo(temp);
		tm.setTitle(temp);
		
		m_meetingList.push_back(tm);
	}

	finUser.close();
	finMeeting.close();

	return true;
}

bool Storage::writeToFile(void)
{
	ofstream foutUser, foutMeeting;
	foutUser.open(Path::userPath, ios::out|ios::trunc);
	foutMeeting.open(Path::meetingPath, ios::out|ios:: trunc);
	auto beUser = m_userList.begin();
	auto beMeeting = m_meetingList.begin();



	if (!foutUser.is_open() || !foutMeeting.is_open())
	{
		return false;
	}


	while (beUser != m_userList.end())
	{
		string password = beUser->getPassword();
		encode(password);
		foutUser << '"' << beUser->getName() << '"' << ','
				 << '"' << password << '"' << ','
				 << '"' << beUser->getEmail() << '"' << ','
				 << '"' << beUser->getPhone() << '"'
				 << '\n';	 
	
		++beUser;
	}

	while (beMeeting != m_meetingList.end())
	{
		foutMeeting << '"' << beMeeting->getSponsor() << '"' << ','
					<< '"';

		vector<string> vP = (*beMeeting).getParticipator();
		int l = vP.size();
		for (auto i : vP)
		{
		    foutMeeting << i;
		    --l;
		    if (l > 0)
		    	foutMeeting << '&';
		}
		 
		foutMeeting << '"' << ','
					<< '"' << (beMeeting->getStartDate()).dateToString(beMeeting->getStartDate()) << '"' << ','
					<< '"' << (beMeeting->getEndDate()).dateToString(beMeeting->getEndDate()) << '"' << ','
					<< '"' << beMeeting->getTitle() << '"' 
					<< '\n';

		++beMeeting;
	}

	foutUser.close();
	foutMeeting.close();

	return true;
}


  /**
  * get Instance of storage
  * @return the pointer of the instance
  */
shared_ptr<Storage> Storage::getInstance(void) {
	if (!m_instance){
		shared_ptr<Storage> temp(new Storage());
		m_instance = temp;
	}
	return m_instance;
}

  /**
  *   destructor
  */
Storage::~Storage() { 
	sync();
}


void Storage::createUser(const User &t_user) {
	m_userList.push_back(t_user);
	m_dirty = 1;
	sync();
}

list<User> Storage::queryUser(function<bool(const User &)> filter) const {
	list<User> temp;

	for (auto be = m_userList.begin(); be != m_userList.end(); ++be) {
		if (filter(*be)) {
			temp.push_back(*be);
		}
	}
	return temp;
}

int Storage::updateUser(function<bool(const User &)> filter,
						function<void(User &)> switcher) {
	int num = 0;
	for (auto be = m_userList.begin(); be != m_userList.end(); ++be) {
		if (filter(*be)) {
			switcher(*be);
			++num;
			m_dirty = 1;
		}
	}
	if (m_dirty)
	{
		sync();
	}
	return num;
}

int Storage::deleteUser(function<bool(const User &)> filter)
{
	int num = 0;
	for (auto be = m_userList.begin(); be != m_userList.end(); )
	{
		if (filter(*be))
		{
			be = m_userList.erase(be);
			++num;
			m_dirty = 1;
		}
		else
		{
			++be;
		}
	}
	if (m_dirty)
	{
		sync();
	}

	return num;
}

void Storage::createMeeting(const Meeting &t_meeting)
{
	m_meetingList.push_back(t_meeting);
	m_dirty = 1;
	sync();
	
}

list<Meeting> Storage::queryMeeting(
      function<bool(const Meeting &)> filter) const
{
	list<Meeting> temp;
	for (auto be = m_meetingList.begin(); be != m_meetingList.end(); ++be)
	{
		if (filter(*be))
		{
			temp.push_back(*be);
		}
	}

	return temp;	
}

int Storage::updateMeeting(function<bool(const Meeting &)> filter,
                    function<void(Meeting &)> switcher)
{
	int num = 0;
	for (auto be = m_meetingList.begin(); be != m_meetingList.end(); ++be)
	{
		if (filter(*be))
		{
			switcher(*be);
			m_dirty = 1;
			++num;
		}
	}
	if (m_dirty)
	{
		sync();
	}
	return num;	
}

int Storage::deleteMeeting(function<bool(const Meeting &)> filter)
{
	int num = 0;
	for (auto be = m_meetingList.begin(); be != m_meetingList.end(); )
	{
		if (filter(*be))
		{
			++num;
			be = m_meetingList.erase(be);
			m_dirty = 1;
		}
		else
		{
			++be;
		}
	}
	if (m_dirty)
	{
		sync();
	}
	return num;
}

bool Storage::sync(void)
{
	if (m_dirty)
	{
		m_dirty = 0;
		return writeToFile();
	}
	else
	{
		return true;
	}
}

