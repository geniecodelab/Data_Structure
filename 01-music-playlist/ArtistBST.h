#pragma once
#include "ArtistBSTNode.h"

class ArtistBST {
private:
	ArtistBSTNode* root;
	ArtistBSTNode* parent;
	string data;
	ArtistBSTNode* target;


public:
	ArtistBST();
	~ArtistBST();

	void insert(string input_title, string input_artist, string input_run_time);
	void search(string input_artist);
	void print();
	void delete_node(string input, string input_title = "");
	void call_print(ofstream& flog, ArtistBSTNode* input);
	pair<ArtistBSTNode*,ArtistBSTNode*>find_node(string input, string song_title = "");//추가 생성+ 부모와 탐색노드 반환을 위해
	void delete_post_order(ArtistBSTNode* root);//postorder방식을 통한 소멸자 구현을 위함.
	vector<pair<string, pair<string, int>>>for_pl(string input);

};