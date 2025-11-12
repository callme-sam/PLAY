#include "snrt.h"
#include "printf.h"

#define LEN 8

float *vec;
int idx_match;
float search_value;


__attribute__((noinline)) static void print_data()
{
    printf("vec: ");
    for (int i = 0; i < LEN; i++)
        printf("%.1f ", vec[i]);
    printf("\n");
}

__attribute__((noinline)) static void init_data()
{
    search_value = 1.0f;

    vec = snrt_l1alloc(LEN * sizeof(float));

    for (int i = 0; i < LEN; i++) {
        vec[i] = 0.0f;
    }

    vec[3] = search_value;
    vec[5] = search_value;
}

__attribute__((noinline)) static void test_vfirst_m()
{
    size_t avl;
    size_t vl;

    avl = LEN;

    asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(avl));

    asm volatile ("vle32.v v0, (%0)" :: "r"(vec));
    snrt_cluster_hw_barrier();

    asm volatile ("vmfeq.vf v8, v0, %0" :: "f"(search_value));
    snrt_cluster_hw_barrier();

    asm volatile ("vfirst.m %0, v8" : "=r"(idx_match));
    snrt_cluster_hw_barrier();
}

int main()
{
    printf("################################### Testing vfirst.m #######################################\n");

    init_data();
    print_data();

    test_vfirst_m();

    printf("Result of vfirst.m: %d\n", idx_match);

    printf("############################################################################################\n");

    return 0;
}

__attribute__((always_inline)) static int rvv_find_max_val(float *mat, const int dim_M, const int dim_N, int *max_idx, int col)
{
    size_t stride;
    float *row_m;
    size_t avl;
    size_t vl;
    float max;

    int base_idx;
    int local_idx;

    // --- Passaggio 1: Trova il Massimo Valore 'max' ---

    // Inizializzazione
    row_m = mat + col * dim_N + col;         // Puntatore alla colonna mat[col][col]
    stride = dim_N * sizeof(float);          // Stride in byte
    avl = dim_M - col;                       // Lunghezza della ricerca

    // Inizializza VL e v0 (accumulatore max) a 0.0f
    asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(avl));
    asm volatile ("vfmv.v.f v0, %0" :: "f"(0.0));

    // Loop 1: Scansione per la Riduzione Massima
    for (; avl > 0; avl -= vl) {
        asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(avl));

        // Carica dati con stride in v8
        asm volatile ("vlse32.v v8, (%0), %1" :: "r"(row_m), "r"(stride));
        snrt_cluster_hw_barrier();

        // Valore Assoluto e Accumulo Max: v0 = max(|v8|, v0)
        asm volatile ("vfabs.v v8, v8");
        asm volatile ("vfmax.vv v0, v8, v0");

        row_m += vl * dim_N;
    }

    // Riduzione finale e spostamento del risultato in 'max'
    asm volatile ("vfredmax.vs v0, v0, v0");
    snrt_cluster_hw_barrier();
    asm volatile ("vfmv.f.s %0, v0" : "=f"(max));
    snrt_cluster_hw_barrier();


    // ----------------------------------------------------------------------
    // --- Passaggio 2: Trova l'Indice Assoluto '*max_idx' con RVV ---
    // ----------------------------------------------------------------------

    // Reset puntatori e contatori
    row_m = mat + col * dim_N + col;
    avl = dim_M - col;
    base_idx = col; // Indice di riga di partenza

    // Inizializza l'indice di default (in caso di colonna di tutti zeri, per esempio)
    *max_idx = col;

    // Loop 2: Scansione per l'Indice
    for (; avl > 0; avl -= vl) {
        asm volatile ("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(avl));

        // 1. Carica dati in v8
        asm volatile ("vlse32.v v8, (%0), %1" :: "r"(row_m), "r"(stride));
        snrt_cluster_hw_barrier();

        // 2. Valore Assoluto
        asm volatile ("vfabs.v v8, v8");

        // 3. Confronto: Crea una maschera (v2) dove v8 == max
        asm volatile ("vmfeq.vf v2, v8, %0" :: "f"(max));
        snrt_cluster_hw_barrier();

        // 4. Trova la Prima Corrispondenza: local_idx = vfirst.m(v2)
        // local_idx (risultato in GPR) sarà l'indice locale (0 a vl-1) o -1 se non trovato
        asm volatile ("vfirst.m %0, v2" : "=r"(local_idx) ::);
        snrt_cluster_hw_barrier();

        // Logica C: Verifica se è stata trovata una corrispondenza
        if (local_idx >= 0) {
            // Indice assoluto = indice di base + indice locale
            *max_idx = base_idx + local_idx;
            goto index_found; // Esci immediatamente dal loop
        }

        // 5. Aggiornamento per il prossimo chunk
        row_m += vl * dim_N;
        base_idx += vl;
    }

index_found:

    return 0;
}
