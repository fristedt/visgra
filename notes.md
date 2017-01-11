# Slide 2
Standard transformations
Rita av tabell på slide 2 s. 50 och kryssprodukt, men glöm inte dot product

# Slide 3
Continuous real objects are represented by a finite set of locations, or samples, in space/time.
This is called a discrete structure.

Grid terminology: point (0d), line (1d), face, voxel

## Data connectivity

Structured grid: connectivity is implicitly given
	- Block-structured grid: combination of several structured grids
Refers to the implicitly given connectivity between the grid vertices

Unstructured grid: connectivity is explicitly given

Hybrid grid: combination of different grid types

## Regular or uniform grids
Cells are rectangles or rectangular cuboids of the same size

All grid lines are parallel to the axes

To define a uniform grid, we need the following:
Bounding box: ( x min , y min , z min) - ( x max , y max , z max)
Number of grid vertices in each dimension: 
	D x , D y , D z 
	Cell size: d x , d y , d z 

Cartesian grid

Special case of a uniform grid: dx = dy = dz
Consists of squares (2D), cubes (3D)

## Linear interpolation

f(x) = ((x1 - x) / (x1 - x0)) f(x0) + ((x - x0) / (x1 - x0)) f(x1)

## Bilinear interpolation

f(x, y) = (1 - x)(1 - y)f_{00} + x(1 - y)f_{10} + (1 - x)yf_{01} + xyf_{11}

### Continuities
Does a particle moving on this curve have a smooth 
trajectory?


Geometric Continuity
G0: curves are joined
G1: first derivatives are proportional at the join point
The curve tangents thus have the same direction, but not necessarily the same magnitude. i.e., C1'(1) = (a,b,c) and C2'(0) = (k*a, k*b, k*c).
G2: first and second derivatives are proportional at join point
Parametric Continuity
C0: curves are joined
C1: first derivatives equal
C2: first and second derivatives are equal
If t is taken to be time, this implies that the acceleration is continuous.
Cn: nth derivatives are equal


(Add proof JUST IN CASE) on page sid 31 (slide 5)

C - requires that the vectors to and from the intersection point are equal
G - same as C, but does not require the above

## Function Derivative Estimation (gradients)

\/f(x, y, z) = [d/dx, d/dy, d/dz]
f(x, y, z) = [df/dx, df/dy, df/dz]
Describes direction of steepest ascent

## Linear Interpolation in a Triangle

A linear function f(x, y) = a + bx + cy
Polynomial can be obtained by solving the linear system
	[1 x0 y0 [a   [f0
	 1 x1 y1  b =  f1
	 1 x2 y2] c]   f2]
- Linear in x and y

## Barycentric coordinates

p = ap1 + bp2 + cp3 with a + b + c = 1
Rita av bild på sida 60

### Barycentric interpolation in a triangle

f(x, y) = a0(x, y)f0 + a1(x, y)f1 + a2(x, y)f2
with a0 + a1 + a2 = 1 (barycentric coordinates)
f0, f1, f2 are the corner vertices of the triangle

Can also solve for unknown coefficients a (cramers rule):
	[x0 x1 x2 [a0   [x
	 y0 y1 y2  a1 =  y
	 1  1  1]  a2]   1]

Gradient of a linearly interpolated function in a 
triangle/tetrahedron: Constant!

# Slide 4

## Geometric modeling

Geometry describes the form and the position/orientation in a 
coordinate system.

Topology defines the fundamental structure that is invariant against 
continuous transformations.

## Skriv upp casteljau om du vill (hampus kan redan den)

# Slide 5

## Spline surfaces
We use splines because it maintain C2-cont.
Model surfaces using bezier curves
Two approaches: tensor product surfaces and total degree surfaces


### Tensor product surfaces
For C0 cont: boundary points is equal
Quadratic bezier
Repeated bilinear interpolation

### Bezier patches 
Remember endpoint interpolation

### Total degree surfaces
For C0 cont: boundary points is equal
For C1 cont: above + points at hatched quadrilaterals are coplanar 
Bezier triangles
Barycentric interpolation 

## Quad patch problem
Hard to parameterize general shapes over quad/triang regions. 
Solved by tesselation (approximation of surface) 

## NURBS
If functions are B-splines => NURBS surface.

# Slide 5.5 
	
## Subdivison surfaces
Redefines a mesh by splitting the current mesh by some SCALE. Then interpolate to smooth the surface.
Algorithm:
Step 1. Subdivide current mesh
Step 2. Splitting (insert interpolated points)
Step 3. Move points (averaging)

Averaging has problems. Where should we PUT NEW POINTS????
Use corner cutting. Chaikin CC converges to quadratic B-spline curve
Algo: Q_i = 3/4 P_i + 1/4 P_i+1
	  R_i = 1/4 P_i + 3/4 P_i+1


## cubic b-spline subdivision scheme
Problem might be that we get to many new control points. Use spectral limit
trick.  Only allow control points that control a point on the curve.  The
dominant eigenvalue / eigenvector of the subdivision scheme determines the
limit mask. Convergence condition: abs(eigenvalue)<= 1.

Catmull-Clark (used to smooth surface) is a generalization of CURBS, resulting
in a new mesh with only quadrilaterals.

# Slide 6 (Coloring)

# Slide 7 (Visibility & Shading)

## Rasterization

- Project all triangles to the screen

- More efficient than raytracing

- Implement using Painter (old and slow due to overwrite) or Z-Buffering

## Clipping

Clipping is the process of truncating triangles to fit them inside the viewing
area.

## Z-Buffering

1. Store depth value for each pixel.

2. Rasterize object closest to the camera (lowest z)

# Slide 7.1 (Shading Models)

## Local Shading Model

- Single point of light source.

## Shading Effects

- Diffuse Light: angle between object and light source, --angle => --light

- Diffuse Reflection: An idealized kind of reflection that spreads the incoming
  light evenly in all direction around the surface normal. Gives a matte look.

- Ambient Reflection: A constant value that represent light that has arrived
  from other surfaces in the scene.

- Perfect Mirrors: Rays are perfectly reflected on surface. Difficult to compute.

- Specular Reflection: Another idealized type of reflection were the incoming
  light is reflected at an equal angle direction around the surface. Creates
  highlights. Glossy part of Phong.

- Glossy Reflection: Phong, wrong but looks ok. Consists of: Ambient, Diffuse
  and Specular.

- Refraction: penna i glas med halva vatten tack

## Local vs. Global Illumination

A local illumination algorithm only affects the object itself while a global
illumination algorithm will affect other objects and the whole scene.

# Slide 8 (Raytracing)

In ray tracing, light rays are processed in inverse direction. It is assumed
that all rays start at the eye of an observer (the viewing point), pass through
the image plane toward objects in a scene, and finally reach the light sources. 

## Raytracing reflection

Recursive computation for N-levels.

## Spatial data structures

### Bounding Volume

We enclose groups of objects in sets of hierarchical bounding volumes and first
test for intersection with the bounding volume, and then only if there is an
intersection, against the objects enclosed by the volume.

Common data-structures: BSP-tree, kD-tree, Quad-tree and Octo-tree.

# Slide 9 (volumerendinering)

## Direct volume rendering

– Consider the data as a light-emitting medium with specific emission and
absorption properties. The visual impression when looking at it is simulated
according to the laws of physics

## Indirect volume rendering techniques

– Convert/reduce volume data to an intermediate representation (e.g., surface
representation), which can be rendered with traditional techniques

## Slicing:

Map data on a series of 2D planes through the volume.
Map data to colors, display on a slice plane

## Isosurfacing:

(Semi-)opaque surfaces, material boundaries

## Transparency effects:

Volume material attenuates reflected or emitted light

## Transfer function

A transfer function maps data values to colors that can be used to visually
display the data

## Color maps used as transfer function

Rainbow color map: The rainbow color map tends to hide variation in regions of
low contrast and appears less smooth in regions of high contrast making it hard
to distinguish between values that are in these regions.
