#include <iostream>
#include "z3++.h"

using namespace z3;

/*
   Implementing a basic formula validator using z3 SAT solver
   In this example, formula is:
   	(Demorgan's Law)
   	not (x or y) = not (x) and not (y)
*/

void isValidFormula() {
    context c;		// instantiating context class

    // defining bit-vectors
    expr x = c.bool_const("x");
    expr y = c.bool_const("y");
    
    // defining formula
    expr conjecture = (!(x || y)) == (!x && !y);
    
    // calling SAT solver
    solver s(c);
    s.add(!conjecture);
    
    // printing outputs
    if(s.check() == unsat)	
    	std::cout << "Formula is valid\n";
    else if(s.check() == sat)	
    	std::cout << "Formula is not valid\n";
    else if(s.check() == unknown) 
    	std::cout << "Unknown\n";
}

int main() {
    try {
        isValidFormula();
    }
    catch (exception &e) {
        std::cout << "Unexpected Error: " << e << "\n";
    }
    Z3_finalize_memory();
    return 0;
}
