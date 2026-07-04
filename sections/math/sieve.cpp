// Sieve of Eratosthenes; returns primes < lim. Requires lim <= MAX_PR.
// Time: lim=1e9 ~ 1.5s if MAX_PR is raised; 5e6 is instant.
const int MAX_PR = 5'000'000;
bitset<MAX_PR> isprime;
vector<int> eratosthenesSieve(int lim) {
	isprime.set(); isprime[0] = isprime[1] = 0;
	for (int i = 4; i < lim; i += 2) isprime[i] = 0;
	for (int i = 3; i*i < lim; i += 2) if (isprime[i])
		for (int j = i*i; j < lim; j += i*2) isprime[j] = 0;
	vector<int> pr;
	for (int i = 2; i < lim; i++) if (isprime[i]) pr.push_back(i);
	return pr;
}
