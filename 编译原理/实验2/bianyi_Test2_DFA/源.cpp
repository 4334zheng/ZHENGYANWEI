#include<iostream>
#include<string.h>
#include<fstream>
#include<vector>
#include<assert.h>
using namespace std;

struct TransitionDiagram   //状态转换图类 
{
	char cur, next, input;   //当前状态，下一状态，转换条件 
	TransitionDiagram(char c, char i, char n)   //构造函数 
	{
		cur = c;
		input = i;
		next = n;
	}
};

struct DFA_class   //DFA结构体 
{
	string state;   //状态集 
	string letter;   //字符集 
	string start_state;   //开始状态（实际使用时只取一个，也就是字符串的[0]位） 
	string end_state;   //接收状态集，可以多个 
	int count;   //符合条件的字符串个数 
	vector<TransitionDiagram>Trans_Rule;   //转换规则数组，数组的类型是上面定义的class 
}DFA;   //一个DFA对象 

int find_letter(char a, string s)   //从一个字符串s中查找是否有字符a 
{
	int len = s.length();
	for (int i = 0; i < len; i++)
	{
		if (a == s[i])
			return 1;
	}
	return 0;
}

int Check_letter(string a)   //查找当前字符串a是否有元素重复，有重复则返回0 
{
	int len = a.length();
	for (int i = 0; i < len; i++)
	{
		for (int j = i + 1; j < len; j++)
		{
			if (a[i] == a[j])
				return 0;
		}
	}
	return 1;
}

int find_start_state(string a)   //查找输入的开始状态是否属于状态集 
{
	for (int i = 0; i < DFA.state.length(); i++)
	{
		if (a[0] == DFA.state[i])
			return 1;
	}
	return 0;
}

int find_end_state(string a)   //查找输入的接收状态是否均属于状态集 
{
	int count = 0;
	int len1 = a.length();
	int len2 = DFA.state.length();
	for (int i = 0; i < len1; i++)
	{
		for (int j = 0; j < len2; j++)
		{
			if (a[i] == DFA.state[j])
			{
				count++;
				break;
			}
		}
	}
	if (count == len1)
		return 1;
	else
		return 0;
}

int Check_rule(string a)   //查找输入的转换规则合法性，转换条件是否属于字符集、转换状态之间是否均属于状态集 
{
	if (find_letter(a[0], DFA.state) && find_letter(a[1], DFA.letter) && find_letter(a[2], DFA.state))
		return 1;
	return 0;
}

char move(char c, char ii)   //如果能够和现有的转换条件匹配，就移动当前状态到下一个，否则返回特定字符 
{
	for (int i = 0; i < DFA.Trans_Rule.size(); i++)
	{
		if (DFA.Trans_Rule[i].cur == c && DFA.Trans_Rule[i].input == ii)   //如果能够匹配转换条件，那么跳转到下一个状态 
		{
			return DFA.Trans_Rule[i].next;
		}
	}
	return '?';   //如果不能匹配，那么返回一个问号代表错误状态 
}

void init_and_input()   //输入数据的函数，包括了数据合法性检查 
{
	DFA.count = 0;
	char Rule[4];
	bool flag = false;

	//输入字符集
	do {
		if (Check_letter(DFA.letter) == 0)
			cout << "字符重复，请重新";
		cout << "输入字符集(输入字母，如abc)：";
		cin >> DFA.letter;
	} while (Check_letter(DFA.letter) == 0);

	DFA.letter += 'O';   //输入字符集之后，在字符集的最后加上一个O代表others 

	//输入状态集
	do {
		if (Check_letter(DFA.state) == 0)
			cout << "状态重复，请重新";
		cout << "输入状态集(输入数字，如123)：";
		cin >> DFA.state;
	} while (Check_letter(DFA.state) == 0);

	do {
		if (find_start_state(DFA.start_state) == 0 && flag == true || DFA.start_state.length() > 1)
			cout << "开始状态输入错误，请重新";
		cout << "请输入开始状态(输入上述状态集中的其中一个，如1)：";
		cin >> DFA.start_state;
		flag = true;
	} while (find_start_state(DFA.start_state) == 0 || DFA.start_state.length() > 1);

	do {
		if (find_end_state(DFA.end_state) == 0)
			cout << "接受状态集输入错误，请重新";
		cout << "请输入接受状态集(输入上述状态集中任意个，如23)：";
		cin >> DFA.end_state;
	} while (find_end_state(DFA.end_state) == 0);

	cout << "请输入状态转换表，格式为q1aq2（当前状态转换条件下一状态），O代表其他字符，输入星号‘*’停止：" << endl;
	while (cin >> Rule)
	{
		if (Rule[0] == '*')
			break;
		else if (Check_rule(Rule))
			DFA.Trans_Rule.push_back(TransitionDiagram(Rule[0], Rule[1], Rule[2]));
		else
			cout << "转换表输入错误，请检查状态和字符是否在范围内。" << endl;
	}
}

void write()   //将DFA的属性写入lab1.dfa文件 
{
	fstream ff("lab1.txt", ios::out);
	ff << "字符集：" << DFA.letter.substr(0, DFA.letter.length() - 1) << endl;   //输入字符集的时候需要去掉最后一个元素，因为最后一个默认O在字符集内 
	ff << "状态集：" << DFA.state << endl;
	ff << "开始状态：" << DFA.start_state << endl;
	ff << "结束状态集：" << DFA.end_state << endl;
	ff << "状态转换表：" << endl;
	for (int i = 0; i < DFA.Trans_Rule.size(); i++)
		ff << DFA.Trans_Rule[i].cur << " " << DFA.Trans_Rule[i].input << " " << DFA.Trans_Rule[i].next << endl;
	ff.close();
}

void read()
{
	fstream ff("lab1.dfa", ios::in);
	assert(ff.is_open());
	string tmp;
	ff >> DFA.letter >> DFA.state >> DFA.start_state >> DFA.end_state;
	cout << "DFA符号集：" << DFA.letter << endl;
	cout << "DFA状态集：" << DFA.state << endl;
	cout << "DFA开始符号：" << DFA.start_state << endl;
	cout << "DFA接收集合：" << DFA.end_state << endl;
	DFA.letter += 'O';
	cout << "DFA转换函数：" << endl;
	while (!ff.eof())
	{
		ff >> tmp;
		//这里需要把最后一行删除，比文件中的转换函数多了一行
		DFA.Trans_Rule.push_back(TransitionDiagram(tmp[0], tmp[1], tmp[2]));
	}
	for (int i = 0; i < DFA.Trans_Rule.size(); i++) {
		cout << DFA.Trans_Rule[i].cur<<DFA.Trans_Rule[i].input<<DFA.Trans_Rule[i].next<< endl;
	}
	cout << "文件读取完毕！" << endl;
	ff.close();
}

void identify(string s)   //检测一个字符串s是否能够被当前的DFA接收 
{
	char cur_state = DFA.start_state[0];
	int len = 0;
	while (len < s.length())
	{
		string tmp = "";
		for (int i = 0; i < DFA.Trans_Rule.size(); i++)   //如果下一个输入匹配不到任何确定的转换条件，那么匹配一个others 
		{
			if (cur_state == DFA.Trans_Rule[i].cur && DFA.Trans_Rule[i].input != 'O')
				tmp += DFA.Trans_Rule[i].input;
		}
		if (find_letter(s[len], tmp) == 0)
			s[len] = 'O';   //无论当前输入是什么，只要匹配不到确定的规则，都将当前位改为others 
		cur_state = move(cur_state, s[len]);   //对于字符串的每一个元素，做基于DFA状态转换规则的移动 
		if (len == s.length() - 1 && find_letter(cur_state, DFA.end_state) == 0)
		{
			cout << "该字符串不能被DFA接收。" << endl;
			break;
		}
		len++;
	}
	if (find_letter(cur_state, DFA.end_state))
		cout << "该字符串能被DFA接收。" << endl;
}

void generate(char cur_state, int num, string tmp = "")   //生成所有长度不大于num且符合DFA的字符串 
{
	if (cur_state == '?' || num < 0)   //如果当前状态是错误的，或者长度超出限制，应当停止递归，回到上一层 
		return;
	num--;   //进入下一层递归，可用字符减少一个 
	if (DFA.end_state.find(cur_state) != DFA.end_state.npos)   //如果当前状态在接收状态集中被找到了，代表DFA能够接收字符串 
	{
		cout << tmp << endl;   //将这个字符串输出，符合要求的字符串数量加一 
		DFA.count++;
	}
	for (int i = 0; i < DFA.letter.length(); i++)   //列举所有可能的字符串情况，一一判断 
	{
		tmp += DFA.letter[i];
		generate(move(cur_state, DFA.letter[i]), num, tmp);   //将当前的字符串循环加上字符集中的每一个元素，一一进行递归判断 
		tmp.erase(tmp.length() - 1, 1);   //如果加上字符之后，该字符串跳转到错误状态或长度超限，那么需要返回到这里，必须要去掉刚刚加上的那个不符合要求的字符 
	}
}

int main()
{
	int choice, n;
	cout << "请选择得到DFA的方式：1-手动输入；2-通过文件读取。请选择：";
	cin >> choice;
	if(choice == 1){
		//直接输入，并将输入写入txt文件
		cout << "请按照提示手动输入DFA：" << endl;
		init_and_input();
		write(); //将输入写到文件中
	}
	else if (choice == 2) {
		//从文件中读入DFA的定义，文件必须是.dfa格式文件
		read();
	}
	else {
		cout << "输入错误!" << endl;
	}

	cout << "请输入一个整数，求满足DFA长度不大于该整数的所有字符串：";
	cin >> n;
	generate(DFA.start_state[0], n);
	cout << "一共有上述" << DFA.count << "个符合条件的字符串。" << endl;
	cout << "输入一个字符串，判断是否满足该DFA：";
	string s;
	cin >> s;
	identify(s);
	return 0;
}