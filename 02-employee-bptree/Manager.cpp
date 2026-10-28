#include "Manager.h"
#include<iostream>
#include <sstream>
#include <cstring>
//#include<string>

void Manager::run(const char* command) 
{
	//fopen
	fin.open("command.txt");
	flog.open("log.txt");
	stringstream for_imsi_cmd;
	//read
	if (!fin.is_open()) 
	{
		cout << "not open";
		printErrorCode(100);//get error
		return;
	}
	
	while(fin >> cmd)//to cmd, max 100 until enter.
	{
		
		if (strcmp(cmd,"LOAD")==0)
		{
			LOAD();
		}
		else if (strcmp(cmd,"ADD_BP")==0)
		{
			ADD_BP();
		}
		else if (strcmp(cmd, "SEARCH_BP")==0)
		{
			string line;
			getline(fin, line); // read the rest of this command line
			stringstream figure(line); // to parse the arguments
			string first, second, extra;

			if (bptree->getRoot() == nullptr) // error: no data in the tree
			{
				printErrorCode(300);
			}
			else if (!(figure >> first)) // error: no argument
			{
				printErrorCode(300);
			}
			else if (figure >> second) // two arguments: range search
			{
				if (figure >> extra) printErrorCode(300); // error: too many arguments
				else SEARCH_BP_RANGE(first, second);
			}
			else // one argument: name search
			{
				SEARCH_BP_NAME(first);
			}
		}
		else if (strcmp(cmd, "PRINT_BP") == 0)
		{
			PRINT_BP();
			
		}
		else if (strcmp(cmd, "ADD_ST") == 0)
		{
			string line;
			getline(fin, line); // read the rest of this command line
			stringstream figure(line);
			string kind, value, extra;

			if (!(figure >> kind >> value) || (figure >> extra)) // missing or too many arguments
			{
				printErrorCode(500);
			}
			else if (kind == "dept_no")
			{
				ADD_ST_DEPTNO(atoi(value.c_str())); // ascii to integer
			}
			else if (kind == "name")
			{
				ADD_ST_NAME(value);
			}
			else // unknown argument
			{
				printErrorCode(500);
			}
		}
		else if(strcmp(cmd, "PRINT_ST") == 0)
		{
			PRINT_ST();
		}
		else if (strcmp(cmd, "DELETE") == 0) 
		{
			DELETE();
		}
		else if (strcmp(cmd, "EXIT") == 0)
		{
			printSuccessCode("EXIT");
			fin.close();
			flog.close();
			return;
		}
		else 
		{
			//wrong code.
			//shut down program
			printErrorCode(800);
			char discard[256];//disregard command
			fin.getline(discard, 256);
		}


	}
	
}

void Manager::LOAD() 
{
	ifstream for_employee("employee.txt"); // 파일 열기
	if (!for_employee.is_open()) //not open
	{
		printErrorCode(100);
		return;
	}

	if (bptree->getRoot() != nullptr)//already load 
	{
		printErrorCode(100);
		return;
	}

	string name;
	int dept_no, id, income;

	// 한 줄씩 읽으며 파싱
	while (for_employee >> name >> dept_no >> id >> income) {
		EmployeeData* emp = new EmployeeData();
		emp->setData(name, dept_no, id, income);
		

		if (bptree->Insert(emp))// insert 
		{

		}
		else // something goes wrong
		{
			printErrorCode(100);
			return;
		}
	}

	
	for_employee.close();
	printSuccessCode("LOAD");
}


void Manager::ADD_BP() 
{
	string line;
	getline(fin, line); // read the rest of this command line (tab separated)
	stringstream figure(line);
	string name, extra;
	int dept_no, id, income;
	// all four arguments must exist and nothing may follow them
	if ((figure >> name >> dept_no >> id >> income) && !(figure >> extra))
	{
		//insert
		EmployeeData* emp = new EmployeeData();
		emp->setData(name, dept_no, id, income);
		bptree->Insert(emp);
		// print result
		flog << "========ADD_BP========" << endl;
		flog << name << "/" << dept_no << "/" << id << "/" << income << endl;
		flog << "====================\n\n";
	}
	else // wrong number of arguments
	{
		printErrorCode(200);
	}
}

void Manager::SEARCH_BP_NAME(string name) 
{
	BpTreeNode* new_target = bptree->searchDataNode(name);

	

	//find node
	if (new_target==nullptr) //error 3-> no man or no tree
	{
		printErrorCode(300);
		return;
	}
	else 
	{
		//find_map and iterator
		map<string, EmployeeData*>* find_map=new_target->getDataMap();
		map<string, EmployeeData*>::iterator it = find_map->find(name);

		//print
		if (it!=find_map->end()) 
		{
			//print
			flog << "========SEARCH_BP========" << endl;
			flog << name << "/" << it->second->getDeptNo()<< "/" << it->second->getID() << "/" << it->second->getIncome() << endl;
			flog << "====================\n\n";
			
		}
		else//error
		{
			printErrorCode(300);
			return;
		
		}

	}


	

		
	
	
}

void Manager::SEARCH_BP_RANGE(string start, string end)
{
	//call function
	bptree->searchRange(start, end);
	
}

void Manager::ADD_ST_DEPTNO(int dept_no) 
{
	// all search(becasue dept is not a key)
	BpTreeNode* new_target=bptree->searchDataNode("");
	if (new_target == nullptr) 
	{
		printErrorCode(500);
		return;
	}
	//compare until end
	bool is_find = false;
	while (new_target != nullptr)
	{
		//get a map and iterator
		map<string, EmployeeData*>* find_map = new_target->getDataMap();
		map<string, EmployeeData*>::iterator it = find_map->begin();
		//find in node
		while (it != find_map->end()) 
		{
			if (it->second->getDeptNo() == dept_no) 
			{
				is_find = true;//find
				stree->Insert(it->second);//insert
				//break;
			}
			//increase
			it++;
		}
		//move next_node
		new_target=new_target->getNext();
	}

	//if find insert selection tree

	if (is_find) 
	{
		printSuccessCode("ADD_ST");
		return;
	}
	else 
	{
		printErrorCode(500);
		return;
	}

}

void Manager::ADD_ST_NAME(string name)
{
	//search, and get data node
	BpTreeNode* new_target=bptree->searchDataNode(name);

	if (new_target == nullptr)//dont have data node
	{
		printErrorCode(500);
		return;
	}

	//get a map and iterator
	map<string, EmployeeData*>* find_map = new_target->getDataMap();
	map<string, EmployeeData*>::iterator it = find_map->find(name);

	if (it != find_map->end()) 
	{
		stree->Insert(it->second);
		printSuccessCode("ADD_ST");
	}
	else //no name
	{
		printErrorCode(500);
		return;
	}


}

void Manager::PRINT_BP() 
{
	BpTreeNode* most_left=bptree->searchDataNode("");//get most left node
	if (most_left == nullptr)//nohing have	
	{
		printErrorCode(400);
		return;
	}


	
	
	flog << "========PRINT_BP========" << endl;
	while (most_left != nullptr) //next node-> getting notthing
	{
		map<string, EmployeeData*>* dataMap = most_left->getDataMap();
		map<string, EmployeeData*>::iterator it = dataMap->begin();
		
		//search and move
		while (it != dataMap->end())
		{
			//print
			flog << it->second->getName() << "/"
				<< it->second->getDeptNo() << "/"
				<< it->second->getID() << "/"
				<< it->second->getIncome() << endl;
			//increase
			it++;
		}

		most_left = most_left->getNext();
	}
	flog << "====================\n\n";


}

void Manager::PRINT_ST() 
{
	//get parsing
	string line;
	getline(fin, line); // read the rest of this command line
	stringstream figure(line);
	string code, extra;
	if (!(figure >> code) || (figure >> extra)) // missing or too many arguments
	{
		printErrorCode(600);
		return;
	}
	int imsi_code = atoi(code.c_str());

	//find run and print it
	if (!stree->printEmployeeData(imsi_code)) 
	{
		printErrorCode(600);
	}
}

void Manager::DELETE()
{
	//delete
	if (stree->Delete()) 
	{
		printSuccessCode("DELETE");
	}
	else 
	{
		printErrorCode(700);
	}
}

void Manager::printErrorCode(int n) {
	flog << "========ERROR========\n";
	flog << n << "\n";
	flog << "=====================\n\n";
}

void Manager::printSuccessCode(string success) {
	flog << "========" << success << "========\n";
	flog << "Success" << "\n";
	flog << "====================\n\n";
}