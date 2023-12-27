#include<iostream>
#include<fstream>
#include<stack>
#include<vector>
#include<string>
#include<cstdlib>
#include<algorithm>
using namespace std;

class G {
private:
	vector<char>temp1; //记录大写
	vector<char>temp2; //记录小写
	//string *P;
	vector<string>P;
	char S;
public:
	//读取文件
	bool readFile() {
		//读取txt文件，infile为输入文件，outfile为输出文件
		ifstream infile;
		//infile.open("C:\\Users\\4334\\Desktop\\自用\\深大\\编译原理\\实验1\\demo_G.txt");
		//infile.open("C:\\Users\\4334\\Desktop\\自用\\深大\\编译原理\\实验1\\demo2.txt");
		//infile.open("C:\\Users\\4334\\Desktop\\自用\\深大\\编译原理\\实验1\\demo3.txt");
		infile.open("C:\\Users\\4334\\Desktop\\自用\\深大\\编译原理\\实验1\\demo4.txt");
		if (!infile)
		{
			cout << "无法打开文件" << endl;
			exit(1);
		}
		//读取txt文件中的每一行
		string ch;
		stack<char>CapitalLetter;
		stack<char>LowercaseLetter;
		int cnt = 0; //用于标识是否存在产生式右侧只有小写字母
		int flag = 0; //用于标识左边是否只有小写字母
		while (getline(infile, ch)) {
			cnt = 0;
			flag = 0;
			cout << ch << endl;
			P.push_back(ch);
			//对于每一行，找到箭头位置，分左右进行判断
			char* ch_left; //记录左部字符
			char* ch_right; //记录右部字符
			int left_len = 0;
			int right_len = 0;
			for (int i = 0; i < ch.length(); i++) {
				if (ch[i] >= 'A' && ch[i] <= 'Z') {
					CapitalLetter.push(ch[i]); //记录大写字符
				}
				else if (ch[i] >= 'a' && ch[i] <= 'z') {
					LowercaseLetter.push(ch[i]); //记录小写字符
				}
				else if (ch[i] == '-') {
					//获得左右部的字符长度
					left_len = i;
					right_len = ch.length() - left_len - 2;
				}
			}

			if (left_len == 0 || right_len == 0) {
				cout << "Error!无法构成合法的文法" << endl;
				return false;
			}
			else {
				//左右不为0，开空间存放，进行进一步判断
				ch_left = new char[left_len];
				ch_right = new char[right_len];
			}

			//得到左右字母数组
			for (int i = 0; i < left_len; i++)
			{
				ch_left[i] = ch[i];
				//cout << ch_left[i] << " ";
				//左边有大写字母
				if (ch_left[i] >= 'A' && ch_left[i] <= 'Z') {
					flag = 1;
				}
			}
			//cout << endl;
			for (int i = 0, j = left_len + 2; i < right_len; i++, j++) {
				ch_right[i] = ch[j];
				//cout << ch_right[i] << " ";
				if (ch_right[i] >= 'A' && ch_right[i] <= 'Z') {
					cnt = 1; //产生式右侧有大写，cnt标识为1
				}
			}
			//cout << endl;
		}
		if (cnt == 1 || flag == 0) {
			//每一行产生式都把cnt的值改为1，即每一行产生式的右侧都有大写，不合法
			//出现一行没有修改flag的值即左边没有大写字母，不合法
			cout << "产生式右侧均有大写，无法结束，不合法!" << endl;
			return false;
		}
		//把大小写符号挪到vector，做进一步处理
		while (!CapitalLetter.empty()) {
			temp1.push_back(CapitalLetter.top());
			CapitalLetter.pop();
		}
		//出现的首个字符为S
		S = temp1[temp1.size() - 1];
		while (!LowercaseLetter.empty()) {
			temp2.push_back(LowercaseLetter.top());
			LowercaseLetter.pop();
		}
		//合法性判断结束，整理非终结符和终结符，构造文法
		cout << "每一行判断结束，可以构造文法" << endl;
		return true;
	}

	void LegalJudge() {
		/*
		cout << "大写字母有";
		while (!CapitalLetter.empty()) {
			cout << CapitalLetter.top() << " ";
			CapitalLetter.pop();
		}
		cout << endl << "小写字母有";
		while (!LowercaseLetter.empty()) {
			cout << LowercaseLetter.top() << " ";
			LowercaseLetter.pop();
		}
		cout << endl;
		*/

		//使用vector实现数组的去重以及排序输出
		sort(temp1.begin(), temp1.end());
		temp1.erase(unique(temp1.begin(), temp1.end()), temp1.end());//去除重复元素
		cout << "所有非终结符:";
		for (auto x1 : temp1)
			cout << x1 << " ";
		cout << endl;

		sort(temp2.begin(), temp2.end());
		temp2.erase(unique(temp2.begin(), temp2.end()), temp2.end());//去除重复元素
		cout << "所有终结符:";
		for (auto x2 : temp2)
			cout << x2 << " ";
		cout << endl;
	}
	void print() {
		int size1 = temp1.size();
		int size2 = temp2.size();
		cout << "构造文法为：G=({";
		for (int i = 0; i < size1 - 1; i++)
			cout << temp1[i] << ",";
		cout << temp1[size1 - 1] << "},{";
		for (int i = 0; i < size2 - 1; i++)
			cout << temp2[i] << ",";
		cout << temp2[size2 - 1] << "},{";
		for (int i = 0; i < P.size() - 1; i++)
			cout << P[i] << ",";
		cout << P[P.size() - 1] << "},";
		cout << S << ")" << endl;
	}

	//判断合法即为0型文法，使用上面得到的产生式集P进行文法类型的判断
	bool FirstJudge() {
		int leftlen = 0;
		int rightlen = 0;
		for (int i = 0; i < P.size(); i++) {
			for (int j = 0; j < P[i].length(); j++) {
				if (P[i][j] == '-') {
					leftlen = j;
					rightlen = P[i].length() - leftlen - 2;
					break;
				}
			}
			//cout << leftlen << "," << rightlen << endl;
			if (leftlen > rightlen) {
				cout << "存在产生式的左部长度大于右部长度，该文法不是1型文法" << endl;
				return false;
			}
		}
		cout << "该文法是1型文法" << endl;
		return true;
	}
	//判断是否是2型文法，首先必须是1型文法
	bool SecondJudge() {
		if (FirstJudge()) {
			//是1型文法，进一步判断。要求产生式的左边必须是一个非终结符
			int leftlen = 0;
			int rightlen = 0;
			for (int i = 0; i < P.size(); i++) {
				for (int j = 0; j < P[i].length(); j++) {
					if (P[i][j] == '-') {
						leftlen = j;
						rightlen = P[i].length() - leftlen - 2;
						break;
					}
				}
				if ((leftlen == 1) && (P[i][leftlen - 1] < 'A' || P[i][leftlen - 1] > 'Z')) {
					//产生式左部是一个非终结符
					cout << "存在产生式的左部长度为1，但不是非终结符，该文法不是2型文法" << endl;
					return false;
				}
				else if (leftlen != 1) {
					cout << "存在产生式的左部长度不为1，该文法不是2型文法" << endl;
					return false;
				}
			}
			cout << "该文法是2型文法" << endl;
			return true;
		}
	}
	//判断是否是3型文法，首先必须是2型文法
	bool ThirdJudge() {
		if (SecondJudge()) {
			//是2型文法，进一步判断，要求只能是这两种形式：A->aB或A->a
			int leftlen = 0;
			int rightlen = 0;
			for (int i = 0; i < P.size(); i++) {
				for (int j = 0; j < P[i].length(); j++) {
					if (P[i][j] == '-') {
						leftlen = j;
						rightlen = P[i].length() - leftlen - 2;
						break;
					}
				}
				int j = P[i].length() - 1;
				if (rightlen != 2 && rightlen != 1) {
					cout << "存在产生式右部长度不为1或2，该文法不是3型文法" << endl;
					return false;
				}
				//长度为1，判断是不是终结符
				else if (rightlen == 1 && (P[i][j] < 'a' || P[i][j] > 'z')) {
					cout << "存在产生式右部长度为1，但不是终结符，该文法不是3型文法" << endl;
					return false;
				}
				else if (rightlen == 2) {
					if ((P[i][j - 1] < 'a' || P[i][j - 1]>'z') || (P[i][j] < 'A' || P[i][j]>'Z')) {
						cout << "存在产生式右部长度为2，但不为A->aB形式，该文法不是3型文法" << endl;
						return false;
					}
				}
			}
			cout << "该文法是3型文法" << endl;
			return true;
		}
	}
};

int main() {
	G firstG;
	if (firstG.readFile()) {
		firstG.LegalJudge();
		firstG.print();
		firstG.ThirdJudge();
	}
	return 0;
}