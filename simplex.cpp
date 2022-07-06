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
		int flag = 1, pivot;
		for(j=0; j<v; j++){
			// if coefficient of basic variable is zero
			if(tab[index][j] == 0)
				continue;
				
			int change;
			// if lower bound is violated, we need to increase basic variable
			cout<<"Inequality = "<<(ineqop==1?">=\n":"<=\n");
			if(ineqop == 1){
				change = (assignment[v+index]-lowerbound[v+index])/tab[index][j];
				// if basic variable has positive coeff, check upper bound
				if(tab[index][v] > 0 and change <= upperbound[index+v] ){
					pivot = j;
					flag = 0;
					break;
				}
				// if basic variable has negative coeff, check lower bound
				else if(tab[index][v] < 0 and change >= lowerbound[index+v] ){
					pivot = j;
					flag = 0;
					break;
				}
			}
			// if upper bound is violated, we need to reduce basic variable
			else if(ineqop == 2){
				change = (upperbound[v+index]-assignment[v+index])/tab[index][j];
				// if basic variable has positive coeff, check lower bound
				if(tab[index][v] > 0 and change >= lowerbound[index+v] ){
					pivot = j;
					flag = 0;
					break;
				}
				// if basic variable has negative coeff, check upper bound
				else if(tab[index][v] < 0 and change <= upperbound[index+v] ){
					pivot = j;
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
		
		// Perform pivot operation
		
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
