#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <math.h>
#include "vec.h"

/*
 * File:     ngraph_bf.c
 * Author:   Gabriel Raulet
 * Date:     08/21/2023
 * Purpose:  Construct the neighborhood graph of a point cloud at a given scale.
 */

typedef struct { size_t u, v; } edge_t;

double* read_points(const char *fname, size_t *npoints, int *dim);
double dist(const double *x, const double *y, int dim);
edge_t* neighborhood_graph_tuples(const double *points, size_t npoints, int dim, double scale, size_t *nedges);

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <scale> <points.txt>\n", argv[0]);
        return -1;
    }

    double scale = atof(argv[1]);
    const char *fname = argv[2];

    int k;
    size_t n, m;
    double *points;
    edge_t *es;

    points = read_points(fname, &n, &k);
    es = neighborhood_graph_tuples(points, n, k, scale, &m);

    for (size_t i = 0; i < m; ++i)
    {
        printf("%lu\t%lu\n", es[i].u+1, es[i].v+1);
    }

    free(es);
    free(points);

    return 0;
}

double* read_points(const char *fname, size_t *npoints, int *dim)
{
    assert(npoints && dim);

    FILE *f = fopen(fname, "r");
    if (!f) return NULL;

    fscanf(f, "%lu\t%d\n", npoints, dim);

    size_t n = *npoints;
    int k = *dim;

    double *points = malloc(n * k * sizeof(double));

    for (size_t i = 0; i < n; ++i)
    {
        double x;

        for (int j = 0; j < k; ++j)
        {
            fscanf(f, "%lf ", &x);
            points[i*k + j] = x;
        }

    }

    fclose(f);

    return points;
}

double dist(const double *x, const double *y, int dim)
{
    double v = 0., a;

    for (int i = 0; i < dim; ++i)
    {
        a = x[i] - y[i];
        v += a*a;
    }

    return sqrt(v);
}

edge_t* neighborhood_graph_tuples(const double *points, size_t npoints, int dim, double scale, size_t *nedges)
{
    /* brute force solution */

    vec_t(edge_t) es;
    vec_init(es);

    for (size_t v = 0; v < npoints; ++v)
        for (size_t u = 0; u < v; ++u)
            if (dist(&points[u*dim], &points[v*dim], dim) <= scale)
            {
                edge_t *e = vec_pushp(es);
                e->u = u, e->v = v;
            }

    *nedges = vec_size(es);
    return vec_release(es);
}
