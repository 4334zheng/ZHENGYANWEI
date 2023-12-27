#include<chrono>
#include<iostream>
#include<string>
#include<fstream>
#include<vector>
using namespace std;
using namespace std::chrono;

//�ؼ��ּ�
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
//�������
const vector<string>Operator = { "+", "-", "*", "/", "=", "==", "!=", "<", ">", "<=", ">=" };
//�ָ�����
char Separater[8] = { ';',',','{','}','[',']','(',')' };

//����������ַ�������ƥ�����
class scan {
private:
	string input;
	vector<string>keyword;
	vector<string>opeword;
	vector<char>sepword;
public:
	//���캯��
	scan(string in) {
		input = in;
	}
	//ƥ��ؼ��֣���ùؼ��ּ�
	void scan_keyword() {
		for (int i = 0; i < KeyWord.size(); i++) {
			string temp1 = KeyWord[i];
			if (input.find(temp1) != string::npos) { //��input���ܹ��ҵ�ĳ���ؼ���
				keyword.push_back(temp1);
			}
			else {
				continue;
			}
		}
	}
	//ƥ�������������������
	void scan_opeword() {
		for (int i = 0; i < Operator.size(); i++) {
			string temp2 = Operator[i];
			if (input.find(temp2) != string::npos) { //��input���ܹ��ҵ�ĳ�������
				opeword.push_back(temp2);
			}
		}
	}
	//ƥ��ָ�������÷ָ�����
	void scan_sepword() {
		for (int i = 0; i < 8; i++) {
			char temp3 = Separater[i];
			for (int j = 0; j < input.length(); j++) {
				//ͬ���ҵ�����ָ����Ϳ����˳�������ָ����Ĳ�����
				if (input[j] == temp3) {
					sepword.push_back(temp3);
					break;
				}
			}
		}
	}
	void print() {
		cout << "������ַ����У�ƥ�䵽�Ĺؼ��ּ�Ϊ:";
		for (int i = 0; i < keyword.size(); i++) {
			cout << keyword[i] << " ";
		}
		cout << endl;
		cout << "������ַ����У�ƥ�䵽���������Ϊ:";
		for (int i = 0; i < opeword.size(); i++) {
			cout << opeword[i] << " ";
		}
		cout << endl;
		cout << "������ַ����У�ƥ�䵽�ķָ�����Ϊ:";
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
	getline(cin, input);//������ַ�������������ո�
	scan S(input);
	S.scan_keyword();
	S.scan_opeword();
	S.scan_sepword();
	S.print();
	auto end = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(end - start);
	cout << "���ʽ����ʱ�䣺" << duration.count() << "ms" << endl;
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
		if (isalpha(ch)) { // ��ĸ
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
			//	cout << current_token << " is an identifier\n";//��ʶ��
			//}
			current_token = "";
		}
		else if (isdigit(ch)) { // ����
			current_token += ch;
			while (i + 1 < input.length() && isdigit(input[i + 1])) {
				i++;
				current_token += input[i];
			}
			cout << current_token << " is a number\n";
			current_token = "";
		}
		else if (isSeparator(ch)) { // �ָ���
			sepword.push_back(ch);
			//cout << string(1, ch) << " is a separator\n";
		}
		else if (isOperator(string(1, ch))) { // �����
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
	//���ʶ����Ϣ
	cout << "��ʶ�𵽵Ĺؼ���Ϊ��";
	for (int i = 0; i < keyword.size(); i++)
		cout << keyword[i] << " ";
	cout << endl << "��ʶ�𵽵ķָ���Ϊ��";
	for (int i = 0; i < sepword.size(); i++)
		cout << sepword[i] << " ";
	cout << endl << "��ʶ�𵽵������Ϊ��";
	for (int i = 0; i < opeword.size(); i++)
		cout << opeword[i] << " ";
	cout << endl;
	return 0;
}
*/