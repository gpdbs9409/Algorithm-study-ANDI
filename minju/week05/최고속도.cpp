#include <bits/stdc++.h>
using namespace std;


// 도로 양 끝, 도로 정중앙(카메라), 도로 위 도시, 두 도로가 만나는 곳
// 좌표 -> 번호 사전
map<pair<int, int>, int> number;

// 처음 보는 좌표면 새 번호를 붙이고, 본 적 있으면 예전 번호를 돌려준다
int getNumber(int x, int y) {
    pair<int, int> p = {x, y};
    if (number.count(p) == 0) {
        int newNum = number.size();
        number[p] = newNum;
    }
    return number[p];
}

vector<int> solution(vector<vector<int>> city, vector<vector<int>> road) {
    int n = city.size();
    int m = road.size();
    int BIG = 1000000000;   // "카메라 없음" -> 큰 제한 속도
    number.clear();

    // 도로마다 위에 있는 중요한 점 모으기
    vector<vector<pair<int, int>>> points(m);
    for (int i = 0; i < m; i++) {
        int x1 = road[i][0];
        int y1 = road[i][1];
        int x2 = road[i][2];
        int y2 = road[i][3];
        points[i].push_back({x1, y1});                        // 시작점
        points[i].push_back({x2, y2});                        // 끝점
        points[i].push_back({(x1 + x2) / 2, (y1 + y2) / 2});  // 카메라
        for (int c = 0; c < n; c++) {                         // 도시
            int cx = city[c][0], cy = city[c][1];
            if (x1 <= cx && cx <= x2 && y1 <= cy && cy <= y2) {
                points[i].push_back({cx, cy});
            }
        }
    }

    // 두 도로가 만나는 점 찾기
    for (int i = 0; i < m; i++) {
        for (int j = i + 1; j < m; j++) {
            int candX[6], candY[6];
            candX[0] = road[j][0]; candY[0] = road[i][1];   // 십자 (i 가로, j 세로)
            candX[1] = road[i][0]; candY[1] = road[j][1];   // 십자 (i 세로, j 가로)
            candX[2] = road[i][0]; candY[2] = road[i][1];   // i의 시작점
            candX[3] = road[i][2]; candY[3] = road[i][3];   // i의 끝점
            candX[4] = road[j][0]; candY[4] = road[j][1];   // j의 시작점
            candX[5] = road[j][2]; candY[5] = road[j][3];   // j의 끝점

            for (int k = 0; k < 6; k++) {
                int x = candX[k], y = candY[k];
                bool onI = (road[i][0] <= x && x <= road[i][2] && road[i][1] <= y && y <= road[i][3]);
                bool onJ = (road[j][0] <= x && x <= road[j][2] && road[j][1] <= y && y <= road[j][3]);
                if (onI && onJ) {
                    points[i].push_back({x, y});
                    points[j].push_back({x, y});
                }
            }
        }
    }

    // 번호 붙이고, 도로마다 옆에 있는 점끼리 연결
    for (int i = 0; i < m; i++) {
        sort(points[i].begin(), points[i].end());
        for (int k = 0; k < points[i].size(); k++) {
            getNumber(points[i][k].first, points[i][k].second);
        }
    }
    int N = number.size();
    vector<vector<int>> adj(N);
    for (int i = 0; i < m; i++) {
        for (int k = 0; k + 1 < points[i].size(); k++) {
            int a = getNumber(points[i][k].first, points[i][k].second);
            int b = getNumber(points[i][k + 1].first, points[i][k + 1].second);
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
    }

    // 점마다 제한 속도 (카메라 없으면 BIG, 겹치면 작은 값)
    vector<int> cam(N, BIG);
    vector<int> cameraPoints;
    for (int i = 0; i < m; i++) {
        int a = getNumber((road[i][0] + road[i][2]) / 2, (road[i][1] + road[i][3]) / 2);
        cam[a] = min(cam[a], road[i][4]);
        cameraPoints.push_back(a);
    }

    // 속도를 큰 값부터 낮춰 가며 BFS
    vector<int> best(N, -1);
    queue<int> q;
    int start = getNumber(city[0][0], city[0][1]);
    best[start] = BIG;
    q.push(start);

    vector<int> speeds;
    speeds.push_back(BIG);                       // 첫 번째: 카메라 없이
    for (int i = 0; i < m; i++) speeds.push_back(road[i][4]);
    sort(speeds.begin(), speeds.end());
    reverse(speeds.begin(), speeds.end());       // 큰 것부터

    for (int s = 0; s < speeds.size(); s++) {
        int v = speeds[s];

        // 지나갈 수 있게 된 카메라 중, 이미 도착한 점 옆에 있는 것 → 큐에 넣기
        for (int k = 0; k < cameraPoints.size(); k++) {
            int c = cameraPoints[k];
            if (best[c] != -1) continue;
            if (cam[c] < v) continue;
            for (int t = 0; t < adj[c].size(); t++) {
                if (best[adj[c][t]] != -1) {
                    best[c] = v;
                    q.push(c);
                    break;
                }
            }
        }

        // BFS
        while (!q.empty()) {
            int now = q.front();
            q.pop();
            for (int t = 0; t < adj[now].size(); t++) {
                int next = adj[now][t];
                if (best[next] != -1) continue;   // 이미 가 본 곳
                if (cam[next] < v) continue;      // 카메라에 걸림
                best[next] = v;
                q.push(next);
            }
        }
    }

    // 답 만들기
    vector<int> answer;
    for (int c = 1; c < n; c++) {
        int a = getNumber(city[c][0], city[c][1]);
        if (best[a] == BIG) answer.push_back(0);
        else answer.push_back(best[a]);
    }
    return answer;
}