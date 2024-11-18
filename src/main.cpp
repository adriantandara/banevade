#include "main.h"

#include "tools/common/Webhook.h"
#include "tools/helpers/WaitPlayerReady.h"
#include "tools/helpers/GetLastLine.h"

void Thread() {
    using namespace std;

    auto chat_future = async(launch::async, WaitPlayerReady);

    if (!chat_future.get() && playerChat == nullptr) return;

    this_thread::sleep_for(chrono::seconds(1));

    const string text0 = "{008080}>> {f9f9f9}client {008080}ban evade{f9f9f9} initialized.";
    const string text1 = "{008080}>> {f9f9f9}developed by {008080}adriantandara{f9f9f9}.";

    playerChat->AddMessage(0x008080FF, text0.c_str());
    playerChat->AddMessage(0x008080FF, text1.c_str());

    this_thread::sleep_for(chrono::seconds(5));

    playerChat->AddMessage(0x008080FF, "{008080}>> {f9f9f9}monitoring {008080}chat{f9f9f9} started.");

    monitorLogFile(playerChat);
}

int APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) std::thread{Thread}.detach();
    return TRUE;
}