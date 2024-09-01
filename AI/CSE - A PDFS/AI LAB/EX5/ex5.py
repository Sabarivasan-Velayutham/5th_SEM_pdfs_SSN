from operator import indexOf
import random


def view(li, index):
    print()
    print(f"Solution number {index + 1}: ", end='')
    print(li)
    print()

    for i in range(8):
        x = li[i] - 1
        for j in range(8):
            if j == x:
                print('[Q]', end='')
            else:
                print('[ ]', end='')
        print()
    print()


def getHuristic(instance):
    huristic = []
    for i in range(len(instance)):
        j = i - 1
        huristic.append(0)
        while j >= 0:
            if instance[i] == instance[j] or (abs(instance[i] - instance[j])
                                              == abs(i - j)):
                huristic[i] += 1
            j -= 1
        j = i + 1
        while j < len(instance):
            if instance[i] == instance[j] or (abs(instance[i] - instance[j])
                                              == abs(i - j)):
                huristic[i] += 1
            j += 1
    return huristic


def getFitness(instance):
    clashes = 0
    for i in range(len(instance) - 1):
        for j in range(i + 1, len(instance)):
            if instance[i] == instance[j]:
                clashes += 1
    for i in range(len(instance) - 1):
        for j in range(i + 1, len(instance)):
            if abs(instance[j] - instance[i]) == abs(j - i):
                clashes += 1
    return 28 - clashes


def buildKid(instance1, instance2, crossOver):
    newInstance = []
    for i in range(crossOver):
        newInstance.append(instance1[random.randint(0, 7)])
    for i in range(crossOver, 8):
        newInstance.append(instance2[random.randint(0, 7)])
    return newInstance


def changeChilds(co):
    global father, mother, child1, child2, crossover
    crossover = co
    child1 = buildKid(father, mother, crossover)
    child2 = buildKid(mother, father, crossover)


def changeChromosome(li):
    global crossover, father, mother
    newchange = -1
    while newchange != 0:
        newchange = 0
        tmpli = li
        getHur = getHuristic(tmpli)
        index = getHur.index(max(getHur))
        maxFitness = getFitness(tmpli)
        for i in range(1, 9):
            tmpli[index] = i
            if getFitness(tmpli) > maxFitness:
                maxFitness = getFitness(tmpli)
                newchange = i
            tmpli = li
        if newchange == 0:
            for i in range(len(li) - 1):
                for j in range(i + 1, len(li)):
                    if li[i] == li[j]:
                        li[j] = random.randint(1, 8)
        else:
            li[index] = newchange


if __name__ == "__main__":
    numberOfSolutions = int(input("No of solutions: "))
    solutions = []
    crossover = 4
    while len(solutions) < numberOfSolutions:
        father = []
        mother = []
        for i in range(8):
            father.append(random.randint(1, 8))
            mother.append(random.randint(1, 8))
        fitnessFather = getFitness(father)
        fitnessMother = getFitness(mother)
        while fitnessFather != 28 and fitnessMother != 28:
            changeChilds(crossover)
            changeChromosome(child1)
            changeChromosome(child2)
            fitnessFather = getFitness(child1)
            fitnessMother = getFitness(child2)
            father = child1
            mother = child2
            #print(father)
            #print(mother)
        if getFitness(father) == 28:
            if father not in solutions:
                solutions.append(father)
        else:
            if mother not in solutions:
                solutions.append(mother)

    print("********************** Solutions **********************")
    print(f"The number of solutions you wanted: {numberOfSolutions}")

    for i in range(len(solutions)):
        view(solutions[i], i)
    print("*******************************************************")


# Making random chromosomes
def random_chromosome(size):
    return [random.randint(0, size - 1) for _ in range(size)]


# Calculating fitness
def fitness(chromosome, maxFitness):
    horizontal_collisions = (
        sum([chromosome.count(queen) - 1 for queen in chromosome]) / 2)
    diagonal_collisions = 0
    n = len(chromosome)
    left_diagonal = [0] * (2 * n - 1)
    right_diagonal = [0] * (2 * n - 1)
    for i in range(n):
        left_diagonal[i + chromosome[i] - 1] += 1
        right_diagonal[len(chromosome) - i + chromosome[i] - 2] += 1
    diagonal_collisions = 0
    for i in range(2 * n - 1):
        counter = 0
        if left_diagonal[i] > 1:
            counter += left_diagonal[i] - 1
        if right_diagonal[i] > 1:
            counter += right_diagonal[i] - 1
        diagonal_collisions += counter

    # 28-(2+3)=23
    return int(maxFitness - (horizontal_collisions + diagonal_collisions))


# Doing cross_over between two chromosomes
def crossover(x, y):
    n = len(x)
    child = [0] * n
    for i in range(n):
        c = random.randint(0, 1)
        if c < 0.5:
            child[i] = x[i]
        else:
            child[i] = y[i]
    return child


# Randomly changing the value of a random index of a chromosome
def mutate(x):
    n = len(x)
    c = random.randint(0, n - 1)
    m = random.randint(0, n - 1)
    x[c] = m
    return x


# Calculating probability
def probability(chromosome, maxFitness):
    return fitness(chromosome, maxFitness) / maxFitness


# Roulette-wheel selection
def random_pick(population, probabilities):
    populationWithProbabilty = zip(population, probabilities)
    total = sum(w for c, w in populationWithProbabilty)
    r = random.uniform(0, total)
    upto = 0
    for c, w in zip(population, probabilities):
        if upto + w >= r:
            return c
        upto += w
    assert False, "Shouldn't get here"


# Genetic algorithm
def genetic_queen(population, maxFitness):
    mutation_probability = 0.1
    new_population = []
    sorted_population = []
    probabilities = []
    for n in population:
        f = fitness(n, maxFitness)
        probabilities.append(f / maxFitness)
        sorted_population.append([f, n])

    sorted_population.sort(reverse=True)

    # Elitism
    new_population.append(sorted_population[0][1])  # the best gen
    new_population.append(sorted_population[-1][1])  # the worst gen

    for i in range(len(population) - 2):

        chromosome_1 = random_pick(population, probabilities)
        chromosome_2 = random_pick(population, probabilities)

        # Creating two new chromosomes from 2 chromosomes
        child = crossover(chromosome_1, chromosome_2)

        # Mutation
        if random.random() < mutation_probability:
            child = mutate(child)

        new_population.append(child)
        if fitness(child, maxFitness) == maxFitness:
            break
    return new_population


# prints given chromosome
def print_chromosome(chrom, maxFitness):
    print("Solutions = {},  Fitness = {}".format(str(chrom),
                                                 fitness(chrom, maxFitness)))


# prints given chromosome board
def print_board(chrom):
    board = []

    for x in range(nq):
        board.append(["x"] * nq)

    for i in range(nq):
        board[chrom[i]][i] = "Q"

    def print_board(board):
        for row in board:
            print(" ".join(row))

    print()
    print_board(board)


if __name__ == "__main__":
    POPULATION_SIZE = 500

    while True:
        # say N = 8
        nq = int(
            input("Please enter your desired number of queens (0 for exit): "))
        if nq == 0:
            break

        maxFitness = (nq * (nq - 1)) / 2  # 8*7/2 = 28
        population = [random_chromosome(nq) for _ in range(POPULATION_SIZE)]

        generation = 1
        while (not maxFitness
               in [fitness(chrom, maxFitness) for chrom in population]
               and generation < 200):
            population = genetic_queen(population, maxFitness)
            if generation % 10 == 0:
                print("=== Generation {} ===".format(generation))
                print("Maximum Fitness = {}".format(
                    max([fitness(n, maxFitness) for n in population])))
            generation += 1
        fitnessOfChromosomes = [
            fitness(chrom, maxFitness) for chrom in population
        ]
        bestChromosomes = population[indexOf(fitnessOfChromosomes,
                                             max(fitnessOfChromosomes))]

        if maxFitness in fitnessOfChromosomes:
            print("\nSolved in Generation {}!".format(generation - 1))
            print_chromosome(bestChromosomes, maxFitness)
            print_board(bestChromosomes)

        else:
            print(
                "\nUnfortunately, we could't find the answer until generation {}. The best answer that the algorithm found was:"
                .format(generation - 1))
            print_board(bestChromosomes)
