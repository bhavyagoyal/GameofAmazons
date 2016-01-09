#include <vector>
#include <stdio.h>
#include <list>
#include <iostream>
#include <limits.h>
#include <string.h>
using namespace std;

#define FOR(i,n) for(int i=0;i<n;i++)
#define MOD 1000000009 
#define MAX(a,b) ( (a) > (b) ? (a) : (b))
#define MIN(a,b) ( (a) < (b) ? (a) : (b))
#define DEPTH 1

struct pos {
    int x;int y;
    pos(){};
    pos( int i, int r ) : x(i), y(r) {}
    bool operator==( const pos & d ) const {
       return ((x==d.x)&&(y==d.y));
    }
};


struct step{
	pos old_pos,new_pos,arrow;
	step(){};
	step(pos a, pos b, pos c) : old_pos(a) , new_pos(b) , arrow(c) {}
};

int DP[10][10];
pos queen[2][4];
step global_step;

int bfs(pos f, int startplay){
	int visited[10][10];
	memset(visited,0,100*sizeof(int));
	list< pair<pos, int> > q;
	FOR(i,4){
		q.push_back(make_pair(queen[startplay][i] , 0));
		visited[queen[startplay][i].x][queen[startplay][i].y]=1;
	}
	while(!q.empty()){
		pair< pos,int > a = q.front();
		q.pop_front();
		if(a.first==f){
			return a.second;
		}

		int j=1;
		while(j<10){
			if(((a.first.y+j)<10) && DP[a.first.x][a.first.y+j]==0){
				if(visited[a.first.x][a.first.y+j]==0){
					q.push_back(make_pair(pos(a.first.x,a.first.y+j) , a.second+1));
					visited[a.first.x][a.first.y+j]=1;
				}
			}
			else{break;}
			j++;
		}

		j=1;
		while(j<10){
			if(((a.first.y-j)>=0) && DP[a.first.x][a.first.y-j]==0){
				if(visited[a.first.x][a.first.y-j]==0){
					q.push_back(make_pair(pos(a.first.x,a.first.y-j) , a.second+1));
					visited[a.first.x][a.first.y-j]=1;
				}
			}
			else{break;}
			j++;
		}

		j=1;
		while(j<10){
			if(((a.first.x+j)<10) && DP[a.first.x+j][a.first.y]==0){
				if(visited[a.first.x+j][a.first.y]==0){
					q.push_back(make_pair(pos(a.first.x+j,a.first.y) , a.second+1));
					visited[a.first.x+j][a.first.y]=1;
				}
			}
			else{break;}
			j++;
		}

		j=1;
		while(j<10){
			if(((a.first.x-j)>=0) && DP[a.first.x-j][a.first.y]==0){
				if(visited[a.first.x-j][a.first.y]==0){
					q.push_back(make_pair(pos(a.first.x-j,a.first.y) , a.second+1));
					visited[a.first.x-j][a.first.y]=1;
				}
			}
			else{break;}
			j++;
		}


		j=1;
		while(j<10){
			if(((a.first.y-j)>=0) && ((a.first.x-j)>=0) && DP[a.first.x-j][a.first.y-j]==0){
				if(visited[a.first.x-j][a.first.y-j]==0){
					q.push_back(make_pair(pos(a.first.x-j,a.first.y-j) , a.second+1));
					visited[a.first.x-j][a.first.y-j]=1;
				}
			}
			else{break;}
			j++;
		}

		j=1;
		while(j<10){
			if(((a.first.y+j)<10) && ((a.first.x+j)<10) && DP[a.first.x+j][a.first.y+j]==0){
				if(visited[a.first.x+j][a.first.y+j]==0){
					q.push_back(make_pair(pos(a.first.x+j,a.first.y+j) , a.second+1));
					visited[a.first.x+j][a.first.y+j]=1;
				}
			}
			else{break;}
			j++;
		}

		j=1;
		while(j<10){
			if(((a.first.y+j)<10) && ((a.first.x-j)>=0) && DP[a.first.x-j][a.first.y+j]==0){
				if(visited[a.first.x-j][a.first.y+j]==0){
					q.push_back(make_pair(pos(a.first.x-j,a.first.y+j) , a.second+1));
					visited[a.first.x-j][a.first.y+j]=1;
				}
			}
			else{break;}
			j++;
		}

		j=1;
		while(j<10){
			if(((a.first.y-j)>=0) && ((a.first.x+j)<10) && DP[a.first.x+j][a.first.y-j]==0){
				if(visited[a.first.x+j][a.first.y-j]==0){
					q.push_back(make_pair(pos(a.first.x+j,a.first.y-j) , a.second+1));
					visited[a.first.x+j][a.first.y-j]=1;
				}
			}
			else{break;}
			j++;
		}
		// FOR(j,9){
		// 	if(DP[j][a.first.y]==0 && (visited[j][a.first.y]==0)){
		// 		q.push_back(make_pair(pos(j,a.first.y) , a.second+1));
		// 		visited[j][a.first.y]=1;
		// 	}

		// 	if((a.first.x+j)<10 && (a.first.y+j)<10 && DP[a.first.x+j][a.first.y+j]==0 && (visited[a.first.x+j][a.first.y+j]==0)){
		// 		q.push_back(make_pair(pos(a.first.x+j,a.first.y+j) , a.second+1));
		// 		visited[a.first.x+j][a.first.y+j]=1;
		// 	}

		// 	if((a.first.x+j)<10 && (a.first.y-j)>=0 && DP[a.first.x+j][a.first.y-j]==0 && (visited[a.first.x+j][a.first.y-j]==0)){
		// 		q.push_back(make_pair(pos(a.first.x+j,a.first.y-j) , a.second+1));
		// 		visited[a.first.x+j][a.first.y-j]=1;
		// 	}

		// 	if((a.first.x-j)>=0 && (a.first.y-j)>=0 && DP[a.first.x-j][a.first.y-j]==0 && (visited[a.first.x-j][a.first.y-j]==0)){
		// 		q.push_back(make_pair(pos(a.first.x-j,a.first.y-j) , a.second+1));
		// 		visited[a.first.x-j][a.first.y-j]=1;
		// 	}

		// 	if((a.first.x-j)>=0 && (a.first.y+j)<10 && DP[a.first.x-j][a.first.y+j]==0 && (visited[a.first.x-j][a.first.y+j]==0)){
		// 		q.push_back(make_pair(pos(a.first.x-j,a.first.y+j) , a.second+1));
		// 		visited[a.first.x-j][a.first.y+j]=1;
		// 	}
	}
	return -1;
}

int territory(){
	// cout<<"territory"<<endl;
	int count=0;
	FOR(i,10){
		FOR(j,10){
			// cerr<<i<<j<<"   ";
			if(DP[i][j] !=0){
				// cout<<" " <<0<<" ";
				continue;
			}
			int a1= bfs(pos(i,j), 0);
			int a2= bfs(pos(i,j), 1);
			if(a1==-1 && a2==-1){
				// cout<<" " <<0<<" ";
				continue;
			}
			if(a1>a2){
				count--;
				// cout<<""<<-1<<" ";
			}
			else if(a1<a2){
				count++;
				// cout<<" "<<1<<" ";
			}
			else{
				// cout<<" "<<0<<" ";
			}
		}
		cout<<endl;
	}
	return count;
}


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
	return count;
}

// int evaluator(){
// 	int ans = 0;
// 	ans = ans+mobility();

// }

std::vector<pos> max_limit(pos q){
	std::vector<pos> limits;
	pos p =  pos(q.x,q.y);
	if(q.x<9){
		while(p.x<9){
			if(DP[p.x+1][p.y]!=0)
				break;
			p.x++;
		}
		if(!(p==q)){
		limits.push_back(p);}
		if(q.y<9){
			p =  pos(q.x,q.y);
			while(p.x<9&&p.y<9){
				if(DP[p.x+1][p.y+1]!=0)
					break;
				p.x++;
				p.y++;
			}
		}
		if(!(p==q)){
		limits.push_back(p);}
		if(q.y>0){
			p =  pos(q.x,q.y);
			while(p.x<9&&p.y>0){
				if(DP[p.x+1][p.y-1]!=0)
					break;
				p.x++;
				p.y--;
			}
		}
		if(!(p==q)){
		limits.push_back(p);}
	}
	if(q.x>0){
		p =  pos(q.x,q.y);
		while(p.x>0){
			if(DP[p.x-1][p.y]!=0)
				break;
			p.x--;
		}
		if(!(p==q)){
		limits.push_back(p);}
		if(q.y<9){
			p =  pos(q.x,q.y);
			while(p.x>0&&p.y<9){
				if(DP[p.x-1][p.y+1]!=0)
					break;
				p.x--;
				p.y++;
			}
		}
		if(!(p==q)){
		limits.push_back(p);}
		if(q.y>0){
			p =  pos(q.x,q.y);
			while(p.x>0&&p.y>0){
				if(DP[p.x-1][p.y-1]!=0)
					break;
				p.x--;
				p.y--;
			}
		}
		if(!(p==q)){
		limits.push_back(p);}
	}
	if(q.y<9){
		p =  pos(q.x,q.y);
		while(p.y<9){
			if(DP[p.x][p.y+1]!=0)
				break;
			p.y++;
		}
		if(!(p==q)){
		limits.push_back(p);}
	}
	if(q.y>0){
		p =  pos(q.x,q.y);
		while(p.y>0){
			if(DP[p.x][p.y-1]!=0)
				break;
			p.y--;
		}
		if(!(p==q)){
		limits.push_back(p);}
	}
	return limits;
}


std::vector<step> list_step(int player){
	std::vector<step> valid;
	FOR(i,4){
		step mystep = step(queen[player-1][i],queen[player-1][i],queen[player-1][i]);
		int m = mystep.old_pos.x;
		int n = mystep.old_pos.y;
		std::vector<int> a;
		a.push_back(m);
		if(m<9){
			a.push_back(m+1);
		}
		if(m>0){
			a.push_back(m-1);
		}
		std::vector<int> b;
		b.push_back(n);
		if(n<9){
			b.push_back(n+1);
		}
		if(n>0){
			b.push_back(n-1);
		}
		FOR(k,a.size()){
			FOR(l,b.size()){
				mystep.new_pos.x = a[k];
				mystep.new_pos.y = b[l];
				if(((a[k]!=mystep.old_pos.x)||(b[l]!=mystep.old_pos.y))&&(DP[a[k]][b[l]]==0))
				{
					vector<pos> arrows = max_limit(mystep.new_pos);
					FOR(j,arrows.size()){
						mystep.arrow = arrows[j];
						valid.push_back(mystep);
					}
				}
			}
		}
	}
	return valid;
}

void implement_step(struct step m,int player)
{
	DP[m.old_pos.x][m.old_pos.y]=0;
	DP[m.new_pos.x][m.new_pos.y]=player;
	DP[m.arrow.x][m.arrow.y]=-1;
}

void unimplement_step(struct step m,int player)
{
	DP[m.old_pos.x][m.old_pos.y]=player;
	DP[m.new_pos.x][m.new_pos.y]=0;
	DP[m.arrow.x][m.arrow.y]=0;

}


double utility()
{
	return mobility()+territory();	
}

double minval(double,double,int,int);

double maxval(double alpha, double beta,int depth,int player)
{
	if(depth==0)
	{
		return utility();
	}
	else
	{
		vector<step> valid_steps=list_step(player);
		double curbest =-1;
		int s=valid_steps.size();
		int curbestind;
		for(int i=0;i<s;i++)
		{
			//cout << "I :"<< i << endl;
			implement_step(valid_steps[i],player);
			double val=minval(alpha,beta,depth-1,(player+1)%2+2*(player%2));
			if(val>curbest)
				curbestind=i;
			curbest=max(val,curbest);
			unimplement_step(valid_steps[i],player);
			alpha=max(alpha,val);
			if(alpha>beta)
			{
				global_step.old_pos=valid_steps[i].old_pos;
				global_step.new_pos=valid_steps[i].new_pos;
				global_step.arrow=valid_steps[i].arrow;
				return val;
			}
		}
		if(depth==DEPTH)
		{
			global_step.old_pos=valid_steps[curbestind].old_pos;
			global_step.new_pos=valid_steps[curbestind].new_pos;
			global_step.arrow=valid_steps[curbestind].arrow;
		}
		return curbest;
	}
}


double minval(double alpha, double beta, int depth,int player)
{
	if(depth==0)
		return utility();
	else
	{
		vector<step> valid_steps=list_step(player);
		double curbest=10000000;
		int s=valid_steps.size();
		int curbestind;
		for(int i=0;i<s;i++)
		{
			implement_step(valid_steps[i],player);
			double val=maxval(alpha,beta,depth-1,(player+1)%2+2*(player%2));
			if(curbest>val)
			{
				curbestind=i;
				curbest=val;

			}
			beta=min(beta,val);
			unimplement_step(valid_steps[i],player);
			if(alpha>beta)
			{
				global_step.old_pos=valid_steps[i].old_pos;
				global_step.new_pos=valid_steps[i].new_pos;
				global_step.arrow=valid_steps[i].arrow;
				return val;
			}
		}

		if(depth==DEPTH)
		{
			global_step.old_pos=valid_steps[curbestind].old_pos;
			global_step.new_pos=valid_steps[curbestind].new_pos;
			global_step.arrow=valid_steps[curbestind].arrow;
		}
		return curbest;

	}
}


void print_step(step a){
	cout<<a.old_pos.x<<" "<<a.old_pos.y<<"   " << a.new_pos.x<<" "<<a.new_pos.y<<"   "<<a.arrow.x<<" "<<a.arrow.y<<endl; 
}
void print_pos(pos a){
  cout<<a.x<<" "<<a.y<<endl;
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
	// FOR(j,4){
	// 	cout<<queen[0][j].x<<" "<<queen[0][j].y<<endl; 
	// 	cout<<queen[1][j].x<<" "<<queen[1][j].y<<endl; 
	// }
	// cout<<"Now"<<endl;
	scanf("%d",&player);
	// cout<<"Player"<<player<<endl;
	// cout<<territory()<<endl;
/*	vector<step> a = list_step(1);
	FOR(i,a.size()){
		print_step(a[i]);
	}
*/
	if(player==1)
		maxval(INT_MIN,INT_MAX,DEPTH,1);
	else
		minval(INT_MIN,INT_MAX,DEPTH,2);
	printf("%d %d\n",global_step.old_pos.x,global_step.old_pos.y);
	printf("%d %d\n",global_step.new_pos.x,global_step.new_pos.y);
	printf("%d %d\n",global_step.arrow.x,global_step.arrow.y);
	return 0;
}





