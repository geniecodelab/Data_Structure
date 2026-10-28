# 02. 직원 정보 관리 (B+트리 · Selection Tree · Heap)

직원 정보(이름, 부서 코드, 사번, 연봉)를 B+트리에 이름순으로 저장하고, 부서별 Max Heap과 이를 묶는 Selection Tree로 연봉 순위를 관리합니다.

## 구조
```
employee.txt ──LOAD / ADD_BP──▶ B+트리 (이름 오름차순)
                                   │ ADD_ST (부서 코드 또는 이름으로 선택)
                                   ▼
              Selection Tree (Max Winner Tree, 연봉 기준)
              └ run 8개 = 부서 코드 100~800, 각 run은 연봉 Max Heap
```
- `BpTree`, `BpTreeIndexNode`, `BpTreeDataNode`: 차수는 `main.cpp`의 `Manager manager(3)`에서 지정 (3, 4, 5, 7에서 동작 확인)
- `SelectionTree`, `SelectionTreeNode`: 포인터로 연결한 Winner Tree
- `EmployeeHeap`: 배열 기반 Max Heap (0번 인덱스 미사용)
- `Manager`: `command.txt`의 명령어를 읽어 조율

## 입력 파일
- `employee.txt`: `이름<TAB>부서코드<TAB>사번<TAB>연봉`, 한 줄에 한 명
- `command.txt`: 인자는 탭으로 구분

## 명령어
| 명령어 | 동작 | 오류 코드 |
|---|---|---|
| `LOAD` | `employee.txt`를 읽어 B+트리 구성 | 100 |
| `ADD_BP 이름 부서 사번 연봉` | 직원 추가 (이미 있으면 연봉만 갱신) | 200 |
| `SEARCH_BP 이름` / `SEARCH_BP 시작 끝` | 이름 검색 / 범위 검색 (끝 글자로 시작하는 이름 포함) | 300 |
| `PRINT_BP` | 이름 오름차순 전체 출력 | 400 |
| `ADD_ST dept_no 코드` / `ADD_ST name 이름` | B+트리의 데이터를 Selection Tree로 복사 | 500 |
| `PRINT_ST 코드` | 해당 부서를 연봉 내림차순으로 출력 | 600 |
| `DELETE` | Selection Tree의 루트(최고 연봉자) 삭제 후 재정렬 | 700 |
| `EXIT` | 메모리를 해제하고 종료 | - |
| 그 밖의 명령어 | 잘못된 명령어 | 800 |

인자가 부족하거나 많은 경우에도 해당 명령어의 오류 코드를 출력하고 다음 명령어로 넘어갑니다.

## 실행
```bash
make && make demo
```
