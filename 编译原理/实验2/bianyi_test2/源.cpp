#include<chrono>
#include<iostream>
#include<string>
#include<fstream>
#include<vector>
using namespace std;
using namespace std::chrono;

//关键字集
const vector<string>KeyWord = { "void","char","int","float","bool","w_char","include","enum",
							"iostream","scanf","main","printf","struct","union",
							"class","typedef","std","long","short","signed","unsigned",
							 "const","volatile", "do","for","while",
							 "break","continue","return","goto",
							 "auto","register","static","extern","inline",
							"if","else","switch","case","default",
							"new","delete","sizeof",
							"private","protected","public",
							"this","friend","true","false","template","typename",
							"using","namespace","throw","try","catch","operator" };
//运算符集
const vector<string>Operator = { "+", "-", "*", "/", "=", "==", "!=", "<", ">", "<=", ">=" };
//分隔符集
char Separater[8] = { ';',',','{','}','[',']','(',')' };

//对于输入的字符串进行匹配分析
class scan {
private:
	string input;
	vector<string>keyword;
	vector<string>opeword;
	vector<char>sepword;
public:
	//构造函数
	scan(string in) {
		input = in;
	}
	//匹配关键字，获得关键字集
	void scan_keyword() {
		for (int i = 0; i < KeyWord.size(); i++) {
			string temp1 = KeyWord[i];
			if (input.find(temp1) != string::npos) { //在input中能够找到某个关键字
				keyword.push_back(temp1);
			}
			else {
				continue;
			}
		}
	}
	//匹配运算符，获得运算符集
	void scan_opeword() {
		for (int i = 0; i < Operator.size(); i++) {
			string temp2 = Operator[i];
			if (input.find(temp2) != string::npos) { //在input中能够找到某个运算符
				opeword.push_back(temp2);
			}
		}
	}
	//匹配分隔符，获得分隔符集
	void scan_sepword() {
		for (int i = 0; i < 8; i++) {
			char temp3 = Separater[i];
			for (int j = 0; j < input.length(); j++) {
				//同样找到这个分隔符就可以退出对这个分隔符的查找了
				if (input[j] == temp3) {
					sepword.push_back(temp3);
					break;
				}
			}
		}
	}
	void print() {
		cout << "在这个字符串中，匹配到的关键字集为:";
		for (int i = 0; i < keyword.size(); i++) {
			cout << keyword[i] << " ";
		}
		cout << endl;
		cout << "在这个字符串中，匹配到的运算符集为:";
		for (int i = 0; i < opeword.size(); i++) {
			cout << opeword[i] << " ";
		}
		cout << endl;
		cout << "在这个字符串中，匹配到的分隔符集为:";
		for (int i = 0; i < sepword.size(); i++) {
			cout << sepword[i] << " ";
		}
		cout << endl;
	}
};

int main() {
	auto start = high_resolution_clock::now();
	string input;
	cout << "please input your string:";
	getline(cin, input);//输入的字符串中允许包含空格
	scan S(input);
	S.scan_keyword();
	S.scan_opeword();
	S.scan_sepword();
	S.print();
	auto end = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(end - start);
	cout << "查表方式运行时间：" << duration.count() << "ms" << endl;
	return 0;
}

/*
#include <iostream>
#include <string>
#include<vector>
#include <unordered_set>
using namespace std;
bool isKeyword(string str) {
	unordered_set<string> keywords = { "void","char","int","float","bool","w_char","include","enum",
							"iostream","scanf","main","printf","struct","union",
							"class","typedef","std","long","short","signed","unsigned",
							 "const","volatile", "do","for","while",
							 "break","continue","return","goto",
							 "auto","register","static","extern","inline",
							"if","else","switch","case","default",
							"new","delete","sizeof",
							"private","protected","public",
							"this","friend","true","false","template","typename",
							"using","namespace","throw","try","catch","operator" };
	return keywords.count(str) > 0;
}
bool isOperator(string str) {
	unordered_set<string> operators = { "+", "-", "*", "/", "=", "==", "!=", "<", ">", "<=", ">=" };
	return operators.count(str) > 0;
}
bool isSeparator(char ch) {
	unordered_set<char> separators = { ' ', ',', ';', '(', ')', '{', '}' };
	return separators.count(ch) > 0;
}
int main() {
	string input;
	vector<string>keyword;
	vector<string>opeword;
	vector<char>sepword;
	cout << "Enter input: ";
	getline(cin, input);
	string current_token = "";
	for (int i = 0; i < input.length(); i++) {
		char ch = input[i];
		if (isalpha(ch)) { // 字母
			current_token += ch;
			while (i + 1 < input.length() && (isalpha(input[i + 1]) || isdigit(input[i + 1]))) {
				i++;
				current_token += input[i];
			}
			if (isKeyword(current_token)) {
				keyword.push_back(current_token);
				//cout << current_token << " is a keyword\n";
			}
			//else {
			//	cout << current_token << " is an identifier\n";//标识符
			//}
			current_token = "";
		}
		else if (isdigit(ch)) { // 数字
			current_token += ch;
			while (i + 1 < input.length() && isdigit(input[i + 1])) {
				i++;
				current_token += input[i];
			}
			cout << current_token << " is a number\n";
			current_token = "";
		}
		else if (isSeparator(ch)) { // 分隔符
			sepword.push_back(ch);
			//cout << string(1, ch) << " is a separator\n";
		}
		else if (isOperator(string(1, ch))) { // 运算符
			current_token += ch;
			while (i + 1 < input.length() && isOperator(current_token + input[i + 1])) {
				i++;
				current_token += input[i];
			}
			opeword.push_back(current_token);
			//cout << current_token << " is an operator\n";
			current_token = "";
		}
	}
	//输出识别信息
	cout << "所识别到的关键字为：";
	for (int i = 0; i < keyword.size(); i++)
		cout << keyword[i] << " ";
	cout << endl << "所识别到的分隔符为：";
	for (int i = 0; i < sepword.size(); i++)
		cout << sepword[i] << " ";
	cout << endl << "所识别到的运算符为：";
	for (int i = 0; i < opeword.size(); i++)
		cout << opeword[i] << " ";
	cout << endl;
	return 0;
}
*/