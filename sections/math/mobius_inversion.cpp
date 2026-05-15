const int N = 1e6;
int mu[N + 1], primes[N + 1], pcnt;
bool is_comp[N + 1];

void mobius_sieve(int n) {
    pcnt = 0;
    for (int i = 0; i <= n; i++) {
        mu[i] = 0;
        is_comp[i] = false;
    }
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
