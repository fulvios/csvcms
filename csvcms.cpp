// csvcms.cpp
#include <iostream>
#include "csvcms.h"

void __stdcall CSVCMSMsgOutput(const char* s)
{
	// return 1;
	std::cout << s << std::endl;
}