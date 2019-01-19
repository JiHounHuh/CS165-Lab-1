#include <iostream>
#include "md5.h"
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

string intermediateZero (string password, string salt, string magic){
	string alternatesum = md5( password + salt + password);
    // char alternatesum_array[alternatesum.length()+1];
    // strcpy(alternatesum_array, alternatesum.c_str());
    // for (int i = 0; i < 33; i++){
    //     cout << alternatesum_array[i] << endl;
    // }
    //string alternatesum = md5("" + password + salt + password);
	string substr4 = ""; //length(password) bytes of the Alternate sum, repeated as necessary
	for (int i = 0; i < password.length(); i+=2){
		//substr4 = substr4 + "" + alternatesum.at(i);
        string subalternatesum = alternatesum.substr(i, 2);
        char alternatesum_array[subalternatesum.length()+1];
        strcpy(alternatesum_array, subalternatesum.c_str());
        char character = char((int)strtol(alternatesum_array, NULL , 16));
        //cout << "hex " << alternatesum_array[i] << alternatesum_array[i+1]<< endl;
        printf("%c\n", 198);
        cout << "character " << ((char)198) << endl;
        cout << "number " << (int)strtol(alternatesum_array, NULL, 16) << endl;
        substr4 += character;
	}
	string substr5 = ""; //for each bit in length(password), from low to high and stopping after...
	//int counter = 1;
	//int num = 2;
	// while (counter < password.length()){
	// 	int mask = 1 << num;
	// 	int isolatebit = ((password.length() >> 2-num) << num) & mask;
	// 	if (isolatebit == 1){
	// 		substr5 = substr5 + "\0"; 
	// 	}
	// 	else{
	// 		substr5 = substr5 + "" + password.at(0);
	// 	}
	// 	counter  = counter + counter<<1;
	// 	num--;
	// }
    for (int i = password.length(); i != 0; i >>= 1){
        if (i & 1){
            substr5 += "\0";
        }
        else{
            substr5 += password.at(0);
        }
    }
    string everything = "" + password + magic + salt + substr4 + substr5;
    for (int i= 0; i < everything.length(); i++){
        printf("%02x", everything.at(i));
    }
    cout << endl << "alternate sum " << alternatesum << endl;
    cout << password + magic + salt + substr4 + substr5 << endl;
    cout << "intermediate 0: " << md5(password + magic + salt + substr4 + substr5) << endl;
	return md5(password + magic + salt + substr4 + substr5);
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
       // cout << j << endl;
    }
  //  cout << "Bitch" << endl;
    return bitch;
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

string encodeBase(string hash) {
   // int len;
    //len = 16;
    string hexed = "";
    int place = 0;
    vector<string> death;
    static const int crypt[] = {11,4,10,5,3,9,15,2,8,14,1,7,13,0,6,12};
   
   //cout << hash << endl;
    //static const int crypt[] = {11,4,10,5,3,9,15,2,8,14,1,7,13,0,6,12};
    //vector<int> crypt = {11, 4, 10, 5, 3, 9, 15, 2, 8, 14, 1, 7, 13, 0, 6, 12};
    //vector<int> crypt (arr, arr + sizeof(arr) / sizeof(arr[0]));
    
    string bin = "";
    for(int p = 0; p < hash.length(); p++) {
      //  cout << "Hello" << endl;
        bin += hexToBin(hash.at(p));
      //  cout << "Bye" << endl;
    }
    for(int j = 7; j < bin.length(); j+= 8) {
       death.push_back(bin.substr(j-7,8));
   }
    for(int test = 0; test < 16; test++) {
        //cout << test << endl;
        //cout << death.size() << endl;
        hexed += death.at(crypt[test]);
       // cout << hexed << endl;
    }
   // cout << "after" << endl;
    return binToB64(hexed);
}
//==========================================================================================
string base64(int hash, int amount) {
    string pin = "";
    string b64="./0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
     int test = hash & 0x3f;
    for(; amount >= 0; --amount) {
        cout << "hash value: " << hash << endl;
       
        cout << "hash plus something: " << test << endl;
        pin += b64.at(hash & 0x3f);
        //hash = (hash >> 6);
        hash >>= 6;
    }
    // while(--amount >= 0) {
    //     pin += b64.at(hash & 0x3f);
    //     hash = (hash >> 6);
    // }
    cout << "done with encode: "<< pin << endl;
    return pin;
}

string to64_tripleGroup(string hash, int first, int second, int third) {
    int semi = (hash.at(first) << 16) | 
                (hash.at(second) << 8) |
                (hash.at(third));
    cout << "Hash String: " << hash << endl;
    cout << "triple value: " << (hash.at(first) << 16) << endl;
    return base64(semi, 4);
}

string to64_singleGroup(string hash, int first) {
    int semi = hash.at(first);
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

//     return to64_tripleGroup(hash, 0,  6, 12) +
//    to64_tripleGroup(hash, 1,  7, 13) +
//    to64_tripleGroup(hash, 2,  8, 14) +
//    to64_tripleGroup(hash, 3,  9, 15) +
//    to64_tripleGroup(hash, 4, 10,  5) +
//    to64_singleGroup(hash, 11);
   //  11 | 4 10 5 | 3 9 15 | 2 8 14 | 1 7 13 | 0 6 12
}
//==========================================================================================
string generateHash(string password, string salt, string magic)
{
    string intermediate = intermediateZero(password, salt, magic);
    // cout << "Intermediate: " << intermediate << endl;

    // cout << endl;
    // cout << endl;
    // cout << endl;
    // cout << endl;
    // cout << endl;
    // cout << endl;
    // cout << endl;
    // cout << endl;
    // cout << endl;
    //string dummy = md5(sample);
    //cout << "Intermediate Hashed: " << md5(intermediate) << endl;
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
      //  if (i == 999) cout << i << endl;
    }
    //string checkup= "";
   // checkup = encodeBase(intermediate);
   //cout << encodeBase(intermediate) << endl;
    //return intermediate;
    cout << "intermediate loop 1000: " << intermediate << endl;
    return encryption(intermediate);
    //return encodeBase(intermediate);
  //  cout << "encodeBase" << endl;
    //return checkup;
}

string generatePassword (string salt, string magic, string correctHash){
    long long counter = 0;
    string result, resultHash;
	for (int i = 97; i < 123; i++){
        counter++;
		result = "" + char(i);
		resultHash = generateHash(result, salt, magic);
        //cout << "1" << endl;
        cout << char(i) << endl;
		if (resultHash == correctHash){
			return result;
		}
		for (int j = 97; j < 123; j++){
            counter++;
			result += char(j);
			resultHash = generateHash(result, salt, magic);
            //cout << "2" << endl;
            cout << char(j) << endl;
			if (resultHash == correctHash){
				return result;
			}
			for (int k = 97; k < 123; k++){
                counter++;
				result += char(k);
				resultHash = generateHash(result, salt, magic);
                //cout << "3" << endl;
                cout << char(k) << endl;
				if (resultHash == correctHash){
					return result;
				}
				for (int f = 97; f < 123; f++){
                    counter++;
					result += char(f);
					resultHash = generateHash(result, salt, magic);
                    cout << char(f) << endl;
                    //cout << "4" << endl;
					if (resultHash == correctHash){
						return result;
					}
					for (int d = 97; d < 123; d++){
                        counter++;
						result += char(d);
						resultHash = generateHash(result, salt, magic);
                        //cout << "5" << endl;
                        cout << char(d) << endl;
						if (resultHash == correctHash){
							return result;
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
								return result;
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
    //cout << "FOR DONE" << endl;
}

int main() {
    string hash,salt,magic;
    salt = "hfT7jp2q";
    magic = "$1$";
    hash = "pZg4uQ9ur9356fohTDh9u/"; 
    string randomhex = "0cc175b9c0f1b6a831c399e269772661";
    //cout << "Correct password is : " << generatePassword(salt,magic,hash) << endl;
    cout << "hash " << generateHash("a", salt, magic) << endl;

}