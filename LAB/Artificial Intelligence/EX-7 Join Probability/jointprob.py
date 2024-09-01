

s = {'sunny': 0.3, 'cloudy': 0.3, 'rainy': 0.4}
w = {'true': 0.3, 'false': 0.7}

# Returning row values of events based on S event


def S_event(event):
    if 'sunny' in event:
        return 0
    elif 'cloudy' in event:
        return 1
    elif 'rainy' in event:
        return 2
    else:
        return 3

# Returning column values of events based on W event


def W_event(event):
    if 'W = T' in event:
        return 0
    elif 'W = F' in event:
        return 1
    else:
        return 2

# Finding probability based on the event


def P(jpdt, event):
    if '|' in event:
        event = event.split('|')
        row = S_event(event[0])
        col = W_event(event[0])

    else:
        row = S_event(event)
        col = W_event(event)

    return jpdt[row][col]


# Joint probability distribution table
jpdt = []

for i in s:
    probability = []
    for j in w:
        probability.append(round(s[i] * w[j], 2))
    jpdt.append(probability)
print(jpdt)

# Finding row sum
for i in range(len(jpdt)):
    rsum  = sum(jpdt[i])
    jpdt[i].append(rsum)
print('with row sum : ',jpdt)

# Finding column sum
csum = []
for i in range(len(jpdt[0])):
    col_sum = 0
    for j in range(len(jpdt)):
        col_sum += jpdt[j][i]
    csum.append(col_sum)
jpdt.append(csum)
print('with col sum : ',jpdt)

# Printing joint probability distribution table
print('\nJOINT PROBABILITY DISTRIBUTION TABLE\n')
print('S/W     \tW = T\t\tW = F\t\tSum\n')
print('S = Sunny ', end="\t")

for i in jpdt[0]:
    print(i, end="\t\t")
print()

print('\nS = Cloudy', end="\t")
for i in jpdt[1]:
    print(i, end="\t\t")
print()

print('\nS = Rainy ', end="\t")
for i in jpdt[2]:
    print(i, end="\t\t")
print()

print('\nSum     ', end="\t")
for i in jpdt[3]:
    print(i, end="\t\t\t")

print("\n\nPRINTING PROBABILITIES OF EVENTS\n")

print('P(S = rainy ∧ W = T) = ', P(jpdt, 'S = rainy ∧ W = T'))
print('P(S = rainy) = ', P(jpdt, 'S = rainy'))
print('P(W = T) = ', P(jpdt, 'W = T'))
print('P(S = rainy | W = T) = ', P(jpdt, 'S = rainy | W = T'))
print('P(W = T | S = rainy) = ', P(jpdt, 'W = T | S = rainy'))
