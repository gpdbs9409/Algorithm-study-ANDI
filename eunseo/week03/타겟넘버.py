# 모든 경우의 수 세기

from collections import deque

def solution(numbers, target):
    q = deque()
    q.append(0)    
    for idx in range(len(numbers)):
        num = numbers[idx]
        temp = []
        while q:
            val = q.popleft()
            temp.append(val+num)
            temp.append(val-num)
        q.extend(temp)
    ans = 0
    while q:
        n = q.pop()
        if n==target:
            ans+=1
            
    return ans