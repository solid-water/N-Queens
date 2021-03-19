# N-Queens Problem
## Introduction to Problem
The N Queen is a very well-known problem in which we need to place N chess Queens on a N x N chessboard such that no two queens attack each other. The Queens can attack in horizontal, vertical as well as diagonal paths. The chessboard is represented by a N x N matrix where empty squares represent the blank positions and the ‘Q’ represents the positions of the Queens.

## Objective
1. To arrange the N queens on a NxN Chess Board in such a way that No Queen attacks any other queen
2. Generate a large number of N-Queen instances and solve them by Hill Climbing, Hill Climbing with Random Restart and Simulated Annealing Algorithms
3. Compare the three algorithms in terms of Search Cost and Percentage of Solved Problems

## Algorithms used:
### 1. Simple Hill Climbing
The Simple Hill Climbing Algorithm is a local search algorithm in which the movement is in the direction of increasing elevation or value until it reaches the peak or provides the best possible solution for the problem.
Algorithm:
 1. : Evaluate the initial state. If it is a goal state then stop and return success. Otherwise, make initial state as current state.
 2. : Loop until the solution state is found or there are no new operators present which can be applied to the current state.
    1. Select a state that has not been yet applied to the current state and apply it to produce a new state.
    1. Perform these to evaluate new state
        1. If the current state is a goal state, then stop and return success.
        2. If it is better than the current state, then make it current state and proceed further.
        3. If it is not better than the current state, then continue in the loop until a solution is found.
 3. : Exit

### 2. Hill Climbing with Random Restarts
In hill climbing with Random Restart, many hill climbing searches are done from randomly generated initial states. Each search is done until it stops or doesn’t show any progress.
Algorithm :
1. : Start with a random state (i.e., a random configuration of Queens on the board)
2. : Scan through all possible neighbours of the current state and jump to the neighbour with the best heuristic value (less cost), if found any. If there does not exist, a neighbour, with heuristic cost strictly lesser than the current state, randomly generate a new configuration of queens on the board
3. : Repeat step 2, until a state whose objective is strictly higher than all its neighbour’s objectives, is found or Random Restart Limit is reached and then go to step 4
4. : If Random Restart Limit is reached, we stop finding the solution. Else otherwise, the state thus found after the local search is either the local optimum or the global optimum. There is no way of escaping local optima but adding a random restart each time a local optimum is encountered increases the chances of achieving global optimum (the solution to our problem)
5. : Output & Exit

### 3. Simulated Annealing
Simulated Annealing is a technique of optimization which is based on exploration. It is a probabilistic technique for approximating the global optimum of the heuristic function rather than local optima.
Algorithm:
1. : Start with a random state ‘S’ (i.e., a random configuration of Queens on the board) and calculate its cost
2. : Define the Temperature and Schedule variable for Annealing process. 
3. : Generate a random neighbourhood state ‘S1’ and evaluate its objective function.
4. : d=F(S) - F(S1); where, d is the change in objective fn between S & S1. If d<0, replace current state S with neighbourhood state S1. Else find the Probability of S1 to find if it’s feasible to accept a locally bad solution
5. : Decrease the Temperature with the help of schedule
6. : Repeat steps 2-5 until Objective function becomes 0(meaning soln is found) or Temperature becomes 0(soln can’t be found)
7. : Exit
