

from collections import deque, defaultdict


def bfs(graph, visited, root):

    queue = deque([root])
    visited.add(root)

    while queue:
        vertex = queue.popleft()
        print(vertex, end=" ")
        if vertex in graph.keys():
            for neighbour in graph[vertex]:
                if neighbour not in visited:
                    visited.add(neighbour)
                    queue.append(neighbour)


def dfs(graph, visited, root):
    if root not in visited:
        print(root, end=' ')
        visited.add(root)
        if root in graph.keys():
            for neighbour in graph[root]:
                dfs(graph, visited, neighbour)


graph = defaultdict(list)
# graph = {0: [1, 2], 1: [3,4], 2: [5,6]}
graph = {0: [4, 5, 8],
         2: [1], 
         3: [1],
         4: [2,3,5],
         5: [7, 10],
         6: [3, 100],
         7: [8, 9],
         8: [9],
         9: [10],
         10: [6]}
visited1 = set()
visited2 = set()

print(graph)
print("BFS : ")
bfs(graph, visited1, 0)

print('\n')

print(graph)
print("DFS : ")
dfs(graph, visited2, 0)
