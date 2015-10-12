#include <stdio.h>
//board width and height
#define width 3
#define height 3
char toUpper(int x);
void initBoard(char[][width]);
void displayBoard(const char[][width]);
int determineWinOrTie(const char[][width]);

int main() {
    char board[height][width];
    initBoard(board);
    displayBoard(board);
    char p[2][80];
    int x=0,y=0;
    for(int i=0,t=0;t<7;i++,t++){
        printf("\nPlayer %i, please enter your selection: ",(i+1)); scanf("%s",&p[i][0]);
        switch(toUpper(p[i][0])){
            case 'A': x=0;
                      break;
            case 'B': x=1;
                      break;
            case 'C': x=2;
                      break;
            default: printf("%s is not a valid option.\n",&p[i--][0]);
                     t--;
                     continue;
                     break;
        }
        switch(p[i][1]){
            case '1':y=0;
                     break;
            case '2':y=1;
                     break;
            case '3':y=2;
                     break;
            default: printf("%s is not a valid option.\n",&p[i--][1]);
                     t--;
                     continue;
                     break;
        }
        if(board[y][x]=='*'){
            board[y][x]=(i==0)?'X':'O';
            i=(i==1)?-1:i;
        }
        else {
            printf("Player %i has already marked this spot.\n",i--);
            t--;
        }
        displayBoard(board);
        if(t>=3)
            switch(determineWinOrTie(board)){
                case 0: if(t>=6)
                        {puts("It's a tie.");return 0;}
                        break;
                case 1: puts("Player one wins.");
                        return 0;
                case 2: puts("Player two wins.");
                        return 0;
                default:puts("An error occured.");
                        break;
            }
    }
    return 0;
}
void initBoard(char board[][width]){
    int x=0, y=0;
    bool initializing=1;
    while(initializing) {
        board[x][y]='*';
        if(y==height) {x++;y=0;}
        else          {y++;}
        initializing = (x<=width);
    }
}
void displayBoard(const char board[][width]){
    enum {A, B, C};
    printf("  A   B   C \n"
            "1 %c | %c | %c\n"
            " ---|---|---\n"
            "2 %c | %c | %c\n"
            " ---|---|---\n"
            "3 %c | %c | %c\n",
            board[0][A],board[0][B],board[0][C],
            board[1][A],board[1][B],board[1][C],
            board[2][A],board[2][B],board[2][C]);

}
int determineWinOrTie(const char board[][width]){
    int sum[3][3]={{0,0,0},{0,0,0},{0,0,1}};
    // v:vertical, h:horizontal, diagonal
    enum {v, h, d};

    for(int x=0,y=0;x<width;x++,y=0){
        while(y<width) {
            sum[v][x]+=board[y][x];
            sum[h][x]+=board[x][y];
            if(x==y)
                sum[d][v]+=board[y][x];
            if((x+y)==2)
                sum[d][h]+=board[y][x];
            y++;
        }
    }
    for (int x=0,y=0;x<width;x++,y=0){
        while(y<height){
            if(sum[x][y]==264||sum[x][y]==264)
                return 1;
            if(sum[x][y]==237||sum[x][y]==237)
                return 2;
            y++;
        }
    }
    return 0;
}
char toUpper(int x){
    if((x>96)&&(x<123)) {
        return((char)(x-32));
    }
    else {
        return((char)x);
    }
}

