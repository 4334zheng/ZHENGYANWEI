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
    std::ifstream infile("C:/Users/4334/Desktop/自用/深大/编译原理/实验2/input.txt");//打开文件
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
                type = 0;  // 字母
            }
            else if (isdigit(c)) {
                type = 1;  // 数字
            }
            else {
                type = 2;  // 其他字符
            }
            state = dfa[state][type];
            if (state == 1 || state == 2) {
                token += c;
            }
            else if (state == 3) {
                if (!token.empty()) {
                    if (isdigit(token[0])) {
                        // 通过遍历字符串中的每个字符，将其转换为数值，单个字符转数值形式
                        int value = 0;
                        for (auto c : token) {
                            value = value * 10 + (c - '0');
                        }
                        cout << "无符号数：" << value << endl;
                    }
                    else {
                        cout << "标识符：" << token << endl;
                    }
                }
                //重置token和state
                token = "";
                state = 0;
            }
            else if (state == 4) {
                cout << "不支持的字符：" << c << endl;
                token = "";
                state = 0;
            }
        }
        if (token.empty()) {
            cout << "当前行中不存在标识符或无符号数" << endl;
        }
        //如果最后一个子串没有切分完毕，则需要再次进行判断
        if (!token.empty()) {
            if (isdigit(token[0])) {
                int value = 0;
                for (auto c : token) {
                    value = value * 10 + (c - '0');
                }
                cout << "无符号数：" << value << endl;
            }
            else {
                cout << "标识符：" << token << endl;
            }
        }
    }
    infile.close();//关闭文件
    return 0;
}