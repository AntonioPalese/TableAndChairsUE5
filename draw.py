import numpy as np
import matplotlib.pyplot as plt
import matplotlib.lines as mlines
import math

plt.figure().add_subplot(projection="3d")    
    
def rotate(P, angle):
    P = (P[0]*math.cos(math.radians(angle)) - P[1]*math.sin(math.radians(angle)), P[0]*math.sin(math.radians(angle)) + P[1]*math.cos(math.radians(angle)), P[2])
    return P
    
class Rectangle():
    def __init__(self, origin, size, angle = 0) -> None:
        self.origin = origin
        self.size = size
        self.angle = angle
        
        dx = size[0]/2
        dy = size[1]/2
        dz = 0
    
        p0 = (origin[0] - dx, origin[1] - dy, origin[2] + dz)
        p1 = (origin[0] + dx, origin[1] - dy, origin[2] + dz)
        p2 = (origin[0] + dx, origin[1] + dy, origin[2] + dz)
        p3 = (origin[0] - dx, origin[1] + dy, origin[2] + dz)
    
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
        plt.plot([self.vertexes[idx][0] for idx in self.triangles], [self.vertexes[idx][1] for idx in self.triangles], [self.vertexes[idx][2] for idx in self.triangles], marker='<', color="red")
        plt.plot([self.vertexes[0][0], self.vertexes[-1][0]], [self.vertexes[0][1], self.vertexes[-1][1]], [self.vertexes[0][2], self.vertexes[-1][2]], marker='<', color="red")     
    
    def attach(self, child):
        self.children.append(child)      
        
        
        

r = Rectangle(origin=(0, 0, 2), size=(10, 10), angle=45)
r.draw()

plt.show()   
    

# draw_rectangle(origin=(0, 0, 2), r=(10, 10), angle=0)
# draw_rectangle(origin=(0, -4, 2), r=(4, 2), angle=90)


    




