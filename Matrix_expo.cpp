#define REP(i,n) for(int i = 0; i < (n); i++)
const int mod = 1e9 + 7;
struct Matrix {
    int a[2][2] = {{0, 0}, {0, 0}};
    Matrix operator *(const Matrix& other) {
        Matrix product;
        REP(i, 2)REP(j, 2)REP(k, 2) {
            product.a[i][k] = (product.a[i][k] + (int) a[i][j] * other.a[j][k]) % mod;
        }
        return product;
    }
};
Matrix expo_power(Matrix a, int k) {
    Matrix product;
    REP(i, 2) product.a[i][i] = 1;
    while (k > 0) {
        if (k % 2) {
            product = product * a;
        }
        a = a * a;
        k /= 2;
    }
    return product;
}