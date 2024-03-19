#ifndef RPN_H
#define RPN_H
#include"../token/token.h"
#include"../token/tokenstr.h"
#include"../token/relational.h"
#include"../stack/MyStack.h"
#include"../queue/MyQueue.h"
#include"../table/typedefs.h"
#include<iostream>
#include<cmath>
using namespace std;

class RPN
{
    public:
        RPN();
        RPN(Queue<Token*>const& queue);
        void set_input(Queue<Token*>const& queue);
        vectorstr evaluate();

    private:
        vectorstr result;
        Stack<Token*>stack_rpn;
        Queue<Token*>queue_rpn;
};







#endif //RPN_H