#include"rpn.h"

RPN::RPN()
{

}

RPN::RPN(Queue<Token*>const& queue)
{
    queue_rpn=queue;
}

void RPN::set_input(Queue<Token*>const& queue)
{
    queue_rpn=queue;
}

vectorstr RPN::evaluate()
{
    Token * walker=queue_rpn.pop();
    string str1,str2;
    while(walker!=nullptr)
    {
        switch(walker->TypeOf())
        {
            case TOKENSTRING:
            {
                stack_rpn.push(walker);
                break;
            }
            case RELATIONAL:
            {
                str1=static_cast<TokenStr*>(stack_rpn.pop())->string_only();
                str2=static_cast<TokenStr*>(stack_rpn.pop())->string_only();
                result.push_back(str2);
                result.push_back(static_cast<Relational*>(walker)->string_only());
                result.push_back(str1);
                break;
            }
            case LOGICAL:
            {
                
            }
            default:
            {
                break;
            }
        }
        walker=queue_rpn.pop();
    }
    return result;
}