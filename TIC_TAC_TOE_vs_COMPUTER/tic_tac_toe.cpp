// TIC TAC TOE GAME IN CPP
// VS COMPUTER

#include<bits/stdc++.h>

#define max_size 3

using namespace std;

struct prob{
    int win_prob;
    int loss_prob;
    int draw_prob;
};
struct pos{
    int row;
    int col;
};

char grid[max_size][max_size];
int N = max_size;
string player_name[2];
vector<pos> win,loss,draw;
int add;

void print_grid();
void get_player_names();
void initialize_grid();
char player_symbol(int player);
void loading();
bool check_is_empty(int row,int col);
bool check_row(int row , int player,char grid[max_size][max_size] );
bool check_column(int col,int player,char grid[max_size][max_size]);
bool check_main_diagonal(int player,char grid[max_size][max_size]);
bool check_another_diagonal(int player,char grid[max_size][max_size]);
bool check_diagonal(int i , int j , int player,char grid[max_size][max_size]);
bool check_win(int i ,int j,int player,char grid[max_size][max_size]);
prob findBestMove( char grd[max_size][max_size], int depth , int player_number  );

int main()
{
    get_player_names();
    loading();
    initialize_grid();
    print_grid();
    int row,col;
    int i=0;
    srand(time(0));
    add = rand()%2;
    while(true)
    {
        win.clear();
        draw.clear();
        loss.clear();
        char temp[max_size][max_size];
        for(int i=0;i<N;i++)
            for(int j=0;j<N;j++)
                temp[i][j]=grid[i][j];
        int player = (i+ add )%2;
        print_grid();
        if(player==0)
        {
            if(i>0)
                cout<<"\n\tCOMPUTER's LAST MOVE : "<<"Row: "<<row<<"\tCol: "<<col<<endl;
            prob res = findBestMove(temp,0,player);
            cout<<"\tWin PROB: "<<res.win_prob*100<<"%"<<endl;
            cout<<"\tLoss PROB: "<<res.loss_prob*100<<"%"<<endl;
            cout<<"\tDraw PROB: "<<res.draw_prob*100<<"%"<<endl;
            cout<<"\tIf you play optimally!!"<<endl;
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
        }
        else
        {
            prob res = findBestMove(temp,0,player);
            if(win.size())
            {
                int q = rand()%(win.size());
                row = win[q].row;
                col = win[q].col;
            }
            else if(draw.size())
            {
                int q = rand()%(draw.size());
                row = draw[q].row;
                col = draw[q].col;
            }
            else
            {
                int q = rand()%(loss.size());
                row = loss[q].row;
                col = loss[q].col;
            }
        }
        grid[row-1][col-1] = player_symbol(player);
        if( check_win(row-1,col-1,player,grid) )
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
    int p = (player + add)%2;
    if(p)
        return 'O';
    else
        return 'X';
}

bool check_is_empty(int row,int col)
{
    if(grid[row][col]=='-')
        return 1;
    return 0;
}

void get_player_names()
{
    system("cls");
    cout<<"\n\n\t\tEnter Your Name: ";
    getline(cin>>ws,player_name[0]);
    player_name[1] = "COMPUTER";
}

void initialize_grid()
{
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
            grid[i][j]='-';
}

bool check_row(int row , int player,char grid[max_size][max_size] )
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

bool check_column(int col,int player,char grid[max_size][max_size])
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

bool check_main_diagonal(int player,char grid[max_size][max_size])
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

bool check_another_diagonal(int player,char grid[max_size][max_size])
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


bool check_diagonal(int i , int j , int player,char grid[max_size][max_size])
{
    if( i!=j and (i+j)!=N-1 )
        return 0;
    if( (N%2!=0) && i==(N-1)/2 && j==(N-1)/2 )
        return (check_main_diagonal(player,grid) || check_another_diagonal(player,grid));
    if(i==j)
        return check_main_diagonal(player,grid);
    return check_another_diagonal(player,grid);
}

bool check_win(int i ,int j,int player,char grid[max_size][max_size])
{
    if( check_row(i,player,grid) || check_column(j,player,grid) || check_diagonal(i,j,player,grid) )
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
    cout<<"\t"<<player_name[0]<<" : "<<"\""<<player_symbol(0)<<"\""<<endl;
    cout<<"\t"<<player_name[1]<<" : "<<"\""<<player_symbol(1)<<"\""<<endl<<endl;
    cout<<endl;
    cout<<"\t\t\t\t";
    for(int j=0;j<N;j++)
        cout<<"|---";
    cout<<"|";
    cout<<endl;
    for(int i=0;i<N;i++)
    {
        cout<<"\t\t\t\t| ";
        for(int j=0;j<N;j++)
        {
            cout<<grid[i][j]<<" | ";
        }
        cout<<endl;
        cout<<"\t\t\t\t";
        for(int j=0;j<N;j++)
            cout<<"|---";
        cout<<"|";
        cout<<endl;
    }
}


prob findBestMove( char grd[max_size][max_size] , int depth , int player_number  )
{
    vector<pair<int,int>> to_fill;
    for(int i=0;i<max_size;i++)
        for(int j=0;j<max_size;j++)
            if(grd[i][j]=='-') to_fill.push_back({i,j});
    if( to_fill.size() == 1 )
    {
        int i = to_fill[0].first;
        int j = to_fill[0].second;
        grd[ i ][ j ] = player_symbol(player_number);
        if(check_win(i,j,player_number,grd))
        {
            grd[ i ][ j ] = '-';
            if(depth==0)
                win.push_back({i+1,j+1});
            return {1,0,0};
        }
        else
        {
            grd[ i ][ j ] = '-';
            if(depth==0)
                draw.push_back({i+1,j+1});
            return {0,0,1};
        }

    }
    for(int z = 0 ; z < to_fill.size() ; z++)
    {
        int i = to_fill[z].first;
        int j = to_fill[z].second;
        grd[i][j] = player_symbol(player_number);
        if( check_win(i,j,player_number,grd) )
        {
            grd[i][j] = '-';
            if(depth==0)
                win.push_back({i+1,j+1});
            return {1,0,0};
        }
        grd[i][j] = '-';
    }
    prob result;
    bool w = 0, d = 0, l = 0;
    for(int z = 0 ; z < to_fill.size() ; z++)
    {
        int i = to_fill[z].first;
        int j = to_fill[z].second;
        grd[i][j] = player_symbol(player_number);
        result = findBestMove(grd, depth+1 ,(player_number+1)%2);
        if(result.draw_prob == 1){
            d = 1;
            if(depth==0)
                draw.push_back({i+1,j+1});
        }
        else if( result.win_prob == 1 ){
            l = 1;
            if(depth==0)
                loss.push_back({i+1,j+1});
        }
        else if( result.loss_prob == 1 ){
            w = 1;
            if(depth==0)
                win.push_back({i+1,j+1});
        }

        grd[i][j] = '-';
    }
    if(w)
        return {1,0,0};
    else if(d)
        return {0,0,1};
    else
        return {0,1,0};
}





