const int mod = 1e9 + 7, MOD = 1e9 + 7;
int mod_expo(int x, int p, int mod = MOD) {
    int res = 1; x = ((x % mod) + mod) % mod;
    while (p > 0) {
        if (p & 1)res = (res * x) % mod;
        x = (x * x) % mod; p /= 2;
    }
    return res;
}
inline int mod_inv(int x, int mod = MOD) { return mod_expo(x, mod - 2, mod); }
vector<int> fact, inv_fact;
void precalculate_factorials(int MAX_FACT) {
    fact.resize(MAX_FACT + 1);
    inv_fact.resize(MAX_FACT + 1);
    fact[0] = 1;
    for (int i = 1; i <= MAX_FACT; i++)
        fact[i] = (fact[i - 1] * i) % MOD;
    inv_fact[MAX_FACT] = mod_inv(fact[MAX_FACT]);
    for (int i = MAX_FACT - 1; i >= 0; i--)
        inv_fact[i] = (inv_fact[i + 1] * (i + 1)) % MOD;
}
inline int nPr_mod(int n, int r) { return (n < r) ? 0 : (fact[n] * inv_fact[n - r]) % MOD; }
inline int nCr_mod(int n, int r) { return (n < r) ? 0 : (nPr_mod(n, r) * inv_fact[r]) % MOD; }