#pragma once
//#include "PlayList.h"
class PlayList;
#include <vector>
#include<fstream>
#include<iostream>
#include<string>

using namespace std;//필요할까?

class PlayListNode {
private:
	string artist;
	string title;
	int runtime_sec;

	PlayListNode* prev;
	PlayListNode* next;


	friend class  PlayList;//데이터 접근을 위해

public:
	PlayListNode(string input_artist,string input_title,int input_runtime_sec) 
	{
		artist = input_artist;//초기화
		title = input_title;
		runtime_sec = input_runtime_sec;
		prev = nullptr;
		next = nullptr;
	}
	~PlayListNode()
	{
		//링크드리스트에서 구현
	}

	void set() {

	}
};
