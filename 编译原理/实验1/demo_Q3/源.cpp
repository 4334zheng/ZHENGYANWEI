#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
using namespace std;

class CFGParser {
public:
	CFGParser() {}

	//设置开始符号
	void setStartSymbol(string s) {
		startSymbol = s;
	}
	//添加产生式
	void addProduction(string nonTerminal, string production) {
		cout << nonTerminal << "->" << production << endl;
		if (!productions.count(nonTerminal)) {
			//如果还没有这个非终结符的产生式列表，就创建一个新的空列表
			productions[nonTerminal] = vector<string>();
		}
		//把产生式添加到非终结符的产生式列表中
		productions[nonTerminal].push_back(production);
	}

	//判断是否为3型文法
	bool isType3Grammar() {
		//对于每个非终结符，遍历它的每个产生式
		for (auto entry : productions) {
			for (auto production : entry.second) {
				if (production.empty() || !isupper(production[0])) {
					//如果产生式为空或者以终结符开头，就跳过
					continue;
				}
				if (production.length() > 1 || !islower(production[0])) {
					//如果产生式长度大于1或者以非小写字母开头，就不是3型文法
					return false;
				}
			}
		}
		//如果所有产生式都满足条件，就是3型文法
		return true;
	}

	//判断给定符号串能否由开始符号推导出来
	bool canDerive(string input) {
		cout << "给定符号串:" << input << endl;
		if (!isType3Grammar()) {
			//如果不是3型文法，就无法进行推导
			cout << "该文法不是3型文法，无法进行推导，结束！" << endl;
			return false;
		}
		//从开始符号开始进行推导
		return derive(startSymbol, input);
	}
private:
	//开始符号
	string startSymbol;
	//非终结符和产生式列表
	unordered_map<string, vector<string>> productions;

	//判断是否能从非终结符推导出给定的符号串
	bool derive(string nonTerminal, string input) {
		if (input.empty()) {
			//如果符号串已经为空，就需要在非终结符的产生式列表中查找空产生式
			return find(productions[nonTerminal].begin(), productions[nonTerminal].end(), "") != productions[nonTerminal].end();
		}
		//对于每个产生式，分析它的符号序列
		for (auto production : productions[nonTerminal]) {
			if (production.empty()) {
				//如果产生式为空，就跳过
				continue;
			}
			//把符号序列解析为一个个符号
			vector<string>symbols;
			size_t i = 0;
			while (i < production.length()) {
				//判断是否是一个终结符                                                                                                                                                                                                                                                                                          
				if (production[i] == '\"') {
					size_t j = i + 1;
					while (j < production.length() && production[j] != '\"') {
						j++;
					}
					symbols.push_back(production.substr(i, j - i + 1));
				}
				else {
					//否则，就是一个非终结符
					symbols.push_back(string(1, production[i]));
				}
				i++;
			}
			//如果符号序列的长度大于符号串的长度，就跳过
			if (symbols.size() > input.length()) {
				continue;
			}
			//对于符号序列和符号串的每一位进行比较
			bool matched = true;
			for (size_t i = 0; i < symbols.size(); i++) {
				if (isupper(symbols[i][0])) {
					//如果是非终结符，就在产生式列表中查找是否能推导出对应的符号串
					matched = matched && derive(symbols[i], input.substr(i, input.length() - i));
				}
				else {
					//如果是终结符，直接比较是否相等
					matched = matched && (symbols[i] == input.substr(i, 1));
				}
				if (!matched) {
					//如果匹配失败，尝试下一个产生式
					break;
				}
			}
			if (matched) {
				//如果匹配成功，结束递归
				return true;
			}
		}
		//所有产生式都尝试过了，但是没有匹配成功，就返回false
		return false;
	}
};

int main()
{
	//创建一个CFGParser对象
	CFGParser parser;
	//添加产生式
	parser.addProduction("S", "aA");
	parser.addProduction("A", "aA");
	parser.addProduction("A", "b");
	//设置开始符号
	parser.setStartSymbol("S");
	//判断是否为3型文法
	if (parser.isType3Grammar()) {
		cout << "该文法是3型文法，接下来进行推导判断" << endl;
		//判断给定符号串能否推导出来
		if (parser.canDerive("ab")) {
			cout << "给定符号串能够被推导出来" << endl;
		}
		else {
			cout << "给定符号串不能被推导出来" << endl;
		}
	}
	else {
		cout << "该文法不是3型文法，也不能进行推导" << endl;
	}
	return 0;
}