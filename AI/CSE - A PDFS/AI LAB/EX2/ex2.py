from binarytree import build
import random
import math

def dls(prlevel, v):
    global goal
    global level
    global seq
    global flag
    global found
    if (level < prlevel or v >= len(seq) or flag == 1):
        return
    print(seq[v], end=" ")
    if (goal == seq[v]):
        flag = 1
        found = 1
        return
    dls(prlevel + 1, 2 * v + 1)
    dls(prlevel + 1, 2 * v + 2)

a, b = input("Enter range: ").split()
a = int(a)
b = int(b)
n = int(input("Enter n: "))
seq = random.sample(range(a, b), n)
print(seq)
tree = build(seq)
flag = 0
print(tree)

level = int(input("Enter level(limit): "))
goal = int(input("Enter goal state: "))
print("\nDLS Traversal:")
dls(0, 0)

print("\n")
print("IDS Traversal:")
levels = math.ceil(math.log(n + 1, 2))

found = 0
for i in range(levels):
    flag = 0
    print("Level", i, ":", end=" ")
    level = i
    dls(0, 0)
    print()
    if (found == 1):
        print("Goal found !")
        break
    else:
        print("Goal not found at level", i)
    print()