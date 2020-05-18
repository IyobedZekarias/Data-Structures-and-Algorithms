//Iyobed Zekarias
//Infix code
//Created the code myself but got the directions for infix to postfix from here https://www.includehelp.com/c/infix-to-postfix-conversion-using-stack-with-c-program.aspx
//Postfix evaluation directions from here https://www.includehelp.com/c/evaluation-of-postfix-expressions-using-stack-with-c-program.aspx

#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <cstring>
#include "Logger.hpp"
#include "LStack.hpp"

LStack<std::string> stack; 


std::string PrecedentCheck(std::string operation)
{
    //Precedent works the same way as PEMDAS from 5th grade 
    //Please Excuse My Dear Aunt Sally 
    std::string higherPrec  = "";
    std::size_t size = stack.Size();

    for(std::size_t i = 0; i < size; i++)
    {
        std::string top = stack.Top();
        if(operation.compare("+") == 0 || operation.compare("-") == 0)
        {
            if(top.compare("+") == 0 || top.compare("-") == 0 || top.compare("/") == 0 || top.compare("*") == 0 || top.compare("^") == 0)
            {
                higherPrec += stack.Pop();
            }
        }
        else if(operation.compare("/") == 0 || operation.compare("*") == 0)
        {
            if(top.compare("/") == 0 || top.compare("*") == 0 || top.compare("^") == 0)
            {
                higherPrec += stack.Pop();
            }
        }
        else if(operation.compare("^"))
        {
            if(top.compare("^") == 0)
            {
                higherPrec += stack.Pop();
            }
        }
    }
    stack.Push(operation);
    return higherPrec;
}

std::string RightPar()
{
    //Whenever a right parenthesis is hit return out everything up to the left parenthesis 
    std::string UpToPar = "";
    int size = stack.Size();

    for(int i = 0; i < size; i++)
    {
        std::string top = stack.Top();
        if(top.compare("(") != 0)
        {
            UpToPar += stack.Pop();
        }
        //Pop '(' off the stack 
        else
        {
            stack.Pop();
            break;
        }
        
    }
    return UpToPar;
    
}

std::string infix2postfix(std::string expression)
{
    //Use PostfixExpression as the string everything gets concatenated to 
    std::string PostfixExpression  = "";
    //Change the string expression to an array of chars 
    //Change the array of chars back to a string with the ')' at the end 
    //Do it this way because it wont work any other way
    char cexpression[expression.size() + 2];
	strcpy(cexpression, expression.c_str());
    cexpression[sizeof(cexpression) - 3] = ')';

    expression = "";
    for(std::size_t i = 0; i < sizeof(cexpression) - 2; i++)
    {
        expression += cexpression[i];
    }

    //Add this so that at the end the program knows when to stop
    stack.Push("(");

    for(std::size_t i = 0; i < expression.length(); i++)
    {
        std::string current = "";
        std::string operation  = "";
        
        switch(expression.at(i))
        {
            case '+':
                //Needs to pop all operations that have a higher or same precedent than addition then push addition
                operation = "+";
                current += PrecedentCheck(operation);
                break;
            case '-':
                //Needs to pop all operation that have a higher or same precedent as subtraction then push subtraction 
                operation = "-";
                current += PrecedentCheck(operation);
                break;
            case '*':
                //Needs to pop all operations that have a higher or same precedent as multiplication then push multiplication
                operation = "*";
                current += PrecedentCheck(operation);
                break;
            case '/':
                //Needs to pop all operations that have a higher or same precedent as multiplication then push multiplication
                operation = "/";
                current += PrecedentCheck(operation);
                break;
            case '^':
                //There is nothing higher precedent except itself
                operation = "^";
                current += PrecedentCheck(operation);
                break;
            case '(':
                //if the current element is a left parantheses push it to the stack
                stack.Push("(");
                break;
            case ')':
                // When a close parentheses is hit get all operations before it 
                current += RightPar();
                break;
            case ' ':
                break;
            default:
                //if it is not an operation then the number needs to be found then appended to the end of the PostfixExpression
                for(std::size_t j = i; j < expression.length(); j++)
                {
                    if(expression.at(j) == '+' || expression.at(j) == '-' || expression.at(j) == '*'
                        || expression.at(j) == '/' || expression.at(j) == '^' 
                        || expression.at(j) == '(' || expression.at(j) == ')')
                    {
                        current += " ";
                        i = j-1;
                        break;
                    }
                    else 
                    {
                        current += expression.at(j);
                    }
                }
                break;
            }
        //current will be a number if nothing was added to the stack 
        //current will be an operation if there is something with higher precedednt or if there was a ')'
        PostfixExpression += current;

    }
    
    return PostfixExpression;
}

std::string Operation(char operation)
{
    /*
    Do B operation A 
    A is the top item on the stack 
    B is the next item on the stack 
    C is the answer 
    Push C back onto stack
    */
    int A = std::stoi(stack.Pop());
    int B = std::stoi(stack.Pop());
    int C = 0;

    switch(operation)
    {
        case '+':
            C = B + A;
            break;
        case '-':
            C = B - A;
            break;
        case '*':
            C = B * A;
            break;
        case '/':
            C = B / A;
            break;
        case '^':
            C = (int) pow(B, A);
            break;
    }
    stack.Push(std::to_string(C));
    return std::to_string(C);
}

std::string PostfixEval(std::string expression)
{
    expression += ")";
    std::string answer = "";

    //Go through expression
    //When operand is found push to stack
    //When operation is found pop top two elements off stack then do B operation A
    //Push answer back onto stack 
    //Top thing in the stack will be the answer 
    for(std::size_t i = 0; i < expression.length(); i++)
    {
        if(expression.at(i) == ')')
        {
            break;
        }
        std::string current  = "";
        switch(expression.at(i))
        {
            case '+':
                current += Operation('+');
                break;
            case '-':
                current += Operation('-'); 
                break;
            case '/':
                current += Operation('/');
                break;
            case '*':
                current += Operation('*'); 
                break;
            case '^':
                current += Operation('^'); 
                break;
            case ' ':
                break;
            default:
                for(std::size_t j = i; j < expression.length(); j++)
                {
                    if(expression.at(j) == ' ')
                    {
                        stack.Push(current);
                        i = j-1;
                        break;
                    }
                    else 
                    {
                        current += expression.at(j);
                    }
                }
                break;
        }
    }
    return stack.Pop();
}

int main()
{
    //opening file code came from here http://www.cplusplus.com/doc/tutorial/files/
    std::string line = "";
    //Name of file
    std::ifstream myfile ("InfixExpressions.txt");
    //Put everything into the logger and purge memory at the end
    Logger logger("InfixLog.txt");
    logger.DisableConsoleLogging();

    //Read from a file then pass whatever line was into the functions
    if (myfile.is_open())
    {
        while(getline(myfile, line)){
            //Non-Expressions dont work so only pass expressions
            if(isdigit(line.at(0)) || line.at(0) == '(')
            {
                std::string InfixExpression = line;

                std::string PostfixExpression = infix2postfix(InfixExpression);
                logger.Log("Postfix Expression: " + PostfixExpression);
                //std::cout <<"Postfix Expression: " << PostfixExpression << std::endl;
                logger.Log("Evaluation of Expression: " + PostfixEval(PostfixExpression) + "\n");
                //std::cout <<"Evaluation of Expression: " << PostfixEval(PostfixExpression) << "\n" <<  std::endl;
            }
        }
        //Close File
        myfile.close();
    }
    else std::cout << "Unable to open file"; 
    
    logger.PurgeMemoryLog();
}
