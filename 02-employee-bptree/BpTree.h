#pragma once
#ifndef _BpTree_H_
#define _BpTree_H_

#include "BpTreeDataNode.h"
#include "BpTreeIndexNode.h"
#include "EmployeeData.h"
#include "SelectionTree.h"

#include<fstream>

class BpTree {
private:
	BpTreeNode* root;
	int	order;		// m children
	ofstream* fout;//to print log.txt

public:
	BpTree(ofstream *fout, int order = 3) 
	{
		this->order = order;
		this->fout = fout;
		this->root = nullptr;
	}
	
	~BpTree() 
	{
		destroy(root); // release every node and employee data
	}

	/* essential */
	bool		Insert(EmployeeData* newData);
	bool		excessDataNode(BpTreeNode* pDataNode);
	bool		excessIndexNode(BpTreeNode* pIndexNode);
	void		splitDataNode(BpTreeNode* pDataNode);
	void		splitIndexNode(BpTreeNode* pIndexNode);
	BpTreeNode* getRoot() { return root; }
	void		destroy(BpTreeNode* node);
	BpTreeNode* searchDataNode(string name);
	void		searchRange(string start, string end);


	//plus
	//bool search(string name);
};

#endif
