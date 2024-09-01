
# run graph inputs which start with source node represented
# as 1 always

import sys

# for image1 and djikstra
# sys.stdin = open("input-image1.txt","r")

# for image 2 and a star search
sys.stdin = open("input-image2.txt", "r")


def minDistance(dist, sptSet, V):
    min = 1000
    for v in range(V):
        if dist[v] < min and sptSet[v] == False:
            min = dist[v]
            min_index = v
    return min_index


def minFind(dist, sptSet, V, heuristic):
    min = 1000
    for v in range(V):
        if dist[v] + heuristic[v] < min and sptSet[v] == False:
            min = dist[v]+heuristic[v]
            min_index = v
    return min_index


def printPath(parent, j):
    if parent[j] == -1:
        print(j, end=' ')
        return
    printPath(parent, parent[j])
    print(j, end=' ')


def printSolution(dist, parent, src):
    print("Source \t\tDistance \tPath")
    for i in range(len(dist)):
        if i != src:
            print("\n%d --> %d \t\t%d \t\t" % (src, i, dist[i]), end=" ")
            printPath(parent, i)
    print("\n")
    # dist[dist.index(0)]=9999
    # print("The path to choose : ")
    # printPath(parent,dist.index(min(dist)))


def dijkstra(graph, src, V):
    dist = [1e7] * V
    dist[src] = 0
    sptSet = [False] * V
    parent = [-1]*V

    for cout in range(V):
        u = minDistance(dist, sptSet, V)
        sptSet[u] = True

        for v in range(V):
            if (graph[u][v] > 0 and sptSet[v] == False and dist[v] > dist[u] + graph[u][v]):
                dist[v] = dist[u] + graph[u][v]
                parent[v] = u

    printSolution(dist, parent, src)


def astar(graph, src, V):
    # heuristic = {0:0, 1:10 ,2:16 ,3:9 ,4:9 ,5:0}
    # source and destination heuristic value = 0
    heuristic = {0: 10,
                 1: 8,
                 2: 5,
                 3: 7,
                 4: 3,
                 5: 6,
                 6: 5,
                 7: 3,
                 8: 1,
                 9: 0}
    dist = [1e7] * V
    dist[src] = 0
    sptSet = [False] * V
    parent = [-1]*V

    for cout in range(V):
        u = minFind(dist, sptSet, V, heuristic)
        sptSet[u] = True

        for v in range(V):
            if (graph[u][v] > 0 and sptSet[v] == False and dist[v] > dist[u] + graph[u][v]):
                dist[v] = dist[u] + graph[u][v]
                parent[v] = u

    printSolution(dist, parent, src)


n = int(input())
graph = [[0]*n for i in range(n)]

for _ in range(int(input())):
    a, b, c = map(int, input().split())

    # comment 2nd line incase of directed graphs
    # otherwise use 2 lines incase of undirected graphs

    graph[a][b] = c
    graph[b][a] = c

print(graph)
print()

print("Using Djkstra search : ")
dijkstra(graph, 0, n)
print()
print("Using A * search : ")
astar(graph, 0, n)
