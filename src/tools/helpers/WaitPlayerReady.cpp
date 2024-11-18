#include "WaitPlayerReady.h"
#include <thread>

bool WaitPlayerReady()
{
    while (playerChat == nullptr)
    {
        playerChat = RefChat();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    return true;
}
