#include<stdio.h>
#include<string.h>

// Function prototypes
int input_prec(char); // Determines the input precedence of operators
int stack_prec(char); // Determines the stack precedence of operators
char peep(char *,int); // Returns the top of the stack without popping
void convert_postfix(char*,char*); // Converts infix to postfix expression
void push(char *, int *, char); // Pushes an element onto the stack
char pop(char *, int *); // Pops an element from the stack
void reverse_string(char *, char *); // Reverses the string and changes parentheses

int main()
{
  char infix[100],prefix[100], reverse[100],postfix[100];
  
  // Get infix expression input from the user
  printf("\nEnter valid Infix Expression\n");
  scanf("%s",infix);
  
  // Reverse the infix expression and store it in the 'reverse' array
  reverse_string(infix, reverse);
  printf("Reversed = %s\n", reverse);
  
  // Convert the reversed infix expression to a postfix expression
  convert_postfix(reverse, postfix);
  printf("\npostfix equivalent = %s",postfix);
  
  // Reverse the postfix expression to get the prefix expression
  reverse_string(postfix, prefix);
  printf("\nThe prefix equivalent=%s\n",prefix);
}


/* Function to convert infix to postfix expression */
void convert_postfix(char *infix, char *postfix)
{
    char s[100]; // Stack to hold operators and parentheses
    int top = -1, i, j;
    i = 0;
    char ch;
    j = 0;

    // Push '#' onto the stack as a sentinel value
    push(s, &top, '#');
	
    // Loop through the infix expression from left to right
    while(infix[i] != '\0')
    {
        ch = infix[i];

        // Pop from the stack if input precedence is lower than stack precedence
        while(input_prec(ch) < stack_prec(peep(s, top)))
            postfix[j++] = pop(s, &top);
	
        // Push to the stack if input precedence is higher than stack precedence
        if(input_prec(ch) > stack_prec(peep(s, top)))
            push(s, &top, ch);
        else
            // If the precedence is equal, this happens when ')' matches '('
            pop(s, &top);
        i++;
    }
	
    // Pop remaining operators from the stack and store in postfix expression
    while(peep(s, top) != '#')
        postfix[j++] = pop(s, &top);
    
    // Null-terminate the postfix string
    postfix[j] = '\0';
}


/* Function to return the input precedence of the operator */
int input_prec(char ch)
{
    switch(ch)
    {
        case '+':
        case '-': return 2; // Lower precedence for '+' and '-' compared to postfix
        case '*':
        case '/': return 4; // Higher precedence for '*' and '/' compared to postfix
        case '(': return 7; // '(' has the highest precedence when it is the input
        case ')': return 0; // ')' has the lowest precedence when it is the input
        default: return 5;  // For operands (like variables), precedence is constant
    }
}

/* Function to return the stack precedence of the operator */
int stack_prec(char ch)
{
    switch(ch)
    {
        case '+':
        case '-': return 1; // Stack precedence is lower for '+' and '-'
        case '*':
        case '/': return 3; // Stack precedence is lower for '*' and '/'
        case '(': return 0; // '(' has the lowest precedence when it is on the stack
        case '#': return -1; // Sentinel value '#' has the lowest precedence
        default: return 6;  // For operands (like variables), precedence is constant
    }
}

/* Function to return the top element of the stack without popping */
char peep(char *s, int t)
{
    return s[t]; // Return the element at the top of the stack
}

/* Function to push an element onto the stack */
void push(char *s, int *t, char x)
{
    ++*t; // Increment the top index
    s[*t] = x; // Place the element at the new top position
}

/* Function to pop an element from the stack */
char pop(char *s, int *t)
{
    char x = s[*t]; // Store the top element
    --*t; // Decrement the top index
    return x; // Return the popped element
}

/* Function to reverse a string and handle the parentheses */
void reverse_string(char *a, char *b)
{
    int i, j;
	
    // Start from the last character of the input string
    i = strlen(a) - 1;
    j = 0;
	
    // Loop through the string backwards
    while(i >= 0)
    {
        // Swap '(' with ')' and vice versa
        if(a[i] == '(')
            b[j++] = ')';
        else if(a[i] == ')')
            b[j++] = '(';
        else
            b[j++] = a[i]; // Copy other characters as they are
        i--;
    }
    
    // Null-terminate the reversed string
    b[j] = '\0';
}
