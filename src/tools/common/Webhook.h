#ifndef WEBHOOK_H
#define WEBHOOK_H

#include <string>

void SendDiscord(std::string webhook_id, std::string webhook_token, std::string title, std::string description);

#endif //WEBHOOK_H
