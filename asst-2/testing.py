import numpy as np

a = []
k=(float)(raw_input())
with open("custom", "w") as f:
    # n = np.random.randint(SIZE_MIN, SIZE_MAX+1)
    n = (int)(k*500000)
    f.write(str(n))
    f.write("\n")

    for _ in range(n):
        a.append(np.random.randint(-6000, 100000))
    
    s = list(map(str, a))
    f.write(" ".join(s))

    a = np.array(a)
    mean = round(np.mean(a), 3)
    std = round(np.std(a, ddof=1), 3)
    median = round(np.median(a), 3)
    print(n)
    with open("ans", "w") as p:
        p.write("The average value is {}\n".format(mean))
        p.write("The standard deviation value is {}\n".format(std))
        p.write("The median value is {}\n".format(median))