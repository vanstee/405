/*
  Model.h

  Header File for Geometric Model Class
  Provides for construction of cuboid, cylinder and cone shapes tiled by triangles
  
  BIHE Computer Graphics    Donald H. House     6/22/06
*/

#ifndef _MODEL_H_
#define _MODEL_H_

#include "Vector.h"

#define MAXVERTICES   1000		  // shapes limited to 1000 vertices
#define MAXTRIANGLES  (MAXVERTICES / 3)

class Model{
private:
  Vector3d vertices[MAXVERTICES];   // vertex coordinates
  int nvertices;		    // count of the number of vertices
  int triangles[MAXTRIANGLES][3];   // 3 vertex indices for each triangle
  Vector2d texcoords[MAXTRIANGLES][3];   // 3 sets of texture coordinates for each triangle
  Vector3d normals[MAXTRIANGLES];   // unit normal vector for each triangle
  int ntriangles;		    // count of the number of triangles
  
  void Clean();			    // bookkeeping, remove all vertices and triangles
  
  int AddVertex(const Vector3d &v); // insert a simple vertex into vertex table

  // insert a triangle and its normal, without texture coords
  int AddTriangle(int v0, int v1, int v2);
  // insert a triangle and its normal, with texture coords
  int AddTriangle(int v0, int v1, int v2, const Vector2d &t0, const Vector2d &t1, const Vector2d &t2);
  
public:
  // Constructor, make sure model is empty
  Model();
  
  // Make a cuboid model
  void BuildCuboid(float width = 1.0, float height = 1.0, float depth = 1.0);
  
  // Make a cylinder model
  void BuildCylinder(float radius = 0.5, float height = 1.0);
  
  // Make a cone model
  void BuildCone(float radius = 0.5, float height = 1.0);
  
  // draw the current model in wireframe or shaded
  void Draw(int wireframe = 1);
};

#endif

