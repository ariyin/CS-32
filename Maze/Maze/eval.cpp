//
//  eval.cpp
//  Maze
//
//  Created by Jenna Wang on 5/1/23.
//

#include <iostream>
#include <string>
#include <stack>
#include <cassert>
using namespace std;

int convert(string infix, string& postfix);
void removespace(string &s);

//   If infix is a syntactically valid infix boolean expression,
//   then set postfix to the postfix form of that expression, set
//   result to the value of the expression, and return zero. If
//   infix is not a syntactically valid expression, return 1; in
//   that case, postfix may or may not be changed, but result must
//   be unchanged.
int evaluate(string infix, string& postfix, bool& result)
{
    if(convert(infix, postfix) == 1)
    {
        return 1;
    }
    
    stack<bool> oprnd;
    bool operand1, operand2;
    
    for(int i = 0; i < postfix.size(); i++)
    {
        if(postfix.at(i) == 'T' || postfix.at(i) == 'F')
        {
            oprnd.push(postfix.at(i) == 'T' ? true : false);
        }
        
        else if(postfix.at(i) == '!')
        {
            operand1 = oprnd.top();
            oprnd.pop();
            oprnd.push(!operand1);
        }
        
        else
        {
            operand2 = oprnd.top();
            oprnd.pop();
            operand1 = oprnd.top();
            oprnd.pop();
            
            // apply the operation that ch represents to operand1 and operand2, and push the result onto the stack
            switch(postfix.at(i))
            {
                case '&':
                    oprnd.push(operand1&&operand2);
                    break;
                case '^':
                    oprnd.push(operand1^operand2);
                    break;
            }
        }
    }
    
    // check
    if(oprnd.size() > 1)
    {
        return -1;
    }
    
    result = oprnd.top();
    return 0;
}

// return 1 if infix is invalid
int convert(string infix, string& postfix)
{
    // remove spaces
    removespace(infix);
    
    postfix = "";
    stack<char> oprtr;
    
    for(int i = 0; i < infix.size(); i++)
    {
        switch(infix.at(i))
        {
            case 'T':
            case 'F':
                // checking for invalid infix expressions:
                // if not the first char, can't have a T/F/) before
                if(i != 0 && (infix.at(i - 1) == 'T' || infix.at(i - 1) == 'F' || infix.at(i - 1) == ')'))
                {
                    return 1;
                }
                
                // if not the last char, can't have a T/F/( after
                if(i != infix.size() - 1 && (infix.at(i + 1) == 'T' || infix.at(i + 1) == 'F' || infix.at(i + 1) == '('))
                {
                    return 1;
                }
                
                // if valid, append the operand to the output
                postfix += infix.at(i);
                break;
            case '(':
                // checking for invalid infix expressions:
                // can't be last
                if(i == infix.size() - 1)
                {
                    return 1;
                }
                
                // if not the first char, can't have T/F/) before
                if((i != 0) && (infix.at(i - 1) == 'T' || infix.at(i - 1) == 'F' || infix.at(i - 1) == ')'))
                {
                    return 1;
                }
                
                // if not the last char, can't have )/&/^ after
                if((i != infix.size() - 1) && (infix.at(i + 1) == ')' || infix.at(i + 1) == '&' || infix.at(i + 1) == '^'))
                {
                    return 1;
                }
                
                oprtr.push(infix.at(i));
                break;
            case ')':
                // checking for invalid infix expressions:
                // can't be first
                if(i == 0)
                {
                    return 1;
                }
                
                // if not the first char, can't have (/!/&/^  before
                if((i != 0) && (infix.at(i - 1) == '(' || infix.at(i - 1) == '!' || infix.at(i - 1) == '&' || infix.at(i - 1) == '^'))
                {
                    return 1;
                }
                
                // if not the last char, can't have T/F/! after
                if((i != infix.size() - 1) && (infix.at(i + 1) == 'T' || infix.at(i + 1) == 'F' || infix.at(i + 1) == '!'))
                {
                    return 1;
                }
                
                // pop stack until matching '('
                while(!oprtr.empty() && oprtr.top() != '(')
                {
                    postfix += oprtr.top();
                    oprtr.pop();
                }
                
                oprtr.pop(); // remove the '('
                break;
            case '!':
                // checking for invalid infix expressions:
                // can't be last
                if(i == infix.size() - 1)
                {
                    return 1;
                }
                
                // if not the first char, can't have )/T/F  before
                if((i != 0) && (infix.at(i - 1) == ')' || infix.at(i - 1) == 'T' || infix.at(i - 1) == 'F'))
                {
                    return 1;
                }
                
                // if not the last char, can't have )/&/^ after
                if((i != infix.size() - 1) && (infix.at(i + 1) == ')' || infix.at(i + 1) == '&' || infix.at(i + 1) == '^'))
                {
                    return 1;
                }
                
                // highest precedence
                oprtr.push(infix.at(i));
                break;
            case '&':
                // checking for invalid infix expressions:
                // can't be first
                if(i == 0)
                {
                    return 1;
                }
                
                // can't be last
                if(i == infix.size() - 1)
                {
                    return 1;
                }
                
                // if not the first char, can't have (/!/&/^  before
                if((i != 0) && (infix.at(i - 1) == '(' || infix.at(i - 1) == '!' || infix.at(i - 1) == '&' || infix.at(i - 1) == '^'))
                {
                    return 1;
                }
                
                // if not the last char, can't have )/&/^ after
                if((i != infix.size() - 1) && (infix.at(i + 1) == ')' || infix.at(i + 1) == '&' || infix.at(i + 1) == '^'))
                {
                    return 1;
                }
                
                // if lower precedence
                while(!oprtr.empty() && oprtr.top() != '(' && oprtr.top() != '^')
                {
                    postfix += oprtr.top();
                    oprtr.pop();
                }
                
                oprtr.push(infix.at(i));
                break;
            case '^':
                // checking for invalid infix expressions:
                // can't be first
                if(i == 0)
                {
                    return 1;
                }
                
                // can't be last
                if(i == infix.size() - 1)
                {
                    return 1;
                }
                
                // if not the first char, can't have (/!/&/^  before
                if((i != 0) && (infix.at(i - 1) == '(' || infix.at(i - 1) == '!' || infix.at(i - 1) == '&' || infix.at(i - 1) == '^'))
                {
                    return 1;
                }
                
                // if not the last char, can't have )/&/^ after
                if((i != infix.size() - 1) && (infix.at(i + 1) == ')' || infix.at(i + 1) == '&' || infix.at(i + 1) == '^'))
                {
                    return 1;
                }
                
                while(!oprtr.empty() && oprtr.top() != '(')
                {
                    postfix += oprtr.top();
                    oprtr.pop();
                }
                
                oprtr.push(infix.at(i));
                break;
            default:
                return 1;
                break;
        }
    }
    
    // append stack top to postfix
    while(!oprtr.empty())
    {
        // uneven amount of parentheses
        if(oprtr.top() == '(')
        {
            return 1;
        }
        
        postfix += oprtr.top();
        oprtr.pop();
    }
    
    // empty postfix
    if(postfix == "")
    {
        return 1;
    }
    
    return 0;
}

void removespace(string &s)
{
    for (int i = 0; i < s.length(); i++)
    {
        if (s.at(i) == ' ')
        {
            s.erase(s.begin() + i);
            i--;
        }
    }
}

int main()
{
    string pf;
    bool answer;
//    assert(evaluate("T", pf, answer) == 0 && answer == true);
//    assert(evaluate("(F)", pf, answer) == 0 && answer == false);
//    assert(evaluate("T^(F)", pf, answer) == 0 && answer == true);
//    assert(evaluate("T ^ !F", pf, answer) == 0 && answer == false);
//    assert(evaluate("!(T&F)", pf, answer) == 0 && answer == true);
//    assert(evaluate("!T&F", pf, answer) == 0 && answer == false);
//    assert(evaluate("T^F&F", pf, answer) == 0 && answer == true);
//    assert(evaluate("T&!(F^T&T^F)^!!!(F&T&F)", pf, answer) == 0 && answer == true);
//
//    assert(evaluate("T^ F", pf, answer) == 0  &&  pf == "TF^"  &&  answer);
//    assert(evaluate("T^", pf, answer) == 1);
//    assert(evaluate("F F", pf, answer) == 1);
//    assert(evaluate("TF", pf, answer) == 1);
//    assert(evaluate("()", pf, answer) == 1);
//    assert(evaluate("()T", pf, answer) == 1);
//    assert(evaluate("T(F^T)", pf, answer) == 1);
//    assert(evaluate("T(&T)", pf, answer) == 1);
//    assert(evaluate("(T&(F^F)", pf, answer) == 1);
//    assert(evaluate("T|F", pf, answer) == 1);
//    assert(evaluate("", pf, answer) == 1);
//    assert(evaluate("F  ^  !F & (T&F) ", pf, answer) == 0
//                           &&  pf == "FF!TF&&^"  &&  !answer);
//    assert(evaluate(" F  ", pf, answer) == 0 &&  pf == "F"  &&  !answer);
//    assert(evaluate("((T))", pf, answer) == 0 &&  pf == "T"  &&  answer);
    assert(evaluate("T&(F&T))&((T&T)", pf, answer) == 1);
    cout << "Passed all tests" << endl;
}
