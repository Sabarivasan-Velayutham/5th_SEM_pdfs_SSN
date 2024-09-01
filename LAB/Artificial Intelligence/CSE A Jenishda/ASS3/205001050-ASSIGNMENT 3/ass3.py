def next_state(a, b):
  nodes = []
  if (a != 0):
    nodes.append((0, b))
    if (a <= 3 - b):
      nodes.append((0, b + a))
    else:
      nodes.append((a - (3 - b), 3))
  if (b != 0):
    nodes.append((a, 0))
    if (b <= 4 - a):
      nodes.append((a + b, 0))
    else:
      nodes.append((4, 3 - (4 - a)))
  if (a != 4):
    nodes.append((4, b))
  if (b != 3):
    nodes.append((a, 3))
  return nodes

def bfs():
  global bfspath
  visited = set()
  que.append(((0, 0), 0))
  while len(que) > 0:
    current_state, level = que.pop(0)
    if current_state not in visited:
      bfspath=bfspath+1
      visited.add(current_state)
      print(current_state)
      if current_state in goal_states:
        print("Goal state reached")
        break
    nxt = next_state(*current_state)
    for x in nxt:
        que.append((x, level + 1))

          
def dfs():
  global dfspath
  visited = set()
  sta.append(((0, 0), 0))
  while len(sta) > 0:
    current_state, level = sta.pop(len(sta)-1)
    if current_state not in visited:
      dfspath=dfspath+1
      visited.add(current_state)
      print(current_state)
      nxt = next_state(*current_state)
      for x in nxt:
        sta.append((x, level + 1))
      if current_state in goal_states:
        print("Goal state reached")
        break

def dls(limit):
  global dlspath
  visited = set()
  sta=[]
  sta.append(((0, 0), 0))
  while len(sta) > 0:
    current_state, level = sta.pop(len(sta)-1)
    if current_state not in visited:
      dlspath=dlspath+1
      visited.add(current_state)
      print(current_state)
      if current_state in goal_states:
        print("Goal state reached")
        return 1
      if level != limit:
        nxt = next_state(*current_state)
        for x in nxt:
            sta.append((x, level + 1))


def ids():
    limit=0
    while(limit+1):
        flag=dls(limit)
        if(flag==1):
            break
        limit=limit+1
        print()

initial_state = (0, 0)
goal_states = [(2, 0), (2, 1), (2, 2), (2, 3)]
que = []
sta = []
bfspath=0
dfspath=0
dlspath=0
limit = 6
print("BFS")
bfs()
print()
print("BFS path cost: ",bfspath)
print()
print("DFS")
dfs()
print()
print("DFS path cost: ",dfspath)
print()
print("DLS")
a=dls(6)
print()
dlspathcost=dlspath
print()
dlspath=0
print("IDS")
ids()
print()
idspathcost=dlspath
arr=[("BFS",bfspath),("DFS",dfspath),("DLS",dlspathcost),("IDS",idspathcost)]
arr.sort(key=lambda x: x[1])
print(arr[0][0],"is the best solution as it has the shortest path cost of",arr[0][1])
