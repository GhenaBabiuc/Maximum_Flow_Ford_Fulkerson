#include <cstdio>
#include <cstdlib>

int m, n;
typedef int mat[20][20];
typedef int vect[20];
mat c, a, l, f, f1;
vect di, de, l1;
int u[100][2], ei, ef;
bool gasit, sel[20];
int a1, b1, min;

void intr(void);

void matrice(void);

void verif(void);

bool ver(int, int);

void flux(int i1);

void prel(int);

void detcap(void);

void intr() {
    FILE *f;
    int i, j;
    f = fopen("../flux.in", "r");
    fscanf(f, "%d %d", &n, &m);
    for (i = 1; i <= m; i++) {
        fscanf(f, "%d %d", &u[i][0], &u[i][1]);
        fscanf(f, "%d", &j);
        c[u[i][0]][u[i][1]] = j;
    }
    fclose(f);
}

void matrice(void) {
    int i, j, k;
    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            a[i][j] = 0;
    for (i = 1; i <= m; i++)
        a[u[i][0]][u[i][1]] = 1;
    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            l[i][j] = a[i][j];
    for (k = 1; k <= n; k++)
        for (i = 1; i <= n; i++)
            if (l[i][k])
                for (j = 1; j <= n; j++)
                    if (l[i][j] < l[k][j])
                        l[i][j] = l[k][j];
}

void verif() {
    int i, j;
    for (i = 1; i <= n; i++)
        di[i] = de[i] = 0;
    a1 = b1 = 0;
    for (i = 1; i <= m; i++) {
        de[u[i][0]]++;
        di[u[i][1]]++;
    }
    for (i = 1; i <= n; i++)
        if (de[i] == 0)
            b1 = i;
    for (i = 1; i <= n; i++)
        if (di[i] == 0) {
            a1 = i;
            break;
        }
    if (a1 == 0 || b1 == 0) {
        printf("Nu este retea");
        exit(1);
    }
    for (i = 1; i <= n; i++)
        printf("Varful %d are gradul intern %d si gradul extern: %d\n", i, di[i], de[i]);
    printf("Graful este retea \n");
    printf("Varf initial %d varf final %d \n", a1, b1);
    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            f[i][j] = 0;
}

void prel(int nr) {
    int i, i1, j1;
    min = 255;
    for (i = 1; i <= nr - 1; i++) {
        i1 = l1[i];
        j1 = l1[i + 1];
        if (a[j1][i1] && f[j1][i1] < min)
            min = f[j1][i1];
        if (a[i1][j1] && c[i1][j1] - f[i1][j1] < min)
            min = c[i1][j1] - f[i1][j1];
    }
    for (i = 1; i <= nr - 1; i++) {
        i1 = l1[i];
        j1 = l1[i + 1];
        if (a[i1][j1] == 1)
            f[i1][j1] += min;
        else
            f[i1][j1] -= min;
    }
}

bool ver(int i, int j) {
    if (a[l1[i]][j] == 0)
        return false;
    return a[l1[i]][j] && c[l1[i]][j] > f[l1[i]][j];
}

void flux(int i) {
    int j;
    for (j = 1; !gasit && j <= n; j++)
        if (ver(i - 1, j) && sel[j] == false) {
            l1[i] = j;
            sel[j] = true;
            if (j == b1) {
                prel(i);
                gasit = true;
            } else if (i < n)
                flux(i + 1);
            sel[j] = false;
        }
}

void detcap(void) {
    int i, flux1;
    flux1 = 0;
    l1[1] = a1;
    do {
        gasit = false;
        for (i = 1; i <= n; i++)
            sel[i] = false;
        sel[a1] = true;
        flux(2);
        if (gasit)
            flux1 += min;
    } while (gasit);
    for (i = 1; i <= m; i++)
        printf("Arcul (%d%d) capacitatea: %d fluxul: %d \n", u[i][0], u[i][1], c[u[i][0]][u[i][1]],
               f[u[i][0]][u[i][1]]);
    printf("Fluxul este: %d \n", flux1);
}

int main() {
    intr();
    matrice();
    verif();
    detcap();
    return 0;
}