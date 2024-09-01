

import sys
sys.stdin = open("input.txt", "r")


class Tree:
    def __init__(self, data, name):
        self.children = []
        self.data = data


root = Tree(0, 0)
stack = [root]
count = 1

n = int(input())
while n > 1:
    cur = stack.pop(0)
    no_of_childs = int(input())
    # print(no_of_childs)
    if(no_of_childs > 0):
        nodes = list(map(int, input().split()))
        for i in nodes:
            node = Tree(i, count)
            cur.children.append(node)
            n -= 1
            count += 1
            stack.append(node)
        print(nodes)
