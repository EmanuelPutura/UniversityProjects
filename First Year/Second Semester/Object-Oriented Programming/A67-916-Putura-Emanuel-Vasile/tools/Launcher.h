//
// Created by Emanuel on 25.03.2021.
//

#ifndef BROWSERLAUNCHER_H
#define BROWSERLAUNCHER_H

#include <string>

/*
 * Launcher class - handles browser launching
 */
class Launcher {
private:
    /*
     * Transforms normal characters array into wide char array
     */
    wchar_t* getWideCharString(const char* c_string) const;
public:
    /*
     * Launches the browser at a given link
     */
    void launch(const std::string& link) const;
};

#endif
