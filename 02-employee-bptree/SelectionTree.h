#pragma once
#include "SelectionTreeNode.h"

class SelectionTree {
private:
    SelectionTreeNode* root;
    ofstream* fout;
    SelectionTreeNode* run[8];

public:
    SelectionTree(ofstream* fout) 
    {
        this->fout = fout;
        root = nullptr;
        for (int i = 0; i < 8; i++) 
        {
            run[i] = nullptr;
        }
        setTree();
    }

    ~SelectionTree() {
        freeInner(root); // inner nodes (run nodes have no children)
        for (int i = 0; i < 8; i++)
        {
            delete run[i]; // each run owns its heap
        }
    }

    void freeInner(SelectionTreeNode* node)
    {
        if (node == nullptr) return;
        if (node->getLeftChild() == nullptr && node->getRightChild() == nullptr) return; // run node
        freeInner(node->getLeftChild());
        freeInner(node->getRightChild());
        delete node;
    }

    void setRoot(SelectionTreeNode* pN) { this->root = pN; }
    SelectionTreeNode* getRoot() { return root; }

    void setTree();

    bool Insert(EmployeeData* newData);
    bool Delete();
    bool printEmployeeData(int dept_no);
    void re_allocate(SelectionTreeNode* new_node);
};