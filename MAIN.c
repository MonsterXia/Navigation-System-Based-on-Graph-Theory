#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DIJKSTRA_H
#define X 65535
#define Max 16
#define Nopath -1

typedef struct node 
{
	int path;
	int visited;
	int distance;
	char name;
}Node;
typedef Node* TABLE;

typedef struct PriorityQueue 
{
	int size;
	int capacity;
	TABLE element[Max];
}Queue;
typedef Queue * QUEUE;


void InitializeTable(int start,TABLE T[])	
{
	int i;
	for(i=0;i<Max;i++)
	{
		T[i]=malloc(sizeof(Node));
		T[i]->visited=0;
		T[i]->path=Nopath;
		T[i]->distance=X;
		T[i]->name=i+65;
	}
	T[start]->distance=0;
	
}

QUEUE InitializeQueue(int capacity)
{
	QUEUE Q;
	Q=malloc(sizeof(Queue));
	Q->capacity=capacity;
	Q->size=0;
	
	for(int i=1;i<Max;i++)
	{
		Q->element[i]=NULL;
	}
	Q->element[0]=malloc(sizeof(Node));
	Q->element[0]->distance=0;
	
	return Q;
	
}

void enqueue(QUEUE Q, TABLE K)
{
	int i,hole;
	
	if(K->path==Nopath)
	{
		Q->size++;
		hole=Q->size;
	}
	else
	{
		i=1;
		while(K->name != Q->element[i]->name && Q->element[i]!=NULL)
		{
			i++;
		} 
		hole=i;	
	}
	i=hole/2;
	
	while(K->distance < Q->element[i]->distance)
	{
		Q->element[hole]=Q->element[i];
		hole=i;
		i=i/2;
	}
	Q->element[hole]=K;
}

int dequeue(QUEUE Q)
{	TABLE OUT;
	int hole=1,child=2,last=Q->size;
	OUT=Q->element[1];
	Q->size--;
	while(child <= Q->size && Q->element[child]->distance < Q->element[last]->distance  )
	{	
		
		if(Q->element[child]->distance > Q->element[child+1]->distance )	
			child++;			
		Q->element[hole]=Q->element[child];
		hole=child;
		child=hole*2;	
	}
	
	Q->element[hole]=Q->element[last];
	Q->element[last]=NULL;
	
	return OUT->name-65;
	
}

void Dijkstra(int const(*map)[Max],int start,TABLE T[])
{
	 
	int current;
	InitializeTable(start,T);
	QUEUE Q;
	Q=InitializeQueue(Max);
	enqueue(Q,T[start]);
	while(Q->size!=0)
	{
		current=dequeue(Q);
	
		for(int i=0;i<Max;i++)
		{
			int EdgeLength = map[current][i];
			
			if(EdgeLength!=0 && EdgeLength!=X && T[i]->visited==0)
			{
				if(T[i]->distance > EdgeLength + T[current]->distance);
				{
					T[i]->distance = EdgeLength + T[current]->distance;
					enqueue(Q,T[i]);
					T[i]->path=current;
				}	
			}
		}
		T[current]->visited=1;
	}
}


void ShowTable(TABLE T[])
{
	int i;
	char code[16]={'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'J', 'K', 'L', 'M', 'N', 'P', 'Q', 'R'};
	printf("des \tdis \tpath\n");
	for(i=0;i<Max;i++)
	{
		if(T[i]->path == -1)
		{
			printf("%c:	\t%d   \t@\n",code[T[i]->name-65],T[i]->distance);
		}else{
			printf("%c:	\t%d   \t%c\n",code[T[i]->name-65],T[i]->distance,code[T[i]->path]);
		}
	}
}



const int map[16][16]={
//		 A		B		C		D		E		F		G		H		J		K		L		M		N		P		Q		R	
/*A*/	{0,		X,		83,		X,		X,		X,		X,		X,		49,		X,		X,		109,	109,	102,	X,		X},
/*B*/	{X,		0,		X,		X,		X,		179,	128,	X,		X,		220,	102,	X,		X,		X,		X,		X},
/*C*/	{83,	X,		0,		X,		X,		X,		111,	X,		108,	X,		199,	63,		X,		X,		186,	X},
/*D*/	{X,		X,		X,		0,		X,		X,		X,		92,		X,		X,		X,		X,		X,		X,		95,		168},
/*E*/	{X,		X,		X,		X,		0,		242,	89,		X,		X,		X,		X,		61,		X,		X,		X,		X},
/*F*/	{X,		179,	X,		X,		242,	0,		217,	X,		X,		60,		X,		X,		X,		X,		X,		X},
/*G*/	{X,		128,	111,	X,		89,		217,	0,		X,		X,		X,		143,	X,		X,		X,		X,		X},
/*H*/	{X,		X,		X,		92,		X,		X,		X,		0,		95,		X,		X,		X,		X,		124,	159,	98},
/*J*/	{49,	X,		108,	X,		X,		X,		X,		95,		0,		X,		X,		X,		X,		X,		162,	X},
/*K*/	{X,		220,	X,		X,		X,		60,		X,		X,		X,		0,		X,		X,		X,		X,		X,		X},
/*L*/	{X,		102,	199,	X,		X,		X,		143,	X,		X,		X,		0,		X,		X,		X,		108,	X},
/*M*/	{109,	X,		63,		X,		61,		X,		X,		X,		X,		X,		X,		0,		142,	X,		X,		X},
/*N*/	{109,	X,		X,		X,		X,		X,		X,		X,		X,		X,		X,		142,	0,		107,	X,		X},
/*P*/	{108,	X,		X,		X,		X,		X,		X,		124,	X,		X,		X,		X,		107,	0,		X,		140},
/*Q*/	{X,		X,		186,	95,		X,		X,		X,		159,	162,	X,		108,	X,		X,		X,		0,		X},
/*R*/	{X,		X,		X,		168,	X,		X,		X,		98,		X,		X,		X,		X,		X,		140,	X,		0},
		};
	

int main(void)
{
	TABLE T[Max];
	Dijkstra(map,0,T);
	ShowTable(T);
	
	return 0;
}
