// program to convert a valid infix expression to postfix
/*ALGORITHM FOR INFIX to POSTFIX:

Input is the token of the infix expression - char array

1. Create an empty stack called opstack for keeping operators.
2. Create an empty array for the output.
3. Scan the input array from L-R
        1. If the token is an operand, add it to the output array.
        2. If the token is a left paranthesis (, push it on to the stack.
        3. IF the token is a right paranthesis ) , pop the stack until the
        corresponding left paranthesis is found. Add all the operators to the
        end of the output array.
        4. If the token is an operator, *,/,+,(,-, push it on to stack.
        However, first remove any operator already on the stack that has higher
        or equal precedence and add them to the output array.
4. When the input is completely processed, check the stack for any leftover
    operators. Pop them to the end of the output array.
*/
#include <stdio.h>

int input_prec(char);
int stack_prec(char);
void convert_postfix(char *, char *);
void push(char *, int *, char);
char pop(char *, int *);

int main()
{
	char infix[10], postfix[10];
	printf("\nEnter valid Infix Expression\n");
	scanf("%s", infix);
	convert_postfix(infix, postfix);
	printf("\nThe postfix equivalent=%s\n", postfix);
}

void convert_postfix(char *infix, char *postfix)
{
	int i, j;
	char ch;
	char s[10]; // stack
	int top = -1;
	i = 0;
	j = 0;
	push(s, &top, '#'); // push # to stack
	while (infix[i] != '\0')
	{
		ch = infix[i];

		// Directly access the top element of the stack
		while (stack_prec(s[top]) > input_prec(ch))
			postfix[j++] = pop(s, &top);

		if (input_prec(ch) > stack_prec(s[top]))
			push(s, &top, ch);
		else
			pop(s, &top); // for parenthesis

		i++;
	}

	// Directly access the top element of the stack
	while (s[top] != '#')
		postfix[j++] = pop(s, &top);

	postfix[j] = '\0';
}

int input_prec(char ch)
{
	switch (ch)
	{
	case '+':
	case '-':
		return 2; // Precedence for addition and subtraction when in the stack
	case '*':
	case '/':
		return 4; // Precedence for multiplication and division when in the stack
	case '(':
		return 0; // Precedence for opening parenthesis; it should not affect other operators
	case '#':
		return -1; // Lowest precedence for the initial stack marker
	default:
		return 6; // Default precedence for operands or any unrecognized characters
	}
}

int stack_prec(char ch)
{
	switch (ch)
	{
	case '+':
	case '-':
		return 1; // Precedence for addition and subtraction - low precedence
	case '*':
	case '/':
		return 3; // Precedence for multiplication and division
	case '(':
		return 7; // High precedence for opening parenthesis to ensure it is pushed onto the stack
	case ')':
		return 0; // Low precedence for closing parenthesis to ensure operators are popped until '(' is found
	default:
		return 5; // Default precedence for operands (e.g., variables, numbers)
	}
}

void push(char *s, int *top, char ch)
{
	(*top)++; // or ++*top
	s[*top] = ch;
}

char pop(char *s, int *top)
{
	char x;
	x = s[*top];
	--*top; // or (*top)--;
	return x;
}
/*
How These Functions Work Together:
Comparison During Conversion:

When an operator from the infix expression is read, its precedence is determined using input_prec.

The top operator of the stack is compared using stack_prec.

If the precedence of the operator at the top of the stack (stack_prec)
is greater than the incoming operator's precedence (input_prec), 
the stack operator is popped and added to the postfix expression.

If the precedence of the incoming operator is higher or equal (input_prec > stack_prec),
 the incoming operator is pushed onto the stack.*/