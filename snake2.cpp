#include <bits/stdc++.h>
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>
using namespace std;

#define ll long long
#define ff first
#define ss second
#define slp(x) usleep((x)*1000)

enum D { Z=0, L, R, U, Dn };

int keyPressed() {
    static bool init = false;
    if (!init) {
        termios t;
        tcgetattr(0, &t);
        t.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(0, TCSANOW, &t);
        setbuf(stdin, NULL);
        init = true;
    }
    int cnt;
    ioctl(0, FIONREAD, &cnt);
    return cnt;
}

int getChar() {
    return getchar();
}

void moveCursor(int x, int y) {
    printf("\033[%d;%dH", y+1, x+1);
}

void hideCursor() { printf("\033[?25l"); }
void showCursor() { printf("\033[?25h"); }

class Core {
protected:
    int w,h;
    int px,py;
    int fx,fy;
    int scn,best;
    int sp;
    bool end;
    D dr;
    deque<pair<int,int>> b;

public:
    Core(int a,int c):w(a),h(c),scn(0),best(0),end(false),dr(Z),sp(200){
        px=w/2; py=h/2;
        b.push_back({px,py});
        b.push_back({px-1,py});
        b.push_back({px-2,py});
        generateFood();
    }

    void setDifficulty(int x){
        if(x==1) sp=260;
        else if(x==2) sp=190;
        else sp=130;
    }

    void generateFood(){
        while(1){
            fx=rand()%w;
            fy=rand()%h;
            bool ok=1;
            for(auto &i:b)
                if(i.ff==fx&&i.ss==fy) ok=0;
            if(ok) break;
        }
    }

    void resetGame(){
        scn=0; dr=Z; end=0;
        px=w/2; py=h/2;
        b.clear();
        b.push_back({px,py});
        b.push_back({px-1,py});
        b.push_back({px-2,py});
        generateFood();
    }

    void drawBoard(){
        moveCursor(0,0);
        for(int i=0;i<w+2;i++) cout<<"🧱";
        cout<<"\n";

        for(int i=0;i<h;i++){
            for(int j=0;j<w+2;j++){
                if(j==0||j==w+1) cout<<"🧱";
                else if(i==py&&j==px+1) cout<<"🐲";
                else if(i==fy&&j==fx+1) cout<<"🐣";
                else{
                    bool body=0;
                    for(auto &k:b)
                        if(k.ff==j-1&&k.ss==i) body=1;
                    cout<<(body?"🐍":"  ");
                }
            }
            cout<<"\n";
        }

        for(int i=0;i<w+2;i++) cout<<"🧱";
        cout<<"\nScore: "<<scn<<"  MAX: "<<best<<"\n";
    }
};

class Play: public Core {
public:
    Play(int a,int b):Core(a,b){}

    void handleInput(){
        if(keyPressed()){
            int c=getChar();
            if(c==27 && getChar()=='['){
                int x=getChar();
                if(x=='A'&&dr!=Dn) dr=U;
                if(x=='B'&&dr!=U) dr=Dn;
                if(x=='C'&&dr!=L) dr=R;
                if(x=='D'&&dr!=R) dr=L;
            }
            if(c=='x') end=1;
        }
        if(dr==Z) dr=R;
    }

    void updateLogic(){
        if(dr==L) px--;
        if(dr==R) px++;
        if(dr==U) py--;
        if(dr==Dn) py++;

        if(px<0||px>=w||py<0||py>=h){ end=1; return; }

        for(auto &i:b)
            if(i.ff==px&&i.ss==py){ end=1; return; }

        b.push_back({px,py});

        if(px==fx&&py==fy){
            scn++;
            generateFood();
        } else b.pop_front();
    }

    void startGame(){
        hideCursor();
        int lastScore=0;

        while(!end){
            drawBoard();
            handleInput();
            updateLogic();
            if(scn>lastScore && scn%10==0){
                sp=max(110,sp-10);
                lastScore=scn;
            }
            slp(sp);
        }

        showCursor();
        best=max(best,scn);
        cout<<"Game Over! Score: "<<scn<<"\n";
        char c;
        cout<<"Press R to restart: ";
        cin>>c;
        if(c=='r'||c=='R'){ resetGame(); startGame(); }
    }
};

int main(){
    srand(time(0));
    string n;
    cout<<"Enter player name: ";
    cin>>n;

    int d;
    cout<<"Difficulty (1 Easy / 2 Medium / 3 Hard): ";
    cin>>d;

    Play g(25,25);
    g.setDifficulty(d);
    g.startGame();

    cout<<"Thanks "<<n<<" for playing\n";
}
