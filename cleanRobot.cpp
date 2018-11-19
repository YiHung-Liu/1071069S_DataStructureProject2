#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>

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

    int row=0, col=0, battery=0;


    //*****file input*****
    string studentNum = argv[1];
    string filePath = ".\\" + studentNum + "\\matrix.data";
    string firstLine; //get matrix info: row, col, battery
    string matrixString; //get matrix

    vector< vector<int> > matrix(row);

    ifstream mapFile;
    mapFile.open(filePath);

    if (mapFile.is_open()){
        for (int i=0; i<3; i++){
            getline(mapFile, firstLine, ' ');
            if (i = 0) row = stoi(firstLine);
            else if (i = 1) col = stoi(firstLine);
            else battery = stoi(firstLine);
        }

        while (getline(mapFile, matrixString)){

        }
    }
    else {
        cerr << "unable to open input file";
        return -1;
    }

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