#include "Driver.h"
#include<iostream>
#include"Expression.h"
#include "Number.h"
#include "Helper.h"
#include "Fraction.h"
#include<vector>

using namespace std;

int main() {
    //Integer* isInt = dynamic_cast<Number*>(base);
    //string str = "3+((-3)/4)";
    //string str = "250e";
	//string str = "2+5/6*8-(5/2)*78";
	//Expression* calc = new Expression(str);
	//calc->testmeth(str);
       // string temp = calc->shunting(str);
		//cout << temp << endl;
	//cout << calc->evaluate(temp) << endl;
                //Irrational* i = new Irrational("260pi");
	//calc->getinput();
	//Fraction* f = new Fraction("256/5634");
    //string s = "25";
    //string t = "log_3:9";
    //HelperFunctions* h = new HelperFunctions(s);
    //HelperFunctions* i = new HelperFunctions(t);
//    Fraction* in = new Fraction("4390/3530");
    //vector<int> factors = in->primeFactorization();
		Fraction* f = new Fraction("3/7");
		Integer* i = new Integer("5");
		vector<Number*> vec;
		vec.push_back(f);
		vec.push_back(i);
		stack<Number*> stack;
		
}
/*double Driver::fractionToDecimal(string input) {

}
*/
