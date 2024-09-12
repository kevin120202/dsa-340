def mm_score(k, g, b, w):
    if len(k) != len(g):
        return 0

    for i in range(len(g)):
        for j in range(len(k)):
            if g[i] == k[j] and i == j:
                b += 1
            elif g[i] == k[j]:
                w += 1
            else:
                continue

    return 1 if b > 0 or w > 0 else 0


def main():
    k = "abc"
    g = "axx"
    b = 0
    w = 0

    print(mm_score(k, g, b, w))
    print(b, w)


main()
