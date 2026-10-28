#include "Manager.h"
#include <string>
#include <cstring>
#include <fstream>
#include <iostream>
#include<utility>
using namespace std;

Manager::Manager() {

}

Manager::~Manager() {

}

void Manager::run(const char* command) {
	//조건에따라, 실행되는 함수 선택
	//해당 파일 읽어들이고, 명령어 해석하기
	fcmd.open(command);//읽기전용 파일 열기
	
	string read_txt;//getline을 위해
	string read_command;
	stringstream imsi;//파싱을 위해.
	

	if (fcmd.is_open())//command.txt가 잘 열린경우 
	{
	

		while (getline(fcmd, read_txt))//엔터마다 문자열 읽어들이는데, 파일 끝날때까지
		{
			//엔터만 입력받은 경우는 무시
			if (read_txt.empty())continue;//이번 입력 건너뛰고 다음 것 받기.
			
			
			imsi.clear();//이전 내용지우기
			imsi.str(read_txt);//내용 이전
			imsi>>read_command;//스페이스 바를 입력받았을때까지
			if (read_command == "LOAD")
			{
				LOAD();//LOAD함수호출
			}
			else if (read_command == "ADD")
			{

				ADD(imsi);//나머지 title인지는 안에서 판단//&전달시, 주소만 전달, 그대로 전달시 참조로의 전달
			}
			else if (read_command == "QPOP")
			{
				QPOP();
			}
			else if (read_command == "SEARCH")
			{
				SEARCH(imsi);
			}
			else if (read_command == "MAKEPL")
			{
				MAKEPL(imsi);
			}
			else if (read_command == "PRINT")
			{
				PRINT(imsi);
			}
			else if (read_command == "DELETE")
			{
				DELETE(imsi);
			}
			else if (read_command == "EXIT")
			{
				EXIT();
				break;//exit 만나면, 뒤에 내용 남아있어도, 어짜피 프로그램 종료될것
			}
			else
			{
				flog.open("log.txt", ios::app);//작업사항 보여주기(오류코드)
				//아무것도 해당되지않는 경우.
				cout << "command 파일에서 잘못된 명령어를 작성하였습니다." << endl;
				flog << "========ERROR========" << endl;//에러코드
				flog << "1000" << endl;
				flog << "=====================" << endl << endl;
				flog.close();
			}

		}
	}
	else
	{
		//아무것도 해당되지않는 경우.
		flog.open("log.txt", ios::app);//작업사항 보여주기(오류코드)
		cout << "command 파일을 열지 못하였습니다.." << endl;
		flog << "========ERROR========" << endl;//에러코드
		flog << "1000" << endl;
		flog << "=====================" << endl << endl;
		flog.close();
	}
		
	fcmd.close();//연 파일 닫기
	
}

void Manager::LOAD() 
{
	ifstream load_fcmd;//Run에서의 중복 ifstream사용 방지
	ofstream load_flog;
	string imsi_load;//불러올떄 임시로 받아들이기.
	stringstream for_parsing;
	string artist;
	string title;
	string run_time;

	bool first_load_print=false; //일단 내용이 있을때, LOAD를 출력하기위해
	
	int count=0;//만약 파일이 비워져있을 수도 있으닌까.
	//파일열기
	load_fcmd.open("Music_List.txt");
	load_flog.open("log.txt", ios::app);//기록할 파일 열기
	//조건확인1
	if(q.empty())//비어있는가?
	{

		//조건 확인2
		if (load_fcmd.is_open())
		{
			cout << "txt파일 열기 성공" << endl;
									
			//파일 읽어들여 큐에 전달
			while (getline(load_fcmd, imsi_load))//다 읽을 때까지 반복(false반환)
			{
				if(!first_load_print)
				{
					//처음 실행됐을때만 할거닌까 true-false 교환
					first_load_print = true; 
					load_flog << "========LOAD========" << endl;//처음 실행될때만 기록

				}
				
				for_parsing.clear();//기존 내용 비우기.
				for_parsing.str(imsi_load);//입력받은 문자열 파싱위해 전달
				getline(for_parsing, artist, '|');
				getline(for_parsing, title, '|');
				getline(for_parsing, run_time);

				//혹시 모를 데이터의 오류가 발생 할 수 있으닌까.
				if(artist.empty()||title.empty()||run_time.empty())
				{
					//혹시 누락된경우. error코드
					cout << "Music_List.txt의 내용이 잘못되었습니다." << endl;
					load_flog << "========ERROR========" << endl;//에러코드
					load_flog << "100" << endl;
					load_flog << "=====================" << endl << endl;
				}
				else 
				{
					q.push(artist, title, run_time);//큐에 전달.
					//정상작동시 log.txt파일 기록
					cout << artist << "/" << title << "/" << run_time << endl;//읽어들인 내용 그대로 다시 작성
					load_flog << artist << "/" << title << "/" << run_time << endl;//읽어들인 내용 그대로 다시 작성
					count++;//비워져있지않음을 보여주기위해
				}

											
			}
			if (count != 0) 
			{
				//내용이 있었던 경우
				load_flog << "=====================" << endl << endl;//종료
			}
			else
			{
				//파일에 내용이 하나도 없었던 경우
				cout << "Music_List.txt 파일에 내용이 하나도 없었습니다." << endl;
				load_flog << "========ERROR========" << endl;//에러코드
				load_flog << "100" << endl;
				load_flog << "=====================" << endl << endl;
			}
			

		}
		else
		{
			//파일을 열지 못했을 경우.
			cout << "Music_List.txt 파일을 열지 못했습니다." << endl;
			load_flog << "========ERROR========" << endl;//에러코드
			load_flog << "100" << endl;
			load_flog << "=====================" << endl << endl;
		}
		
	}
	else
	{
		cout << "Queue에 내용이 차있습니다." << endl;
		load_flog << "========ERROR========" << endl;//에러코드
		load_flog << "100" << endl;
		load_flog << "=====================" << endl << endl;
	}
	load_fcmd.close();//입출력과정에서의 객체 닫아주기.
	load_flog.close();
	
}

void Manager::ADD(stringstream& input_imsi)
{
	ofstream load_flog;//Run에서의 중복 ifstream사용 방지
	load_flog.open("log.txt", ios::app);//기록할 파일 열기
	
	string input_artist, input_title, input_run_time;//파싱을 위한 세개의 변수
	
	//add와 곡간의 공백제거
	input_imsi >> ws;//stream대상으로 공백제거 조작자
	
	getline(input_imsi, input_artist, '|');
	getline(input_imsi, input_title, '|');
	getline(input_imsi, input_run_time);//어짜피 마지막에 남은 거닌까.
	//형식이 올바르지않을 경우 오류코드
	if (input_artist.empty() || input_title.empty() || input_run_time.empty()) 
	{
		cout << "데이터 형식이 올바르지 않습니다." << endl;
		load_flog << "========ERROR========" << endl;//에러코드
		load_flog << "200" << endl;
		load_flog << "=====================" << endl << endl;

	}
	else
	{
		//중복된지 확인
		if(q.exist(input_artist,input_title))
		{
			cout << "기존의 곡이 중복되었습니다." << endl;
			load_flog << "========ERROR========" << endl;//에러코드
			load_flog << "200" << endl;
			load_flog << "=====================" << endl << endl;
		}
		else
		{
			q.push(input_artist, input_title, input_run_time);
			load_flog << "========ADD========" << endl;
			load_flog << input_artist << "/" << input_title << "/" << input_run_time << endl;//읽어들인 내용 그대로 다시 작성
			load_flog << "=====================" << endl << endl;//종료
		}


	}

	
	load_flog.close();//닫아주기
}

void Manager::QPOP() 
{
	ofstream load_flog;//Run에서의 중복 ifstream사용 방지
	load_flog.open("log.txt", ios::app);//기록할 파일 열기
	if(q.empty())//큐가 비어져있는경우.
	{
		load_flog << "========ERROR========" << endl;//에러코드
		load_flog << "300" << endl;
		load_flog << "=====================" << endl << endl;
		return;//함수종료
	}
	
	while(!q.empty())//빌때까지 POP
	{
		MusicQueueNode* imsi =q.pop();//POP한 노드 받아들이기
		//get함수를 통한 매개변수 전달.
		tb.insert(imsi->get_title(), imsi->get_artist(), imsi->get_run_time());
		ab.insert(imsi->get_title(), imsi->get_artist(), imsi->get_run_time());

		delete imsi;//메모리해제를 위해
		
	}
	load_flog << "========QPOP========" << endl;//에러코드
	load_flog << "Success" << endl;
	load_flog << "=====================" << endl << endl;

	
	load_flog.close();

}

void Manager::SEARCH(stringstream& input_imsi) 
{
	ofstream load_flog;//Run에서의 중복 ifstream사용 방지
	load_flog.open("log.txt", ios::app);//기록할 파일 열기
	//다음 문자열 종류에 따른 bst의 search함수 호출

	//파싱
	string type;
	input_imsi >> ws;//search사이 공백제거
	getline(input_imsi, type,' ');
	if(type=="ARTIST")
	{
		input_imsi >> ws;//artist사이 공백제거
		getline(input_imsi, type);
		ab.search(type);//bst에 전달 후 처리
	}
	else
	{
		if(type=="TITLE")
		{
			input_imsi >> ws;//artist사이 공백제거
			getline(input_imsi, type);
			tb.search(type);//bst에 전달 후 처리
		}
		else
		{
			if(type=="SONG")
			{
				string title;
				input_imsi >> ws;//artist사이 공백제거
				getline(input_imsi, type,'|');//|기준으로 가수입력
				getline(input_imsi, title);
				tb.search(title,type);//title bst에 제목과 가수 이름 전달 
			}
			else
			{
				//형식에 맞지않아 오류코드 발행
				load_flog << "========ERROR========" << endl;//에러코드
				load_flog << "400" << endl;
				load_flog << "=====================" << endl << endl;
				
			}
		}
	}

	load_flog.close();
}

void Manager::MAKEPL(stringstream& input_imsi)//플리에 존재하는지 확인 후 삽입
{
	ofstream load_flog;//Run에서의 중복 ifstream사용 방지
	load_flog.open("log.txt", ios::app);//기록할 파일 열기
	//문자열 파싱
	input_imsi >> ws;//공백제거
	string imsi;
	string input_aritst;//플리 insert함수 전달을 위함.
	string input_title;
	int input_runtime;

	input_imsi>>imsi;//space를 입력받을때까지
	if(imsi=="ARTIST")
	{
		input_imsi >> ws;
		getline(input_imsi,imsi);//아티스트 대입
		vector<pair<string, pair<string, int>>>for_pl = ab.for_pl(imsi);

		if (for_pl.empty())//vecor가 비어있는경우
		{
			//오류발생
			load_flog << "========ERROR========" << endl;//에러코드
			load_flog << "500" << endl;
			load_flog << "=====================" << endl << endl;
		}
		else
		{
			//찾은경우
			if (pl.full())//다 찼는가?(검사1)
			{
				load_flog << "========ERROR========" << endl;//에러코드
				load_flog << "500" << endl;
				load_flog << "=====================" << endl << endl;
			}
			else
			{
				for (int i = 0; i < for_pl.size(); i++)
				{

					if (pl.exist(for_pl[i].first, for_pl[i].second.first)) //기존 곡 존재하는 경우(검사2)//한곡이라도 존재한다면 다른곡 존재안해도 오류코드 발행
					{

						load_flog << "========ERROR========" << endl;//에러코드
						load_flog << "500" << endl;
						load_flog << "=====================" << endl << endl;
						return;
					}

				}

				//삽입곡이 더 많은가?(검사 3)
				if (for_pl.size() + pl.get_size() >= 10) {
					load_flog << "========ERROR========" << endl;//에러코드
					load_flog << "500" << endl;
					load_flog << "=====================" << endl << endl;
					return;
				}

				load_flog << "========MAKEPL=======" << endl;
				for (int i = 0; i < for_pl.size(); i++)
				{
					pl.insert_node(for_pl[i].first, for_pl[i].second.first, for_pl[i].second.second);//전달
				}
				string for_print = pl.print();//string반환
				load_flog << for_print;//파일 출력

				load_flog << "=====================" << endl << endl;
			}
			
		}
	}
	else
	{
		vector<pair<string, pair<string, int>>>for_pl;
		if(imsi=="TITLE")
		{
			input_imsi >> ws;
			getline(input_imsi, imsi);//아티스트 대입
			for_pl = tb.for_pl(imsi);
			
		}
		else
		{
			if(imsi=="SONG")
			{
				input_imsi >> ws;
				string imsi_artist;
				getline(input_imsi, imsi_artist,'|');//
				getline(input_imsi, imsi);
				for_pl = tb.for_pl(imsi,imsi_artist);
				
			}
			else
			{
				//세가지 입력이 아닌경우
				load_flog << "========ERROR========" << endl;//에러코드
				load_flog << "500" << endl;
				load_flog << "=====================" << endl << endl;
				return;//종료
			}
		}

		if (for_pl.empty())//titleBst의 vecor가 비어있는경우
		{
			//오류발생
			load_flog << "========ERROR========" << endl;//에러코드
			load_flog << "500" << endl;
			load_flog << "=====================" << endl << endl;
		}
		else
		{
			//찾은경우
			if(pl.full())//다 찼는가?(검사1)
			{
				load_flog << "========ERROR========" << endl;//에러코드
				load_flog << "500" << endl;
				load_flog << "=====================" << endl << endl;
			}
			else
			{
				bool one_makepl = false;
				
				for (int i = 0; i < for_pl.size(); i++)
				{

					if (pl.exist(for_pl[i].first, for_pl[i].second.first)) //기존 곡 존재하는 경우(검사2)//한곡이라도 존재한다면 다른곡 존재안해도 오류코드 발행
					{
						
						load_flog << "========ERROR========" << endl;//에러코드
						load_flog << "500" << endl;
						load_flog << "=====================" << endl << endl;
						return;
					}
																		
				}
				//삽입곡이 더 많은가?(검사 3)
				if (for_pl.size() + pl.get_size() >= 10) {
					load_flog << "========ERROR========" << endl;//에러코드
					load_flog << "500" << endl;
					load_flog << "=====================" << endl << endl;
					return;
				}

				for (int i = 0; i < for_pl.size(); i++) 
				{
					pl.insert_node(for_pl[i].first, for_pl[i].second.first, for_pl[i].second.second);//전달
				}
				load_flog << "========MAKEPL=======" << endl;
				string for_print = pl.print();//string반환

				load_flog << for_print;//파일 출력
				load_flog << "=====================" << endl << endl;
		
				
				
			}



			
		}

	}
	
	
	
	load_flog.close();
	//
}

void Manager::PRINT(stringstream& input_imsi) 
{
	string imsi;//문자열로의 변환
	input_imsi >> imsi;//공백제거된 문자열
	

	ofstream print_flog;//Run에서의 중복 ifstream사용 방지
	print_flog.open("log.txt", ios::app);//기록할 파일 열기

	if(imsi=="ARTIST")
	{
		ab.print();
	}
	else
	{
		if(imsi=="TITLE")
		{
			tb.print();//안에서 처리할것
		}
		else
		{
			if(imsi=="LIST")
			{
				string for_print= pl.print();//문자열 반환
				if(for_print=="")
				{
					//오류가 발생했을경우
					print_flog << "========ERROR========" << endl;//에러코드
					print_flog << "600" << endl;
					print_flog << "=====================" << endl << endl;
				}
				else
				{
					//정상출력
					
					print_flog << "========Print========" << endl;//정상작동
					print_flog << for_print << endl;//문자열 작성
					print_flog << "=====================" << endl << endl;
				}
				
			}
			else 
			{
				//위의 세가지가 아닌경우.
				//오류코드 발행
				print_flog << "========ERROR========" << endl;//에러코드
				print_flog << "600" << endl;
				print_flog << "=====================" << endl << endl;
			}
		}
	}

	print_flog.close();

}

void Manager::DELETE(stringstream& input_imsi) 
{
	bool title_bst,artist_bst,list = false;//정상작동했는가?

	
	ofstream print_flog;//Run에서의 중복 ifstream사용 방지
	print_flog.open("log.txt", ios::app);//기록할 파일 열기
	input_imsi >> ws;//공백제거
	string a;
	input_imsi >> a;//스페이스바를 입력받을 때까지
	
	if(a=="ARTIST")
	{
		input_imsi >> ws;//공백제거
		string i;
		getline(input_imsi,i);
		if(ab.find_node(i).first!=nullptr)
		{
			vector<pair<string, pair<string, int>>>c = ab.for_pl(i);
			//플리에 있는 경우에만 삭제//성공 여부와 무관
			for(int j=0;j<c.size();j++)//노드의 데이터 만큼 탐색
			{
				if (pl.exist(c[j].first, c[j].second.first))//가수와 곡을 입력받았을때 존재하는가?
				{
				

					//pl에서의 삭제
					pl.delete_node(c[j].first, c[j].second.first);
				}
			}
			

			
			

			
			
			//있을 경우
			//1. ab로 부터의 곡정보 탈환
			vector<pair<string, pair<string, int>>>for_pl = ab.for_pl(i);
			for (int j = 0; j < for_pl.size(); j++) 
			{
				//tb에서의 노드 삭제
				tb.delete_node(for_pl[j].second.first,for_pl[j].first);
				
			}
			


			ab.delete_node(i);//안에서 처리할 것
			print_flog << "========DELETE========" << endl;//삭제 완료 출력
			print_flog << "Success" << endl;
			print_flog << "======================" << endl << endl;
			



		}
		//없으면 안에서 오류발생
		else
		{
			print_flog << "========ERROR========" << endl;//에러코드
			print_flog << "700" << endl;
			print_flog << "=====================" << endl << endl;
		}
	}
	else
	{
		if(a=="TITLE")
		{
			input_imsi >> ws;//공백제거
			string i;
			getline(input_imsi,i);
			
			if(tb.find_node(i).first != nullptr)
			{
				//플리에 있는 경우에만 삭제//성공 여부와 무관
				vector<pair<string, pair<string, int>>>c = tb.for_pl(i);
				
				for (int j = 0; j < c.size(); j++)//노드의 데이터 만큼 탐색
				{
					if (pl.exist(c[j].first, c[j].second.first))//가수와 곡을 입력받았을때 존재하는가?
					{
						pl.delete_node(c[j].first,c[j].second.first);
					}
				}
				//1. ab로 부터의 곡정보 탈환
				vector<pair<string, pair<string, int>>>for_pl = tb.for_pl(i);
				for (int j = 0; j < for_pl.size(); j++)
				{
					//tb에서의 노드 삭제
					ab.delete_node(for_pl[j].first, for_pl[j].second.first);

				}
				
								
				//탐색결과 있는경우 일단 플레이리스트 삭제후 bst삭제
				tb.delete_node(i);
				print_flog << "========DELETE========" << endl;//삭제 완료 출력
				print_flog << "Success" << endl;
				print_flog << "======================" << endl << endl;
			}
			else
			{
				print_flog << "========ERROR========" << endl;//에러코드
				print_flog << "700" << endl;
				print_flog << "=====================" << endl << endl;
			}
		}
		else
		{
			if(a=="LIST")
			{
				string imsi_artist;
				string imsi_title;
				input_imsi >> ws;//공백제거
				getline(input_imsi, imsi_artist, '|');//기호 구분해 전달
				getline(input_imsi,imsi_title);//제목 전달.
				//문자열 끝에 있을 수 있는 '\r' 제거
				if (!imsi_title.empty() && imsi_title.back() == '\r') {
					imsi_title.pop_back();
				}
				if(pl.exist(imsi_artist, imsi_title))
				{
					//내용이 존재한다
					
					pl.delete_node(imsi_artist, imsi_title);//내부 처리
					print_flog << "========DELETE========" << endl;
					print_flog << "Success" << endl;
					print_flog << "=====================" << endl << endl;
				}
				else
				{
					//내용이 존재하지않는다.
					print_flog << "========ERROR========" << endl;//에러코드
					print_flog << "700" << endl;
					print_flog << "=====================" << endl << endl;
				}
			}
			else
			{
				
				if (a == "SONG")
				{
					//전부삭제
					
					//list삭제
					string imsi_artist;
					string imsi_title;
					
					input_imsi >> ws;//공백제거
					getline(input_imsi, imsi_artist, '|');//기호 구분해 전달
					getline(input_imsi, imsi_title);//제목 전달.
					

					//문자열 끝에 있을 수 있는 '\r' 제거
					if (!imsi_title.empty() && imsi_title.back() == '\r') {
						imsi_title.pop_back();
					}
					if(pl.exist(imsi_artist, imsi_title))//플리에 존재할때만 삭제
					{
						pl.delete_node(imsi_artist, imsi_title);//내부 처리
					}

					if (ab.find_node(imsi_artist, imsi_title).first != nullptr&& tb.find_node(imsi_title, imsi_artist).first != nullptr)//만약 bst에만 있어도 정상처리
					{
						//내용이 존재한다
						
						// Artist Bst삭제
						ab.delete_node(imsi_artist, imsi_title);
						//TitleBst삭제
						tb.delete_node(imsi_title, imsi_artist);
						print_flog << "========DELETE========" << endl;
						print_flog << "Success" << endl;
						print_flog << "=====================" << endl << endl;
					}
					else
					{
						//내용이 존재하지않는다.
						print_flog << "========ERROR========" << endl;//에러코드
						print_flog << "700" << endl;
						print_flog << "=====================" << endl << endl;
					}
				}
				else
				{
					//오류발생
					print_flog << "========ERROR========" << endl;//에러코드
					print_flog << "700" << endl;
					print_flog << "=====================" << endl << endl;
				}
				
			}

		}
	}

	print_flog.close();

	
}

void Manager::EXIT() 
{
	ofstream exit_fout("log.txt", ios::app);
	exit_fout << "========EXIT========" << endl;
	exit_fout << "Success" << endl;
	exit_fout << "====================" << endl << endl;
	exit_fout.close();
	//소멸자 호출 break호출
}