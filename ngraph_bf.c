#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <math.h>

/*
 * File:     ngraph_bf.c
 * Author:   Gabriel Raulet
 * Date:     08/21/2023
 * Purpose:  Construct the neighborhood graph of a point cloud at a given scale.
 */

double* read_points(const char *fname, size_t *npoints, int *dim);

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <scale> <points.txt>\n", argv[0]);
        return -1;
    }

    double scale = atof(argv[1]);
    const char *fname = argv[2];

    size_t n;
    int k;

    double *points = read_points(fname, &n, &k);

    printf("num points = %lu\n", n);
    printf("dimensions = %d\n", k);

    for (size_t i = 0; i < n; ++i)
    {
        for (int j = 0; j < k; ++j)
            printf("%.5f\t", points[i*k + j]);

        printf("\n");
    }

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
