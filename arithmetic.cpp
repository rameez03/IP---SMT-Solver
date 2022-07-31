#include <iostream>
#include "z3++.h"

using namespace z3;

/* 
   Implementing a basic bit-vector solver using Z3 SAT solver to solve linear arithmetic formulas
   Here, we are using Tactics Class to convery linear arithmetic formulas to propositional formulas
   In this example, formulas are:
      x*16 + y == 18
      (x & y) < 12
      y > -50		
*/

void tactic_linath() {
    context con;	// instantiating context class
    params p(con);	// creating params object
    
    // configuring params 
    p.set("arith_lhs", true);	
    p.set("som", true);
    
    // configuring solver with tactics class
    solver s = 
        (with(tactic(con, "simplify"), p) &
         tactic(con, "normalize-bounds") &
         tactic(con, "lia2pb") &
         tactic(con, "pb2bv") &
         tactic(con, "bit-blast") &	//	performs bit-blasting
         tactic(con, "sat")).mk_solver();
         
    // defining variables
    expr x = con.int_const("x");
    expr y = con.int_const("y");
    expr z = con.int_const("z");
    
    // defining linear arithmetic formulas
    s.add(x > 2 && x < 20);
    s.add(y > 3 && y < 20);
    s.add(z > 5 && z < 20);
    s.add(3*x + 2*y == z);
    
    // calling SAT solver
    std::cout << s.check() << "\n";
    model m = s.get_model();
    
    // printing outputs
    std::cout << "x = " << m.eval(x) << "\n";
    std::cout << "y = " << m.eval(y) << "\n";
    std::cout << "z = " << m.eval(z) << "\n";
}

int main() {
    try {
        tactic_linath();
    }
    catch (exception &e) {
        std::cout << "Unexpected Error: " << e << "\n";
    }
    Z3_finalize_memory();
    return 0;
}
