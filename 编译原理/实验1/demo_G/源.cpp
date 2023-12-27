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
	vector<char>temp1; //��¼��д
	vector<char>temp2; //��¼Сд
	//string *P;
	vector<string>P;
	char S;
public:
	//��ȡ�ļ�
	bool readFile() {
		//��ȡtxt�ļ���infileΪ�����ļ���outfileΪ����ļ�
		ifstream infile;
		//infile.open("C:\\Users\\4334\\Desktop\\����\\���\\����ԭ��\\ʵ��1\\demo_G.txt");
		//infile.open("C:\\Users\\4334\\Desktop\\����\\���\\����ԭ��\\ʵ��1\\demo2.txt");
		//infile.open("C:\\Users\\4334\\Desktop\\����\\���\\����ԭ��\\ʵ��1\\demo3.txt");
		infile.open("C:\\Users\\4334\\Desktop\\����\\���\\����ԭ��\\ʵ��1\\demo4.txt");
		if (!infile)
		{
			cout << "�޷����ļ�" << endl;
			exit(1);
		}
		//��ȡtxt�ļ��е�ÿһ��
		string ch;
		stack<char>CapitalLetter;
		stack<char>LowercaseLetter;
		int cnt = 0; //���ڱ�ʶ�Ƿ���ڲ���ʽ�Ҳ�ֻ��Сд��ĸ
		int flag = 0; //���ڱ�ʶ����Ƿ�ֻ��Сд��ĸ
		while (getline(infile, ch)) {
			cnt = 0;
			flag = 0;
			cout << ch << endl;
			P.push_back(ch);
			//����ÿһ�У��ҵ���ͷλ�ã������ҽ����ж�
			char* ch_left; //��¼���ַ�
			char* ch_right; //��¼�Ҳ��ַ�
			int left_len = 0;
			int right_len = 0;
			for (int i = 0; i < ch.length(); i++) {
				if (ch[i] >= 'A' && ch[i] <= 'Z') {
					CapitalLetter.push(ch[i]); //��¼��д�ַ�
				}
				else if (ch[i] >= 'a' && ch[i] <= 'z') {
					LowercaseLetter.push(ch[i]); //��¼Сд�ַ�
				}
				else if (ch[i] == '-') {
					//������Ҳ����ַ�����
					left_len = i;
					right_len = ch.length() - left_len - 2;
				}
			}

			if (left_len == 0 || right_len == 0) {
				cout << "Error!�޷����ɺϷ����ķ�" << endl;
				return false;
			}
			else {
				//���Ҳ�Ϊ0�����ռ��ţ����н�һ���ж�
				ch_left = new char[left_len];
				ch_right = new char[right_len];
			}

			//�õ�������ĸ����
			for (int i = 0; i < left_len; i++)
			{
				ch_left[i] = ch[i];
				//cout << ch_left[i] << " ";
				//����д�д��ĸ
				if (ch_left[i] >= 'A' && ch_left[i] <= 'Z') {
					flag = 1;
				}
			}
			//cout << endl;
			for (int i = 0, j = left_len + 2; i < right_len; i++, j++) {
				ch_right[i] = ch[j];
				//cout << ch_right[i] << " ";
				if (ch_right[i] >= 'A' && ch_right[i] <= 'Z') {
					cnt = 1; //����ʽ�Ҳ��д�д��cnt��ʶΪ1
				}
			}
			//cout << endl;
		}
		if (cnt == 1 || flag == 0) {
			//ÿһ�в���ʽ����cnt��ֵ��Ϊ1����ÿһ�в���ʽ���Ҳ඼�д�д�����Ϸ�
			//����һ��û���޸�flag��ֵ�����û�д�д��ĸ�����Ϸ�
			cout << "����ʽ�Ҳ���д�д���޷����������Ϸ�!" << endl;
			return false;
		}
		//�Ѵ�Сд����Ų��vector������һ������
		while (!CapitalLetter.empty()) {
			temp1.push_back(CapitalLetter.top());
			CapitalLetter.pop();
		}
		//���ֵ��׸��ַ�ΪS
		S = temp1[temp1.size() - 1];
		while (!LowercaseLetter.empty()) {
			temp2.push_back(LowercaseLetter.top());
			LowercaseLetter.pop();
		}
		//�Ϸ����жϽ�����������ս�����ս���������ķ�
		cout << "ÿһ���жϽ��������Թ����ķ�" << endl;
		return true;
	}

	void LegalJudge() {
		/*
		cout << "��д��ĸ��";
		while (!CapitalLetter.empty()) {
			cout << CapitalLetter.top() << " ";
			CapitalLetter.pop();
		}
		cout << endl << "Сд��ĸ��";
		while (!LowercaseLetter.empty()) {
			cout << LowercaseLetter.top() << " ";
			LowercaseLetter.pop();
		}
		cout << endl;
		*/

		//ʹ��vectorʵ�������ȥ���Լ��������
		sort(temp1.begin(), temp1.end());
		temp1.erase(unique(temp1.begin(), temp1.end()), temp1.end());//ȥ���ظ�Ԫ��
		cout << "���з��ս��:";
		for (auto x1 : temp1)
			cout << x1 << " ";
		cout << endl;

		sort(temp2.begin(), temp2.end());
		temp2.erase(unique(temp2.begin(), temp2.end()), temp2.end());//ȥ���ظ�Ԫ��
		cout << "�����ս��:";
		for (auto x2 : temp2)
			cout << x2 << " ";
		cout << endl;
	}
	void print() {
		int size1 = temp1.size();
		int size2 = temp2.size();
		cout << "�����ķ�Ϊ��G=({";
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

	//�жϺϷ���Ϊ0���ķ���ʹ������õ��Ĳ���ʽ��P�����ķ����͵��ж�
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
				cout << "���ڲ���ʽ���󲿳��ȴ����Ҳ����ȣ����ķ�����1���ķ�" << endl;
				return false;
			}
		}
		cout << "���ķ���1���ķ�" << endl;
		return true;
	}
	//�ж��Ƿ���2���ķ������ȱ�����1���ķ�
	bool SecondJudge() {
		if (FirstJudge()) {
			//��1���ķ�����һ���жϡ�Ҫ�����ʽ����߱�����һ�����ս��
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
					//����ʽ����һ�����ս��
					cout << "���ڲ���ʽ���󲿳���Ϊ1�������Ƿ��ս�������ķ�����2���ķ�" << endl;
					return false;
				}
				else if (leftlen != 1) {
					cout << "���ڲ���ʽ���󲿳��Ȳ�Ϊ1�����ķ�����2���ķ�" << endl;
					return false;
				}
			}
			cout << "���ķ���2���ķ�" << endl;
			return true;
		}
	}
	//�ж��Ƿ���3���ķ������ȱ�����2���ķ�
	bool ThirdJudge() {
		if (SecondJudge()) {
			//��2���ķ�����һ���жϣ�Ҫ��ֻ������������ʽ��A->aB��A->a
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
					cout << "���ڲ���ʽ�Ҳ����Ȳ�Ϊ1��2�����ķ�����3���ķ�" << endl;
					return false;
				}
				//����Ϊ1���ж��ǲ����ս��
				else if (rightlen == 1 && (P[i][j] < 'a' || P[i][j] > 'z')) {
					cout << "���ڲ���ʽ�Ҳ�����Ϊ1���������ս�������ķ�����3���ķ�" << endl;
					return false;
				}
				else if (rightlen == 2) {
					if ((P[i][j - 1] < 'a' || P[i][j - 1]>'z') || (P[i][j] < 'A' || P[i][j]>'Z')) {
						cout << "���ڲ���ʽ�Ҳ�����Ϊ2������ΪA->aB��ʽ�����ķ�����3���ķ�" << endl;
						return false;
					}
				}
			}
			cout << "���ķ���3���ķ�" << endl;
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