#include "SelectionTree.h"

void SelectionTree::setTree() 
{
 //generate inner
    SelectionTreeNode* inner_node_1 = new SelectionTreeNode;
    SelectionTreeNode* inner_node_2 = new SelectionTreeNode;
    SelectionTreeNode* inner_node_3 = new SelectionTreeNode;
    SelectionTreeNode* inner_node_4 = new SelectionTreeNode;
    SelectionTreeNode* inner_node_5 = new SelectionTreeNode;
    SelectionTreeNode* inner_node_6 = new SelectionTreeNode;
    SelectionTreeNode* inner_node_7 = new SelectionTreeNode;
//generate run
    for (int i = 0; i < 8; i++)
    {
       
        this->run[i] = new SelectionTreeNode;//allocate memory
        this->run[i]->HeapInit();//allocate each heap
    }

 //link inner_node
    this->root = inner_node_1;
    inner_node_1->setLeftChild(inner_node_2);
    inner_node_1->setRightChild(inner_node_3);

    inner_node_2->setParent(inner_node_1);
    inner_node_2->setLeftChild(inner_node_4);
    inner_node_2->setRightChild(inner_node_5);

    inner_node_3->setParent(inner_node_1);
    inner_node_3->setLeftChild(inner_node_6);
    inner_node_3->setRightChild(inner_node_7);

    inner_node_4->setParent(inner_node_2);
    inner_node_5->setParent(inner_node_2);
    inner_node_6->setParent(inner_node_3);
    inner_node_7->setParent(inner_node_3);

    //link leaf node--> run
    this->run[0]->setParent(inner_node_4);
    this->run[1]->setParent(inner_node_4);
    inner_node_4->setLeftChild(run[0]);//heap 100
    inner_node_4->setRightChild(run[1]);//heap 200

    this->run[2]->setParent(inner_node_5);
    this->run[3]->setParent(inner_node_5);
    inner_node_5->setLeftChild(run[2]);//heap 300
    inner_node_5->setRightChild(run[3]);//heap 400

    this->run[4]->setParent(inner_node_6);
    this->run[5]->setParent(inner_node_6);
    inner_node_6->setLeftChild(run[4]);//heap 500
    inner_node_6->setRightChild(run[5]);//heap 600

    this->run[6]->setParent(inner_node_7);
    this->run[7]->setParent(inner_node_7);
    inner_node_7->setLeftChild(run[6]);//heap 700
    inner_node_7->setRightChild(run[7]);//heap 800
}

void SelectionTree::re_allocate(SelectionTreeNode* new_node)//new_function for insert-> insert first or new heap root
{
    //get parent
    SelectionTreeNode* imsi_parent = new_node->getParent();

    //end if doesnt have parent-> when arrive at root
    if(imsi_parent==nullptr)
    {
        return;
    }

    //compare child income
    SelectionTreeNode* left = imsi_parent->getLeftChild();
    SelectionTreeNode* right = imsi_parent->getRightChild();
    EmployeeData* imsi_winner;
    if (left->getEmployeeData() != nullptr && right->getEmployeeData() != nullptr) //already have
    {
        if (left->getEmployeeData()->getIncome() > right->getEmployeeData()->getIncome()) //left>right
        {
           
            
            imsi_winner = left->getEmployeeData();
         
            

        }
        else //right>left
        {
            imsi_winner = right->getEmployeeData();
          
        }
    }
    else 
    {
        if (left->getEmployeeData() != nullptr)//only left 
        {
            imsi_winner = left->getEmployeeData();
               
        }
        else//only right
        {
            imsi_winner = right->getEmployeeData();
           
        }
    }
    if (imsi_winner == imsi_parent->getEmployeeData()) //dpes not changed
    {
        return;

    }
    imsi_parent->setEmployeeData(imsi_winner);


    //recall
    new_node = imsi_parent;
    re_allocate(new_node);


}


bool SelectionTree::Insert(EmployeeData* newData) 
{
 //get code
    int code = newData->getDeptNo();
    code = code / 100 - 1;//get index num
    if (code == -1)return false;
//inset heap
    EmployeeData* before=run[code]->getHeap()->Top();//before top
    run[code]->getHeap()->Insert(newData);
    EmployeeData* after= run[code]->getHeap()->Top();//after insert top
//renew top root
    if(before!=nullptr&&before->getIncome()==after->getIncome())//exist and does not change  
    {
        return true;//exist node-> does not need re_allocate
    }
    
    //insert
    run[code]->setEmployeeData(after);

    //reallocate
    re_allocate(run[code]);
    return true;
}

bool SelectionTree::Delete() 
{
    //is root ok?
    if (root->getEmployeeData() == nullptr)
    {
        return false;
    }
    //which heap?
    int run_num = root->getEmployeeData()->getDeptNo();
    int real_run = run_num / 100 - 1;
    //delete heap top(reallocate)
    run[real_run]->getHeap()->Delete();
    EmployeeData* new_run=run[real_run]->getHeap()->Top();//getting new
    //reallocate run num
    run[real_run]->setEmployeeData(new_run);
    re_allocate(run[real_run]);
    return true;
}

bool SelectionTree::printEmployeeData(int dept_no) //print all dept
{
    //select run
    int loc = dept_no / 100 - 1;
    if (loc < 0 || loc>7) { return false; }
    //if empty
    if (run[loc]->getHeap() == nullptr) 
    {
        return false;
    }

   if (run[loc]->getHeap()->Top() == nullptr) 
    {
        return false;
    }
    //print top, and delete
    run[loc]->getHeap()->selection_print(fout);
    return true;
}