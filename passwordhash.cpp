#include <iostream>
#include <string>

using namespace std;

int main() {
    string Hash = "";
    string intermediate = "";
    string sample = "";
    for(int i = 0; i < 1000; i++) {
        if(i%2 == 0) sample += intermediate;
        if(i%2 == 1) sample += password;
        if(i%3 != 0) sample += salt;
        if(i%7 != 0) sample += password;
        if(i%2 == 0) sample += password;
        if(i%2 == 1) sample += intermediate;
        //HASH FUNCTION (sample);
        intermediate = sample;
        sample = "";
    }

}