
from collections import defaultdict

def dls(graph, visited, root, limit, search):

    if limit == 0:
        return 0
    if root == search:
        print(root, " FOUND IT !")
        return 1

    else:
        if root not in visited:
            print(root, end=' ')
            visited.add(root)
            if root in graph.keys():
                for neighbour in graph[root]:
                    ans = dls(graph, visited, neighbour, limit-1, search)
                    if ans == 1:
                        return 1
            return 0
    return 0


def ids(graph, root, limit, search):
    for i in range(1, limit+1):
        print("LIMIT : ", i)
        if dls(graph, set(), root, i, search) == 1:
            break
        else:
            print("NOT FOUND :(")
        print()


# print("Enter values for the tree : ")
# values = list(map(int, input().split()))
# print("Enter limit : ")
# limit = int(input())
# print("Enter element to be searched : ")
# search = tuple(map(int, input().split()))

graph = defaultdict(list)
# graph = {0: [1, 2], 1: [3, 4], 2: [5, 6], 3: [7, 8], 4: [9, 10]}
graph = {0: [4, 5, 8],
         2: [1], 3: [1],
         4: [2, 3],
         5: [7, 10],
         6: [3, 100],
         7: [8, 9],
         8: [9],
         9: [10],
         10: [6]}
visited = set()

print("TREE : ")
print(graph)
print()

print("DLS : ")
ans = dls(graph, visited, 0, 9, 100)
if ans != 1:
    print("NOT FOUND :(")

print()

print("IDS : ")
ids(graph, 0, 5, 100)
