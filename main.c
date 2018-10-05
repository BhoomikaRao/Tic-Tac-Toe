#include<stdio.h>
#include<stdlib.h>


struct nodetype{
	char board[3][3];
	int turn;
    struct nodetype*next;
	
};

typedef struct nodetype *NODEPTR;

int minimax(NODEPTR p);
int computerMove(NODEPTR p);
int win(char board[][3]);
void playerMove(NODEPTR*);
void draw(char brd[3][3]) ;
char alpha(int i);
NODEPTR getnode();
NODEPTR generate(NODEPTR p);


int main()
{
    int play;
    do {
	    NODEPTR p;
        p = getnode();
        int i, flag =1 ,player;
	    do 
	    {
		    printf("Computer plays as O and you X ");
		    printf("\n Do you want to play first? If yes enter 1 else 2");
            scanf("%d",&player);
		    if(player <0 || player >2) 
                printf("\n %d is a invalid input. Choose again") ;
            else
                flag =0;
	    }while(flag == 1);
		
        printf("\n");
        unsigned turn;
        for(turn = 0; turn < 9 && win(p->board) == 0 ; ++turn) 
        {
            if((turn+player) % 2 == 0)
            {
			    computerMove(p);
            }
            else 
            {
                printf("\n player move");
                draw(p->board);
                playerMove(&p);
            }
        }
        switch(win(p->board))
        {
            case 0:
                printf("It's a draw.\n");
                break;
            case 1:
                draw(p->board);
                printf("Ooops. You lost.\n");
                break;
            case -1:
                printf("Congo!!! You won the game\n");
                break;
        }
        printf(" Enter 1 to play again. 0 to exit");
        scanf("%d",&play);
        if(play == 0)
            exit(0);
    }while(1);
}


int minimax(NODEPTR p)
{
	int winner = win(p->board);
	if(winner!=0) return winner*(p->turn);
	
	int move =-1;
	int score = -2;
	int i;
    NODEPTR son, pbest;
    son = NULL;
    pbest = NULL;
    son = generate(p);
    while(son!= NULL)
    {
        int thisScore = -minimax(son);
			if(thisScore>score)
			{
				score=thisScore;
				pbest =son;
			}
        son = son->next;
    }
    if(pbest == NULL) return 0;
	return score;
}

	


int computerMove(NODEPTR p)
{
	int move = -1;
	int score = -2;
	int i=0;
	for(i=0;i<9;i++)
	{
		if(p->board[i/3][i%3]==' ')
		{
			p->board[i/3][i%3]='O';
			p->turn = -1;
			int tempScore = -minimax(p);
			p->board[i/3][i%3]=' ';
			if(tempScore> score)
			{
				score = tempScore;
				move =i;
			}
		}
	}
	p->board[move/3][move%3] = 'O';
}


int win(char board[][3])
{
    int i;
	for (i=0; i<3; i++)
	{
		if (board[i][0]!= ' ' && board[i][0] == board[i][1] && board[i][0]==board[i][2] )
		{
			if (board[i][0] == 'X')
				return -1;
			else
				return 1;
		}
	}
	
	for(i =0; i<3; i++)
	{
		if(board[0][i]!= ' ' && board[0][i] == board[1][i] && board[0][i]==board[2][i])
		{
			if (board[0][i] == 'X')
				return -1;
			else
				return 1;
		}
	}
	if (board[0][0]!= ' ' && board[0][0] ==  board[1][1] && board[0][0]== board[2][2])
	{
		if (board[0][0]== 'X')
			return -1;
		else
			return 1;
	}
	if (board[0][2]!= ' ' && board[0][2] == board[1][1] && board[0][2] == board[2][0])
	{
		if (board[0][2]=='X')
			return -1;
		else
			return 1;
	}
	
		return 0;
}

char alpha(int i) {
    switch(i) {
        case -1:
            return 'X';
        case 0:
            return ' ';
        case 1:
            return 'O';
    }
}

void draw(char brd[3][3]) 
{
    printf("\n \n");
    printf(" %c | %c | %c\n", brd[0][0],brd[0][1],brd[0][2]);
    printf("---+---+---\n");
    printf(" %c | %c | %c\n",brd[1][0],brd[1][1],brd[1][2]);
    printf("---+---+---\n");
    printf(" %c | %c | %c\n",brd[2][0],brd[2][1],brd[2][2]);
}

void playerMove(NODEPTR*root)
{ 
	NODEPTR temp;
	temp = *root;
    int move = 0;
    do {
        printf("\nInput move ([0..8]): ");
        scanf("%d", &move);
        printf("\n");
    } while (move >= 9 || move < 0 || temp->board[move/3][move%3] != ' ');
    temp->board[move/3][move%3] = 'X' ;
	temp->turn  =- 1;
}

NODEPTR getnode()
{
	NODEPTR temp;
	temp = (NODEPTR)malloc(sizeof(struct nodetype));
    temp->next = NULL;
    int i;
	for(i=0; i<9;i++)
		temp->board[i/3][i%3]=' ';
	return temp;
}



NODEPTR generate(NODEPTR p)
{
	NODEPTR temp, head, tail;
	head =NULL;
    int i,j;
	for(i=0; i<9; i++)
	{
        temp = getnode();
	    temp->turn = (p->turn)*-1;
        for(j=0; j<9; j++)
            temp->board[j/3][j%3]= p->board[j/3][j%3];
		if(temp->board[i/3][i%3]==' ')
		{
			//temp->board[i/3][i%3] = -1 *( temp->turn);
            if(temp->turn == -1)
                temp->board[i/3][i%3] = 'O';
            else
                temp->board[i/3][i%3]='X';
            if(head == NULL)
		    {
			    head = temp;
			    tail = head;
		    }
		    else
		    {
                tail->next = temp;
                tail = tail->next;
		    }
            
		}
	}
	return head;
}