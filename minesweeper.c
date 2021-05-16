#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#define NUMBER_OF_BOMB 15

void increase_numbers(int ** table , int x,int y,int row,int column){
	int i=-1;
	for(;i<2;i++){
		if(x>0){
			if(!(y==0 && i==-1) || !(y==column-1 && i==1)){
				if(table[x-1][y+i]!=-1)
					table[x-1][y+i]++;
			}
		}
	}
	if(y>0){
		if(table[x][y-1]!=-1)
			table[x][y-1]++;
	}
	if(y<row-1){
		if(table[x][y+1]!=-1)
			table[x][y+1]++;
	}
	for(i=-1;i<2;i++){
		if(x<row-1){
			if(!(y==0 && i==-1) || !(y==column-1 && i==1)){
				if(table[x+1][y+i]!=-1)
					table[x+1][y+i]++;
			}
		}
	}
}
void print_table(int **table,int row,int column){
	int i,j;
	printf("  ");
	for(i=0;i<10;i++){
		printf(" %d",i );
	}
	printf("\n");
	for(i=0;i<row;i++){
		printf("%d| ",i );
		for(j=0;j<column;j++){
			if(table[i][j]==-1)
				printf("* ");
			else 
				printf("%d ",table[i][j] );
		}
		printf("\n");
	}
}
void print_gamers_table(int **table,int ** should_be_showed,int number_of_flags){
	int i,j;
	printf("Remain Flags: %d\n", number_of_flags);
	printf("   ");
	for (i = 0; i < 10; ++i)
	{
		printf("%d ",i);
	}
	printf("\n");
	for(i=0;i<10;i++){
		printf("%d| ",i);
		for(j=0;j<10;j++){
			if(should_be_showed[i][j]==1){
				printf("%d ",table[i][j] );
			}
			else if(should_be_showed[i][j]==2){
				printf("F ");
			}
			else
				printf("- ");
		}
		printf("\n");
	}
}
int ** create_table(){
	int difficulty=0,number_of_boom=NUMBER_OF_BOMB,row=10,column=10,i=0,x=0,y=0;
	int **table;
	table=(int **)calloc(row,sizeof(int*));
	for(i=0;i<row;i++){
		table[i]=(int *)calloc(column,sizeof(int));
	}
	for(i=0;i<number_of_boom;i++){
			x=rand()%row;
			y=rand()%column;
			if(table[x][y]!=-1){
				table[x][y]=-1;
				increase_numbers(table,x,y,row,column);
			}

			else
				i--;
	}

	//print_table(table,10,10);
	return table;
}
int recuuurrrsssiiiooonnnnn(int **table,int **should_be_showed,int *number_of_showed,int x,int y){
	int i=-1;
	int column=10;
	int row=10;
	//printf("%d %d\n",x,y );
	if(should_be_showed[x][y]!=1)
		(*number_of_showed)++;
	should_be_showed[x][y]=1;
	if(table[x][y]==0){
	for(;i<2;i++){
		if(x>0){
			if(!(y==0 && i==-1) && !(y==column-1 && i==1)){
				if(table[x-1][y+i]!=-1 && should_be_showed[x-1][y+i]==0 && y>=0 && y<10)
					recuuurrrsssiiiooonnnnn(table,should_be_showed,number_of_showed,x-1,y+i);
			}
		}
	}
	if(y>0){
		if(table[x][y-1]!=-1 && should_be_showed[x][y-1]==0 && x>=0 && x<10)
			recuuurrrsssiiiooonnnnn(table,should_be_showed,number_of_showed,x,y-1);
	}
	if(y<row-1){ 
		if(table[x][y+1]!=-1 && should_be_showed[x][y+1]==0 && x>=0 && x<10 && y>=0 )
			recuuurrrsssiiiooonnnnn(table,should_be_showed,number_of_showed,x,y+1);
	}
	for(i=-1;i<2;i++){
		if(x<row-1){
			if(!(y==0 && i==-1) && !(y==column-1 && i==1)){
				if(table[x+1][y+i]!=-1 && should_be_showed[x+1][y+i]==0 && y>-1 && y<10)
					recuuurrrsssiiiooonnnnn(table,should_be_showed,number_of_showed,x+1,y+i);
			}
		}
	}	
	}
}
int selected(int ** table,int **should_be_showed,int *number_of_showed,int x,int y,int flag ,int *number_of_flags){
		if(table[x][y]== -1 && flag==0){
			print_table(table,10,10);
			printf("GAME OVER\nThere is a bomb in the %d %d\n",x,y);
			return 1;
		}
		else if(flag==1){
			if(should_be_showed[x][y]==0 && *number_of_flags>0){
				should_be_showed[x][y]=2;//if flag should_be_showed contains 2
				(*number_of_flags)--;
			}
		}
		else if(table[x][y]>0){
			if(should_be_showed[x][y]!=1)
				(*number_of_showed)++;
			should_be_showed[x][y]=1;		
		}
		else{
			recuuurrrsssiiiooonnnnn(table,should_be_showed,number_of_showed,x,y);
		}
	
	
	print_gamers_table(table,should_be_showed,*number_of_flags);
}
int main(){
	srand(time(NULL));
	int number_of_showed=0,x=0,y=0,flag=0;
	int game_over=0;
	int number_of_flags=NUMBER_OF_BOMB;
	int **should_be_showed=(int **)calloc(10,sizeof(int*));
	int **table=create_table();	
	int i=0;
	for(;i<10;i++){
		should_be_showed[i]=(int *)calloc(10,sizeof(int));
	}
	print_gamers_table(table,should_be_showed,number_of_flags);
	while(game_over!=1){
		printf("Select row: ");
		scanf("%d",&x);
		printf("Select column: ");
		scanf("%d",&y);
		printf("Do you think that there is a bomb here ? If so press 1 else press 0\n");
		scanf("%d",&flag);
		if(x>=0 && x<10 && y>=0 && y<10 && (flag==0 || flag ==1)){
			game_over=selected(table,should_be_showed,&number_of_showed,x,y,flag,&number_of_flags);
			if(number_of_showed>=100- NUMBER_OF_BOMB )
			{
				printf("Good Job bot player\n");
				game_over=1;
			}
		}
		else{
			printf("Almost there try again \nThe Rules: x && y >=0 ,x && y<=9 && (flag==0 || flag==1)\n");
		}
	}
	free(table);
	free(should_be_showed);
	return 0;
}