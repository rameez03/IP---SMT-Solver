#include<bits/stdc++.h>
using namespace std;

int main(){
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
	cout<<"\nThe enteres inequalities are:\n";
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
	
	return 0;
}
