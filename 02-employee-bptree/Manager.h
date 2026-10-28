#pragma once
#include "SelectionTree.h"
#include "BpTree.h"
#include <fstream>

class Manager {
private:
	char* cmd;
	BpTree* bptree;
	SelectionTree* stree;

public:
	Manager(int bpOrder) 
	{		//constructor
		cmd = new char[100];
		bptree = new BpTree(&flog, bpOrder); // order of the B+ tree (3 by default in main.cpp)
		stree = new SelectionTree(&flog);
	}


	~Manager() {				//destructor
		delete[] cmd;
		delete bptree;
		delete stree;
	}

	ifstream fin;
	ofstream flog;

	void run(const char* command);
	void LOAD();
	void ADD_BP();
	void SEARCH_BP_NAME(string name);
	void SEARCH_BP_RANGE(string start, string end);
	void PRINT_BP();
	void ADD_ST_DEPTNO(int dept_no);
	void ADD_ST_NAME(string name);
	void PRINT_ST();
	void DELETE();

	void printErrorCode(int n);
	void printSuccessCode(string success);
};

