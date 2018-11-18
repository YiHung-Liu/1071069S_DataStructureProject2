#include <stdio.h>
#include <iostream>
#include <fstream>

using namespace std;

class node{
    int row;
    int col;
    int dist; //distance to root
};

void createGraph(void){

    return;
}

int main(int argc, char *argv[]){

    //*****file input*****
    string studentNum = argv[1];
    string filePath = ".\\" + studentNum + "\\matrix.data";

    ifstream mapFile;
    mapFile.open(filePath);

    //*****transfer matrix to graph*****



    createGraph();

    //*****path finding alogorithm*****

    

    //*****file output*****
    ofstream pathFile;
    string outputFilePath = ".\\" + studentNum + "\\peak.final";
    pathFile.open(outputFilePath);
    pathFile << endl; //output anwser
    pathFile.close();

    return 0;
}