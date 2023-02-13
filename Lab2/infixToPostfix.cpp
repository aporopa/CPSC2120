/*
 * Name: Abigail Poropatich
 * Date Submitted: 6 February 2023
 * Lab Section: 003
 * Assignment Name: Infix to Postfix Conversion
 */

#include <string>
#include <iostream>
#include <stack>

using namespace std;

int infixToPostfix(string infix[], int length, string postfix[]){
    stack<string> stackString;
    int j = 0;

    for(int i = 0; i < length; i++){

        //if the character that is being passed through is not a symbol
        //then add it to the postfix array
        if(infix[i] != "+" && infix[i] != "-" && infix[i] != "*" && infix[i] != "/" && infix[i] != "%" && infix[i] != "(" && infix[i] != ")"){
            postfix[j] = infix[i];
            j++;
        }

        //pushing the open parenthesis to the stack
        else if(infix[i] == "("){
            stackString.push(infix[i]);
        }

        //pop to postfix until you reach the left parand
        else if(infix[i] == ")"){
            //pop all operators from the stack with higher or equal precedence
            while(!stackString.empty() && stackString.top() != "("){
                if(stackString.top() == "(" || stackString.empty()){
                    return 0;
                }
                postfix[j] = stackString.top();
                stackString.pop();
                j++;
            }
            //pop the left parand from the stack
            stackString.pop();
        }

        //if the character is "+" or "-"
        else if(infix[i] == "+" || infix[i] == "-"){
            //if the top element is an open parenthesis or the stack is empty
            while(!stackString.empty() && stackString.top() != "("){
                if(stackString.top() == "(" || stackString.empty()){
                        return 0;
                    }
                postfix[j] = stackString.top();
                stackString.pop();
                j++;
            }
            if(stackString.empty()){
                return 0;
            }

            stackString.push(infix[i]);
        }

        //if the character is "*" or "%" or "/"
        else if(infix[i] == "*" || infix[i] == "%" || infix[i] == "/"){
            //check stack status or operator precedence
            while(!stackString.empty() && (stackString.top() == "*" || stackString.top() == "%" || stackString.top() == "/")){
                postfix[j] = stackString.top();
                stackString.pop();
                j++;
            }
            
            stackString.push(infix[i]);
        }
    }
    
    //pop everything else to the postfix stack
    while(!stackString.empty()){
        if(stackString.top() == "("){
            return 0;
        }
        postfix[j] = stackString.top();
        stackString.pop();
        j++;
    }
    return j;
}