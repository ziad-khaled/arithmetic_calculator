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
	switch(x)
	{
		case '(':
		case ')':
			return 4;
		
		case '^':
			return 3;
		
		case '*':
		case '/':
			return 2;cout<<endl;
		
		case '+':
		case '-':
			return 1;		
	}
}

vector<Token> to_postfix(vector<Token> infix_tokens)
{

	stack <Token> operators;

	vector <Token> postfix_tokens;

	for(Token t : infix_tokens )
	{	
        cout<<t.value<<" in the loop\n";
		// check if the current token is a number if yes added it to the postfix tokens
		if(t.type==OPERAND)
            postfix_tokens.push_back(t);
		else
		{	
            char current_operator = t.value[0];

			switch(current_operator)
			{
				case '(':
					operators.push(t);
				break;

				case ')':

					while(operators.top().value[0] != '(')
					{		
                        postfix_tokens.push_back(operators.top());		
						operators.pop();
					}
					operators.pop();
				break;

				default:
                    
					if(operators.empty() || operators.top().value[0] == '(' || get_precedence(operators.top().value[0]) < get_precedence(current_operator))
						operators.push(t);
			
					else
					{	
						
						while(!operators.empty() && get_precedence(operators.top().value[0]) >= get_precedence(current_operator))
						{				
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
	
    return postfix_tokens;
}

int main()
{
    string expression;
    cin>>expression;
    cout<<"read\n";
    vector <Token> infix_tokens = tokenize(expression);
    cout<<"tokenized\n";
    vector <Token> postfix_tokens = to_postfix(infix_tokens);
    cout<<"to postfix\n";
    for(Token t : postfix_tokens)
        cout<<t.value<<" ";

    cout<<endl;

    return 0;
}