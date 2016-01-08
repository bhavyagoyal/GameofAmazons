#include <bits/stdc++.h>
using namespace std;


#define FOR(i,n) for(int i=0;i<n;i++)
#define MOD 1000000009 
#define MAX(a,b) ( (a) > (b) ? (a) : (b))
#define MIN(a,b) ( (a) < (b) ? (a) : (b))

int main(){
	int DP[10][10];
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

char list_move(int DP[10][10], int player){


}
