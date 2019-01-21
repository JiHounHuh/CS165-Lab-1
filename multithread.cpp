#include <iostream>
#include "md5.h"
#include <string>
#include <vector>
#include <cstdlib>
#include <iomanip>
#include <thread>
using namespace std;

string intermediateZero (string &password, string &salt, string &magic){
    string alternatesum = md5( password + salt + password);
    string substr4 = ""; //length(password) bytes of the Alternate sum, repeated as necessary
    for (int i = 0; i < password.length(); i++){
        //substr4 = substr4 + "" + alternatesum.at(i);
        string subalternatesum = alternatesum.substr(i*2, 2);
        char alternatesum_array[subalternatesum.length()+1];
        strcpy(alternatesum_array, subalternatesum.c_str());
        int characternum = (int)(strtol(alternatesum_array, NULL , 16));
        unsigned char character = (unsigned char)(characternum);
        //cout << "hex " << alternatesum_array[i] << alternatesum_array[i+1]<< endl;
        printf("%02x", character);
        // cout << endl << "character " << character << endl;
        // cout << "number " << characternum << endl;
        //cout << "number " << (int)strtol(alternatesum_array, NULL, 16) << endl;
        substr4 += character;
    }
    string substr5 = ""; //for each bit in length(password), from low to high and stopping after...
    for (int i = password.length(); i != 0; i >>= 1){
        if (i & 1){
            substr5 += '\0';
        }
        else{
            substr5 += password.at(0);
        }
    }
    // string everything = "" + password + magic + salt + substr4 + substr5;
    // for (int i= 0; i < everything.length(); i++){
    //     printf("%02x", everything.at(i));
    // }
    // cout << endl << "alternate sum " << alternatesum << endl;
    // cout << password + magic + salt + substr4 + substr5 << endl;
    // cout << "intermediate 0: " << md5(password + magic + salt + substr4 + substr5) << endl;
    return md5(password + magic + salt + substr4 + substr5);
}

// string binToB64(string convert) {
//     string b64="./0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
//     string fuck;
//     string bitch = "";
//     int ass;
    
//     for(int j = 5; j < convert.length();j+=6) {
//         fuck = convert.substr(j-5,6);
//         ass = stoi(fuck,nullptr,2);
//         bitch += b64.at(ass);
//        // cout << j << endl;
//     }
//   //  cout << "Bitch" << endl;
//     return bitch;
// }

// const char* hexToBin(char hex) {
//     switch(toupper(hex)) {
//         case '0': return "0000";
//         case '1': return "0001";
//         case '2': return "0010";
//         case '3': return "0011";
//         case '4': return "0100";
//         case '5': return "0101";
//         case '6': return "0110";
//         case '7': return "0111";
//         case '8': return "1000";
//         case '9': return "1001";
//         case 'A': return "1010";
//         case 'B': return "1011";
//         case 'C': return "1100";
//         case 'D': return "1101";
//         case 'E': return "1110";
//         case 'F': return "1111";
//     }
// }

// string encodeBase(string hash) {
//    // int len;
//     //len = 16;
//     string hexed = "";
//     int place = 0;
//     vector<string> death;
//     static const int crypt[] = {11,4,10,5,3,9,15,2,8,14,1,7,13,0,6,12};
   
//    //cout << hash << endl;
//     //static const int crypt[] = {11,4,10,5,3,9,15,2,8,14,1,7,13,0,6,12};
//     //vector<int> crypt = {11, 4, 10, 5, 3, 9, 15, 2, 8, 14, 1, 7, 13, 0, 6, 12};
//     //vector<int> crypt (arr, arr + sizeof(arr) / sizeof(arr[0]));
    
//     string bin = "";
//     for(int p = 0; p < hash.length(); p++) {
//         bin += hexToBin(hash.at(p));
//     }
//     for(int j = 7; j < bin.length(); j+= 8) {
//        death.push_back(bin.substr(j-7,8));
//    }
//     for(int test = 0; test < 16; test++) {
//         hexed += death.at(crypt[test]);
//     }
//    // cout << "after" << endl;
//     return binToB64(hexed);
// }
const string b64="./0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
//==========================================================================================
string base64(unsigned int hash, int amount) {
   string pin;
    int test = hash & 0x3f;
    for(int i = amount; i > 0 ; --i) {
        // cout << "hash value: " << hash << endl;
        // cout << "hash plus something: " << test << endl;
        pin += b64.at(hash & 0x3f);
        hash = (hash >> 6);
       // hash >>= 6;
    }

    // while(--amount >= 0) {
    //     pin += b64.at(hash & 0x3f);
    //     //hash = (hash >> 6);
    //     hash >>= 6;
    // }
    // cout << "done with encode: "<< pin << endl;
    return pin;
}

string to64_tripleGroup(string hash, unsigned int first, unsigned int second, unsigned int third) {
    unsigned int semi = ((static_cast<unsigned char>(hash.at(first)) << 16)) |
                (static_cast<unsigned char>(hash.at(second))<<8) |
                (static_cast<unsigned char>(hash.at(third)));
    
    // cout << "Hash String: " << hash << endl;

    // cout << "Semi: " << hex << semi << endl;
    // cout << "triple one: " << hex << (static_cast<unsigned char>(hash.at(first)) << 16) << endl;
    // cout << "triple two: " << hex << ((static_cast<unsigned char>(hash.at(second)) << 8)) << endl;
    // cout << "triple three: " << hex << static_cast<unsigned char>(hash.at(third)) << endl;
    return base64(semi, 4);
}

string to64_singleGroup(string hash, unsigned int first) {
    unsigned int semi = hash.at(first);
    return base64(semi, 2);
}


string encryption(string hash) {
    cout << endl;
    string finalProduct = "";
    finalProduct += to64_tripleGroup(hash, 0, 6, 12);
    finalProduct += to64_tripleGroup(hash, 1, 7, 13);
    finalProduct += to64_tripleGroup(hash, 2, 8, 14);
    finalProduct += to64_tripleGroup(hash, 3, 9, 15);
    finalProduct += to64_tripleGroup(hash, 4, 10, 5);
    finalProduct += to64_singleGroup(hash, 11);
    return finalProduct;
//     return "$1$hfT7jp2q$" + to64_tripleGroup(hash, 0, 6, 12) + to64_tripleGroup(hash, 1, 7, 13)
//      +to64_tripleGroup(hash, 2, 8, 14)
//      +to64_tripleGroup(hash, 3, 9, 15)
//      +to64_tripleGroup(hash, 4, 10, 5)
//      +to64_singleGroup(hash, 11);
}
//==========================================================================================
string generateHash(string password, string salt, string magic)
{
    string intermediate = intermediateZero(password, salt, magic);
    string convertedintermediate = "";
    for (int i = 0; i < intermediate.length()-1; i+=2){
        //substr4 = substr4 + "" + alternatesum.at(i);
        string hexVal = intermediate.substr(i, 2);
        char hexVal_array[hexVal.length()+1];
        strcpy(hexVal_array, hexVal.c_str());
        int characternum = (int)(strtol(hexVal_array, NULL , 16));
        unsigned char character = (unsigned char)(characternum);
        //cout << "hex " << alternatesum_array[i] << alternatesum_array[i+1]<< endl;
        //printf("%02x", character);
        //cout << endl << "character " << character << endl;
        //cout << "number " << characternum << endl;
        //cout << "number " << (int)strtol(alternatesum_array, NULL, 16) << endl;
        convertedintermediate += character;
    }
    string sample = "";
    for(int i = 0; i < 1000; i++) {
        if(i%2 == 0) sample += convertedintermediate;
        //if(i%2 == 1) sample += password;
        else sample += password;
        if(i%3 != 0) sample += salt;
        if(i%7 != 0) sample += password;
        if(i%2 == 0) sample += password;
        //if(i%2 == 1) sample += intermediate;
        else sample += convertedintermediate;
        //HASH FUNCTION (sample);
        if (i == 0){
            cout << "sample " << sample << endl;
        }
        //for (int i = 0; i < password.length(); i++){
        //substr4 = substr4 + "" + alternatesum.at(i);
        intermediate = md5(sample);
        if (i == 0 || i == 999) {
            cout << "intermediate " << i << " " << intermediate << endl;
        }
        convertedintermediate = "";
        
        for (int i = 0; i < intermediate.length()-1; i+=2){
            //substr4 = substr4 + "" + alternatesum.at(i);
            string hexval = intermediate.substr(i, 2);
            char hexval_array[hexval.length()+1];
            strcpy(hexval_array, hexval.c_str());
            unsigned int characternum = (unsigned int)(strtol(hexval_array, NULL , 16));
            unsigned char character = (unsigned char)(characternum);
            convertedintermediate += character;
        }
        sample = "";
      //  if (i == 999) cout << i << endl;
    }

    // cout << "intermediate loop 1000: " << intermediate << endl;
    // cout << "convertedIntermediate: " << convertedintermediate << endl;

    //  cout << "Length of converted: " << convertedintermediate.length() << endl;
    // cout << "intermed length: " << intermediate.length() << endl;
    // for (int i= 0; i < convertedintermediate.length(); i++){
    //    // if(convertedintermediate.at(i) == 'f') convertedintermediate.at(i) = '0';
    //    //cout << "Char value at " << i << ": " << static_cast<unsigned int>(convertedintermediate[i]) << endl;
    // //    cout << hex << static_cast<unsigned int>(convertedintermediate[i]);
    //     // printf("%02x", convertedintermediate.at(i));
    // }
    //cout << endl;
   
    return encryption(convertedintermediate);
}

void generatePassword (string salt, string magic, string correctHash, int start, int end){
    long long counter = 0;
    string result, resultHash;
    for (int i = start; i < end; i++){
        counter++;
        result = char(i);
        cout << "this is doge: " << result << endl;
        resultHash = generateHash(result, salt, magic);
        //cout << "1" << endl;
        cout << char(i) << endl;
        if (resultHash == correctHash){
            cout << "password is: " << result<<endl;
            return;
        }
        for (int j = 97; j < 123; j++){
            counter++;
            result += char(j);
            resultHash = generateHash(result, salt, magic);
            //cout << "2" << endl;
            cout << char(j) << endl;
            if (resultHash == correctHash){
                cout << "password is: " << result<<endl;
                return;
            }
            for (int k = 97; k < 123; k++){
                counter++;
                result += char(k);
                resultHash = generateHash(result, salt, magic);
                //cout << "3" << endl;
                cout << char(k) << endl;
                if (resultHash == correctHash){
                    cout << "password is: " << result<<endl;
                    return;
                }
                for (int f = 97; f < 123; f++){
                    counter++;
                    result += char(f);
                    resultHash = generateHash(result, salt, magic);
                    cout << char(f) << endl;
                    //cout << "4" << endl;
                    if (resultHash == correctHash){
                        cout << "password is: " << result<<endl;
                        return;
                    }
                    for (int d = 97; d < 123; d++){
                        counter++;
                        result += char(d);
                        resultHash = generateHash(result, salt, magic);
                        //cout << "5" << endl;
                        cout << char(d) << endl;
                        if (resultHash == correctHash){
                            cout << "password is: " << result<<endl;
                            return;
                        }
                        for (int s = 97; s < 123; s++){
                            counter++;
                            result += char(s);
                            //if(s < 123) {result += char(s+1);}
                            //else {result += char(122);}
                            resultHash = generateHash(result, salt, magic);
                            //cout << s+1 << endl;
                            //cout << char(s+1) << endl;
                            //cout << char(122) << endl;
                            cout << char(s) << endl;
                            
                            if (resultHash == correctHash){
                                //cout << "6 done" << endl;
                                cout << "password is: " << result<<endl;
                                return;
                            }
                            //cout << "Done 6" << endl;
                            cout << counter << endl;
                            result.pop_back();
                        }
                        //cout << "Done 5" << endl;
                        cout << counter << endl;
                        result.pop_back();
                    }
                    //cout << "Done 4" << endl;
                    cout << counter << endl;
                    result.pop_back();
                }
                //cout << "Done 3" << endl;
                cout << counter << endl;
                result.pop_back();
            }   
            //cout << "Done 2" << endl; 
            cout << counter << endl;
            result.pop_back();
        }
        
       // cout << "Done 1" << endl;
       cout << counter << endl;
       cout << char(i) << endl;
    } 
    cout << "FOR DONE" << endl;
}

int main() {
    string hash,salt,magic;
    salt = "hfT7jp2q";
    magic = "$1$";
    hash = "pZg4uQ9ur9356fohTDh9u/"; 
    // string randomhex = "0cc175b9c0f1b6a831c399e269772661";
    thread th1(generatePassword, salt, magic, hash, 97, 104);
    thread th2(generatePassword, salt, magic, hash, 104, 111);
    thread th3(generatePassword, salt, magic, hash, 111, 117);
    thread th4(generatePassword, salt, magic, hash, 117, 123);
    th1.join();
    th2.join();
    th3.join();
    th4.join();
    //cout << "Correct password is : " << generatePassword(salt,magic,hash) << endl;
    //cout << "hash " << generateHash("a", salt, magic) << endl;

}