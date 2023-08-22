#!/usr/bin/env python

import sys

def main(npoints, ndims):
    import numpy as np
    sys.stdout.write("{}\t{}\n".format(npoints, ndims))
    pc = np.random.rand(npoints, ndims).tolist()
    for i in range(npoints):
        sys.stdout.write("\t".join(str(p) for p in pc[i]) + "\n")
        sys.stdout.flush()
    return 0

if __name__ == "__main__":
    if len(sys.argv) != 3:
        sys.stderr.write("Usage: {} <npoints> <ndims>\n".format(sys.argv[0]))
        sys.stderr.flush()
        sys.exit(-1)
    npoints = int(sys.argv[1])
    ndims = int(sys.argv[2])
    main(npoints, ndims)
