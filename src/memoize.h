#ifndef MEMOIZE_H_
#define MEMOIZE_H_

#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <tuple>
#include <utility>

/**
 * Specialization of std::hash for tuples.
 *
 * Provides a hash function for arbitrary tuples of hashable types. Probably
 * quite shitty. Hashes each element seperateley, rotates the hash based on the
 * position in the tuple (because std::hash<int> is the identity function) and
 * xors everything.
 *
 */
template <typename... Args>
struct std::hash<std::tuple<Args...>> {
    size_t operator()(std::tuple<Args...> t) const {
        return std::apply(hash_pack, t);
    }

   private:
    /**
     * the shift/rotate offset, based on splitting the bits of the hash among
     * the elements, equally.
     *
     */
    static constexpr int shift = 64 / sizeof...(Args);

    /**
     * Actual hashing logic. Behaves as explained above.
     *
     */
    static size_t hash_pack(Args... a) {
        size_t acc = 0;
        const size_t v[sizeof...(Args)] = {std::hash<Args>()(a)...};
        for (int i = 0; i < sizeof...(Args); i++) {
            acc ^= v[i] ^ (v[i] << ((i + 1) * shift));
        }
        return acc;
    }
};

/**
 * Class for automatic memoization of functions.
 *
 * This class can optimize functions automatically, using a hashmap to store
 * argument-return pairs and only calling the function when the lookup fails.
 * Functions to be memoized must be pure.
 *
 * In order to memoize recursive functions properly, they must be modified
 * slightly. A recursive function should be modified to take a std::function<>
 * with the functions original signature as its first argument, and use that
 * argument for recursion. Otherwise, only the toplevel calls are memoized.
 *
 * Template arguments are the functions return type, followed by the argument
 * types.
 *
 */
template <typename Ret, typename... Args>
class memoize {
   public:
    /**
     * Constructor for top-level memoization.
     * */
    memoize(std::function<Ret(Args...)> func) : f(func){};
    /**
     * Constructor for recursive memoization.
     *
     * Here, the first std::function argument of the passed function is set to
     * the lookup_or_compute method, so that all recursive calls are memoized,
     * too.
     * */
    memoize(std::function<Ret(std::function<Ret(Args...)>, Args...)> func)
        : f([&](Args... a) {
              return func([&](Args... a) { return lookup_or_compute(a...); },
                       a...);
          }){};

    /**
     * To make memoize objects callable.
     * */
    Ret operator()(Args... a) { return lookup_or_compute(a...); }

   private:
    /**
     * Memoization logic
     * */
    Ret lookup_or_compute(Args... a) {
        auto args = std::make_tuple(a...);
        auto cached = cache.find(args);
        if (cached == cache.end()) {
            Ret computed = f(a...);
            cache[args] = computed;
            return computed;
        }
        return cached->second;
    }

    std::function<Ret(Args...)> f;
    std::unordered_map<std::tuple<Args...>, Ret> cache;
};

#endif  // MEMOIZE_H_
