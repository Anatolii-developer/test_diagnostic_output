/* { dg-do compile } */
/* { dg-options "-O2 -fdump-tree-all" } */

int main() {
    int a = 5;
    int b = 10;
    int c = a + b;
    return c;
}

/* { dg-final { scan-tree-dump "Executing pass_prune_clones" "gimple" } } */
