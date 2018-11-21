#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <vector>

using namespace std;

struct AdjListNode{
    int dest;
    int weight;
    struct AdjListNode* next;
};

class Node{
    int row;
    int col;
    int dist; //distance to root
};

int main(int argc, char *argv[]){

    int row=0, col=0, battery=0;


    //*****file input & creat graph*****
    string studentNum = argv[1];
    string filePath = ".\\" + studentNum + "\\matrix.data";
    string firstLine; //get matrix info: row, col, battery
    string matrixString; //get matrix

    ifstream mapFile;
    mapFile.open(filePath);

    if (mapFile.is_open()){

        for (int i=0; i<3; i++){
            getline(mapFile, firstLine, ' ');
            if (i = 0) row = stoi(firstLine);
            else if (i = 1) col = stoi(firstLine);
            else battery = stoi(firstLine);
        }

        string *lineRecord = new string[col]; //record the line after visited
        bool isFirstLine = true;

        while (getline(mapFile, matrixString)){
            istringstream ss(matrixString);
            string token;

            int index = 0; //index of lineRecord
            bool isFirstToken = true;

            while (getline(ss, token, ' ')){

                if (token == "R" || stoi(token) == 0 ){ //paths to go

                    //add Node into adjList
                    //record: row, col, nodeNumber
                    //**********************

                    if (isFirstToken){
                        isFirstToken = false;
                    }
                    else if (stoi(lineRecord[index-1]) == 0 || lineRecord[index] == "R"){ //if predeccessor == 0 -> is connected
                        //add Edge to graph
                        //
                        //*****************
                    }

                    if (isFirstLine){ //first line doesn't need to compare with upper line
                        isFirstLine = false;
                    }
                    else if (stoi(lineRecord[index]) == 0 || lineRecord[index] == "R"){ //second line after
                        //add Edge to graph
                        //
                        //*****************
                    }
                }
                else{ //walls
                    //do nothing
                }

                lineRecord[index] = token;
                index++;
            }
        }
        delete []lineRecord;
    }
    else {
        cerr << "unable to open input file";
        return -1;
    }

    //*****path finding alogorithm*****

    

    //*****file output*****
    ofstream pathFile;
    string outputFilePath = ".\\" + studentNum + "\\peak.final";
    pathFile.open(outputFilePath);
    pathFile << endl; //output anwser
    pathFile.close();

    return 0;
}