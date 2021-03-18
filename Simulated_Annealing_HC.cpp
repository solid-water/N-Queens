// N-Queen problem using Hill Climbing with Simulated Annealing

#include <bits/stdc++.h>
using namespace std;

#define TEMPERATURE 4000 //Temperature value taken for annealing

int n_queens;
int cost=0, instance=0, maxInstance=100, fail_cnt=0;
bool flag=false;
int final_chess_board[1002][1002]={0};  //Final Chess Board 


// fn to generate a random configuration of N queens on the chess board
void random_Board_Generator(vector<int> &chess_board){
    for (int i = 0; i < n_queens; i++) { // Create a vector from 0 to N_QUEENS - 1
        chess_board[i]=i;
    }
    //Initial Configuration of chess_board is={0,1,2,3,4,....,n}
    //Now Shuffling the configuration to make sure it is random
    random_shuffle(chess_board.begin(), chess_board.end()); 
    return;
}


// heuristic/objective func of a state: #pairs of queens attacking each other
int heuristicFunc(vector<int> chess_board){
    int currCost=0; //variable for heuristic value of state
    int r1,r2,c1,c2;

    // loop to check collisions of queens
    for(int i=0; i<n_queens; i++){
        r1=chess_board[i];
        c1=i;

        for(int j=i+1; j<n_queens; j++){
            r2=chess_board[j];
            c2=j;

            // check for collision of queens 
            //  rows  || columns||   diagonal-collision         
            if(r1==r2 || c1==c2 || abs(r1-r2)==abs(c1-c2) ){
                currCost++;
            }
        }
    }
    return currCost;
}


vector<int> nextBoard_withSimulatedAnnealing(vector<int> chess_board, double t){
    int currCost, tempCost; //to store heuristic value of states
    vector<int> next_board;
    // chess_board -> current state of the board
    // next_board -> next state of the board with better cost
    
    currCost = heuristicFunc(chess_board); //heuristic value of current state of chess_board

    // initialise next_board with current_chess_board
    next_board = chess_board; 
    
    
    int rand_col_1, rand_col_2;
    while (true) { // pick 2 distinct random queens from the current chess board
        rand_col_1 = (int) rand() % n_queens;   //Random Function to generate a number from 0 to N-1.
        rand_col_2 = (int) rand() % n_queens;   //Random Function to generate a number from 0 to N-1.
        if (next_board[rand_col_1] != next_board[rand_col_2]) break;
        if(n_queens == 1) break; // to prevent infinite loop
    }

    swap(next_board[rand_col_1], next_board[rand_col_2]); // swap the two queens chosen to form a new state
    
    tempCost = heuristicFunc(next_board); //heuristic value of next_board

    double delta = tempCost - currCost;  // Calculating difference b/w cost of new state and current state.
    if (delta < 0){         //If cost of new state is less than current state assign new state to the current state. 
        chess_board = next_board; //Assigning new state to current state 
        currCost = tempCost; //Calculating the Cost of current state
    }
    else {
        double p = exp(-delta / t); // finding probability of neighbouring soln
        // accepting a less optimal solution, with probability(p) inverse to the increase in cost => for global maxima 
        if (rand() / double(RAND_MAX) < p) { 
            chess_board = next_board; // Assigning new state to current state
            currCost = tempCost;  // heuristic value of current state
        }
    }

    // return the next_board_state and its cost
    cost = currCost;
    return chess_board;
}


// fn to print soln: a 2-D Chess Board Configuration of the N-Queens
void print_ChessBoard(vector<int> chess_board){
    
    // marking the queens' positions on 2d-final_chess_board
    for(int i=0; i<n_queens; i++){
        // chess_board vector indicates the Row of the Queen in i-th Column
        final_chess_board[ chess_board[i] ][i]=1;   
    }

    // printing the soln : 2d Chess_Board Configuration of N-Queens
    
    cout<<"\nOne Possible Solution : \n";
    for(int k=0;k<n_queens;k++) cout<<"__"; //to print chess board outline
    cout<<"\n";
    
    for(int i=0; i < n_queens; i++) {   
        cout<<"|";
        for(int j=0 ; j < n_queens; j++) {
            if(final_chess_board[i][j]==1){
                cout<<"Q|"; // |Q| denotes presence of Queen on Chess Board
            }
            else{
                cout<<"_|"; // |_| denotes an empty square on chess board 
            }
        }
        cout<<endl;
    }
}



int main() {
    
    // for using shuffle fn
    srand((unsigned int) time(nullptr));
    random_device rd;
    mt19937 g(rd());

    cout<<"\tN-QUEEN PROBLEM\nHill Climbing with Simulated Annealing\n\n";

    // INPUT
    cout<<"Enter Number of queens:"<<endl;
    cin >> n_queens; // Global Variable to store the Number of Queens for N-Queen Problem 

    
    // for N-Queen problem, soln DOESN'T exist for N=2 && N=3 && N<1
    if(n_queens<=3 && n_queens!=1){ 
        cout<<"No arrangement is possible"<<endl;
        return 0;
    }

    clock_t start = clock(); // For execution time of program
    
    vector<int> chess_board(n_queens), goal_state(n_queens);// stores the Configuration of N-Queens on Chess_Board
    int cost_currState; // stores heuristic value of current state of the chess board

    while(instance < maxInstance){ // loop to generate many instances of n-queen ans solve them ; #instances=maxInstance
        instance++;

        //generate a random board configuration of queens and shuffle it
        random_Board_Generator(chess_board); 
        shuffle(chess_board.begin(), chess_board.end(), g);

        cost_currState = heuristicFunc(chess_board); // stores the heuristic value of the current state of chess_board
      
        // Simulated Annealing
      
        double t = TEMPERATURE; //Initial Temperature at which the process starts. 
        double sch = 0.99;      //Temperature Schedule : mapping from time to temperature
        
        while (t > 0.000001) { //Running loop till temperature is almost zero & to prevent TLE
            t *= sch;  //Slowely Decreasing the temperature Value as algo runs longer
            
            //find next state & its cost via Simulated Annealing Algo
            chess_board = nextBoard_withSimulatedAnnealing(chess_board, t);
            cost_currState = cost;

            // check if Goal state reached
            if (cost_currState == 0) {
                // then => store the soln state of the chess board for display
                goal_state = chess_board;
                break;
            }
        }
        if(t <= 0.000001 && cost_currState != 0){
            fail_cnt++;
        }
    }

    clock_t stop = clock(); //stop the clock for execution time
    
    // display soln

    // Printing soln: a 2-D Chess Board Configuration of the N-Queens: none attacking each other
    if(fail_cnt == maxInstance) // No soln Found
        cout<<"\nCouldn't find a Solution\n";
    else 
        print_ChessBoard(goal_state); // print chess board configuration

    float successRate = (1 - ( (float)fail_cnt/maxInstance))*100; // %age of instances that yielded a solution for N-Queen Problem 
    cout<<"\nRuntime: " << (float) (stop - start) / CLOCKS_PER_SEC << " seconds\n"; // Execution Time of Program
    cout<<"Success Rate: "<< successRate <<"%\n\n";
    
    return 0;
}