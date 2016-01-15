#include <vector>
#include <stdio.h>
#include <cstdlib>
#include <list>
#include <iostream>
#include <limits.h>
#include <string.h>
#include <ctime>
#include <algorithm>
using namespace std;
#include <time.h>
#include <sys/time.h>
#define FOR(i,n) for(int i=0;i<n;i++)
#define MOD 1000000009 
#define MAX(a,b) ( (a) > (b) ? (a) : (b))
#define MIN(a,b) ( (a) < (b) ? (a) : (b))
int DEPTH=1;

struct pos {
				int x;int y;
				pos(){};
				pos( int i, int r ) : x(i), y(r) {}
				bool operator==( const pos & d ) const {
								return ((x==d.x)&&(y==d.y));
				}
};

pos arrow_steps[40];
int arrowstepscount=0;

struct step{
				pos old_pos,new_pos,arrow;
				step(){};
				step(pos a, pos b, pos c) : old_pos(a) , new_pos(b) , arrow(c) {}
};

int DP[10][10];
pos queen[2][4];
step global_step;
int arrows_cnt=0;
int ***territory1;
double begin_time;
int we=0;

double get_wall_time(){
				struct timeval time;
				if (gettimeofday(&time,NULL)){
								return 0;
				}
				return (double)time.tv_sec + (double)time.tv_usec * .000001;
}

void bfs(int startplay){
				int visited[10][10];
				memset(visited,0,100*sizeof(int));
				list< pair<pos, int> > q;
				FOR(i,4){
								q.push_back(make_pair(queen[startplay][i] , 0));
								visited[queen[startplay][i].x][queen[startplay][i].y]=1;
				}
				FOR(i,10){
								FOR(j,10){
												territory1[startplay][i][j] = INT_MAX;
								}
				}
				while(!q.empty()){
								pair< pos,int > a = q.front();
								q.pop_front();
								territory1[startplay][a.first.x][a.first.y] = a.second;
								// if(a.first==f){
								// 	return a.second;
								// }

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
				// FOR(i,10){
				// 	FOR(j,10){
				// 		cout<<territory1[startplay][i][j]<<" ";
				// 	}
				// 	cout<<endl;
				// }
				}

				double territory(int player){
								// cout<<"territory"<<endl;
								double count = 0.0;
								// FOR(i,10){
								// 	memset(done[i],0,10*sizeof(int));
								// }
								// FOR(i,10){
								// 	FOR(j,10){
								// if(done[i][j]){
								// 	continue;
								// }
								bfs(0);
								bfs(1);
								FOR(i,10){
												FOR(j,10){
																if(territory1[player-1][i][j]>territory1[2-player][i][j]){
																				if(territory1[player-1][i][j]==INT_MAX){
																								count = count - 5.0;
																				}
																				else{
																								count = count - (territory1[player-1][i][j])+(territory1[2-player][i][j]);
																				}
																				// cout<<" " <<2<<"   ";
																}
																else if(territory1[2-player][i][j]>territory1[player-1][i][j]){
																				if(territory1[2-player][i][j]==INT_MAX){
																								count = count + 3.0;
																				}
																				else{
																								count = count - (territory1[player-1][i][j])+(territory1[2-player][i][j]);
																				}
																				// cout<<" " <<1<<"   ";
																}
																else if(territory1[2-player][i][j] == territory1[player-1][i][j] && territory1[player-1][i][j]!=INT_MAX ){
																				count = count-0.5;
																				// cout<<" " <<0.2<<" ";
																}
																else{
																				// cout<<" " <<0<<"   ";
																}
												}
												// cout<<endl;
								}
								// cout << "exit terr"<< endl;
								return count;
				}


				double mobility(int player){
								// cerr<<"enter"<<endl;
								double count=0.0;
								double sign=1.0;
								// int player_order[2]={player,3-player};
								FOR(r,2){
												FOR(t,4){
																// cerr<<"enter"<<r<<" " <<t<<endl;
																int i=queen[r][t].x;
																int j=queen[r][t].y;
																if(r== (player-1)){
																				sign = 0.75;
																}
																else{
																				sign=-1.0;
																}
																std::vector<int> a;
																a.push_back(0);
																if(i<9){
																				a.push_back(1);
																}
																if(i>0){
																				a.push_back(-1);
																}
																std::vector<int> b;
																b.push_back(0);
																if(j<9){
																				b.push_back(1);
																}
																if(j>0){
																				b.push_back(-1);
																}
																// cout << "DP val "<< DP[i][j]<< " x "<< i << " y " << j << endl;
																FOR(k,a.size()){
																				FOR(l,b.size()){
																								int x=i+a[k],y=j+b[l];

																								while(x>=0 && x<=9 && y>=0 && y<=9 && DP[x][y]==0){
																												count = count+sign;
																												x+=a[k];
																												y+=b[l];
																								}
																				}
																}
												}
								}
								// cout << "exit mobility"<< endl;
								// cerr<<"exit"<<endl;
								// FOR(i,10){
								// 	FOR(j,10){
								// 		if(DP[i][j] == 1 ||  DP[i][j]==2){
								// 			if(DP[i][j] == 2){
								// 				sign = -1;
								// 			}
								// 			else{
								// 				sign=1.5;
								// 			}
								// 		}
								// 	}
								// }
								return count;
				}

				// int evaluator(){
				// 	int ans = 0;
				// 	ans = ans+mobility();

				// }
				void print_step(step a){
								cerr<<a.old_pos.x<<" "<<a.old_pos.y<<"   " << a.new_pos.x<<" "<<a.new_pos.y<<"   "<<a.arrow.x<<" "<<a.arrow.y<<endl; 
				}
				void print_pos(pos a){
								cerr<<a.x<<" "<<a.y<<endl;
				}

				void max_limit(pos q){
								arrowstepscount=0;
								int x,y;
								// std::vector<pos> limits;
								// pos p =  pos(q.x,q.y);
								//cerr<<p.x<<" "<<p.y<<"ADS"<<endl;
								int stepsize;	
								if(arrows_cnt<=30)
												stepsize=10;
								else
												stepsize=5;
								int a[3]={1,0,-1};
								FOR(k,3){
												FOR(l,3){
																for(int m=1;m<=stepsize;m++){
																				x = m*a[k]+q.x;
																				y = m*a[l]+q.y;
																				if(x<=9 && x>=0 && y<=9 && y>=0 && DP[x][y]==0){
																								arrow_steps[arrowstepscount].x =x;
																								arrow_steps[arrowstepscount].y =y;
																								arrowstepscount++;
																				}
																				else{break;}
																}
												}
								}
								return;
				}


				std::vector<step> list_step(int player){
								std::vector<step> valid;
								int stepsize;
								if(arrows_cnt<=30)
												stepsize = 10;
								else
												stepsize=7;
								int queenid=-1;
								int i = 3;
								/*	if(arrows_cnt<=8){
										queenid = (arrows_cnt/2)%4;
										i = queenid;
										}
								 */

								while(i>=queenid&&i!=-1){
												//cerr << "shiv"<< endl;
												step mystep = step(queen[player-1][i],queen[player-1][i],queen[player-1][i]);
												int m = mystep.old_pos.x;
												int n = mystep.old_pos.y;
												//cerr<<m<<" "<<n<<"ADS"<<endl;
												int a[3]={1,0,-1};

												FOR(k,3){
																FOR(l,3){
																				for(int p=1;p<=stepsize;p++){
																								mystep.new_pos.x = p*a[k]+m;
																								mystep.new_pos.y = p*a[l]+n;
																								if(mystep.new_pos.x<=9 && mystep.new_pos.x>=0 && mystep.new_pos.y<=9 && mystep.new_pos.y>=0 && DP[mystep.new_pos.x][mystep.new_pos.y]==0)
																								{	
																												DP[mystep.new_pos.x][mystep.new_pos.y] = player;
																												DP[mystep.old_pos.x][mystep.old_pos.y] = 0;
																												max_limit(mystep.new_pos);
																												DP[mystep.new_pos.x][mystep.new_pos.y] = 0;
																												DP[mystep.old_pos.x][mystep.old_pos.y] = player;
																												// cerr<<"SIZE:"<<arrows.size()<<endl;
																												FOR(j,arrowstepscount){
																																mystep.arrow = arrow_steps[j];
																																valid.push_back(mystep);
																												}
																								}
																								else
																												break;
																				}
																}
												}
												i--;
								}
								//cerr <<"RETURNING"<<endl;
								return valid;
				}

				void implement_step(struct step m,int player)
				{
								// cout << "implementing ";
								// print_step(m);
								DP[m.old_pos.x][m.old_pos.y]=0;
								DP[m.new_pos.x][m.new_pos.y]=player;
								DP[m.arrow.x][m.arrow.y]=-1;
								FOR(i,4){
												if(queen[player-1][i]==m.old_pos){
																queen[player-1][i] = m.new_pos;
																break;
												}
								}
				}

				void unimplement_step(struct step m,int player)
				{
								DP[m.arrow.x][m.arrow.y]=0;
								DP[m.old_pos.x][m.old_pos.y]=player;
								DP[m.new_pos.x][m.new_pos.y]=0;
								FOR(i,4){
												if(queen[player-1][i]==m.new_pos){
																queen[player-1][i] = m.old_pos;
																break;
												}
								}
								// cout << "unimplementing ";
								// print_step(m);
				}


				double utility()
				{
								// cout << "hehe"<< endl;
								if(arrows_cnt<=15)
												return 1.0*territory(we)+1.0*mobility(we);
								else if(arrows_cnt>16 && arrows_cnt<40)
												return 1.0*mobility(we)+2.0*territory(we);
								else
												return mobility(we)+3.0*territory(we);
				}

				vector<step> curbestmoves;

				double minval(double,double,int,int);

				bool comparator(const pair<double,step> &p, const pair<double,step> &q)
				{
								return p.first>q.first;
				}

				double maxval_vary(double alpha, double beta,int depth,int player)
				{
								if(depth==0)
								{
												return utility();
								}
								else
								{
												//cerr<<"sadwdewfew"<< endl;
												vector<step> valid_steps=list_step(player);
												//cerr <<"wdhwhceoihcfeor"<< endl;
												double curbest =INT_MIN;
												int s=valid_steps.size();
												int curbestind=0;
												vector< pair<double,step> > moves;
												for(int i=0;i<s;i++)
												{
																//ncerr << "eher"<< endl;
																implement_step(valid_steps[i],player);
																double val=minval(alpha,beta,depth-1,3-player);
																unimplement_step(valid_steps[i],player);
																moves.push_back(make_pair(val,valid_steps[i]));
												}
												sort(moves.begin(),moves.end(),comparator);
												DEPTH=2;
												depth=2;
												int len=MIN(moves.size(),50);
												for(int i=0;i<len;i++)
												{
																implement_step(moves[i].second,player);
																double val=minval(alpha,beta,depth-1,3-player);
																//cerr << curbest << " "<< val << endl;
																if(val>curbest && depth==DEPTH)
																{
																				curbestmoves.clear();
																				curbestmoves.push_back(moves[i].second);
																				//cout << "added"<< endl;
																}
																if(val==curbest && depth==DEPTH)
																{
																				curbestmoves.push_back(moves[i].second);
																}
																curbest=max(val,curbest);
																unimplement_step(moves[i].second,player);
																alpha=max(alpha,val);
																if(alpha>=beta && depth==DEPTH)
																{
																				int ind=rand()%curbestmoves.size();
																				global_step.old_pos=curbestmoves[ind].old_pos;
																				global_step.new_pos=curbestmoves[ind].new_pos;
																				global_step.arrow= curbestmoves[ind].arrow;
																				return val;
																}
																if(alpha>=beta)
																{
																				return val;
																}

												}
												if(depth==DEPTH)
												{
																int ind=rand()%curbestmoves.size();
																global_step.old_pos=curbestmoves[ind].old_pos;
																global_step.new_pos=curbestmoves[ind].new_pos;
																global_step.arrow= curbestmoves[ind].arrow;
												}
												return curbest;
								}
				}


				double maxval(double alpha, double beta,int depth,int player)
				{
								if(depth==0)
								{
												return utility();
								}
								else
								{
												vector<step> valid_steps=list_step(player);
												double curbest =INT_MIN;
												int s=valid_steps.size();
												//cout << "moves size " << s << endl;
												int curbestind=0;
												for(int i=0;i<s;i++)
												{
																//cerr << "I :"<< i << endl;
																if((get_wall_time()-begin_time)>0.9)
																				break;
																implement_step(valid_steps[i],player);
																double val=minval(alpha,beta,depth-1,3-player);
																//cout << curbest << " "<< val <<" move ";
																//print_step(valid_steps[i]);
																if(val>curbest && depth==DEPTH)
																{
																				curbestmoves.clear();
																				curbestmoves.push_back(valid_steps[i]);
																				//cout << "added"<< endl;
																}
																if(val==curbest && depth==DEPTH)
																{
																				curbestmoves.push_back(valid_steps[i]);
																}
																curbest=max(val,curbest);
																unimplement_step(valid_steps[i],player);
																alpha=max(alpha,val);
																if(alpha>=beta && depth==DEPTH)
																{
																				int ind=rand()%curbestmoves.size();
																				global_step.old_pos=curbestmoves[ind].old_pos;
																				global_step.new_pos=curbestmoves[ind].new_pos;
																				global_step.arrow= curbestmoves[ind].arrow;
																				return val;
																}
																if(alpha>=beta)
																{
																				return val;
																}
												}

												// cerr<<curbestind<<endl;
												// print_step(valid_steps[curbestind]);
												if(depth==DEPTH)
												{
																int ind=rand()%curbestmoves.size();
																global_step.old_pos=curbestmoves[ind].old_pos;
																global_step.new_pos=curbestmoves[ind].new_pos;
																global_step.arrow= curbestmoves[ind].arrow;
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
												double curbest=INT_MAX;
												int s=valid_steps.size();
												for(int i=0;i<s;i++)
												{
																implement_step(valid_steps[i],player);
																double val=maxval(alpha,beta,depth-1,3-player);
																if(curbest>val && depth==DEPTH)
																{
																				curbestmoves.clear();
																				curbestmoves.push_back(valid_steps[i]);
																}
																if(curbest==val && depth==DEPTH)
																{
																				curbestmoves.push_back(valid_steps[i]);
																}
																curbest=min(val,curbest);
																beta=min(beta,val);
																unimplement_step(valid_steps[i],player);
																if(alpha>=beta && depth==DEPTH)
																{
																				int ind=rand()%curbestmoves.size();
																				global_step.old_pos=curbestmoves[ind].old_pos;
																				global_step.new_pos=curbestmoves[ind].new_pos;
																				global_step.arrow=curbestmoves[ind].arrow;
																				return val;

																}
																if(alpha>=beta)
																{
																				return val;
																}
												}

												if(depth==DEPTH)
												{
																int ind=rand()%curbestmoves.size();
																global_step.old_pos=curbestmoves[ind].old_pos;
																global_step.new_pos=curbestmoves[ind].new_pos;
																global_step.arrow=curbestmoves[ind].arrow;
												}
												return curbest;

								}
				}



				int main(){
								begin_time=get_wall_time();
								srand(std::time(0));
								int player;
								int qcount1=0;
								int qcount2=0;
								territory1 = (int***)malloc(sizeof(int**)*2);
								FOR(i,2){
												territory1[i] = (int**)malloc(sizeof(int*)*10);
												FOR(j,10){
																territory1[i][j] = (int*)malloc(sizeof(int)*10);
												}
								}

								FOR(i,10){
												FOR(j,10){
																scanf("%d",&DP[i][j]);
																if(DP[i][j]==-1)
																				arrows_cnt++;
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
								we=player;

								if(arrows_cnt<=15)
								{
												DEPTH=1;
												maxval_vary(INT_MIN,INT_MAX,DEPTH,player);
								}
								else if(arrows_cnt>15 && arrows_cnt <45)
								{
												DEPTH=2;
												maxval(INT_MIN,INT_MAX,DEPTH,player);
								}

								else
								{
												DEPTH=3;
												maxval(INT_MIN,INT_MAX,DEPTH,player);
								}
								// FOR(j,4){
								// 	cout<<queen[0][j].x<<" "<<queen[0][j].y<<endl; 
								// 	cout<<queen[1][j].x<<" "<<queen[1][j].y<<endl; 
								// }
								// cout<<"Now"<<endl;
								// cout<<"Player"<<player<<endl;
								// cout<<territory(player)<<endl;
								// vector<step> a = list_step(1);
								// FOR(i,a.size()){
								// 	print_ste`p(a[i]);
								// }
								// cerr<<"ADSADS"<<endl;
								//	if(player==1)
								//		maxval(INT_MIN,INT_MAX,DEPTH,1);
								//	else
								printf("%d %d\n",global_step.old_pos.x,global_step.old_pos.y);
								printf("%d %d\n",global_step.new_pos.x,global_step.new_pos.y);
								printf("%d %d\n",global_step.arrow.x,global_step.arrow.y);
								printf("%d %d\n",1,4);
								return 0;
				}

