# Evaluational-Tree  



This challenge was about processing trees and training objective approach.  

Application is about using tree structure to evaluate math calculations.  

App contains three layers:  
Logical - comming with Tree class, this is where all the computations are made.  
Manager - comming with Manager class, here are all the methods to handle user interactions comming from the interface, by passing control to logical layer.  
Interface - contains an interface class with methods needed in every CLI app, like read/print and so on.

Small instruction to app:  
Because it's all about CLI we use defined commands with attributes:  

enter [formula] - formula is mathematic calculation written in Reverse Polish Notation. Formula accepts basic math operator +|-|*|/, numbers and variables. When formula is not correct, app will repair it by adding 1 to places where it is needed, or cutting wrong/not needed tail of formula. Ex. (enter b a + 5 *).  

comp [var0] [var1] [varX] - evaluates actual tree, giving value of computation, takes variables as attributes, number of attributes must correspond to number of variables declared before. Example for tree from previous one (comp 2 1).  

vars - shows all the variables in actual tree.  

print - prints actual tree in RPN.  

join [formula] - tries to create tree in the same way as enter command, and then it joins it to actual tree, in place of last node to the right.



