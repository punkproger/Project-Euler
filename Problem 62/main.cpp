#include <iostream>
#include <limits>
#include <unordered_map>

using ull = unsigned long long;


ull getCube(ull val) {
	return val * val * val;
}

ull getSmartHash(ull val) {
	constexpr ull bitsPerDigit{(sizeof(ull) * 8)/10};

	ull digits[10] = {0};
	ull result{0};
	
	do {
		++digits[val%10];
	} while(val/=10);

	for(uint8_t i = 0; i < 10; ++i) {
		result |= (digits[i] << (i * bitsPerDigit));
	}

	return result;
}

int main() {
	ull result{std::numeric_limits<ull>::max()};

	std::unordered_map<ull, uint8_t> hash_to_freq;
	std::unordered_map<ull, ull> hash_to_value;

	for(ull i = 10; i < 10000; ++i) {
		const ull cube{getCube(i)}; 
		const ull hash{getSmartHash(cube)}; 
		
		++hash_to_freq[hash];

		if(hash_to_value.find(hash) == hash_to_value.end()) {
			hash_to_value[hash] = cube;
		}
	}

	for(const auto & hash_and_freq : hash_to_freq) {
		auto value = hash_to_value[hash_and_freq.first];

		if(hash_and_freq.second == 5 && result > value) {
			result = value;
		}
	}

	std::cout << "Result: " << result << std::endl;

	return 0;
}