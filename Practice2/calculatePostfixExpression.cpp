#include <string>
#include <stack>
#include <iostream>
#include <algorithm>

using namespace std;

int calculatePostfixExpression(string expression[], int length){
    stack<int> stack;
    int result = 0;

    //looping through the postfix string
    for(int i = 0; i < length; i++){
        //if all of the expressions are numbers
        //push them to the stack
        if(all_of(expression[i].begin(), expression[i].end(), ::isdigit)){
            int operand = stoi(expression[i]);
            stack.push(operand);
        }
        
        //if expression is found to be an operator
        else{
            //if there are not enough digits to operate on
            //then terminate the program
            if(stack.size() < 2)
                return 0;

            //if there is enough to operate on
            else if(stack.size() >= 2){
                //pop two integers and proceed with
                //the proper arithmetic 
                int x = stack.top();
                stack.pop();

                int y = stack.top();
                stack.pop();

                if(expression[i] == "+")
                    stack.push(y + x);

                else if(expression[i] == "-")
                    stack.push(y - x);
                
                else if(expression[i] == "*")
                    stack.push(y * x);

                else if(expression[i] == "/")
                    stack.push(y / x);

                else if(expression[i] == "%")
                    stack.push(y % x);
            }
        }

    }
    //return if expression is zero-length 
    //or if there are insufficient operands
    if(stack.empty())
        return 0;

    //the result is the leftover number
    //at the top of the stack
    result = stack.top();
    stack.pop();

    //return zero if the stack is not empty
    //after popping the top
    if(!stack.empty())
        return 0;
        
    return result;
}