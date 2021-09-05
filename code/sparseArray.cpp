#include <iostream>
#include <time.h>
#include <random>
#include <map>
#include<chrono>
#include<cmath>
#include<fstream>

using namespace std;
using namespace std::chrono;

/*
	1. A sparse array will be stored as a vector of a pair of values (distance,data), where
	distance-> horizontal distance of an element from (0,0) in a row order format
	data-> value of the element 

	2. Main idea for multiplication is based on the formula:

		c[i][j] =  sum(A[i][k]*B[k][j]) for all k in the range (0,p-1)

	it can be seen that an element in  A , A[i][k] will only contribute to a non zero value
	of an element in C, if there exits a non zero B[k][j] ( 0<=j<=p-1) , i.e , if there is a
	non zero element in the kth row of B

	3. using an array "row_marker" ,which tells us where the first non zero element of a particular
	   row is in the vector representation of B.
       If a row 'r' has all zeroes ,then row_marker[r]=-1
       else, row_marker[r] = position of the element in the vector B


*/

/*
	function to initialize the sparse arrays A and B
	makes use of a map with distance as the key and data as the value associated with the key,
	to keep track of the positions that have already been filled
	and to keep the elements in a sorted order based on their distance values.
	then converts the map into a vector and returns the vector
*/
vector<pair<int,int>> init(int m,int n,float sp){
	
	float total_nz_elements = m*n*(1.0-sp);

	map<int,int> temp_map;

	for(int i=0;i<floor(total_nz_elements);i++){
		int d = rand()%(m*n);  // generate a random distance at which a value will be filled

		if(temp_map.find(d)==temp_map.end()){ //if position not filled
			int data = rand()%10;
			if(data==0){ // if 0 itself has been generated then try again
				i--;
				continue;
			}
			temp_map.insert({d,data}); 
		}

		else //if position filled then try again
			i--;
	}
	vector<pair<int,int>> temp_v(temp_map.begin(),temp_map.end());  //convert to a vector
	return temp_v;
}


// returns the distance of an element at (x,y) index
int distance(int x,int y,int col){
	return (x*col)+y;
}


// returns the 2-D indexes of an element at a distance 'd'
pair<int,int> co_ordinate(int d,int col){
	pair<int,int> location;
	location.first=d/col;
	location.second=d%col;
	return location;
} 


map<int,int> multiply(vector<pair<int,int>> A,vector<pair<int,int>> B,
	vector<short int> row_marker,int n,int p){

	map<int,int> C;

	for(auto a: A){
		auto a_pos =  co_ordinate(a.first,n); // get the 2-D indexes of the element, say(i,k)

		/*  get the lower and upper bounds of the kth row in B.
			the current element of A will only be multiplied with the elements of B 
			with a distance value in between these bounds.
		*/

		int min_dval_B = distance(a_pos.second,0,p); // distance of B(k,0) is lower bound
		int max_dval_B = min_dval_B+p-1;  // distance of B(k,p-1) is upper bound 

		int position = row_marker[a_pos.second]; // position of the first non-zero element of kth row

		// if the kth row in B has a non zero element then compute further otherwise examine next element of A
		
		if(position>-1){ 
			while(position<B.size()&&B[position].first<=max_dval_B){

				auto b_pos= co_ordinate(B[position].first,p); // get indexed of the non-zero element say (k,j)
				
				// A[i][k] and B[k][j] will contribute to C[i][j] , so calculate its distance value
				int dval_C= distance(a_pos.first,b_pos.second,p); 
				
				C[dval_C]+= a.second*B[position].second; //update the value associated with this distance
				
				position++; //move to next non-zero element in B			
			}

		}

		// repeat for all elements in A
		
	}

	return C;
}

int main(){

	srand((unsigned)time(NULL));

	// ofstream filestream("spdata.txt");
	// ofstream filestream2("timedata.txt");


	int m,n,p;
	float sA=0.3,sB=0.3;

	cin>>m>>n>>p;


	for(float step=0.0;step<=0.69;step=step+0.01){

		vector<pair<int,int>> A = init(m,n,sA+step);

		vector<pair<int,int>> B = init(m,n,sB+step);

		/*	
			lines 146-160 computes the "row_marker" array discussed above
		*/
		vector<short int> row_marker(n,-1);
		int lower=0,upper=p-1,row=0; // lower and upper are the min and max distances of an element in a row
		for(int i=0;i<B.size();i++){
			if(B[i].first>=lower){
				if(B[i].first<=upper) // first non zero element of a row found which is the ith element of vector B
					row_marker[row]=i;

				else // examine the current element for the next row
					i--;

				row++;
				lower+=p;
				upper+=p;
			}
		}

		
		auto start = high_resolution_clock::now(); //start clock timing

		map<int,int> C=multiply(A,B,row_marker,n,p);

		auto stop = high_resolution_clock::now();	//stop clock timing
		
		
		auto duration = duration_cast<milliseconds>(stop-start);
		
		// write to data file
		// filestream<<sA+step<<endl;
	 	// filestream2<<duration.count()<<endl;

	}

	
}