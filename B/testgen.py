from random import randint

with open('D.in', "w") as f:
    f.write("3500000\n")
    for i in range(3500000):
        f.write(str(randint(-10000000, 10000000)) + " " + str(randint(-10000000, 10000000)) + "\n")
