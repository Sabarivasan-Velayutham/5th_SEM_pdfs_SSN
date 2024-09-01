
def modus_ponens(p1, p2):
    # p->q, p
    # => q
    if '->' in p2 and '->' not in p1:
        p1, p2 = p2, p1

    p1 = p1.split('->')
    if p2 == p1[0]:
        return p1[1]


def modus_tollens(p1, p2):
    # p->q, ~q
    # => ~p
    if '->' in p2 and '->' not in p1:
        p1, p2 = p2, p1

    p1 = p1.split('->')
    p2 = p2.split('~')
    if p2[1] == p1[1]:
        return '~' + p1[0]

# print(modus_ponens("w", "w->s"))
# print(modus_tollens("~s", "w->s"))


def conjunction(p1, p2):
    return p1 + '^' + p2

# print(conjunction("s","r"))


def simplification(p):
    p = p.split('^')
    return p[0], p[1]

# print(simplification("s^r"))


def addition(s1, s2):
    return s1 + 'v' + s2

# print(addition("S","R"))


# main
print("Premises:-")
kb = ["~s^c", "w->s", "~w->t", "t->h"]
goal = "h"

for i in range(len(kb)):
    print(i+1, ".", kb[i])

print("\nGoal: ", goal)

print("\nProof using inference rules:-\n")
print("Step\t\tPremise\t\tInference rule")
print("1.\t\t\t", kb[0], "\t\tpremise")
kb.extend(simplification(kb[0]))
print("2.\t\t\t", kb[4], "\t\tsimplification of 1")
print("3.\t\t\t", kb[1], "\t\tpremise")
kb.append(modus_tollens(kb[4], kb[1]))
print("4.\t\t\t", kb[-1], "\t\tmodus tollens of 2,3")
print("5.\t\t\t", kb[2], "\t\tpremise")
kb.append(modus_ponens(kb[-1], kb[2]))
print("6.\t\t\t", kb[-1], "\t\t\tmodus ponens of 4,5")
print("7.\t\t\t", kb[3], "\t\tpremise")
kb.append(modus_ponens(kb[-1], kb[3]))
print("8.\t\t\t", kb[-1], "\t\t\tmodus ponens of 6,7")
print("goal found!")
# print(kb)


def resolution(p1, p2):
    if 'v' in p2 and 'v' not in p1:
        p1, p2 = p2, p1

    p1 = p1.split('v')
    if '~' not in p2:
        if '~' + p2 == p1[0]:
            return p1[1]
        elif '~' + p2 == p1[1]:
            return p1[0]
    else:
        p2 = p2.split('~')[1]
        if p2 == p1[1]:
            return p1[0]
        elif p2 == p1[0]:
            return p1[1]
# print(resolution('~rvw','~w'))


print("\nConverted to CNF")
kb = ["~s", "c", "~wvs", "wvt", "~tvh"]

for i in range(len(kb)):
    print(i+1, ".", kb[i])

print("\nGoal: ", goal)
print("\nProof using resolution:-")
print("\nStep\t\tPremise\t\tInference rule")
print("1.\t\t\t", kb[0], "\t\tpremise")
print("2.\t\t\t", kb[2], "\t\tpremise")
kb.append(resolution(kb[0], kb[2]))
print("3.\t\t\t", kb[-1], "\t\tresolution of 1,2")
print("4.\t\t\t", kb[3], "\t\tpremise")
kb.append(resolution(kb[-1], kb[3]))
print("5.\t\t\t", kb[-1], "\t\t\tresolution of 3,4")
print("6.\t\t\t", kb[4], "\t\tpremise")
kb.append(resolution(kb[-1], kb[4]))
print("7.\t\t\t", kb[-1], "\t\t\tresolution of 5,6")
print("goal found!")
