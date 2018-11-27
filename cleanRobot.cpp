#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#define INT_MAX 9999

using namespace std;

struct AdjListNode{
    int dest;
    int weight;
    int row;
    int col;
    struct AdjListNode* next;
};
struct AdjList 
{ 
    struct AdjListNode *head;  // pointer to head node of list 
}; 
struct Graph 
{ 
    int V; 
    struct AdjList* array; 
};

struct AdjListNode* newAdjListNode(int dest, int weight, int row, int col) 
{ 
    struct AdjListNode* newNode = (struct AdjListNode*) malloc(sizeof(struct AdjListNode)); 
    newNode->dest = dest; 
    newNode->weight = weight;
    newNode->row = row;
    newNode->col = col;
    newNode->next = NULL; 
    return newNode; 
}

struct Graph* createGraph(int V) 
{ 
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph)); 
    graph->V = V; 
  
    // Create an array of adjacency lists.  Size of array will be V 
    graph->array = (struct AdjList*) malloc(V * sizeof(struct AdjList)); 
  
     // Initialize each adjacency list as empty by making head as NULL 
    for (int i = 0; i < V; ++i) 
        graph->array[i].head = NULL; 
  
    return graph; 
}
  
// Adds an edge to an undirected graph 
void addEdge(struct Graph* graph, int src, int dest, int weight, int col) 
{ 
    // Add an edge from src to dest.  A new node is added to the adjacency 
    // list of src.  The node is added at the begining 
    struct AdjListNode* newNode = newAdjListNode(dest, weight, dest / col, dest % col); 
    newNode->next = graph->array[src].head; 
    graph->array[src].head = newNode; 
  
    // Since graph is undirected, add an edge from dest to src also 
    newNode = newAdjListNode(src, weight, src / col, src % col); 
    newNode->next = graph->array[dest].head; 
    graph->array[dest].head = newNode; 
}

// Structure to represent a min heap node 
struct MinHeapNode 
{ 
    int  v; 
    int dist; 
}; 
  
// Structure to represent a min heap 
struct MinHeap 
{ 
    int size;      // Number of heap nodes present currently 
    int capacity;  // Capacity of min heap 
    int *pos;     // This is needed for decreaseKey() 
    struct MinHeapNode **array; 
}; 
  
// A utility function to create a new Min Heap Node 
struct MinHeapNode* newMinHeapNode(int v, int dist) 
{ 
    struct MinHeapNode* minHeapNode = 
           (struct MinHeapNode*) malloc(sizeof(struct MinHeapNode)); 
    minHeapNode->v = v; 
    minHeapNode->dist = dist; 
    return minHeapNode; 
} 
  
// A utility function to create a Min Heap 
struct MinHeap* createMinHeap(int capacity) 
{ 
    struct MinHeap* minHeap = 
         (struct MinHeap*) malloc(sizeof(struct MinHeap)); 
    minHeap->pos = (int *)malloc(capacity * sizeof(int)); 
    minHeap->size = 0; 
    minHeap->capacity = capacity; 
    minHeap->array = 
         (struct MinHeapNode**) malloc(capacity * sizeof(struct MinHeapNode*)); 
    return minHeap; 
} 
  
// A utility function to swap two nodes of min heap. Needed for min heapify 
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b) 
{ 
    struct MinHeapNode* t = *a; 
    *a = *b; 
    *b = t; 
} 
  
// A standard function to heapify at given idx 
// This function also updates position of nodes when they are swapped. 
// Position is needed for decreaseKey() 
void minHeapify(struct MinHeap* minHeap, int idx) 
{ 
    int smallest, left, right; 
    smallest = idx; 
    left = 2 * idx + 1; 
    right = 2 * idx + 2; 
  
    if (left < minHeap->size && 
        minHeap->array[left]->dist < minHeap->array[smallest]->dist ) 
      smallest = left; 
  
    if (right < minHeap->size && 
        minHeap->array[right]->dist < minHeap->array[smallest]->dist ) 
      smallest = right; 
  
    if (smallest != idx) 
    { 
        // The nodes to be swapped in min heap 
        MinHeapNode *smallestNode = minHeap->array[smallest]; 
        MinHeapNode *idxNode = minHeap->array[idx]; 
  
        // Swap positions 
        minHeap->pos[smallestNode->v] = idx; 
        minHeap->pos[idxNode->v] = smallest; 
  
        // Swap nodes 
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]); 
  
        minHeapify(minHeap, smallest); 
    } 
} 
  
// A utility function to check if the given minHeap is ampty or not 
int isEmpty(struct MinHeap* minHeap) 
{ 
    return minHeap->size == 0; 
} 
  
// Standard function to extract minimum node from heap 
struct MinHeapNode* extractMin(struct MinHeap* minHeap) 
{ 
    if (isEmpty(minHeap)) 
        return NULL; 
  
    // Store the root node 
    struct MinHeapNode* root = minHeap->array[0]; 
  
    // Replace root node with last node 
    struct MinHeapNode* lastNode = minHeap->array[minHeap->size - 1]; 
    minHeap->array[0] = lastNode; 
  
    // Update position of last node 
    minHeap->pos[root->v] = minHeap->size-1; 
    minHeap->pos[lastNode->v] = 0; 
  
    // Reduce heap size and heapify root 
    --minHeap->size; 
    minHeapify(minHeap, 0); 
  
    return root; 
} 
  
// Function to decreasy dist value of a given vertex v. This function 
// uses pos[] of min heap to get the current index of node in min heap 
void decreaseKey(struct MinHeap* minHeap, int v, int dist) 
{ 
    // Get the index of v in  heap array 
    int i = minHeap->pos[v]; 
  
    // Get the node and update its dist value 
    minHeap->array[i]->dist = dist; 
  
    // Travel up while the complete tree is not hepified. 
    // This is a O(Logn) loop 
    while (i && minHeap->array[i]->dist < minHeap->array[(i - 1) / 2]->dist) 
    { 
        // Swap this node with its parent 
        minHeap->pos[minHeap->array[i]->v] = (i-1)/2; 
        minHeap->pos[minHeap->array[(i-1)/2]->v] = i; 
        swapMinHeapNode(&minHeap->array[i],  &minHeap->array[(i - 1) / 2]); 
  
        // move to parent index 
        i = (i - 1) / 2; 
    } 
} 
  
// A utility function to check if a given vertex 
// 'v' is in min heap or not 
bool isInMinHeap(struct MinHeap *minHeap, int v) 
{ 
   if (minHeap->pos[v] < minHeap->size) 
     return true; 
   return false; 
} 
  
// A utility function used to print the solution 
void printArr(int dist[], int n) 
{ 
    printf("Vertex   Distance from Source\n"); 
    for (int i = 0; i < n; ++i) 
        printf("%d \t\t %d\n", i, dist[i]); 
} 
  
// The main function that calulates distances of shortest paths from src to all 
// vertices. It is a O(ELogV) function 
void dijkstra(struct Graph* graph, int src) 
{ 
    int V = graph->V;// Get the number of vertices in graph 
    int dist[V];      // dist values used to pick minimum weight edge in cut 
  
    // minHeap represents set E 
    struct MinHeap* minHeap = createMinHeap(V); 
  
    // Initialize min heap with all vertices. dist value of all vertices  
    for (int v = 0; v < V; ++v) 
    { 
        dist[v] = INT_MAX; 
        minHeap->array[v] = newMinHeapNode(v, dist[v]); 
        minHeap->pos[v] = v; 
    } 
  
    // Make dist value of src vertex as 0 so that it is extracted first 
    minHeap->array[src] = newMinHeapNode(src, dist[src]); 
    minHeap->pos[src]   = src; 
    dist[src] = 0; 
    decreaseKey(minHeap, src, dist[src]); 
  
    // Initially size of min heap is equal to V 
    minHeap->size = V; 
  
    // In the followin loop, min heap contains all nodes 
    // whose shortest distance is not yet finalized. 
    while (!isEmpty(minHeap)) 
    { 
        // Extract the vertex with minimum distance value 
        struct MinHeapNode* minHeapNode = extractMin(minHeap); 
        int u = minHeapNode->v; // Store the extracted vertex number 
  
        // Traverse through all adjacent vertices of u (the extracted 
        // vertex) and update their distance values 
        struct AdjListNode* pCrawl = graph->array[u].head; 
        while (pCrawl != NULL) 
        { 
            int v = pCrawl->dest; 
  
            // If shortest distance to v is not finalized yet, and distance to v 
            // through u is less than its previously calculated distance 
            if (isInMinHeap(minHeap, v) && dist[u] != INT_MAX &&  
                                          pCrawl->weight + dist[u] < dist[v]) 
            { 
                dist[v] = dist[u] + pCrawl->weight; 
  
                // update distance value in min heap also 
                decreaseKey(minHeap, v, dist[v]); 
            } 
            pCrawl = pCrawl->next; 
        } 
    } 
  
    // print the calculated shortest distances 
    printArr(dist, V); 
}

int main(int argc, char *argv[]){

    int row=0, col=0, battery=0;
    int rechargeNode = 0;
    int nodeNum = 0;

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
        struct Graph* graph = createGraph(V);

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
                        addEdge(graph, nodeNum, (nodeNum - 1), 1, col);
                        //*****************
                    }

                    if (isFirstLine){ //first line doesn't need to compare with upper line
                        isFirstLine = false;
                    }
                    else if (lineRecord[index] == "R" || stoi(lineRecord[index]) == 0){ //second line after
                        //add Edge to graph
                        // upper nodeNUm = nodeNum - col
                        addEdge(graph, nodeNum, (nodeNum - col), 1, col);
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

        dijkstra(graph, rechargeNode);
    }
    else {
        /*cerr << "unable to open input file";
        return -1;*/
        cout << "Unable to open file." << endl;
    }
    mapFile.close();

    //*****path finding alogorithm*****

    

    //*****file output*****
    ofstream pathFile;
    string outputFilePath = ".\\" + studentNum + "\\final.path";
    pathFile.open(outputFilePath);
    pathFile << "test" << endl; //output anwser
    pathFile.close();

    return 0;
}