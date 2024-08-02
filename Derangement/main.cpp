#include <assert.h>
#include <stdio.h>

#include <cstdint>
#include <iostream>
#include <set>
#include <vector>

void PrintVector(std::vector<std::uint8_t> const &vec) {
    constexpr static bool kEnableOutput{false};
    if (!kEnableOutput) {
        return;
    }

    std::cout << '[' << ' ';
    for (auto const &ele : vec) {
        std::cout << static_cast<std::int32_t>(ele) << ' ';
    }
    std::cout << ']' << std::endl;
}

// Algorithm with constant space complexity is possible.
// Following O(N) algorithm is chosen only for better readiblity.
std::uint64_t CalcPermutationsByAlgebra(std::uint8_t const N) {
    assert(N > 0);
    // D[0] is a placeholder to make index align with the document.
    std::vector<std::uint64_t> D(N + 1, 0);
    D[1] = 0;
    D[2] = 1;
    for (std::uint8_t i{3U}; i <= N; ++i) {
        D[i] = (i - 1) * (D[i - 1] + D[i - 2]);
    }
    return D[N];
}

std::uint64_t FillOneMoreNest(std::vector<std::uint8_t> const &nests, std::vector<std::uint8_t> const &homeless_birds) {
    if (homeless_birds.empty()) {
        // Every bird has an ideal nest, making current nests a feasible permutation.
        PrintVector(nests);
        return 1;
    }
    std::uint64_t ret{0};
    for (std::uint8_t i{1U}; i < nests.size(); ++i) {
        if (nests[i] != 0) {
            // Do not repeatedly process occupied nest.
            continue;
        }
        for (std::uint8_t j{0U}; j < homeless_birds.size(); ++j) {
            std::uint8_t const homeless_bird{homeless_birds[j]};
            // Birds and nests are 1-indexed.
            if (i == homeless_bird) {
                // No birds wants to stay in its own nest.
                continue;
            }
            std::vector<std::uint8_t> new_nests{nests};
            std::vector<std::uint8_t> new_homeless_birds{homeless_birds};
            new_nests[i] = homeless_bird;
            new_homeless_birds.erase(new_homeless_birds.begin() + j);
            ret += FillOneMoreNest(new_nests, new_homeless_birds);
        }
        // In a feasible permutation, every bird should have its own nest.
        if (!homeless_birds.empty()) {
            return ret;
        }
    }
    return ret;
}

std::uint64_t CalcPermutationsByBackTrace(std::uint8_t const N) {
    assert(N > 0);
    // Value in nests represent the index of the bird occupying this nest.
    // Value 0 means the nest is not occupied yet.
    // Index 0 is a placeholder for easier indexing.
    std::vector<std::uint8_t> nests(N + 1, 0);
    std::vector<std::uint8_t> homeless_birds(N);
    for (std::uint8_t i{0U}; i < N; ++i) {
        homeless_birds[i] = i + 1;
    }
    return FillOneMoreNest(nests, homeless_birds);
}

int main() {
    std::uint8_t kMaxN{10U};
    for (std::uint8_t N{1U}; N <= kMaxN; ++N) {
        std::uint64_t const sol1{CalcPermutationsByAlgebra(N)};
        std::uint64_t const sol2{CalcPermutationsByBackTrace(N)};
        assert(sol1 == sol2);
        printf("N = %u, D_N = %lu.\n", N, sol1);
    }
    return 0;
}