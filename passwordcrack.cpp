#include <iostream>
#include "md5.h"
#include <string>

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

string generatePassword (string salt, string magic, string correctHash){
	for (int i = 97; i < 123; i++){
		result = "" + char(i);
		resultHash = generateHash(result, salt, magic);
		if (resultHash == correctHash){
			return result;
		}
		for (int j = 97; j < 123; j++){
			result += char(j);
			resultHash = generateHash(result, salt, magic);
			if (resultHash == correctHash){
				return result;
			}
			for (int k = 97; k < 123; k++){
				result += char(k);
				resultHash = generateHash(result, salt, magic);
				if (resultHash == correctHash){
					return result;
				}
				for (int f = 97; f < 123; f++){
					result += char(f);
					resultHash = generateHash(result, salt, magic);
					if (resultHash == correctHash){
						return result;
					}
					for (int d = 97; d < 123; d++){
						result += char(d);
						resultHash = generateHash(result, salt, magic);
						if (resultHash == correctHash){
							return result;
						}
						for (int f = 97; f < 123; f++){
							result += char(f);
							resultHash = generateHash(result, salt, magic);
							if (resultHash == correctHash){
								return result;
							}
						}
					}
				}
			}		
		}
	}
}
