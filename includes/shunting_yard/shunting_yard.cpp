#include<iostream>
#include<cassert>
#include"shunting_yard.h"
#include"../token/token.h"
#include"../token/tokenstr.h"
#include"../token/relational.h"
#include"../stack/MyStack.h"
#include"../queue/MyQueue.h"
using namespace std;

ShuntingYard::ShuntingYard()
{

}

ShuntingYard::ShuntingYard(Queue<Token*>const& queue)
{
    queue_input=queue;
}

Queue<Token*> ShuntingYard::postfix()
{
    Queue<Token*>queue_output;
    Token * walker=queue_input.pop();
    Token * hold;
    int walker_order;
    int top_order;
    Queue<Token*>logical_hold;
    Queue<Token*>temp;
    while(walker!=nullptr)
    {
        //cout<<"Post fix 1"<<endl;
        switch(walker->TypeOf())
        {
            case TOKENSTRING:
            {
                //cout<<"Post fix double"<<endl;
                queue_output.push(walker);
                //cout<<"queue size: "<<queue_output.size()<<endl;
                break;
            }
            case RELATIONAL:
            {
                stack_shunting.push(walker);
                break;
            }
            case LOGICAL:
            {
                if(static_cast<Logical*>(walker)->string_only()=="or")
                {
                    if(stack_shunting.size()==0)
                    {
                        stack_shunting.push(walker);
                        break;
                    }
                    else{
                    while(stack_shunting.top()->TypeOf()!=LPAREN)
                    {
                        queue_output.push(stack_shunting.pop());
                        if(stack_shunting.size()==0)
                        break;
                    }
                    stack_shunting.push(walker);
                    //cout<<"stack is "<<stack_shunting<<endl;
                    //cout<<"queue is "<<queue_output<<endl;
                    break;
                    }
                }
                if(static_cast<Logical*>(walker)->string_only()=="and")
                {
                    if(stack_shunting.size()==0)
                    {
                        stack_shunting.push(walker);
                        break;
                    }
                    else if(static_cast<Logical*>(stack_shunting.top())->string_only()=="or")
                    {
                        stack_shunting.push(walker);
                        break;
                    }
                    else
                    {
                    while(stack_shunting.top()->TypeOf()!=LPAREN && static_cast<Logical*>(stack_shunting.top())->string_only()!="or")
                    {
                        queue_output.push(stack_shunting.pop());
                        if(stack_shunting.size()==0)
                        break;
                    }
                    stack_shunting.push(walker);
                    //cout<<"stack is "<<stack_shunting<<endl;
                    //cout<<"queue is "<<queue_output<<endl;
                    break;
                    }
                }
            }
            case LPAREN:
            {
                stack_shunting.push(walker);
                break;
            }
            case RPAREN:
            {
                while(stack_shunting.top()->TypeOf()!=LPAREN)
                {
                    assert(stack_shunting.size()!=0);
                    queue_output.push(stack_shunting.pop());
                }
                assert(stack_shunting.top()->TypeOf()==LPAREN);
                stack_shunting.pop();
                //cout<<"stack is "<<stack_shunting<<endl;
                //cout<<"queue is "<<queue_output<<endl;
                break;
            }
            default:
            break;
        }
        walker=queue_input.pop();
    }
    int size=stack_shunting.size();
                for(int i=0;i<size; i++)
                {
                    hold=stack_shunting.pop();
                    queue_output.push(hold);
                }
    return queue_output;
}

Queue<Token*> ShuntingYard::ShuntingYard::postfix(Queue<Token*>const& queue)
{
    queue_input=queue;
    return postfix();
}
void ShuntingYard::infix(Queue<Token*>const& queue)
{
    queue_input=queue;
}
   
