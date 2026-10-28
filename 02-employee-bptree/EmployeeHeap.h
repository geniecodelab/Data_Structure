#pragma once

#include "EmployeeData.h"
#include<fstream>
class EmployeeHeap {
private:
    int datanum;
    EmployeeData** heapArr;
    int maxCapacity = 10;

public:
    EmployeeHeap() 
    {
        datanum = 0;//tree node count
        heapArr =new  EmployeeData * [maxCapacity+1];//not use index 0
    }
    ~EmployeeHeap() 
    {
        delete[] heapArr;//destruct
    }
   
    void Insert(EmployeeData* data);
    EmployeeData* Top();
    void Delete();

    bool IsEmpty();

    void UpHeap(int index);
    void DownHeap(int index);
    void ResizeArray();
    //additional 
    EmployeeHeap(const EmployeeHeap& other); // for copy heap
    void selection_print(ofstream* fout);
};