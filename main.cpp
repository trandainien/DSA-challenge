#include <iostream>
#include <sstream>
#include <vector>
#include <stack>
#include <math.h>
#include <fstream>
using namespace std;

string formString(string s){
	string ans = "";
	for (int i = 0; i < s.length(); i++){
		if (s[i] == ')'){
				ans += " ";
		}
		ans += s[i];
		if (s[i] == '(' || s[i] == ' '){
			ans += " ";
		}
	}
	return ans;
}

vector<string> split(string s){
	stringstream ss(s);
	string tmp;
	vector<string> ans;
	while (ss >> tmp){
		ans.push_back(tmp);
	}
	return ans;
}

int getPrecedence(string s){
	if (s == "+" || s == "-") return 1;
	else if (s == "*" || s == "/") return 2;
	else if (s == "^") return 3;
	else return 0;
}

bool isNumber(string s){
	for (int i = 0; i < s.length(); i++){
		if (s[i] == '(' || s[i] == ')' || s[i] == '^' || s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/')
			return false;
	}
	return true;
}

void getPostfix(vector<string> vec, string &postfix){
	postfix = "";
	stack <string> st;
	st.push("empty");
	for (int i = 0; i < vec.size(); i++){
		string s = vec[i];
		if (isNumber(s)){
			postfix += s + " ";
		}else{
			if (s == "(" || s == "^"){
				st.push(s);
			}else{
				if (s == ")"){
					while (st.top() != "empty" && st.top() != "("){
						postfix += st.top() + " ";
						st.pop();
					}
					st.pop();
				}else{
					if (getPrecedence(s) > getPrecedence(st.top())){
						st.push(s);
					}else{
						while (st.top() != "empty"  && getPrecedence(s) <= getPrecedence(st.top())){
							postfix += st.top() + " ";
							st.pop();
						}
						st.push(s);
					}
				}
			}
		}
	}
	
	while (st.top() != "empty" ){
		postfix += st.top() + " ";
		st.pop();
	}

}

float calculate(float a, float b, string s){
	if (s == "+") return b + a;
	else if (s == "-") return b - a;
	else if (s == "*") return b * a;
	else if (s == "/") return b / a;
	else return pow(b,a);
}

bool evaluatePostfix(float &res, string postfix){
	float a;
	float b;
	stack<float> st;
	vector<string> vec = split(postfix);
	for (int i = 0; i < vec.size(); i++){
		string s = vec[i];
		if (!isNumber(s)){
			if (st.empty()) return false;
			a = st.top(); 
			st.pop();
			if (st.empty()) return false;
			b = st.top(); 
			st.pop();
			st.push(calculate(a, b, s));
		}else{
			cout << s << endl;
			st.push(stof(s));
		}
	}
	if (st.size() != 1) return false;
	res = st.top();
	return true;
}

void solve(string inputFile, string outputFile, int n, string action){
	ifstream fin;
	fin.open(inputFile);
	ofstream fout;
	fout.open(outputFile);
	for (int i = 0; i < n; i++){
		string infix, postfix;
		getline(fin, infix);
		cout << infix << endl;
		// infix = formString(infix);
		
		// vector<string> vec = split(infix);
		
		// getPostfix(vec, postfix);
		// if (action == "-c"){
			// float result;
			// if (!evaluatePostfix(result, postfix) || infix == postfix){
				// fout << "E" << endl;
			// }else{
				// fout << result << endl;
			// }
		// }else{
			// if (infix == postfix){
				// fout << "E" << endl;
			// }else{
				// fout << postfix << endl;
			// }
		// }
	}
	
	
	fin.close();
	fout.close();
}

int main(int argc, char** argv){
	string inputFile = (argv[1])? argv[1] : "";
	string outputFile = (argv[4])? argv[4] : "";
	int n = (argv[2])? atoi(argv[2]) : 0;
	string action = (argv[3])? argv[3] : "";
	
	solve(inputFile, outputFile, n, action);

	// string s = "+ 2 3";
	// string initS = s;
	// vector<string> vec;
	// s = formString(s);
	// vec = split(s);
	// string postfix;
	// getPostfix(vec, postfix);
	// if (postfix == initS) cout <<"invalid";
	// else {
		// cout << postfix << endl;
		// float result; 
		// if (!evaluatePostfix(result, postfix)) cout << "invalid";
		// else cout << result;
	// }
}

// reference
// https://www.tutorialspoint.com/Convert-Infix-to-Postfix-Expression#:~:text=To%20convert%20infix%20expression%20to,maintaining%20the%20precedence%20of%20them.
// https://stackoverflow.com/questions/19894989/how-do-i-properly-test-whether-my-postfix-expression-is-valid
// https://www.tutorialspoint.com/program-to-evaluate-postfix-notation-in-cplusplus

// how to know if the expression is valid?
