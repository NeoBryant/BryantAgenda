#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP value

#include <sstream>
#include <string>
#include <iostream>

using namespace std;

class Exception {
public:
  virtual const std::string what() const throw() { return "Exception occurs!"; };
};


class Wrongdate : public Exception
{
public:
    const string what() const throw() { 
    	return "[error] The date is wrong!"; 
    };
};

class Busysponsor : public Exception
{
public:
	const string what() const throw() { 
		return "[error] You are busy in other meeting at the same time!"; 
	};
};

class Busyparticipator : public Exception
{
public:
	const string what() const throw() { 
		return ("[error] The Participator is busy in other meeting!"); 
	};
};


class Participatornotexist : public Exception
{
public:	
	const string what() const throw() { 
		return ("[error] The Participator does not existed in the system!"); 
	};	
};


class Titlerepetitive : public Exception
{
public:
	const string what() const throw() { 
		return "[error] The title of meeting has existed!"; 
	};
};

class Titlenotexist : public Exception
{
public:
	const string what() const throw() { 
		return "[error] The title of meeting does not exist!"; 
	};
};




#endif