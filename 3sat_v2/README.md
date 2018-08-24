# We’re Back: 3SAT

Satisfiability is the problem of determining if the variables of a given Boolean formula can be assigned in such a way as to make the formula evaluate to TRUE. Equally important is to determine whether no such assignments exist, which would imply that the function expressed by the formula is identically FALSE for all possible variable assignments. In this latter case, we would say that the function is unsatisfiable; otherwise it is satisfiable.

A _literal_ is either a variable or the negation of a variable. A clause is a disjunction of literals.

3SAT is a special case of k-satisfiability, when each clause contains exactly k = 3 literals. For example:

_E_ = (_x<sub>1</sub>_ $\vee$ _-x<sub>2</sub>_ $\vee$ _-x<sub>3</sub>_) $\wedge$
 (_x<sub>1</sub>_ $\vee$ _x<sub>2</sub>_ $\vee$ _x<sub>3</sub>_)

In this formula, E has two clauses (denoted by parentheses), four variables (_x<sub>1</sub>_, _x<sub>2</sub>_, _x<sub>3</sub>_, _x<sub>4</sub>_), and _k=3_ (three literals per clause).

Write a parallel program that determines if there is an assignment of Boolean values that will satisfy the given 3SAT expression.

## Input

The input contains only one test case. The first line contains two integers: the number of clauses (_N_) and the number of literals (_L_), separated by a single space (1 ≤ _N_ ≤ 255, 1 ≤ _L_ < 2<sup>64</sup>). The next N lines contain three integers separated by a space (1 ≤ _x<sub>1</sub>_ ≤ _N_).
These integers represent a literal: either a variable or the negation of a variable.

_The input must be read from the standard input._

## Output

If there is an assignment that satisfies the entire input expression, the output contains an integer that represents the solution followed by its binary representation: each bit represents the variable’s value. 
Otherwise, if there is no solution, the output contains only one message _'Solution not found.'_.

_The output must be written to the standard output._

### Example 1

| Input | Output |
| ----- | ------ |
| 4 3 |  |
| 3 3 3 |  |
| 2 1 -1 | Solution found [5]: 1 0 1 |
| -3 -2 -3 |  |
| 2 1 2 |  |



### Example 2


| Input | Output |
| ----- | ------ |
| 2 1 |  |
| 1 1 1 | Solution not found. |
| -1 -1 -1 |  |