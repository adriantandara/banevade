#include "Webhook.h"
#include <windows.h>

int system_no_output(std::string command)
{
    command.insert(0, "/C ");

    SHELLEXECUTEINFOA ShExecInfo = { 0 };
    ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
    ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
    ShExecInfo.hwnd = NULL;
    ShExecInfo.lpVerb = NULL;
    ShExecInfo.lpFile = "cmd.exe";
    ShExecInfo.lpParameters = command.c_str();
    ShExecInfo.lpDirectory = NULL;
    ShExecInfo.nShow = SW_HIDE;
    ShExecInfo.hInstApp = NULL;

    if (ShellExecuteExA(&ShExecInfo) == FALSE)
        return -1;

    WaitForSingleObject(ShExecInfo.hProcess, INFINITE);

    DWORD rv;
    GetExitCodeProcess(ShExecInfo.hProcess, &rv);
    CloseHandle(ShExecInfo.hProcess);

    return rv;
}

void SendDiscord(std::string webhook_id, std::string webhook_token, std::string title, std::string description) {
    std::string url = "https://discord.com/api/webhooks/" + webhook_id + "/" + webhook_token;
    std::string command = "curl -X POST -H \"Content-Type: application/json\" -d \"{\\\"username\\\": \\\"Ban Evade\\\", \\\"embeds\\\":[{ \\\"color\\\": 16711680, \\\"title\\\": \\\"" + title + "\\\", \\\"description\\\": \\\"" + description + "\\\" }]}\" " + url;
    system_no_output(command);
}
