#include <bits/stdc++.h>
using namespace std;


#define FOR(i,n) for(int i=0;i<n;i++)
#define MOD 1000000009 
#define MAX(a,b) ( (a) > (b) ? (a) : (b))
#define MIN(a,b) ( (a) < (b) ? (a) : (b))



struct pos {
    int x;int y;
    pos(){};
    pos( int i, int r ) : x(i), y(r) {}
    bool operator=( const myclass & d ) const {
       return ((x==d.x)&&(y==d.y));
    }
};

int DP[10][10];
pos queen[2][4];


// int bfs()

// int territory(){

// 	FOR(i,10){
// 		FOR(j,10){
// 			if(DP[i][j] !=0){
// 				continue;
// 			}

// 		}
// 	}
// }


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
	int qcount1=0;
	int qcount2=0;
	FOR(i,10){
		FOR(j,10){
			scanf("%d",&DP[i][j]);
			if(DP[i][j]==1){
				queen[0][qcount1].x=i;
				queen[0][qcount1].y=j;
				qcount1++;
			}
			if(DP[i][j]==2){
				queen[1][qcount2].x=i;
				queen[1][qcount2].y=j;
				qcount2++;
			}
		}
	}
	scanf("%d",&player);

	return 0;
}

struct move{
	pos old_pos, new_pos, arrow;
};

std::vector<pos> max_limit(pos q){
	std::vector<pos> limits;
	pos p = {q.x,q.y};
	if(q.x<9){
		while(p.x<9){
			if(DP[p.x][p.y]!=0)
				break;
			p.x++;
		}
		limits.push_back(p);
		if(q.y<9){
			p = {q.x,q.y};
			while(p.x<9&&p.y<9){
				if(DP[p.x][p.y]!=0)
					break;
				p.x++;
				p.y++;
			}
		}
		limits.push_back(p);
		if(q.y>0){
			p = {q.x,q.y};
			while(p.x<9&&p.y>0){
				if(DP[p.x][p.y]!=0)
					break;
				p.x++;
				p.y--;
			}
		}
		limits.push_back(p);
	}
	if(q.x>0){
		while(p.x>0){
			if(DP[p.x][p.y]!=0)
				break;
			p.x--;
		}
		limits.push_back(p);
		if(q.y<9){
			p = {q.x,q.y};
			while(p.x>0&&p.y<9){
				if(DP[p.x][p.y]!=0)
					break;
				p.x--;
				p.y++;
			}
		}
		limits.push_back(p);
		if(q.y>0){
			p = {q.x,q.y};
			while(p.x>0&&p.y>0){
				if(DP[p.x][p.y]!=0)
					break;
				p.x--;
				p.y--;
			}
		}
		limits.push_back(p);
	}
	if(q.y<9){
		p = {q.x,q.y};
		while(p.y<9){
			if(DP[p.x][p.y]!=0)
				break;
			p.y++;
		}
		limits.push_back(p);
	}
	if(q.y>0){
		p = {q.x,q.y};
		while(p.y>0){
			if(DP[p.x][p.y]!=0)
				break;
			p.y--;
		}
		limits.push_back(p);
	}
	return limits;
}


std::vector<move> list_move(int player){
	std::vector<move> valid;
	FOR(i,4){
		move mymove = {queen[player][i],queen[player][i],queen[player][i]};
		//R
		if(mymove.old_pos.x<9 && (DP[mymove.old_pos.x+1][mymove.old_pos.y]==0)){
			mymove.new_pos.x = mymove.old_pos.x + 1;
			pos arrows = max_limit(mymove.new_pos);
			FOR(j,arrows.size()){
				mymove.arrow = arrow[j];
				valid.push_back(mymove);
			}
		}
		//L
		if(mymove.old_pos.x>0 && (DP[mymove.old_pos.x-1][mymove.old_pos.y]==0)){
			mymove.new_pos.x = mymove.old_pos.x - 1;
			pos arrows = max_limit(mymove.new_pos);
			FOR(j,arrows.size()){
				mymove.arrow = arrow[j];
				valid.push_back(mymove);
			}
		}
		//T
		if(mymove.old_pos.y<9 && (DP[mymove.old_pos.x][mymove.old_pos.y+1]==0)){
			mymove.new_pos.y = mymove.old_pos.y + 1;
			pos arrows = max_limit(mymove.new_pos);
			FOR(j,arrows.size()){
				mymove.arrow = arrow[j];
				valid.push_back(mymove);
			}
		}
		//B
		if(mymove.old_pos.y>0 && (DP[mymove.old_pos.x][mymove.old_pos.y-1]==0)){
			mymove.new_pos.y = mymove.old_pos.y - 1;
			pos arrows = max_limit(mymove.new_pos);
			FOR(j,arrows.size()){
				mymove.arrow = arrow[j];
				valid.push_back(mymove);
			}
		}
		//TR
		if(mymove.old_pos.x<9 && mymove.old_pos.y<9 && (DP[mymove.old_pos.x+1][mymove.old_pos.y+1]==0)){
			mymove.new_pos.x = mymove.old_pos.x + 1;
			mymove.new_pos.y = mymove.old_pos.y + 1;
			pos arrows = max_limit(mymove.new_pos);
			FOR(j,arrows.size()){
				mymove.arrow = arrow[j];
				valid.push_back(mymove);
			}
		}
		//TL
		if(mymove.old_pos.x>0 && mymove.old_pos.y<9 && (DP[mymove.old_pos.x-1][mymove.old_pos.y+1]==0)){
			mymove.new_pos.x = mymove.old_pos.x - 1;
			mymove.new_pos.y = mymove.old_pos.y + 1;
			pos arrows = max_limit(mymove.new_pos);
			FOR(j,arrows.size()){
				mymove.arrow = arrow[j];
				valid.push_back(mymove);
			}
		}
		//BR
		if(mymove.old_pos.x<9 && mymove.old_pos.y>0 && (DP[mymove.old_pos.x+1][mymove.old_pos.y-1]==0)){
			mymove.new_pos.x = mymove.old_pos.x + 1;
			mymove.new_pos.y = mymove.old_pos.y - 1;
			pos arrows = max_limit(mymove.new_pos);
			FOR(j,arrows.size()){
				mymove.arrow = arrow[j];
				valid.push_back(mymove);
			}
		}
		//BL
		if(mymove.old_pos.x>0 && mymove.old_pos.y>0 && (DP[mymove.old_pos.x-1][mymove.old_pos.y-1]==0)){
			mymove.new_pos.x = mymove.old_pos.x - 1;
			mymove.new_pos.y = mymove.old_pos.y - 1;
			pos arrows = max_limit(mymove.new_pos);
			FOR(j,arrows.size()){
				mymove.arrow = arrow[j];
				valid.push_back(mymove);
			}
		}
	}
	return valid;
}

