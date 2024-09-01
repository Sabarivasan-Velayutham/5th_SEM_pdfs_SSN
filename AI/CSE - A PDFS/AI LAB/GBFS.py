from queue import PriorityQueue
g={}
node={}
pos={}
dx = [1, -1, 0, 0]
dy = [0, 0, 1, -1]
f = {}
visited = set()
def create_graph():
  g['A'].append(('B', 9))
  g['B'].append(('A', 9))
  g['A'].append(('C', 6))
  g['C'].append(('A', 6))
  g['B'].append(('D', 5))
  g['D'].append(('B', 5))
  g['C'].append(('D', 8))
  g['D'].append(('C', 8))
  g['D'].append(('E', 7))
  g['E'].append(('D', 7))
  g['C'].append(('F', 5))
  g['F'].append(('C', 5))
  g['D'].append(('G', 6))
  g['G'].append(('D', 6))
  g['H'].append(('E', 4))
  g['E'].append(('H', 4))
  g['G'].append(('F', 7))
  g['F'].append(('G', 7))
  g['H'].append(('G', 8))
  g['G'].append(('H', 8))
def manhattan_dst(x1, y1, x2, y2):
  return abs(x1 - x2) + abs(y1 - y2)
def greedy_best_fs(x, y):
  global f, visited
  visited = set()
  t = node[(x, y)]
  f[t] = manhattan_dst(x, y, 3, 3)
  q = PriorityQueue()
  q.put((f[t], t))
  while q.qsize() > 0:
    (c1, t1) = q.get()
    if t1 in visited:
      continue
    visited.add(t1)
    print((c1, t1))
    if t1 == 'H':
      break
    for (t, c1) in g[t1]:
      (x1, y1) = pos[t]
      f[t] = manhattan_dst(x1, y1, 3, 3)    
      q.put((f[t], t))

c = 'A'
for i in range(1, 4):
  for j in range(1, 4):
    if i == 1 and j == 3:
      continue
    node[(i, j)] = c
    pos[c] = (i, j)
    g[c] = []
    c = chr(ord(c) + 1)
    
create_graph()
print("greedy best first search")
greedy_best_fs(1,1)