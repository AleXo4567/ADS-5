// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

std::string infx2pstfx(const std::string& inf) {
  TStack<char, 100> stackOp;
  std::string result;

  std::map<char, int> priority = {
    {'+', 1},
    {'-', 1},
    {'*', 2},
    {'/', 2}
  };

  for (size_t idx = 0; idx < inf.size(); ++idx) {
    char symbol = inf[idx];

    if (symbol >= '0' && symbol <= '9') {
      result += symbol;
      while (idx + 1 < inf.size() && inf[idx + 1] >= '0' && inf[idx + 1] <= '9') {
        ++idx;
        result += inf[idx];
      }
      result += ' ';
    } else if (symbol == '(') {
      stackOp.push(symbol);
    } else if (symbol == ')') {
      while (!stackOp.isempty() && stackOp.get() != '(') {
        result += stackOp.get();
        result += ' ';
        stackOp.pop();
      }
      if (!stackOp.isempty()) {
        stackOp.pop();
      }
    } else if (priority.find(symbol) != priority.end()) {
      while (!stackOp.isempty() && stackOp.get() != '(' && priority[stackOp.get()] >= priority[symbol]) {
        result += stackOp.get();
        result += ' ';
        stackOp.pop();
      }
      stackOp.push(symbol);
    }
  }

  while (!stackOp.isempty()) {
    if (stackOp.get() != '(') {
      result += stackOp.get();
      result += ' ';
    }
    stackOp.pop();
  }

  if (!result.empty()) {
    result.pop_back();
  }

  return result;
}

int eval(const std::string& pref) {
  TStack<int, 100> calcStack;

  for (size_t pos = 0; pos < pref.size(); ++pos) {
    char cur = pref[pos];

    if (cur == ' ') {
      continue;
    }

    if (cur >= '0' && cur <= '9') {
      int value = cur - '0';
      while (pos + 1 < pref.size() && pref[pos + 1] >= '0' && pref[pos + 1] <= '9') {
        ++pos;
        value = value * 10 + (pref[pos] - '0');
      }
      calcStack.push(value);
    } else {
      int rightOp = calcStack.get();
      calcStack.pop();
      int leftOp = calcStack.get();
      calcStack.pop();

      int answer = 0;
      switch (cur) {
        case '+': answer = leftOp + rightOp; break;
        case '-': answer = leftOp - rightOp; break;
        case '*': answer = leftOp * rightOp; break;
        case '/': answer = leftOp / rightOp; break;
      }

      calcStack.push(answer);
    }
  }

  return calcStack.get();
}
