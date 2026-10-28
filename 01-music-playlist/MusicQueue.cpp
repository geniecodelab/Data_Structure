#include "MusicQueue.h"
#include<iostream>


MusicQueue::MusicQueue() {
	head = nullptr;
	rear = nullptr;
}

MusicQueue::~MusicQueue() {
	//pop함수를 이용한 기존의 메모리해제
	
	while(!empty())//빌때까지
	{
		MusicQueueNode* imsi = pop();
		delete imsi;//pop된 헤드 삭제
	}
}

bool MusicQueue::empty() 
{
	if(size==0)//아무것도 없는경우
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool MusicQueue::exist(string recieve_artist, string recieve_title) 
{
	//탐색 가수+곡 모두 동일한지
	//처음부터 탐색

	//비어 있거나, 아예 없거나
	MusicQueueNode* for_search = head;
	
	while(for_search!=nullptr)//nullptr이 될때까지 반복
	{
		if(for_search->artist==recieve_artist&&for_search->title==recieve_title)
		{
			//동일 곡 찾은경우
			return true;
		}
		else
		{
			//못찾은 경우
			for_search = for_search->next;//다음으로 이동
		}
	
	}
	return false;
	
	
}

void MusicQueue::push(string recieve_artist, string recieve_title, string recieve_run_time) {
	//입력가능한 상태에서일듯.
	
	if(size>=100)//다 찼을경우.
	{
		cerr << "삽입 시 큐의 용량이 100을 넘김"<<endl<<"프로그램 비정상 종료합니다."<<endl;
		//프로그램 종료조건
		exit(1);//비정상종료
	}
	else
	{

		MusicQueueNode* new_node = new MusicQueueNode(recieve_artist, recieve_title, recieve_run_time);//노드 생성(포인터의 형태)

		if (empty())//비어있는경우.
		{
			//첫삽입의 경우.
			head = new_node;//처음노드
			rear = new_node;//일단 없으닌까.
		}
		else
		{
			//이미 들어있는경우
			rear->next = new_node;//기존의 노드 다음주소할당
			new_node->prev = rear;//새로운 노드 이전주소 연결
			rear = new_node;
		}
		size++;//사이즈 증가
	}
	
	

}

MusicQueueNode* MusicQueue::pop()//앞에 추출 및 큐 전체 갱신-> 내용을 가져야하니, 삭제는 하지말고, 연결관계만 끊기
{
	//비어있는가?(조건 확인)
	//출력
	//탐색노드로 이동
	MusicQueueNode* for_search = head;//전달할 내용
	if(empty())//헤드는 있는가?
	{
		cerr << "현재 큐가 비어있습니다." << endl << "프로그램 비정상 종료합니다." << endl;
		//프로그램 종료조건
		exit(1);//비정상종료
	}
	else
	{
		//출력후 next prev재정비
		head = head->next;//헤드 갱신
		if(head==nullptr)
		{
			//만약 하나 있을 떄 뽑았을 경우
			rear = nullptr;
		}
		else
		{
			head->prev = nullptr;//이전 내용 잊기
		}
		size--;//사이즈 줄이기
		return for_search;
	}
}

MusicQueueNode* MusicQueue::front() 
{
	return head;//앞에만 확인
}