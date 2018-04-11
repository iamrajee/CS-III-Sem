#include<stdio.h>
void move(int ,int ,int ,int );
int main(){
	int n;
	printf("Total no. disc :");
	scanf("%d", &n);
	move(n,1,2,3);
}

void move(int n,int p1,int p2,int p3){
	if(n ==1){
		printf("move top disc from pole(%d -->%d)\n", p1,p3);
	}
	else{
		move(n-1,p1,p3,p2);
		move(1,p1,p2,p3);
		move(n-1,p2,p1,p3);

	}
}
