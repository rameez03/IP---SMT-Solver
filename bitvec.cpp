#include <iostream>
#include "z3++.h"

using namespace z3;

/* 
   Implementing a basic bit-vector solver using Z3 SAT solver to solve propositional formulas
   Here, we are using Tactics Class to convert bit-vector formulas to propositional formulas
   In this example, we have two bit vectors of 32 bits
   Bit vector formulas are:
      x*16 + y == 18
      (x & y) < 12
      y > -50		
*/

void tactic_bitvector() {
    context con;	// instantiating context class
    params p(con);	// creating params object
    p.set("mul2concat", true);	// configuring params
    
    //	configuring solver:	bit-vector formulas --> proposiotional formulas
    tactic t = 
        with(tactic(con, "simplify"), p) &	
        tactic(con, "solve-eqs") &		
        tactic(con, "bit-blast") &		//	performs bit-blasting
        tactic(con, "aig") &			//	compress boolean formulas using And-Inverted Graphs
        tactic(con, "sat");			//	propositional sat solver
      
    // converting tactic object into a solver object using the method mk_solver()  
    solver s = t.mk_solver();
    
    // defining bit-vectors
    expr x = con.bv_const("x", 32);
    expr y = con.bv_const("y", 32);
    
    // defining bit-vector formulas
    s.add(x*16 + y == 18);
    s.add((x & y) < 12);
    s.add(y > -50);
    
    // calling SAT solver
    s.check();
    model m = s.get_model();
    
    // printing outputs
    std::cout << "x = " << m.eval(x) << "\n";
    std::cout << "y = " << m.eval(y) << "\n";
    std::cout << "x*32 + y = " << m.eval(x*32 + y) << "\n";
    std::cout << "x & y = " << m.eval(x & y) << "\n";  
}

int main() {
    try {
        tactic_bitvector();
    }
    catch (exception &e) {
        std::cout << "Unexpected Error: " << e << "\n";
    }
    Z3_finalize_memory();
    return 0;
}
