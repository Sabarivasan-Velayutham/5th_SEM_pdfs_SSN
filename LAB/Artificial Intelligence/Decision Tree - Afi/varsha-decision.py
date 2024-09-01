
from math import log2
a = [x for x in range(10)]
deadline = ["Urgent", "Urgent", "Near", "None",
            "None", "None", "Near", "Near", "Near", "Urgent"]
isthereparty = [1, 0, 1, 1, 0, 1, 0, 0, 1, 0]
lazy = [1, 1, 1, 0, 1, 0, 0, 1, 1, 0]
activity = ["Party", "Study", "Party", "Party",
            "Pub", "Party", "Study", "TV", "Party", "Study"]


def entropy(a):
    val1 = 0
    val2 = 0
    val3 = 0
    val4 = 0
    total = sum(a)
    if a[0]:
        val1 = -a[0]/total*log2(a[0]/total)
    if a[1]:
        val2 = -a[1]/total*log2(a[1]/total)
    if a[2]:
        val3 = -a[2]/total*log2(a[2]/total)
    if a[3]:
        val4 = -a[3]/total*log2(a[3]/total)
    return val1 + val2 + val3 + val4


def find_activity(x):
    if x == "Party":
        return 0
    if x == "Study":
        return 1
    if x == "Pub":
        return 2
    if x == "TV":
        return 3


def cal_count(a):
    cnt = [0, 0, 0, 0]
    for x in a:
        cnt[find_activity(activity[x])] += 1
    return cnt


def information_gain(a, attribute):
    cnt = cal_count(a)
    div = {}
    # print(cnt)
    for x in a:
        k = attribute[x]
        if k not in div:
            div[k] = [0, 0, 0, 0]
        div[k][find_activity(activity[x])] += 1
    ans = entropy(cnt)
    # print(ans)
    for x, y in div.items():
        curr = entropy(y) * sum(y) / len(a)
        # print(curr)
        ans -= curr
    # print(ans)
        # print(x, y)
    return ans


def decision_tree():
    # taken=[]
    max1 = 0
    val = ""

    v = information_gain(a, deadline)
    print("Information gain Deadline", v)
    if v > max1:
        max1 = v
        val = "deadline"
    v = information_gain(a, isthereparty)
    print("Information gain isthereparty", v)
    if v > max1:
        max1 = v
        val = "isthereparty"

    v = information_gain(a, lazy)
    print("Information gain Lazy", v)
    if v > max1:
        max1 = v
        val = "lazy"

    a1 = []
    for x in a:
        if isthereparty[x] == 0:
            a1.append(x)

    # print(a1)
    print(val)
    print()
    v = information_gain(a1, deadline)
    print("Information gain Deadline", v)
    max1 = 0
    if v > max1:
        max1 = v
        val = "deadline"
    v = information_gain(a1, lazy)
    print("Information gain Lazy", v)
    if v > max1:
        max1 = v
        val = "lazy"
    print(val)
    print()
    a2 = []
    for x in a1:
        if deadline[x] == "Near":
            a2.append(x)

    max1 = 0
    v = information_gain(a2, lazy)
    print("Information gain Lazy", v)
    if v > max1:
        max1 = v
        val = "lazy"
    print(val)


decision_tree()
