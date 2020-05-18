//Iyobed Zekarias
//Reverse Number

#include <iostream>
#include <string>
#include <math.h>

using namespace std;
int main(){

    int digit;
    int rdigit = 0;
    cout << "This program reverses the digits of an integer."  << endl << endl;

    cout << "Enter an integer: ";

    cin >> digit;

    int digit_length = 0;
    int x = digit;

   for(; x != 0; x /= 10, digit_length++);

    while(true){
        if(digit == 0){
            break;
        }
        int mod = digit % 10;
        digit = digit / 10;
    
        rdigit = rdigit + (mod * pow(10, (digit_length - 1)));
        --digit_length;
    
        if(digit_length == 0)
            break;
     }

    cout << "The reversed number is " << rdigit << "." << endl;
}

