### General simplex algorithm

1. Transform the system into the general form Ax = 0 and set upper and lower bouds of basic variables, li ≤ si ≤ ui .
2. Set B to be the set of additional variables s1, . . . , sm.
3. Construct the tableau for A.
4. Determine a fixed order on the variables.
5. If there is no basic variable that violates its bounds, return “Satisfiable”. Otherwise, let xi be the first basic variable in the order that violates its bounds.
6. Search for the first suitable nonbasic variable xj in the order for pivoting with xi. If there is no such variable, return “Unsatisfiable”.
7. Perform the pivot operation on xi and xj.
8. Go to step 5.