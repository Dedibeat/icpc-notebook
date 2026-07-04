// Safe hash for unordered_map/set. libstdc++'s default hash for integers is
// the IDENTITY: a setter can pick keys colliding mod the bucket prime and
// degrade the map to O(n) per op (same anti-test class as mod-2^64 string
// hashing). splitmix64 + runtime-random offset defeats fixed test data.
// Usage: unordered_map<long long, int, chash> mp;
struct chash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const {
        static const uint64_t R =
            chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + R);
    }
};
