// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

int prior(char op) {
    if (op == '(') {
        return 0;
    }
    if (op == ')') {
        return 1;
    }
    if (op == '+' || op == '-') {
        return 2;
    }
    if (op == '*' || op == '/') {
        return 3;
    }
    return -1;
}

bool is_oper(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

std::string infx2pstfx(const std::string& inf) {
    TStack<char, 100> st;
    std::string out;
    int n = static_cast<int>(inf.length());

    for (int i = 0; i < n; ++i) {
        char ch = inf[i];

        if (ch == ' ') {
            continue;
        }

        if (ch >= '0' && ch <= '9') {
            std::string num;
            while (i < n && inf[i] >= '0' && inf[i] <= '9') {
                num += inf[i];
                ++i;
            }
            out += num;
            out += ' ';
            --i;
        } else if (ch == '(') {
            st.push(ch);
        } else if (ch == ')') {
            while (!st.isEmpty() && st.top() != '(') {
                out += st.top();
                out += ' ';
                st.pop();
            }
            if (!st.isEmpty() && st.top() == '(') {
                st.pop();
            }
        } else if (is_oper(ch)) {
            while (!st.isEmpty() && st.top() != '(' &&
                   prior(st.top()) >= prior(ch)) {
                out += st.top();
                out += ' ';
                st.pop();
            }
            st.push(ch);
        }
    }

    while (!st.isEmpty()) {
        out += st.top();
        out += ' ';
        st.pop();
    }

    if (!out.empty() && out.back() == ' ') {
        out.pop_back();
    }

    return out;
}

int eval(const std::string& post) {
    TStack<int, 100> st;
    int n = static_cast<int>(post.length());

    for (int i = 0; i < n; ++i) {
        char c = post[i];

        if (c == ' ') {
            continue;
        }

        if (c >= '0' && c <= '9') {
            int num = 0;
            while (i < n && post[i] >= '0' && post[i] <= '9') {
                num = num * 10 + (post[i] - '0');
                ++i;
            }
            st.push(num);
            --i;
        } else if (is_oper(c)) {
            int b = st.top();
            st.pop();
            int a = st.top();
            st.pop();
            int res = 0;

            if (c == '+') {
                res = a + b;
            } else if (c == '-') {
                res = a - b;
            } else if (c == '*') {
                res = a * b;
            } else if (c == '/') {
                res = a / b;
            }

            st.push(res);
        }
    }

    return st.top();
}
    return st.get();
}
