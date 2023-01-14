#include <iostream>
#include <string>

using namespace std;

#define compare(x, y, z) ((board[x] == board[y]) && (board[y] == board[z]) && (board[x] != 0))
                                                    //comparing three consecutive spaces and checking if there are blank or not
#define get_symbol(x) ((x > 0) ? (x == 1) ? 'X' : 'O' : ' ')
                                                    //Takes the number and turns it into the letter or space.
#define player_icon(x) ((x%2==0) ? 'X' : 'O')
#define player_no(x) ((x%2==0) ? 2 : 1)

int check_winner(int board[9]) {
	//Finds winner of game, if there is no winner, returns 0.
	for (int x = 0; x < 3; x++) {
		if (compare(3*x, 3*x+1, 3*x+2)) //Chekcs rows.
			return board[3*x];
		else if (compare(x, x+3, x+6)) //Checks columns.
			return board[x];
		else if (compare(2*x, 4, 8-2*x) && (x < 2)) //Checks diagonals. Doesn't check if x == 2.
			return board[4];
	}
	return 0;
}

bool game_over(int board[9]){
	//Checks if game is over, and announces who won, or if it was a tie.
	int winner = check_winner(board);
	if (winner > 0) {
		cout<<"\t\t\t"<<get_symbol(winner) << " Wins!\n\n"<< endl;
		return true;
	}
	for (int x = 0; x < 9; x++) {
		if (board[x] == 0) return false;
	}
	cout<<"\t\t\tTie!\n\n";
	return true;
}

int case1(int board[9]) {
    for(int i=2;i>0;i--) {
        for(int j=0;j<9;j++) {
            int newboard[9];
            memcpy(newboard,board,36);
            if(board[j]>0)
                continue;
            newboard[j]=i;
            if(check_winner(newboard) == i)
                return j;
        }
    }
    return -1;
}

int spcase(int board[9]) {
    if((board[0]==1 && board[8]==1 || board[2]==1 && board[6]==1)&& board[1]==0)
        return 1;
    else if(board[1]==1 && board[3]==1 && board[0]==0)
        return 0;
    else if(board[1]==1 && board[5]==1 && board[2]==0)
        return 2;
    else if(board[3]==1 && board[7]==1 && board[6]==0)
        return 6;
    else if(board[5]==1 && board[7]==1 && board[8]==0)
        return 8;
    return -1;
}

int case4(int board[9], int blank[4]) {
    for(int i=0;i<4;i++)
        if(board[blank[i]]==0)
            return blank[i];
	return -1;
}

void display(int board[9]) {
	for(int i=0;i<3;i++){
        cout<<"\t\t\t";
		for (int box=0;box<3;box++)
			cout<<get_symbol(board[3*i+box]) << ((box < 2) ? '|' : '\n');
		cout<<"\t\t\t"<<((i < 2) ? "-----\n" : "\t\t\t\n");
	}
}

void choice1(int board[9]){
    int corners[4]={0,2,6,8}, sides[4]={1,3,5,7};
    int move,ctr;
    while(1){
		//Player X decides what move they'll do.
        do{
            ctr=0;
            cout<<"\t\t\tX: ";
            cin>>move;
            move=move-1;
            if(move>8 || move<0 || board[move]!=0){
                cout<<"\t\t\tInvalid input"<<endl;
                ctr++;
            }
            else{
                board[move]=1;
                cout<<endl;
            }
        }while(ctr!=0);

		if (game_over(board) > 0) {  //Decides whether or not the game continues.
			display(board);
			break;
		}

		if (case1(board)!= -1)
                board[case1(board)]=2;
		else if (board[4] == 0)
                board[4] = 2; //Middle
		else if (spcase(board)>0)
                board[spcase(board)] = 2; //tricky cases
		else if (case4(board, corners) != -1)
                board[case4(board, corners)] = 2; //secure corners
		else
                board[case4(board, sides)] = 2; //secure sides

		display(board);
		if(game_over(board)) break;
	}
}

void choice2(int board[9]){
    int move,move_no=0,ctr=0;
    while(1){
        do{
            ctr=0;
            cout<<"\t\t\t"<<player_icon(move_no)<<" turn :";
            cin>>move;
            move=move-1;
            if(board[move]!=0 || move>8 || move<0){
                cout<<"\t\t\tInvalid input"<<endl;
                ctr++;
            }
            else{
                move_no++;
                board[move]=player_no(move_no);
                cout<<endl;
            }
        }while(ctr!=0);

        if (game_over(board) > 0) {  //Decides whether or not the game continues.
            display(board);
            break;
		}
        display(board);
		if(game_over(board)) break;
    }
}

int main(){
    while(1){
        int board[9]={0,0,0,0,0,0,0,0,0}; //Starts empty board.
        int ctr, choice;
        do{
            ctr==0;
            cout<<"\n\n\n\n\n\t\t\t Enter game mode :";
            cout<<"\n\t\t\t 1. Player Vs Computer ";
            cout<<"\n\t\t\t 2. Player Vs Player ";
            cout<<"\n\t\t\t 3. Exit ";
            cout<<"\n\n\t\t\t Choice : ";
            cin>>choice;
            if(choice==3){
                cout<<"\n\t\t\t Thank You "<<endl;
                return 0;
            }
            else if(choice<1){
                cout<<"Invalid Input"<<endl;
                ctr++;
            }
            system("cls");
        }while(ctr!=0);

        cout<<"\n\t\t\t1|2|3 \n\t\t\t----- \n\t\t\t4|5|6 \n\t\t\t----- \n\t\t\t7|8|9\n\n";
        switch(choice){
            case 1:
                choice1(board);
                break;
            case 2:
                choice2(board);
                break;
        }
        cin.get();
        cin.get();
        system("cls");
    }

	return 0;
}
