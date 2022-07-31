#include <iostream>
#include "z3++.h"

using namespace z3;

/* 
   Implementing an expression evaluator using Z3 SAT solver
   In this example, expressions used are:
      z < x + y
      x < y + z
      y < 7
   Output:
      x + y + z = ?	
*/

void eval_exp() {
    context c;	// instantiating context class
    
    // defining bit-vectors
    expr x = c.int_const("x");
    expr y = c.int_const("y");
    expr z = c.int_const("z");
    
    solver s(c);	// instantiating SAT solver

    // defining expressions
    s.add(z < x + y);
    s.add(x < y + z);
    s.add(y < 10);
    
    // calling SAT solver
    std::cout << s.check() << "\n";
    model m = s.get_model();
    
    // displaying results
    std::cout << "x + y + z = " << m.eval(x+y+z) << "\n";
}

int main() {
    try {
        eval_exp();
    }
    catch (exception &e) {
        std::cout << "Unexpected Error: " << e << "\n";
    }
    Z3_finalize_memory();
    return 0;
}
