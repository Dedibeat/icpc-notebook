const int N = 1e6;
int mu[N + 1], primes[N + 1], pcnt;
bool is_comp[N + 1];

void mobius_sieve(int n) { // linear sieve; each composite is visited once
    pcnt = 0;
    fill(mu, mu + n + 1, 0);
    fill(is_comp, is_comp + n + 1, false);
    mu[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!is_comp[i]) primes[pcnt++] = i, mu[i] = -1;
        for (int j = 0; j < pcnt && i * primes[j] <= n; j++) {
            is_comp[i * primes[j]] = true;
            if (i % primes[j] == 0) break; // mu stays 0: square factor
            mu[i * primes[j]] = -mu[i];
        }
    }
}
