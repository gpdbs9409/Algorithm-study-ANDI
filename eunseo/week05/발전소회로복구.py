from collections import deque

def solution(h, grid, panels, seqs):
    n, m = len(grid), len(grid[0])
    k = len(panels)

    for i in range(n):
        for j in range(m):
            if grid[i][j] == '@':
                er, ec = i, j

    def bfs(sr, sc):
        dist = [[-1] * m for _ in range(n)]
        dist[sr][sc] = 0
        q = deque([(sr, sc)])
        while q:
            r, c = q.popleft()
            for dr, dc in ((1, 0), (-1, 0), (0, 1), (0, -1)):
                nr, nc = r + dr, c + dc
                if 0 <= nr < n and 0 <= nc < m and grid[nr][nc] != '#' and dist[nr][nc] == -1:
                    dist[nr][nc] = dist[r][c] + 1
                    q.append((nr, nc))
        return dist

    # 패널마다 한 층 기준 거리
    pos = [(f, r - 1, c - 1) for f, r, c in panels]
    d = [bfs(r, c) for _, r, c in pos]

    # 패널 간 이동 시간
    cost = [[0] * k for _ in range(k)]
    for i in range(k):
        fi, ri, ci = pos[i]
        for j in range(k):
            fj, rj, cj = pos[j]
            if fi == fj:
                cost[i][j] = d[i][rj][cj]
            else:
                cost[i][j] = d[i][er][ec] + abs(fi - fj) + d[j][er][ec]

    # 선행 패널 비트마스크
    pre = [0] * k
    for a, b in seqs:
        pre[b - 1] |= 1 << (a - 1)

    INF = float('inf')
    full = (1 << k) - 1
    dp = [[INF] * k for _ in range(1 << k)]
    dp[0][0] = 0  # 1번 패널 위치에서 시작

    for mask in range(1 << k):
        row = dp[mask]
        for i in range(k):
            t = row[i]
            if t == INF:
                continue
            for j in range(k):
                if mask >> j & 1 or pre[j] & mask != pre[j]:
                    continue
                nt = t + cost[i][j]
                nxt = dp[mask | 1 << j]
                if nt < nxt[j]:
                    nxt[j] = nt

    return min(dp[full])



