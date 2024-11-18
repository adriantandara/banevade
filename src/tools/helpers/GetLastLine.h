#ifndef GETLASTLINE_H
#define GETLASTLINE_H

#include <string>

#include "sampapi/0.3.7-R1/CChat.h"

using namespace std;
using namespace sampapi::v037r1;

string getLastLine(const string& filePath);
void monitorLogFile(CChat *playerChat);

#endif //GETLASTLINE_H
