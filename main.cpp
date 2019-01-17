#include <iostream>
#include "md5.h"
#include <string>
#include <vector>

using namespace std;

string intermediateZero (string password, string salt, string magic){
	string alternatesum = md5(password + salt + password);
	string substr4 = ""; //length(password) bytes of the Alternate sum, repeated as necessary
	for (int i = 0; i < password.length(); i++){
		substr4 = substr4 + "" + alternatesum.at(i);
	}
	string substr5 = ""; //for each bit in length(password), from low to high and stopping after...
	int counter = 1;
	int num = 2;
	while (counter < password.length()){
		int mask = 1 << num;
		int isolatebit = ((password.length() >> 2-num) << num) & mask;
		if (isolatebit == 1){
			substr5 = substr5 + "\0"; 
		}
		else{
			substr5 = substr5 + "" + password.at(0);
		}
		counter  = counter + counter<<1;
		num--;
	}
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
    int len;
    len = 16;
    string hexed = "";
    static const int crypt[] = {11,4,10,5,3,9,15,2,8,14,1,7,13,0,6,12};
    //vector<int> crypt = {11, 4, 10, 5, 3, 9, 15, 2, 8, 14, 1, 7, 13, 0, 6, 12};
    //vector<int> crypt (arr, arr + sizeof(arr) / sizeof(arr[0]));


    for(int test = 0; test < 16; test++) {
        //cout << test << endl;
        hexed.push_back(hash.at(crypt[test]));
       // cout << hexed << endl;
    }
    string bin = "";
    for(int p = 0; p < hexed.length(); p++) {
      //  cout << "Hello" << endl;
        bin += hexToBin(hexed.at(p));
      //  cout << "Bye" << endl;
    }
   // cout << "after" << endl;
    return binToB64(bin);
}

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
    }
    //string checkup= "";
   // checkup = encodeBase(intermediate);
    return encodeBase(intermediate);
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
		if (resultHash == correctHash){
			return result;
		}
		for (int j = 97; j < 123; j++){
            counter++;
			result += char(j);
			resultHash = generateHash(result, salt, magic);
            //cout << "2" << endl;
			if (resultHash == correctHash){
				return result;
			}
			for (int k = 97; k < 123; k++){
                counter++;
				result += char(k);
				resultHash = generateHash(result, salt, magic);
                //cout << "3" << endl;
				if (resultHash == correctHash){
					return result;
				}
				for (int f = 97; f < 123; f++){
                    counter++;
					result += char(f);
					resultHash = generateHash(result, salt, magic);
                    //cout << "4" << endl;
					if (resultHash == correctHash){
						return result;
					}
					for (int d = 97; d < 123; d++){
                        counter++;
						result += char(d);
						resultHash = generateHash(result, salt, magic);
                        //cout << "5" << endl;
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
    hash = "KqcshpOfHc7VFTtiIZHPe1"; 
    cout << "Correct password is : " << generatePassword(salt,magic,hash) << endl;

}