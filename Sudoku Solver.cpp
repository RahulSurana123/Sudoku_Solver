




/* 
    Developed by Rahul Surana
    
    ***********************************************************


	Here I am Going to use dfs solution to find a correct 

	Solution for a sudoku Puzzle with some given inputs and Stats

	Input Format:
	
	-> First input is N  which is No of sudoku inputs already given 
	
	-> Next N line would be x, y, k which are 
		xth row ( 1 <= x  <= 9) and 
		yth Column ( 1 <= y  <= 9) and 
		k No to be filled ( 1 <= k  <= 9) 



    ***********************************************************
*/











#include <bits/stdc++.h>
#define ll          long long
#define vl          vector<ll>
#define vi          vector<int>
#define pi          pair<int,int>
#define pl          pair<ll,ll>
#define all(a)      a.begin(),a.end()
#define mem(a,x)    memset(a,x,sizeof(a))
#define pb          push_back
#define mp          make_pair
#define F           first
#define S           second
#define FOR(i,a)     for(int i = 0; i < a; i++)
#define trace(x)    cerr<<#x<<" : "<<x<<endl;
#define trace2(x,y) cerr<<#x<<" : "<<x<<" | "<<#y<<" : "<<y<<endl;
#define trace3(x,y,z) cerr<<#x<<" : "<<x<<" | "<<#y<<" : "<<y<<" | "<<#z<<" : "<<z<<endl;
#define fast_io 	std::ios::sync_with_stdio(false),cin.tie(NULL),cout.tie(NULL)
 
using namespace std;

vector<vector<int>> sudoku(9,vector<int>(9,-1));
vector<set<pair<int,int>>> blocks(9,set<pair<int,int>>());
int ans = 0;


void init(){
	for(int i = 0; i < 9; i++){
		cout << "\t ___ ___ ___ ___ ___ ___ ___ ___ ___\n\t|";
		for(int j = 0; j < 9; j++){
			cout << ""<< i+1<<","<<j+1 <<"" << "|";
		}	
		cout<<"\n";
	}
	cout << "\t ___ ___ ___ ___ ___ ___ ___ ___ ___\n";
	for(int i = 0; i < 9; i++){
		for(int j = 0; j < 9; j++){
			if( i < 3 && j < 3) blocks[0].insert({i,j});
			else if( i < 3 && j >= 3 && j <= 5) blocks[1].insert({i,j});
			else if( i < 3 && j >5) blocks[2].insert({i,j});
			else if( i >= 3 && i<= 5 && j < 3) blocks[3].insert({i,j});
			else if( i >= 3 && i<= 5 && j >= 3 && j <= 5) blocks[4].insert({i,j});
			else if( i >= 3 && i<= 5 && j > 5) blocks[5].insert({i,j});
			else if( i > 5 && j < 3 ) blocks[6].insert({i,j});
			else if( i > 5 && j >= 3 && j <= 5) blocks[7].insert({i,j});
			else if( i > 5 && j > 5) blocks[8].insert({i,j});
		}	
	}
}

pair<int,int> getNext(){
	for(int i = 0 ; i < 9 ; i++){
		for(int j = 0 ; j < 9 ; j++){
			if(sudoku[i][j] == -1) {
				return {i,j};
			}
		} 
	}
	return {-1,-1};
}

void display(){

	for(int i = 0; i < sudoku.size(); i++){
		cout << "\t _ _ _ _ _ _ _ _ _\n\t|";
		for(int j = 0; j < sudoku.size(); j++){
			if(sudoku[i][j] == -1)
			cout << " |";
			else
			cout << sudoku[i][j] << "|";
		}	
		cout<<"\n";
	}
	cout << "\t _ _ _ _ _ _ _ _ _\n";
}

bool error(pair<int,int> pos, int num){
	// if(sudoku[pos.first][k])
	for(int k = 0; k < 9; k++){
		if(pos.second != k && sudoku[pos.first][k] == num) return false;
		if(pos.first != k && sudoku[k][pos.second] == num) return false;
	}
	if( pos.first < 3 && pos.second < 3) {
		for(auto x: blocks[0]){
			if(pos.first!=x.first && pos.second != x.second && num == sudoku[x.first][x.second]){
				return false;
			}
		}
	}
	else if( pos.first < 3 && pos.second >= 3 && pos.second <= 5) {
		for(auto x: blocks[1]){
			if( pos.first !=x.first && pos.second != x.second && num == sudoku[x.first][x.second]){
				return false;
			}
		}
	}
	else if( pos.first < 3 && pos.second >5) {
		for(auto x: blocks[2]){
			if( pos.first !=x.first && pos.second != x.second && num == sudoku[x.first][x.second]){
				return false;
			}
		}
	}
	else if( pos.first >= 3 && pos.first <= 5 && pos.second < 3) {
		for(auto x: blocks[3]){
			if(pos.first!=x.first && pos.second != x.second && num == sudoku[x.first][x.second]){
				return false;
			}
		}
	}
	else if( pos.first >= 3 && pos.first<= 5 && pos.second >= 3 && pos.second <= 5) {
		for(auto x: blocks[4]){
			if(pos.first!=x.first && pos.second != x.second && num == sudoku[x.first][x.second]){
				return false;
			}
		}
	}
	else if( pos.first >= 3 && pos.first<= 5 && pos.second > 5) {
		for(auto x: blocks[5]){
			if(pos.first!=x.first && pos.second != x.second && num == sudoku[x.first][x.second]){
				return false;
			}
		}
	}
	else if( pos.first > 5 && pos.second < 3 ) {
		for(auto x: blocks[6]){
			if(pos.first!=x.first && pos.second != x.second && num == sudoku[x.first][x.second]){
				return false;
			}
		}
	}
	else if( pos.first > 5 && pos.second >= 3 && pos.second <= 5) {
		for(auto x: blocks[7]){
			if(pos.first!=x.first && pos.second != x.second && num == sudoku[x.first][x.second]){
				return false;
			}
		}
	}
	else if( pos.first > 5 && pos.second > 5) {
		for(auto x: blocks[8]){
			if(pos.first!=x.first && pos.second != x.second && num == sudoku[x.first][x.second]){
				return false;
			}
		}
	}
	return true;
}


bool solve(){
	// if(ans < 50){
		
	// }
	ans++;
	auto u = getNext();
	if(u.first == -1 && u.second == -1) return true;
	for(int k = 1; k <= 9; k++){
		if(error(u,k)){

			sudoku[u.first][u.second] = k;
			// if(u.first == 0 && u.second == 0) display();
			if(solve()) {
				return true;
			}
			sudoku[u.first][u.second] = -1;
		}
	}
	sudoku[u.first][u.second] = -1;
	// cout << u.first <<" "<< u.second <<" Why is it not solveable\n";
	return false;
}





int main()
{
	// fast_io;
	init();
	
	int N;
	cin >> N;
	for(int i = 0; i < N; i++){
		int x,y,k;
		cin >> x >> y >> k;
		sudoku[x-1][y-1] = k;
	}
	display();
	getchar();
	cout << solve()<<" ";
	display();
	cout << ans <<" ";
}