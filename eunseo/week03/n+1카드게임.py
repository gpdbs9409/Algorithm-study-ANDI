# from collections import deque
# from itertools import combinations


# def solution(coin, cards):
#     result_round = 0
#     n = len(cards)  # [수정] n+1 계산용
#     # 1. 카드에서 n/3 뽑아 모두 가지기 => ([가진카드, 나머지카드, 동전, 라운드]) q 추가
#     q = deque()
#     q.append([cards[:n // 3], cards[n // 3:], coin, 1])

#     # 2. remain에서 카드 두 장 뽑고, 코인 쓰는 경우의 수 따라 이번 라운드 통과 가능한지 판별
#     # 3. 가능하면 라운드+1해서 q에 추가, 불가능하면 라운드 최종 크기 비교 갱신
#     # 뽑으려 했는데 남은 카드가 0: 종료
#     while q:
#         got, remain, c, r = q.popleft()
#         if r > result_round:
#             result_round = r

#         if len(remain) == 0:
#             continue

#         # 2장 뽑기
#         new = remain[:2]
#         # remain에서 빼버리기
#         tremain = remain[2:]

#         # 버릴지말지 결정 후
#         for ci in range(min(c, 2) + 1):
#             for rn in combinations(new, ci):
#                 new_got = got[:]
#                 new_got.extend(list(rn))
#                 if len(new_got) >= 2:
#                     # 2개 뽑아서 n+1 가능한 조합에 대해 got에서 빼고 coin 계산해서 q에 추가하기
#                     for a, b in combinations(new_got, 2):
#                         if a + b == n + 1:
#                             next_got = new_got[:]
#                             next_got.remove(a)
#                             next_got.remove(b)
#                             q.append([next_got, tremain, c - ci, r + 1])

#     answer = result_round
#     return answer


def solution(coin, cards):
    n = len(cards)
    target = n + 1

    hand = set(cards[:n // 3])   # 처음 승패 (공짜)
    pending = set()              # 뽑았지만 아직 동전 안 낸 카드
    idx = n // 3
    round_ = 1

    while idx < n:               # 뽑을 카드가 없으면 종료
        pending.add(cards[idx])
        pending.add(cards[idx + 1])
        idx += 2

        found = False

        # 1) 손패끼리: 동전 0개
        for x in hand:
            if target - x in hand:
                hand.remove(x)
                hand.remove(target - x)
                found = True
                break

        # 2) 손패 + 보류: 동전 1개
        if not found and coin >= 1:
            for x in hand:
                if target - x in pending:
                    hand.remove(x)
                    pending.remove(target - x)
                    coin -= 1
                    found = True
                    break

        # 3) 보류끼리: 동전 2개
        if not found and coin >= 2:
            for x in pending:
                if target - x in pending:
                    pending.remove(x)
                    pending.remove(target - x)
                    coin -= 2
                    found = True
                    break

        if not found:            # 낼 쌍이 없으면 이 라운드에서 종료
            break
        round_ += 1

    return round_