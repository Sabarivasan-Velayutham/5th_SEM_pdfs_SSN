
# constructing a decision tree from a given dataset using ID3

from math import log2

table1 = {
    'Deadline': ['Urgent', 'Urgent', 'Near', 'None', 'None', 'None', 'Near', 'Near', 'Near', 'Urgent'],
    'Party': ['Yes', 'No', 'Yes', 'Yes', 'No', 'Yes', 'No', 'No', 'Yes', 'No'],
    'Lazy': ['Yes', 'Yes', 'Yes', 'No', 'Yes', 'No', 'No', 'Yes', 'Yes', 'No'],
    'Activity': ['Party', 'Study', 'Party', 'Party', 'Pub', 'Party', 'Study', 'TV', 'Party', 'Study']}

table2 = {'Fever': ['No', 'Yes', 'Yes', 'Yes', 'Yes', 'No', 'Yes', 'Yes', 'No', 'Yes', 'No', 'No', 'No', 'Yes'],
          'Cough': ['No', 'Yes', 'Yes', 'No', 'Yes', 'Yes', 'No', 'No', 'Yes', 'Yes', 'Yes', 'Yes', 'Yes', 'Yes'], 'Breathing Issues': ['No', 'Yes', 'No', 'Yes', 'Yes', 'No', 'Yes', 'Yes', 'Yes', 'No', 'No', 'Yes', 'Yes', 'No'],
          'Infected': ['No', 'Yes', 'No', 'Yes', 'Yes', 'No', 'Yes', 'Yes', 'Yes', 'Yes', 'No', 'Yes', 'No', 'No']}


def freq(list):
    frequency = {}
    for item in list:
        if (item in frequency):
            frequency[item] += 1
        else:
            frequency[item] = 1
    return frequency


def select(target, list):
    target_split = {}
    for index in range(len(list)):
        item = list[index]
        value = target[index]
        if (item in target_split):
            target_split[item].append(value)
        else:
            target_split[item] = [value]
    return target_split


def findProbs(list):
    frequency = freq(list)
    # print(frequency)
    total = len(list)
    probs = []
    for count in frequency.values():
        prob = round(count/total, 3)
        probs.append(prob)
    return probs


def entropyTarget(attr_values):
    probs = findProbs(attr_values)
    # print(probs)
    return round(sum([-prob*log2(prob) for prob in probs]), 3)


def entropy(target, attribute):
    attr_values = data[attribute]
    total = len(attr_values)
    # print(total)
    split = select(target, attr_values)
    split_count = freq(attr_values)
    # print(split)
    entr_attr = 0
    for (attr_value, classes) in split.items():
        count = split_count[attr_value]
        # print(count)
        entr = entropyTarget(classes)
        # print(entr)
        entr_attr += round(((count/total) * entr), 3)
        # print(entr_attr)
    return round(entr_attr, 3)


def ig(target, attribute):
    entropy_s = entropyTarget(target)
    entr_attr = entropy(target, attribute)
    info_gain = entropy_s - entr_attr
    return round(info_gain, 3)


print("\nRound 1: ")
data = table1

attributes = list(data.keys())[:-1]
target_attr = list(data.keys())[-1]
target = data[target_attr]

print("Attributes:", attributes)
print("Target:", target_attr)
# print(target)

entropy_s = entropyTarget(target)
print("\nEntropy(S) =", entropy_s)

ig_max, root = 0, None
for attribute in attributes:
    entr_attr = entropy(target, attribute)
    print("\nEntropy(S,", attribute, "\b) =", entr_attr)
    ig_attr = ig(target, attribute)
    print("IG(S,", attribute, "\b) =", ig_attr)
    if (ig_attr > ig_max):
        ig_max = ig_attr
        root = attribute

print("\nChosen attribute:", root)


table1 = {
    'Deadline': ['Urgent', 'None', 'Near', 'Near', 'Urgent'],
    'Party': ['No', 'No', 'No', 'No', 'No'],
    'Lazy': ['Yes', 'Yes', 'No', 'Yes', 'No'],
    'Activity': ['Study', 'Pub', 'Study', 'TV', 'Study']}


print("\n\nRound 2: ")
data = table1

attributes = list(data.keys())[:-1]
target_attr = list(data.keys())[-1]
target = data[target_attr]

print("Attributes:", attributes)
print("Target:", target_attr)
# print(target)

entropy_s = entropyTarget(target)
print("\nEntropy(S) =", entropy_s)

ig_max, root = 0, None
for attribute in attributes:
    entr_attr = entropy(target, attribute)
    print("\nEntropy(S,", attribute, "\b) =", entr_attr)
    ig_attr = ig(target, attribute)
    print("IG(S,", attribute, "\b) =", ig_attr)
    if (ig_attr > ig_max):
        ig_max = ig_attr
        root = attribute

print("\nChosen attribute:", root)


table1 = {
    'Deadline': ['Near', 'Near'],
    'Party': ['No', 'No'],
    'Lazy': ['No', 'Yes'],
    'Activity': ['Study', 'TV']}


print("\n\nRound 3: ")
data = table1

attributes = list(data.keys())[:-1]
target_attr = list(data.keys())[-1]
target = data[target_attr]

print("Attributes:", attributes)
print("Target:", target_attr)
# print(target)

entropy_s = entropyTarget(target)
print("\nEntropy(S) =", entropy_s)

ig_max, root = 0, None
for attribute in attributes:
    entr_attr = entropy(target, attribute)
    print("\nEntropy(S,", attribute, "\b) =", entr_attr)
    ig_attr = ig(target, attribute)
    print("IG(S,", attribute, "\b) =", ig_attr)
    if (ig_attr > ig_max):
        ig_max = ig_attr
        root = attribute

print("\nChosen attribute:", root)
