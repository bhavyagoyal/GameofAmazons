#include <bits/stdc++.h>
using namespace std;


#define FOR(i,n) for(int i=0;i<n;i++)
#define MOD 1000000009 
#define MAX(a,b) ( (a) > (b) ? (a) : (b))
#define MIN(a,b) ( (a) < (b) ? (a) : (b))

int DP[10][10];


int mobility(){
	int count=0;
	int sign=1;
	FOR(i,10){
		FOR(j,10){
			if(DP[i][j] == 1 ||  DP[i][j]==2){
				if(DP[i][j] == 2){
					sign = -1;
				}
				else{
					sign=1;
				}
				std::vector<int> a;
				a.push_back(i);
				if(i<9){
					a.push_back(i+1);
				}
				if(i>0){
					a.push_back(i-1);
				}
				std::vector<int> b;
				b.push_back(j);
				if(j<9){
					b.push_back(j+1);
				}
				if(j>0){
					b.push_back(j-1);
				}
				FOR(k,a.size()){
					FOR(l,b.size()){
						if(DP[a[k]][b[l]] == 0){
							count = count+sign;
						}
					}
				}
			}
		}
	}
}

int evaluator(){
	int ans = 0;
	ans = ans+mobility();
}

int main(){
	int player;
	FOR(i,10){
		FOR(j,10){
			scanf("%d",&DP[i][j]);
		}
	}
	scanf("%d",&player);



	return 0;
}

struct move{
	int old_x, old_y;
	int new_x, new_y;
	int arrowx, arrowy;
};

 std::vector<move> list_move(int DP[10][10], int player){
	std::vector<move> valid;
	FOR(i,4){
		move mymove = {queen};
a.push_back(mypoint);
	}
	return valid;
}
