#include <stdio.h>
#include <stdlib.h>
#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#define INF 0x3f3f3f3f

using namespace std;

class Graph{
    int V; //Number of vertices
    list< pair<int, int> > *adj;

public:
    void createGraph(int V);
    void addEdge(int u, int v, int w = 1);
    void deleteEdge(int u, int v);
    
    vector<pair<int, int>> dijkstra(int src);
};

void Graph::createGraph(int V){
    this->V = V;
    adj = new list< pair<int, int> >[V];
}

void Graph::addEdge(int u, int v, int w){
    adj[u].push_back(make_pair(v, w));
    adj[v].push_back(make_pair(u, w));
}

void Graph::deleteEdge(int u, int v){
    list< pair<int, int> >::iterator i;
    for (i = adj[u].begin(); i != adj[u].end(); ++i){
        if ( (*i).first == v )
            i = adj[u].erase(i);
    }
    list< pair<int, int> >::iterator j; 
    for (j = adj[v].begin(); j != adj[v].end(); ++j){
        if ( (*j).first == u )
            j = adj[v].erase(j);
    }
}

bool sortbysec(const pair<int,int> &a, const pair<int,int> &b){ 
    return (a.second > b.second); 
} 

vector<pair<int, int>> Graph::dijkstra(int src)
{ 
    // Create a set to store vertices that are being 
    // prerocessed 
    set< pair<int, int> > setds; 
  
    // Create a vector for distances and initialize all 
    // distances as infinite (INF) 
    vector<int> dist(V, INF); 
  
    // Insert source itself in Set and initialize its 
    // distance as 0. 
    setds.insert(make_pair(0, src)); 
    dist[src] = 0; 
  
    /* Looping till all shortest distance are finalized 
       then setds will become empty */
    while (!setds.empty()) 
    { 
        // The first vertex in Set is the minimum distance 
        // vertex, extract it from set. 
        pair<int, int> tmp = *(setds.begin()); 
        setds.erase(setds.begin()); 
  
        // vertex label is stored in second of pair (it 
        // has to be done this way to keep the vertices 
        // sorted distance (distance must be first item 
        // in pair) 
        int u = tmp.second; 
  
        // 'i' is used to get all adjacent vertices of a vertex 
        list< pair<int, int> >::iterator i; 
        for (i = adj[u].begin(); i != adj[u].end(); ++i) 
        { 
            // Get vertex label and weight of current adjacent 
            // of u. 
            int v = (*i).first; 
            int weight = (*i).second; 
  
            //  If there is shorter path to v through u. 
            if (dist[v] > dist[u] + weight) 
            { 
                /*  If distance of v is not INF then it must be in 
                    our set, so removing it and inserting again 
                    with updated less distance.   
                    Note : We extract only those vertices from Set 
                    for which distance is finalized. So for them,  
                    we would never reach here.  */
                if (dist[v] != INF) 
                    setds.erase(setds.find(make_pair(dist[v], v))); 
  
                // Updating distance of v 
                dist[v] = dist[u] + weight; 
                setds.insert(make_pair(dist[v], v)); 
            } 
        } 
    } 
  
    int num = 0;
    vector<pair<int, int>> newDist;
    // Print shortest distances stored in dist[] 
    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < V; ++i){
        if (dist[i] < INF){
            //printf("%d \t\t %d\n", i, dist[i]);
            newDist.push_back(make_pair(i, dist[i]));
            num++;
        }
    }

    sort(newDist.begin(), newDist.end(), sortbysec);

    for (int i = 0; i < num; ++i){
        printf("%d \t\t %d\n", newDist[i].first, newDist[i].second);
    }

    return newDist;
} 

bool isInVec(vector<pair<int, int>> dist, int index){
    vector<pair<int, int>>::iterator it;
    int i = 0;
    for (it = dist.begin() ; it != dist.end(); ++it){
        if (dist[i].first == index)
            return true;
        i++;
    }
    return false;
}

int main(int argc, char *argv[]){

    int row=0, col=0, battery=0;
    int rechargeNode = 0;
    int nodeNum = 0;
    vector<pair<int, int>> dist;
    Graph graph;

    //*****file input & creat graph*****
    string studentNum = argv[1];
    string filePath = ".\\" + studentNum + "\\floor.data";
    //filePath = ".\\floorCleaner\\1071070s\\floor.data";  //for debug
    string firstLine; //get matrix info: row, col, battery
    string matrixString; //get matrix

    ifstream mapFile(filePath);

    if (mapFile.is_open()){

        getline(mapFile, firstLine);
        istringstream ssInfo(matrixString);
        string info;
        for (int i=0; i<3; i++){
            ssInfo >> info;
            if (i == 0) row = stoi(firstLine);
            else if (i == 1) col = stoi(firstLine);
            else battery = stoi(firstLine);
        }

        string *lineRecord = new string[col]; //record the line after visited
        bool isFirstLine = true;

        int V = row * col;
        graph.createGraph(V);

        int currentRow = 0;

        while (getline(mapFile, matrixString)){
            istringstream ss(matrixString);
            string token;

            int index = 0; //index of lineRecord
            bool isFirstToken = true;
            int currentCol = 0;

            while (ss >> token){ //getline(ss, token, ' ')
                if (token == "R" || stoi(token) == 0 ){ //paths to go
                    
                    if (token == "R"){
                        rechargeNode = nodeNum;
                    }

                    if (isFirstToken){
                        isFirstToken = false;
                    }
                    else if (lineRecord[index-1] == "R" || stoi(lineRecord[index-1]) == 0){ //if predeccessor == 0 -> is connected
                        //add Edge to graph
                        //predeccessor nodeNum = nodeNum - 1
                        graph.addEdge(nodeNum, (nodeNum - 1));
                        //*****************
                    }

                    if (isFirstLine){ //first line doesn't need to compare with upper line
                        isFirstLine = false;
                    }
                    else if (lineRecord[index] == "R" || stoi(lineRecord[index]) == 0){ //second line after
                        //add Edge to graph
                        // upper nodeNUm = nodeNum - col
                        graph.addEdge(nodeNum, (nodeNum - col));
                        //*****************
                    }
                }
                else{ //walls
                    if(isFirstToken)
                        isFirstToken = false;
                }

                nodeNum++; //record node number, start from 0

                currentCol++;

                lineRecord[index] = token;
                index++;
            }
            if (isFirstLine)
                isFirstLine = false;
            currentRow++;
        }
        delete []lineRecord;

        dist = graph.dijkstra(rechargeNode);
    }
    else {
        /*cerr << "unable to open input file";
        return -1;*/
        cout << "Unable to open file." << endl;
    }
    mapFile.close();

    //*****path finding alogorithm*****

    if (isInVec(dist, 22))
        printf("yes\n");
    else
        printf("no\n");

    int V = 0;//dist.size;
    bool *visited = new bool[V]; 
    stack<int> path;

    for(int i = 0; i < V; i++){
        visited[i] = false;
    }

    /*list<int> queue; 
    while (!queue.empty()){

    }*/
    int index = 0;
    if (index != rechargeNode){
        visited[index] = true;
        path.push(index);
        graph.deleteEdge(dist[index].first, dist[index+1].first);
        graph.dijkstra(rechargeNode);
    }

    //*****file output*****
    ofstream pathFile;
    string outputFilePath = ".\\" + studentNum + "\\final.path";
    pathFile.open(outputFilePath);
    pathFile << "test" << endl; //output anwser
    pathFile.close();

    return 0;
}