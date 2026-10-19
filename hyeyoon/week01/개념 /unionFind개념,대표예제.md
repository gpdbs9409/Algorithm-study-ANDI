# Union-Find (유니언 파인드)

## 1. 개념

유니언 파인드를 이해할 때 C의 포인터 개념을 떠올렸다.

포인터는 메모리의 값 자체가 아니라 메모리 주소를 저장하고, 해당 주소를 통해 값에 접근한다.

유니언 파인드는 포인터와 동일한 개념은 아니지만, 여러 원소가 하나의 대표를 가리키도록 관리한다는 점에서 비슷하다고 생각했다.

기본적으로 유니언 파인드는 큐, 스택, 힙처럼 특정 목적을 위해 만들어진 자료구조이다. 그러나 Python 표준 라이브러리에서 기본 제공되지 않기 때문에 직접 구현해서 사용한다.

'서로소 집합(Disjoint Set)'을 관리할 때 사용하며, 원소들의 그룹을 합치고 같은 그룹에 속하는지 확인할 수 있다.

## 2. 동작 원리

초기 상태에서는 모든 원소가 자기 자신을 가리킨다.

```text
1 → 1
2 → 2
3 → 3
4 → 4
5 → 5
```

union(1, 2)를 실행하면 다음과 같다.

```text
1 ← 2

parent[1] = 1
parent[2] = 1
```

이후 union(2, 3)을 실행하면 다음과 같다.

```text
    1
   / \
  2   3
```

union(2, 3)은 2와 3을 합치는 명령이지만, 실제로는 2가 속한 그룹의 대표인 1을 찾아 3을 해당 그룹에 연결한다.

즉, 3을 2와 합친다고 명시했지만 사실은 1의 그룹에 들어가는 것이다.

## 3. Find

```python
def find(x):
    if parent[x] == x:
        return x

    parent[x] = find(parent[x])
    return parent[x]
```

그룹의 대표를 찾는 함수이다.

- parent 배열은 각 원소의 부모를 저장한다.
- 인덱스는 원소, 값은 해당 원소의 부모이다.
- 부모가 자기 자신이면 그룹의 대표이다.
- 부모가 자기 자신이 아니라면 재귀적으로 최종 대표를 찾는다.
- `parent[x] = find(parent[x])`는 경로 압축으로, 탐색 과정에서 최종 대표를 직접 가리키도록 갱신한다.

## 4. Union

```python
def union(a, b):
    root_a = find(a)
    root_b = find(b)

    if root_a != root_b:
        parent[root_b] = root_a
```

a, b의 대표값을 찾는다.

두 대표값이 동일하지 않다면 한쪽 그룹의 대표를 다른 그룹의 대표에 연결한다.

이미 대표값이 동일하다면 같은 그룹에 속해 있으므로 별도로 연결할 필요가 없다.

---
대표예제 

백준 집합 표현하기 


```python
#parent배열선언
parents=[]

for i in range(len(nodes))
    parent.append(i)


#union함수 구현 >parent를 합침 
def union(a,b):
    a=find(a)
    b=find(b)
    if a!=b:
        parent[b]=a
#find함수 구현 
    
    


1.문자열을 공백단위로 split한다 . 
for command in commands:
    command.split()
     #0으로 시작하면 union 해서 합함 
    if command[0]=0:
        union

    #1로 시작하면 find해서 두 노드가 동일한 parent를 가졌는지 확인함 
```
