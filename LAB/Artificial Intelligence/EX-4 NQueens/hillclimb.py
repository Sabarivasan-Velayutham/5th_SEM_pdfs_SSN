import random


def attack(brd):
    mov = {}
    best = 999
    for i in range(8):
        for k in range(8):
            if k == brd[i]:
                continue
            h = 0
            for j in range(8):
                if i == j:
                    continue
                if k == brd[j] or abs(i-j) == abs(k-brd[j]):
                    h += 1
            if h < best:
                best = h
                mov.clear()
                mov[i] = k
    return mov


brd = [0]*8
for i in range(8):
    brd[i] = random.randint(0, 7)
for i in range(100):
    mov = attack(brd)
    y = list(mov.keys())[0]
    x = mov[y]
    brd[y] = x
board = []
for i in range(8):
    row = []
    for j in range(8):
        row.append(0)
    board.append(row)
for i in range(8):
    board[brd[i]][i] = 1
for i in range(8):
    for j in range(8):
        print(board[i][j], end=" ")
    print()
print(brd)
