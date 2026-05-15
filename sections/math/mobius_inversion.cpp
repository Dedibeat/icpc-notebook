const int N = 1e6;
// NOTE: arrays are size N, so mobius_sieve(N) is out of bounds. Use N+1.
int mu[N], primes[N], pcnt;
bool is_comp[N];

void mobius_sieve(int n) {
    mu[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!is_comp[i]) {
            primes[pcnt++] = i;
            mu[i] = -1;
        }
        for (int j = 0; j < pcnt && i * primes[j] <= n; j++) {
            int x = i * primes[j];
            is_comp[x] = true;
            if (i % primes[j] == 0) {
                mu[x] = 0;
                break;
            } else {
                mu[x] = -mu[i];
            }
        }
    }
}
