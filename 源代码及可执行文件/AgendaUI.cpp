#include "AgendaUI.hpp"
#include "AgendaService.hpp"
#include "Meeting.hpp"
#include "Date.hpp"
#include "Exception.hpp"
#include <iostream>
#include <string>
#include <list>
#include <iomanip>
#include <regex>

using namespace std;

AgendaUI::AgendaUI()
{ 
	username = "";
	password = "";
}
AgendaUI::~AgendaUI()
{ }
void AgendaUI::Login()
{
	string username, password;
	cout << "[log in] [user name] [password]\n"
		 << "[log in] ";
	cin >> username >> password;	 
	while (!agendaservice.userLogIn(username, password))
	{
		cout << "[log in] password error or user doesn't exist\n"
			 << "[log in] Please input again!\n"
			 << "[log in] [user name] [password]\n"
			 << "[log in] ";
		cin >> username >> password;	 
	}
	cout << "[log in] succeed!\n";
	this->username = username;
	this->password = password;
}

void AgendaUI::Register()
{
	string username, password, email, phone;
	cout << "[register] [user name] [password] [email] [phone]\n"
		 << "[register] ";
	cin >> username >> password >> email >> phone;

	while (!checkUsername(username)) {
		cout << "[register] This username is a wrong form!\n"
			 << "[register] Please input again!\n"
			 << "[register] [user name] [password] [email] [phone]\n"
			 << "[register] ";
		cin >> username >> password >> email >> phone;	
	}

	while (!checkPassword(password)) {
		cout << "[register] This password is a wrong form!\n"
			 << "[register] Please input again!\n"
			 << "[register] [user name] [password] [email] [phone]\n"
			 << "[register] ";
		cin >> username >> password >> email >> phone;	
	}

	while (!checkEmail(email)) {
		cout << "[register] This email is a wrong form!\n"
			 << "[register] Please input again!\n"
			 << "[register] [user name] [password] [email] [phone]\n"
			 << "[register] ";
		cin >> username >> password >> email >> phone;	
	}	

	while (!checkPhone(phone)) {
		cout << "[register] This phone is a wrong form!\n"
			 << "[register] Please input again!\n"
			 << "[register] [user name] [password] [email] [phone]\n"
			 << "[register] ";
		cin >> username >> password >> email >> phone;	
	}


	while (!agendaservice.userRegister(username, password, email, phone))	 
	{
		cout << "[register] This username has been registered!\n"
			 << "[register] Please input again!\n"
			 << "[register] [user name] [password] [email] [phone]\n"
			 << "[register] ";
		cin >> username >> password >> email >> phone;	 
	}
	cout << "[register] succeed!\n";
	this->username = username;
	this->password = password;	
}

int AgendaUI::listaction()
{
	string ope = "";
	cout << "---------------------------Agenda---------------------------\n"
		 << "Action :\n"
		 << "o    - log out Agenda\n"
		 << "dc   - delete Agenda accout\n"
		 << "lu   - list all Agenda user\n"
		 << "cm   - create a meeting\n"
		 << "amp  - add meeting participator\n"
		 << "rmp  - remove meeting participator\n"
		 << "rqm  - request to quit meeting\n"
		 << "la   - list all meetings\n"
		 << "las  - list all sponsor meetings\n"
		 << "lap  - list all participator meetings\n"
		 << "qm   - query meeting by title\n"
		 << "qt   - query meeting by time interval\n"
		 << "dm   - delete meeting by title\n"
		 << "da   - delete all meetings\n"
		 << "------------------------------------------------------------\n\n"
		 << "Agenda@" << username << " :~# ";
	cin >> ope;

	while (ope != "o" && ope != "dc" && ope != "lu" && ope != "cm"
		&& ope != "amp" && ope != "rmp" && ope != "rqm" && ope != "la"
		&& ope != "las" && ope != "lap" && ope != "qm" && ope != "qt"
		&& ope != "dm" && ope != "da") {
		cout << "Agenda@" << username << " :~# " << "wrong action!\n" << endl;	
		cout << "---------------------------Agenda---------------------------\n"
			 << "Action :\n"
			 << "o    - log out Agenda\n"
			 << "dc   - delete Agenda accout\n"
			 << "lu   - list all Agenda user\n"
			 << "cm   - create a meeting\n"
			 << "amp  - add meeting participator\n"
			 << "rmp  - remove meeting participator\n"
			 << "rqm  - request to quit meeting\n"
			 << "la   - list all meetings\n"
			 << "las  - list all sponsor meetings\n"
			 << "lap  - list all participator meetings\n"
			 << "qm   - query meeting by title\n"
			 << "qt   - query meeting by time interval\n"
			 << "dm   - delete meeting by title\n"
			 << "da   - delete all meetings\n"
			 << "------------------------------------------------------------\n\n"
			 << "Agenda@" << username << " :~# ";
		cin >> ope;
	}	 	 
	if (ope == "o") {
		return 0;
	}
	else if (ope == "dc") {
		return 1;
	}
	else if (ope == "lu") {
		return 2;
	}
	else if (ope == "cm") {
		return 3;
	}
	else if (ope == "amp") {
		return 4;
	}
	else if (ope == "rmp") {
		return 5;
	}
	else if (ope == "rqm") {
		return 6;
	}
	else if (ope == "la") {
		return 7;
	}
	else if (ope == "las") {
		return 8;
	}
	else if (ope == "lap") {
		return 9;
	}
	else if (ope == "qm") {
		return 10;
	}
	else if (ope == "qt") {
		return 11;
	}
	else if (ope == "dm") {
		return 12;
	}
	else if (ope == "da") {
		return 13;
	}							
}


void AgendaUI::OperationLoop()
{
	string ope;
	int action;
	cout << "---------------------------Agenda---------------------------\n"
		 << "Action :\n"
		 << "l    - log in Agenda by user name and password\n"
		 << "r    - register an Agenda accout\n"
		 << "q    - quit Agenda\n"
		 << "-------------------------------------------------------------\n\n"
		 << "Agenda :~$ ";

	cin >> ope;	 
	while (ope != "l" && ope != "r" && ope != "q") {
		cout << "Agenda :~$ wrong action!\n"
			 << "Agenda :~$ Please input again!\n";
		cout << "---------------------------Agenda---------------------------\n"
			 << "Action :\n"
			 << "l    - log in Agenda by user name and password\n"
			 << "r    - register an Agenda accout\n"
			 << "q    - quit Agenda\n"
			 << "-------------------------------------------------------------\n\n"
			 << "Agenda :~$ ";

		cin >> ope;			
	}

	if (ope == "l") {
		Login();
	}
	else if (ope == "r") {
		Register();
	}
	else if (ope == "q"){
		return ; 
	}
	action = listaction();
	while (action != 0) {
		switch (action) {
			case 1: {
				deleteAgendaAccout();
				action = 0;
				break;
			}
			case 2: {
				listAllAgendaUser();
				break;
			}
			case 3: {
				createAMeeting();
				break;
			}
			case 4: {
				addMeetingParticipator();
				break;
			}
			case 5: {
				removeMeetingParticipator();
				break;
			}
			case 6: {
				requestToQuitMeeting();
				break;
			}
			case 7: {
				listAllMeetings();
				break;
			}
			case 8: {
				listAllSponsorMeetings();
				break;
			}
			case 9: {
				listAllParticipatorMeetings();
				break;
			}
			case 10: {
				queryMeetingByTitle();
				break;
			}
			case 11: {
				queryMeetingByTimeInterval();
				break;
			}
			case 12: {
				deleteMeetingByTitle();
				break;
			}
			case 13: {
				deleteAllMeetings();
				break;
			}
			default: {
				break;
			}
		}
		if (action != 0) {
			action = listaction();
		}
	}	
	if (action == 0) {
		OperationLoop();
	}	
}

bool AgendaUI::deleteAgendaAccout() {
	agendaservice.deleteUser(username, password);
	cout << "[delete agenda account] succed!" << endl;
	return true;
}

bool AgendaUI::listAllAgendaUser() {
	cout.setf(ios::left);
	cout << "\n[list all users]\n\n" 
		 << setw(20) << "name"  << setw(20) << "email" << "phone" << endl;
	list<User> u = agendaservice.listAllUsers();
	for (auto i : u) {
		cout.setf(ios::left);
		cout << setw(20) << i.getName() 
			 << setw(20) << i.getEmail() 
			 << setw(20) << i.getPhone() << "\n";
	}
	return true;
}

bool AgendaUI::createAMeeting() {
	string strnum = "";
	int number = 0;
	string participator, title, startdate, enddate;
	vector<string> pas;
	cout << "\n[create meeting] [the number of participators]\n"
		 << "[create meeting] ";
	cin >> strnum;

	for (auto i : strnum) {
		if (i < '0' || i > '9') {
			cout << "[create meeting] wrong number!\n";
			return false;
		}
	}
	for (auto i : strnum) {
		number *= 10;
		number += (i - '0');
	}

	for (int i = 0; i < number; ++i) {
		cout << "[create meeting] [please enter the participator "<< i+1 <<" ]\n"
			 << "[create meeting] ";
		cin >> participator;	
		pas.push_back(participator); 
	}	 
	cout << "[create meeting] [title] [start time(yyyy-mm-dd/hh:mm)] [end time(yyyy-mmdd/hh:mm)]\n"
		 << "[create meeting] ";
	cin >> title >> startdate >> enddate;

	while (!Date::isValid(Date::stringToDate(startdate)) || !Date::isValid(Date::stringToDate(enddate))) {
		cout << "[create meeting] The dates are wrong forms!\n"
			 << "[create meeting] Please input again!\n"
			 << "[create meeting] [title] [start time(yyyy-mm-dd/hh:mm)] [end time(yyyy-mmdd/hh:mm)]\n"
			 << "[create meeting] "; 
		cin >> title >> startdate >> enddate;	 
	}

	try {
		if (agendaservice.createMeeting(username, title, startdate, enddate, pas)) {
			cout << "[create meeting] succeed!" << endl;
			return true;
		}
		else {
			cout << "[create meeting] error!" << endl;
			return false;
		}
	}
	catch (Titlerepetitive e) {
		cout << e.what() << endl;
		return false;
	}
	catch (Wrongdate e) {
		cout << e.what() << endl;
		return false;
	}
	catch (Busysponsor e) {
		cout << e.what() << endl;
		return false;		
	}
	catch (Busyparticipator e) {
		cout << e.what() << endl;
		return false;			
	}
	catch(Participatornotexist e) {
		cout << e.what() << endl;
		return false;
	}

}

bool AgendaUI::addMeetingParticipator() {
	string title, participator;
	cout <<  "\n[add participator] [meeting title] [participator username]\n"
		 << "[add participator] ";
	cin >> title >> participator; 

	try { 
		if (agendaservice.addMeetingParticipator(username, title, participator)) {
			cout << "[add participator] succed!" << endl;
			return true;
		}
		else {
			cout << "[add participator] error!" << endl;
			return false;
		}
	}
	catch (Titlenotexist e) {
		cout << e.what() << endl;
		return false;
	}
	catch (Busyparticipator e) {
		cout << e.what() << endl;
		return false;	
	}
	catch (Participatornotexist e) {
		cout << e.what() << endl;
		return false;	
	}
}
bool AgendaUI::removeMeetingParticipator() {
	string title, participator;
	cout <<  "\n[remove participator] [meeting title] [participator username]\n" 
		 << "[remove participator] ";
	cin >> title >> participator;
	try {
		if (agendaservice.removeMeetingParticipator(username, title, participator)) {
			cout << "[remove participator] succed!" << endl;
			return true;
		}
		else {
			cout << "[remove participator] error!" << endl;
			return false;
		}
	}
	catch (Titlenotexist e) {
		cout << e.what() << endl;
		return false;
	}
	catch (Participatornotexist e) {
		cout << e.what() << endl;
		return false;	
	}	
}
bool AgendaUI::requestToQuitMeeting() {
	string title;
	cout << "\n[quit meeting] [meeting title]\n"
		 << "[quit meeting] ";
	cin >> title;	
	try { 
		if (agendaservice.quitMeeting(username, title)) {
			cout << "[quit meeting] succeed!" << endl;
			return true;
		}
		else {
			cout << "[quit meeting] error!" << endl;
			return false;
		}
	}
	catch (Titlenotexist e) {
		cout << e.what() << endl;
		return false;		
	}

}
bool AgendaUI::listAllMeetings() {
	list<Meeting> me = 	agendaservice.listAllMeetings(username); 

	if (me.size() == 0) {
		cout << "[list all meetings] no any meetings" << endl;
		return false;
	}
	
	cout.setf(ios::left);
	cout << "\n[list all meetings]\n\n"
		 << setw(20) << "title"
		 << setw(20) << "sponsor"
		 << setw(20) << "start time"
		 << setw(20) << "end time"
		 << "participators\n";

	for (auto i : me) {
		cout.setf(ios::left);
		cout << setw(20) << i.getTitle()
			 << setw(20)  << i.getSponsor()
			 << setw(20)  << Date::dateToString(i.getStartDate())
			 << setw(20)  << Date::dateToString(i.getEndDate());
		vector<string> pas = i.getParticipator();
		for (auto be = pas.begin(); be != pas.end(); ++be) {
			cout << *be;
			if (--pas.end() != be) {
				cout << ',';
			}
		}	
		cout << "\n"; 
	}	 
	return true;
}
bool AgendaUI::listAllSponsorMeetings() {
	list<Meeting> me = agendaservice.listAllSponsorMeetings(username);	

	if (me.size() == 0) {
		cout << "[list all sponsor meetings] no such a meeting" << endl;
		return false;
	}

	cout.setf(ios::left);
	cout << "\n[list all sponsor meetings]\n\n"
		 << setw(20) << "title"
		 << setw(20) << "sponsor"
		 << setw(20) << "start time"
		 << setw(20) << "end time"
		 << "participators\n";

	for (auto i : me) {
		cout.setf(ios::left);
		cout << setw(20) << i.getTitle()
			 << setw(20)  << i.getSponsor()
			 << setw(20)  << Date::dateToString(i.getStartDate())
			 << setw(20)  << Date::dateToString(i.getEndDate());
		vector<string> pas = i.getParticipator();
		for (auto be = pas.begin(); be != pas.end(); ++be) {
			cout << *be;
			if (--pas.end() != be) {
				cout << ',';
			}
		}	
		cout << "\n"; 
	}	 
	return true;
}

bool AgendaUI::listAllParticipatorMeetings() {
	list<Meeting> me = 	agendaservice.listAllParticipateMeetings(username);

	if (me.size() == 0) {
		cout << "[list all participator meetings] no such a meeting" << endl;
		return false;
	}

	cout.setf(ios::left);
	cout << "\n[list all participator meetings]\n"
		 << setw(20) << "title"
		 << setw(20) << "sponsor"
		 << setw(20) << "start time"
		 << setw(20) << "end time"
		 << "participators\n";

	for (auto i : me) {
		cout.setf(ios::left);
		cout << setw(20) << i.getTitle()
			 << setw(20)  << i.getSponsor()
			 << setw(20)  << Date::dateToString(i.getStartDate())
			 << setw(20)  << Date::dateToString(i.getEndDate());
		vector<string> pas = i.getParticipator();
		for (auto be = pas.begin(); be != pas.end(); ++be) {
			cout << *be;
			if (--pas.end() != be) {
				cout << ',';
			}
		}	
		cout << "\n"; 
	}	 
	return true;
}
bool AgendaUI::queryMeetingByTitle() {
	cout.setf(ios::left);
	string title;
	cout << "\n[query meeting] [title]\n"
		 << "[query meeting] ";
	cin >> title;

	list<Meeting> me = agendaservice.meetingQuery(username, title);

	if (me.size() == 0) {
		cout << "[query meeting] no such a meeting!" << endl;
		return false;
	}


	cout << setw(20) << "title"
		 << setw(20) << "sponsor"
		 << setw(20) << "start time"
		 << setw(20) << "end time"
		 << "participators\n";
	for (auto i : me) {
		cout.setf(ios::left);
		cout << setw(20) << i.getTitle()
			 << setw(20)  << i.getSponsor()
			 << setw(20)  << Date::dateToString(i.getStartDate())
			 << setw(20)  << Date::dateToString(i.getEndDate());
		vector<string> pas = i.getParticipator();
		for (auto be = pas.begin(); be != pas.end(); ++be) {
			cout << *be;
			if (--pas.end() != be) {
				cout << ',';
			}
		}	
		cout << "\n"; 
	}	 
	return true;
}
bool AgendaUI::queryMeetingByTimeInterval() {
	cout.setf(ios::left);
	string startdate, enddate;
	cout << "\n[query meetings] [start time(yyyy-mm-dd/hh:mm)] [end time(yyyy-mm-dd/hh:mm)]\n"
		 << "[query meetings] ";
	cin >> startdate >> enddate;


	while (!Date::isValid(Date::stringToDate(startdate)) || !Date::isValid(Date::stringToDate(enddate))) {
		cout << "[query meetings] The dates are wrong forms!\n"
			 << "[query meetings] Please input again!\n"
			 << "[query meetings] [start time(yyyy-mm-dd/hh:mm)] [end time(yyyy-mm-dd/hh:mm)]\n"
			 << "[query meetings] "; 
		cin >> startdate >> enddate;	 
	}


	list<Meeting> me = agendaservice.meetingQuery(username, startdate, enddate);

	if (me.size() == 0) {
		cout << "[query meeting] no such a meeting!" << endl;
		return false;
	}

	cout << setw(20) << "title"
		 << setw(20) << "sponsor"
		 << setw(20) << "start time"
		 << setw(20) << "end time"
		 << "participators\n";	
	for (auto i : me) {
		cout.setf(ios::left);
		cout << setw(20) << i.getTitle()
			 << setw(20)  << i.getSponsor()
			 << setw(20)  << Date::dateToString(i.getStartDate())
			 << setw(20)  << Date::dateToString(i.getEndDate());
		vector<string> pas = i.getParticipator();
		for (auto be = pas.begin(); be != pas.end(); ++be) {
			cout << *be;
			if (--pas.end() != be) {
				cout << ',';
			}
		}	
		cout << "\n"; 
	}	 
	return true;
}
bool AgendaUI::deleteMeetingByTitle() {
	string title;
	cout << "\n[delete meeting] [title]\n"
		 << "[delete meeting] ";
	cin >> title;

	if (agendaservice.deleteMeeting(username, title)) {
		cout << "[delete meeting] succeed!" << endl;
		return true;
	}
	else {
		cout << "[delete meeting] error!" << endl;
		return false;		
	}
}
bool AgendaUI::deleteAllMeetings() {
	if (agendaservice.deleteAllMeetings(username)) {
		cout << "\n[delete all meetings] succeed!" << endl;
		return true;
	}
	else {
		cout << "\n[delete all meetings] error!" << endl;
		return false;		
	}
}


bool AgendaUI::checkUsername(string username) {
	regex pattern("[A-Za-z0-9]{8,30}");
	if( regex_match(username, pattern)) {
	   	return true;
	}
	else {
		return false;
	}
}
bool AgendaUI::checkPassword(string password) {
	//regex pattern("/^(?=.*[A-Za-z])(?=.*\\d)[A-Za-z\\d]{6,18}$/");
	regex pattern("[A-Za-z0-9]{6,18}");
	if( regex_match(password, pattern)) {
	   	return true;
	}
	else {
		return false;
	}
}

bool AgendaUI::checkEmail(string email) {
	regex pattern("([0-9A-Za-z\\-_\\.]+)@([0-9a-z]+\\.[a-z]{2,3}(\\.[a-z]{2})?)");
	if ( regex_match( email, pattern )) {
		return true;
	}
	else {
		return false;
	}
}
bool AgendaUI::checkPhone(string phone) {
	regex pattern("1[0-9]{10}");
	if ( regex_match( phone, pattern )) {
		return true;
	}
	else {
		return false;
	}	
}