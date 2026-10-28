#include "BpTree.h"
#include <cmath>

bool BpTree::Insert(EmployeeData* newData) 
{
	//get name
	string name = newData->getName();
	//get money
	
	//is it allocated? 
	BpTreeNode* for_insert_node = searchDataNode(name);
	
	if (for_insert_node == nullptr) 
	{
		//no tree
		BpTreeDataNode* new_root = new BpTreeDataNode;
		new_root->insertDataMap(name, newData);
		root = new_root;//allocate new root

		return true;
	}
	else
	{
		//no key or located key
		//to use child function, doing casting
		BpTreeDataNode* for_insert_data_node = (BpTreeDataNode*)for_insert_node;

		map <string, EmployeeData*>* to_confirm_name= for_insert_data_node->getDataMap();//to confirm
		map <string, EmployeeData*>::iterator allocated = to_confirm_name->find(name);//return pair
		if (allocated == to_confirm_name->end()) 
		{
			//no name
			for_insert_data_node->insertDataMap(name, newData);
			//is it full?
			if (excessDataNode(for_insert_data_node))
			{
				splitDataNode(for_insert_data_node);//split
			}
		}
		else //has name
		{
			
			allocated->second->setIncome(newData->getIncome());//allocate new income
			delete newData;//becasue not use newData
		}

		return true;

	
		
	}


}

bool BpTree::excessDataNode(BpTreeNode* pDataNode)//is it full?
{
	//confirm key num
	BpTreeDataNode* new_node = (BpTreeDataNode*)pDataNode;//casting
	map <string, EmployeeData*>* to_confirm_num=new_node->getDataMap();
	if (to_confirm_num->size() >= order) 
	{
		return true;
	}
	return false;
}

bool BpTree::excessIndexNode(BpTreeNode* pIndexNode) 
{
	//confirm key num
	BpTreeIndexNode* new_node = (BpTreeIndexNode*)pIndexNode;//casting
	map <string, BpTreeNode*>* to_confirm_num = new_node->getIndexMap();
	if (to_confirm_num->size() >= order)
	{
		return true;
	}
	return false;
	
}

void BpTree::splitDataNode(BpTreeNode* pDataNode)//when full 
{
	
	//prepare split
	//get loc
	double loc=ceil((order-1)/2.0)+1;
	//new data node
	BpTreeDataNode* new_node = new BpTreeDataNode;
	//casting
	BpTreeDataNode* casting_node = (BpTreeDataNode*)pDataNode;

	//split
	map <string, EmployeeData*>* getting_map = casting_node->getDataMap();
	map <string, EmployeeData*>::iterator allocated = getting_map->begin();//return  first pair
	for (int i = 0; i < loc-1; i++)// becasue start in 1 
	{
		allocated++;//moving split locate
	}



	//parent search
	if (casting_node->getParent() == nullptr)//no parent
	{
		

		BpTreeIndexNode* new_index_node = new BpTreeIndexNode;//generate new index
		new_index_node->insertIndexMap(allocated->first, new_node);

		// copy and delete
		while (allocated != getting_map->end())
		{
			new_node->insertDataMap(allocated->first, allocated->second);
			string delete_name = allocated->first;
			allocated++;
			casting_node->deleteMap(delete_name);
			

		}
		//connect parent
		casting_node->setParent(new_index_node);

		//connect leftchild
		new_index_node->setMostLeftChild(casting_node);

		//allocate new root
		root = new_index_node;


		//allocate new_spilit_node's parent
		new_node->setParent(new_index_node);




	}
	else //parent is in
	{
		//allocate new_spilit_node's parent
		new_node->setParent(casting_node->getParent());


		BpTreeNode*before_insert_index= casting_node->getParent();//name+ data node location
		BpTreeIndexNode* real_insert_index = (BpTreeIndexNode*)before_insert_index;//casting
		real_insert_index->insertIndexMap(allocated->first, new_node);//insert
		// copy
		while (allocated != getting_map->end())
		{
			new_node->insertDataMap(allocated->first, allocated->second);
			string delete_name = allocated->first;
			allocated++;
			casting_node->deleteMap(delete_name);
		}
		if (excessIndexNode(real_insert_index))
		{
			splitIndexNode(real_insert_index); // 부모 노드를 분열시킵니다.
		}

		
	}

	//connect data_node
	//new<=>prev_next
	new_node->setNext(casting_node->getNext());//new connection
	if (casting_node->getNext() != nullptr)// if alive
	{
		casting_node->getNext()->setPrev(new_node);
	}
	//casting <=>new
	new_node->setPrev(casting_node);
	casting_node->setNext(new_node);
	


	


	return;

}

void BpTree::splitIndexNode(BpTreeNode* pIndexNode) 
{
	//casting
	BpTreeIndexNode* casting_index = (BpTreeIndexNode*)pIndexNode;
	//new_index
	BpTreeIndexNode* new_index = new BpTreeIndexNode;
	//find split location
	double loc = ceil((order - 1) / 2.0) + 1;
	//getting map, and moving to location
	map <string, BpTreeNode*>* casting_map = casting_index-> getIndexMap();
	map <string, BpTreeNode*>::iterator allocated = casting_map->begin();//return  first pair
	



	
	
	for (int i = 0; i < loc - 1; i++)// becasue start in 1 
	{
		allocated++;//moving split locate
	}
	//remeber spilit point
	string remember =allocated->first;
	//process second key
	new_index->setMostLeftChild(allocated->second);
	allocated->second->setParent(new_index);
	//increase
	allocated++;
	
	

	string delete_name;
	//copy
	while (allocated != casting_map->end())//end next 
	{
		delete_name = allocated->first;
		new_index->insertIndexMap(delete_name, allocated->second);
		allocated->second->setParent(new_index);
		allocated++;
		casting_index->deleteMap(delete_name);
	}

	casting_index->deleteMap(remember);//delete remember

	//connect parent
	if (casting_index->getParent() == nullptr) //no parent
	{
		//make new parent
		BpTreeIndexNode* new_parent = new BpTreeIndexNode;
		//insert to parent
		new_parent->setMostLeftChild(casting_index);
		new_parent->insertIndexMap(remember, new_index);
		//connect to parent
		casting_index->setParent(new_parent);
		new_index->setParent(new_parent);
		//allocate new root
		root = new_parent;

	


	}
	else
	{
		BpTreeIndexNode* casting_parent = (BpTreeIndexNode*)casting_index->getParent();
		casting_parent->insertIndexMap(remember,new_index);
		//contect prev ,allocated pointer
		new_index->setParent(casting_index->getParent());

		


		if (excessIndexNode(casting_parent))
		{
			splitIndexNode(casting_parent); // split partenr
		}

	}

	

	
	
	

	
}

BpTreeNode* BpTree::searchDataNode(string name) 
{
	//generate seaerch node
	BpTreeNode* search_node =root;
	
	
	//not have tree?
	if (root == nullptr) 
	{
		return nullptr;
	}
	
	//if no index node?-> return root, else, search-> return data node
	while (search_node->getIndexMap() != nullptr)
	{
		
		map <string, BpTreeNode*>* casting_map =search_node->getIndexMap();//getting map
		BpTreeNode* default_key = search_node->getMostLeftChild();//default node
		
		map <string, BpTreeNode*>::iterator find_key=casting_map->begin();//find key
		

		if (name < find_key->first)
		{
			search_node = default_key;//move next node
		}
		else 
		{
			while (find_key != casting_map->end() && name >= find_key->first)
			{

				find_key++;//move in the map

			}
			find_key--;
			search_node = find_key->second;//move to next
		}

	
	}
	return search_node;
}

void BpTree::searchRange(string start, string end) 
{
	//find start node
	BpTreeNode* start_node = searchDataNode(start);
	//if no node-> error
	if (start_node == nullptr)
	{
		(*fout) << "========ERROR========\n" << "400\n" << "=====================\n";
		return;
	}



	bool end_search=false;// to end all search

	


	*fout << "========SEARCH_BP========" << endl;
	//move node
	while(start_node!=nullptr&&end_search!=true)
	{
		//inner
		//gettin map, and iterator
		map <string, EmployeeData*>* search_map = start_node->getDataMap();
		map <string, EmployeeData*>::iterator inner_iterator = search_map->begin();

	//inner search
		
		for(;inner_iterator != search_map->end(); inner_iterator++)//move next iterator
		{
			//is not begin?
			if (inner_iterator->first < start)
			{
				continue;//jump
			}
			//is end? the end bound is compared by its prefix, so "e" also includes every name starting with "e"
			if (inner_iterator->first.substr(0, end.size()) > end)
			{
				end_search = true;//end moving
				break;//end inner search
			}

			//print
			(*fout) << inner_iterator->second->getName() << "/"
				<< inner_iterator->second->getDeptNo() << "/"
				<< inner_iterator->second->getID() << "/"
				<< inner_iterator->second->getIncome() << endl;
			
			
		}


		//move next
		start_node=start_node->getNext();

	}
	*fout << "====================\n\n";

}

/*
bool BpTree::search(string name)
{
	//find spot
	BpTreeNode* spot=searchDataNode(name);
	//get iterator
	map <string, EmployeeData*>*find_map= spot->getDataMap();
	map <string, EmployeeData*>::iterator new_iterator = find_map->begin();


	while (find_map->end()!=new_iterator) 
	{
		if (new_iterator->first == name) 
		{
			*fout << " ========SEARCH_BP========" << endl;
			*fout << new_iterator->first<<"/"<<new_iterator->second->getDeptNo()<<"/"<<new_iterator->second->getID()<<"/"<<new_iterator->second->getIncome() << endl;//print all
			*fout << " =======================" << endl<<endl;
			return true;
		}
		new_iterator++;
	}
	return false;

}*/

// free the subtree of node (index nodes: children, data nodes: employee data)
void BpTree::destroy(BpTreeNode* node)
{
	if (node == nullptr) return;

	map<string, BpTreeNode*>* index_map = node->getIndexMap();
	if (index_map != nullptr) // index node
	{
		destroy(node->getMostLeftChild());
		for (map<string, BpTreeNode*>::iterator it = index_map->begin(); it != index_map->end(); it++)
		{
			destroy(it->second);
		}
	}
	else // data node: it owns the employee data
	{
		map<string, EmployeeData*>* data_map = node->getDataMap();
		for (map<string, EmployeeData*>::iterator it = data_map->begin(); it != data_map->end(); it++)
		{
			delete it->second;
		}
	}
	delete node;
}
