#include <iostream>
#include "md5.h"
#include <string>
#include <vector>

using namespace std;

string intermediateZero (string password, string salt, string magic){
	string alternatesum = md5(password + salt + password);
	string substr4 = ""; //length(password) bytes of the Alternate sum, repeated as necessary
	for (int i = 0; i < password.length(); i++){
		substr4 += alternatesum.at(i);
	}
	string substr5 = ""; //for each bit in length(password), from low to high and stopping after...
    for (int i = password.length(); i != 0; i >>= 1){
        if (i & 1){
            substr5 += "\0";
        }
        else{
            substr5 += password.at(0);
        }
    }
    cout << "alternate sum " << alternatesum << endl;
    cout << "" + password + magic + salt + substr4 + substr5 << endl;
	return md5(password + "$1$" + salt + substr4 + substr5);
}


//==========================================================================================
string base64(int hash, int amount) {
    string pin = "";
    string b64="./0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    for(int i = amount; amount >= 0; --i) {
        cout << "hash value: " << hash << endl;
        pin += b64.at(hash & 0x3F);
        cout << endl << "hash char value: " << hash << endl;
        cout << endl << "base64 char value: " <<b64.at(hash & 0x3F) << endl;
        hash >>= 6;
    }
    // while(--amount >= 0) {
    //     pin += b64.at(hash & 0x3f);
    //     hash >>= 6;
    // }
    cout << "done with encode: "<< pin << endl;
    return pin;
}

string to64_tripleGroup(string hash, int first, int second, int third) {
    auto semi = (hash.at(first) << 16) | 
                (hash.at(second) << 8) |
                (hash.at(third));
    cout << "Value of triple Group: " << semi << endl;
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
        if (i == 999) cout << i << endl;
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