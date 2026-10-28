#pragma once
#include "PlayListNode.h"
#include <vector>
#include<fstream>
#include<iostream>
#include <string>
#include<sstream>
using namespace std;

class PlayList {
private:
	PlayListNode* head;
	PlayListNode* cursor;
	int count;
	int time;
	string data;

public:
	PlayList();
	~PlayList();
	void insert_node(string input_artist, string input_title, int input_run_time);
	void delete_node(string input_artist, string input_title);//만약 플리에있으면 한정된 정보로 지워야할 수 도있다.
	bool empty();
	bool full();
	bool exist(string input_artist, string input_title);
	string print();
	int run_time();//입력받으면 현재 플리의 초를 출력
	int get_size()
	{
		return count;
	}
	
};
