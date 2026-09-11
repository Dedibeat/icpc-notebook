// Shared C++17 setup; copy once before the selected snippets.
// Modular helpers: O(log e) power, O(1) normalization; fixed prime only.
// Signed 64-bit products are safe for this modulus. Do not increase blindly.
#pragma once
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
const ll HMOD = 1000000007;
ll hnorm(ll x) { x %= HMOD; return x < 0 ? x + HMOD : x; }
ll hpow(ll a, ll e) {
    ll r = 1; a = hnorm(a);
    for (; e; e >>= 1, a = a * a % HMOD)
        if (e & 1) r = r * a % HMOD;
    return r;
}
// Seed once in main; use a fixed seed while debugging.
// mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ll pick(mt19937_64& rng, ll lo, ll hi) {
    return uniform_int_distribution<ll>(lo, hi)(rng);
}
