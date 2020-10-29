#include <iostream>
#include <cmath>
#include <sstream>
#include<ctime>  ///newly added for generating random numbers

using namespace std;

#define GRIDSIZE 4
#define UP      0
#define DOWN    2
#define LEFT    3
#define RIGHT   1
#define MAX_SHOTS 3


string to__string(int x)
{
    std::string out_string;
    std::stringstream ss;
    ss << x;
    return ss.str();
}


class Position
{

    int x, y;

public:

    Position (int x, int y)
    {
        this->x = x;
        this->y = y;
    }

    Position()
    {
        x=0;
        y=0;
    }

    // Modify the following four so that the resulting position does not leave the grid
    void moveRight()
    {
        if(x<GRIDSIZE-1)
            x++;
    }

    void moveLeft()
    {
        if(x>0)
            x--;
    }

    void moveUp()
    {
        if(y<GRIDSIZE-1)
            y++;
    }

    void moveDown()
    {
        if(y>0)
            y--;
    }

    bool isAdjacent(Position p)
    {
        return ((p.x==x+1&&p.y==y&&x+1<GRIDSIZE)||(p.x==x-1&&p.y==y&&x-1>0)||(p.x==x&&p.y==y+1&&y+1<GRIDSIZE)||(p.x==x&&p.y==y-1&&y-1>0));


        //implement the function
    }

    bool isSamePoint(Position p)
    {
        return (p.x==x&&p.y==y);
        //implement the function
    }

    int getX()
    {
        return x;
    }

    int getY()
    {
        return y;
    }

};


class Wumpus
{

    bool killed;
    Position p;

public:

    Wumpus(int x, int y)
    {

        p = Position(x, y);
        killed = false;

        /// if you are interested about POSITIONS

        cout<<"WUMPUS"<<"("<<x<<","<<y<<")"<< " ";
    }

    Wumpus()
    {
        killed=false;

        //...
    }

    void kill()
    {
        killed = true;
    }

    Position getPosition()
    {
        return p;
    }
    bool isWumpusKilled()   ///newly added    for knowing the state of WUMPUS
    {

        return killed;

    }

};


class Player
{

    int direction;
    int total_shots;
    bool killed;
    Position p;

public:


    Player()
    {

    };

    Player(Position p,int direction)
    {
         ///newly added for 2 player mode  so that starting point can be different like (0,3) or (3,3)
        this->p=p;
        this->direction=direction;

        total_shots=MAX_SHOTS;
        killed=false;
        // cout<<p.getX()<<" "<<p.getY()<<direction<<endl;

        //...
    }

    void turnLeft()
    {
        if(direction==UP)
            direction=LEFT;
        else if(direction==LEFT)
            direction=DOWN;
        else if(direction==DOWN)
            direction=RIGHT;
        else //if(direction==RIGHT)
            direction=UP;
        //...
    }

    void turnRight()
    {
        if(direction==UP)
            direction=RIGHT;
        else if(direction==RIGHT)
            direction=DOWN;
        else if(direction==DOWN)
            direction=LEFT;
        else //if(direction==LEFT)
            direction=UP;
        //...
    }

    void moveForward()
    {
        if(direction==UP)
            p.moveUp();
        if(direction==RIGHT)
            p.moveRight();
        if(direction==DOWN)
            p.moveDown();
        if(direction==LEFT)
            p.moveLeft();
        //...
        //...
    }

    bool isAdjacent(Position pos)
    {
        return p.isAdjacent(pos);
    }

    bool isSamePoint(Position pos)
    {
        return p.isSamePoint(pos);
    }


    void kill()
    {
        killed = true;
    }

    Position getPosition()
    {
        return p;
    }
    string getPositionInfo(int d)   /// parameter so that we can print who is "talking" or "dominating"
    {
        return "Player# "+to__string(d+1) +"  is now at " + to__string(p.getX()) + ", " + to__string(p.getY());
    }

    string getDirectionInfo(int d)   /// parameter so that we can print who is "talking" or "dominating"
    {
        string s;
        if (direction == UP)
            s = "up";
        if (direction == DOWN)
            s = "down";
        if (direction == LEFT)
            s = "left";
        if (direction == RIGHT)
            s = "right";
        return "Player# "+to__string(d+1)+" is moving at direction: " + s;
    }



    /// newly added functions for accessing private members

    int get_direction()
    {

        return direction;
    }
    int remaining_shots()
    {
        return total_shots;

    }
    void cut_shots()
    {

        total_shots--;
    }


};



class WumpusWorld
{

private:

    Player player[2]; /// newly added for  2 players
    Wumpus wumpus;
    Position gold_position;
    Position pit_position;
    bool ended;

public:

    WumpusWorld()
    {
        //...
        ended=false;

        ///newly added to set value of direction  and position for p1 and p2
        player[0]=Player(Position(0,0),UP);
        player[1]=Player(Position(0,3),RIGHT);


        int wumpus_x=rand()%GRIDSIZE;
        int wumpus_y=rand()%GRIDSIZE;

        while(wumpus_x==0&&wumpus_y==0)
        {
            wumpus_x=rand()%GRIDSIZE;
            wumpus_y=rand()%GRIDSIZE;

        }

        wumpus=Wumpus(wumpus_x,wumpus_y);



        int gold_x=rand()%GRIDSIZE;
        int gold_y=rand()%GRIDSIZE;

        while((gold_x==wumpus_x&&gold_y==wumpus_y)||(gold_x==0&&gold_y==0))
        {
            gold_x=rand()%GRIDSIZE;
            gold_y=rand()%GRIDSIZE;

        }
        gold_position=Position(gold_x,gold_y);



        int pit_x=rand()%GRIDSIZE;
        int pit_y=rand()%GRIDSIZE;

        while((pit_x==wumpus_x&&pit_y==wumpus_y)||(pit_x==gold_x&&pit_y==gold_y)||(pit_x==0&&pit_y==0))
        {
            pit_x=rand()%GRIDSIZE;
            pit_y=rand()%GRIDSIZE;

        }
        pit_position=Position(pit_x,pit_y);


        /// if you are interested about POSITIONS
        //  cout<<"GOLD"<<"("<<gold_position.getX()<<","<<gold_position.getY()<<")"<< " ";
        // cout<<"PIT"<<"("<<pit_position.getX()<<","<<pit_position.getY()<<")"<< " "<<endl;

    }

    WumpusWorld(int wumpus_x, int wumpus_y)
    {
        ended=false;
                ///newly added to set value of direction  and position for p1 and p2

        player[0]=Player(Position(0,0),UP);
        player[1]=Player(Position(0,3),RIGHT);
        wumpus=Wumpus(wumpus_x,wumpus_y);


        int gold_x=rand()%GRIDSIZE;
        int gold_y=rand()%GRIDSIZE;

        while((gold_x==wumpus_x&&gold_y==wumpus_y)||(gold_x==0&&gold_y==0))
        {
            gold_x=rand()%GRIDSIZE;
            gold_y=rand()%GRIDSIZE;

        }

        gold_position=Position(gold_x,gold_y);

        int pit_x=rand()%GRIDSIZE;
        int pit_y=rand()%GRIDSIZE;

        while((pit_x==wumpus_x&&pit_y==wumpus_y)||(pit_x==gold_x&&pit_y==gold_y)||(pit_x==0&&pit_y==0))
        {
            pit_x=rand()%GRIDSIZE;
            pit_y=rand()%GRIDSIZE;

        }
        pit_position=Position(pit_x,pit_y);



        /// if you are interested about POSITIONS
        // cout<<"GOLD"<<"("<<gold_position.getX()<<","<<gold_position.getY()<<")"<< " ";
        // cout<<"PIT"<<"("<<pit_position.getX()<<","<<pit_position.getY()<<")"<< " "<<endl;
        //...
    }

    WumpusWorld(int wumpus_x, int wumpus_y, int gold_x, int gold_y)
    {
        ended=false;
        ///newly added to set value of direction  and position for p1 and p2

       player[0]=Player(Position(0,0),UP);
        player[1]=Player(Position(0,3),RIGHT);

        wumpus=Wumpus(wumpus_x,wumpus_y);
        gold_position=Position(gold_x,gold_y);

        int pit_x=rand()%GRIDSIZE;
        int pit_y=rand()%GRIDSIZE;

        while((pit_x==wumpus_x&&pit_y==wumpus_y)||(pit_x==gold_x&&pit_y==gold_y)||(pit_x==0&&pit_y==0))
        {
            pit_x=rand()%GRIDSIZE;
            pit_y=rand()%GRIDSIZE;

        }
        pit_position=Position(pit_x,pit_y);


        /// if you are interested about POSITIONS
        //cout<<"GOLD"<<"("<<gold_position.getX()<<","<<gold_position.getY()<<")"<< " ";
        //cout<<"PIT"<<"("<<pit_position.getX()<<","<<pit_position.getY()<<")"<< " "<<endl;
        //...
    }

    WumpusWorld(int wumpus_x, int wumpus_y, int gold_x, int gold_y, int pit_x, int pit_y)
    {
        ended=false;
        ///newly added to set value of direction  and position for p1 and p2

        player[0]=Player(Position(0,0),UP);
        player[1]=Player(Position(0,3),RIGHT);

        wumpus=Wumpus(wumpus_x,wumpus_y);
        gold_position=Position(gold_x,gold_y);
        pit_position=Position(pit_x,pit_y);



        /// if you are interested about POSITIONS
        cout<<"GOLD"<<"("<<gold_position.getX()<<","<<gold_position.getY()<<")"<< " ";
        cout<<"PIT"<<"("<<pit_position.getX()<<","<<pit_position.getY()<<")"<< " "<<endl;
        //...
    }

    void moveForward(int d)
    {
        player[d].moveForward();
        return showGameState();
    }

    void turnLeft(int d)
    {
        player[d].turnLeft();
        return showGameState();
    }

    void turnRight(int d)
    {
        player[d].turnRight();
        return showGameState();
    }

    void shoot(int d)
    {
        if(!wumpus.isWumpusKilled())
        {


            if(player[d].remaining_shots()>0)
                player[d].cut_shots();
            else
            {
                cout<<"player# "<<d+1<<" You Have Used All shots"<<endl;
                return showGameState();
            }


            Position wumpus_p=wumpus.getPosition();
            Position player_p=player[d].getPosition();


            if(player[d].get_direction()==UP)
            {
                if(wumpus_p.getX()==player_p.getX()&&wumpus_p.getY()>player_p.getY())
                {
                    cout<<"ahhhhhhhhhhhhhhhhhh...."<<endl;
                    cout<<"PLAYER# "<<d+1<<" killed the WUMPUS"<<endl;
                    wumpus.kill();
                    return showGameState();
                }

            }


            if(player[d].get_direction()==RIGHT)
            {
                if(wumpus_p.getY()==player_p.getY()&&wumpus_p.getX()>player_p.getX())
                {
                    cout<<"ahhhhhhhhhhhhhhhhhh...."<<endl;
                    cout<<"PLAYER# "<<d+1<<" killed the WUMPUS"<<endl;
                    wumpus.kill();
                    return showGameState();
                }
            }

            if(player[d].get_direction()==LEFT)
            {
                if(wumpus_p.getY()==player_p.getY()&&wumpus_p.getX()<player_p.getX())
                {
                    cout<<"ahhhhhhhhhhhhhhhhhh...."<<endl;
                    cout<<"PLAYER# "<<d+1<<" killed the WUMPUS"<<endl;
                    wumpus.kill();
                    return showGameState();
                }
            }
            if(player[d].get_direction()==DOWN)
            {
                if(wumpus_p.getX()==player_p.getX()&&wumpus_p.getY()<player_p.getY())
                {
                    cout<<"ahhhhhhhhhhhhhhhhhh...."<<endl;
                    cout<<"PLAYER# "<<d+1<<" killed the WUMPUS"<<endl;
                    wumpus.kill();
                    return showGameState();
                }
            }


        }
        else
        {
            cout<<"WUMPUS HAS ALREADY BEEN KILLED"<<endl;
            return showGameState();
        }

        cout<<"player# "<<d+1<<" You have missed it"<<endl;
        return showGameState();
        //...

    }

    void showGameState()

    {
        for(int i=0; i<2; i++)
        {
            cout << player[i].getPositionInfo(i) << endl;
            cout << player[i].getDirectionInfo(i) << endl;



            ///  wumpus handling
            if (player[i].isAdjacent(wumpus.getPosition())&&!wumpus.isWumpusKilled()&&!ended)
            {
                cout << "player# "<<i+1<<" feels stench!" << endl;
            }
            if (player[i].isSamePoint(wumpus.getPosition())&&!wumpus.isWumpusKilled()&&!ended)
            {
                cout << "player# "<<i+1<<" is killed" << endl;
                player[i].kill();
                cout << "Game over!" << endl;
                if(i==0)
                    cout << "player# 2is winner" << endl;
                else
                    cout << "player# 1 is winner" << endl;
                ended = true;
            }


            ///  pit handling
            if (player[i].isAdjacent(pit_position)&&!ended)
            {
                cout << "player# "<<i+1<<" feels breeze!" << endl;
            }

            if (player[i].isSamePoint(pit_position))
            {
                cout << "Player# "<<i+1<<" is lost forever!" << endl;
                player[i].kill();
                cout << "Game over!" << endl;

                if(i==0)
                    cout << "player# 2 is winner" << endl;
                else
                    cout << "player# 1 is winner" << endl;
                ended = true;
            }

            /// wining moment  or GOLD "handling !!!"
            if (player[i].isSamePoint(gold_position)&&!ended)
            {
                cout <<"player#"<<i+1<< "Got the gold!" << endl;
                cout << "Game ended"<<"player# "<<i+1<<" won!" << endl;
                ended = true;
            }
        }

    }

    bool isOver()
    {
        return ended;
    }

};


int main()
{
    srand(time(0));  ///for generating random positions

    int c, wumpus_x, wumpus_y, gold_x, gold_y, pit_x, pit_y;

    ///take the six integers input from file
    FILE *fp;
    fp=fopen("D:\\Departmental Things 2\\Cse 2\\OPPS LAB\\Offline 1\\wumpus_file.txt","r");
    fscanf(fp,"%d%d%d%d%d%d",&wumpus_x,&wumpus_y,&gold_x,&gold_y,&pit_x,&pit_y);
    fclose(fp);




    WumpusWorld w(wumpus_x, wumpus_y, gold_x, gold_y, pit_x, pit_y);  ///  from FILE

    /// WumpusWorld w;                                                    /// all random

    ///WumpusWorld w(wumpus_x,wumpus_y, gold_x, gold_y);                 ///  pit random

    /// WumpusWorld w(wumpus_x, wumpus_y);                               ///  pit & gold random

    int PLAYER=0;


    w.showGameState();
    while (!w.isOver())
    {

        int d=PLAYER%2;
        if(!d)
            cout<<"PLAYER 1 NOW"<<endl;
        else
            cout<<"PLAYER 2 NOW"<<endl;

        cout << "1: move forward" << endl;
        cout << "2: Turn left" << endl;
        cout << "3: Turn right" << endl;
        cout << "4: Shoot" << endl;


        cin >> c; ///control with c.......

        if (c == 1)
        {
            w.moveForward(d);
        }
        else if (c == 2)
        {
            w.turnLeft(d);
        }
        else if (c == 3)
        {
            w.turnRight(d);
        }
        else if (c == 4)
        {
            w.shoot(d);
        }
        PLAYER++;
    }
    return 0;
}
