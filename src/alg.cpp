#include <string>
#include <map>
#include <cctype>
#include "tstack.h"

int getOpPriority(char op) {
    if (op == '(') return 0;
    if (op == ')') return 1;
    if (op == '+' || op == '-') return 2;
    if (op == '*' || op == '/') return 3;
    return -1;
}

bool checkIsOperator(char c) {
    if (c == '+' || c == '-' || c == '*' || c == '/') {
        return true;
    }
    return false;
}

std::string infx2pstfx(const std::string& inf) {
    TStack<char, 100> st;
    std::string result = "";
    
    for (int i = 0; i < inf.length(); i++) {
        char sym = inf[i];
        
        if (sym == ' ') {
            continue;
        }
        
        if (sym >= '0' && sym <= '9') {
            while (i < inf.length() && inf[i] >= '0' && inf[i] <= '9') {
                result = result + inf[i];
                i++;
            }
            result = result + ' ';
            i--;
        }
        else if (sym == '(') {
            st.push(sym);
        }
        else if (sym == ')') {
            while (!st.empty() && st.get() != '(') {
                result = result + st.get();
                result = result + ' ';
                st.pop();
            }
            if (!st.empty() && st.get() == '(') {
                st.pop();
            }
        }
        else if (checkIsOperator(sym)) {
            while (!st.empty() && st.get() != '(' && 
                   getOpPriority(st.get()) >= getOpPriority(sym)) {
                result = result + st.get();
                result = result + ' ';
                st.pop();
            }
            st.push(sym);
        }
    }
    
    while (!st.empty()) {
        result = result + st.get();
        result = result + ' ';
        st.pop();
    }
    
    if (result.length() > 0 && result[result.length() - 1] == ' ') {
        result = result.substr(0, result.length() - 1);
    }
    
    return result;
}

int eval(const std::string& post) {
    TStack<int, 100> st;
    
    for (int i = 0; i < post.length(); i++) {
        char ch = post[i];
        
        if (ch == ' ') {
            continue;
        }
        
        if (ch >= '0' && ch <= '9') {
            std::string num = "";
            while (i < post.length() && post[i] >= '0' && post[i] <= '9') {
                num = num + post[i];
                i++;
            }
            
            int number = 0;
            for (int j = 0; j < num.length(); j++) {
                number = number * 10 + (num[j] - '0');
            }
            st.push(number);
            i--;
        }
        else if (checkIsOperator(ch)) {
            int b = st.get();
            st.pop();
            int a = st.get();
            st.pop();
            
            int res = 0;
            if (ch == '+') {
                res = a + b;
            } else if (ch == '-') {
                res = a - b;
            } else if (ch == '*') {
                res = a * b;
            } else if (ch == '/') {
                res = a / b;
            }
            
            st.push(res);
        }
    }
    
    return st.get();
}
