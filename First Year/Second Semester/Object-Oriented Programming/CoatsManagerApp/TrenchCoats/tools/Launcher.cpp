//
// Created by Emanuel on 25.03.2021.
//

#include "Launcher.h"

#include <windows.h>
#include <shellapi.h>
#include <string>
#include <string.h>

wchar_t* Launcher::getWideCharString(const char *c_string) const {
    const size_t cSize = strlen(c_string) + 1;
    wchar_t* wc = new wchar_t[cSize];
    mbstowcs(wc, c_string, cSize);

    return wc;
}

void Launcher::launch(const std::string& link) const {
    wchar_t* widec_link = getWideCharString(link.c_str());
    ShellExecuteW(NULL, L"open", widec_link, NULL, NULL, SW_SHOWNORMAL);
    delete[] widec_link;
}
