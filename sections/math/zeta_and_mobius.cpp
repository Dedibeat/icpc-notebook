template<typename T>
void SubsetZetaTransform(vector<T>& v) {
	const int n = v.size(); // n must be a power of 2
	for (int j = 1; j < n; j <<= 1) {
		for (int i = 0; i < n; i++)
			if (i & j) v[i] += v[i ^ j];
	}
}

template<typename T>
void SubsetMobiusTransform(vector<T>& v) {
	const int n = v.size(); // n must be a power of 2
	for (int j = 1; j < n; j <<= 1) {
		for (int i = 0; i < n; i++)
			if (i & j) v[i] -= v[i ^ j];
	}
}

template<typename T>
void SupersetZetaTransform(vector<T>& v) {
	const int n = v.size(); // n must be a power of 2
	for (int j = 1; j < n; j <<= 1) {
		for (int i = 0; i < n; i++)
			if (i & j) v[i ^ j] += v[i];
	}
}

template<typename T>
void SupersetMobiusTransform(vector<T>& v) {
	const int n = v.size(); // n must be a power of 2
	for (int j = 1; j < n; j <<= 1) {
		for (int i = 0; i < n; i++)
			if (i & j) v[i ^ j] -= v[i];
	}
}

template<typename T>
void DivisorZetaTransform(vector<T>& v) {
	const int n = (int)v.size() - 1;
	for (int p : PrimeEnumerate(n)) {
		for (int i = 1; i * p <= n; i++)
			v[i * p] += v[i];
	}
}

template<typename T>
void DivisorMobiusTransform(vector<T>& v) {
	const int n = (int)v.size() - 1;
	for (int p : PrimeEnumerate(n)) {
		for (int i = n / p; i; i--)
			v[i * p] -= v[i];
	}
}
template<typename T>
void MultipleZetaTransform(vector<T>& v) {
	const int n = (int)v.size() - 1;
	for (int p : PrimeEnumerate(n)) {
		for (int i = n / p; i; i--)
			v[i] += v[i * p];
	}
}

template<typename T>
void MultipleMobiusTransform(vector<T>& v) {
	const int n = (int)v.size() - 1;
	for (int p : PrimeEnumerate(n)) {
		for (int i = 1; i * p <= n; i++)
			v[i] -= v[i * p];
	}
