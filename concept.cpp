#include <concepts>
#include <type_traits>
#include <utility>

template<typename T>
concept Arithmetic = std::integral<T> || std::floating_point<T>;

auto add(Arithmetic auto ... nums)
{
    return std::make_pair{0 + ... + nums, 1 * ... * nums};
}

