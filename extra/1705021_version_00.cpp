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

        // cout<<"WUMPUS"<<"("<<x<<","<<y<<")"<< " ";
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
        direction=UP;
        total_shots=MAX_SHOTS;
        killed=false;
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
    string getPositionInfo()
    {
        return "Player is now at " + to__string(p.getX()) + ", " + to__string(p.getY());
    }

    string getDirectionInfo()
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
        return "Player is moving at direction: " + s;
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

    Player player;
    Wumpus wumpus;
    Position gold_position;
    Position pit_position;
    bool ended;

public:

    WumpusWorld()
    {
        //...
        ended=false;

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
        wumpus=Wumpus(wumpus_x,wumpus_y);
        gold_position=Position(gold_x,gold_y);
        pit_position=Position(pit_x,pit_y);



        /// if you are interested about POSITIONS
        //cout<<"GOLD"<<"("<<gold_position.getX()<<","<<gold_position.getY()<<")"<< " ";
        // cout<<"PIT"<<"("<<pit_position.getX()<<","<<pit_position.getY()<<")"<< " "<<endl;
        //...
    }

    void moveForward()
    {
        player.moveForward();
        return showGameState();
    }

    void turnLeft()
    {
        player.turnLeft();
        return showGameState();
    }

    void turnRight()
    {
        player.turnRight();
        return showGameState();
    }

    void shoot()
    {
        if(!wumpus.isWumpusKilled())
        {


            if(player.remaining_shots()>0)
                player.cut_shots();
            else
            {
                cout<<"You Have Used All shots"<<endl;
                return showGameState();
            }


            Position wumpus_p=wumpus.getPosition();
            Position player_p=player.getPosition();


            if(player.get_direction()==UP)
            {
                if(wumpus_p.getX()==player_p.getX()&&wumpus_p.getY()>player_p.getY())
                {
                    cout<<"ahhhhhhhhhhhhhhhhhh...."<<endl;
                    cout<<"WUMPUS GONE BUT PIT IS STILL HERE"<<endl;
                    wumpus.kill();
                    return showGameState();
                }

            }


            if(player.get_direction()==RIGHT)
            {
                if(wumpus_p.getY()==player_p.getY()&&wumpus_p.getX()>player_p.getX())
                {
                    cout<<"ahhhhhhhhhhhhhhhhhh...."<<endl;
                    cout<<"WUMPUS GONE BUT PIT IS STILL HERE"<<endl;
                    wumpus.kill();
                    return showGameState();
                }
            }

            if(player.get_direction()==LEFT)
            {
                if(wumpus_p.getY()==player_p.getY()&&wumpus_p.getX()<player_p.getX())
                {
                    cout<<"ahhhhhhhhhhhhhhhhhh...."<<endl;
                    cout<<"WUMPUS GONE BUT PIT IS STILL HERE"<<endl;
                    wumpus.kill();
                    return showGameState();
                }
            }
            if(player.get_direction()==DOWN)
            {
                if(wumpus_p.getX()==player_p.getX()&&wumpus_p.getY()<player_p.getY())
                {
                    cout<<"ahhhhhhhhhhhhhhhhhh...."<<endl;
                    cout<<"WUMPUS GONE BUT PIT IS STILL HERE"<<endl;
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

        cout<<"You have missed it"<<endl;
        return showGameState();
        //...

    }

    void showGameState()
    {
        cout << player.getPositionInfo() << endl;
        cout << player.getDirectionInfo() << endl;



        ///  wumpus handling
        if (player.isAdjacent(wumpus.getPosition())&&!wumpus.isWumpusKilled()&&!ended)
        {
            cout << "stench!" << endl;
        }
        if (player.isSamePoint(wumpus.getPosition())&&!wumpus.isWumpusKilled()&&!ended)
        {
            cout << "Player is killed!" << endl;
            player.kill();
            cout << "Game over!" << endl;
            ended = true;
        }


        ///  pit handling
        if (player.isAdjacent(pit_position)&&!ended)
        {
            cout << "breeze!" << endl;
        }
        if (player.isSamePoint(pit_position))
        {
            cout << "Player is lost forever!" << endl;
            player.kill();
            cout << "Game over!" << endl;
            ended = true;
        }
        /// wining moment  or GOLD "handling !!!"
        if (player.isSamePoint(gold_position)&&!ended)
        {
            cout << "Got the gold!" << endl;
            cout << "Game ended, you won!" << endl;
            ended = true;
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
    fp=fopen("F:\\Offline 1\\wumpus_file.txt","r");
    fscanf(fp,"%d%d%d%d%d%d",&wumpus_x,&wumpus_y,&gold_x,&gold_y,&pit_x,&pit_y);
    fclose(fp);




    WumpusWorld w(wumpus_x, wumpus_y, gold_x, gold_y, pit_x, pit_y);  ///  from FILE

    /// WumpusWorld w;                                                    /// all random

    ///WumpusWorld w(wumpus_x,wumpus_y, gold_x, gold_y);                 ///  pit random

    /// WumpusWorld w(wumpus_x, wumpus_y);                               ///  pit & gold random




    w.showGameState();
    while (!w.isOver())
    {


        cout << "1: move forward" << endl;
        cout << "2: Turn left" << endl;
        cout << "3: Turn right" << endl;
        cout << "4: Shoot" << endl;


        cin >> c; ///control with c.......

        if (c == 1)
        {
            w.moveForward();
        }
        else if (c == 2)
        {
            w.turnLeft();
        }
        else if (c == 3)
        {
            w.turnRight();
        }
        else if (c == 4)
        {
            w.shoot();
        }
    }
    return 0;
}

