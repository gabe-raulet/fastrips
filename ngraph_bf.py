#!/usr/bin/env python

import sys

def dist(x, y):
    k = len(x)
    return sum((x[i]-y[i])**2 for i in range(k)) ** 0.5

def read_points(fname):
    points = []
    with open(fname, "r") as f:
        n, k = (int(item) for item in next(f).rstrip().split())
        for i in range(n):
            p = [float(item) for item in next(f).rstrip().split()]
            points.append(p)
    return points

def create_ngraph(points, scale):
    edges = []
    nverts = len(points)
    k = len(points[0])
    for v in range(nverts):
        for u in range(v):
            if dist(points[u], points[v]) <= scale:
                edges.append((u,v))
    return edges

def write_ngraph(fname, edges, nverts):
    with open(fname, "w") as f:
        f.write("{}\t{}\n".format(nverts, len(edges)))
        for u, v in sorted(edges):
            f.write("{}\t{}\n".format(u+1, v+1))

def main(scale, points_fname, graph_fname):
    points = read_points(points_fname)
    edges = create_ngraph(points, scale)
    write_ngraph(graph_fname, edges, len(points))
    return 0

if __name__ == "__main__":
    if len(sys.argv) != 4:
        sys.stderr.write("Usage: {} <scale> <points.txt> <graph.txt>\n".format(sys.argv[0]))
        sys.stderr.flush()
        sys.exit(-1)
    scale = float(sys.argv[1])
    points_fname = sys.argv[2]
    graph_fname = sys.argv[3]
    main(scale, points_fname, graph_fname)

