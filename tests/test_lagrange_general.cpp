#include "../sections/hacks/lagrange_general.cpp"
#include "../sections/math/lagrange_interpolation.cpp"

ll polynomial(const vector<ll>& a, ll x) {
    ll value = 0; x = hnorm(x);
    for (int i = (int)a.size()-1; i >= 0; --i)
        value = (value*x + hnorm(a[i])) % HMOD;
    return value;
}
int main() {
    assert(!lagrangeGeneral({}, {}, 0));
    assert(!lagrangeGeneral({1}, {}, 1));
    assert(!lagrangeGeneral({}, {1}, 1));
    assert(!lagrangeGeneral({1,2}, {1}, 1));
    assert(!lagrangeGeneral({1,1}, {2,2}, 1));
    assert(!lagrangeGeneral({1,1+HMOD}, {2,3}, 1));
    assert(!lagrangeGeneral({-1,HMOD-1}, {2,2}, 7));
    // A sample-point query must not bypass duplicate validation elsewhere.
    assert(!lagrangeGeneral({0,1,1+HMOD}, {9,3,3}, 0));
    assert(lagrangeGeneral({-1,2,4}, {1,4,16}, 3) == 9);
    assert(lagrangeGeneral({3,9}, {0,0}, LLONG_MAX) == 0);
    vector<ll> extreme{LLONG_MIN,LLONG_MAX,-HMOD,-1,0,1,HMOD,HMOD+1};
    for (ll x : extreme) for (ll at : extreme) {
        assert(lagrangeGeneral({x}, {-7}, at) == HMOD-7);
        assert(lagrangeGeneral({x}, {LLONG_MIN}, at) == hnorm(LLONG_MIN));
    }
    vector<ll> xs{LLONG_MIN,LLONG_MAX,0}, coefficients{-7,13,LLONG_MAX}, ys;
    for (ll x : xs) ys.push_back(polynomial(coefficients,x));
    for (ll at : extreme)
        assert(lagrangeGeneral(xs,ys,at) == polynomial(coefficients,at));

    mt19937_64 rng(20260912);
    for (int it = 0; it < 1500; ++it) {
        int n = pick(rng,1,25);
        vector<ll> a(n), x, y, consecutive;
        for (ll& v : a) v = pick(rng,-2*HMOD,2*HMOD);
        set<ll> used;
        while ((int)x.size() < n) {
            ll v = pick(rng,-3*HMOD,3*HMOD);
            if (used.insert(hnorm(v)).second) x.push_back(v);
        }
        for (ll v : x) y.push_back(polynomial(a,v)-HMOD);
        for (int i = 0; i < n; ++i) consecutive.push_back(polynomial(a,i));
        for (ll at : {x.front(), x.back(), pick(rng,-4*HMOD,4*HMOD), LLONG_MAX}) {
            auto got = lagrangeGeneral(x,y,at);
            assert(got && *got == polynomial(a,at));
            assert(*got == lagrangeConsecutive(consecutive,at));
        }
        reverse(x.begin(),x.end()); reverse(y.begin(),y.end());
        assert(lagrangeGeneral(x,y,-1) == polynomial(a,-1));
        x.push_back(x[0]+HMOD); y.push_back(y[0]);
        assert(!lagrangeGeneral(x,y,x[0]));
    }
    cout << "General Lagrange: edge cases + 1500 random polynomials OK\n";
}
