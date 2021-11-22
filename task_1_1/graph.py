import matplotlib.pyplot as plt
with open('results.txt') as fp:
    x = [float(numeric_string) for numeric_string in ((fp.readline()).strip()).split()]
    y = [float(numeric_string) for numeric_string in ((fp.readline()).strip()).split()]
    z = [float(numeric_string) for numeric_string in ((fp.readline()).strip()).split()]
fig = plt.figure()

ax = fig.add_subplot(projection='3d')

ax.plot(x,y,z)

plt.show()