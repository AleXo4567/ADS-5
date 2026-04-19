// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

std::string infx2pstfx(const std::string& inf) {
  TStack<char, 100> opStack;
  std::string postfix;

  std::map<char, int> prec = {
    {'+', 1},
    {'-', 1},
    {'*', 2},
    {'/', 2}
  };

  for (size_t j = 0; j < inf.size(); ++j) {
    char ch = inf[j];

    if (ch >= '0' && ch <= '9') {
      postfix += ch;
      while (j + 1 < inf.size() && inf[j + 1] >= '0' && inf[j + 1] <= '9') {
        ++j;
        postfix += inf[j];
      }
      postfix += ' ';
    } 
    else if (ch == '(') {
      opStack.push(ch);
    } 
    else if (ch == ')') {
      while (!opStack.isempty() && opStack.get() != '(') {
        postfix += opStack.get();
        postfix += ' ';
        opStack.pop();
      }
      if (!opStack.isempty()) {
        opStack.pop();
      }
    } 
    else if (prec.find(ch) != prec.end()) {
      while (!opStack.isempty() && opStack.get() != '(' && prec[opStack.get()] >= prec[ch]) {
        postfix += opStack.get();
        postfix += ' ';
        opStack.pop();
      }
      opStack.push(ch);
    }
  }

  while (!opStack.isempty()) {
    if (opStack.get() != '(') {
      postfix += opStack.get();
      postfix += ' ';
    }
    opStack.pop();
  }

  if (!postfix.empty()) {
    postfix.pop_back();
  }

  return postfix;
}

int eval(const std::string& prefix) {
  TStack<int, 100> st;

  for (size_t pos = 0; pos < prefix.size(); ++pos) {
    char cur = prefix[pos];

    if (cur == ' ') {
      continue;
    }

    if (cur >= '0' && cur <= '9') {
      int val = cur - '0';
      while (pos + 1 < prefix.size() && prefix[pos + 1] >= '0' && prefix[pos + 1] <= '9') {
        ++pos;
        val = val * 10 + (prefix[pos] - '0');
      }
      st.push(val);
    } 
    else {
      int right = st.get();
      st.pop();
      int left = st.get();
      st.pop();

      int result;
      if (cur == '+') {
        result = left + right;
      } else if (cur == '-') {
        result = left - right;
      } else if (cur == '*') {
        result = left * right;
      } else {
        result = left / right;
      }

      st.push(result);
    }
  }

  return st.get();
}
