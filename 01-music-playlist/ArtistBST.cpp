#include "ArtistBST.h"


ArtistBST::ArtistBST() 
{
	root = nullptr;
	target = nullptr;
	parent = nullptr;
}
ArtistBST::~ArtistBST() 
{
	//postder 방식을 통한 소멸
	delete_post_order(root);//추가 구현함수
}

void ArtistBST::insert(string input_title, string input_artist, string input_run_time) 
{
	//오직 삽입만.

	//루트가 비어있는가?(탐색)
	if (root == nullptr)
	{
		ArtistBSTNode* new_node = new ArtistBSTNode(input_title, input_artist, input_run_time);//노드 생성
		root = new_node;

	}
	else
	{
		target = root;//일단 초기화
		parent = root;
		while (target != nullptr && input_artist != target->artist)//끝까지 가거나 같은 거 찾은 경우.
		{

			if (input_artist > target->artist)
			{
				//삽입이 더 큰 경우.
				parent = target;
				target = target->right;//오른편으로 이동
			}
			else
			{
				parent = target;
				target = target->left;
			}
		}

		//삽입(만약 동일할 경우 노드 생성은 필요없다.)
		if (target != nullptr)
		{
			target->set(input_title, input_run_time);//노드의 set함수 이용

		}
		else
		{
			ArtistBSTNode* new_node = new ArtistBSTNode(input_title, input_artist, input_run_time);//노드 생성
			//어느쪽인지 확인
			if (input_artist > parent->artist)
			{
				//생성값이 더 큰 경우
				parent->right = new_node;

			}
			else
			{
				parent->left = new_node;
			}
		}

	}

}

void ArtistBST::search(string input_artist)
{

	ofstream search_flog;
	search_flog.open("log.txt", ios::app);//로그에 기록하기위함.
	//어짜피 가수 그자체.
	
	//동일한 제목이 있는지 확인하는 용도.
	if (root == nullptr)
	{
		//bst가 비어져있는경우.
			//못찾아서 끝난 경우. 
		cout << "ArtistBst에 내용이 존재하지않습니다." << endl;
		search_flog << "========ERROR========" << endl;//에러코드
		search_flog << "400" << endl;
		search_flog << "=====================" << endl << endl;
	}
	else
	{
		target = find_node(input_artist).first;//새롭게 생성한 함수 호출을 통한 처리

		//while문의 종료가 찾아서 끝난건가?
		if (target != nullptr)//반대로 하면 nullptr의 title을 읽으려함.
		{
			//시간 string 파싱.
			stringstream for_run_time(target->run_time);
			string imsi;

			search_flog << "========SEARCH========" << endl;
			for (int i = 0; i < target->count; i++) //가지고 있는 동일 제목 곡 모두 방출
			{
				getline(for_run_time, imsi, '|');//문자열 파싱
				search_flog << target->artist << "/" << target->title[i] << "/" << imsi << endl;//읽어들인 내용 그대로 다시 작성
			}
			search_flog << "=====================" << endl << endl;//종료
		}
		else
		{
			//못찾아서 끝난 경우. 
			cout << "찾으려는 Artist가 존재하지않습니다." << endl;
			search_flog << "========ERROR========" << endl;//에러코드
			search_flog << "400" << endl;
			search_flog << "=====================" << endl << endl;

		}



	}

	search_flog.close();
}

void ArtistBST::call_print(ofstream& flog, ArtistBSTNode* input)
{
	//재귀처리
	if (input == nullptr)
	{
		//끝까지 간 경우 켜놓은 함수 하나 종료+ 다음 줄 실행
		return;
	}
	call_print(flog, input->left);//왼편으로 이동


	//출력
	stringstream for_run_time(input->run_time);//문자열 파싱
	string imsi;
	for (int i = 0; i < input->title.size(); i++) //가지고 있는 동일 제목 곡 모두 방출
	{
		getline(for_run_time, imsi, '|');//문자열 파싱
		flog << input->artist << "/" << input->title[i] << "/" << imsi << endl;//읽어들인 내용 그대로 다시 작성
	}
	call_print(flog, input->right);//오른편이 없다면, 해당 left 종료 및 parent로 이동/


}


void ArtistBST::print()
{
	ofstream print_flog;//파일 쓰기
	print_flog.open("log.txt", ios::app);//로그에 기록하기위함.


	//bst가 비어있는지 확인
	if (root == nullptr)
	{
		//비어있는경우
		print_flog << "========ERROR========" << endl;//에러코드
		print_flog << "600" << endl;
		print_flog << "=====================" << endl << endl;
	}
	else
	{
		//재귀함수를 통한 구현

		target = root;
		parent = nullptr;
		
		print_flog << "========PRINT========" << endl;//에러코드
		print_flog << "ArtistBST" << endl;
		call_print(print_flog, target);//재귀함수용 호출
		print_flog << "=====================" << endl << endl;
	}
	print_flog.close();

}

void ArtistBST::delete_node(string input, string input_title)
{
	ofstream delete_flog;
	delete_flog.open("log.txt", ios::app);//로그에 기록하기위함.





	//탐색하기
	if (root == nullptr)
	{
		//탐색 대상 없어 오류 발생

		delete_flog << "========ERROR========" << endl;//에러코드
		delete_flog << "700" << endl;
		delete_flog << "=====================" << endl << endl;
		return;


	}
	else
	{

		pair<ArtistBSTNode*, ArtistBSTNode*>imsi_node = find_node(input);//찾으면 노드 넘기고 아니면 nullptr넘길 것.
		ArtistBSTNode* for_delete_target = imsi_node.first;
		ArtistBSTNode* for_delete_parent = imsi_node.second;





		if (for_delete_target == nullptr)
		{
			//못찾은경우 오류발생
			delete_flog << "========ERROR========" << endl;//에러코드
			delete_flog << "700" << endl;
			delete_flog << "=====================" << endl << endl;
			return;
		}
		else
		{
			//song을 입력받은경우
			if (input_title != "")
			{
				//search를 통해 삭제
				for_delete_target->search(input, input_title);//탐색 및 삭제
				return;
			}
			//그렇지않은경우

			
			
			//자식조사
			if (for_delete_target->left != nullptr && for_delete_target->right != nullptr)//자식을 두개 가질 경우
			{

				target = for_delete_target->right;//자식 탐색을 위한
				parent = for_delete_target;

				while (target->left != nullptr)
				{
					parent = target;
					target = target->left;
				}



				//오른편에 딸린 자식이 있다면 위치 대체하기
				if (parent->left == target)//좌측으로 넘어간경우
				{
					parent->left = target->right;//없으면 자동 nullptr대입
				}
				else//우측에서 좌측으로 못넘어간 상황
				{
					parent->right = target->right;
				}

				//노드 대체(포인터를 제외하고, 나머지 내용 전부다 복사하기)
				for_delete_target->artist = target->artist;//값 복사하기
				for_delete_target->title = target->title;
				for_delete_target->run_time = target->run_time;
				for_delete_target->rt = target->rt;
				for_delete_target->count = target->count;

				delete target;//타겟노드 삭제//덮어쓴 기존의 노드 삭제(대체노드 삭제)

			}
			else
			{
				if (for_delete_target->left == nullptr && for_delete_target->right == nullptr)//자식이 없는 경우
				{

					//삭제만 하면된다.

					if (for_delete_target == root)
					{
						delete root;//루트 삭제
						root = nullptr;//삭제대상이 루트인경우
					}
					else
					{
						if (for_delete_parent->left == for_delete_target)//부모 대체 
						{
							for_delete_parent->left = nullptr;
						}
						else
						{
							for_delete_parent->right = nullptr;
						}
						delete for_delete_target;//삭제

					}

				}
				else
				{
					//삭제대상이 한개인 경우
					target = for_delete_target;//탐색을 위해
					parent = for_delete_parent;


					if (for_delete_target == root)//삭제대상이 루트인 경우
					{


						if (root->left != nullptr)
						{
							ArtistBSTNode* imsi_root = root->left;//delete가 이뤄져야 누수가 발생하지않기에 바로 덮어쓰지말고 임시롬 답고있다가 delete 후 대입
							delete root;
							root = imsi_root;
						}
						else
						{
							ArtistBSTNode* imsi_root = root->right;
							delete root;
							root = imsi_root;
						}
					}
					else
					{
						//부모의 연결 바꾸기
						if (for_delete_parent->left == for_delete_target)
						{
							if (for_delete_target->left != nullptr)//자식이 어디에 있는가?
							{
								for_delete_parent->left = target->left;
							}
							else
							{
								for_delete_parent->left = target->right;
							}


						}
						else
						{
							if (for_delete_target->left != nullptr)//자식이 어디에 있는가?
							{
								for_delete_parent->right = target->left;
							}
							else
							{
								for_delete_parent->right = target->right;
							}
						}

						delete for_delete_target;//노드 1개일 경우 연결 후, 삭제노드 삭제


					}



				}

			}


			







		}
	}

	delete_flog.close();



}



pair<ArtistBSTNode*, ArtistBSTNode*> ArtistBST::find_node(string input, string song_title)//추가로 생성한 함수
{
	target = root;//탐색노드 생성
	parent = nullptr;//부모 노드 기억
	while (target != nullptr && target->artist != input)//더이상 탐색할 것이 없거나, 동일한 거 찾을 때까지 반복
	{
		//찾지 못한경우.

		//알파벳 비교 후 다음 노드로의 이동
		if (target->artist > input)
		{
			//찾으려는 대상이 더 작은 경우--> 왼편으로 이동.
			parent = target;
			target = target->left;
		}
		else
		{
			parent = target;
			target = target->right;
		}
	}
	if (target != nullptr)
	{
		//찾은 경우.
		if (song_title != "")//song을 입력받은 경우
		{
			for (int i = 0; i < target->title.size(); i++)
			{
				if (target->title[i] == song_title)//song에서 둘 다 동일 한 거를 찾은 경우
				{
					return pair<ArtistBSTNode*, ArtistBSTNode*>(target, parent);//정석적인 반환 방법
				}

			}
			//끝까지 못찾은 경우
			return { nullptr,nullptr };//찾는 대상이 없을경우
		}
		else
		{
			return pair<ArtistBSTNode*, ArtistBSTNode*>(target, parent);//정석적인 반환 방법
		}
	}
	else
	{
		return { nullptr,nullptr };//찾는 대상이 없을경우
	}
}

void ArtistBST::delete_post_order(ArtistBSTNode* input)
{

	//root 입력
	if (input == nullptr)
	{
		return;//끝까지 왼편 갔으면 종료
	}

	delete_post_order(input->left);//가장 왼편으로 이동
	delete_post_order(input->right);//
	delete input;
	root = nullptr;//주소는 남아있기에, 주소도 해제(그렇지않으면 소멸자에서 루트만이라도 nullptr)

}



vector<pair<string, pair<string, int>>> ArtistBST::for_pl(string input)
{
	
	ArtistBSTNode* insert = find_node(input).first;//노드 탐색
	vector<pair<string, pair<string, int>>> a;//객체 생성
	if(insert==nullptr)
	{
		//오류
		
		
	}
	else
	{
		
		for(int i = 0; i < insert->title.size() && insert->rt.size(); i++)//있는 원소만큼 vector의 원소 생성
		{
			
			
			a.push_back({ insert->artist, {insert->title[i], insert->rt[i]} });//3개자료형, pair 두개 대입, pair와 string, pair는 또다시 플레이리스트와 시간
		}
		;
	}
	
	return a;//빈내용일수도 차있을수도
}