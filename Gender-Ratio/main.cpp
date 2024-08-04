#include <cmath>
#include <cstdint>
#include <string>

constexpr static std::uint8_t kBoy{0U};
constexpr static std::uint8_t kGirl{1U};

// Half-to-half probability to have a boy and girl.
std::uint8_t GenGender() {
    constexpr static double kThreshold{RAND_MAX / 2.0};
    return (rand() > kThreshold) ? kBoy : kGirl;
}

int main() {
    // Test with 10^j samples.
    for (std::uint8_t j{0U}; j < 8U; ++j) {
        std::uint64_t num_male{0U};
        std::uint64_t num_female{0U};
        std::uint32_t const num_samples{static_cast<std::uint32_t>(std::pow(10, j))};

        for (std::uint32_t i{0U}; i < num_samples; ++i) {
            while (true) {
                std::uint8_t const gender{GenGender()};
                if (gender == kBoy) {
                    ++num_male;
                    break;
                } else {
                    ++num_female;
                }
            }
        }

        double const boy_ratio{num_male * 1.0 / (num_male + num_female)};
        double const girl_ratio{1.0 - boy_ratio};

        printf("Boy-Girl ratio is %.4f : %.4f in %u samples.\n", boy_ratio, girl_ratio, num_samples);
    }

    return 0;
}
