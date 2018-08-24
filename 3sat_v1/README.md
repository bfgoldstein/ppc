# 3SA T

Satisfiability is a problem that takes an expression made up of the conjunction of disjunctions between Boolean variables. To solve the problem you must determine whether or not an assignment of TRUE or FALSE to the Boolean variables exists that will make the entire expression evaluate to TRUE. The Satisfiability belongs to the NP- complete class problem.
The 3SAT problem is a version of Satisfiability that restricts the size of the disjunction subexpressions to contain exactly three variables. An example of a 3SAT expression would be:

(X_1 | !X_2 | X_3) & (X_3 | X_2 | !X_1) & (X_2 | X_1 | !X_3) & (!X_1 | !X_2 | !X_3)

where ‘|’ is OR, ‘&’ is AND, and ‘!’ signifies NOT. This expression is satisfied when the variables X_1 and X_2 are TRUE and X_3 is FALSE.
Write a parallel program that determines if there is an assignment of Boolean values that will satisfy the given 3SAT expression.


### Input

The input contains only one test case. The first line contains two integers: the maximum number of variables that will be in the expression (N) and the number of disjunction subexpressions in the file (K), separated by a single space (1 ≤ N ≤ 100, 1 ≤ K ≤ 104). The next K lines will contain three integers from abs([1,N]) separated by a space. These integers represent the subscript of a Boolean variable and a negative value represents the negation of the Boolean variable within that subexpression.

_The input must be read from standard input_


### Output

If there is an assignment that satisfies the entire input expression, the output contains N lines. Each line corresponds to one of the N variables and the Boolean value needed.


The format of each line is an integer from [1,N], a space, and the character ‘T’ or ‘F’ for the assignment of TRUE or FALSE, respectively. The variables must be ordered. Otherwise, if there is no solution, the output contains only one message ‘Solution is not possible’.
The output must be written to standard output


## Example 1

| Input | Output |
| ----- | ------ |
| 3 4 | 1 T |
| 1 -2 3 | 2 T |
| 3 2 -1 | 3 T |
| 2 1 -3 | |
| -1 -2 -3 | | 


## Example 2

| Input | Output |
| ----- | ------ |
| 1 2 |  |
| 1 1 1 | Solution is not possible |
| -1 -1 -1 | |