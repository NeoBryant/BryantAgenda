#ifndef AGENDAUI_HPP
#define AGENDAUI_HPP value

#include <string>
#include <iostream>
#include "AgendaService.hpp"

using namespace std;

class AgendaUI
{
public:
	AgendaUI();
	~AgendaUI();
	void Login();
	void Register();
	int listaction();

	bool deleteAgendaAccout();
	bool listAllAgendaUser();
	bool createAMeeting();
	bool addMeetingParticipator();
	bool removeMeetingParticipator();
	bool requestToQuitMeeting();
	bool listAllMeetings();
	bool listAllSponsorMeetings();
	bool listAllParticipatorMeetings();
	bool queryMeetingByTitle();
	bool queryMeetingByTimeInterval();
	bool deleteMeetingByTitle();
	bool deleteAllMeetings();

	void OperationLoop();

	bool checkUsername(string username);
	bool checkPassword(string password);
	bool checkEmail(string email);
	bool checkPhone(string phone);
	
private:
	AgendaService agendaservice;
	string username, password;

};

#endif