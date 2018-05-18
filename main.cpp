#include <bits/stdc++.h>

using namespace std;

struct Token
{
	char type;
	string value;

	Token (char t)
	{
		type = t;
	}
		

	Token(char t, string v)
	{
		type = t;
		value = v;
	}
};

// Check if enterred character is an operator.
bool is_operand(char x)
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
			return false;
		default:
			return true;
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
	const char OPERAND = 'N';
	const char OPERATOR = 'R';

	string infix_expression;
	cin>>infix_expression;

	stack <char> operators;

	vector <Token> postfix_expression;
	int current_operand_place = 0;

	bool after_operator = true;

	for(char x : infix_expression)
	{	
		// check if x is a number if yes conactenate it to the current operand token
		if(is_operand(x))
		{	
			string current_operand;
			current_operand += x;

			if(after_operator)
			{
				postfix_expression.push_back(* new Token(OPERAND, current_operand));
				after_operator = false;
			}
			else
				postfix_expression[current_operand_place].value += current_operand;
		}
		else
		{	
			after_operator = true;

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

						string current_operator;
						current_operator.push_back(operators.top());	

						postfix_expression.push_back( * new Token(OPERATOR,current_operator));
					
						current_operand_place++;

						operators.pop();
					}

					operators.pop();
				break;

				default:
					if(operators.empty() || operators.top() == '(' || get_precedence(operators.top()) < get_precedence(x))
					{
						operators.push(x);
					}	
					else
					{	
						
						while(get_precedence(operators.top()) >= get_precedence(x))
						{	
							/*
						 	add the top element in the operators stack to the token value 
						 	and push it in the postfix expression
							then clear the token value to be able to use it later
							and add one to the operand place t
							*/

							string current_operator;
							current_operator.push_back(operators.top());	

							postfix_expression.push_back( * new Token(OPERATOR,current_operator));
					
							current_operand_place++;

							operators.pop();
						}
						operators.push(x);	
					}
			}	
			
		}
		

	}

	//While operators stack still has elements in it pop and push in the postfix expression
	
		
	while(!operators.empty())
	{	
			string current_operator;
			current_operator += operators.top();
			postfix_expression.push_back(* new Token(OPERATOR, current_operator));
			operators.pop();
	}
	

	for(Token temp : postfix_expression)
		cout<<temp.value<<" ";
	
	cout<<endl;
	return 0;
	
}