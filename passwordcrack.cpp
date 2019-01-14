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
