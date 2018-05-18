#include <bits/stdc++.h>

using namespace std;

struct Token
{
	char type;
	string value;

	Token (char t)
		type = t;

	Token(char t, string v)
	{
		type = t;
		value = v;
	}
}

// Check if enterred character is an operator.
bool is_operator(char x)
{
	switch(x)
	{
		case '(':
		case ')':
		case '^':
		case '*':
		case '/':
		case '+':
		case '-':
			return true;
		default:
			return false;
	}
}

/*
	Return opertar precedence to know which one will be executed before the others
	and as we know () comdefault:
			return false;e first then /* then +- 
*/
int get_precedence(char x)
{
	switch(x)
	{
		case '(':
		case ')':
			return 4;
		break;

		case '^':
			return 3;
		break;

		case '*':
		case '/':
			return 2;
		break;

		case '+':
		case '-':
			return 1;		
	}
}

int main()
{	
	const char TOKEN_END = "_";
	const char NUMBER = 'n';
	const char OPERATOR = 'o';

	string infix_expression;
	cin>>infix_expression;

	stack <char> operators;

	vector <Token> postfix_expression;
	int operand_place = 0;
	for(char x : infix_expression)
	{	
		// check if x is a number if yes conactenate it to current operand
		if(!is_operator(x))
		{
			postfix_expression[operand_place].type = NUMBER;
			postfix_expression[operand_place].value += x;
		}
		else
		{	Token operator_token = new Token(OPERATOR);
			switch(x)
			{
				case '(':
					operators.push(x);
				break;

				case ')':
					
					
					while(operators.top() != '(')
					{	
						/*
						 	add the top element in the operators stack to the token value 
						 	and push it in the postfix expression
							then clear the token value to be able to use it later
							and add one to the operand place t
						*/

						operator_token.value += operators.top();
						postfix_expression.push_back(temp_token)
						operator_token.value.clear();

						operand_place++;

						operators.pop();
					}

					operators.pop();
				break;

				default:
					if(operators.empty() || operators.top() == '(' || get_precedence(operators.top()) < get_precedence(x))
						operators.push(x);
					else
					{	
						
						while(get_precedence(operators.top()) >= get_precedence(x)))
						{	
							/*
						 	add the top element in the operators stack to the token value 
						 	and push it in the postfix expression
							then clear the token value to be able to use it later
							and add one to the operand place t
							*/

							operator_token.value += operators.top();
							postfix_expression.push_back(temp_token)
							operator_token.value.clear();

							operand_place++;

							operators.pop();
								
						}
						operators.push(x);	
					}
			}	
			
		}
		

	}

	//While operators stack still has elements in it pop and push in the postfix expression
	{
		char current_operator;
		while(!operators.empty())
		{	
			current_operator = operators.top();
			postfix_expression.push_back(current_operator);
			operators.pop();
		}
	}

	

	return 0;
	
}