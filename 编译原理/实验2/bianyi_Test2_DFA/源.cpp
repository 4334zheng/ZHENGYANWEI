#include<iostream>
#include<string.h>
#include<fstream>
#include<vector>
#include<assert.h>
using namespace std;

struct TransitionDiagram   //״̬ת��ͼ�� 
{
	char cur, next, input;   //��ǰ״̬����һ״̬��ת������ 
	TransitionDiagram(char c, char i, char n)   //���캯�� 
	{
		cur = c;
		input = i;
		next = n;
	}
};

struct DFA_class   //DFA�ṹ�� 
{
	string state;   //״̬�� 
	string letter;   //�ַ��� 
	string start_state;   //��ʼ״̬��ʵ��ʹ��ʱֻȡһ����Ҳ�����ַ�����[0]λ�� 
	string end_state;   //����״̬�������Զ�� 
	int count;   //�����������ַ������� 
	vector<TransitionDiagram>Trans_Rule;   //ת���������飬��������������涨���class 
}DFA;   //һ��DFA���� 

int find_letter(char a, string s)   //��һ���ַ���s�в����Ƿ����ַ�a 
{
	int len = s.length();
	for (int i = 0; i < len; i++)
	{
		if (a == s[i])
			return 1;
	}
	return 0;
}

int Check_letter(string a)   //���ҵ�ǰ�ַ���a�Ƿ���Ԫ���ظ������ظ��򷵻�0 
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

int find_start_state(string a)   //��������Ŀ�ʼ״̬�Ƿ�����״̬�� 
{
	for (int i = 0; i < DFA.state.length(); i++)
	{
		if (a[0] == DFA.state[i])
			return 1;
	}
	return 0;
}

int find_end_state(string a)   //��������Ľ���״̬�Ƿ������״̬�� 
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

int Check_rule(string a)   //���������ת������Ϸ��ԣ�ת�������Ƿ������ַ�����ת��״̬֮���Ƿ������״̬�� 
{
	if (find_letter(a[0], DFA.state) && find_letter(a[1], DFA.letter) && find_letter(a[2], DFA.state))
		return 1;
	return 0;
}

char move(char c, char ii)   //����ܹ������е�ת������ƥ�䣬���ƶ���ǰ״̬����һ�������򷵻��ض��ַ� 
{
	for (int i = 0; i < DFA.Trans_Rule.size(); i++)
	{
		if (DFA.Trans_Rule[i].cur == c && DFA.Trans_Rule[i].input == ii)   //����ܹ�ƥ��ת����������ô��ת����һ��״̬ 
		{
			return DFA.Trans_Rule[i].next;
		}
	}
	return '?';   //�������ƥ�䣬��ô����һ���ʺŴ������״̬ 
}

void init_and_input()   //�������ݵĺ��������������ݺϷ��Լ�� 
{
	DFA.count = 0;
	char Rule[4];
	bool flag = false;

	//�����ַ���
	do {
		if (Check_letter(DFA.letter) == 0)
			cout << "�ַ��ظ���������";
		cout << "�����ַ���(������ĸ����abc)��";
		cin >> DFA.letter;
	} while (Check_letter(DFA.letter) == 0);

	DFA.letter += 'O';   //�����ַ���֮�����ַ�����������һ��O����others 

	//����״̬��
	do {
		if (Check_letter(DFA.state) == 0)
			cout << "״̬�ظ���������";
		cout << "����״̬��(�������֣���123)��";
		cin >> DFA.state;
	} while (Check_letter(DFA.state) == 0);

	do {
		if (find_start_state(DFA.start_state) == 0 && flag == true || DFA.start_state.length() > 1)
			cout << "��ʼ״̬�������������";
		cout << "�����뿪ʼ״̬(��������״̬���е�����һ������1)��";
		cin >> DFA.start_state;
		flag = true;
	} while (find_start_state(DFA.start_state) == 0 || DFA.start_state.length() > 1);

	do {
		if (find_end_state(DFA.end_state) == 0)
			cout << "����״̬���������������";
		cout << "���������״̬��(��������״̬�������������23)��";
		cin >> DFA.end_state;
	} while (find_end_state(DFA.end_state) == 0);

	cout << "������״̬ת������ʽΪq1aq2����ǰ״̬ת��������һ״̬����O���������ַ��������Ǻš�*��ֹͣ��" << endl;
	while (cin >> Rule)
	{
		if (Rule[0] == '*')
			break;
		else if (Check_rule(Rule))
			DFA.Trans_Rule.push_back(TransitionDiagram(Rule[0], Rule[1], Rule[2]));
		else
			cout << "ת���������������״̬���ַ��Ƿ��ڷ�Χ�ڡ�" << endl;
	}
}

void write()   //��DFA������д��lab1.dfa�ļ� 
{
	fstream ff("lab1.txt", ios::out);
	ff << "�ַ�����" << DFA.letter.substr(0, DFA.letter.length() - 1) << endl;   //�����ַ�����ʱ����Ҫȥ�����һ��Ԫ�أ���Ϊ���һ��Ĭ��O���ַ����� 
	ff << "״̬����" << DFA.state << endl;
	ff << "��ʼ״̬��" << DFA.start_state << endl;
	ff << "����״̬����" << DFA.end_state << endl;
	ff << "״̬ת����" << endl;
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
	cout << "DFA���ż���" << DFA.letter << endl;
	cout << "DFA״̬����" << DFA.state << endl;
	cout << "DFA��ʼ���ţ�" << DFA.start_state << endl;
	cout << "DFA���ռ��ϣ�" << DFA.end_state << endl;
	DFA.letter += 'O';
	cout << "DFAת��������" << endl;
	while (!ff.eof())
	{
		ff >> tmp;
		//������Ҫ�����һ��ɾ�������ļ��е�ת����������һ��
		DFA.Trans_Rule.push_back(TransitionDiagram(tmp[0], tmp[1], tmp[2]));
	}
	for (int i = 0; i < DFA.Trans_Rule.size(); i++) {
		cout << DFA.Trans_Rule[i].cur<<DFA.Trans_Rule[i].input<<DFA.Trans_Rule[i].next<< endl;
	}
	cout << "�ļ���ȡ��ϣ�" << endl;
	ff.close();
}

void identify(string s)   //���һ���ַ���s�Ƿ��ܹ�����ǰ��DFA���� 
{
	char cur_state = DFA.start_state[0];
	int len = 0;
	while (len < s.length())
	{
		string tmp = "";
		for (int i = 0; i < DFA.Trans_Rule.size(); i++)   //�����һ������ƥ�䲻���κ�ȷ����ת����������ôƥ��һ��others 
		{
			if (cur_state == DFA.Trans_Rule[i].cur && DFA.Trans_Rule[i].input != 'O')
				tmp += DFA.Trans_Rule[i].input;
		}
		if (find_letter(s[len], tmp) == 0)
			s[len] = 'O';   //���۵�ǰ������ʲô��ֻҪƥ�䲻��ȷ���Ĺ��򣬶�����ǰλ��Ϊothers 
		cur_state = move(cur_state, s[len]);   //�����ַ�����ÿһ��Ԫ�أ�������DFA״̬ת��������ƶ� 
		if (len == s.length() - 1 && find_letter(cur_state, DFA.end_state) == 0)
		{
			cout << "���ַ������ܱ�DFA���ա�" << endl;
			break;
		}
		len++;
	}
	if (find_letter(cur_state, DFA.end_state))
		cout << "���ַ����ܱ�DFA���ա�" << endl;
}

void generate(char cur_state, int num, string tmp = "")   //�������г��Ȳ�����num�ҷ���DFA���ַ��� 
{
	if (cur_state == '?' || num < 0)   //�����ǰ״̬�Ǵ���ģ����߳��ȳ������ƣ�Ӧ��ֹͣ�ݹ飬�ص���һ�� 
		return;
	num--;   //������һ��ݹ飬�����ַ�����һ�� 
	if (DFA.end_state.find(cur_state) != DFA.end_state.npos)   //�����ǰ״̬�ڽ���״̬���б��ҵ��ˣ�����DFA�ܹ������ַ��� 
	{
		cout << tmp << endl;   //������ַ������������Ҫ����ַ���������һ 
		DFA.count++;
	}
	for (int i = 0; i < DFA.letter.length(); i++)   //�о����п��ܵ��ַ��������һһ�ж� 
	{
		tmp += DFA.letter[i];
		generate(move(cur_state, DFA.letter[i]), num, tmp);   //����ǰ���ַ���ѭ�������ַ����е�ÿһ��Ԫ�أ�һһ���еݹ��ж� 
		tmp.erase(tmp.length() - 1, 1);   //��������ַ�֮�󣬸��ַ�����ת������״̬�򳤶ȳ��ޣ���ô��Ҫ���ص��������Ҫȥ���ոռ��ϵ��Ǹ�������Ҫ����ַ� 
	}
}

int main()
{
	int choice, n;
	cout << "��ѡ��õ�DFA�ķ�ʽ��1-�ֶ����룻2-ͨ���ļ���ȡ����ѡ��";
	cin >> choice;
	if(choice == 1){
		//ֱ�����룬��������д��txt�ļ�
		cout << "�밴����ʾ�ֶ�����DFA��" << endl;
		init_and_input();
		write(); //������д���ļ���
	}
	else if (choice == 2) {
		//���ļ��ж���DFA�Ķ��壬�ļ�������.dfa��ʽ�ļ�
		read();
	}
	else {
		cout << "�������!" << endl;
	}

	cout << "������һ��������������DFA���Ȳ����ڸ������������ַ�����";
	cin >> n;
	generate(DFA.start_state[0], n);
	cout << "һ��������" << DFA.count << "�������������ַ�����" << endl;
	cout << "����һ���ַ������ж��Ƿ������DFA��";
	string s;
	cin >> s;
	identify(s);
	return 0;
}