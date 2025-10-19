#include <iostream>
#include <vector>
#include <string.h>
#include <cmath>
#include <set>
#include <numeric>

using namespace std;

using ull = unsigned long long;

namespace {
    void dfs(ull k, ull start, ull prod, ull sum, ull terms, ull& best) {
        // попытка «зафиксировать» текущий набор факторов
        if (prod >= sum) {
            ull ones = prod - sum;
            ull k_now = terms + ones;
            if (k_now == k) {
                if (prod < best) best = prod;
                // даже если совпало, можно не углубляться, т.к. больше факторов увеличат prod
                // но оставим возврат — всё равно ограничивает best
            }
            if (k_now > k) {
                // добавление новых множителей только увеличит terms и prod => k_now не уменьшится
                return;
            }
        } else {
            // sum > prod: нужно набрать ещё хотя бы один множитель, чтобы prod рос быстрее
            // но ограничим по best ниже
        }

        // перебор следующего множителя в неубывающем порядке
        for (ull f = start; ; ++f) {
            // прунинг по переполнению и по текущему лучшему
            if (prod > 0 && f > best / prod) break; // prod*f бы превысил best
            ull nprod = prod * f;
            ull nsum  = sum + f;
            ull nterms = terms + 1;

            // если уже хуже текущего лучшего — нет смысла углубляться
            if (nprod >= best) break;

            dfs(k, f, nprod, nsum, nterms, best);
        }
    }
}

// Минимальное product-sum число для заданного k (k >= 2).
ull find_mps(ull k) {
    // Хорошая верхняя граница известна: N <= 2k
    ull best = 2 * k;
    dfs(k, /*start*/2, /*prod*/1, /*sum*/0, /*terms*/0, best);
    return best;
}

int main() {
    std::set<ull> answers;

    for (ull k = 2; k <= 12000; ++k)
    {
        answers.insert(find_mps(k));
    }

	std::cout << std::reduce(answers.begin(), answers.end()) << std::endl;

	return 0;
}