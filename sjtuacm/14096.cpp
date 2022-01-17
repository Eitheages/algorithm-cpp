/*
move a over b，把a上面的箱子放到初始位置，并把a放到b箱子的最上方； 
move a onto b，把a和b上面的箱子放回初始位置，并把a放到b上面； 
pile a over b，把a和a上面的箱子一起放到b的最上方； 
pile a onto b，把b上面的箱子放回初始位置，然后把a和a上面的箱子一起放到b上面。 
当a = b或a和b处在同一摞时，任何企图操作a和b的命令都是非法的。
所有非法的命令都要忽略，且不能对当前积木的状态产生作用。
*/
#include <iostream>
#include <cstring>
using namespace std;
#define check(a, b) if (a == b || pos[a] == pos[b]) return

class Game
{
public:
    Game (int n = 10);
    Game (const Game&) = default;
    ~Game ();
    void move_over(int, int);
    void move_onto(int, int);
    void pile_over(int, int);
    void pile_onto(int, int);
    void display() const;
    
private:
    char **box; //a string array to record the status of every position
    int *pos; //an array to record the position of every box
    const int N; // a constant to record how many boxes
    int reput(int a); // clear the box over box-a
};

Game::Game(int n): box(new char*[n]), pos(new int[n]), N(n)
{
    for (int i = 0; i < N; i++)
    {
        box[i] = new char [N+1];
        box[i][0] = i + '0';
        box[i][1] = 0;
        pos[i] = i;
    }
}

Game::~Game()
{
    for (int i = 0; i < N; i++)
        delete box[i];
    delete []box;
    delete []pos;
}

int Game::reput(int a)
{
    char *s = box[pos[a]];
    int i = 0;
    while (s[i] != a + '0')
        i++;
    for (int j = i + 1; s[j] != '\0'; j++)
    {
        pos[s[j]-'0'] = s[j]-'0';
        char* &tmp = box[s[j]-'0'];
        tmp[strlen(tmp)] = s[j];
        tmp[strlen(tmp)+1] = 0;
        s[j] = 0;
    }
    return i;
}

//把a上面的箱子放到初始位置，并把a放到b箱子的最上方
void Game::move_over(int a, int b)
{
    check(a, b);
    int i = reput(a);
    box[pos[a]][i] = 0;
    char* &tmp = box[pos[b]];
    int j = strlen(tmp);
    tmp[j] = a + '0';
    tmp[j+1] = 0;
    pos[a] = pos[b];
}

//把a和b上面的箱子放回初始位置，并把a放到b上面
void Game::move_onto(int a, int b)
{
    check(a, b);
    int i = reput(a);
    reput(b);
    box[pos[a]][i] = 0;
    char* &tmp = box[pos[b]];
    int j = strlen(tmp);
    tmp[j] = a + '0';
    tmp[j+1] = 0;
    pos[a] = pos[b];
}

//把a和a上面的箱子一起放到b的最上方
void Game::pile_over(int a, int b)
{
    check(a, b);
    char *s1 = box[pos[a]], *s2 = box[pos[b]];
    int i = 0, j = strlen(s2);
    while (s1[i] != a + '0')
        i++;
    for (; s1[i] != '\0'; i++, j++)
    {
        s2[j] = s1[i];
        pos[s1[i]-'0'] = pos[b];
        s1[i] = 0;
    }
    s2[j] = 0;
}

//把b上面的箱子放回初始位置，然后把a和a上面的箱子一起放到b上面
void Game::pile_onto(int a, int b)
{
    check(a, b);
    char *s1 = box[pos[a]], *s2 = box[pos[b]];
    int i = 0, j = reput(b) + 1;
    while (s1[i] != a + '0')
        i++;
    for (; s1[i] != '\0'; i++, j++)
    {
        s2[j] = s1[i];
        pos[s1[i]-'0'] = pos[b];
        s1[i] = 0;
    }
    s2[j] = 0;
}

void Game::display() const
{
    for (int i = 0; i < N; i++)
    {
        cout << i << ':';
        for (int j = 0; box[i][j] != '\0'; j++)
            cout << ' ' << box[i][j];
        cout << endl;
    }
}

int main(int argc, char **argv)
{
    int n;
    cin >> n;
    Game game(n);
    char *s = new char[20];
    while (1)
    {
        cin.getline(s, 20);
        switch (s[0])
        {
            case 'q':
                game.display();
                delete s;
                return 0;
            case 'm':
                if (s[8] == 'n')
                    game.move_onto(s[5]-'0', s[12]-'0');
                else if (s[8] == 'v')
                    game.move_over(s[5]-'0', s[12]-'0');
                break;
            case 'p':
                if (s[8] == 'n')
                    game.pile_onto(s[5]-'0', s[12]-'0');
                else if (s[8] == 'v')
                    game.pile_over(s[5]-'0', s[12]-'0');
                break;
            default:
                break;
        }
    }
    delete s;
    return 0;
}