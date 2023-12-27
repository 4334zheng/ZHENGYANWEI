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
    return keywords.count(str) > 0; //unordered_set�У�ͳ��str��keywords�г��ֵĴ���
}
bool isOperator(string str) {
    unordered_set<string> operators = { "+", "-", "*", "/", "=", "==", "!=", "<", ">", "<=", ">=" };
    return operators.count(str) > 0;
}
bool isSeparator(char ch) {
    unordered_set<char> separators = { ';',',','{','}','[',']','(',')' };
    return separators.count(ch) > 0;
}

//����0�������ģ�����1��������
int IncludeChinese(string s)
{
    const char* str = s.data();
    char c;
    while (1)
    {
        c = *str++;
        if (c == 0) break;  //������ַ���β��˵�����ַ���û�������ַ�
        if (c & 0x80)        //����ַ���λΪ1����һ�ַ���λҲ��1���������ַ�
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
        cout << "�ַ����а������ģ�" << endl;
        return 0;
    }
    if (input.length() == 0) {
        cout << "������ַ���Ϊ��" << endl;
        return 0;
    }
    string current_token = "";
    for (int i = 0; i < input.length(); i++) {
        char ch = input[i];
        if (isalpha(ch)) { // ��ĸ
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
        else if (isSeparator(ch)) { // �ָ���
            sepword.push_back(ch);
        }
        else if (isOperator(string(1, ch))) { // �����
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
    cout << "����DFA������ʱ�䣺" << duration.count() << "ms" << endl;
    //�Թؼ��֡��ָ��������������ȥ�ز��������
    if (keyword.size() == 0) {
        cout << "ƥ�䲻���κιؼ���" << endl;
    }
    else {
        sort(keyword.begin(), keyword.end()); // ��vector����
        keyword.erase(unique(keyword.begin(), keyword.end()), keyword.end()); // ȥ��
        cout << "������ַ����У�ƥ�䵽�Ĺؼ��ּ�Ϊ��";
        for (const auto& s : keyword) {
            cout << s << " ";
        }
        cout << endl;
    }
    if (opeword.size() == 0) {
        cout << "ƥ�䲻���κ������" << endl;
    }
    else {

        sort(opeword.begin(), opeword.end());
        opeword.erase(unique(opeword.begin(), opeword.end()), opeword.end());
        cout << endl << "������ַ����У�ƥ�䵽���������Ϊ��";
        for (const auto& s : opeword) {
            cout << s << " ";
        }
        cout << endl;
    }
    if (sepword.size() == 0) {
        cout << "ƥ�䲻���κηָ���" << endl;
    }
    else {
        sort(sepword.begin(), sepword.end());
        sepword.erase(unique(sepword.begin(), sepword.end()), sepword.end());
        cout << endl << "������ַ����У�ƥ�䵽�ķָ�����Ϊ��";
        for (const auto& c : sepword) {
            cout << c << " ";
        }
        cout << endl;

    }
    return 0;
}

/*
//��ν�����ǰ״̬�������ַ������д�����һ״̬���Ļ���DFA������ɴ���
//α����
//����ö������State
enum State {
    State0,
    State1,
    //����״̬
};
//���崦����ProcessFunc
typedef void(*ProcessFunc)(char);
//����״̬ת������StateTransFunc
typedef State(*StateTransFunc)(char);
//�������ɸ�������
void Process0(char ch) {
    //����State0
}
//����״̬�Ĵ�����
//�������ɸ�״̬ת������
State StateTran0(char ch) {
    //�����State0�����ַ�ch�����һ״̬
}
//����״̬ת������
//����ָ������洢��������״̬ת������
ProcessFunc p_Funcs[] = {
    Process0,
    //����������
};
StateTransFunc s_Funcs[] = {
    StateTran0,
    //����״̬ת������
};
//ȷ����ǰ״̬state������ѭ������������ַ���
//��ѭ���ڣ����ö�Ӧ��s_Funcs[state]��p_Funcs[state]������һ״̬�ļ���ʹ������µ�ǰ״̬
*/
