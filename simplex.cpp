#include<bits/stdc++.h>
#include<limits.h>
using namespace std;

void simplex(vector<string> vars, vector<vector<int>> tab, int n, int v){

	vector<int> assignment((n+v), 0);
	vector<int> lowerbound((n+v), INT_MIN);
	vector<int> upperbound((n+v), INT_MAX);
	
	// bounds of basic variables
	for(int i=v; i<v+n; i++){
		if(tab[i-v][v] == 1)
			lowerbound[i] = tab[i-v][v+1];
		else if(tab[i-v][v] == 2)
			upperbound[i] = tab[i-v][v+1];
	}
	
	int j=0;
	while(j<1){
		int index = -1, ineqop;
		for(int i=0; i<n; i++){
			int j;
			for(j=0; j<v; j++){
				assignment[v+i] += assignment[j]*tab[i][j];
			}
			ineqop = tab[i][j];
			if((tab[i][j] == 1) and (assignment[v+i] < tab[i][j+1])){
				index = i;
				break;
			}
			else if((tab[i][j] == 2) and (assignment[v+i] > tab[i][j+1])){
				index = i;
				break;
			}
		}
		if (index == -1){
			cout<<"Satisfiable\n";
			cout<<"Satisfying assignment is:\n";
			for(j=0; j<v; j++){
				cout<<"\t"<<vars[j]<<" = "<<assignment[j]<<", ";
			}
			cout<<"\n";
			return;
		}
		else
			cout<<"Basic variable "<<(index+1)<<" violated\n";
			
		// finding pivot element
		cout<<"Finding pivot element\n";
		int flag = 1, pivot, change;
		for(int i=0; i<v; i++){
			// if coefficient of non-basic variable is zero
			if(tab[index][i] == 0)
				continue;
			
			// if lower bound is violated, we need to increase basic variable
			if(ineqop == 1){
				change = (assignment[v+index]-lowerbound[v+index])/tab[index][i];
				// if non-basic variable has positive coeff, check upper bound
				if(tab[index][v] > 0 and assignment[i]+change <= upperbound[index+v] ){
					pivot = i;
					flag = 0;
					break;
				}
				// if non-basic variable has negative coeff, check lower bound
				else if(tab[index][v] < 0 and assignment[i]-change >= lowerbound[index+v] ){
					pivot = i;
					flag = 0;
					break;
				}
			}
			// if upper bound is violated, we need to reduce basic variable
			else if(ineqop == 2){
				change = (upperbound[v+index]-assignment[v+index])/tab[index][i];
				// if non-basic variable has positive coeff, check lower bound
				if(tab[index][v] > 0 and assignment[i]-change >= lowerbound[index+v] ){
					pivot = i;
					flag = 0;
					break;
				}
				// if non-basic variable has negative coeff, check upper bound
				else if(tab[index][v] < 0 and assignment[i]+change <= upperbound[index+v] ){
					pivot = i;
					flag = 0;
					break;
				}
			}
		}
		if(flag == 1){
			cout<<"The system of inequalities is unsatisfiable\n";
			return;
		}
		else{
			cout<<"Pivot is "<<vars[pivot]<<"\n";
		}
		
		// Perform pivot operation - incomplete
		cout<<"Pivot operation is still incomplete\n";
		
		// if lower bound is violated
		if(ineqop == 1){
			// adjust pivot
			if(tab[index][v] > 0){
				assignment[pivot] += change;
			}
			else if(tab[index][v] < 0){
				assignment[pivot] -= change;
			}
			
			// adjust basic variable
			assignment[index] = lowerbound[index];
		}
		
		// if upper bound is violated
		else if(ineqop == 2){
			// adjust pivot
			if(tab[index][v] > 0){
				assignment[pivot] -= change;
			}
			else if(tab[index][v] < 0){
				assignment[pivot] += change;
			}
			
			// adjust basic variable
			assignment[index] = upperbound[index];
			
		}
		
		// modify tableau
		int pivot_coeff = tab[index][pivot];
		
		// modify violated row
		for(int i=0; i<v; i++){
			if(i == pivot)
				tab[index][i] = 1/pivot_coeff;
			else
				tab[index][i] *= -1/pivot_coeff;
		}
		
		// modify remaining rows
		for(int i=0; i<n; i++){
			if(i == index)
				continue;
			for(int k=0; k<v; k++){
				if(k == pivot)
					continue;
				else{
					tab[i][k] += tab[i][pivot] * tab[index][k];
				}
			}
			tab[i][pivot] *= 1/pivot_coeff;
		}
		
		// swap assignment rows
		swap(assignment[index], assignment[pivot]);
		swap(lowerbound[index], lowerbound[pivot]);
		swap(upperbound[index], upperbound[pivot]);
		
		// redo asssignments
		for(int i=0; i<n; i++){
			assignment[v+i] = 0;
			for(int j=0; j<v; j++){
				assignment[v+i] += assignment[j]*tab[i][j]; 
			}
		}
		
		j++;
	}
}

int main(){

	// Input inequalities from user
	int n, v;
	cout<<"Enter the number of inequalities: ";
	cin>>n;
	cout<<"Enter the number of variables: ";
	cin>>v;
	vector<string> vars(v);
	cout<<"\nEnter variable names:\n";
	for(int j=0; j<v; j++){
		cout<<"variable "<<(j+1)<<": ";
		cin>>vars[j];
	}
	vector<vector<int>> tab(n, vector<int>(v+2));
	for(int i=0; i<n; i++){
		cout<<"\nEnter coefficients of variables in inequality "<<(i+1)<<"\n";
		int j;
		for(j=0; j<v; j++){
			cout<<vars[j]<<": ";
			cin>>tab[i][j];
		}
		int op;
		cout<<"Choose inequality symbol: 1) >=   2)<=  : ";
		cin>>tab[i][j++];
		cout<<"Constant: ";
		cin>>tab[i][j];
	}
	cout<<"\nThe entered inequalities are:\n";
	for(int i=0; i<n; i++){
		cout<<"\t";
		int j;
		for(j=0; j<v; j++){
			if(tab[i][j] >= 0)
				cout<<"+"<<tab[i][j]<<vars[j]<<" ";
			else
				cout<<tab[i][j]<<vars[j]<<" ";
		}
		if(tab[i][j++] == 1)
			cout<<" >= "<<tab[i][j]<<"\n";
		else
			cout<<" <= "<<tab[i][j]<<"\n";
	}
	
	// Cal to simplex algorithm
	simplex(vars, tab, n, v);
	
	return 0;
}
