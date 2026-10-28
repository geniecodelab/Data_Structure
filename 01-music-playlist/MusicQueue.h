#pragma once
#include "MusicQueueNode.h"
#include<string>
class MusicQueue {
private:
	MusicQueueNode* head;
	MusicQueueNode* rear;
	int size = 0;
public:
	MusicQueue();
	~MusicQueue();

	bool empty();//큐 비어있는가.
	bool exist(string recieve_artist, string recieve_title);//중복된 곡 있는가.
	void push(string recieve_artist, string recieve_title, string recieve_run_time);
	MusicQueueNode* pop();
	MusicQueueNode* front();
};