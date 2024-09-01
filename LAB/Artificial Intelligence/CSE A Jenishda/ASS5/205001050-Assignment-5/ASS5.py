import random


def fitnessFunction(state):
    fitness = 0
    for i in range(0, 7 + 1):
        for j in range(i + 1, 7 + 1):
            if (state[i] != state[j] and j - i != abs(state[i] - state[j])):
                fitness += 1
    return fitness


K = 10

states = []


def generateSeedStates():
    for i in range(K):
        state = [random.randint(0, 7) for _ in range(8)]
        states.append([fitnessFunction(state), 0, state])


def createChildren(parent1, parent2):
    state1 = parent1[2]
    state2 = parent2[2]
    parent1[1] -= 1
    parent2[1] -= 1

    #crossover
    child1 = [
        state1[0], state1[1], state1[2], state1[3], state2[4], state2[5],
        state2[6], state2[7]
    ]
    child2 = [
        state2[0], state2[1], state2[2], state2[3], state1[4], state1[5],
        state1[6], state1[7]
    ]

    #mutation
    pos = random.randint(0, 7)
    val = random.randint(0, 7)
    child1[pos] = val

    pos = random.randint(0, 7)
    val = random.randint(0, 7)
    child2[pos] = val

    return [fitnessFunction(child1), 0,
            child1], [fitnessFunction(child2), 0, child2]


def geneticAlgorithm():
    generateSeedStates()
    states.sort(reverse=True)
    iterations = 0
    while (states[0][0] < 28):
        print("Iteration : ", iterations)
        iterations += 1

        for i in range(0, min(100, len(states) - 1), 2):
            parent1 = states[i]
            parent2 = states[i + 1]

            children = createChildren(parent1, parent2)

            states.append(children[0])
            states.append(children[1])

        states.sort(reverse=True)

    print("Solution : ", states[0][2])


geneticAlgorithm()
