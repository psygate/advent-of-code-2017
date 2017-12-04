#! /usr/bin/env python

def contains_dupes(l):
    for orig in range(0, len(l)):
        for dup in range(0, len(l)):
            if orig == dup: continue

            if l[orig] == l[dup]:
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
