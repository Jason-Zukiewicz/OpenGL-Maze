To BUILD: make

To Run: cd build --> ./app 

To Clean: make clean

---------------------------------------------------

Project 3


1. NORMAL - DONE?
need array of normals - like that of verts 
every 3 verts gives a surface
Then the normal of those 3 will be the same
Take p0, p1, p2 
u = p1 - p0
v = p2 - p0
norm = normalize(cross(u,v))

Rememer Normal must be transformed with world so with ctm and model view

2. L - vector from fragment to light pos  (eyePoint)
L = vec4_VVS(eyePoint, vertexPos)
eyePoint must be translated with world
for model view eye point will be origin
(0,0,0) in vShader

p = model_view - ctm * vPosition
L = {0,0,0,1} - p

3. V viewer 
 will be at 0,0,0 after model transform
 