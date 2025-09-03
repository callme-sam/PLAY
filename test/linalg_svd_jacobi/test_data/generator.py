import os
import sys
import numpy as np
from scipy.linalg import eigh

def parse_args():
    """Parse command line arguments for matrix dimensions."""
    if len(sys.argv) != 2:
        print("Error: missing arguments <M>")
        print("Usage: python3 generator.py <M>")
        sys.exit(1)

    try:
        M = int(sys.argv[1])
    except ValueError:
        print("Error: <M> must be integer")
        print("Usage: python3 generator.py <M>")
        sys.exit(1)

    return M

def generate_matrix(rows, cols):
    """Generate a matrix of floats with given dimensions."""
    return np.random.randn(rows, cols)

def generate_vector(length):
    """Generate a vector of floats."""
    return np.random.randn(length)

def generate_scalar():
    """Generate a random scalar"""
    return np.random.rand()

def get_symm_mat(mat):
    return mat.T @ mat

def svd_jacobi(mat):
    """Computes the Singular Value Decomposition (SVD) of a symmetric matrix using the Jacobi algorithm"""
    eigvals, eigvecs = eigh(mat)
    idx = eigvals.argsort()[::-1]
    eigvals = eigvals[idx]
    eigvecs = eigvecs[:, idx]
    expected_matrix = np.diag(eigvals)
    vec_S = np.sqrt(np.maximum(eigvals, 0))
    mat_V = eigvecs
    return expected_matrix, vec_S, mat_V

def format_matrix(array):
    """Convert a NumPy matrix into a C-style array."""
    # Flatten the array for C representation
    flat_array = array.flatten()
    return "{ " + ", ".join(f"{x:f}" for x in flat_array) + " }"

def format_array(array):
    """Convert a NumPy array into a C-style array."""
    return "{ " + ", ".join(f"{x:f}" for x in array) + " }"

def format_float(value):
    """Convert a float value into a C-style representation."""
    return f"{value:f}"

def generate_header_file(M, mat, S, V, expected, filename="data.h"):
    """Generate a C header file containing the matrices and their expected result."""

    script_dir = os.path.dirname(os.path.abspath(__file__))
    filepath = os.path.join(script_dir, filename)

    with open(filepath, "w") as f:
        f.write("#ifndef DATA_H_\n")
        f.write("#define DATA_H_\n\n")
        f.write('#include "pmsis.h"\n\n')

        f.write(f"#define DIM_M {M}\n\n")

        f.write(f"PI_L2 float mat[] = {format_matrix(mat)};\n")
        f.write(f"PI_L2 float V[] = {format_matrix(V)};\n")
        f.write(f"PI_L2 float S[] = {format_array(S)};\n")
        f.write(f"PI_L2 float expected[] = {format_matrix(expected)};\n\n")

        f.write("#endif  /* DATA_H_ */\n")

def main():
    M = parse_args()
    mat = generate_matrix(M, M)
    mat = get_symm_mat(mat)

    expected, S, V = svd_jacobi(mat)

    generate_header_file(M, mat, S, V, expected)
    print(f"File 'data.h' successfully generated for matrices of size {M}x{M}.")

if __name__ == "__main__":
    main()
