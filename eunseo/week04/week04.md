### 게임 맵 최단거리

```python
from collections import deque

dx = [-1, 1, 0, 0]
dy = [0, 0, -1, 1]

def solution(maps):
    q = deque()
    q.append((0,0))
    
    while q:
        r, c = q.popleft()
        for i in range(4):
            nr = r + dx[i]
            nc = c + dy[i]
            
            if nr<0 or nr>=len(maps) or nc<0 or nc>=len(maps[0]):
                continue
            if maps[nr][nc] == 1:
                maps[nr][nc] = maps[r][c] + 1
                q.append((nr, nc))
        
    if maps[len(maps)-1][len(maps[0])-1] == 1:
        return -1
    else:
        return maps[len(maps)-1][len(maps[0])-1]
    
```

- 어떤 알고리즘?
    - BFS

특이사항 X

- 시간/공간 복잡도
    - O(NM)

### 미로 탈출

```python
from collections import deque

def solution(maps):
    dx = [-1, 1, 0, 0]
    dy = [0, 0, -1, 1]

    l_dist = -1
    mintime = -1

    S = 0
    L = 0
    E = 0

    # S, L, E 찾기
    for i in range(len(maps)):
        for j in range(len(maps[i])):
            if maps[i][j] == 'S':
                S = (i, j)
            elif maps[i][j] == 'L':
                L = (i, j)
            elif maps[i][j] == 'E':
                E = (i, j)

    # 1. S -> L BFS
    v = set()
    q = deque()
    q.append((S, 0))
    v.add(S)

    while q:
        (ci, cj), dist = q.popleft()

        if (ci, cj) == L:
            l_dist = dist
            break

        for dr in range(4):
            ni = ci + dx[dr]
            nj = cj + dy[dr]

            if (0 <= ni < len(maps) and
                0 <= nj < len(maps[0]) and
                (ni, nj) not in v and
                maps[ni][nj] != 'X'):

                v.add((ni, nj))
                q.append(((ni, nj), dist + 1))

    if l_dist == -1:
        return -1

    # 2. L -> E BFS
    v = set()
    q = deque()
    q.append((L, 0))
    v.add(L)

    while q:
        (ci, cj), dist = q.popleft()

        if (ci, cj) == E:
            mintime = dist
            break

        for dr in range(4):
            ni = ci + dx[dr]
            nj = cj + dy[dr]

            if (0 <= ni < len(maps) and
                0 <= nj < len(maps[0]) and
                (ni, nj) not in v and
                maps[ni][nj] != 'X'):

                v.add((ni, nj))
                q.append(((ni, nj), dist + 1))

    if mintime == -1:
        return -1

    return l_dist + mintime
```

- 알고리즘
    - BFS
- 해당 알고리즘 선택 이유
    - 최단거리이기 때문에
- 유의점
    - 방문’행렬’이 아니라 set으로 방문 좌표를 관리했음. 레버를 건든 이후에는 방문 좌표를 초기화해야 하기 때문, 시간 복잡도 관리를 위해 set을 활용
- 시간복잡도
    - O(N*M)
- 공간복잡도
    - O(N*M)

### 이모티콘 할인행사

```python
from collections import deque

def solution(users, emoticons):
    answer = []
    q = deque()
    for ds in [10, 20, 30, 40]:
        q.append([ds])

    while q:
        discount = q.popleft()

        if len(discount) == len(emoticons):
            total_price = 0
            plus = 0

            for rate, price in users:
                user_total = 0

                for i in range(len(emoticons)):
                    if discount[i] >= rate:
                        user_total += emoticons[i] * (100 - discount[i]) // 100

                if user_total >= price:
                    plus += 1
                else:
                    total_price += user_total

            answer.append([plus, total_price])

        else:
            for ds in [10, 20, 30, 40]:
                temp = discount[:]
                temp.append(ds)
                q.append(temp)

    answer.sort(key=lambda x: (x[0], x[1]), reverse=True)
    return answer[0]
```

- 알고리즘
    - BFS, 모든 경우의 수를 확인해야하기 때문에, 명확하게 연산량을 줄일 수 있는 부분이 없어서 그리디는 X
- 시간복잡도
    - O(4^M * N * M)
- 공간복잡도
    - O(4^M)