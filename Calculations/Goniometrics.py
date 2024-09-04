import matplotlib.pyplot as plt
import matplotlib.path as mpath
import math
import numpy as np
import matplotlib.patches as mpatches

fig, ax = plt.subplots()

D_w = 1.5
r_W = D_w/2
AB = np.array([0,2])
BC = np.array([.5, .25])

alfa = math.pi/3
beta = 0
O = np.array([0,0])

A = [0, r_W]

length_AB = np.linalg.norm(AB)
ABx = math.sin(alfa)*length_AB
ABy = math.cos(alfa)*length_AB

B = [ A[0] + ABx, A[1] + ABy ]

BCx = math.cos(alfa-beta)*BC[0] + math.sin(alfa-beta)*BC[1]
BCy = -math.sin(alfa-beta)*BC[0] + math.cos(alfa-beta)*BC[1]


C = B[0] + BCx , B[1] + BCy

Path = mpath.Path
path_data = [
    (Path.MOVETO, (0, 0)),
    (Path.LINETO, A),
    (Path.LINETO, B),
    (Path.LINETO, C),
    ]
codes, verts = zip(*path_data)
path = mpath.Path(verts, codes)
# plot control points and connecting lines
x, y = zip(*path.vertices)
line, = ax.plot(x, y, 'go-')
ax.grid()
ax.axis('equal')
plt.show()