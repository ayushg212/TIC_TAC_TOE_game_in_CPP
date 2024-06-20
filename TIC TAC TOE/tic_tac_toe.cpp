// TIC TAC TOE GAME IN CPP

#include<bits/stdc++.h>

#define max_size 20 // Can Change Max Size of grid

using namespace std;

char grid[max_size][max_size];
int N;
string player_name[2];

void print_grid();
void get_grid_size();
void get_player_names();
void initialize_grid();
char player_symbol(int player);
void loading();
bool check_is_empty(int row,int col);
bool check_row(int row , int player );
bool check_column(int col,int player);
bool check_main_diagonal(int player);
bool check_another_diagonal(int player);
bool check_diagonal(int i , int j , int player);
bool check_win(int i ,int j,int player);

int main()
{
    get_grid_size();
    get_player_names();
    loading();
    initialize_grid();
    print_grid();
    int row,col;
    int i=0;
    while(true)
    {
        print_grid();
        int player = i%2;
        cout<<"\n\t"<<player_name[player]<<"'s Turn : \""<<player_symbol(player)<<"\"\n";
        do
        {
            cout<<"\n\tEnter Row(1 to "<<N<<"): ";
            cin>>row;
            if(cin.fail() || !(row>=1 && row<=N))
            {
                cin.clear();
                cin.ignore(1000,'\n');
                continue;
            }
            cout<<"\tEnter Column(1 to "<<N<<"): ";
            cin>>col;
            cin.clear();
            cin.ignore(1000,'\n');
        }while( !(col>=1 && col<=N) || !check_is_empty(row-1,col-1) || cin.fail() );
        grid[row-1][col-1] = player_symbol(player);
        if( check_win(row-1,col-1,player) )
        {
            print_grid();
            cout<<"\n\n\t\t"<<player_name[player]<<" WINS!!\n\n\n";
            system("pause");
            exit(1);
        }
        i++;
        if(i==N*N)
        {
            print_grid();
            cout<<"\n\n\t\t"<<" DRAW!!\n\n\n";
            system("pause");
            exit(1);
        }
    }
    return 0;
}


char player_symbol(int player)
{
    if(player==0)
        return 'O';
    if(player==1)
        return 'X';
}

bool check_is_empty(int row,int col)
{
    if(grid[row][col]=='-')
        return 1;
    return 0;
}

void get_grid_size()
{
    cout<<"\n\n\t\tENTER GRID SIZE(3 to "<<max_size<<"): ";
    cin>>N;
    while( cin.fail() || !(N>=3) || !(N<=max_size) )
    {
        cin.clear();
        cin.ignore(1000,'\n');
        cout<<"\n\t\t!!Enter Valid SIZE!!";
        cout<<"\n\n\t\tENTER GRID SIZE(3 to "<<max_size<<"): ";
        cin>>N;
    }
}

void get_player_names()
{
    system("cls");
    cout<<"\n\n\t\tEnter Player 1 Name: ";
    getline(cin>>ws,player_name[0]);
    cout<<"\n\n\t\tEnter Player 2 Name: ";
    getline(cin>>ws,player_name[1]);

}

void initialize_grid()
{
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
            grid[i][j]='-';
}

bool check_row(int row , int player )
{
    int count=0;
    for(int i=0 ; i<N ; i++ )
    {
        if(grid[row][i]==player_symbol(player))
            count++;
    }
    if(count==N)
        return true;
    return false;
}

bool check_column(int col,int player)
{
    int count=0;
    for(int i=0;i<N;i++)
    {
        if(grid[i][col] == player_symbol(player))
            count++;
    }
    if(count==N)
        return 1;
    return 0;
}

bool check_main_diagonal(int player)
{
    int count = 0;
    for(int i=0;i<N;i++)
    {
        if(grid[i][i]==player_symbol(player))
            count++;
    }
    if(count==N)
        return 1;
    return 0;
}

bool check_another_diagonal(int player)
{
    int count = 0;
    for(int i=0;i<N;i++)
    {
        if(grid[i][N-i-1]==player_symbol(player))
            count++;
    }
    if(count==N)
        return 1;
    return 0;
}


bool check_diagonal(int i , int j , int player)
{
    if( i!=j and (i+j)!=N-1 )
        return 0;
    if( (N%2!=0) && i==(N-1)/2 && j==(N-1)/2 )
        return (check_main_diagonal(player) || check_another_diagonal(player));
    if(i==j)
        return check_main_diagonal(player);
    return check_another_diagonal(player);
}

bool check_win(int i ,int j,int player)
{
    if( check_row(i,player) || check_column(j,player) || check_diagonal(i,j,player) )
        return 1;
    return 0;
}

void loading()
{
    system("cls");
    for(int i=0;i<10;i++)
        cout<<"\n";
    for(int i=0;i<5;i++)
        cout<<"\t";
    cout<<"LOADING...\n";
    for(int i=0;i<4;i++)
        cout<<"\t";
    char ch=178;
    for(int i =0 ; i <23;i++)
    {
        cout<<ch;
        for(int j=0;j<=1e7;j++);
    }
    system("cls");
}

void print_grid()
{
    system("cls");
    cout<<"\n\n";
    cout<<player_name[0]<<" : "<<"\"O\""<<endl;
    cout<<player_name[1]<<" : "<<"\"X\""<<"\n\n";
    for(int i=0;i<N;i++)
    {
        cout<<" ";
        for(int j=0;j<N;j++)
        {
            cout<<grid[i][j]<<" | ";
        }
        cout<<endl;
        for(int j=0;j<N;j++)
            cout<<"----";
        cout<<endl;
    }
}
