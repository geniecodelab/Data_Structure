#pragma once
#include "MusicQueue.h"
#include "TitleBST.h"
#include "ArtistBST.h"
#include "PlayList.h"
#include <fstream>


using namespace std;

class Manager {
private:
	MusicQueue q;
	ArtistBST ab;
	TitleBST tb;
	PlayList pl;
	ifstream fcmd;
	ofstream flog;
public:
	Manager();
	~Manager();

	void run(const char* command);//커멘더 파일 읽어들이기

	void LOAD();
	void ADD(stringstream& input_imsi);
	void QPOP();
	void SEARCH(stringstream& input_imsi);
	void MAKEPL(stringstream& input_imsi);
	void PRINT(stringstream& input_imsi);
	void DELETE(stringstream& input_imsi);
	void EXIT();

};