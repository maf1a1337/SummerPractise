#include <iostream>
#include <windows.h>
#include <string>
#include <stack>
#include <vector>    
#include <algorithm>  
#include <map>

using namespace std;

int Priority(char c) {
    if (c == '(')
        return 0;
    if (c == ')')
        return 1;
    if (c == '+' || c == '-')
        return 2;
    if (c == '*' || c == '/')
        return 3;
    return 4;
}

int BoolInt(char c) {
    if (isdigit(c)) return 1;
    else return 0;
}


string PostfixNotation(string a) {
    string vuvod, vvod;
    stack <char> steck;
    if (a[0] == '-') {
        a[0] = '*';
        vvod += "(-1)" + a;
    }
    else vvod = a;
    for (int i = 0; i <= vvod.length() - 1; i++) {
        if (Priority(vvod[i]) == 4) {
            vuvod.push_back(vvod[i]);
            if (Priority(vvod[i]) == Priority(vvod[i + 1]) && i!=vvod.length()-1) {
                i++;
                while (Priority(vvod[i]) == 4) {
                    if (i == vvod.length()) break;
                    vuvod.push_back(vvod[i]);
                    i++;
                }
            }
            vuvod.push_back(' ');
            if (i == vvod.length() - 1) {
                while (size(steck) != 0) {
                    if (steck.top() == '(') {
                        steck.pop();
                        continue;
                    }
                    vuvod.push_back(steck.top());
                    vuvod.push_back(' ');
                    steck.pop();
                }
            }
        }
        if (Priority(vvod[i]) == 2 || Priority(vvod[i]) == 3) {
            if (size(steck) == 0) {
                steck.push(vvod[i]);
                continue;
            }
            while (Priority(vvod[i]) <= Priority(steck.top()) && steck.top() != '(') {
                vuvod.push_back(steck.top());
                vuvod.push_back(' ');
                steck.pop();
                if (size(steck) == 0) break;
            }
            steck.push(vvod[i]);
        }
        if (Priority(vvod[i]) == 1 && vvod[i-3] != '(') {
            while (size(steck) != 0 && steck.top() != '(') {
                vuvod.push_back(steck.top());
                vuvod.push_back(' ');
                steck.pop();
            }
            if (size(steck) != 0) steck.pop();
        }
        if (Priority(vvod[i]) == 0 && vvod[i+1] != '-') {
            steck.push(vvod[i]);
        }
        if (Priority(vvod[i]) == 0 && vvod[i + 1] == '-') {
            vuvod += "(-1) ";
            i += 3;
        }
        if (i == vvod.length()) {
            while (size(steck) != 0) {
                vuvod.push_back(steck.top());
                vuvod.push_back(' ');
                steck.pop();
            }
        }
    }
     while (steck.size() != 0) {
         if (steck.top() == '(') {
             steck.pop();
             continue;
         }
         vuvod.push_back(steck.top());
         vuvod.push_back(' ');
         steck.pop();
     }
    
    return vuvod;
}

float Operators(float a, float b, char op) {
    if (op == '-') return a - b;
    if (op == '+') return a + b; 
    if (op == '*') return a * b;
    if (op == '/') return a / b;
}

int PostfixCalc(string str) {
    stack <float> steck;
    string digits;
    for (int i = 0; i != str.length(); i++) {
        if (str[i] == ' ') continue;
        if (Priority(str[i]) == 4) {
            digits.push_back(str[i]);
            if (Priority(str[i + 1]) == 4 && i != str.length() - 1) {
                i++;
                while (str[i] != ' ') {
                    digits.push_back(str[i]);
                    i++;
                }
            }
            steck.push(stof(digits));
            digits.clear();
            continue;
        } 
        if (Priority(str[i]) == 3 || Priority(str[i]) == 2) {
            float a = steck.top();
            steck.pop();
            float b = steck.top();
            steck.pop();
            steck.push(Operators(b, a, str[i]));
        }
    }
    return steck.top();
}


string Multiplication(string a, string b, char op) {
    stack <string> steck;
    stack <char> oper;
    string digits;
    int aznak = 0;
    int bznak = 0;
    int j = 0;
    for (int i = 0; i < a.length(); i++)
        if (Priority(a[i]) == 2) aznak++;
    for (int i = 0; i < b.length(); i++)
        if (Priority(b[i]) == 2) bznak++;
    if (aznak <= bznak) swap(a, b);
    for (int i = 0; i<b.length(); i++) {
        if (Priority(b[i]) == 4 || Priority(b[i]) == 3 || Priority(b[i]) == 0) { 
            if (Priority(b[i]) == 0)
                while (Priority(b[i]) != 1) {
                    digits.push_back(b[i]);
                    i++;
                }
            digits.push_back(b[i]); 
        }
        else {
            oper.push(b[i]);
            steck.push(digits);
            digits.clear();
        }
    } 
    if (digits.length() != 0) steck.push(digits); 

    string result;
    int i = 0;
    while (steck.size() != 0) {
        if (Priority(a[i]) == 2 && a[i+1] != '1') {
             result += op + steck.top() + a[i];
        }
        else if (i == a.length()) {
            if (aznak == 0)
                return result += op + steck.top();
            result += op + steck.top();
            if (oper.size() != 0) { 
                result += oper.top();
                oper.pop(); 
            }
            steck.pop();
            i = 0;
            continue;
        }
        else {
            result += a[i];
        }
        i++;
    }
    return result;
}

string Sign(string a) {
    string b;
    b += "+(-1)*";
    for (int i = 0; i < a.length(); i++) {
        if (a[i] == '+') a[i] = '-';
        else if (a[i] == '-' && a[i + 1] != '1') a[i] = '+';
    }
    return b+a; 
}
string InfixView(string str) {
    stack <string> steck;
    string digits;
    string a, b, c, op;
    int j = 0;
    for (int i = 0; i <= str.length(); i++) {
        if (str[i] == ' ') continue;
        if (Priority(str[i]) == 4 && i <= str.length() - 1) {
            while (str[i] != ' ') {
                digits.push_back(str[i]);
                i++;
            }
            steck.push(digits);
            digits.clear();
            continue;
        }
        if (Priority(str[i]) == 0 && i <= str.length() - 1) {
            while (str[i] != ' ') {
                digits.push_back(str[i]);
                i++;
            }
            steck.push(digits);
            digits.clear();
            continue;
        }
        if (Priority(str[i]) == 2 && str[i-1] != '(') { 
            j = i;
            op = str[j]; 
            a = steck.top();
            steck.pop();
            b = steck.top();
            steck.pop();
            if (op == "-") {
                a = Sign(a);
                steck.push(b + a);
            }
            else steck.push(b + op + a);
        }
         else {
             if (Priority(str[i]) == 3 && i != j) {
                 a = steck.top();
                 steck.pop();
                 b = steck.top();
                 steck.pop();
                 steck.push(Multiplication(b, a, str[i]));
             }
         } 
        } 

    return steck.top();
}

string CalcCoef(string a) {
    if (Priority(a[0]) == 3) a.erase(0, 1);
    if (a.find("*") != string::npos)
        a = to_string(PostfixCalc(PostfixNotation(a)));
    return a;
}

string CalcView(string elem) {
    vector <char> vect;
    stack <char> op;
    string digits, result;
    for (int i = 0; i < elem.length(); i++) {
        if (elem[i] == ';') {
            digits = CalcCoef(digits);
            if (op.top() == '-') result.push_back(op.top());
            op.pop();
            if (digits.size() != 0) {
                result += digits;
                result.push_back('*');
            } 
            else {
                result.push_back('1');
                result.push_back('*');
            }
            sort(vect.begin(), vect.end());
            for (int j = 0; j < vect.size(); j++) {
                result.push_back(vect[j]);
                if (j == vect.size() - 1) break;
            }
            result += ";";
            digits.clear();
            vect.clear();
            continue;
        }
        if (Priority(elem[i]) == 2) {
            op.push(elem[i]);
            continue;
        }

        if (BoolInt(elem[i]) == 0 && Priority(elem[i]) != 3) {
            vect.push_back(elem[i]);
            continue;
        }
        if (BoolInt(elem[i + 1]) == 1 && Priority(elem[i]) == 3) {
            digits.push_back(elem[i]);
            continue;
        }
        if (BoolInt(elem[i]) == 1) digits.push_back(elem[i]);
    }
    return result;
}

string DefinitionSign(string elem) {
    string a, digits;
    int counter = 0;
    for (int i = 0; i < elem.length(); i++) {
        if (elem[i] == ';') {
            if (counter % 2) a.push_back('-');
            else a.push_back('+');
            a += digits;
            a.push_back(';');
            digits.clear();
            counter = 0;
            continue;
        }
        if (elem[i] == '-' && elem[i + 1] == '1') {
            counter++;
        }
        else if (elem[i] != '+') digits.push_back(elem[i]);
    }
    return a;
}

string CanonView(string a) {
    string elem;
    string digits;
    for (int i = 0; i < a.length(); i++) {
        if (i == 0 && Priority(a[i]) == 4) {
            digits.push_back(a[i]);
            elem.push_back('+');
            continue;
        }
        if (i == 0 && Priority(a[i]) == 2) {
            elem.push_back(a[i]);
            elem += ";";
            continue;
        }
        if (a[i] == '(') {
            i++;
            while (a[i] != ')') {
                digits.push_back(a[i]);
                i++;
            }
        }
        if (Priority(a[i]) == 4 || Priority(a[i]) == 3) {
            digits.push_back(a[i]);
        }
        if (Priority(a[i]) == 2) {
            elem += digits;
            elem += ";";
            if (a[i] == '-') elem += "-1*";
            else elem += a[i];
            digits.clear();
        }   
        if (i == a.length() - 1) {
            elem += digits + ";";
            digits.clear();
            break;
        }
    }

    return CalcView(DefinitionSign(elem));
}

string Operation(string a) {
    string digits;
    string b,c;
    multimap<string, int> m;
    for (int i = 0; i < a.length(); i++) {
        if (a[i] == ';') {
            for (int j = 0; j < digits.length(); j++) {
                if (digits[j] == '-') { b.push_back(digits[j]); continue; }
                if (BoolInt(digits[j]) == 1 && digits[j] != '*') {
                    b.push_back(digits[j]);
                }
                else if (digits[j] != '*') {
                    c.push_back(digits[j]);
                }
            }
            m.insert({ c, stoi(b) });
            digits.clear();
            b.clear();
            c.clear();
            continue;
        }
        digits.push_back(a[i]);
    }
    digits.clear();
    multimap<string, int>::iterator it1, it2, it3;
    it1 = m.begin();
    it2 = it1;
    it2++;
    it3 = m.end();
    string result;
    int k = 0;
    while (it1 != it3) {
        if (it2 != m.end()){
            if (it1->first == it2->first) {
                while (it1->first == it2->first) {
                    k += it1->second;
                    it1++;
                    if (it1 == m.end()) break;
                }
                result += to_string(k) + "*" + it2->first + "+";
                if (it1 == m.end()) break;
                it2 = it1;
                it2++;
                k = 0;
                continue;
            }
        }
        result += to_string(it1->second) + "*" + it1->first + "+";
        
        it1++;
        if (it1 == m.end()) break;
        it2++;
    }
    result.erase(result.length() - 1, 1);
    return result; 
}

void Printing(string a) {
    string b;
    for (int i = 0; i < a.length(); i++) {
        if (a[i] == '*' && Priority(a[i + 1]) == 2) a[i] = ' ';
        if (a[i] == '*' && i == a.length() - 1){
            a[i] = ' ';
            continue;
        }
        if (Priority(a[i]) == 2 && Priority(a[i + 1]) == 2) a[i] = ' ';
        if (a[i] == '1' && a[i + 1] == '*' && i!=a.length()-2) {
            if (Priority(a[i + 2]) == 2) continue;
            a[i] = ' ';
            a[i + 1] = ' ';
            i++;
        }
    }
    for (int i = 0; i < a.length(); i++) {
        if (a[i] == ' ') continue;
        b.push_back(a[i]);
    }
    cout << b;
}

int main(){
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    string a;
    cout << "Input: ";
    cin >> a;
    
    cout << endl << "Output: ";
    a = Operation(CanonView(InfixView(PostfixNotation(a))));
    Printing(a);
    cout << endl << endl << endl;
}
