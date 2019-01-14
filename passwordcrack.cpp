#include <iostream>
#include "md5.h"
#include <string>



string intermediateZero (string pasword, string salt, string magic){
	string alternatesum = md5(password + salt + password);
	string substr4 = ""; //length(password) bytes of the Alternate sum, repeated as necessary
	for (int i = 0; i < password.length(); i++){
		substr4 = "" + alternatesum.at(i);
	}
	string substr5 = ""; //for each bit in length(password), from low to high and stopping after...
	int counter = 0;
	int shiftval = 0;
	while (counter < password.length()){
		int mask = 1 << 0;

	}
}