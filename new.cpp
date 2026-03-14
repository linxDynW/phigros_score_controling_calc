#include <chrono>
#include <iostream>
#include <vector>

using namespace std;

#define min(a, b) ((a) <= (b) ? (a) : (b))
#define max(a, b) ((a) >= (b) ? (a) : (b))

struct result_t {
    int p;
    int g;
    int m;
    int mc;
};

void prt(int p, int g, int m, int mc) {
    std::cout << "p:" << p << " g:" << g << " m:" << m << " mc:" << mc << std::endl;
}

inline int64_t r(int64_t n, int64_t d) {
    int64_t q = n / d;
    int64_t tr = 2LL * (n % d);
    return (tr < d) ? q : (tr > d ? q + 1 : (q % 2 ? q + 1 : q));
}

#ifndef PTST
vector<result_t> function(int S, int N) {
#else
uint64_t function(int S, int N) {
#endif
    int64_t s, k, kl, kl1, kr, kr1, t, tl, tr, p, g, m, mc;
#ifndef PTST
    vector<result_t> result;
#else
    uint64_t result = 0;
#endif
    for (mc = N; mc >= 0; mc--) {
        s = S - r(mc * 100000LL, N);
        kl1 = N * (1799997LL - 2 * s);
        kl = kl1 >= 0 ? (kl1 + 89999LL) / 90000LL : 0;
        kr1 = N * (1800003LL - 2 * s);
        kr = kr1 >= 0 ? kr1 / 90000LL : 0;
        for (k = kl; k <= kr; k++) {
            if (S != r((180 * N - 9 * k + 20 * mc) * 5000LL, N)) {
                continue;
            }
            tl = max((k + 6) / 7, (2 * k - N + 12) / 13);
            tl = max(tl, ((k + (N / (mc + 1))) + 6) / 7);
            tr = min((3 * k) / 20, (N + k - mc) / 7);
            for (t = tl; t <= tr; t++) {
#ifndef PTST
                result.emplace_back( //
                    result_t{        //
                             (int)(N - 2 * k + 13 * t),
                             (int)(3 * k - 20 * t),
                             (int)(7 * t - k),
                             (int)mc});
#else
                result++;
#endif
            }
        }
    }
    return result;
}

int main(int argc, char* argv[]) {
    if (argc != 3 && argc != 4) {
        return 1;
    }
    bool enable_prt = true;
    if (argc == 4) {
        enable_prt = false;
    }
    int S = atoi(argv[1]);
    int N = atoi(argv[2]);

    auto t1 = std::chrono::high_resolution_clock::now();
    auto result = function(S, N);
    auto t2 = std::chrono::high_resolution_clock::now();
    auto delta = std::chrono::duration_cast<std::chrono::duration<double, std::ratio<1, 1000>>>(t2 - t1);
    uint64_t count;
#ifndef PTST
    if (enable_prt) {
        for (const auto& x : result) {
            prt(x.p, x.g, x.m, x.mc);
        }
    }
    count = result.size();
#else
    count = result;
    std::cout << "(results not saved)" << std::endl;
#endif

    std::cout << count << " item(s) finished in " << delta.count() << "ms. " << std::endl;

    return 0;
}
