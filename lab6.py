import numpy as np
import matplotlib.pyplot as plt


x, y = np.mgrid[-1:3:100j, -5:5:100j]

fig, axes = plt.subplots()

#  Задаем значение каждого уровня:
#lev = [1, 2, 3, 4, 6, 10, 20, 40, 100, 900]
#lev = 40
z = x ** 3 - 3 * x ** 2 + y ** 2 + 4 * y + 9
#  Контуры одного цвета:
axes.contour(x, y, z, #levels = lev,
           colors = 'r')
data = np.loadtxt("vec_p3.txt")
axes.plot(data[:,0],data[:,1])


fig.set_figwidth(8)    #  ширина и
fig.set_figheight(8)    #  высота "Figure"
plt.savefig("g.png")
plt.show()


