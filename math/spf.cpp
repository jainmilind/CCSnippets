vector<bool> is_prime;
vector<int> primes;
vector<int> spf;
void prime_sieve(int MAX_PR) {
    is_prime.assign(MAX_PR + 1, 1);
    spf.resize(MAX_PR + 1);
    iota(spf.begin(), spf.end(), 0);
    is_prime[0] = is_prime[1] = 0;
    for (int i = 4; i <= MAX_PR; i += 2) {
        is_prime[i] = 0;
        spf[i] = 2;
    }
    for (int i = 3; i * i <= MAX_PR; i += 2)
        if (is_prime[i])
            for (int j = i * i; j <= MAX_PR; j += i * 2) {
                is_prime[j] = 0;
                if (spf[j] == j)spf[j] = i;
            }
    primes.push_back(2);
    for (int i = 3; i <= MAX_PR; i += 2)
        if (is_prime[i])
            primes.push_back(i);
}

vector<int> get_fact(int x) {
    vector<int> ret;
    while (x != 1) {
        ret.push_back(spf[x]);
        x /= spf[x];
    }
    return ret;
}
