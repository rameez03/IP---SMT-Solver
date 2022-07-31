#include <iostream>
#include "z3++.h"

using namespace z3;

/* 
   Implementing a model finder using Z3 SAT solver
   
   In this example, expressions used are:
      x <= 15
      y > x - 5
      
   Output:
      x = ?	
      y = ?
*/

void modelfind() {
    context c;	// instantiating context class
    
    // defining bit-vectors
    expr x = c.int_const("x");
    expr y = c.int_const("y");
    
    solver s(c);	// instantiating SAT solver

    // defining expressions
    s.add(x <= 15);
    s.add(y > x - 5);
    
    // calling SAT solver
    std::cout << s.check() << "\n";
    model m = s.get_model();
    
    // displaying assignments
    for (unsigned i = 0; i < m.size(); i++) {
        func_decl a = m[i];
        assert(a.arity() == 0); 
        std::cout << a.name() << " = " << m.get_const_interp(a) << "\n";
    }
}

int main() {
    try {
        modelfind();
    }
    catch (exception &e) {
        std::cout << "Unexpected Error: " << e << "\n";
    }
    Z3_finalize_memory();
    return 0;
}
