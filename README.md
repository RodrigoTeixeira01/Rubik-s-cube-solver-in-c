# Rubik-s-cube-solver-in-c

This readme was written in the context of version 1.0 of the solver. When/if the solver is updated, the read me may or may not be updated as well to reflect the changes.
This is an implementation of Kociemba's algorithm for solving a 3x3 rubik's cube. No AI was used in the creating of this project, in either the original python version or the c version.

The code may be downloaded and distributed freely and long as it is distributed for free and giving the original author (Rodrigo Teixeira) the credits for the code, even if it was modified. Modifying the code is allowed. This warning must not be removed or changed in any way when distributing the code.

How does this work?

There are three pillars for the working of this project: the cube representation, the search algorithm and the pruning tables.
Note: understanding of the kociemba algorithm will be assumed in the explanation. I will be explaining instead the technical details of how it works.

# Cube representation
The cube is represented using 4 arrays: cp, co, ep, eo; which respectively represent corner permutation, corner orientation, edge permutation, edge orientation. The corner arrays are 8 chars (or 8 bytes) long, while the edge arrays are 12 chars (or 12 bytes) long. This is because the 3x3 rubik's cube has 8 corners and 12 edges. The centers are ignored, and thus not stored, as they are fixed in place.

The order of the corners in memory is the following: UBL, UBR, UFR, UFL, DFL, DFR, DBR, DBL.

The order of the edges in memory is the following: UB, UR, UF, UL, DF, DR, DB, DL, FL, FR, BR, BL.

The permutation arrays store the index of each piece in each place. For example, in the solved state the cp arrays stores {0, 1, 2, 3, 4, 5, 6, 7}, as in UBL (index 0) is the UBL piece (value 0), in UBR (index 1= is the UBR piece (value 1), etc.

The edge orientation arrays stores a 0 for every oriented edge and a 1 for every disoriented edge.
The corner orientation array stores how many clockwise twists each corner needs in order to have either the U or the D sticker pointing to either U or D.

# The search algorithm
This project uses the IDA* (iterative deepening A*) algorithm. This algorithm tries increasingly long move sequences until one of them solve the current phase. Additionally, it has an optimization called "pruning", where certain branches of the search are aborted early as they are garanteed not to contain the solution. For example, if we are exploring 4 move long move sequences and the current cube state requires 5 moves or more to solve the phase, then there is no point in searching any further, as we know that literally no 4 move solution will ever solve the phase. This is called an heuristic, and for this algorithm specifically we must use an heuristic that is always less than or equal, but never greater than, the ammount of moves required to solve the phase. This specific type of heuristic is also known as a lower bound. In this project, the lower bound is obtained by looking at the state of the cube and looking up at a giant table to get the pre-calculated value (more detailed information in the next section of the read me).

# The pruning tables
4 pruning tables are beeing used by this project, 2 of them for the first phase and 2 of them for the secound phase.

For the first phase, an edge orientation table and a corner orientation table are used. The edge orientation table is contains 2 ^ 12 / 2 = 2048 values ranging from 1 to 7 and the corner orientation table contains 3 ^ 8 / 3 = 2187 values ranging from 1 to 6, and when looking up the lower bound for a given state, both tables are looked up and the greatest is used as the lower bound. A seperate check is also explicitly written to change the lower bound from 0 to 1 if there are E slice edges outside of the E slice. This way the lower bound is only 0 if the cube is actually in phase 1. Because we know the maximum value for edge orientation is 7, and for corner orientation is 6, we don't actually explore up to depths 7 and 6, but rather up to depths 6 and 5, since any state not explored must necessarely need at least 7 moves for edge orientation or 6 moves for corner orientation. This saves setup time, altho it doesn't affect the time spent actually solving the cube.

For the secound phase, an edge permutation table and a corner permutation table are used. Both tables have 8! (8 factorial) = 40320 values. Note that theese tables store how many moves a state needs to be solved in the context of phase 2 (aka within <U, L2, F2, R2, B2, D>), not to be solved in general. For theese tables I opted to limit the table-generating search to a depth of 8 moves, as I found it to have the best balance of table generation time and search time, and all not explored states are stored as requiring at least 9 moves. For the edge permutation table, only the U layer and the D layer edges are considered, and the E slice edges are ignored. This means that this table doesn't store how many moves are required within phase 2 to solve all the edges, but rather how many moves are required within phase 2 to solve the U and D layer edges. Similarly to what happens in the first phase, an explicit check is also in place in this phase to make sure the E slice edges are also solved.
