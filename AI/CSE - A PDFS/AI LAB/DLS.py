from collections import defaultdict
def dls(graph, visited, root, limit, search):
    if limit == 0:
        return 0
    if root == search:
        print(root, "\nGOAL FOUND !")
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
graph = defaultdict(list)
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
print("DLS TRAVERSAL: ")
ans = dls(graph, visited, 0, 9, 100)
if ans != 1:
    print("\nGOAL NOT FOUND :(")