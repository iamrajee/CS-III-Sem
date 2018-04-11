#include<stdio.h>
int main(){
	int n, m,i,j,k,temp;
	printf("Enter the order of the matrix\n");
	scanf("%d%d", &n , &m);
	int a[n][m], b[n*m][2];
	printf("Enter the element of the the matrix\n");
	for(i=0; i<n; i++){
		for(j=0; j<m; j++){
			printf("a[%d][%d] = ", i, j);
			scanf("%d", &a[i][j]);		
		}	
	
	}
	
	k = 0;
	for(i=0; i<n; i++){
		for(j=0; j<m; j++){
			if(a[i][j] == 0){
				b[k][1] = i;
				b[k][2] = j;
				printf("%d, %d\n",b[k][1], b[k][2]);
				k++;
				
			}	
		}
	}
	for(i=0; i<k; i++){
		for(j=0; j<n; j++){
			a[j][b[i][2]] = 0;
		}

		for(j=0; j<m; j++){
			a[b[i][1]][j] = 0;
		}
	}

	printf("\n\n");
	for(i=0; i<n; i++){
		for(j=0; j<m; j++){
			printf("%d\t", a[i][j] );		
		}
		printf("\n");
	}
	
}
