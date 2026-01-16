import os
import sys
import numpy as np
from scipy.linalg import solve_triangular

def parse_args():
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

def generate_backward_solve_test(M):
    random_matrix = np.random.rand(M, M).astype(np.float32)
    U = np.triu(random_matrix)
    for i in range(M):
        U[i, i] = np.random.rand() * 2.0 + 1.0  # valori tra 1.0 e 3.0

    y = np.random.rand(M).astype(np.float32)
    expected = np.linalg.solve(U, y).astype(np.float32)

    residuo = np.dot(U, expected) - y
    norma_residuo = np.linalg.norm(residuo)

    if norma_residuo > 1e-4:
        print(f"ATTENZIONE: Residuo elevato {norma_residuo}")
        print(f"Numero di condizione: {np.linalg.cond(U)}")

    return U, y, expected


def format_matrix(array):
    flat_array = array.flatten()
    return "{ " + ", ".join(f"{x:f}" for x in flat_array) + " }"

def format_array(array):
    return "{ " + ", ".join(f"{x:f}" for x in array) + " }"

def format_float(value):
    return f"{value:f}"

def generate_header_file(M, U, y, expected):
    filename = f"data.h"
    script_dir = os.path.dirname(os.path.abspath(__file__))
    filepath = os.path.join(script_dir, filename)

    with open(filepath, "w") as f:
        f.write("#ifndef BW_DATA_H_\n")
        f.write("#define BW_DATA_H_\n\n")

        f.write(f"#define DIM_M {M}\n\n")

        f.write(f"float U[] = {format_matrix(U)};\n")
        f.write(f"float y[] = {format_array(y)};\n")
        f.write(f"float expected[] = {format_array(expected)};\n\n")

        f.write("#endif  /* BW_DATA_H_ */\n")

def main():
    M = parse_args()
    U, y, expected = generate_backward_solve_test(M)

    print("\nVerifica (U * expected):")
    print(np.dot(U, expected))
    print("\nDifferenza (dovrebbe essere ~0):")
    print(np.linalg.norm(np.dot(U, expected) - y))

    generate_header_file(M, U, y, expected)
    print(f"File 'data_{M}.h' successfully generated for matrices of size {M}x{M}.")

if __name__ == "__main__":
    main()
