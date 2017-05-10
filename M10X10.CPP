#include<iostream.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
class mine{
	char val[3];
	int m;
	int mcount;
	int sel;
	int flagged;
	public:
	void ini(){
		val[0]=' ';
		val[1]='x';
		val[2]=' ';
		sel=0;
		m=0;
		flagged=0;
		mcount=0;
	}
	void print(){
		cout<<val[0]<<val[1]<<val[2];
	}
	void select(){
		sel=1;
		val[0]='[';
		val[2]=']';
	}
	void unselect(){
		sel=0;
		val[0]=' ';
		val[2]=' ';
	}
	int ismine(){
		return m;
	}
	void makemine(){
		m=1;
	}
	void setmcount(int a){
		mcount=a;
	}
	int getmcount(){
		return mcount;
	}
	void setval(char v){
		val[1]=v;
		flagged=0;
	}
	char getval(){
		return val[1];
	}
	void setf(){
		val[1]='F';
		flagged=1;
	}
	void unsetf(){
		val[1]='x';
		flagged=0;
	}
	int getf(){
		return flagged;
	}
};
// Initialising all Game Board Variables
void in(mine a[10][10]){
	for(int i=0;i<10;i++){
		for(int j=0;j<10;j++){
			a[i][j].ini();
		}
	}
}
// Game Board Display Function
void disp(mine a[10][10],int c,int f,int mines){
	clrscr();
	cout<<endl<<endl<<endl;
	for(int i=0;i<10;i++){
		for(int j=0;j<10;j++){
			a[i][j].print();
		}
		cout<<endl;
	}
	cout<<"Flags Left = "<<mines-f<<endl;
	if(c){
		cout<<endl;
		cout<<"Cheat mode on"<<endl;
		for(int k=0;k<10;k++){
			for(int l=0;l<10;l++){
				cout<<" "<<a[k][l].getmcount()<<" ";
			}
			cout<<endl;
		}
	}
}
void fillup(mine a[10][10],int mno){
	// Generating Mines
	int eno=0;
	int i=0,j=0;
	int mines=0;
	int count=0;
	int e[100][2];
	int r;
	while(mines<mno){
		eno=0;
		for(i=0;i<10;i++){
			for(j=0;j<10;j++){
				if(!a[i][j].ismine()){
					e[eno][0]=i;
					e[eno][1]=j;
					eno++;
				}
			}
		}
		r=random(eno);
		cout<<mines<<"  "<<e[r][0]<<" "<<e[r][1]<<endl;
		a[e[r][0]][e[r][1]].makemine();
		mines++;
	}
	// Generating Values for non mine places
	for(i=0;i<10;i++){
		for(j=0;j<10;j++){
			count=0;
			if(!a[i][j].ismine()){
				if(i!=0){
					count+=a[i-1][j].ismine();
				}
				if(i!=9){
					count+=a[i+1][j].ismine();
				}
				if(j!=0){
					count+=a[i][j-1].ismine();
				}
				if(j!=9){
					count+=a[i][j+1].ismine();
				}
				if(i!=0&&j!=0){
					count+=a[i-1][j-1].ismine();
				}
				if(i!=0&&j!=9){
					count+=a[i-1][j+1].ismine();
				}
				if(i!=9&&j!=0){
					count+=a[i+1][j-1].ismine();
				}
				if(i!=9&&j!=9){
					count+=a[i+1][j+1].ismine();
				}
			}
			else{
				count=9;
			}
			a[i][j].setmcount(count);
		}
	}

}
void open(mine a[10][10],int l0,int l1){
	if(a[l0][l1].getval()=='x'){
		a[l0][l1].setval(a[l0][l1].getmcount()+48);
		if(a[l0][l1].getmcount()==0){
			if(l0!=0){
				open(a,l0-1,l1);
			}
			if(l0!=9){
				open(a,l0+1,l1);
			}
			if(l1!=0){
				open(a,l0,l1-1);
			}
			if(l1!=9){
				open(a,l0,l1+1);
			}
		}
	}
}
int checkwin(mine a[10][10]){
	int left=100;
	for(int i=0;i<10;i++){
		for(int j=0;j<10;j++){
			if(a[i][j].getval()!='x'){
				left--;
			}
		}
	}
	if(left==0){
		return 1;
	}
	else{
		return 0;
	}
}
void main(){
	clrscr();
	// Declarations and Initializations
	randomize();
	mine g[10][10];
	int mines=4;
	int win=0;
	int f=0;
	int cur[2]={0,0};
	int c=0;
	char inp='0';
	in(g);
	fillup(g,mines);
	g[0][0].select();
	// Game Loop
	while(1){
		//Display
		disp(g,c,f,mines);
		win=checkwin(g);
		if(win==1){
			cout<<"Congrats You won"<<endl;
			getch();
			break;
		}
		//Get inpupt
		inp=getch();
		// Game loop condition set
		if(inp=='q'){
			break;
		}
		else if(inp=='w'&&cur[0]!=0){
			g[cur[0]][cur[1]].unselect();
			cur[0]--;
			g[cur[0]][cur[1]].select();
		}
		else if(inp=='s'&&cur[0]!=9){
			g[cur[0]][cur[1]].unselect();
			cur[0]++;
			g[cur[0]][cur[1]].select();
		}
		else if(inp=='a'&&cur[1]!=0){
			g[cur[0]][cur[1]].unselect();
			cur[1]--;
			g[cur[0]][cur[1]].select();
		}
		else if(inp=='d'&&cur[1]!=9){
			g[cur[0]][cur[1]].unselect();
			cur[1]++;
			g[cur[0]][cur[1]].select();
		}
		else if(inp=='c'){
			if(!c){
				c=1;
			}
			else{
				c=0;
			}
		}
		else if(inp==' '){
			if(g[cur[0]][cur[1]].ismine()){
				g[cur[0]][cur[1]].setval('*');
				disp(g,c,f,mines);
				cout<<"You Lose"<<endl;
				getch();
				break;
			}
			else{
				open(g,cur[0],cur[1]);
			}
		}
		else if(inp=='f'){
			if(g[cur[0]][cur[1]].getf()){
				g[cur[0]][cur[1]].unsetf();
				f--;
			}
			else if(f<mines){
				g[cur[0]][cur[1]].setf();
				f++;
			}
			else{
				cout<<"No flags left unflag a position to use a flag "<<endl;
				getch();
			}
		}
	}
}