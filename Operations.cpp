#include <iostream>
#include <string>
#include <sstream>
#include <exception>
//#include "Add.h"
using namespace std;
class invalidIrrational: public exception {
  virtual const char* what() const throw()
  {
    return "You have entered an invalid irrational number";
  }
} invalidIrr;
int gcd(int a, int b) { 
    if (b==0) {
        return a; 
    }
    return gcd(b, a % b); 
} 
string simplifyLog(int base, int num) {
    //if the left log can be simplified to an int
          //if the fractions can be simplified
            int d, ans;
            int gcf = 1;
            d = gcd(base, num);
          //if the number is greater than the base
          if(d != 1 && num > base) {
              int j = 0;
              while(num > 1) {
                  num /= d;
                  gcf *= d;
                  j++;
              }
              if(gcf == num)
                  if(num == 1) {
                      ostringstream ans;
                      ans << j;
                      return ans.str();
                  }
                  else {
                      gcf /= d;
                      num /= gcf;
                      ostringstream b;
                      ostringstream n;
                      b << base;
                      n << num;
                      return "log_" + b.str() + ":" + n.str();
                  }
          }
          else {
              ostringstream b;
              ostringstream n;
              b << base;
              n << num;
              return "log_" + b.str() + ":" + n.str();
          }

          
}
bool isNegative(string str) {
	if (str[0] == '-') {
		return true;
	}
	return false;
}
bool isIrrational(string str) {
    int i = 0;
    int num;
    while(i < str.length()) {
        if(!(istringstream(str.substr(i, 1)) >> num)) {
            if(str.find("pi") < str.length() || str.find("pI") < str.length() || str.find("Pi") < str.length() || str.find("PI") < str.length()) {
                return true;
                }
            else if(str.find("e") < str.length() || str.find("E") < str.length()) {
                return true;
                }
            else {

                return false;
                }
            }
        else if(istringstream(str.substr(i, 1)) >> num) {
            i++;
        }
    }
}
bool isInteger(string str) {
    string::const_iterator it = str.begin();
	char neg = '-';
    while (it != str.end() && ((std::isdigit(*it))||((*it) == '-'))) ++it;
    return !str.empty() && it == str.end();
}
bool isFraction(string str) {
    int i = 0;
       if((str.find('/') < str.length()) && !((str.find('-') < str.length()) && !isNegative(str)) && !(str.find('+') < str.length()) && !(str.find('*') < str.length())) {
           return true;
        }
		return false;
}
bool isPolynomial(string str) {
    if(!isFraction(str) && (str.find('/')< str.length())) {
		return true;
	}
	if(!isNegative(str) && str.find('-')< str.length()) {
		return true;
	}
	if(str.find('+') < str.length()) {
		return true;
	}
	if(str.find('c') < str.length()) {
		return true;
	}
		return false;
}
bool isLog(string str) {
    if(!isPolynomial(str) && (str.find("log") < str.length())) {
        return true;
    }
	return false;
}
bool isPi(string str) {
    int i = 0;
    while(i < str.length()) {
        if((str[i] == 'p' && str[i+1] == 'i') || (str[i] == 'P' && str[i+1] == 'i') || (str[i] == 'p' && str[i+1] == 'I') || (str[i] == 'P' && str[i+1] == 'I')) {
            return true;
         }
        i++;
    }
}
bool isE(string str) {
    int i = 0;
    while(i < str.length()) {
        if(str[i] == 'e' || str[i] == 'E') {
            return true;
        }
        i++;
    }
}
string add(string left, string right) {
    string leftCoefficient, rightCoefficient,leftExponent,rightExponent, finalC, answer, simplifiedLeft, simplifiedRight;
    int leftC, rightC, final, leftIndex, rightIndex, originalLength, leftO, rightO;
    //checks if the left and right operands are of the same type
    if((isIrrational(left) && isIrrational(right)) || (isFraction(left) && isFraction(right)) || (isInteger(left) && isInteger(right)) || (isLog(left) && isLog(right)) || (isPolynomial(left) && isPolynomial(right))) {
        //Dealing with Irrational Numbers
        if(isIrrational(left)) {
            int i = 0;
            leftCoefficient = "";
            leftExponent = "";
            int temp;
            originalLength = left.length();
            while(i < left.length()) {
                if(istringstream(left.substr(i, 1)) >> temp) {
                    leftCoefficient += left[i];

                }
                else {
                    break;     
                }
                i++;
            }
            if(leftCoefficient == ""){
                 leftCoefficient = "1";
            }
            i = 0;
            rightCoefficient = "";
            rightExponent = "";
            while(i < right.length()) {
                 if(istringstream(right.substr(i, 1)) >> temp) {
                    rightCoefficient += right[i];

                }
                else {
                  break;
                }
                 i++;
             }
             if(rightCoefficient == ""){
                 rightCoefficient = "1";
             }
            istringstream(leftCoefficient) >> leftC;
            istringstream(rightCoefficient) >> rightC;
            //adds the coefficients
            final = leftC + rightC;
            //converts coefficient to string
            ostringstream temporary;
            temporary << final;
            finalC = temporary.str();
            //if both operands contain pi
           if(isPi(left) && isPi(right)) {
               while(i < left.length()) {
                         if(left.substr(i, 1) == "^") {
                             while(i < left.length()) {
                                 leftExponent += left[i+1];
                                 i++;
                             }
                         }
                         i++;
                 }
                 i =0;
                 while(i < right.length()) {
                         if(right.substr(i, 1) == "^") {
                             while(i < right.length()) {
                                 rightExponent += right[i+1];
                                 i++;
                             }
                         }
                         i++;
                 }
                 if((leftExponent == rightExponent) && !(leftExponent == "" && rightExponent == "")) {
                         answer = finalC + "pi" + "^" + leftExponent;
                 }
                 else if((leftExponent == rightExponent) && (leftExponent == "" && rightExponent == "")){
                         answer = finalC + "pi";
                 }
                 else
                     answer = left + " + " + right;
            }
            //if both operands contain e
            else if(isE(left) && isE(right)) {
                while(i < left.length()) {
                         if(left.substr(i, 1) == "^") {
                             while(i < left.length()) {
                                 leftExponent += left[i+1];
                                 i++;
                             }
                         }
                         i++;
                 }
                 i =0;
                 while(i < right.length()) {
                         if(right.substr(i, 1) == "^") {
                             while(i < right.length()) {
                                 rightExponent += right[i+1];
                                 i++;
                             }
                         }
                         i++;
                 }
                 if((leftExponent == rightExponent) && !(leftExponent == "" && rightExponent == "")) {
                         answer = finalC + "e" + "^" + leftExponent;
                 }
                 else if((leftExponent == rightExponent) && (leftExponent == "" && rightExponent == "")){
                         answer = finalC + "e";
                 }
                 else
                     answer = left + " + " + right;
            }
            //if the operands cannot be added and simplified, concatenate them
            else if(isPi(left) && isE(right) || isE(left) && isPi(right)) {
                answer = left + " + " + right;
            }
            else {
                throw invalidIrr;
            }
        }
        //Dealing with logs
        else if(isLog(left)) {
          string leftBase, rightBase, leftNum, rightNum, final;
          int i = 4;
          //Specified base for the log
          if(left[3] == '_' ) {
              while(left[i] != ':') {
                  leftBase += left[i];
                  i++;
              }
              i++;
              while(i <= left.length()-1) {
                  leftNum += left[i];
                  i++;
              }
          }
          //This is log base 10
          else if(left[3] == ':') {
              leftBase = "10";
              while(i <= left.length()-1) {
                  leftNum += left[i];
                  i++;
              }
          }
          i = 4;
          if(right[3] == '_' ) {
              while(right[i] != ':') {
                  rightBase += right[i];
                  i++;
              }
              i++;
              while(i <= right.length()-1) {
                  rightNum += right[i];
                  i++;
              }
          }
          //This is log base 10
          else if(right[3] == ':') {
              rightBase = "10";
              while(i <= right.length()-1) {
                  rightNum += right[i];
                  i++;
              }
          }
          int num, tempLeft, tempRight, tempLNum, tempRNum;
          istringstream(leftBase) >> tempLeft;
          istringstream(rightBase) >> tempRight;
          istringstream(leftNum) >> tempLNum;
          istringstream(rightNum) >> tempRNum;
          //simplifies the logs to numbers if possible. 
          //if the log cannot be simplified it will return the log as it was. 
          simplifiedLeft = simplifyLog(tempLeft, tempLNum);
          simplifiedRight = simplifyLog(tempRight, tempRNum);
          if(isInteger(simplifiedLeft)) {
              left = simplifiedLeft;
              istringstream(left) >> leftO;
          }
          if(isInteger(simplifiedRight)) {
              right = simplifiedRight;
              istringstream(left) >> rightO;
          }
          num = tempLNum * tempRNum;
          if(isInteger(simplifiedLeft) && isInteger(simplifiedRight)) {
              answer = leftO - rightO;
          }
          else if(!isInteger(simplifiedLeft) && !isInteger(simplifiedRight)) {
              if(tempLeft == tempRight) {
                  string a = simplifyLog(tempLeft, num);
                  answer = a;
              }
              else {
                answer = left + " + " + right;
              }
          }
          else {
              answer = left + " + " + right;
          }
        }
        else if(isFraction(left)) {
            string numerator, denominator;
            int i =0;
            string topLeft, topRight, bottomLeft, bottomRight;
            int leftNum, rightNum, leftDenom, rightDenom, finalNum;
            while(left[i] != '/'){
                topLeft += left[i];
                i++;
            }
            i++;
            while(i < left.length()) {
                bottomLeft += left[i];
                i++;
            }
            i = 0;
            while(right[i] != '/'){
                topRight += right[i];
                i++;
            }
            i++;
            while(i < right.length()) {
                bottomRight += right[i];
                i++;
            }
            istringstream(topLeft) >> leftNum;
            istringstream(topRight) >> rightNum;
            istringstream(bottomLeft) >> leftDenom;
            istringstream(bottomRight) >> rightDenom;
            //if the fractions can be simplified
            int d, e;
            d = gcd(leftNum, leftDenom);
            leftNum /= d;
            leftDenom /= d;
            e = gcd(rightNum, rightDenom);
            rightNum /= e;
            rightDenom /= e;
            if(leftDenom == rightDenom) {
                finalNum = leftNum + rightNum;
                ostringstream temp;
                temp << finalNum;
                numerator = temp.str();
                denominator = bottomLeft;
            }
            else {
                leftNum *= rightDenom;
                rightNum *= leftDenom;
                leftDenom *= rightDenom;
                finalNum = leftNum + rightNum;
                ostringstream numer;
                numer << finalNum;
                numerator = numer.str();
                ostringstream denom;
                denom << leftDenom;
                denominator = denom.str();

            }
            answer = numerator + "/" + denominator;
        }
        if(isPolynomial(left)) {

        }
        if(isInteger(left)) {
            int leftO, rightO, ans;
            istringstream(left) >> leftO;
            istringstream(right) >> rightO;
            ans = leftO + rightO;
            ostringstream t;
            t << ans;
            answer = t.str();
        }

    }

    else {
      answer = left + " + " + right;
    }
    return answer;
}
string subtract(string left, string right) {
    string leftCoefficient, rightCoefficient, leftExponent, rightExponent, finalC, answer, simplifiedLeft, simplifiedRight, a;
    int leftC, rightC, final, leftO, rightO;
    //checks if the left and right operands are of the same type
    if((isIrrational(left) && isIrrational(right)) || (isFraction(left) && isFraction(right)) || (isInteger(left) && isInteger(right)) || (isLog(left) && isLog(right)) || (isPolynomial(left) && isPolynomial(right))) {
        //Dealing with Irrational Numbers
        if(isIrrational(left)) {
            int i = 0;
            leftCoefficient = "";
            leftExponent = "";
            int temp;
            while(i < left.length()) {
                if(istringstream(left.substr(i, 1)) >> temp) {
                    leftCoefficient += left[i];

                }
                else {
                    break;
                }
                i++;
            }
            if(leftCoefficient == ""){
                 leftCoefficient = "1";
            }
            i = 0;
            rightCoefficient = "";
            rightExponent = "";
            while(i < right.length()) {
                 if(istringstream(right.substr(i, 1)) >> temp) {
                    rightCoefficient += right[i];
                }
                 else {
                     break;
                 }
                i++;
             }
             if(rightCoefficient == ""){
                 rightCoefficient = "1";
             }
            istringstream(leftCoefficient) >> leftC;
            istringstream(rightCoefficient) >> rightC;
            final = leftC - rightC;
            ostringstream temporary;
            temporary << final;
            finalC = temporary.str();
            if(isPi(left) && isPi(right)) {
                while(i < left.length()) {
                         if(left.substr(i, 1) == "^") {
                             while(i < left.length()) {
                                 leftExponent += left[i+1];
                                 i++;
                             }
                         }
                         i++;
                 }
                 i =0;
                 while(i < right.length()) {
                         if(right.substr(i, 1) == "^") {
                             while(i < right.length()) {
                                 rightExponent += right[i+1];
                                 i++;
                             }
                         }
                         i++;
                 }
                 if((leftExponent == rightExponent) && !(leftExponent == "" && rightExponent == "")) {
                         answer = finalC + "pi" + "^" + leftExponent;
                 }
                 else if((leftExponent == rightExponent) && (leftExponent == "" && rightExponent == "")){
                         answer = finalC + "pi";
                 }
                 else
                     answer = left + " - " + right;
            }
            else if(isE(left) && isE(right)) {
                while(i < left.length()) {
                         if(left.substr(i, 1) == "^") {
                             while(i < left.length()) {
                                 leftExponent += left[i+1];
                                 i++;
                             }
                         }
                         i++;
                 }
                 i =0;
                 while(i < right.length()) {
                         if(right.substr(i, 1) == "^") {
                             while(i < right.length()) {
                                 rightExponent += right[i+1];
                                 i++;
                             }
                         }
                         i++;
                 }
                 if((leftExponent == rightExponent) && !(leftExponent == "" && rightExponent == "")) {
                         answer = finalC + "e" + "^" + leftExponent;
                 }
                 else if((leftExponent == rightExponent) && (leftExponent == "" && rightExponent == "")){
                         answer = finalC + "e";
                 }
                 else
                     answer = left + " - " + right;
            }
            else if(isPi(left) && isE(right) || isE(left) && isPi(right)) {
                answer = left + " - " + right;
            }
            else {
                throw invalidIrr;
            }
        }
        else if(isLog(left)) {
          string leftBase, rightBase, leftNum, rightNum, final;
          int i = 4;
          //Specified base for the log
          if(left[3] == '_' ) {
              while(left[i] != ':') {
                  leftBase += left[i];
                  i++;
              }
              i++;
              while(i <= left.length()-1) {
                  leftNum += left[i];
                  i++;
              }
          }
          //This is log base 10
          else if(left[3] == ':') {
              leftBase = "10";
              while(i <= left.length()-1) {
                  leftNum += left[i];
                  i++;
              }
          }
          i = 4;
          if(right[3] == '_' ) {
              while(right[i] != ':') {
                  rightBase += right[i];
                  i++;
              }
              i++;
              while(i <= right.length()-1) {
                  rightNum += right[i];
                  i++;
              }
          }
          //This is log base 10
          else if(right[3] == ':') {
              rightBase = "10";
              while(i <= right.length()-1) {
                  rightNum += right[i];
                  i++;
              }
          }
          int num, tempLeft, tempRight, tempLNum, tempRNum;
          istringstream(leftBase) >> tempLeft;
          istringstream(rightBase) >> tempRight;
          istringstream(leftNum) >> tempLNum;
          istringstream(rightNum) >> tempRNum;
          simplifiedLeft = simplifyLog(tempLeft, tempLNum);
          simplifiedRight = simplifyLog(tempRight, tempRNum);
          if(isInteger(simplifiedLeft)) {
              left = simplifiedLeft;
              istringstream(left) >> leftO;
          }
          if(isInteger(simplifiedRight)) {
              right = simplifiedRight;
              istringstream(left) >> rightO;
          }
          if(tempLNum % tempRNum == 0) {
              num = tempLNum / tempRNum;
          }
          else {
              int p = gcd(tempLNum, tempRNum);
              tempLNum /= p;
              tempRNum /= p;
              ostringstream c, d;
              c << tempLNum;
              d << tempRNum;
              a = "(" + c.str() + "/" + d.str() + ")";
          }
          if(isInteger(simplifiedLeft) && isInteger(simplifiedRight)) {
              answer = leftO - rightO;
          }
          else if(!isInteger(simplifiedLeft) && !isInteger(simplifiedRight)) {
              if(tempLeft == tempRight) {
                  answer = "log_" + leftBase + ":" + a ;
              }
              else {
                answer = left + " - " + right;
              }
          }
          else {
              answer = left + " - " + right;
          }
        }
        else if(isFraction(left)) {
            string numerator, denominator;
            int i =0;
            string topLeft, topRight, bottomLeft, bottomRight;
            int leftNum, rightNum, leftDenom, rightDenom, finalNum;
            while(left[i] != '/'){
                topLeft += left[i];
                i++;
            }
            i++;
            while(i < left.length()) {
                bottomLeft += left[i];
                i++;
            }
            i = 0;
            while(right[i] != '/'){
                topRight += right[i];
                i++;
            }
            i++;
            while(i < right.length()) {
                bottomRight += right[i];
                i++;
            }
            istringstream(topLeft) >> leftNum;
            istringstream(topRight) >> rightNum;
            istringstream(bottomLeft) >> leftDenom;
            istringstream(bottomRight) >> rightDenom;
            //if the fractions can be simplified
            int d, e;
            d = gcd(leftNum, leftDenom);
            leftNum /= d;
            leftDenom /= d;
            e = gcd(rightNum, rightDenom);
            rightNum /= e;
            rightDenom /= e;
            if(leftDenom == rightDenom) {
                finalNum = leftNum - rightNum;
                ostringstream temp;
                temp << finalNum;
                numerator = temp.str();
                denominator = bottomLeft;
            }
            else {
                leftNum *= rightDenom;
                rightNum *= leftDenom;
                leftDenom *= rightDenom;
                finalNum = leftNum - rightNum;
                ostringstream numer;
                numer << finalNum;
                numerator = numer.str();
                ostringstream denom;
                denom << leftDenom;
                denominator = denom.str();

            }
            answer = numerator + "/" + denominator;
        }
        if(isPolynomial(left)) {

        }
        if(isInteger(left)) {
            int leftO, rightO, ans;
            istringstream(left) >> leftO;
            istringstream(right) >> rightO;
            ans = leftO - rightO;
            ostringstream t;
            t << ans;
            answer = t.str();
        }
    }
    else {
      answer = left + " - " + right;
    }
    return answer;
}
string multiply(string left, string right) {
    string leftCoefficient, rightCoefficient, finalC, answer;
    int leftC, rightC, final;
    //checks if the left and right operands are of the same type
    if((isIrrational(left) && isIrrational(right)) || (isFraction(left) && isFraction(right)) || (isInteger(left) && isInteger(right)) || (isLog(left) && isLog(right)) || (isPolynomial(left) && isPolynomial(right))) {
        //Dealing with Irrational Numbers
		//PARSE COFFICIENTS OF IRRATIONALS NOW
        if(isIrrational(left)) {
            int i = 0;
            leftCoefficient = "";
            int temp;
			if(isNegative(left)) {							//If left is negative
				leftCoefficient = "-";						//make the leftcoeff start with a "-"
				i++;										//increment i
			}
            while(i < left.length()) {
                if(istringstream(left.substr(i, 1)) >> temp) {		//if this character of left is an int
                    leftCoefficient += left[i];						//concatenate to leftcoefficient string (handles multi digit ints)

                }
                i++;
            }
            if(leftCoefficient == ""){								//if left coeff is 1 (i.e. "pi")
                 leftCoefficient = "1";								//leftcoefficient is 1;
            }
            i = 0;
            rightCoefficient = "";
			if(isNegative(right)) {							//If left is negative
				rightCoefficient = "-";						//make the leftcoeff start with a "-"
				i++;										//increment i
			}
            while(i < right.length()) {
                 if(istringstream(right.substr(i, 1)) >> temp) {			//if this character of right is an int
                    rightCoefficient += right[i];							//concatenate to rightcoefficient string (handles multidigit numbers)

                }
                i++;
             }
             if(rightCoefficient == ""){							//if right coeff is 1 (i.e. "pi")																						//rightCoefficient is 1;
                 rightCoefficient = "1";							//make rightCoefficient 1
             }
            istringstream(leftCoefficient) >> leftC;
            istringstream(rightCoefficient) >> rightC;				//write the coefficients to ints; we can handle them and multiply now
            final = leftC * rightC;										//final gets the product of leftC and rightC
            ostringstream temporary;
            temporary << final;											//writes product of coefficients to a stringstream
            finalC = temporary.str();									//finalC gets the string of temporary stringstream
            if(isPi(left) && isPi(right)) {
                answer = finalC + "pi";
            }
            else if(isE(left) && isE(right)) {
                answer = finalC + "e";
            }
            else if(isPi(left) && isE(right) || isE(left) && isPi(right)) {
                answer = left + " + " + right;
            }
            }
       else if(isLog(left)) {
          string leftBase, rightBase, leftNum, rightNum, final;
          int i = 4;
          //Specified base for the log
          if(left[3] == '_' ) {
              while(left[i] != ':') {
                  leftBase += left[i];
                  i++;
              }
              i++;
              while(i <= left.length()-1) {
                  leftNum += left[i];
                  i++;
              }
          }
          //This is log base 10
          else if(left[3] == ':') {
              leftBase = "10";
              while(i <= left.length()-1) {
                  leftNum += left[i];
                  i++;
              }
          }
          i = 4;
          if(right[3] == '_' ) {
              while(right[i] != ':') {
                  rightBase += right[i];
                  i++;
              }
              i++;
              while(i <= right.length()-1) {
                  rightNum += right[i];
                  i++;
              }
          }
          //This is log base 10
          else if(right[3] == ':') {
              rightBase = "10";
              while(i <= right.length()-1) {
                  rightNum += right[i];
                  i++;
              }
          }
          int num, tempLeft, tempRight, tempLNum, tempRNum;
          istringstream(leftBase) >> tempLeft;
          istringstream(rightBase) >> tempRight;
          istringstream(leftNum) >> tempLNum;
          istringstream(rightNum) >> tempRNum;
          num = tempLNum * tempRNum;
          ostringstream n;
          n << num;
          if(tempLeft == tempRight) {

              answer = "log_" + leftBase + ":" + n.str() ;
          }
          else {
              answer = left + " + " + right;
          }


        }
        else if(isFraction(left)) {
            string numerator, denominator;
            int i =0;
            string topLeft, topRight, bottomLeft, bottomRight;
            int leftNum, rightNum, leftDenom, rightDenom, finalNum;
            while(left[i] != '/'){
                topLeft += left[i];
                i++;
            }
            i++;
            while(i < left.length()) {
                bottomLeft += left[i];
                i++;
            }
            i = 0;
            while(right[i] != '/'){
                topRight += right[i];
                i++;
            }
            i++;
            while(i < right.length()) {
                bottomRight += right[i];
                i++;
            }
            istringstream(topLeft) >> leftNum;
            istringstream(topRight) >> rightNum;
            istringstream(bottomLeft) >> leftDenom;
            istringstream(bottomRight) >> rightDenom;
            if(leftDenom == rightDenom) {
                finalNum = leftNum + rightNum;
                ostringstream temp;
                temp << finalNum;
                numerator = temp.str();
                denominator = bottomLeft;
            }
            else {
                leftNum *= rightDenom;
                rightNum *= leftDenom;
                leftDenom *= rightDenom;
                finalNum = leftNum + rightNum;
                ostringstream numer;
                numer << finalNum;
                numerator = numer.str();
                ostringstream denom;
                denom << leftDenom;
                denominator = denom.str();

            }
            answer = numerator + "/" + denominator;
        }
        if(isPolynomial(left)) {

        }
        if(isInteger(left)) {
            int leftO, rightO, ans;
            istringstream(left) >> leftO;
            istringstream(right) >> rightO;
            ans = leftO + rightO;
            ostringstream t;
            t << ans;
            answer = t.str();
        }

    }

    else {
      answer = left + " + " + right;
    }
    return answer;
}
string divide(string left, string right) {
     string leftCoefficient, rightCoefficient, leftExponent, rightExponent, finalC,finalE, answer, simplifiedLeft, simplifiedRight;
     int leftC, rightC,leftE, rightE, final, leftO, rightO;
     //checks if the left and right operands are of the same type
     if ((isIrrational(left) && isIrrational(right)) || (isFraction(left) && isFraction(right)) || (isInteger(left) && isInteger(right)) || (isLog(left) && isLog(right)) || (isPolynomial(left) && isPolynomial(right))) {
         //Dealing with Irrational Numbers
         if (isIrrational(left)) {
             int i = 0;
             leftCoefficient = "";
             leftExponent = "";
             int temp;
 
             while (i < left.length()) {
                 if (istringstream(left.substr(i, 1)) >> temp) {
                     leftCoefficient += left[i];
 
                 } else
                     break;
                 i++;
             }
             if (leftCoefficient == "") {
                 leftCoefficient = "1";
             }
             i = 0;
             rightCoefficient = "";
             rightExponent = "";
             while (i < right.length()) {
                 if (istringstream(right.substr(i, 1)) >> temp) {
                     rightCoefficient += right[i];
 
                 } else
                     break;
                 i++;
             }
             if (rightCoefficient == "") {
                 rightCoefficient = "1";
             }
             istringstream(leftCoefficient) >> leftC;
             istringstream(rightCoefficient) >> rightC;
             //if the coefficients can be divided into a whole number
             if ((leftC % rightC) == 0) {
                 final = leftC / rightC;
                 ostringstream temporary;
                 temporary << final;
                 finalC = temporary.str();
             }
             else {
                 int d = gcd(leftC, rightC);
                 leftC /= d;
                 rightC /= d;
                 ostringstream tempNumerator;
                 ostringstream tempDenominator;
                 tempNumerator << leftC;
                 tempDenominator << rightC;
                 finalC = tempNumerator.str() + "/" + tempDenominator.str();
             }
             i = 0;
                 if (isPi(left) && isPi(right)) {
                     while (i < left.length()) {
                         if (left.substr(i, 1) == "^") {
                             while(i < left.length()) {
                                 leftExponent += left[i + 1];
                                 i++;
                             }
                         }
                         i++;
                     }
                     if(leftExponent == "") {
                         leftExponent == "0";
                     }
                     i = 0;
                     while (i < right.length()) {
                         if (right.substr(i, 1) == "^") {
                             while(i < right.length()) {
                                rightExponent += right[i + 1];
                                i++;
                             }
                         }
                         i++;
                     }
                     if(rightExponent == "") {
                         rightExponent == "0";
                     }
                    istringstream(leftExponent) >> leftE;
                    istringstream(rightExponent) >> rightE;
                     final = leftE - rightE;
                     ostringstream temporary;
                     temporary << final;
                     finalE = temporary.str();
                     if (final == 0) {
                         answer = finalC;
                     } 
                     else {
                         answer = finalC + "pi" + "^" + finalE;
                     }
                 }
                 else if (isE(left) && isE(right)) {
                     while (i < left.length()) {
                         if (left.substr(i, 1) == "^") {
                             while (i < left.length()) {
                                 leftExponent += left[i + 1];
                                 i++;
                             }
                         }
                         i++;
                     }
                     if(leftExponent == "") {
                         leftExponent == "0";
                     }
                     i = 0;
                     while (i < right.length()) {
                         if (right.substr(i, 1) == "^") {
                             while (i < right.length()) {
                                rightExponent += right[i + 1];
                                i++;
                             }
                         }
                         i++;
                     }
                     if(rightExponent == "") {
                         rightExponent == "0";
                     }
                     istringstream(leftExponent) >> leftE;
                     istringstream(rightExponent) >> rightE;
                     final = leftE - rightE;
                     ostringstream temporary;
                     temporary << final;
                     finalE = temporary.str();
                     if (final == 0) {
                         answer = finalC;
                     } 
                     else {
                         answer = finalC + "e" + "^" + finalE;
                     }
                 } 
                 else if (isPi(left) && isE(right)) {
                     if(leftE == 0 && rightE == 0){
                         answer = finalC + "pi" + "/" + "e";
                     }
                     else
                         answer = finalC + "pi" + "^" + leftExponent + "/" + "e" + "^" + rightExponent;
                 }
                 else if(isE(left) && isPi(right)) {
                     if(leftE == 0 && rightE == 0)
                         answer = finalC + "e" + "/" + "i";
                     else
                         answer = finalC + "e" + "^" + leftExponent + "/" + "pi" + "^" + rightExponent;
                 }
                 else {
                     throw invalidIrr;
                 }
             }
          else if (isLog(left)) {
             string leftBase, rightBase, leftNum, rightNum, final;
             int i = 4;
             //Specified base for the log
             if (left[3] == '_') {
                 while (left[i] != ':') {
                     leftBase += left[i];
                     i++;
                 }
                 i++;
                 while (i <= left.length() - 1) {
                     leftNum += left[i];
                     i++;
                 }
             }//This is log base 10
             else if (left[3] == ':') {
                 leftBase = "10";
                 while (i <= left.length() - 1) {
                     leftNum += left[i];
                     i++;
                 }
             }
             i = 4;
             if (right[3] == '_') {
                 while (right[i] != ':') {
                     rightBase += right[i];
                     i++;
                 }
                 i++;
                 while (i <= right.length() - 1) {
                     rightNum += right[i];
                     i++;
                 }
             }//This is log base 10
             else if (right[3] == ':') {
                 rightBase = "10";
                 while (i <= right.length() - 1) {
                     rightNum += right[i];
                     i++;
                 }
             }
             int num, tempLeft, tempRight, tempLNum, tempRNum;
             istringstream(leftBase) >> tempLeft;
             istringstream(rightBase) >> tempRight;
             istringstream(leftNum) >> tempLNum;
             istringstream(rightNum) >> tempRNum;
             simplifiedLeft = simplifyLog(tempLeft, tempLNum);
             simplifiedRight = simplifyLog(tempRight, tempRNum);
              if(isInteger(simplifiedLeft)) {
                  left = simplifiedLeft;
                  istringstream(left) >> leftO;
              }
              if(isInteger(simplifiedRight)) {
                  right = simplifiedRight;
                  istringstream(left) >> rightO;
              }
              //if the two logs simmplify to integers and the integers are evenly divisible
              if(isInteger(simplifiedLeft) && isInteger(simplifiedRight) && (leftO % rightO == 0)) {
                  answer = leftO / rightO;
              }
              //if the two logs simplify to integers but the integers are not evenly divisible
              else if(isInteger(simplifiedLeft) && isInteger(simplifiedRight) && !(leftO % rightO == 0)) {
                  int a = gcd(leftO, rightO);
                  ostringstream n;
                  ostringstream d;
                  leftO /= a;
                  rightO /= a;
                  n << leftO;
                  d << rightO;
                  answer = n.str() +"/" + d.str() ;
              }
              else if(!isInteger(simplifiedLeft) && !isInteger(simplifiedRight)) {
                  //if the bases are equal
                  if(tempLeft == tempRight) {
                      answer = "log_" + rightNum + ":" + leftNum ;
                  }
                  else {
                    answer = left + " / " + right;
                  }
              }
              else {
                  answer = left + " / " + right;
              }
         } 
         else if (isFraction(left)) {
             string numerator, denominator;
             int i = 0;
             string topLeft, topRight, bottomLeft, bottomRight;
             int leftNum, rightNum, leftDenom, rightDenom, finalNum, finalDenom;
             while (left[i] != '/') {
                 topLeft += left[i];
                 i++;
             }
             i++;
             while (i < left.length()) {
                 bottomLeft += left[i];
                 i++;
             }
             i = 0;
             while (right[i] != '/') {
                 topRight += right[i];
                 i++;
             }
             i++;
             while (i < right.length()) {
                 bottomRight += right[i];
                 i++;
             }
             istringstream(topLeft) >> leftNum;
             istringstream(topRight) >> rightDenom;
             istringstream(bottomLeft) >> leftDenom;
             istringstream(bottomRight) >> rightNum;
             //if the fractions can be simplified
             int d, e;
             d = gcd(leftNum, leftDenom);
             leftNum /= d;
             leftDenom /= d;
             e = gcd(rightNum, rightDenom);
             rightNum /= e;
             rightDenom /= e;
             finalNum = leftNum * rightNum;
             finalDenom = leftDenom * rightDenom;
             int g = gcd(finalNum, finalDenom);
             finalNum /= g;
             finalDenom /= g;
             ostringstream numer;
             numer << finalNum;
             numerator = numer.str();
             ostringstream denom;
             denom << finalDenom;
             denominator = denom.str();
 
             //}
             answer = numerator + "/" + denominator;
         }
         if (isPolynomial(left)) {
 
         }
         if (isInteger(left)) {
             int leftO, rightO, ans;
             istringstream(left) >> leftO;
             istringstream(right) >> rightO;
             if(leftO % rightO == 0) {
             ans = leftO / rightO;
             ostringstream t;
             t << ans;
             answer = t.str();
             }
             else {
                 int d = gcd(leftO, rightO);
                 leftO /= d;
                 rightO /= d;
                 ostringstream numera;
                 ostringstream denomi;
                 numera << leftO;
                 denomi << rightO;
                 answer = numera.str() + "/" + denomi.str();
             }      
         }
     }
     else {
         answer = left + " / " + right;
     }
     return answer;
 }
