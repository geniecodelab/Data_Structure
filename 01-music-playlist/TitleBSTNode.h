#pragma once
//#include "TitleBST.h"
class TitleBST;
#include "MusicQueueNode.h"
#include<vector>
#include<fstream>
#include<iostream>

class TitleBSTNode {
private:
	string title;
	vector<string> artist;
	string run_time;
	vector<int> rt;
	int count;
	TitleBSTNode* left;
	TitleBSTNode* right;

	


	friend class TitleBST;//노드 접근을 위한 friend class
public:
	TitleBSTNode(string input_title, string input_artist,string input_run_time) 
	{
		left = nullptr;
		right = nullptr;
		count = 1;//일단 한곡은 추가된 상태
		title = input_title;
		run_time = input_run_time;

		//vector 처리
		string imsi_min, imsi_second;//분과 초의 구분을 위해
		stringstream for_run(input_run_time);//stringstream으로의 변환
		artist.push_back(input_artist);
		getline(for_run,imsi_min,':');
		getline(for_run,imsi_second);
		int min = stoi(imsi_min);//문자열->정수형변수로의 변환
		int second = stoi(imsi_second);

		rt.push_back(60*min + second);//runtime값에 초값으로 대입


	}
	~TitleBSTNode() 
	{
		//bst에서 해제
	}

	void set(string input_artist, string input_run_time)
	{
		ofstream set_flog;
		set_flog.open("log.txt", ios::app);//로그에 기록하기위함.
		//같은 제목인 경우


		//1.동일한 곡이 있는지 확인
		for(const string& art:artist)//복사로 인한 데이터낭비 방지
		{
			if(input_artist==art)
			{
				cout << "BST에 동일한 곡이 존재합니다." << endl;
				set_flog << "========ERROR========" << endl;//에러코드
				set_flog << "300" << endl;
				set_flog << "=====================" << endl << endl;
				return;//함수 자체의 종료
			}
			
		}
		

		//2.동일한 곡이 없는경우.
		//바로 다음것에 대입
		artist.push_back(input_artist);
		
		if(!run_time.empty()){
			run_time = run_time + '|';//구분자 삽입
		}
		run_time = run_time + input_run_time;//새로운 시간 추가
		// 벡터 대입
		stringstream for_run(input_run_time);//stringstream으로의 변환
		string imsi_min, imsi_second;//분과 초의 구분을 위해
		getline(for_run, imsi_min, ':');
		getline(for_run, imsi_second);
		int min = stoi(imsi_min);//문자열->정수형변수로의 변환
		int second = stoi(imsi_second);
		rt.push_back(60 * min + second);//runtime값에 초값으로 대입

		//수 증가
		count++;

		set_flog.close();
	}
	void search(string input, string input_artist)//song입력시 탐색 및 삭제
	{
		//해당 노드에 동일한 가수가 있는가?
		for(int i=0;i<count;i++)//탐색
		{
			if (input_artist == artist[i])
			{


				artist.erase(artist.begin() + i);//제목삭제-> 자동 재정렬 이뤄짐
				rt.erase(rt.begin() + i);//rt삭제
				int imsi_min, imsi_sec;
				stringstream a;//문자열 결합을 위해
				//기존 rt를 통한 새로운 rt 배치
				bool once = false;

				for (int j = 0; j < rt.size(); j++)
				{

					imsi_min = rt[j] / 60;//분 부여
					imsi_sec = rt[j] % 60;//초 부여
					if (once == false)//처음 한번만
					{
						a << imsi_min << ":" << (imsi_sec < 10 ? "0" : "") << imsi_sec;//시간 초 부여
					}
					else
					{
						a << "|" << imsi_min << ":" << (imsi_sec < 10 ? "0" : "") << imsi_sec;//시간 초 부여
					}
					once = true;//한번만 실행하기위해
				}
				run_time = a.str();//문자열로의 변환
				count--;//수 감소
				return;//종료




			}
		
			
		}
	}

};
