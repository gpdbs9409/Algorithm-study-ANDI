#include <bits/stdc++.h>
using namespace std;

int solution(int k, vector<vector<int>> dungeons) {
   int n = dungeons.size();
   int answer = 0;

   vector<int> order;
   for (int i = 0; i < n; i++) {
       order.push_back(i);
   }

   do {
       int fatigue = k;
       int count = 0;

       for (int i = 0; i < n; i++) {
           int index = order[i];

           int required = dungeons[index][0];
           int cost = dungeons[index][1];

           if (fatigue < required) {
               break;
           }

           fatigue -= cost;
           count++;
       }

       answer = max(answer, count);

   } while (next_permutation(order.begin(), order.end()));

   return answer;
}

