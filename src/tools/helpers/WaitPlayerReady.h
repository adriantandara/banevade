#ifndef WAITPLAYERREADY_H
#define WAITPLAYERREADY_H

#include "sampapi/0.3.7-R1/CChat.h"

using namespace sampapi::v037r1;

inline CChat *playerChat = nullptr;
bool WaitPlayerReady();

#endif //WAITPLAYERREADY_H
