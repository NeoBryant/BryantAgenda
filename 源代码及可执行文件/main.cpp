#include <iostream>
#include <string>
#include <vector>
#include "User.hpp"
#include "Date.hpp"
#include "Meeting.hpp"
#include "Storage.hpp"
#include "AgendaService.hpp"
#include "AgendaUI.hpp"
using namespace std;



AgendaUI aui;


int main()
{

	aui.OperationLoop();


	return 0;
}