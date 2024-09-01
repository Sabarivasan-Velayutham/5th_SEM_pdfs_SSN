def And(a, b):
    n = len(a)
    return [a[i] and b[i] for i in range(n)]

def Or(a, b):
    n = len(a)
    return [a[i] or b[i] for i in range(n)]

def Not(a):
    l = []
    for x in a:
        if x:
            l.append(0)
        else:
            l.append(1)
    return l

def Implication(a, b):
    return Or(Not(a), b)

def BiConditional(a, b):
    return And(Implication(a, b), Implication(b, a))

def isTautology(a):
    return min(a) == 1

def are_equivalent(a, b):
    return a == b

a = [0, 0, 1, 1]
b = [0, 1, 0, 1]

print("\n(p⇒q) ∨ (q⇒p)")
print("Tautology :", isTautology(Or(Implication(a, b), Implication(a, b))))

print("\np⇒(p∨q)")
print("Tautology :", isTautology(Implication(a, Or(a, b))))

print("\n~p⇒p")
print("Tautology :", isTautology(Implication(Not(a), a)))

print("\n~p∧q⇒~(p∨q)")
print("Tautology :", isTautology(Implication(And(Not(a), b), Not(Or(a, b)))))

print("\n~a∨b, a->b")
print("Are Equivalent :", are_equivalent(Or(Not(a), b), Implication(a, b)))

print("\np∨~p, p∧~p")
print("Are Equivalent :", are_equivalent(Or(a, Not(a)), And(a, Not(a))))

print("\n(p->q) <=> (~pvq)")
print("Tautology: ",
      isTautology(BiConditional(Implication(a, b), Or(Not(a), b))))
list_biconditional = BiConditional(Implication(a, b), Or(Not(a), b))
list_implication = Implication(a, b)
list_or_of_notOfA_and_B = Or(Not(a), b)
list_notOfA = Not(a)
print(
    "\nTRUE TABLE\n-----------------------------------------------------------------"
)
print("|  p  |  q  | ~q  | (~p v q)  |  (p -> q)  | (p->q) <=> (~pvq)  |")
print("------------------------------------------------------------------")
for i in range(4):
    print("| ", a[i], " | ", b[i], " | ", list_notOfA[i], " |    ",
          list_or_of_notOfA_and_B[i], "   |     ", list_implication[i],
          "     |        ", list_biconditional[i], "         |")
    print("-----------------------------------------------------------------")