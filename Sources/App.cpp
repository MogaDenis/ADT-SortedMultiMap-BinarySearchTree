#include <iostream>

#include "../Headers/ShortTest.h"
#include "../Headers/ExtendedTest.h"

int main(){
    testAll();
	testAllExtended();

    std::cout<<"Finished SMM Tests!"<<std::endl;

    testGetKeyRange();
    std::cout << "Bonus requirement test passed\n";
	// system("pause");
}
