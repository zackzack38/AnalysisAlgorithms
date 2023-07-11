//Notes I don't remember any C++, I would use Java but I don't even remember what I used to code in Java, I'm not using BlueJay in college
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <iterator>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <stack>
#include <list>
#include <vector>
#include <queue>
using namespace std;
struct node {
    //position i, j, k = x, y, z
    int posX;
    int posY;
    int posZ;
    // 1 can move, 0 can not move, given in NESWUD
    int dirN; //North
    int dirE; //East
    int dirS; //South
    int dirW; //West
    int dirU; //Up
    int dirD; //Down
    string value;
    node* N;
    node* E;
    node* S;
    node* W;
    node* U;
    node* D;
    //Used for checking if used
    int visited;
};
string getKey(int x, int y, int z);
int hasAdjacentHere(node v, int i);
void DFS(map<string, node> map, node *v);
int l, r, c;
list<node> *adjList;
vector<node> vi;
int main()
{
    string inputName = "input.txt";
    string outputName = "output.txt";
    string line;
    ifstream inputFile;
    inputFile.open(inputName.c_str());
    if(!inputFile.is_open())
    {
        cout << "Unable to open file";
        return -1;
    }
    //int l, r, c; //levels, rows, columns
    int sx, sy, sz; //start location
    int ex, ey, ez; //end location
    //int numMazes;
    // >> works the same as .get() but it's easier to use >> when looking at the input.txt file. Loops = Cringe, >> = Easy
    //inputFile >> numMazes; //I hate cpp who looks at this and sees "ah yes this is ideal"
    //Number of mazes is no longer used as per announcement
    //for(int tempNum = 0; tempNum < numMazes; tempNum++)
    //{
    inputFile >> l;
    inputFile >> r; 
    inputFile >> c;
    inputFile >> sx;
    inputFile >> sy;
    inputFile >> sz;
    inputFile >> ex;
    inputFile >> ey;
    inputFile >> ez;
    //Testing of input
    cout << l << r << c << endl;
    cout << sx << sy << sz << endl;
    cout << ex  << ey << ez << endl;
    
    string tempString;
    map<string, node> map;

    //cout << "Made it here" << endl;
    list<node> adj_list[l*r*c];
    for(int i = 0; i < l; i++)
    {
        for(int j = 0; j < r; j++)
        {
            for(int k = 0; k < c; k++)
            {
                //cout << "Made it here" << endl;
                inputFile >> tempString;
                node neoNode;
                neoNode.posX = i;
                neoNode.posY = j;
                neoNode.posZ = k;
                neoNode.value = tempString;
                string key = to_string(i)+to_string(j)+to_string(k);
                
                if(tempString[0] == '0')
                {
                    //cout << "A0" << endl;
                    neoNode.dirN = 0;
                    //neoNode->N = NULL;
                }
                else if(tempString[0] == '1')
                {
                    //cout << "A1" << endl;
                    neoNode.dirN = 1;
                    //neoNode->N = map[i][j-1][k];
                }
                if(tempString[1] == '0')
                {
                    //cout << "B0" << endl;
                    neoNode.dirE = 0;
                    //neoNode->E = NULL;
                }
                else if(tempString[1] == '1')
                {
                    //cout << "B1" << endl;
                    neoNode.dirE = 1;
                    //cout << "AAAA";
                    //neoNode->E = map[i][j][k+1];
                    //cout << "AAAAAAAAAAA";
                }
                if(tempString[2] == '0')
                {
                    //cout << "C0" << endl;
                    neoNode.dirS = 0;
                    //neoNode->S = NULL;
                }
                else if(tempString[2] == '1')
                {
                    //cout << "C1" << endl;
                    neoNode.dirS = 1;
                    //neoNode->S = map[i][j+1][k];
                }
                if(tempString[3] == '0')
                {
                    //cout << "D0" << endl;
                    neoNode.dirW = 0;
                    //neoNode->W = NULL;
                }
                else if(tempString[3] == '1')
                {
                    //cout << "D1" << endl;
                    neoNode.dirW = 1;
                    //neoNode->W = map[i][j][k-1];
                }
                if(tempString[4] == '0')
                {
                    //cout << "E0" << endl;
                    neoNode.dirU = 0;
                    //neoNode->U = NULL;
                }
                else if(tempString[4] == '1')
                {
                    //cout << "E1" << endl;
                    neoNode.dirU = 1;
                    //neoNode->U = map[i+1][j][k];
                }
                if(tempString[5] == '0')
                {
                    //cout << "F0" << endl;
                    neoNode.dirD = 0;
                    //neoNode->D = NULL;
                }
                else if(tempString[5] == '1')
                {
                    //cout << "F1" << endl;
                    neoNode.dirD = 1;
                    //neoNode->D = map[i-1][j][k];
                }
                neoNode.visited = 0;
                map[key] = neoNode;
            }
            //cout << endl;
        }
        //cout << endl;
    }
    for(int i = 0; i < l; i++)
    {
        for(int j = 0; j < r; j++)
        {
            for(int k = 0; k < c; k++)
            {
                node tempV = map[getKey(i,j,k)];
                if(tempV.value[0] == 1)
                {
                    tempV.N = &map[getKey(i,j-1,k)];
                }
                if(tempV.value[1] == 1)
                {
                    tempV.E = &map[getKey(i,j,k+1)];
                }
                if(tempV.value[2] == 1)
                {
                    tempV.S = &map[getKey(i,j+1,k)];
                }
                if(tempV.value[3] == 1)
                {
                    tempV.W = &map[getKey(i,j,k-1)];
                }
                if(tempV.value[4] == 1)
                {
                    tempV.U = &map[getKey(i+1,j,k)];
                }
                if(tempV.value[5] == 1)
                {
                    tempV.D = &map[getKey(i-1,j,k)];
                }
            }
        }
    }

    //DFS(map, &map[getKey(sx,sy,sz)]);
    stack<node> S;
    stack<node> backNodes;
    node v = map[to_string(sx)+to_string(sy)+to_string(sz)];
    S.push(v);
    //cout << "Made it here" << endl;

    int curX = sx;
    int curY = sy;
    int curZ = sz;
    stack<string> output;
    vector<string> popedOff;
    while(!S.empty())
    {
        if(v.posX-1 == S.top().posX)
        {
            output.push("D");
        }
        else if(v.posX+1 == S.top().posX)
        {
            output.push("U");
        }
        else if(v.posY-1 == S.top().posY)
        {
            output.push("N");
        }
        else if(v.posY+1 == S.top().posY)
        {
            output.push("S");
        }
        else if(v.posZ-1 == S.top().posZ)
        {
            output.push("W");
        }
        else if(v.posZ+1 == S.top().posZ)
        {
            output.push("E");
        }
        v = S.top();
        curX = v.posX;
        curY = v.posY;
        curZ = v.posZ;
        //popedOff = v.;
        S.pop();
        if(v.posX == ex && v.posY == ey && v.posZ == ez)
        {
            return 0;
            stack<string> outputFlip;
            while(!output.empty())
            {
                outputFlip.push(output.top());
                output.pop();
            }
            while(!outputFlip.empty())
            {
                string a = outputFlip.top();
                cout << a << " ";
                outputFlip.pop();
            }
            cout << endl;
        }
        if(map[getKey(curX,curY,curZ)].visited == 0) // v is not labeled as discoverd
        {
            map[getKey(curX,curY,curZ)].visited = 1;
            if(v.dirN == 1)
            {
                //curY = curY - 1;
                if(map[getKey(curX,curY-1,curZ)].visited == 0)
                {
                    curY = curY - 1;
                    S.push(map[getKey(curX,curY,curZ)]);
                    cout << "N ";
                    output.push("N");
                    
                    curY = curY + 1;
                }
            }
            if(v.dirE == 1)
            {
                //curZ = curZ + 1;
                if(map[getKey(curX,curY,curZ+1)].visited == 0)
                {
                    curZ = curZ + 1;
                    S.push(map[getKey(curX,curY,curZ)]);
                    cout << "E ";
                    output.push("E");
                    curZ = curZ - 1;
                }
            }
            if(v.dirS == 1)
            {
                //curY = curY + 1;
                if(map[getKey(curX,curY+1,curZ)].visited == 0)
                {
                    curY = curY + 1;
                    S.push(map[getKey(curX,curY,curZ)]);
                    cout << "S ";
                    output.push("S");
                    curY = curY - 1;
                }
            }
            if(v.dirW == 1)
            {
                //curZ = curZ - 1;
                if(map[getKey(curX,curY,curZ-1)].visited == 0)
                {
                    curZ = curZ - 1;
                    S.push(map[getKey(curX,curY,curZ)]);
                    cout << "W ";
                    output.push("W");
                    curZ = curZ + 1;
                }
            }
            if(v.dirU == 1)
            {
                //curX = curX + 1;
                if(map[getKey(curX+1,curY,curZ)].visited == 0)
                {
                    curX = curX + 1;
                    S.push(map[getKey(curX,curY,curZ)]);
                    cout << "U ";
                    output.push("U");
                    curX = curX - 1;
                }
            }
            if(v.dirD == 1)
            {
                //curX = curX - 1;
                if(map[getKey(curX-1,curY,curZ)].visited == 0)
                {
                    curX = curX - 1;
                    S.push(map[getKey(curX,curY,curZ)]);
                    cout << "D ";
                    output.push("D");
                    curX = curX + 1;
                }
            }
        }
        //prevTemp = v;
    }
    return 0;
}

int hasAdjacentHere(node v, int i)
{
    if(i == 0)
    {
        return v.dirN;
    }
    else if(i == 1)
    {
        return v.dirE;
    }
    else if(i == 2)
    {
        return v.dirS;
    }
    else if(i == 3)
    {
        return v.dirW;
    }
    else if(i == 4)
    {
        return v.dirU;
    }
    else if(i == 5)
    {
        return v.dirD;
    }
    return 0;
}

string getKey(int x, int y, int z)
{
    return to_string(x)+to_string(y)+to_string(z);
}