#include "Irrational.h"
Irrational::Irrational() {

   }
Irrational::Irrational(string str) {
    int i = 0;
    string num;
    int temp;
    while(i < str.length()) {
         if(istringstream(str.substr(i, 1)) >> temp) {
            num += str[i];
            i++;
        }
         else if(!(istringstream(str.substr(i, 1)) >> temp)) {
            if((str[i] == 'p' && str[i+1] == 'i') || (str[i] == 'P' && str[i+1] == 'i') || (str[i] == 'p' && str[i+1] == 'I') || (str[i] == 'P' && str[i+1] == 'I')) {
                num += "pi";
                }
            else if(str.compare("e") == 0 || str.compare("E") == 0) {
                num += "e";
                }
            i = str.length();
         }
    }
    cout << num << endl;
}
string Irrational::addSubtractPi() {

}
string Irrational::multiplyPi() {

}
string Irrational::addSubtractE() {

}
string Irrational::multiplyE() {

}

