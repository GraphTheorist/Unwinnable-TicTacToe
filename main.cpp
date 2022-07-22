#include<bits/stdc++.h>
using namespace std;
#define inf 1000000
int nxt_x, nxt_y;
int gb_filled;
struct Board{
    vector<vector<char>>v;
    Board(){
        v.resize(4, vector<char>(4, '_'));  //constructor for initializing the board to a 3 x 3 square
    }
    void print(){
        for(int i=1; i<=3; ++i){
            for(int j=1; j<=3; ++j){
                cout<<v[i][j]<<" ";
            }
            cout<<'\n';
        }
    }
    
};
int score(Board& b){
    for(int i=1;i<=3;i++){
        if(b.v[i][1] == b.v[i][2] && b.v[i][1] == b.v[i][3]){  //row check
            if(b.v[i][1] == 'O')
                return -1;
            if(b.v[i][1] == 'X')
                return 1;
        }
        if(b.v[1][i] == b.v[2][i] && b.v[1][i] == b.v[3][i]){  //column check
            if(b.v[1][i] == 'O')
                return -1;
            if(b.v[1][i] == 'X')
                return 1;
        }
    }
    if(b.v[1][1] == b.v[2][2] && b.v[1][1] == b.v[3][3]){  //first diagonal check
        if(b.v[1][1] == 'O')
            return -1;
        if(b.v[1][1] == 'X')
            return 1;
    }
    if(b.v[1][3] == b.v[2][2] && b.v[1][3] == b.v[3][1]){  //second diagonal check
        if(b.v[1][3] == 'O')
            return -1;
        if(b.v[1][3] == 'X')
            return 1;
    }

    return 0;
}
int minimax(Board& b, bool mx, int filled){
   // if(filled==9) return 0;
    int sc=score(b);
    if(sc) return sc;  //board has reached an end state
    if(filled==9) return 0;  //tied
    int final_score;
    if(mx){
        int cur_score=-inf;
        for(int i=1; i<=3; ++i){
            for(int j=1; j<=3; ++j){
                if(b.v[i][j]=='_'){
                    b.v[i][j]='X';
                    int temp_score=minimax(b, false, filled+1);  //recursively get the max possible score
                    cur_score=max(cur_score, temp_score);
                    b.v[i][j]='_';
                }
            }
        }
        final_score=cur_score;
    }
    else{
        int cur_score=inf;
        for(int i=1; i<=3; ++i){
            for(int j=1; j<=3; ++j){
                if(b.v[i][j]=='_'){
                    b.v[i][j]='O';
                    int temp_score=minimax(b, true, filled+1);
                    if(gb_filled==filled && (score(b)==-1 || temp_score<cur_score)) nxt_x=i, nxt_y=j;
                    //set the computer's move only when we are at the topmost recursion state.
                    //if score reduces, or already at a losing state, set the computer's move
                    cur_score=min(cur_score, temp_score);
                    b.v[i][j]='_';
                }
            }
        }
        final_score=cur_score;
    }
    return final_score;
}
signed main(){
    Board TicTacToe;
    while(true){
        nxt_x=0;
        nxt_y=0;
        cout<<"Please enter the coordinates of X: "<<'\n';
        int x,y; cin>>x>>y;
        while(TicTacToe.v[x][y]!='_'){
            cout<<"Please enter coordinates for a cell which hasn't been occupied\n";
            cin>>x>>y;
            continue;
        }
        TicTacToe.v[x][y]='X';
        ++gb_filled;
        int occ=minimax(TicTacToe, false, gb_filled);
        if(nxt_x && nxt_y){ //if board was not full after our move, we get the computer's move
            TicTacToe.v[nxt_x][nxt_y]='O';
            ++gb_filled;
        }
        if(score(TicTacToe)==-1){  //final state is lose
            TicTacToe.print();
            cout<<"You lose!\n";
            return 0;
        }
        if(score(TicTacToe)==1){  //final state is win; redundant because human will never win
            TicTacToe.print();
            cout<<"You win!\n";
            return 0;
        }
        if(gb_filled==9){  //final state is a tie
            TicTacToe.print();
            cout<<"Tie!\n";
            return 0;
        }
        TicTacToe.print();
    }
}