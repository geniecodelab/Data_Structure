# 자료구조 프로젝트 모음 (광운대학교 2025-2학기)

자료구조 수업의 프로젝트 3개를 C++로 구현한 저장소입니다.
클래스와 파일 구성은 과제로 제공된 스켈레톤 코드를 따랐고, 자료구조와 알고리즘은 직접 구현했습니다.

| 프로젝트 | 주제 | 사용한 자료구조·알고리즘 |
|---|---|---|
| [01-music-playlist](01-music-playlist) | 음악 플레이리스트 | 큐, 이진 탐색 트리 2개(가수·제목 기준), 원형 연결 리스트 |
| [02-employee-bptree](02-employee-bptree) | 직원 정보 관리 | B+트리(이름 정렬), Selection Tree(Max Winner Tree), Max Heap(연봉) |
| [03-graph-algorithms](03-graph-algorithms) | 그래프 탐색 | 인접 리스트·인접 행렬, BFS, DFS, Kruskal, Dijkstra, Bellman-Ford, Floyd, 근접 중심성 |

## 개발 환경
- Ubuntu 22.04, g++ (C++11), make

## 빌드와 실행
```bash
cd 01-music-playlist        # 다른 프로젝트도 동일
make                        # 실행 파일 ./run 생성
make demo                   # examples/ 입력으로 실행하고 examples/expected_log.txt와 비교
make clean
```
프로그램은 실행한 폴더의 `command.txt` 등 입력 파일을 읽고, 결과를 같은 폴더의 `log.txt`에 기록합니다.
직접 실행하려면 `examples/`의 입력 파일을 `./run`과 같은 폴더에 복사한 뒤 실행하세요.

## 검증 방법
- 01: 과제에서 제공된 예시 명령어와 예시 출력 로그를 대조했습니다.
- 02: 직원 300명을 무작위로 넣어 B+트리의 정렬·중복 여부를 확인했고, B+트리 차수를 3, 4, 5, 7로 바꿔 동작을 확인했습니다.
- 03: 명세서의 예시 그래프에서 예시 출력과 같은 결과가 나오는지 확인했습니다.
- 세 프로젝트 모두 AddressSanitizer·UBSan·LeakSanitizer(`g++ -fsanitize=address,undefined`)로 예제 입력을 실행해 오류와 메모리 누수가 없음을 확인했습니다.

## 과제 제출 후 다시 검증하며 고친 내용
- **01:** 존재하지 않는 곡을 `SEARCH SONG`으로 찾으면 프로그램이 종료되던 문제를 고쳐 오류 코드 400을 출력하도록 했습니다. 재생 시간의 초가 한 자리일 때 `4:5`로 나오던 것을 `4:05`로, `PRINT TITLE`·`PRINT LIST`의 제목 표기를 명세 예시와 같게 맞췄습니다.
- **02:** `SelectionTree::Insert`에 반환문이 없어 `ADD_ST` 실행 시 비정상 종료되던 문제를 고쳤습니다. 인자가 부족한 명령어(`ADD_BP`, `SEARCH_BP`, `ADD_ST`, `PRINT_ST`)가 이후 명령어 처리를 막던 문제를 고치고, 범위 검색에서 끝 글자로 시작하는 이름이 빠지던 문제를 고쳤습니다. 소멸자를 구현해 메모리 누수를 없애고, B+트리 차수를 생성자 인자로 받도록 연결했습니다.
- **03:** 나가는 간선이 없는 정점을 `PRINT`할 때 `[3] ->`로 표기하도록 명세 예시에 맞췄습니다.

## 알려진 한계
- 03의 근접 중심성은 어느 정점에서도 도달할 수 없는 정점이 그래프에 하나라도 있으면 모든 정점을 `x`로 출력합니다. 명세의 예외 처리 문구를 어떻게 해석하느냐에 따라 달라질 수 있는 부분입니다.
- 01은 실행 중 디버그용 한글 메시지를 콘솔에 출력하고, `-Wall`에서 부호 비교 경고가 나옵니다(동작에는 영향 없음).

## 출처
스켈레톤 코드: [Project 1](https://github.com/Elechun/2025_Kwangwoon_DS_Project_1), [Project 2](https://github.com/evejaeyong/2025_Kwangwoon_DS_Project_2), [Project 3](https://github.com/KimTaegwan03/2025_Kwangwoon_DS_Project_3)
과제 명세서는 수업 자료이므로 이 저장소에 포함하지 않았습니다.
