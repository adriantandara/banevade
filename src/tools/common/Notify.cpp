#include <windows.h>
#include <string>

void Notify(const char* title, const char* message) {
    std::string script =
        "Add-Type -AssemblyName System.Windows.Forms; "
        "$global:balloon = New-Object System.Windows.Forms.NotifyIcon; "
        "$path = (Get-Process -id $pid).Path; "
        "$balloon.Icon = [System.Drawing.Icon]::ExtractAssociatedIcon($path); "
        "$balloon.BalloonTipIcon = [System.Windows.Forms.ToolTipIcon]::Info; "
        "$balloon.BalloonTipText = '" + std::string(message) + "'; "
        "$balloon.BalloonTipTitle = '" + std::string(title) + "'; "
        "$balloon.Visible = $true; "
        "$balloon.ShowBalloonTip(9000);";

    std::string command = "powershell.exe -NoProfile -Command \"" + script + "\"";

    STARTUPINFO si = { sizeof(STARTUPINFO) };
    si.dwFlags = STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_HIDE;

    PROCESS_INFORMATION pi = {};

    if (!CreateProcess(
            nullptr,
            const_cast<char*>(command.c_str()),
            nullptr,
            nullptr,
            FALSE,
            CREATE_NO_WINDOW,
            nullptr,
            nullptr,
            &si,
            &pi
        )) {
        MessageBox(nullptr, "Failed to create process", "Error", MB_OK | MB_ICONERROR);
        return;
    }

    WaitForSingleObject(pi.hProcess, INFINITE);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}
