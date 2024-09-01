from binarytree import build
def createTree(arr):
  btree = build(arr)
  return btree
color = input("Enter the color: ")
num=int(input("Enter the number of elements: "))
arr = []
if(color=="RED"):
  for i in range(num):
    arr.append(2*i+1)
elif(color=="GREEN"):
  for i in range(num):
    arr.append((i+1)*2)
btree = createTree(arr)
print(btree)
bfs = btree.levelorder
goal = int(input("Enter the goal state for BFS: "))
for i in bfs:
  if i.value != goal:
    print(i.value,end="->")
  else:
    print(i.value)
    break
dfs = btree.preorder
goal = int(input("Enter the goal state for DFS: "))
for i in dfs:
  if i.value != goal:
    print(i.value,end="->")
  else:
    print(i.value)
    break
