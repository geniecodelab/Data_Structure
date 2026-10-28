#include "PlayList.h"
#include "PlayListNode.h"

PlayList::PlayList() 
{
	head = nullptr;
	cursor = nullptr;
	count = 0;
	time = 0;
	data = "";
}

PlayList::~PlayList() 
{
	//cursor로 돌며 삭제
	if(empty())//비어있는경우
	{
		return;
	}
	else
	{
		//1.순환에서 일반 링크드리스트로
		head->prev->next = nullptr;
		cursor = head;//시작부설정
		PlayListNode* for_delete = nullptr;//진짜 삭제 대상
		
		while (cursor != nullptr)//위에서 설정한 끊어진 마지막이 될때까지
		{
			for_delete = cursor;//커서로 이동
			cursor = cursor->next;//커서는 다음으로 이동
			delete for_delete;//이전 노드 삭제
		}
		//아예 도입부 끊기
		head = nullptr;
	
		
	}
	
}

void PlayList::insert_node(string input_artist, string input_title, int input_run_time) 
{
	ofstream insert_flog;
	insert_flog.open("log.txt", ios::app);//로그에 기록하기위함.
	
	PlayListNode* new_node=new PlayListNode(input_artist, input_title, input_run_time);//노드생성
	
	
	
	if(empty())
	{
		head = new_node;
		head->next = new_node;//다음것도 자기자신
		head->prev = new_node;//이전도 자기자신
		count++;//플리수 1 증가
		time = time + input_run_time;//시간 갱신
	}
	else
	{
		//비어있지않은 경우
		if(full())//10곡까지 넣을 수 있으니.
		{
			/*cout << "playlist에 내용이 가득찼습니다.." << endl;
			insert_flog << "========ERROR========" << endl;//에러코드
			insert_flog << "500" << endl;
			insert_flog << "=====================" << endl << endl;*/
		}
		else
		{
			
			//공간이 있는경우
			//바로 삽입
			cursor = head->prev;//마지막 노드

			//삽입(마지막과의 연결)
			cursor->next = new_node;
			new_node->prev = cursor;

			//삽입2(head와의 연결)
			head->prev = new_node;
			new_node->next = head;


			count++;//수 증가
			time = time + input_run_time;//시간 갱신
		}



	}
	
	insert_flog.close();
}

void PlayList::delete_node(string input_artist, string input_title)
{
	ofstream delete_flog;
	delete_flog.open("log.txt", ios::app);//로그에 기록하기위함.
	
	//있다는 가정하에
	//커서로 탐색
	cursor = head;//시작부터

	do 
	{
		if(cursor->artist==input_artist&&cursor->title==input_title)
		{
			//찾은 경우.

			//예외처리(count가 1인 경우)
			if(count==1)
			{
				head = nullptr;
				time = 0;
				count = 0;
				data = "";//전부 초기상태로
			}
			else
			{
				if (cursor == head)
				{
					//헤드의 제할당
					head = head->next;

					//연결
					head->prev = cursor->prev;//헤드의 이전 변경
					cursor->prev->next = head;//이전거으 다음은 헤드
				}
				else
				{
					//이전노드의 연결 해제
					cursor->prev->next = cursor->next;//다음걸로 연결
					//다음 노드와의 연결해제
					cursor->next->prev = cursor->prev;//이전걸로 연결
				}
				count--;//수 감소.
				time = time - cursor->runtime_sec;//시간감소

			}

			
			
			delete cursor;//메몰리해제
			cursor = nullptr;//멤버 변수로 써야하기에
			//삭제는 manager에서 출력

			return;//반복문 및 함수 종료
		}
		cursor=cursor->next;//다음으로이동
	}while(cursor != head);//한바퀴를 돌때까지
	
	
	
	delete_flog.close();
}

bool PlayList::empty() 
{
	if(count==0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool PlayList::full() 
{
	if (count == 10)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool PlayList::exist(string input_artist, string input_title)
{
	
	if(head==nullptr)
	{
		return false;//플리가없는경우
	}
	else
	{
		cursor = head;
		//한바퀴 돌때까지 반복
		do
		{
			if(cursor->artist==input_artist&&cursor->title==input_title)
			{
				return true;
			}
			cursor=cursor->next;

		} while (cursor != head);
		//못찾은 경우
		return false;
	}
}

string PlayList::print() 
{
	//bst가 비어있는지 확인
	if (head == nullptr)
	{
		//비어있는경우
	
		return "";//공백 출력//이때는 외부에 오류코드로 읽기
	}
	else
	{
		cursor = head;//탐색을 위해
		stringstream imsi;//문자열합치기위헤
		do
		{
			//초단위의 시간 분과 초로계산
			int imsi_min = cursor->runtime_sec / 60;//몫만 남기에 분 반환

			imsi << cursor->artist << "/" << cursor->title << "/" << imsi_min << ":" << (cursor->runtime_sec % 60 < 10 ? "0" : "") << cursor->runtime_sec % 60 << endl;//stringstream으로 정수 및 문자열 합치기
			cursor = cursor->next;//다음으로 이동

		} while (cursor != head);//다시 돌아왔는가?
		//끝까지 내용저장
		imsi << "Count : " << count << " / 10" << endl;//count 반영
		imsi << "Time : " << time / 60 << "min " << time % 60 << "sec" << endl;//플레이리스트 시간 반영

		data = imsi.str();//문자열로의 변환
		
		return data;
	}
	
}

int PlayList::run_time() 
{
	return time;//초의 반환
}

