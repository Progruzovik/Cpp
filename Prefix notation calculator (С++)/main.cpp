#include <iostream>
#include <cstring>
#include <stack>

using namespace std;

bool isCorrect(const string &e);

stack<char> infToPref(const string &e);
char strToOperator(const string &e, int n);
int hierarchy(char c);
void newOperand(stack<char> &s1, stack<char> &s2);
void saveOperand(stack<char> &s1, stack<char> &s2);
void loadOperand(stack<char> &s1, stack<char> &s2);
stack<char> reverse(stack<char> &s);

int count(stack<char> &s);
char calculate(char a, char op, char b);

int main()
{
    cout << "Enter the expression:" << endl;
    string e;
    getline(cin, e);
    if (isCorrect(e)) {
        stack<char> s = infToPref(e);
        cout << endl << "The expression in prefix notation:" << endl;
        stack<char> l = s;
        l = reverse(l);
        while (!s.empty()) {
            if (s.top() > ')') {
                if (s.top() < '0') {
                    cout << s.top();
                    s.pop();
                } else {
                    cout << int(s.top() - '0');
                    s.pop();
                }
                cout << ' ';
            } else {
                s.pop();
            }
        }
        cout << endl << endl << "Your result: " << count(l) << endl;
    } else {
        cout << endl << "Invalid expression!" << endl;
    }
    return 0;
}

bool isCorrect(const string &e)
{
    if ((e[0] != '(' && (e[0] < '0' || e[0] > '9')) || (e[e.size() - 1] != ')' && (e[e.size() - 1] < '0' || e[e.size() - 1] > '9'))) {
        return false;
    }
    for (unsigned int i = 1; i < e.size(); i++) {
        if (e[i] < '(' || e[i] > '9' || (e[i - 1] >= '*' && e[i - 1] <= '/' && e[i] >= '*' && e[i] <= '/')) {
            return false;
        }
    }
    return true;
}

stack<char> infToPref(const string &e)
{
    stack<char> s1, s2;
    for (unsigned int i = 0; i < e.size(); i++) {
        if (e[i] >= '0' && e[i] <= '9') {
            if (i == e.size() - 1 || e[i + 1] < '0' || e[i + 1] > '9') {
                if (i > 0 && e[i - 1] >= '0' && e[i - 1] <= '9') {
                    s1.push(strToOperator(e, i));
                } else {
                    s1.push(e[i]);
                }
            }
        } else if (e[i] == '(' || s2.empty() || hierarchy(e[i]) > hierarchy(s2.top())) {
            s2.push(e[i]);
        } else if (e[i] == ')') {
            while (s2.top() != '(') {
                newOperand(s1, s2);
            }
            s2.pop();
        } else if (hierarchy(e[i]) <= hierarchy(s2.top())) {
            while (!s2.empty() && hierarchy(e[i]) <= hierarchy(s2.top())) {
                newOperand(s1, s2);
            }
            s2.push(e[i]);
        }
    }
    while (!s2.empty()) {
        newOperand(s1, s2);
    }
    return reverse(s1);
}

char strToOperator(const string &e, int n)
{
    char c = '0';
    int i = 1;
    while (n > -1 && e[n] >= '0' && e[n] <= '9') {
        c += (e[n] - '0') * i;
        i *= 10;
        n--;
    }
    return c;
}

int hierarchy(char c)
{
    if (c == '*' || c == '/') {
        return 2;
    } else if (c == '+' || c == '-') {
        return 1;
    } else {
        return 0;
    }
}

void newOperand(stack<char> &s1, stack<char> &s2)
{
    stack<char> sL, sR;
    saveOperand(s1, sR);
    saveOperand(s1, sL);
    s1.push('(');
    s1.push(s2.top());
    s2.pop();
    loadOperand(sL, s1);
    loadOperand(sR, s1);
    s1.push(')');
}

void saveOperand(stack<char> &s1, stack<char> &s2)
{
    if (s1.top() == ')') {
        int n = -1;
        while (!(s1.top() == '(' && n == 0)) {
            if (s1.top() == ')') {
                n++;
            } else if (s1.top() == '(') {
                n--;
            }
            s2.push(s1.top());
            s1.pop();
        }
    }
    s2.push(s1.top());
    s1.pop();
}

void loadOperand(stack<char> &s1, stack<char> &s2)
{
    while (!s1.empty()) {
        s2.push(s1.top());
        s1.pop();
    }
}

stack<char> reverse(stack<char> &s)
{
    stack<char> r;
    while (!s.empty()) {
        r.push(s.top());
        s.pop();
    }
    return r;
}

int count(stack<char> &s)
{
    stack<char> ops;
    while (!s.empty()) {
        if (s.top() < '*') {
            s.pop();
        } else if (s.top() < '0') {
            char a = ops.top(), op = s.top();
            ops.pop();
            s.pop();
            s.push(calculate(a, op, ops.top()));
            ops.pop();
        } else {
            ops.push(s.top());
            s.pop();
        }
    }
    return ops.top() - '0';
}

char calculate(char a, char op, char b)
{
    a -= '0';
    b -= '0';
    switch (op) {
    case '*':
        return a * b + '0';
    case '/':
        return a / b + '0';
    case '+':
        return a + b + '0';
    default:
        return a - b + '0';
    }
}
