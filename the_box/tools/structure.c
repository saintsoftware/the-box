/*
	Manage the structure of development  :
	
	Functionality :
	
	º Enviorment Object (used in: )
	º Gravity
	º Wind
	º Light
	º Files ()
	
	Inherit :
	
	- position
	- movement
	- textue
	- enviorment
	- framebuffer
	- Material
	- memory
	- color
	
	Notes:
*/

#include structure.h

#include<stdio.h>
#define MAX 100
 
void display(int matrix[MAX][MAX], int n);
int adj[MAX][MAX];
int n;
void create_graph();
 
int main()
{
	int i,j,k;
	int P[MAX][MAX];
 
	create_graph();
	printf("\nThe adjacency matrix is :\n");
	display(adj,n);
 
	for(i=0; i<n; i++)
	   for(j=0; j<n; j++)
		 P[i][j] = adj[i][j];
 
	for(k=0; k<n; k++)
	{
		for(i=0; i<n; i++)
		  for(j=0; j<n; j++)
		      P[i][j] = ( P[i][j] || ( P[i][k] && P[k][j] ) );
		printf("\nP%d is :\n",k);
		display(P,n);
	}
	printf("\nP%d is the path matrix of the given graph\n",k-1);
}/*End of main() */
 
void display(int matrix[MAX][MAX],int n)
{
	int i,j;
	for(i=0; i<n; i++)
	{
		for(j=0; j<n; j++)
			printf("%3d",matrix[i][j]);
		printf("\n");
	}
}/*End of display()*/
 
void create_graph()
{
	int i,max_edges,origin,destin;
 
	printf("\nEnter number of vertices : ");
	scanf("%d",&n);
 
	max_edges = n*(n-1);
 
	for( i=1; i<=max_edges; i++ )
	{
		printf("\nEnter edge %d( -1 -1 ) to quit : ",i);
		scanf("%d %d",&origin,&destin);
		if((origin == -1) && (destin == -1))
			break;
		if( origin >= n || destin >= n || origin<0 || destin<0)
		{
			printf("\nInvalid edge!\n");
			i--;
		}
		else
			adj[origin][destin] = 1;
	}/*End of for*/
}/*End of create_graph()*/
OUTPUT : :
C
/*  C Program to find Path Matrix by Warshall's Algorithm  */

Enter number of vertices : 4

Enter edge 1( -1 -1 ) to quit : 0 1

Enter edge 2( -1 -1 ) to quit : 0 2

Enter edge 3( -1 -1 ) to quit : 0 3

Enter edge 4( -1 -1 ) to quit : 1 3

Enter edge 5( -1 -1 ) to quit : 2 3

Enter edge 6( -1 -1 ) to quit : -1 -1

The adjacency matrix is :
  0  1  1  1
  0  0  0  1
  0  0  0  1
  0  0  0  0

P0 is :
  0  1  1  1
  0  0  0  1
  0  0  0  1
  0  0  0  0

P1 is :
  0  1  1  1
  0  0  0  1
  0  0  0  1
  0  0  0  0

P2 is :
  0  1  1  1
  0  0  0  1
  0  0  0  1
  0  0  0  0

P3 is :
  0  1  1  1
  0  0  0  1
  0  0  0  1
  0  0  0  0

P3 is the path matrix of the given graph

Process returned 0
1
2
3
4
5
6
7
8
9
10
11
12
13
14
15
16
17
18
19
20
21
22
23
24
25
26
27
28
29
30
31
32
33
34
35
36
37
38
39
40
41
42
43
44
45
46
47
48
49
/*  C Program to find Path Matrix by Warshall's Algorithm  */
 
Enter number of vertices : 4
 
Enter edge 1( -1 -1 ) to quit : 0 1
 
Enter edge 2( -1 -1 ) to quit : 0 2
 
Enter edge 3( -1 -1 ) to quit : 0 3
 
Enter edge 4( -1 -1 ) to quit : 1 3
 
Enter edge 5( -1 -1 ) to quit : 2 3
 
Enter edge 6( -1 -1 ) to quit : -1 -1
 
The adjacency matrix is :
  0  1  1  1
  0  0  0  1
  0  0  0  1
  0  0  0  0
 
P0 is :
  0  1  1  1
  0  0  0  1
  0  0  0  1
  0  0  0  0
 
P1 is :
  0  1  1  1
  0  0  0  1
  0  0  0  1
  0  0  0  0
 
P2 is :
  0  1  1  1
  0  0  0  1
  0  0  0  1
  0  0  0  0
 
P3 is :
  0  1  1  1
  0  0  0  1
  0  0  0  1
  0  0  0  0
 
P3 is the path matrix of the given graph
 
Process returned 0