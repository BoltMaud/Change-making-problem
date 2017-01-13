#include <iostream>
#include <vector> 
#include <string>
#include <algorithm>    // std::count
#include <fstream>
#include <sstream>

using namespace std;

/*
	function min 
*/
int min(int a,int b){
	if(a<b){
		return a;
	}
	else return b;
}

/*
	complete a case of the tab
	tab : the completed tab
	s : the line, represente the sum
	i : the colone, represente the coins
	coinsList : represente the list of available coins
	result -> set the case (s;i) of the tab to the min needed number of coins
*/
void constructTab(int **tab, int s, int i,std::vector<int> coinsList){
	if(s==0 ){
		tab[s][i]=0;
	}
	else{
			//if line minus value of coin is ok and not on the first colone
			if(s-coinsList.at(i)>0 && i!=0){
				tab[s][i]=min(tab[s-coinsList.at(i)][i]+1, tab[s][i-1]);
			}
			else {
				//if line minus coin is ok
				if(s-coinsList.at(i)>0){
					tab[s][i]=tab[s-coinsList.at(i)][i]+1;
				}
				//if not in the first colone
				else{
					tab[s][i]=tab[s][i-1];
				}
			}
	}
}

/*
	this function complete all the cases of the tab
	see void constructTab(int **tab, int s, int i,std::vector<int> coinsList);
*/
void contructAllTab(int **tab, vector<int> listpiece,int s){
	for(int i=0;i<=s; i++){
		for(int unsigned j=0; j<listpiece.size();j++){
			constructTab(tab,i,j,listpiece);
		}
	}
}

/*
	start an empty tab
*/
int ** constructEmptyTab(int sum, int nbCoins){
	int **tab= new int*[sum];
	for(int i=0; i<sum+1; i++){
		tab[i]=new int[nbCoins-1];
	}
	return tab;
}

/*
	return the minimum of coins 
*/
int minTab(vector<int> coinsList, int sum, int **tab){
	contructAllTab(tab,coinsList,sum);
	return tab[sum][coinsList.size()-1];
}

/*
	get the list of coins
*/
void recCompleteListOfCoins(int s,int i, vector<int> & listOfUsedCoins, int **tab,vector<int> coinsList){
	if(i>0){
		//if same on the top
		if (tab[s][i]==tab[s][i-1]){
			recCompleteListOfCoins(s,i-1,listOfUsedCoins,tab,coinsList);
		}
		else{
			//if mod is possible
			if(s-coinsList.at(i)>=0){
				//add the coin
				listOfUsedCoins.push_back(coinsList.at(i));
				recCompleteListOfCoins(s-coinsList.at(i),i,listOfUsedCoins,tab,coinsList);
			}
		}
	}
	else{
			//if mod is possible
			if(s-coinsList.at(i)>=0){
				//add the coin
				listOfUsedCoins.push_back(coinsList.at(i));
				recCompleteListOfCoins(s-coinsList.at(i),i,listOfUsedCoins,tab,coinsList);
			}
	}
}

int main(int argc, char* argv[])
{

	if(argc>1){
		//find the file
		std::ifstream source;
		source.open( argv[1]);
		std::string line;


		//declare variables
		vector<int> v = {};
		int s;

		//read the test 
		while (std::getline(source, line)){
			cout << line <<endl;
			//note the coins
			if(line[0]=='p'){
				std::stringstream iss( line.substr(8,line.size()-2) );
				while ( iss.good() ){
					string number;
   					getline( iss, number, ',' );
  					v.push_back( std::stof(number) );
					 
				}
				
			}
			//note the sum
			if(line[0]=='s'){
				s=std::stof(line.substr(2,line.size()));
			}
		}

		//make the test
		//create the tab
		int **tab=constructEmptyTab(s,v.size());
		contructAllTab(tab,v,s);

		//get the min
		int min =minTab(v,s,tab);
		cout<<"nombre de pièces="<< min;
		
		vector<int> coinsList;
		//complete the coinsList
		recCompleteListOfCoins(s,v.size()-1, coinsList, tab,v);

		//for each coin
		cout << " résultat:"<<endl;
		for(int coin :v){
			int mycount = std::count (coinsList.begin(), coinsList.end(), coin);
			cout <<mycount<<" pièces de " << coin << endl;
		}

	}
	else{
		cout << "please see the README.txt"<< endl;
	}

	
  
}
