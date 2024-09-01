

class Tree:
    def __init__(self, data, name):
        self.children = []
        self.data = data
        self.name = name


root = Tree(0, 0)
stack = [root]
n = int(input("Total Nodes:"))
c = 1

while n > 1:
    cur = stack.pop(0)
    N = int(input("Enter No of Children["+str(cur.name)+"]:"))
    if(N > 0):
        nodes = list(map(int, input("Enter the values:").split()))
        for i in nodes:
            node = Tree(i, c)
            cur.children.append(node)
            n -= 1
            c += 1
            stack.append(node)
print()


def DFS(root, tab=0):
    print("("+str(tab)+")"+"---"*tab+"<"+str(root.data)+">")
    for i in root.children:
        DFS(i, tab+1)
    if root.children == []:
        return


DFS(root)
print()


def minimax(root):
    print("Minimax:")
    main = root

    def helper(root, t=1):
        if root.children == []:
            return root.data
        if root.data == 0:
            if t == 1:
                root.data = -999
            else:
                root.data = 999
        for i in root.children:
            if t == 1:
                root.data = max(root.data, helper(i, 0))
            else:
                root.data = min(root.data, helper(i, 1))
        DFS(main)
        print()
        return root.data

    helper(root)
    print()
    return root.data


def alphabeta(root):
    print("Alpha-Beta Pruning:")
    main = root

    def helper(root, a=-9999, b=9999, t=1):
        if root.children == []:
            return root.data
        if root.data == 0:
            if t == 1:
                root.data = -999
            else:
                root.data = 999
        for i in root.children:
            if t == 1:
                root.data = max(root.data, helper(i, a, b, 0))
                a = max(a, root.data)
            else:
                root.data = min(root.data, helper(i, a, b, 1))
                b = min(b, root.data)
            if b <= a:
                break
        DFS(main)
        print()
        return root.data
    helper(root)
    print()
    return root.data


choice = int(input("1)Minimax 2)Alpha Beta\n"))
if choice == 1:
    v = minimax(root)
else:
    v = alphabeta(root)

print("Value:", v)
