import matplotlib
import matplotlib.pyplot as plt
import random
import os

plt.figure().add_subplot(projection="3d")  

def _mesh():
    
    global triangles
    global vertexes
    
    colors = []
    for k, v in matplotlib.colors.cnames.items():
        colors.append(v)
        
    for idx in range(0, len(triangles), 3):
        tmp_triangles = triangles[idx:idx+3]
        randint = random.randint(0, len(colors))
        plt.plot([vertexes[idx][0] for idx in tmp_triangles],
                    [vertexes[idx][1] for idx in tmp_triangles],
                    [vertexes[idx][2] for idx in tmp_triangles], 
                    marker='<', color="green")
    
    #plt.plot([vertexes[0][0], vertexes[-1][0]], [vertexes[0][1], vertexes[-1][1]], [vertexes[0][2], vertexes[-1][2]], marker='<', color="red")     
        
        


for file in os.listdir("C:\\code\\MyGit\\TableAndChairsUE5\\builder_files"):
    with open(os.path.join("C:\\code\\MyGit\\TableAndChairsUE5\\builder_files", file), "r") as fd:
        lines = fd.readlines()
        
    vertexes = [(float(v_p.strip()[1:-1].split(",")[0]), float(v_p.strip()[1:-1].split(",")[1]), float(v_p.strip()[1:-1].split(",")[2])) for v_p in lines[0].split("::")[:-1]]
    triangles = [int(idx) for idx in lines[1].split(",")[:-1]]
    _mesh()
    
plt.show()   

# cmd = input("Flush the folder (n) ? : ")
# if cmd.startswith("n"):
#     print("Folder Kept!") 
# else:

for file in os.listdir("C:\\code\\MyGit\\TableAndChairsUE5\\builder_files"):
    os.remove(os.path.join("C:\\code\\MyGit\\TableAndChairsUE5\\builder_files", file))
print("Folder Flushed !")