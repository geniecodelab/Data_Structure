#include "Manager.h"
#include "GraphMethod.h"
#include "ListGraph.h"
#include "MatrixGraph.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

Manager::Manager()
{
    graph = nullptr;
    fout.open("log.txt", ios::out); // open initial mode
    load = 0;
}

Manager::~Manager()
{
    if (load && graph)
        delete graph;
    if (fout.is_open())
        fout.close();
}

void Manager::run(const char* command_txt) {
    ifstream fin;
    fin.open(command_txt, ios_base::in);

    if (!fin) {
        fout << "command file open error" << endl;
        return;
    }

    string line;
    while (getline(fin, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string cmd;
        ss >> cmd;

        if (cmd == "LOAD") {
            string filename, junk;
            if (ss >> filename) {
                if (ss >> junk) printErrorCode(100);
                else if (!LOAD(filename.c_str())) printErrorCode(100);
            }
            else printErrorCode(100);
        }
        else if (cmd == "PRINT") {
            string junk;
            if (ss >> junk) printErrorCode(200);
            else if (!PRINT()) printErrorCode(200);
        }
        else if (cmd == "BFS") {
            char op; int v; string junk;
            if (ss >> op >> v) {
                if (ss >> junk) printErrorCode(300);
                else if (!mBFS(op, v)) printErrorCode(300);
            }
            else printErrorCode(300);
        }
        else if (cmd == "DFS") {
            char op; int v; string junk;
            if (ss >> op >> v) {
                if (ss >> junk) printErrorCode(400);
                else if (!mDFS(op, v)) printErrorCode(400);
            }
            else printErrorCode(400);
        }
        else if (cmd == "KRUSKAL") {
            string junk;
            if (ss >> junk) printErrorCode(500);
            else if (!mKRUSKAL()) printErrorCode(500);
        }
        else if (cmd == "DIJKSTRA") {
            char op; int v; string junk;
            if (ss >> op >> v) {
                if (ss >> junk) printErrorCode(600);
                else if (!mDIJKSTRA(op, v)) printErrorCode(600);
            }
            else printErrorCode(600);
        }
        else if (cmd == "BELLMANFORD") {
            char op; int s, e; string junk;
            if (ss >> op >> s >> e) {
                if (ss >> junk) printErrorCode(700);
                else if (!mBELLMANFORD(op, s, e)) printErrorCode(700);
            }
            else printErrorCode(700);
        }
        else if (cmd == "FLOYD") {
            char op; string junk;
            if (ss >> op) {
                if (ss >> junk) printErrorCode(800);
                else if (!mFLOYD(op)) printErrorCode(800);
            }
            else printErrorCode(800);
        }
        else if (cmd == "CENTRALITY") {
            string junk;
            if (ss >> junk) printErrorCode(900);
            else if (!mCentrality()) printErrorCode(900);
        }
        else if (cmd == "EXIT") {
            fout << "========EXIT========" << endl;
            fout << "Success" << endl;
            fout << "====================" << endl;
            break;
        }
    }
    fin.close();
}

bool Manager::LOAD(const char* filename)
{
    ifstream gFile(filename);
    if (!gFile.is_open()) return false; //no file

    
    //delete existing graph and initialize
    if (graph != nullptr) {
        delete graph;
        graph = nullptr;
        load = 0;
    }

    char typeChar;
    int size;

    // read header
    string line;
    if (!getline(gFile, line)) return false;
    stringstream ssType(line);
    ssType >> typeChar;

    if (!getline(gFile, line)) return false;
    stringstream ssSize(line);
    ssSize >> size;

    if (typeChar == 'L') {
        graph = new ListGraph(false, size);
        graph->setOfstream(&fout); //connect ofstream

        int currentSrc = -1;
        while (getline(gFile, line)) {
            if (line.empty()) continue;

            stringstream ss(line);
            vector<int> numbers;
            int num;
            while (ss >> num) {
                numbers.push_back(num);
            }

            if (numbers.empty()) continue;

            // if num>1 new start
            if (numbers.size() == 1) {
                currentSrc = numbers[0];
            }
            
            // many num== edge data
            else {
                if (currentSrc != -1) {
                    for (size_t i = 0; i < numbers.size(); i += 2) {
                        if (i + 1 < numbers.size()) {
                            int dst = numbers[i];
                            int weight = numbers[i + 1];
                            graph->insertEdge(currentSrc, dst, weight);
                        }
                    }
                }
            }
        }
    }
    else if (typeChar == 'M') {
        graph = new MatrixGraph(true, size);
        graph->setOfstream(&fout); //connect ofstream

        for (int i = 0; i < size; i++) {
           
            //read maxtrix step by step
            for (int j = 0; j < size; j++) {
                int weight;
                gFile >> weight;
                if (weight != 0) {
                    graph->insertEdge(i, j, weight);
                }
            }
        }
    }
    else {
        gFile.close();
        return false;
    }

    gFile.close();
    load = 1;

    fout << "========LOAD========" << endl;
    fout << "Success" << endl;
    fout << "====================" << endl << endl;

    return true;
}

bool Manager::PRINT()
{
    if (!graph) return false;
    fout << "========PRINT========" << endl;
    graph->printGraph(&fout);
    fout << "=====================" << endl << endl;
    return true;
}

// call function in graphmethod
bool Manager::mBFS(char option, int vertex)
{
    if (!graph) return false;
    return BFS(graph, option, vertex);
}

bool Manager::mDFS(char option, int vertex)
{
    if (!graph) return false;
    return DFS(graph, option, vertex);
}

bool Manager::mDIJKSTRA(char option, int vertex)
{
    if (!graph) return false;
    return Dijkstra(graph, option, vertex);
}

bool Manager::mKRUSKAL()
{
    if (!graph) return false;
    return Kruskal(graph);
}

bool Manager::mBELLMANFORD(char option, int s_vertex, int e_vertex)
{
    if (!graph) return false;
    return Bellmanford(graph, option, s_vertex, e_vertex);
}

bool Manager::mFLOYD(char option)
{
    if (!graph) return false;
    return FLOYD(graph, option);
}

bool Manager::mCentrality() {
    if (!graph) return false;
    return Centrality(graph);
}

void Manager::printErrorCode(int n)
{
    fout << "========ERROR========" << endl;
    fout << n << endl;
    fout << "=====================" << endl << endl;
}