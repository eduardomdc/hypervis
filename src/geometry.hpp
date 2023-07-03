#ifndef GEOMETRY
#define GEOMETRY

typedef struct point2d {
    float x;
    float y;
} point2d;

typedef struct pointnd {
    float* vec;
    int dim;
} pointnd;

typedef struct edge {
    pointnd* a;
    pointnd* b;
} edge;

typedef struct object {
    pointnd* points;
    edge* edges;
    int numPoints;
    int numEdges;
    int dimension;
} object;

object makeCube(float size);
void rotateAroundX(object obj, float ang);

#endif
