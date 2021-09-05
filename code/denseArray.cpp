#include <iostream>
#include <time.h>
#include <random>
#include <map>
#include<chrono>
#include<fstream>

using namespace std;
using namespace std::chrono;

/*
	as the sparsity of the arrays increases from 0.3 to 0.99 it can seen from the graph that 
	dense array multiplication algo takes the same amount of time on an average.
*/

//function to initialize the arrays
void init_dense_array(int **arr,int m, int n,float sp){
	
	
	map<pair<int,int>, int> sparse_values_map;// hashmap to keep a track of positions that have been assigned values

	float total_nz_elements= ((1-sp)*m*n);

	for(int i=0;i<total_nz_elements;i++){
		pair<int,int> temp= {rand()%m,rand()%n};// generate a random position to fill

		if(sparse_values_map.find(temp)==sparse_values_map.end()){ //assign a random value if position not generated before
			sparse_values_map.insert({temp,1});
			arr[temp.first][temp.second]=rand()%100;
		}

		else  //if position generated before, then try again
			i--;
	}


}


//function to assign memory for the arrays
int ** build_dense_array(int m,int n){

	int **arr = new int *[m];

	for(int i=0;i<m;i++)
		arr[i]= new int[n];

	return arr;
}

int main(){

	srand((unsigned)time(NULL));
	
	// ofstream filestream("spdata.txt");
	// ofstream filestream2("timedata.txt");

	int m,n,p;

	cin>>m>>n>>p;

	float sp_A=0.3,sp_B=0.3;
	
	

	for(float step=0.0;step<=0.69;step=step+0.01){

		int **A = build_dense_array(m,n),**B = build_dense_array(n,p); //creating arrays A and B

		
		init_dense_array(A,m,n,sp_A+step); //initializing array A

		init_dense_array(B,n,p,sp_B+step); //initializing array B

		int **C = build_dense_array(m,p);	//creating array C

		auto start = high_resolution_clock::now(); //start clock timing

		for(int i=0;i<m;i++){ //dense array multiplication
	        for(int j=0;j<p;j++){
	            C[i][j] = 0;
	            for(int k=0;k<n; k++)
	                C[i][j] += A[i][k] * B[k][j];
	        }
	    }

	    auto stop = high_resolution_clock::now();  //end clock timing

	    auto duration = duration_cast<milliseconds>(stop - start);
	  	
	  	//storing value in a data file
	   	// filestream<<sp_A+step<<endl;
	    // filestream2<<duration.count()<<endl;

	}

	// filestream.close();
	// filestream2.close();
	

}