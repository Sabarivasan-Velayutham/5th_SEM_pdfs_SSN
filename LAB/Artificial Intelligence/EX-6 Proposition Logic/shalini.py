
def modus_ponens(premise1, premise2):
    # p->q, p => q
    if '->' in premise1:
        premise1 = premise1.split('->')
        if premise2 == premise1[0]:
            return premise1[1]

    # p, p->q => q
    elif '->' in premise2:
        premise2 = premise2.split('->')
        if premise1 == premise2[0]:
            return premise2[1]


def negation(premise):
    if premise[0] == '7':
        return premise[1]
    else:
        return '7' + premise[0]


def modus_tollens(premise1, premise2):
    # p->q, 7q => 7p
    if '->' in premise1 and '7' in premise2:
        premise1 = premise1.split('->')
        premise2 = premise2.split('7')
        if premise2[1] == premise1[1]:
            return negation(premise1[0])

    # 7q, p->q => 7p
    elif '7' in premise1 and '->' in premise2:
        premise2 = premise2.split('->')
        premise1 = premise1.split('7')
        if premise1[1] == premise2[1]:
            return negation(premise2[0])


def hypothetical_syllogism(premise1, premise2):
    if '->' in premise1 and '->' in premise2:
        premise1 = premise1.split('->')
        premise2 = premise2.split('->')
        if premise1[1] == premise2[0]:  # p->q, q->r => p->r
            return premise1[0] + '->' + premise2[1]
        elif premise2[1] == premise1[0]:  # q->r, p->q => p->r
            return premise2[0] + '->' + premise1[1]


def simplification(premise):
    # p^q => p, q
    return premise.split('^')


def equivalence(premise):
    # p<->q <=> p->q ^ q->p
    if '<->' in premise:
        premise = premise.split('<->')
        return premise[0] + '->' + premise[1] + '^' + premise[1] + '->' + premise[0]


def complementation(premise1, premise2):
    # p v 7p => F
    if ('7' in premise1 and premise1[1] == premise2) or ('7' in premise2 and premise2[1] == premise1):
        return 'F'


def inference(premises, goal):
    print("\nPROOF\nSTEP\t\tPREMISE\t\tINFERENCE RULE")

    print('1.\t\t\t' + '7' + goal + '\t\t\tPremise')
    print('2.\t\t\t' + premises[3] + '\t\tPremise')

    res = modus_tollens('7' + goal, premises[3])
    print('3.\t\t\t' + res + '\t\t\tModus Tollens from steps 1, 2')

    print('4.\t\t\t' + premises[2] + '\t\tPremise')
    res = modus_tollens(res, premises[2])
    print('5.\t\t\t' + res + '\t\t\tModus Tollens from steps 4, 5')

    print('6.\t\t\t' + premises[1] + '\t\tPremise')
    premises.extend(simplification(equivalence(premises[1])))
    print('7.\t\t\t' +
          premises[4] + '\t\tEquivalence to implication and simplification from step 6')

    res = modus_ponens(res, premises[4])
    print('8.\t\t\t' + res + '\t\t\tModus Ponens from steps 5, 7')

    print('9.\t\t\t' + premises[0] + '\t\tPremise')
    premises.extend(simplification(premises[0]))

    print('10.\t\t\t' + premises[6] + '\t\t\tSimplification from step 9')

    res = complementation(res, premises[6])
    print('11.\t\t\t' + res + '\t\t\tComplementation from step 8, 10')

    premises.remove(premises[1])
    premises.remove(premises[0])


def implication_conversion(premises):
    for i in range(len(premises)):
        if '->' in premises[i]:
            premises[i] = premises[i].split('->')
            premises[i][0] = negation(premises[i][0])
            premises[i] = premises[i][0] + ' v ' + premises[i][1]

# def resolve_pivot(premise1, premise2):
#  if premise1 == '' and premise2 == '':
#    return 'F'
#  elif premise1 == '':
#    return premise2
#  elif premise2 == '':
#    return premise1
#  return premise1 + ' v ' + premise2


def resolution(premise1, premise2):
    premise1 = premise1.split(' v ')
    premise2 = premise2.split(' v ')

    # p v 7q, q v r => p v r
    if len(premise1) > 1 and len(premise2) > 1:
        if complementation(premise1[0], premise2[0]) == 'F':
            return premise1[1] + ' v ' + premise2[1]
        elif complementation(premise1[0], premise2[1]) == 'F':
            return premise1[1] + ' v ' + premise2[0]
        elif complementation(premise1[1], premise2[0]) == 'F':
            return premise1[0] + ' v ' + premise2[1]
        elif complementation(premise1[1], premise2[1]) == 'F':
            return premise1[0] + ' v ' + premise2[0]

    elif len(premise2) > 1:
        # 7p, p v q => q
        if complementation(premise1[0], premise2[0]) == 'F':
            return premise2[1]
        # 7q, p v q => p
        elif complementation(premise1[0], premise2[1]) == 'F':
            return premise2[0]

    elif len(premise1) > 1:
        # p v q, 7p => q
        if complementation(premise2[0], premise1[0]) == 'F':
            return premise1[1]
        # p v q, 7q => p
        elif complementation(premise2[0], premise1[1]) == 'F':
            return premise1[0]

    # p v 7p => F
    elif complementation(premise1[0], premise2[0]) == 'F':
        return 'F'


def resolution_proof(premises, goal):
    print("\nPROOF\nSTEP\t\tPREMISE\t\tRESOLUTION STEPS")
    print("1.\t\t\t" + '7' + goal + "\t\t\tPremise")
    print("2.\t\t\t" + premises[1] + "\t\tPremise")
    res = resolution('7' + goal, premises[1])
    print("3.\t\t\t" + res + "\t\t\tResolution from steps 1, 2")
    print("4.\t\t\t" + premises[0] + "\t\tPremise")
    res = resolution(res, premises[0])
    print("5.\t\t\t" + res + "\t\t\tResolution from steps 3, 4")
    print("6.\t\t\t" + premises[2] + "\t\tPremise")
    res = resolution(res, premises[2])
    print("7.\t\t\t" + res + "\t\t\tResolution from steps 5, 6")
    print("8.\t\t\t" + premises[4] + "\t\t\tPremise")
    res = resolution(res, premises[4])
    print("9.\t\t\t" + res + "\t\t\tResolution from steps 7, 8")


# Proof
premises = ['7s^c', 'w<->s', '7w->t', 't->h']
print("PREMISES")
for i in range(len(premises)):
    print(str(i + 1) + '. ' + premises[i])

goal = 'h'
print("\nGOAL: " + goal)
inference(premises, goal)

implication_conversion(premises)

print("\nPREMISES IN CNF")
for i in range(len(premises)):
    print(str(i + 1) + '. ' + premises[i])

print("\nGOAL: " + goal)
resolution_proof(premises, goal)
