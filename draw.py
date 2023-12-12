import numpy as np
import matplotlib.pyplot as plt
import matplotlib
import matplotlib.lines as mlines
import math
import random

plt.figure().add_subplot(projection="3d")    
    
def rotate(P, angle):
    P = (P[0]*math.cos(math.radians(angle)) - P[1]*math.sin(math.radians(angle)), P[0]*math.sin(math.radians(angle)) + P[1]*math.cos(math.radians(angle)), P[2])
    return P
    
class Rectangle:
    def __init__(self, origin, size, angle = 0, mode="xy") -> None:
        self.origin = origin
        self.size = size
        self.angle = angle   
               
        dx = size[0]/2
        dy = size[1]/2
        dz = size[2]/2
    
        if mode == "xy":
            p0 = (origin[0] - dx, origin[1] - dy, origin[2])
            p1 = (origin[0] + dx, origin[1] - dy, origin[2])
            p2 = (origin[0] + dx, origin[1] + dy, origin[2])
            p3 = (origin[0] - dx, origin[1] + dy, origin[2])
        elif mode == "xz":
            p0 = (origin[0] - dx, origin[1], origin[2] - dz)
            p1 = (origin[0] + dx, origin[1], origin[2] - dz)
            p2 = (origin[0] + dx, origin[1], origin[2] + dz)
            p3 = (origin[0] - dx, origin[1], origin[2] + dz)
        elif mode == "yz":
            p0 = (origin[0], origin[1] - dy, origin[2] - dz)
            p1 = (origin[0], origin[1] - dy, origin[2] + dz)
            p2 = (origin[0], origin[1] + dy, origin[2] + dz)
            p3 = (origin[0], origin[1] + dy, origin[2] - dz)
    
        self.vertexes = [p0, p1, p2, p3]
        self.children = []
        
        if self.angle != 0:
            self.rotate(angle=self.angle)
        
        self.triangles = [0, 1, 2,     0, 2, 3]
        
        
    
    def rotate(self, center = None, angle = 0):
        
        if center is None:
            center = self.origin        
        p0, p1, p2, p3 = self.vertexes    
            
        ############## center
        p0 = (p0[0] - center[0], p0[1] - center[1], p0[2] )
        p1 = (p1[0] - center[0], p1[1] - center[1], p1[2] )
        p2 = (p2[0] - center[0], p2[1] - center[1], p2[2] )
        p3 = (p3[0] - center[0], p3[1] - center[1], p3[2] )   
        #####################
        
        p0 = rotate(p0, angle)
        p1 = rotate(p1, angle)
        p2 = rotate(p2, angle)
        p3 = rotate(p3, angle)
        
        ############## decenter  
        p0 = (p0[0] + center[0], p0[1] + center[1], p0[2] )
        p1 = (p1[0] + center[0], p1[1] + center[1], p1[2] )
        p2 = (p2[0] + center[0], p2[1] + center[1], p2[2] )
        p3 = (p3[0] + center[0], p3[1] + center[1], p3[2] )    
        #######################
        self.vertexes = [p0, p1, p2, p3]
        
        for c in self.children:
            c.rotate(center=center, angle=angle)
        
        return self
        
    def draw(self):
        for c in self.children:
            c.draw()          
            
        self._mesh()
        
    def _mesh(self):
        colors = []
        for k, v in matplotlib.colors.cnames.items():
            colors.append(v)
            
        for idx in range(0, len(self.triangles), 3):
            tmp_triangles = self.triangles[idx:idx+3]
            randint = random.randint(0, len(colors))
            plt.plot([self.vertexes[idx][0] for idx in tmp_triangles],
                     [self.vertexes[idx][1] for idx in tmp_triangles],
                     [self.vertexes[idx][2] for idx in tmp_triangles], 
                     marker='<', color="red")
        
        plt.plot([self.vertexes[0][0], self.vertexes[-1][0]], [self.vertexes[0][1], self.vertexes[-1][1]], [self.vertexes[0][2], self.vertexes[-1][2]], marker='<', color="red")     
    
    def attach(self, child):
        self.children.append(child)   
        
class Cuboid:
    def __init__(self, origin, size, angle = 0) -> None:
        self.origin = origin
        self.size = size
        self.angle = angle
        
        dx = size[0]
        dy = size[1]
        dz = size[2]
        
        self.children = []
        
        #top
        self.children.append(Rectangle(origin=(self.origin[0], self.origin[1], self.origin[2] + dz/2), size=(dx, dy, 0), mode="xy"))
        #bottom
        self.children.append(Rectangle(origin=(self.origin[0], self.origin[1], self.origin[2] - dz/2), size=(dx, dy, 0), mode="xy"))
        #front
        self.children.append(Rectangle(origin=(self.origin[0], self.origin[1] + dy/2, self.origin[2]), size=(dx, 0, dz), mode="xz"))
        #back
        self.children.append(Rectangle(origin=(self.origin[0], self.origin[1] - dy/2, self.origin[2]), size=(dx, 0, dz), mode="xz"))
        #right
        self.children.append(Rectangle(origin=(self.origin[0] + dx/2, self.origin[1], self.origin[2]), size=(0, dy, dz), mode="yz"))        
        #left
        self.children.append(Rectangle(origin=(self.origin[0] - dx/2, self.origin[1], self.origin[2]), size=(0, dy, dz), mode="yz"))
        
    def draw(self):
        for c in self.children:
            c.draw()
        
    

# r = Rectangle(origin=(0, 0, 0), size=(10, 10, 0), mode="xy")
# r.draw()
# plt.show()

c = Cuboid(origin=(0, 0, 0), size=(0.3, 10, 2))
c.draw()
plt.show()   



    




