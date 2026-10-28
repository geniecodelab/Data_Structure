#pragma once
#include "TitleBSTNode.h"
class TitleBST {
private:
	TitleBSTNode* root;
	TitleBSTNode* parent;//삭제시 자식 연결
	string data;
	TitleBSTNode* target;//삭제할 대상

public:
	TitleBST();
	~TitleBST();

	void insert(string input_title, string input_artist, string input_run_time);
	void search(string input_title,string song_artist="");//입력안받으면 자동 공백처리
	void print();
	void delete_node(string input, string input_artist="");//제목만 넘겨준 상태
	void call_print(ofstream& flog, TitleBSTNode* input);
	pair<TitleBSTNode*, TitleBSTNode*>find_node(string input, string song_artist = "");//추가 생성+ 부모와 탐색노드 반환을 위해
	void delete_post_order(TitleBSTNode* root);//postorder방식을 통한 소멸자 구현을 위함.
	vector<pair<string, pair<string, int>>>for_pl(string input, string song_artist = "");
};