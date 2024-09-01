
import random

N = int(input())


def genBoard():
    return [random.randint(0, N-1) for i in range(N)]


def showBoard(board):
    for i in range(N):
        for j in range(N):
            if board[j] == i:
                print(1, end=' ')
            else:
                print(0, end=' ')
        print()


def attacks(board):
    x = 0
    for q in range(N):
        for c in range(N):
            if (board[q] == board[c] and q != c) or (abs(q-c) == abs(board[q]-board[c]) and q != c):
                x += 1
    return x


def hillClimb(board):
    for t in range(10):
        minh = 1e9
        nrc = []
        for c in range(N):
            orow = board[c]
            for nr in range(N):
                board[c] = nr
                h = attacks(board)
                if h < minh:
                    minh = h
                    nrc = [nr, c]
            board[c] = orow
        board[nrc[1]] = nrc[0]


board = genBoard()
print(board)
showBoard(board)
print(attacks(board))
hillClimb(board)
showBoard(board)
print(attacks(board))
