#include <iostream>
#include <string>
#include<fstream>
using namespace std;
int dfa[5][3] = {
    {1, 2, 4},
    {1, 1, 3},
    {3, 2, 3},
    {3, 3, 3},
    {4, 4, 4}
};
int main() {
    std::ifstream infile("C:/Users/4334/Desktop/����/���/����ԭ��/ʵ��2/input.txt");//���ļ�
    if (!infile.is_open()) {
        std::cerr << "Failed to open file" << std::endl;
        return 1;
    }
    std::string line;
    while (std::getline(infile, line)) {
        //string input_str = "for(int i=0;i<=100;i++){sum += i;}";
        int state = 0;
        string token = "";
        for (auto c : line) {
            int type = 0;
            if (isalpha(c) || c == '_') {
                type = 0;  // ��ĸ
            }
            else if (isdigit(c)) {
                type = 1;  // ����
            }
            else {
                type = 2;  // �����ַ�
            }
            state = dfa[state][type];
            if (state == 1 || state == 2) {
                token += c;
            }
            else if (state == 3) {
                if (!token.empty()) {
                    if (isdigit(token[0])) {
                        // ͨ�������ַ����е�ÿ���ַ�������ת��Ϊ��ֵ�������ַ�ת��ֵ��ʽ
                        int value = 0;
                        for (auto c : token) {
                            value = value * 10 + (c - '0');
                        }
                        cout << "�޷�������" << value << endl;
                    }
                    else {
                        cout << "��ʶ����" << token << endl;
                    }
                }
                //����token��state
                token = "";
                state = 0;
            }
            else if (state == 4) {
                cout << "��֧�ֵ��ַ���" << c << endl;
                token = "";
                state = 0;
            }
        }
        if (token.empty()) {
            cout << "��ǰ���в����ڱ�ʶ�����޷�����" << endl;
        }
        //������һ���Ӵ�û���з���ϣ�����Ҫ�ٴν����ж�
        if (!token.empty()) {
            if (isdigit(token[0])) {
                int value = 0;
                for (auto c : token) {
                    value = value * 10 + (c - '0');
                }
                cout << "�޷�������" << value << endl;
            }
            else {
                cout << "��ʶ����" << token << endl;
            }
        }
    }
    infile.close();//�ر��ļ�
    return 0;
}