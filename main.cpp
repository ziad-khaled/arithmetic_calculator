#include <bits/stdc++.h>

#define OPERAND 'N'
#define OPERATOR 'R'

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
bool is_operator(char x)
{   
    bool is_operator;
	switch(x)
	{
		case '(':
		case ')':
		case '^':
		case '*':
		case '/':
		case '+':
		case '-':
			is_operator = true;
        break;
		default:
			is_operator = false;
	}
	
	return is_operator;
}

// Get tokens from the expression to be able to deal later with each token individually
vector<Token> tokenize(string expression)
{   
    vector<Token> tokens;
    bool after_operator = true;

    for(char x : expression)
    {
        if(is_operator(x))
        {   
            string current_operator;
            current_operator += x;
            tokens.push_back( *new Token(OPERATOR,current_operator));
            after_operator = true;
        }
        else
        {
            if(after_operator)
            {
                string current_operand;
                current_operand += x;
                tokens.push_back( *new Token(OPERAND, current_operand));
                after_operator = false;
            }
            else
                tokens.back().value += x;
        }  
    }

    return tokens;
}

/*
	Return opertar precedence to know operator order of operationand as we know from maths classes 
    () come first then ^ then /* then +- 
*/

int get_precedence(char x)
{   
    int precedence;
	switch(x)
	{
		case '(':
		case ')':
			precedence = 4;
		break;
        
		case '^':
			precedence = 3;
        break;
        
		case '*':
		case '/':
			precedence = 2;
        break;
        
		case '+':
		case '-':
			precedence = 1;		
	}
	
	return precedence;
}

vector<Token> to_postfix(vector<Token> infix_tokens)
{

	stack <Token> operators;

	vector <Token> postfix_tokens;
	int power_num = 0;
	for(int i =0, l = infix_tokens.size(); i < l; i++)
	{	
		Token t = infix_tokens[i];
		if(i<l-1 && infix_tokens[i+1].value=="^")
			power_num++;
		// check if the current token is a number if yes added it to the postfix tokens
		if(t.type==OPERAND)
            postfix_tokens.push_back(t);
		else if(t.value != "^")
		{	
			while(power_num>0)
			{	
				string temp;
				temp += "^";
				postfix_tokens.push_back(*new Token(OPERATOR, temp));
                power_num--;
			}
			
            char current_operator = t.value[0];
			
			switch(current_operator)
			{
				case '(':
					operators.push(t);
				break;

				case ')':
					while(!operators.empty() && operators.top().value[0] != '(')
					{		
                        postfix_tokens.push_back(operators.top());		
						operators.pop();
					}
					if(!operators.empty())
                        operators.pop();
				break;

				default:
					if(operators.empty() || operators.top().value[0] == '(' || get_precedence(operators.top().value[0]) < get_precedence(current_operator))
						operators.push(t);
			
					else
					{	
						while(!operators.empty() && get_precedence(operators.top().value[0]) >= get_precedence(current_operator))
						{				
							if(operators.top().value[0] != '(')
                                postfix_tokens.push_back(operators.top());				
							operators.pop();
						}
						operators.push(t);	
					}
			}	
			
		}
		
	}

	//While operators stack still has elements in it pop and push in the postfix expression	
	while(!operators.empty())
	{	 
		postfix_tokens.push_back(operators.top());
		operators.pop();
	}

	while(power_num>0)
	{	
		string temp;
		temp += "^";
		postfix_tokens.push_back(*new Token(OPERATOR, temp));
        power_num--;
	}
	
    return postfix_tokens;
}
double get_value(double val1, double val2, char current_operator)
{   
    double value;
	switch(current_operator)
	{
		case '+':
			value = val2 + val1;
        break;
        
		case '-':
            value = val2 - val1;
        break;
        
		case '*':
			value = val2 * val1;
        break;
        
        case '/':
			value = val2 / val1;
        break;
        
		case '^':
			value = pow(val2, val1);
	}
	
	return value;
}
double evaluate(vector<Token> postfix_tokens)
{
	double result = 0;
	stack<Token> evaluation_stack;

	for(Token t : postfix_tokens)
	{
		if(t.type == OPERAND)
			evaluation_stack.push(t);
		else
		{
			double val1 = stod(evaluation_stack.top().value);
			evaluation_stack.pop();

			double val2 = stod(evaluation_stack.top().value);
			evaluation_stack.pop();

			result = get_value(val1, val2, t.value[0]);

			evaluation_stack.push(*new Token(OPERAND, to_string(result)));
		}
	}

	result = stod(evaluation_stack.top().value);

	return result;
}


int main()
{	
	char continue_program;
	
    do
	{
		string expression;
		cout<<">> ";
		cin>>expression;

		vector <Token> infix_tokens = tokenize(expression);
		
		vector <Token> postfix_tokens = to_postfix(infix_tokens);
		cout<<"postfix: ";
		for(Token t : postfix_tokens)
			cout<<t.value<<" ";

		cout<<endl;
		cout<<"= "<<evaluate(postfix_tokens)<<"\n";

		cout<<"\nDo you want to continue?y/n ";
		cin>>continue_program;
		cout<<endl;
	}while(continue_program == 'y');

	cout<<"Goodbye!\n";

    return 0;
}
