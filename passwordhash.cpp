#include <iostream>
#include <string>
#include "md5.h"

using namespace std;

    string thousandLoop(string password, string salt, string magic)
    {
        string intermediate = intermediateZero(password, salt, magic);
        string sample = "";
        for(int i = 0; i < 1000; i++) {
            if(i%2 == 0) sample += intermediate;
            if(i%2 == 1) sample += password;
            if(i%3 != 0) sample += salt;
            if(i%7 != 0) sample += password;
            if(i%2 == 0) sample += password;
            if(i%2 == 1) sample += intermediate;
            //HASH FUNCTION (sample);
            intermediate = md5(sample);
            sample = "";
        }
        return intermediate;

    }