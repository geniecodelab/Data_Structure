#pragma once
//#include "MusicQueue.h"
#include <string>
#include <cstring>
#include <sstream>

using namespace std;

class MusicQueueNode {
private:
	string artist;
	string title;
	string run_time;

	MusicQueueNode* next;
	MusicQueueNode* prev;
	
	friend class MusicQueue;

public:
	MusicQueueNode(string input_artist, string input_title, string input_run_time)
	{
		next = nullptr;
		prev = nullptr;
		artist = input_artist;
		title = input_title;
		run_time = input_run_time;
	}
	~MusicQueueNode() 
	{
		//큐에서 삭제할 것.
	}
	//실질적인 노드생성
	void insert()
	{
		

	}
	//해당 노드이 데이터 확인 용도
	bool exist(string artist_name,string title_name) {
		if(artist== artist_name&&title==title_name)
		{
			return true;
		}
		else
		{
			return false;//가수 이름이나, 곡 명 다르면 false
		}
	}
	//pop과정에서 필요한 정보
	string get_artist()
	{
		return artist;
	}
	string get_title()
	{
		return title;
	}
	string get_run_time()
	{
		return run_time;
	}

};
