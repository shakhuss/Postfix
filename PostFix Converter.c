//Shakeb Hussain
//Project 2
//November 7, 2018


#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 


// This is a Structure to represent a stack with an array implementation
struct Stack 
{ 
    int top; 
    unsigned capacity; 
    int* array; 
}; 
  
// Function to create a stack with a capacity given when initialized
struct Stack* createStack( unsigned capacity ) 
{ 
    struct Stack* stack = (struct Stack*) malloc(sizeof(struct Stack)); 
  	stack->capacity = capacity; 
	stack->top = -1; 
  	stack->array = (int*) malloc(stack->capacity * sizeof(int)); 
  
    return stack; 
} 


// Checks if Stack is full when the top is equal to the last index
int isFull(struct Stack* stack)
{
	return stack->top == stack->capacity - 1;	
}


// The Stack is empty when the top is equal to -1
int isEmpty(struct Stack* stack) 
{ 
    return stack->top == -1 ; 
} 


// This function adds an item to the Stack
void push(struct Stack* stack, char item) 
{ 
	if(isFull(stack))
		return;
    stack->array[++stack->top] = item; 
    printf("%c pushed to stack \n", item);
} 
  

// This Function removes an item from the stack one by one
char pop(struct Stack* stack) 
{ 
    if (!isEmpty(stack))
    	return stack->array[stack->top--];  
} 


// This function checks element on the top of the Stack 
char peek(struct Stack* stack) 
{ 
	if(!isEmpty(stack))
    	return stack->array[stack->top]; 
} 


// This function takes the alphabet and numbers 0-9 as tokens and checks if the character
// is an operand
int Operand(char x)
{
    if(x >= '0' && x <= '9')
	    return x;
	else if(x >= 'a' && x <= 'z')
	    return x;
	else if(x >= 'A' && x <= 'Z')
	    return x;
	else
	    return 0;
}



// This function sets the priority of the operators of precedence
int Priority(char y)
{
	if (y == '+' || y == '-')
		return 1;
	else if (y == '*' || y == '/')
		return 2;
	else
		return -1;
}



// This function goes through the each character in the string to determine to place in the 
// append to the stack, array, and/or remove
int intoPost(char* equ)
{
	struct Stack* stack = createStack(strlen(equ)); // Creates a stack in regards to the length of the input string

	int i, j; // Initialize these values to traverse through the string equation

	for (i = 0, j = -1; equ[i]; ++i)	// Start the position of the array i at 0, and j at -1 so as i increases j 
	{									// is one step behind iterating. Increasing i by one until the length of equ
		if (Operand(equ[i]))			// is reached. 
			equ[++j] = equ[i];

		else if (equ[i] == '(')			// The if and else if statments first being by appending the operands to the array first.
			push(stack, equ[i]);		// Once an open parenthesis is found it will push it to the stack then later removed. 
			
		else if (equ[i] == ')')			// This will see if the current char is an ending parenthesis. It will not be added to the Stack 
		{								// 
			while (!isEmpty(stack) && peek(stack) != '(')	
				equ[++j] = pop(stack);						// This checks if it comes across an ending parenthesis. If it is found it will check the top of
			if (!isEmpty(stack) && peek(stack) == '(')		// the stack if the open parenthesis is present. It will pop the stack into the array then.	
				pop(stack);									// Then it will check if the stack is not empty and the top is the opening parenthesis it will pop it
			else
				printf("ERROR: Variable not declared or defined"); // This will show if there is an operator that was not defined or declared

		}

		else
		{
			while (!isEmpty(stack) && Priority(equ[i]) <= Priority(peek(stack)))	//This will check the precedence of the each of the operators going through the Stack
				equ[++j] = pop(stack);												// and determine whether to pop is or push it to the stack. Determines which operator
			push(stack, equ[i]);													// has a greater precedence. 
		}
	}

	while (!isEmpty(stack))				// This will pop the stack into the array one by one if the Stack is not empty
		equ[++j] = pop(stack);
		
	equ[++j] = '\0';					// Reached the end of the array and indicates the end of the string 
	printf( "%s\n",equ);				// Displays the PostFix of the equation

}


int main()
{
	char equate[20];													// The next few lines are used to get an input from the user of an InFix equation
	printf("---InFix to PostFix Conversion of an Equation---\n ");		// It allocates size of 20 to the character array of equate
	printf("Enter Equation to Convert:\n");
	scanf("%s",equate);
	//char equ[] = ("%s",equate);
	intoPost(equate);
	printf("TEST EQUATION:\n");											// This is a quick test equation to display the program
	char equ[] = "5+6-(3-2)+7";
	intoPost(equ);
	return 0;

}

