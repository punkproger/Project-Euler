#include <iostream>
#include <vector>
#include <unordered_set>
#include <cmath>
#include <cstring>
#include <array>
#include <numeric>
#include <limits>

using ull = unsigned long long;

std::unordered_set<ull> primes_set;
ull biggest_prime;
constexpr ull c_default_best{999999999};

constexpr std::size_t c_size{5};

bool isPrime(ull num)
{
    if (num < 2) return false;
    if (num % 2 == 0 && num != 2) return false;
    if (num % 5 == 0) return false;
    if (num % 10 == 0) return false;
    // проверяем только по заранее подготовленному множеству (будь аккуратен: для больших чисел оно может не содержать значения)
    return primes_set.count(num) != 0;
}

std::vector<ull> get_primes(ull max){ // from: http://code.activestate.com/recipes/576559-fast-prime-generator/
    std::vector<ull> primes;
    char *sieve = new char[max/8+1];
    // Fill sieve with 1
    std::memset(sieve, 0xFF, (max/8+1) * sizeof(char));
    for(ull x = 2; x <= max; x++)
        if(sieve[x/8] & (0x01 << (x % 8))){
            primes.push_back(x);
            primes_set.insert(x);
            // Is prime. Mark multiples.
            for(ull j = 2*x; j <= max; j += x)
                sieve[j/8] &= ~(0x01 << (j % 8));
        }
    delete[] sieve;
    return primes;
}

/* ====== utils: digits, pow10, safe concat, Miller–Rabin 64-bit ====== */
static inline int digits10(ull x){
    if (x==0) return 1;
    int d=0; while(x){ x/=10; ++d; } return d;
}
static inline ull pow10_u(int d){
    static const ull p10[20] = {
        1ULL,10ULL,100ULL,1000ULL,10000ULL,100000ULL,1000000ULL,10000000ULL,100000000ULL,1000000000ULL,
        10000000000ULL,100000000000ULL,1000000000000ULL,10000000000000ULL,100000000000000ULL,
        1000000000000000ULL,10000000000000000ULL,100000000000000000ULL,1000000000000000000ULL,0ULL
    };
    return p10[d];
}
// out = concat(a,b) = a * 10^{digits(b)} + b; false -> overflow
static inline bool concat2(ull a, ull b, ull& out){
    int d = digits10(b);
    ull p = pow10_u(d);
    if (p!=0 && a > std::numeric_limits<ull>::max()/p) return false;
    ull t = a*p;
    if (t > std::numeric_limits<ull>::max() - b) return false;
    out = t + b;
    return true;
}

static inline ull mul_mod_u128(ull a, ull b, ull m){
#if defined(__SIZEOF_INT128__)
    __uint128_t z = ( __uint128_t)a * b;
    return (ull)(z % m);
#else
    // fallback без __int128
    ull res = 0;
    while (b){
        if (b & 1) res = (res >= m - a) ? (res + a - m) : (res + a);
        b >>= 1;
        a = (a >= m - a) ? (a + a - m) : (a + a);
    }
    return res;
#endif
}
static inline ull pow_mod(ull a, ull e, ull m){
    ull r = 1 % m;
    while(e){
        if (e & 1) r = mul_mod_u128(r,a,m);
        a = mul_mod_u128(a,a,m);
        e >>= 1;
    }
    return r;
}
static bool isPrime64(ull n){
    if (n < 2) return false;
    // быстрые делители
    for (ull p: {2ULL,3ULL,5ULL,7ULL,11ULL,13ULL,17ULL,19ULL,23ULL,29ULL,31ULL,37ULL}){
        if (n == p) return true;
        if (n % p == 0) return n == p;
    }
    ull d = n - 1, s = 0;
    while ((d & 1) == 0) { d >>= 1; ++s; }
    auto check = [&](ull a)->bool{
        if (a % n == 0) return true;
        ull x = pow_mod(a, d, n);
        if (x == 1 || x == n-1) return true;
        for (ull i=1;i<s;++i){
            x = mul_mod_u128(x,x,n);
            if (x == n-1) return true;
        }
        return false;
    };
    // детерминированные основания для 64-bit
    for (ull a: {2ULL,3ULL,5ULL,7ULL,11ULL,13ULL,17ULL})
        if (!check(a)) return false;
    return true;
}
/* ====== end utils ====== */

bool concat_check(ull v1, ull v2)
{
	ull ab, ba;
	concat2(v1, v2, ab);
	concat2(v2, v1, ba);
	// a||b
	if ((ab <= biggest_prime && !isPrime(ab)) || !isPrime64(ab))
	{
		// std::cout << "!isPrime(ab)" << " : " << ab << std::endl;
		return false; // надёжнее, чем искать в primes_set
	}
	// b||a
	if ((ba <= biggest_prime && !isPrime(ba)) || !isPrime64(ba))
	{
		// std::cout << "!isPrime(ba)" << " : " << ba << std::endl;
		return false;
	}

	return true;
}

// Главная функция: все пары (i≠j) дают простое при конкатенации в обоих порядках
int all_pairs_concat_prime(const std::array<ull, c_size>& v, ull curr){
	/*for (int i = 0; i < v.size(); ++i)
	{
		if (v[i])
	}*/

    const int n = static_cast<int>(v.size());
    for (int i=0;i<n;++i){
        for (int j=i+1;j<n;++j){
            if (!concat_check(v[i], v[j]))
			{
				if (i < curr && j < curr)
				{
					return -1;
				}
				else
				{
					// std::cout << curr << " " << i << " " << j << std::endl;
					return 0;
				}
			}
        }
    }
    return 1;
}

std::array<ull, c_size> gen_array(const std::array<ull, c_size>& prime_idxs, const std::vector<ull>& primes)
{
    std::array<ull, c_size> primes_arr{};
    for (std::size_t i = 0; i < primes_arr.size(); ++i)
    {
        primes_arr[i] = primes[prime_idxs[i]]; // индексируем ВЕКТОР квадратными скобками
    }
    return primes_arr; // NRVO
}

void dfs(std::array<ull, c_size> prime_idxs, std::size_t curr, const std::vector<ull>& primes, ull& best)
{
	if (best != c_default_best)
	{
		return;
	}
    // генерим текущий набор простых по индексам
    auto primes_arr = gen_array(prime_idxs, primes);

    ull sum = std::accumulate(primes_arr.begin(), primes_arr.end(), 0ULL);
	if (sum > best)
	{
		return;
	}

	/*std::cout << "Array:";
	for (auto v : primes_arr)
	{
		std::cout << " " << v;
	}
	std::cout << ", Best: " << best << std::endl;*/

    // если текущий набор "не склеивается" в простые при конкатенации — можно прунинг
	int res = all_pairs_concat_prime(primes_arr, curr);
    if (res == -1) {
		return;
    } else if (res == 1) {
        if (sum < best) 
		{
			best = sum;
			std::cout << "Array:";
			for (auto v : primes_arr)
			{
				std::cout << " " << v;
			}
			std::cout << ", Best: " << best << std::endl;
			std::cout << best << std::endl;
		}
    }

	// Переходим к следующей позиции
    if (curr + 1 < c_size)
    {
        dfs(prime_idxs, curr + 1, primes, best);
    }

    // Пытаемся сдвигать текущий индекс вперёд (неубывающие индексы)
    if ((curr == 0 || prime_idxs[curr] + 1 <= prime_idxs[curr-1]) &&
        prime_idxs[curr] + 1 < primes.size())
    {
        auto prime_idxs_copy = prime_idxs;
        prime_idxs_copy[curr]++;
        dfs(std::move(prime_idxs_copy), curr, primes, best);
    }
}

ull checkAllPrimePairSets(const std::vector<ull>& primes)
{
    ull best{c_default_best};

    std::array<ull, c_size> prime_idxs{};
    prime_idxs.fill(0);

    dfs(prime_idxs, 0, primes, best);

    return best;
}

int main() {
    constexpr ull limit{10000};
    auto primes = get_primes(limit);
	biggest_prime = primes.back();
	//std::cout << primes.size() << std::endl;

    //std::cout << all_pairs_concat_prime(std::array<ull, c_size>({3, 7, 109, 673})) << std::endl;
    std::cout << checkAllPrimePairSets(primes) << std::endl;

    return 0;
}
