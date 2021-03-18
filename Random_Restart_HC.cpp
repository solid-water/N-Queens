// N-Queen problem using Hill Climbing with Random Restart

#include <bits/stdc++.h>
using namespace std;

int n_queens;
int restart_cnt=0, max_restarts=40;
int cost=0, instance=0, maxInstance=100, fail_cnt=0;
bool flag=false;
int final_chess_board[1002][1002]={0};  //Final Chess Board state


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


// fn to find the best neighbour state of the board with lowest heuristic value out of all neighbours
vector<int> nextBoard_withRandomRestart(vector<int> chess_board){
	int bestCost, tempCost, currCost; //to store heuristic value of states
	vector<int> next_board(n_queens), temp_board(n_queens);
	// chess_board -> current state of the board
	// next_board -> next state of the board with better cost
	// temp_board -> to store temporary state of the board
	
	currCost=heuristicFunc(chess_board);  //heuristic value of current state of chess_board
	bestCost=currCost; // stores the best cost out of all neighbours. Initialised with current state cost

	// initialise the next_state & Temp_state with Current_state of Chess_Board
	next_board=chess_board;
	temp_board=chess_board;	

	// iterate to find the next neighbour state with BEST heuristic value out of all neighbours
	
	//choose the queen in the i-th column
	for(int i=0; i<n_queens; i++){ 
		if(i>0){ // discard the change in position for (i-1)th queen
			temp_board[i-1]=chess_board[i-1];
		}

		// move the queen in different rows of i-th column and find heuristic cost of the new state formed
		for(int j=0; j<n_queens; j++){ 
			temp_board[i]=j; //moving queen j-th row of i-th column
			tempCost=heuristicFunc(temp_board);// find cost for this temp_board state
			
			// check if this temp_board state is better than the best_state found so far
			if(tempCost < bestCost){
				// copy temp_board as next_board
				next_board = temp_board;
				// update best_cost
				bestCost = tempCost;
			}
		}
	}

	// IF: cost(current state) == cost(next-best state)
	// => CAN'T Find any Neighbour state with less heuristic value than current_state 
	// NOW, randomly generate a new configuration of Queens and take it to be the next-best board
	if(bestCost == currCost){
		restart_cnt++; //RANDOM RESTART

		// check for Restart Limit for a particular instance
		if(restart_cnt >= max_restarts){
			//restart limit reached => Can't find soln for this instance anymore
			flag=true; 
			return next_board;
		} 

		random_Board_Generator(next_board); // Generating a new Random Configuration of queens
		cost=heuristicFunc(next_board);     // and calculating its heuristic value
	}

	//ELSE: A neighbour state with better heuristic cost found => return the state and its cost 
	else{ 	
		cost=bestCost;
	}
	return next_board;
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



int main(){
	
   	// for using shuffle fn
    srand((unsigned int) time(nullptr));
    random_device rd;
    mt19937 g(rd());

    cout<<"\tN-QUEEN PROBLEM\nHill Climbing with Random Restart\n\n";

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
		restart_cnt = 0; flag = false; //initialising variables for each instance
		
		//generate a random board configuration of queens and shuffle it
    	random_Board_Generator(chess_board); 
	    shuffle(chess_board.begin(), chess_board.end(), g);

	    cost_currState = heuristicFunc(chess_board); // stores the heuristic value of the current state of chess_board
	
	    // test if current_board state is the soln configuration
	    while(cost_currState != 0){
	    	// cost != 0 => not the soln board
	    	// get the next better board and its heuristic cost
	    	chess_board = nextBoard_withRandomRestart(chess_board);
	    	if(flag==false) { // => a better neighbouring state found
	    		cost_currState = cost;
	    	}
	    	else {// flag==true
	    		// Random Restart Limit reached for the current instance
				// terminate the current instance ; soln can't be found 
				fail_cnt++; //keeps track of the #instances which could not find a soln
	    		flag=false;
	    		break;
	    	}
	    }

	    // check if Goal state reached
	    if(cost_currState == 0){ 
	    	// then => store the soln state of the chess board for display
    		goal_state = chess_board;
	    }
	}
	    
	clock_t stop = clock(); //stop the clock for execution time
    
    // display soln

    // Printing soln: a 2-D Chess Board Configuration of the N-Queens: none attacking each other
    if(fail_cnt == maxInstance) // No soln Found
    	cout<<"\nCouldn't find a Solution\n";
    else 
    	print_ChessBoard(goal_state);

    float successRate = (1 - ( (float)fail_cnt/maxInstance))*100; // %age of instances that yielded a solution for N-Queen Problem 
    cout<<"\nRuntime: " << (float) (stop - start) / CLOCKS_PER_SEC << " seconds\n"; // Execution Time of Program
    cout<<"Success Rate: "<< successRate <<"%\n\n";
    
	return 0;
}