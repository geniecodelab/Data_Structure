# 01. 음악 플레이리스트

음악 데이터 파일을 큐에 적재하고, 꺼낸 곡으로 가수 기준·제목 기준 이진 탐색 트리를 만든 뒤, 두 트리를 이용해 원형 연결 리스트 형태의 플레이리스트를 구성합니다.

## 구조
```
Music_List.txt ──LOAD──▶ MusicQueue ──QPOP──▶ ArtistBST (가수 이름 기준)
                                           └▶ TitleBST  (노래 제목 기준)
                          MAKEPL (두 BST 검색 결과) ──▶ PlayList (원형 연결 리스트, 최대 10곡)
```
- `MusicQueue` / `MusicQueueNode`: 크기 100의 큐
- `ArtistBST`, `TitleBST`: 삽입·삭제·검색·중위 순회 출력. 양쪽 자식이 있는 노드를 지울 때는 오른쪽 서브트리의 최솟값 노드로 대체
- `PlayList` / `PlayListNode`: 곡 추가·삭제·검색·출력, 총 재생 시간 갱신
- `Manager`: `command.txt`의 명령어를 읽어 위 클래스들을 조율

## 입력 파일
- `Music_List.txt`: `가수|제목|m:ss` 형식, 한 줄에 한 곡
- `command.txt`: 한 줄에 명령어 하나 (명령어는 대문자)

## 명령어
| 명령어 | 동작 | 오류 코드 |
|---|---|---|
| `LOAD` | `Music_List.txt`를 읽어 큐 구성 (이미 데이터가 있으면 오류) | 100 |
| `ADD 가수\|제목\|m:ss` | 큐에 곡 추가 (중복이면 오류) | 200 |
| `QPOP` | 큐의 모든 곡을 꺼내 두 BST 구성 | 300 |
| `SEARCH ARTIST 가수` / `TITLE 제목` / `SONG 가수\|제목` | BST 검색 | 400 |
| `MAKEPL ARTIST 가수` / `TITLE 제목` / `SONG 가수\|제목` | 플레이리스트에 추가 (최대 10곡) | 500 |
| `PRINT ARTIST` / `TITLE` / `LIST` | BST 중위 순회 또는 플레이리스트 출력 | 600 |
| `DELETE ARTIST 가수` / `TITLE 제목` / `LIST 가수\|제목` / `SONG 가수\|제목` | 삭제 | 700 |
| `EXIT` | 메모리를 해제하고 종료 | - |
| 그 밖의 명령어 | 잘못된 명령어 | 1000 |

## 실행
```bash
make && make demo
```
`log.txt`가 이미 있으면 뒤에 이어서 기록합니다. 그래서 `make demo`는 별도 폴더(`demo_out/`)에서 실행합니다.
