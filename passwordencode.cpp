#include <iostream>
#include "md5.h"
#include <vector>
#include <string>

using namespace std;

string encodeBase(string hash, int len) {
    string hexed;
    vector<int> crypt{11, 4, 10, 5, 3, 9, 15, 2, 8, 14, 1, 7, 13, 0, 6, 12};
    for(int k = 0; k < 16; k++) {
        hexed.push_back(hash.at(crypt.at(k)));
    }
    string bin = "";
    for(int i = 0; i < len; i++) {
        bin += hexToBin(hexed.at(i));
    }
    return binToB64(bin);
}

const char* hexToBin(char hex) {
    switch(toupper(hex)) {
        case '0': return "0000";
        case '1': return "0001";
        case '2': return "0010";
        case '3': return "0011";
        case '4': return "0100";
        case '5': return "0101";
        case '6': return "0110";
        case '7': return "0111";
        case '8': return "1000";
        case '9': return "1001";
        case 'A': return "1010";
        case 'B': return "1011";
        case 'C': return "1100";
        case 'D': return "1101";
        case 'E': return "1110";
        case 'F': return "1111";
    }
}

string binToB64(string convert) {
    string b64="./0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    string fuck;
    string bitch = "";
    int ass;
    
    for(int j = 5; j < convert.length();j+=6) {
        fuck = convert.substr(j-5,6);
        ass = stoi(fuck,nullptr,2);
        bitch += b64.at(ass);
    }
    return bitch;
}


// 4 * ((n + 2) / 3);

