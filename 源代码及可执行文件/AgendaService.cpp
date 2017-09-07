#include "User.hpp"
#include "Date.hpp"
#include "Meeting.hpp"
#include "Storage.hpp"
#include "AgendaService.hpp"
#include "Exception.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <functional>
using namespace std;

shared_ptr<Storage> m_storage = nullptr;

AgendaService::AgendaService() {
    startAgenda();
}


AgendaService::~AgendaService() {
    quitAgenda();
}

bool AgendaService::userLogIn(const string &userName, const string &password) {
    auto fun = [=](const User &temp) ->bool{ return true; };
    list<User> allusers = m_storage->queryUser(fun);      
    for (auto i : allusers) {
        if (i.getName() == userName) {
            if (i.getPassword() == password) {
                return true;
            }
            else {
                return false;
            }
        }
    }   
    return false;
}

bool AgendaService::userRegister(const string &userName, const string &password,
                    const string &email, const string &phone) {
    auto fun = [=](const User &temp) ->bool{ return true; };
    list<User> allusers = m_storage->queryUser(fun);    
    for (auto i : allusers) {
        if (i.getName() == userName) {
            return false;
        }
    }
    
    User user(userName, password, email, phone);

    m_storage->createUser(user);
    return true;
}

bool AgendaService::deleteUser(const string &userName, const string &password) {
    auto fun = [=](const User &temp)->bool{
        if (temp.getName() == userName && temp.getPassword() == password) {
            return true;
        }
        else {
            return false;
        }
    };
    int mark = m_storage->deleteUser(fun);
    if (mark) {
        deleteAllMeetings(userName);
        list<Meeting> me = listAllParticipateMeetings(userName);
        for (auto i : me) {
            quitMeeting(userName, i.getTitle());
        }
    }
    return mark;
}


list<User> AgendaService::listAllUsers(void) const {
    auto fun = [](const User &temp) ->bool{ return true; };
 list<User> allusers = m_storage->queryUser(fun);
    return allusers;
}

bool AgendaService::createMeeting(const string &userName, const string &title,
                     const string &startDate, const string &endDate,
                     const vector<string> &participator) {
    auto fun = [=](const Meeting &t)->bool {
        return (t.getTitle() == title);
    }; 
    list<Meeting> me = m_storage->queryMeeting(fun);

    if (me.size()) {
        throw Titlerepetitive();
        return false;
    }
    
    Date startdate(startDate), enddate(endDate);

    if (startdate >= enddate) {
        throw Wrongdate();
        return false;
    }
   
    if (!(startdate.getYear() && enddate.getYear() && Date::isValid(startdate) && Date::isValid(enddate))) {
        return false;
    }
   

    auto fun2 = [](const User& u)->bool { return true; };
    list<User> users = m_storage->queryUser(fun2);
    for (auto i = participator.begin(); i != participator.end(); ++i) {
        bool mark = 0;
        for (auto j : users) {
            if (*i == j.getName()) {
                mark = 1;
                break;
            }
        }
        auto k = i;
        ++k;
        for (; k != participator.end(); ++k) {
            if (*i == *k) {
                return false;
            }
        }
        if (!mark) {
            throw Participatornotexist();
            return false;
        }

        if (*i == userName) {
            return false;
        }
    }
    
    bool mark2 = 0;
    for (auto j : users) {
        if (userName == j.getName()) {
            mark2 = 1;
            break;
        }
    }
    if (!mark2) {
        return false;
    }
    
    auto fun3 = [=](const Meeting &temp)->bool {
        bool mark = 0;
        if (temp.getSponsor() == userName) {
            mark = 1;
        }
        else {
            vector<string> v = temp.getParticipator();
            for (auto j : v) {
                if (j == userName) {
                    mark = 1;
                    break;
                }
            }
        }
        return mark;
    };
    list<Meeting> me2 = m_storage->queryMeeting(fun3);

    for (auto i : me2) {
        if ((startdate > i.getStartDate() && startdate < i.getEndDate())
            ||(enddate > i.getStartDate() && enddate < i.getEndDate())
            ||(i.getStartDate() > startdate && i.getStartDate() < enddate)
            ||(i.getEndDate() > startdate && i.getEndDate() < enddate)
            ||(startdate == i.getStartDate() && enddate == i.getEndDate())) {
            throw Busysponsor();
            return false;
        }
    }
    
    for (auto i : participator) {
        auto fun4 = [=](const Meeting& temp) {
            bool mark = 0;
            if (temp.getSponsor() == i) {
                mark = 1;
            }
            else {
                vector<string> v = temp.getParticipator();
                for (auto j : v) {
                    if (j == i) {
                        mark = 1;
                        break;
                    }
                }
            }
            return mark;           
        };
        list<Meeting> me3 = m_storage->queryMeeting(fun4);

        for (auto j : me3) {
            if ((startdate > j.getStartDate() && startdate < j.getEndDate())
                ||(enddate > j.getStartDate() && enddate < j.getEndDate())
                ||(j.getStartDate() > startdate && j.getStartDate() < enddate)
                ||(j.getEndDate() > startdate && j.getEndDate() < enddate)
                ||(startdate == j.getStartDate() && enddate == j.getEndDate())) {
                throw Busyparticipator();
                return false;
            }
        }
    }
    Meeting meeting(userName, participator, startdate, endDate, title);

    m_storage->createMeeting(meeting);
    return true;
}

bool AgendaService::addMeetingParticipator(const string &userName,
                              const string &title,
                              const string &participator) {
    auto fun = [=](const Meeting& temp)->bool{
        if (temp.getTitle() == title) {
            return true;
        }
        else {
            return false;
        }
    };

    list<Meeting> allmeeting = m_storage->queryMeeting(fun);

    if (allmeeting.size() != 1) {
        throw Titlenotexist();
        return false;
    }
    if ((allmeeting.begin()->getSponsor() != userName)
        || participator == userName) {
        return false;
    }

    vector<string> ve = allmeeting.begin()->getParticipator();
    for (auto i : ve) {
        if (i == participator) {
            return false;
        }
    }

    auto fun1 = [=](const User & t) {
        if ((participator == t.getName())) {
            return true;
        }
        else {
            return false;
        }
    };
    list<User> us = m_storage->queryUser(fun1);
    if (us.size() != 1) {
        throw Participatornotexist();
        return false;
    }

    bool mark2 = 0, mark3 = 0;
    Date startdate(allmeeting.begin()->getStartDate()), enddate(allmeeting.begin()->getEndDate());
    auto fun5 = [=](const Meeting & temp)->bool {
        bool mark = 0;
        if (temp.getSponsor() == participator) {
            mark = 1;
        }
        else {
            vector<string> v = temp.getParticipator();
            for (auto j : v) {
                if (j == participator) {
                    mark = 1;
                    break;
                }
            }
        }
        return mark;       
    };
    list<Meeting> me3 = m_storage->queryMeeting(fun5);
    for (auto j : me3) {
        if ((startdate > j.getStartDate() && startdate < j.getEndDate())
            ||(enddate > j.getStartDate() && enddate < j.getEndDate())
            ||(j.getStartDate() > startdate && j.getStartDate() < enddate)
            ||(j.getEndDate() > startdate && j.getEndDate() < enddate)
            ||(startdate == j.getStartDate() && enddate == j.getEndDate())) {
            throw Busyparticipator();
            return false;  
        }
    }



    auto fun3 = [=](const Meeting& t)->bool {
        return (t.getTitle() == title);
    };

    auto fun4 = [=](Meeting &t) {
        vector<string> ve = t.getParticipator();
        ve.push_back(participator);
        t.setParticipator(ve);
    };

    return m_storage->updateMeeting(fun3, fun4);
}

bool AgendaService::removeMeetingParticipator(const string &userName,
                                 const string &title,
                                 const string &participator) {
    auto fun = [=](const Meeting& temp)->bool{
        if (temp.getTitle() == title) {
            return true;
        }
        else {
            return false;
        }
    };
    list<Meeting> allmeeting = m_storage->queryMeeting(fun);

    if (allmeeting.size() != 1) {
        throw Titlenotexist();
        return false;
    }
    if (allmeeting.begin()->getSponsor() != userName) {
        return false;
    }

    bool mark = 0;
    vector<string> vec = allmeeting.begin()->getParticipator();
    for (auto i : vec) {
        if (participator == i) {
            mark = 1;
            break;
        }
    }
    if (!mark) {
        throw Participatornotexist();
        return false;
    }


    vector<string> ve = allmeeting.begin()->getParticipator();
    for (auto i = ve.begin(); i != ve.end(); ++i) {
        if (*i == participator) {
            ve.erase(i);
            break;
        }
    }
    auto fun2 = [=](const Meeting& t)-> bool {
        return (t.getTitle() == title);
    };
    auto fun3 = [=](Meeting &t) {
        t.setParticipator(ve);
    };

    if (ve.size()) {
        return m_storage->updateMeeting(fun2, fun3);
    }
    else {
        return m_storage->deleteMeeting(fun2);
    }
}

bool AgendaService::quitMeeting(const string &userName, const string &title) {
    auto fun = [=](const Meeting&temp)->bool{
        if (temp.getTitle() == title) {
            return true;
        }
        else {
            return false;
        }
    };

    list<Meeting> allmeeting = m_storage->queryMeeting(fun);

    if (allmeeting.size() != 1) {
        throw Titlenotexist();
        return false;
    }
    
    bool mark = 0;
    vector<string> ve = allmeeting.begin()->getParticipator();
    for (auto i : ve) {
        if (i == userName) {
            mark = 1;
            break;
        }
    }
    if (!mark) {
        return false;
    }
    
    for (auto i = ve.begin(); i != ve.end(); ++i) {
        if (*i == userName) {
            ve.erase(i);
            break;
        }
    }
    
    auto fun2 = [=](const Meeting& t)-> bool {
        if (t.getTitle() == title) {
            return true;
        }
        else {
            return false;
        }
    };

    auto fun3 = [=](Meeting &t) {
        t.setParticipator(ve);
    };

    if (ve.size()) {
        return m_storage->updateMeeting(fun2, fun3);
    }
    else {
        return m_storage->deleteMeeting(fun2);
    }    
}

list<Meeting> AgendaService::meetingQuery(const string &userName,
                                  const string &title) const {
    auto fun = [=](const Meeting &temp) ->bool{
        bool mark = 0;
        if (temp.getSponsor() == userName) {
            mark = 1;
        }
        else {
            vector<string> v = temp.getParticipator();
            for (auto j : v) {
                if (j == userName) {
                    mark = 1;
                    break;
                }
            }
        }

        return (temp.getTitle() == title && mark);
    };

    return m_storage->queryMeeting(fun);   
}

list<Meeting> AgendaService::meetingQuery(const std::string &userName,
                                  const string &startDate,
                                  const string &endDate) const {
    Date startdate(startDate), enddate(endDate);
    list<Meeting> empty;
    if (startdate > enddate) {
        return empty;
    }
   if ( !(Date::isValid(startdate) && Date::isValid(enddate))) {
        return empty;
    }

    auto fun = [=](const Meeting& temp)->bool {
        bool mark = 0, mark2 = 0;
        if (temp.getSponsor() == userName) {
            mark = 1;
        }
        else {
            vector<string> v = temp.getParticipator();
            for (auto j : v) {
                if (j == userName) {
                    mark = 1;
                    break;
                }
            }
        }
        
        if (!(temp.getEndDate() < startdate || temp.getStartDate() > enddate)) {
            mark2 = 1;
        }

        return (mark && mark2);
    };
    list<Meeting> res = m_storage->queryMeeting(fun);
    return res;
}


list<Meeting> AgendaService::listAllMeetings(const string &userName) const {
    auto fun = [=](const Meeting& temp)->bool{
        bool mark = 0;
        if (temp.getSponsor() == userName) {
            mark = 1;
        }
        else {
            vector<string> v = temp.getParticipator();
            for (auto j : v) {
                if (j == userName) {
                    mark = 1;
                    break;
                }
            }
        }
        return mark;
    };
    list<Meeting> res = m_storage->queryMeeting(fun);
    return res;
}

list<Meeting> AgendaService::listAllSponsorMeetings(const string &userName) const {
    auto fun = [=](const Meeting& temp)->bool{
        if (temp.getSponsor() == userName) {
            return true;
        }
        return false;
    };
    list<Meeting> res = m_storage->queryMeeting(fun);
    return res;   
}

list<Meeting> AgendaService::listAllParticipateMeetings(
      const string &userName) const {
    auto fun = [=](const Meeting& temp)->bool{
        vector<string> v = temp.getParticipator();
        for (auto j : v) {
            if (j == userName) {
                   return true;
            }    
        }
        return false;
    };

    list<Meeting> res = m_storage->queryMeeting(fun);
    return res;      
}

bool AgendaService::deleteMeeting(const string &userName, const string &title) {
    auto fun = [=](const Meeting& temp)->bool {
        return (temp.getSponsor() == userName && temp.getTitle() == title);
    };
    return (m_storage->deleteMeeting(fun)) ;
}

bool AgendaService::deleteAllMeetings(const string &userName) {
    auto fun = [=](const Meeting& temp)->bool {
        return (temp.getSponsor() == userName);
    };
    return (m_storage->deleteMeeting(fun));
}

void AgendaService::startAgenda(void) {
    m_storage = Storage::getInstance();
}

void AgendaService::quitAgenda(void) {
    m_storage->sync();
}
