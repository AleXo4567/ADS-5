// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include <cctype>
#include "tstack.h"

int priority(char op) {
    if (op == '(') return 0;
    if (op == ')') return 1;
    if (op == '+' || op == '-') return 2;
    if (op == '*' || op == '/') return 3;
    return -1;
}

bool check_op(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

std::string infx2pstfx(const std::string& inf) {
    TStack<char, 100> st;
    std::string res;
    int len = inf.size();
    
    for (int i = 0; i < len; i++) {
        char sym = inf[i];
        
        if (sym == ' ') continue;
        
        if (sym >= '0' && sym <= '9') {
            while (i < len && inf[i] >= '0' && inf[i] <= '9') {
                res += inf[i];
                i++;
            }
            res += ' ';
            i--;
        }
        else if (sym == '(') {
            st.push(sym);
        }
        else if (sym == ')') {
            while (!st.empty() && st.get() != '(') {
                res += st.get();
                res += ' ';
                st.pop();
            }
            if (!st.empty() && st.get() == '(') {
                st.pop();
            }
        }
        else if (check_op(sym)) {
            while (!st.empty() && st.get() != '(' && 
                   priority(st.get()) >= priority(sym)) {
                res += st.get();
                res += ' ';
                st.pop();
            }
            st.push(sym);
        }
    }
    
    while (!st.empty()) {
        res += st.get();
        res += ' ';
        st.pop();
    }
    
    if (res.size() > 0 && res[res.size() - 1] == ' ') {
        res.erase(res.size() - 1);
    }
    
    return res;
}

int eval(const std::string& post) {
    TStack<int, 100> st;
    int len = post.size();
    
    for (int i = 0; i < len; i++) {
        char c = post[i];
        
        if (c == ' ') continue;
        
        if (c >= '0' && c <= '9') {
            int num = 0;
            while (i < len && post[i] >= '0' && post[i] <= '9') {
                num = num * 10 + (post[i] - '0');
                i++;
            }
            st.push(num);
            i--;
        }
        else if (check_op(c)) {
            int b = st.get();
            st.pop();
            int a = st.get();
            st.pop();
            int ans = 0;
            
            if (c == '+') ans = a + b;
            else if (c == '-') ans = a - b;
            else if (c == '*') ans = a * b;
            else if (c == '/') ans = a / b;
            
            st.push(ans);
        }
    }
    
    return st.get();
}
