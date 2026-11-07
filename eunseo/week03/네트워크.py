## 방문한 컴퓨터를 전부 표시

from collections import deque


def solution(n, computers):
    v = [0]*n
    net = 0
    for idx in range(n):
        if v[idx] == 0:
            net += 1
            q = deque()
            q.append(idx)
            while q:
                tidx = q.popleft()
                temp = computers[tidx]
                for cidx in range(len(temp)):
                    if temp[cidx] == 1 and v[cidx] == 0:
                        v[cidx] = 1
                        q.append(cidx)
                
    return net