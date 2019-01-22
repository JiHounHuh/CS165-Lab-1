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
    unsigned int semi = ((static_cast<unsigned char>(hash.at(first))));
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
    }
    return encryption(convertedintermediate);
}

void generatePassword (string salt, string magic, string &correctHash, int start, int end){
    int counter = 0;
    clock_t time_a = clock();
    string result, resultHash;
    for (int i = start; i < end; i++){
        counter++;
        result = char(i);
        //cout << "computed: " << result << endl;
        resultHash = generateHash(result, salt, magic);
        if (correctHash == resultHash){
            cout << "password is: " << result<<endl;
            clock_t time_b = clock();
            unsigned int total_time_ticks = (unsigned int)(time_b - time_a);
            cout << "Completed " << counter << " iterations" << endl;
            double seconds = static_cast<double>(total_time_ticks) / CLOCKS_PER_SEC;
            cout << "Took: " << seconds << endl;
            cout << "Hash rate: " << counter / seconds << " hashes per second" << endl;
            return;
        }
        for (int j = 122; j > 96; j--){
            counter++;
            result += char(j);
            //cout << "computed: " << result << endl;
            resultHash = generateHash(result, salt, magic);
            if (correctHash == resultHash){
                cout << "password is: " << result<<endl;
                clock_t time_b = clock();
                unsigned int total_time_ticks = (unsigned int)(time_b - time_a);
                cout << "Completed " << counter << " iterations" << endl;
                double seconds = static_cast<double>(total_time_ticks) / CLOCKS_PER_SEC;
                cout << "Took: " << seconds << endl;
                cout << "Hash rate: " << counter / seconds << " hashes per second" << endl;
                return;
            }
            for (int k = 122; k > 96; k--){
                counter++;
                result += char(k);
                //cout << "computed: " << result << endl;
                resultHash = generateHash(result, salt, magic);
                //cout << "3" << endl;
              //  cout << char(k) << endl;
                if (correctHash == resultHash){
                    cout << "password is: " << result<<endl;
                    clock_t time_b = clock();
                    unsigned int total_time_ticks = (unsigned int)(time_b - time_a);
                    cout << "Completed " << counter << " iterations" << endl;
                    double seconds = static_cast<double>(total_time_ticks) / CLOCKS_PER_SEC;
                    cout << "Took: " << seconds << endl;
                    cout << "Hash rate: " << counter / seconds << " hashes per second" << endl;
                    return;
                }
                for (int f = 122; f > 96; f--){
                    counter++;
                    result += char(f);
                   //cout << "computed: " << result << endl;
                    resultHash = generateHash(result, salt, magic);
                  //  cout << char(f) << endl;
                    //cout << "4" << endl;
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
                    for (int d = 122; d > 96; d--){
                        counter++;
                        result += char(d);
                        //cout << "computed: " << result << endl;
                        resultHash = generateHash(result, salt, magic);
                        //cout << "5" << endl;
                     //   cout << char(d) << endl;
                        if (correctHash == resultHash){
                            cout << "password is: " << result<<endl;
                            clock_t time_b = clock();
                            unsigned int total_time_ticks = (unsigned int)(time_b - time_a);
                            cout << "Completed " << counter << " iterations" << endl;
                            double seconds = static_cast<double>(total_time_ticks) / CLOCKS_PER_SEC;
                            cout << "Took: " << seconds << endl;
                            cout << "Hash rate: " << counter / seconds << " hashes per second" << endl;
                            return;
                        }
                        for (int s = 122; s > 96; s--){
                            counter++;
                            
                            result += char(s);
                            //cout << "computed: " << result << endl;
                            //if(s < 123) {result += char(s+1);}
                            //else {result += char(122);}
                            resultHash = generateHash(result, salt, magic);
                            //cout << s+1 << endl;
                            //cout << char(s+1) << endl;
                            //cout << char(122) << endl;
                        //    cout << char(s) << endl;
                            
                            if (correctHash == resultHash){
                                //cout << "6 done" << endl;
                                cout << "password is: " << result<< endl;
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
}

int main() {
    string hash,salt,magic;
    salt = "hfT7jp2q";
    magic = "$1$";
    hash = "KqcshpOfHc7VFTtiIZHPe1"; 
    thread th1(generatePassword, salt, magic, hash, 97, 100);
    thread th2(generatePassword, salt, magic, hash, 100, 102);
    thread th3(generatePassword, salt, magic, hash, 102, 104);
    thread th4(generatePassword, salt, magic, hash, 104, 106);
    thread th5(generatePassword, salt, magic, hash, 106, 108);
    thread th6(generatePassword, salt, magic, hash, 108, 110);
    thread th7(generatePassword, salt, magic, hash, 110, 112);
    thread th8(generatePassword, salt, magic, hash, 112, 114);
    thread th9(generatePassword, salt, magic, hash, 114, 116);
    thread th10(generatePassword, salt, magic, hash, 116, 118);
    thread th11(generatePassword, salt, magic, hash, 118, 120);
    thread th12(generatePassword, salt, magic, hash, 120, 123);
    th1.join();
    th2.join();
    th3.join();
    th4.join();
    th5.join();
    th6.join();
    th7.join();
    th8.join();
    th9.join();
    th10.join();
    th11.join();
    th12.join();
}