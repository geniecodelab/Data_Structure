#pragma once
#include "EmployeeHeap.h"

void EmployeeHeap::Insert(EmployeeData* data) 
{
    //max heap insertion
    if (datanum == maxCapacity) // if heap is full?
    {
        ResizeArray();//double size
    }
    //increase num--> starts in 0
    datanum++;

    //make root
    if (heapArr[1] == nullptr)
    {
        heapArr[1] = data;
        return;
    }
    
    
    //insert
    heapArr[datanum] = data;
    //re-struct
    UpHeap(datanum);
    
}

EmployeeData* EmployeeHeap::Top() 
{
    if (IsEmpty() == true)//no node
    {
        return nullptr;
    }
    else 
    {
        return heapArr[1];
    }
   
}

void EmployeeHeap::Delete() 
{
    if(IsEmpty())//nothing
    {
        return;
    }
    //duplicate 1index
    heapArr[1] = heapArr[datanum];
    heapArr[datanum] = nullptr;
    datanum--;
    //re compare until getting last or not change
    DownHeap(1);
}

bool EmployeeHeap::IsEmpty() 
{
    if (datanum == 0) 
    {
        return true;
    }
    else
    {
        return false;
    }
}

void EmployeeHeap::UpHeap(int index) 
{
//end repaet
 if(index<= 1)
 {
     return;
 }

//should it move?
    if (heapArr[index]->getIncome()>heapArr[index / 2]->getIncome())
    {
        //change location
        EmployeeData* imsi = heapArr[index / 2];
        heapArr[index / 2] = heapArr[index];
        heapArr[index] = imsi;
        //move to parent
        index = index / 2;
        //repeat
        UpHeap(index);
    }

}

void EmployeeHeap::DownHeap(int index)
{

  //is it compare?
    int imsi_index = index;
    //case 1) left is in
    if (index * 2 <= datanum && heapArr[imsi_index]->getIncome() < heapArr[index * 2]->getIncome()) 
    {
        imsi_index = index * 2;
    }
    //case2) right is in +  //case3) left,right is in
    if (index * 2+1 <= datanum && heapArr[imsi_index]->getIncome() < heapArr[index * 2+1]->getIncome())
    {
        imsi_index = index * 2 + 1;
    }
   
    //call function + end repaet
    if(imsi_index!=index)//does it change
    {
        //change
        EmployeeData* imsi_heap=heapArr[imsi_index];
        heapArr[imsi_index] = heapArr[index];
        heapArr[index] = imsi_heap;
       //new index
        index = imsi_index;
        //repeat
        DownHeap(index);
    }

}

void EmployeeHeap::ResizeArray() 
{
 
    //imsi array
    //double size
    maxCapacity = maxCapacity * 2;
    EmployeeData** imsi=new EmployeeData*[maxCapacity+1];
    for (int i = 1; i <= datanum; i++) 
    {
        imsi[i] = heapArr[i];
    }
   
    delete[] heapArr;
    heapArr = imsi;
  
}


void  EmployeeHeap::selection_print(ofstream*fout)//new-> for insert
{
    // make copy
    EmployeeHeap tempHeap(*this);

    *fout << "========PRINT_ST========" << endl;

    //repeat when empty
    while (!tempHeap.IsEmpty())
    {
        //bring most income
        EmployeeData* imsi = tempHeap.Top();

        //delete top and rearrane
        tempHeap.Delete();

        // print
        *fout << imsi->getName() << "/";
        *fout << imsi->getDeptNo() << "/";
        *fout << imsi->getID() << "/";
        *fout << imsi->getIncome() << endl;
    }
    *fout << "=======================" << endl << endl;

    // 함수가 종료되면 'tempHeap'은 자동으로 소멸자를 호출하여 
    // '복사본'의 heapArr 메모리만 해제합니다. (원본은 안전함)
   
    
}


//new, for copy heap
EmployeeHeap::EmployeeHeap(const EmployeeHeap& other) {
    this->maxCapacity = other.maxCapacity;
    this->datanum = other.datanum;

    // allocate memory
    this->heapArr = new EmployeeData * [this->maxCapacity + 1];

    // copy from original version
    for (int i = 1; i <= this->datanum; i++) {
        this->heapArr[i] = other.heapArr[i];
    }
    this->heapArr[0] = nullptr; //not use 0 index
}