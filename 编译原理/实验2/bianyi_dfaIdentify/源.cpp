#include <iostream>
#include <string>
#include<vector>
#include <unordered_set>
#include<algorithm>
#include<chrono>
#include<regex>
#include<locale>
#include<codecvt>
using namespace std;
using namespace std::chrono;
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
    return keywords.count(str) > 0; //unordered_set中，统计str在keywords中出现的次数
}
bool isOperator(string str) {
    unordered_set<string> operators = { "+", "-", "*", "/", "=", "==", "!=", "<", ">", "<=", ">=" };
    return operators.count(str) > 0;
}
bool isSeparator(char ch) {
    unordered_set<char> separators = { ';',',','{','}','[',']','(',')' };
    return separators.count(ch) > 0;
}

//返回0：无中文，返回1：有中文
int IncludeChinese(string s)
{
    const char* str = s.data();
    char c;
    while (1)
    {
        c = *str++;
        if (c == 0) break;  //如果到字符串尾则说明该字符串没有中文字符
        if (c & 0x80)        //如果字符高位为1且下一字符高位也是1则有中文字符
            if (*str & 0x80) return 1;
    }
    return 0;
}
int main() {
    string input;
    vector<string>keyword;
    vector<string>opeword;
    vector<char>sepword;
    auto start = high_resolution_clock::now();
    cout << "please input your string based on C++: ";
    getline(cin, input);
    if (IncludeChinese(input)) {
        cout << "字符串中包含中文！" << endl;
        return 0;
    }
    if (input.length() == 0) {
        cout << "输入的字符串为空" << endl;
        return 0;
    }
    string current_token = "";
    for (int i = 0; i < input.length(); i++) {
        char ch = input[i];
        if (isalpha(ch)) { // 字母
            current_token += ch;
            while (i + 1 < input.length() && (isalpha(input[i + 1]))) {
                i++;
                current_token += input[i];
            }
            if (isKeyword(current_token)) {
                keyword.push_back(current_token);
            }
            current_token = "";
        }
        else if (isSeparator(ch)) { // 分隔符
            sepword.push_back(ch);
        }
        else if (isOperator(string(1, ch))) { // 运算符
            current_token += ch;
            while (i + 1 < input.length() && isOperator(current_token + input[i + 1])) {
                i++;
                current_token += input[i];
            }
            opeword.push_back(current_token);
            current_token = "";
        }
    }
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    cout << "基于DFA的运行时间：" << duration.count() << "ms" << endl;
    //对关键字、分隔符和运算符进行去重并进行输出
    if (keyword.size() == 0) {
        cout << "匹配不到任何关键字" << endl;
    }
    else {
        sort(keyword.begin(), keyword.end()); // 将vector排序
        keyword.erase(unique(keyword.begin(), keyword.end()), keyword.end()); // 去重
        cout << "在这个字符串中，匹配到的关键字集为：";
        for (const auto& s : keyword) {
            cout << s << " ";
        }
        cout << endl;
    }
    if (opeword.size() == 0) {
        cout << "匹配不到任何运算符" << endl;
    }
    else {

        sort(opeword.begin(), opeword.end());
        opeword.erase(unique(opeword.begin(), opeword.end()), opeword.end());
        cout << endl << "在这个字符串中，匹配到的运算符集为：";
        for (const auto& s : opeword) {
            cout << s << " ";
        }
        cout << endl;
    }
    if (sepword.size() == 0) {
        cout << "匹配不到任何分隔符" << endl;
    }
    else {
        sort(sepword.begin(), sepword.end());
        sepword.erase(unique(sepword.begin(), sepword.end()), sepword.end());
        cout << endl << "在这个字符串中，匹配到的分隔符集为：";
        for (const auto& c : sepword) {
            cout << c << " ";
        }
        cout << endl;

    }
    return 0;
}

/*
//如何将“当前状态，遇到字符，进行处理，下一状态”的基本DFA描述变成代码
//伪代码
//定义枚举类型State
enum State {
    State0,
    State1,
    //其他状态
};
//定义处理函数ProcessFunc
typedef void(*ProcessFunc)(char);
//定义状态转换函数StateTransFunc
typedef State(*StateTransFunc)(char);
//定义若干个处理函数
void Process0(char ch) {
    //处理State0
}
//其他状态的处理函数
//定义若干个状态转换函数
State StateTran0(char ch) {
    //计算从State0输入字符ch后的下一状态
}
//其他状态转换函数
//函数指针数组存储处理函数和状态转换函数
ProcessFunc p_Funcs[] = {
    Process0,
    //其他处理函数
};
StateTransFunc s_Funcs[] = {
    StateTran0,
    //其他状态转换函数
};
//确定当前状态state，设置循环遍历输入的字符串
//在循环内：调用对应的s_Funcs[state]和p_Funcs[state]进行下一状态的计算和处理，更新当前状态
*/
