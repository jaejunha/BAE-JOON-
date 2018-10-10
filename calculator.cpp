#include <iostream>
#include <cstring>
#include <string>
#include <stack>
#include <vector>
using namespace std;

int t;

/* �Է� �޴� ����		*
*----------------------*
* input: ����			*
* length: ������ ����	*
*----------------------*/
char input[100];
int length;

/* ���� ǥ���            	*
*--------------------------*
* postfix: ����ǥ��� ���� *
*--------------------------*/
vector<string> postfix;

/* ����            									*
*--------------------------------------------------*
* stack_operator: ���� -> ������ ������ �� ���	*
* stack_calculator: ����ǥ��� �� ���� ����� ���	*
*--------------------------------------------------*/
stack<char> stack_operator;
stack<int> stack_calculator;

/* �켱���� ����ϴ� �Լ�	*
*---------------------------*
* ������(c)�� �Է¹޾�		*
* �켱���� ����				*
* ����, ������: 1			*
* ����, ����: 0				*
* ��ȣ: -1					*
*---------------------------*/
int priority(char c) {
	switch (c) {
	case '*':
	case '/':
		return 1;
	case '+':
	case '-':
		return 0;
	case '(':
	case ')':
		return -1;
	}
}

/* ���� ǥ����� ���� ǥ������� �ٲٴ� �Լ�																						*
* ��� ����: stack_operator																										*
*----------------------------------------------------------------------------------------------------------------------------------*
* �Է� ���� �������� ���� ���� �ϳ��� ����																							*
* ���� ���ڰ� ������ ���: postfix�� ����																							*
* ���� ���ڰ� ���� ��ȣ�� ���: ���ÿ� ����																						*
* ���� ���ڰ� �ݴ� ��ȣ�� ���: ���� ��ȣ�� ���� ������ ���ÿ� �ִ°͵��� postfix�� ����											*
* �������� ���: �Ʒ��� ���� �� ������ ������																						*
*					1. ������ �� ���:			���� �����ڸ� ���ÿ� ����															*
*					2. ������ ���� ���� ���:	���ÿ��� ���� ������ ���� �켱������ ���ų� ���� �����ڵ��� ����(postfix�� ����)	*
*												���� �����ڸ� ���ÿ� ����															*
* ������ �� �а� ���ÿ� �����ڰ� ���������� ������� postfix�� �����Ѵ�															*
*----------------------------------------------------------------------------------------------------------------------------------*/
void infixToPostfix();

/* ���� ǥ����� ����ϴ� �Լ�										*
* ��� ����: stack_calculator										*
*------------------------------------------------------------------*
* ���� ǥ��� �������� ���� �ϳ��� ����							*
* ������ ���: ���ÿ� ����											*
* �������� ���: ���� �ΰ��� ���� ������ ���� �ٽ� ���ÿ� �ִ´�	*
*------------------------------------------------------------------*/
void calculate();

int main() {
	/* �׽�Ʈ ���̽� ���� �Է� */
	cin >> t;

	/* �׽�Ʈ ���̽� ���� ��ŭ �ݺ� */
	for (int i = 1; i <= 4; i++) {

		/* ���� �Է� ����*/
		cin >> input;
		length = strlen(input);

		/* ���� ǥ��� -> ���� ǥ��� */
		infixToPostfix();

		/* ���� ��� */
		calculate();
	}

	return 0;
}

void infixToPostfix() {
	char c;
	string s;
	/* �Է� ���� ������ ���� */
	for (int i = 0; i < length; i++) {
		/* ���Ŀ��� �ϳ��� �о�� */
		c = input[i];
		/* ������ ��� */
		if (c >= '0' && c <= '9') {
			/* ���ڸ� postfix�� �ű� */
			postfix.push_back(to_string(atoi(input + i)));
			while (input[i] >= '0' && input[i] <= '9')
				i++;
			i--;
		}
		/* �������� ��� */
		else {
			/* ���� ��ȣ�� ��� */
			if (c == '(')
				stack_operator.push('(');
			/* �ݴ� ��ȣ�� ��� */
			else if (c == ')') {
				/* ���� ��ȣ�� ���� ������ */
				while (stack_operator.top() != '(') {

					/* ���� ��ܿ� �ִ� �͵��� postfix�� �ű� */
					string str(1, stack_operator.top());
					postfix.push_back(str);
					stack_operator.pop();
				}
				/* ���� ��ȣ�� ���ÿ��� ���� */
				stack_operator.pop();
			}
			/* ��Ģ ������ ��� */
			else {
				/* ���ÿ� �ƹ� �͵� ���� ��� �ܼ��� ���� */
				if (stack_operator.empty())
					stack_operator.push(c);

				/* ���ÿ� ���� �ִ� ��� */
				else {

					/* ���� top�� �ִ� �����ڰ� ������ ������ ���� �켱������ ũ�ų� ���� ��� */
					while (priority(stack_operator.top()) >= priority(c)) {

						/* ���� ��ܿ� �ִ� �͵��� postfix�� �ű� */
						string str(1, stack_operator.top());
						postfix.push_back(str);
						stack_operator.pop();

						/* ������ �� ��� �ݺ��� ��� */
						if (stack_operator.empty())
							break;
					}
					/* �켱���� ���� �͵� ���� ������ ���� �߰� �� �� ���ÿ� ���� */
					stack_operator.push(c);
				}
			}
		}
	}

	/* ���� �����ڵ��� postfix�� �ű�� ���� */
	while (!stack_operator.empty()) {
		/* ���� ��ܿ� �ִ� �͵��� postfix�� �ű� */
		string str(1, stack_operator.top());
		postfix.push_back(str);
		stack_operator.pop();
	}
}

void calculate() {
	for (string s : postfix) {
		/* postfix���� �ϳ��ϳ��� ���� */
		char c = s.at(0);
		/* ���� ���� �������� ��� */
		if (c == '+' || c == '-' || c == '*' || c == '/') {
			/* ���� �ΰ��� �������κ��� ���� ���� */
			int n1 = stack_calculator.top();
			stack_calculator.pop();
			int n2 = stack_calculator.top();
			stack_calculator.pop();

			switch (c) {
			case '+':
				stack_calculator.push(n2 + n1);
				break;
			case '-':
				stack_calculator.push(n2 - n1);
				break;
			case '*':
				stack_calculator.push(n2 * n1);
				break;
			case '/':
				stack_calculator.push(n2 / n1);
				break;
			}
		}

		/* ���� ���� ������ ��� */
		else
			stack_calculator.push(atoi(s.c_str()));
	}
	cout << stack_calculator.top() << endl;
}