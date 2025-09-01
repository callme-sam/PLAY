import os
import sys
import numpy as np
from scipy.linalg import lu

def parse_args():
    """Parse command line arguments for matrix dimensions."""
    if len(sys.argv) != 3:
        print("Error: missing arguments <M> <N>")
        print("Usage: python3 generator.py <M> <N>")
        sys.exit(1)

    try:
        M = int(sys.argv[1])
        N = int(sys.argv[2])
    except ValueError:
        print("Error: <M> and <N> must be integers")
        print("Usage: python3 generator.py <M> <N>")
        sys.exit(1)

    return M, N

def generate_matrix(rows, cols):
    """Generate a matrix of floats with given dimensions."""
    return np.random.randn(rows, cols)

def lu_decomp(mat):
    """Performs LU decomposition of matix mat with partial pivoting"""

    rows, cols = mat.shape
    dim_min = min(rows, cols)

    perm, L, U = lu(mat, permute_l=False, p_indices=True)

    dst = np.copy(mat)

    dst[:dim_min, :dim_min] = U
    for i in range(rows):
        for j in range(dim_min):
            if (i > j):
                dst[i, j] = L[i, j]

    return dst, perm

def format_matrix(array):
    """Convert a NumPy matrix into a C-style array."""
    # Flatten the array for C representation
    flat_array = array.flatten()
    return "{ " + ", ".join(f"{x:f}" for x in flat_array) + " }"

def format_array(array):
    """Convert a NumPy array into a C-style array."""
    return "{ " + ", ".join(f"{x}" for x in array) + " }"

def format_float(value):
    """Convert a float value into a C-style representation."""
    return f"{value:f}"

def generate_header_file(M, N, mat, perm, expected, filename="data.h"):
    """Generate a C header file containing the matrices and their expected result."""

    script_dir = os.path.dirname(os.path.abspath(__file__))
    filepath = os.path.join(script_dir, filename)

    with open(filepath, "w") as f:
        f.write("#ifndef DATA_H_\n")
        f.write("#define DATA_H_\n\n")
        f.write('#include "pmsis.h"\n\n')

        f.write(f"#define DIM_M {M}\n")
        f.write(f"#define DIM_N {N}\n\n")

        f.write(f"PI_L2 float mat[] = {format_matrix(mat)};\n")
        f.write(f"PI_L2 int expected_perm[] = {format_array(perm)};\n")
        f.write(f"PI_L2 float expected_mat[] = {format_matrix(expected)};\n\n")

        f.write("#endif  /* DATA_H_ */\n")

def main():
    M, N = parse_args()
    mat = generate_matrix(M, N)

    expected, perm = lu_decomp(mat)

    generate_header_file(M, N, mat, perm, expected)
    print(f"File 'data.h' successfully generated for matrices of size {M}x{N}.")

if __name__ == "__main__":
    main()
