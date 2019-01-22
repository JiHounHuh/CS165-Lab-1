#include <iostream>
#include "md5.h"
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cstdio>
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
       // printf("%02x", character);
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
string base64(unsigned int &hash, int amount) {
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

string to64_tripleGroup(string &hash, unsigned int first, unsigned int second, unsigned int third) {
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

string to64_singleGroup(string &hash, unsigned int first) {
    unsigned int semi = hash.at(first);
    return base64(semi, 2);
}


string encryption(string &hash) {
    //cout << endl;
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
string generateHash(string &password, string &salt, string &magic)
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
        // if (i == 0){
        //     cout << "sample " << sample << endl;
        // }
        //for (int i = 0; i < password.length(); i++){
        //substr4 = substr4 + "" + alternatesum.at(i);
        intermediate = md5(sample);
        // if (i == 0 || i == 999) {
        //     cout << "intermediate " << i << " " << intermediate << endl;
        // }
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
void generatePassword1(string salt, string magic, string correctHash){
    int counter = 0;
    clock_t time_a = clock();
    string result, resultHash;
    for (int i = 97; i < 123; i++){   //check passwords of 1 character
        result  = char(i);
        resultHash = generateHash(result, salt, magic);
        if (resultHash == correctHash){
            cout << "password is: " << result<<endl;
            clock_t time_b = clock();
            unsigned int total_time_ticks = (unsigned int)(time_b - time_a);
            cout << "Completed " << counter << " iterations" << endl;
            double seconds = static_cast<double>(total_time_ticks) / CLOCKS_PER_SEC;
            cout << "Took: " << seconds << endl;
            cout << "Hash rate: " << counter / seconds << " hashes per second" << endl;
            return;
        }
    }
    cout << "password is more than 1 char long" << endl;
    return;
}

void generatePassword2(string salt, string magic, string correctHash){
    int counter = 0;
    clock_t time_a = clock();
    string result, resultHash;
    

    for (int i = 97; i < 123; i++){   //check passwords of 2 character
        result  = char(i);
        for(int j = 97; j < 123; j++){
            result += char(j);
            resultHash = generateHash(result, salt, magic);
            if (resultHash == correctHash){
                cout << "password is: " << result<<endl;
                clock_t time_b = clock();
                unsigned int total_time_ticks = (unsigned int)(time_b - time_a);
                cout << "Completed " << counter << " iterations" << endl;
                double seconds = static_cast<double>(total_time_ticks) / CLOCKS_PER_SEC;
                cout << "Took: " << seconds << endl;
                cout << "Hash rate: " << counter / seconds << " hashes per second" << endl;
                return;
            }
            result.pop_back();
        }
        result.pop_back();
    }
    cout << "password is more than 2 char long" << endl;
    return;
}

void generatePassword3(string salt, string magic, string correctHash){
    int counter = 0;
    clock_t time_a = clock();
    string result, resultHash;
    

    for (int i = 97; i < 123; i++){   //check passwords of 3 character
        result  = char(i);
        for(int j = 97; j < 123; j++){
            result += char(j);
            for (int k = 97; k < 123; k++){
                result += char(k);
                resultHash = generateHash(result, salt, magic);
                if (resultHash == correctHash){
                    cout << "password is: " << result<<endl;
                    clock_t time_b = clock();
                    unsigned int total_time_ticks = (unsigned int)(time_b - time_a);
                    cout << "Completed " << counter << " iterations" << endl;
                    double seconds = static_cast<double>(total_time_ticks) / CLOCKS_PER_SEC;
                    cout << "Took: " << seconds << endl;
                    cout << "Hash rate: " << counter / seconds << " hashes per second" << endl;
                    return;
                }
                result.pop_back();
            }
            result.pop_back();
        }
        result.pop_back();
    }
    cout << "password is more than 3 char long" << endl;
    return;
}

void generatePassword4(string salt, string magic, string correctHash, int start, int end){
    int counter = 0;
    clock_t time_a = clock();
    string result, resultHash;
    

    for (int i = start; i < end; i++){   //check passwords of 4 character
        result  = char(i);
        for(int j = 97; j < 123; j++){
            result += char(j);
            for (int k = 97; k < 123; k++){
                result += char(k);
                for (int d = 97; d < 123; d++){
                    result+= char(d);
                    resultHash = generateHash(result, salt, magic);
                    if (resultHash == correctHash){
                        cout << "password is: " << result<<endl;
                        clock_t time_b = clock();
                        unsigned int total_time_ticks = (unsigned int)(time_b - time_a);
                        cout << "Completed " << counter << " iterations" << endl;
                        double seconds = static_cast<double>(total_time_ticks) / CLOCKS_PER_SEC;
                        cout << "Took: " << seconds << endl;
                        cout << "Hash rate: " << counter / seconds << " hashes per second" << endl;
                        return;
                    }
                    result.pop_back();
                }
                result.pop_back();
            }
            result.pop_back();
        }
        result.pop_back();
    }
    cout << "password is more than 4 char long" << endl;
    return;
}

void generatePassword5 (string salt, string magic, string correctHash, int start, int end){
    int counter = 0;
    clock_t time_a = clock();
    string result, resultHash;
    

    for (int i = start; i < end; i++){   //check passwords of 5 character
        result  = char(i);
        for(int j = 97; j < 123; j++){
            result += char(j);
            for (int k = 97; k < 123; k++){
                result += char(k);
                for (int d = 97; d < 123; d++){
                    result+= char(d);
                    for (int s = 97; s < 123; s++){
                        result += char(s);
                        resultHash = generateHash(result, salt, magic);
                        if (resultHash == correctHash){
                            cout << "password is: " << result<<endl;
                            clock_t time_b = clock();
                            unsigned int total_time_ticks = (unsigned int)(time_b - time_a);
                            cout << "Completed " << counter << " iterations" << endl;
                            double seconds = static_cast<double>(total_time_ticks) / CLOCKS_PER_SEC;
                            cout << "Took: " << seconds << endl;
                            cout << "Hash rate: " << counter / seconds << " hashes per second" << endl;
                            return;
                        }
                        result.pop_back();
                    }
                    result.pop_back();
                }
                result.pop_back();
            }
            result.pop_back();
        }
        result.pop_back();
    }
    cout << "password is more than 5 char long" << endl;
    return;
}

void generatePassword6 (string salt, string magic, string correctHash, int start, int end){
    int counter = 0;
    clock_t time_a = clock();
    string result, resultHash;
    

    for (int i = start; i < end; i++){      //check for 6 character
        result = char(i);
        for (int j = 97; j < 123; j++){
            result += char(j);
            for (int k = 97; k < 123; k++){
                result += char(k);
                for (int f = 97; f < 123; f++){
                    result += char(f);
                    for (int d = 97; d < 123; d++){
                        result += char(d);
                        for (int s = 97; s < 123; s++){
                            result += char(s);
                            //if(s < 123) {result += char(s+1);}
                            //else {result += char(122);}
                            resultHash = generateHash(result, salt, magic);
                            //cout << s+1 << endl;
                            //cout << char(s+1) << endl;
                            //cout << char(122) << endl;
                        //    cout << char(s) << endl;
                            
                            if (resultHash == correctHash){
                                //cout << "6 done" << endl;
                                cout << "password is: " << result<<endl;
                                clock_t time_b = clock();
                                unsigned int total_time_ticks = (unsigned int)(time_b - time_a);
                                cout << "Completed " << counter << " iterations" << endl;
                                double seconds = static_cast<double>(total_time_ticks) / CLOCKS_PER_SEC;
                                cout << "Took: " << seconds << endl;
                                cout << "Hash rate: " << counter / seconds << " hashes per second" << endl;
                                
                                return;
                            }
                            //cout << "Done 6" << endl;
                      //      cout << counter << endl;
                            result.pop_back();
                        }
                        //cout << "Done 5" << endl;
                      //  cout << counter << endl;
                        result.pop_back();
                    }
                    //cout << "Done 4" << endl;
                 //   cout << counter << endl;
                    result.pop_back();
                }
                //cout << "Done 3" << endl;
              //  cout << counter << endl;
                result.pop_back();
            }   
            //cout << "Done 2" << endl; 
           // cout << counter << endl;
            result.pop_back();
        }
        
       // cout << "Done 1" << endl;
      // cout << counter << endl;
      // cout << char(i) << endl;
    } 
    cout << "FOR DONE" << endl;
    return;
}

int main() {
    string hash,salt,magic;
    salt = "hfT7jp2q";
    magic = "$1$";
    hash = "mJpiQ6c5/hc6giQA.QSq.1"; 
    generatePassword1(salt, magic, hash);
    // string randomhex = "0cc175b9c0f1b6a831c399e269772661";
    //thread th1(generatePassword, salt, magic, hash, 97, 98);
    //thread th2(generatePassword, salt, magic, hash, 98, 99);
    // thread th3(generatePassword, salt, magic, hash, 99, 100);
    // thread th4(generatePassword, salt, magic, hash, 100, 101);
    // thread th5(generatePassword, salt, magic, hash, 101, 102);
    // thread th6(generatePassword, salt, magic, hash, 102, 103);
    // thread th7(generatePassword, salt, magic, hash, 103, 104);
    // thread th8(generatePassword, salt, magic, hash, 104, 105);
    // thread th9(generatePassword, salt, magic, hash, 105, 106);
    // thread th10(generatePassword, salt, magic, hash, 106, 107);
    // thread th11(generatePassword, salt, magic, hash, 107, 108);
    // thread th12(generatePassword, salt, magic, hash, 108, 109);
    // thread th13(generatePassword, salt, magic, hash, 109, 110);
    // thread th14(generatePassword, salt, magic, hash, 110, 111);
    // thread th15(generatePassword, salt, magic, hash, 111, 112);
    // thread th16(generatePassword, salt, magic, hash, 112, 113);
    // thread th17(generatePassword, salt, magic, hash, 113, 114);
    // thread th18(generatePassword, salt, magic, hash, 114, 115);
    // thread th19(generatePassword, salt, magic, hash, 115, 116);
    // thread th20(generatePassword, salt, magic, hash, 116, 117);
    // thread th21(generatePassword, salt, magic, hash, 117, 118);
    // thread th22(generatePassword, salt, magic, hash, 118, 119);
    // thread th23(generatePassword, salt, magic, hash, 119, 120);
    // thread th24(generatePassword, salt, magic, hash, 120, 121);
    // thread th25(generatePassword, salt, magic, hash, 121, 122);
    // thread th26(generatePassword, salt, magic, hash, 122, 123);
    //th1.join();
    //th2.join();
    // th3.join();
    // th4.join();
    // th5.join();
    // th6.join();
    // th7.join();
    // th8.join();
    // th9.join();
    // th10.join();
    // th11.join();
    // th12.join();
    // th13.join();
    // th14.join();
    // th15.join();
    // th16.join();
    // th17.join();
    // th18.join();
    // th19.join();
    // th20.join();
    // th21.join();
    // th22.join();
    // th23.join();
    // th24.join();
    // th25.join();
    // th26.join();
    //cout << "Correct password is : " << generatePassword(salt,magic,hash) << endl;
    //cout << "hash " << generateHash("a", salt, magic) << endl;

}