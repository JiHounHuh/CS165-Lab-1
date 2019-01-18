#include <iostream>
#include <string>
#include <vector>
#include <thread>


using namespace std;
void test(string correct, int start, int finish){
	string result = "";
	for (int i = start; i <= finish; i++){
		result+=char(i);
		if (result == correct){
			cout << "correct" << correct << " result " << result << endl;
			return;
		}

		for (int k = 97; k<= 122; k++){
			result+=char(k);
			if (result == correct){
				cout << "correct " << correct << " result " << result << endl;
				return;
				}
			for (int j = 97; j<= 122; j++){
				result+=char(j);
				if (result == correct){
					cout << "correct " << correct << " result " << result << endl;
					return;
				}
				for (int g = 97; g<= 122; g++){
					result+=char(g);
					if (result == correct){
						cout << "correct " << correct << " result " << result << endl;
						return;
					}
					for (int h = 97; h<= 122; h++){
							result+=char(h);
							if (result == correct){
								cout << "correct " << correct << " result " << result << endl;
								return;
							}
							for (int y = 97; y<= 122; y++){
									result+=char(y);
									if (result == correct){
										cout << "correct " << correct << " result " << result << endl;
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
		result.pop_back();
	}
	cout << "none " << start << endl;
}

int main(){
	// thread th1(test, "zad", 97, 103);
 //    thread th2(test, "zad", 104, 110);
 //    thread th3(test, "zad", 111, 116);
 //    thread th4(test, "zad", 117, 122);
 //    th1.join();
 //    th2.join();
 //    th3.join();
 //    th4.join();
	test("zad", 97, 122);
}