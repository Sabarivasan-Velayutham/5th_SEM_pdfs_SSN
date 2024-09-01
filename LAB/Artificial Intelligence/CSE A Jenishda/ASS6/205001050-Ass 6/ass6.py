from cmath import log
import math

def generateList(n):
    tot = 2**n - 1
    seq = []
    seq.append(1)
    counter = 0
    while (counter < tot):
        seq.append(2 * seq[counter] + 1)
        seq.append(2 * seq[counter] + 2)
        counter += 1
    return seq


def miniMax(currLev, nodeIndex, maxTurn, seq, totLev):
    if (currLev == totLev):
        return seq[nodeIndex]
    if (maxTurn):
        return max(miniMax(currLev + 1, nodeIndex * 2 + 1, False, seq, totLev),
                   miniMax(currLev + 1, nodeIndex * 2 + 2, False, seq, totLev))
    else:
        return min(miniMax(currLev + 1, nodeIndex * 2 + 1, True, seq, totLev),
                   miniMax(currLev + 1, nodeIndex * 2 + 2, True, seq, totLev))


n = int(input("ENTER VALUE OF LEVEL : "))
seq = generateList(n)
count = 0
print("STATE SPACE REPRESENTAION")
for level in range(n + 1):
    if level == 0:
        print("Level ", level, " ", [seq[0]])
        count += 1
    else:
        print("Level ", level, " ", seq[count:count + (2**(level))])
        count += 2**level
print("Assume first move is by the max player, the final score is ", end="")
print(miniMax(0, 0, True, seq, n))