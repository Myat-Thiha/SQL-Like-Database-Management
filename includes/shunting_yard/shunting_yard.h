#ifndef SHUNTING_YARD
#define SHUNTING_YARD
#include<iostream>
#include<cmath>
#include"../token/token.h"
#include"../token/tokenstr.h"
#include"../token/relational.h"
#include"../stack/MyStack.h"
#include"../queue/MyQueue.h"
#include"../rpn/rpn.h"

class ShuntingYard
{
    public:
        ShuntingYard();
        ShuntingYard(Queue<Token*>const& queue);
        void infix(Queue<Token*>const& queue);
        Queue<Token*> postfix(Queue<Token*>const& queue);
        Queue<Token*> postfix();
    private:
        Stack<Token*>stack_shunting;
        Queue<Token*>queue_input;
};


#endif //SHUNTING_YARD