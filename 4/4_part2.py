#! /usr/bin/env python

def is_anagram(a,b):
    aletters = list(a)
    bletters = list(b)

    if len(aletters) != len(bletters):
        return False

    for i in range(0, len(aletters)):
        letter = aletters[i]
        if not letter in bletters:
            return False
        else:
            bletters.remove(letter)

    return len(bletters) == 0

def contains_dupes(l):
    for orig in range(0, len(l)):
        for dup in range(0, len(l)):
            if orig == dup: continue

            if l[orig] == l[dup] or is_anagram(l[orig], l[dup]):
                return True

    return False

def contains_no_dupes(l):
    return not contains_dupes(l)

def main():
    with open("input.txt") as f:
        passphrases = f.readlines()
    
    phrases_split = map(lambda x: x.strip().split(), passphrases)

    phrases_valid = filter(contains_no_dupes, phrases_split)

    print(len(phrases_valid))

if __name__ == '__main__':
    main()
