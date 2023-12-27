#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
using namespace std;

class CFGParser {
public:
	CFGParser() {}

	//���ÿ�ʼ����
	void setStartSymbol(string s) {
		startSymbol = s;
	}
	//��Ӳ���ʽ
	void addProduction(string nonTerminal, string production) {
		cout << nonTerminal << "->" << production << endl;
		if (!productions.count(nonTerminal)) {
			//�����û��������ս���Ĳ���ʽ�б��ʹ���һ���µĿ��б�
			productions[nonTerminal] = vector<string>();
		}
		//�Ѳ���ʽ��ӵ����ս���Ĳ���ʽ�б���
		productions[nonTerminal].push_back(production);
	}

	//�ж��Ƿ�Ϊ3���ķ�
	bool isType3Grammar() {
		//����ÿ�����ս������������ÿ������ʽ
		for (auto entry : productions) {
			for (auto production : entry.second) {
				if (production.empty() || !isupper(production[0])) {
					//�������ʽΪ�ջ������ս����ͷ��������
					continue;
				}
				if (production.length() > 1 || !islower(production[0])) {
					//�������ʽ���ȴ���1�����Է�Сд��ĸ��ͷ���Ͳ���3���ķ�
					return false;
				}
			}
		}
		//������в���ʽ����������������3���ķ�
		return true;
	}

	//�жϸ������Ŵ��ܷ��ɿ�ʼ�����Ƶ�����
	bool canDerive(string input) {
		cout << "�������Ŵ�:" << input << endl;
		if (!isType3Grammar()) {
			//�������3���ķ������޷������Ƶ�
			cout << "���ķ�����3���ķ����޷������Ƶ���������" << endl;
			return false;
		}
		//�ӿ�ʼ���ſ�ʼ�����Ƶ�
		return derive(startSymbol, input);
	}
private:
	//��ʼ����
	string startSymbol;
	//���ս���Ͳ���ʽ�б�
	unordered_map<string, vector<string>> productions;

	//�ж��Ƿ��ܴӷ��ս���Ƶ��������ķ��Ŵ�
	bool derive(string nonTerminal, string input) {
		if (input.empty()) {
			//������Ŵ��Ѿ�Ϊ�գ�����Ҫ�ڷ��ս���Ĳ���ʽ�б��в��ҿղ���ʽ
			return find(productions[nonTerminal].begin(), productions[nonTerminal].end(), "") != productions[nonTerminal].end();
		}
		//����ÿ������ʽ���������ķ�������
		for (auto production : productions[nonTerminal]) {
			if (production.empty()) {
				//�������ʽΪ�գ�������
				continue;
			}
			//�ѷ������н���Ϊһ��������
			vector<string>symbols;
			size_t i = 0;
			while (i < production.length()) {
				//�ж��Ƿ���һ���ս��                                                                                                                                                                                                                                                                                          
				if (production[i] == '\"') {
					size_t j = i + 1;
					while (j < production.length() && production[j] != '\"') {
						j++;
					}
					symbols.push_back(production.substr(i, j - i + 1));
				}
				else {
					//���򣬾���һ�����ս��
					symbols.push_back(string(1, production[i]));
				}
				i++;
			}
			//����������еĳ��ȴ��ڷ��Ŵ��ĳ��ȣ�������
			if (symbols.size() > input.length()) {
				continue;
			}
			//���ڷ������кͷ��Ŵ���ÿһλ���бȽ�
			bool matched = true;
			for (size_t i = 0; i < symbols.size(); i++) {
				if (isupper(symbols[i][0])) {
					//����Ƿ��ս�������ڲ���ʽ�б��в����Ƿ����Ƶ�����Ӧ�ķ��Ŵ�
					matched = matched && derive(symbols[i], input.substr(i, input.length() - i));
				}
				else {
					//������ս����ֱ�ӱȽ��Ƿ����
					matched = matched && (symbols[i] == input.substr(i, 1));
				}
				if (!matched) {
					//���ƥ��ʧ�ܣ�������һ������ʽ
					break;
				}
			}
			if (matched) {
				//���ƥ��ɹ��������ݹ�
				return true;
			}
		}
		//���в���ʽ�����Թ��ˣ�����û��ƥ��ɹ����ͷ���false
		return false;
	}
};

int main()
{
	//����һ��CFGParser����
	CFGParser parser;
	//��Ӳ���ʽ
	parser.addProduction("S", "aA");
	parser.addProduction("A", "aA");
	parser.addProduction("A", "b");
	//���ÿ�ʼ����
	parser.setStartSymbol("S");
	//�ж��Ƿ�Ϊ3���ķ�
	if (parser.isType3Grammar()) {
		cout << "���ķ���3���ķ��������������Ƶ��ж�" << endl;
		//�жϸ������Ŵ��ܷ��Ƶ�����
		if (parser.canDerive("ab")) {
			cout << "�������Ŵ��ܹ����Ƶ�����" << endl;
		}
		else {
			cout << "�������Ŵ����ܱ��Ƶ�����" << endl;
		}
	}
	else {
		cout << "���ķ�����3���ķ���Ҳ���ܽ����Ƶ�" << endl;
	}
	return 0;
}