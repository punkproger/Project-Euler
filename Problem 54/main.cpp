// poker_hands.cpp
#include <array>
#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <optional>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

enum class Suit { Clubs, Diamonds, Hearts, Spades };
enum class Value : int {
    V2 = 2, V3, V4, V5, V6, V7, V8, V9, V10, Jack = 11, Queen = 12, King = 13, Ace = 14
};
enum class CombinationType {
    HighCard,
    OnePair,
    TwoPairs,
    ThreeOfAKind,
    Straight,
    Flush,
    FullHouse,
    FourOfAKind,
    StraightFlush,
    RoyalFlush
};

struct Card {
    Value value;
    Suit suit;
};

struct Combination {
    CombinationType type;
    Value highest; // «старшая карта» внутри найденной комбинации
};

// ---------- Вспомогательные утилиты ----------
inline Value valueFromChar(char c) {
    switch (std::toupper(static_cast<unsigned char>(c))) {
        case '2': return Value::V2;
        case '3': return Value::V3;
        case '4': return Value::V4;
        case '5': return Value::V5;
        case '6': return Value::V6;
        case '7': return Value::V7;
        case '8': return Value::V8;
        case '9': return Value::V9;
        case 'T': return Value::V10;
        case 'J': return Value::Jack;
        case 'Q': return Value::Queen;
        case 'K': return Value::King;
        case 'A': return Value::Ace;
        default: throw std::runtime_error(std::string("Bad value char: ") + c);
    }
}
inline Suit suitFromChar(char c) {
    switch (std::toupper(static_cast<unsigned char>(c))) {
        case 'C': return Suit::Clubs;
        case 'D': return Suit::Diamonds;
        case 'H': return Suit::Hearts;
        case 'S': return Suit::Spades;
        default: throw std::runtime_error(std::string("Bad suit char: ") + c);
    }
}

inline int iv(Value v) { return static_cast<int>(v); }

inline std::string toString(Value v) {
    switch (v) {
        case Value::V2: return "2";
        case Value::V3: return "3";
        case Value::V4: return "4";
        case Value::V5: return "5";
        case Value::V6: return "6";
        case Value::V7: return "7";
        case Value::V8: return "8";
        case Value::V9: return "9";
        case Value::V10: return "T";
        case Value::Jack: return "J";
        case Value::Queen: return "Q";
        case Value::King: return "K";
        case Value::Ace: return "A";
    }
    return "?";
}

inline std::string toString(CombinationType t) {
    switch (t) {
        case CombinationType::HighCard: return "High Card";
        case CombinationType::OnePair: return "One Pair";
        case CombinationType::TwoPairs: return "Two Pairs";
        case CombinationType::ThreeOfAKind: return "Three of a Kind";
        case CombinationType::Straight: return "Straight";
        case CombinationType::Flush: return "Flush";
        case CombinationType::FullHouse: return "Full House";
        case CombinationType::FourOfAKind: return "Four of a Kind";
        case CombinationType::StraightFlush: return "Straight Flush";
        case CombinationType::RoyalFlush: return "Royal Flush";
    }
    return "?";
}

// ---------- Предикаты (каждый возвращает найденную комбинацию или std::nullopt) ----------

using CardArr = std::array<Card, 5>;

// ожидание: карты уже отсортированы по возрастанию value
inline bool isFlush(const CardArr& cs) {
    return cs[0].suit == cs[1].suit && cs[1].suit == cs[2].suit &&
           cs[2].suit == cs[3].suit && cs[3].suit == cs[4].suit;
}

// Возвращает <isStraight, highestValue>. Обрабатывает «колесо» A-2-3-4-5 (highest = 5).
inline std::pair<bool, Value> straightInfo(const CardArr& cs) {
    // соберём уникальные значения (на случай дубликатов — хотя в корректной колоде их нет)
    for (int i = 1; i < 5; ++i) {
        if (iv(cs[i].value) == iv(cs[i-1].value)) {
            return {false, Value::V2}; // дубликат — не стрит
        }
    }
    // обычный стрит
    bool progressive = true;
    for (int i = 1; i < 5; ++i) {
        if (iv(cs[i].value) != iv(cs[i-1].value) + 1) {
            progressive = false; break;
        }
    }
    if (progressive) return {true, cs[4].value};

    // A-2-3-4-5 (колесо): значения после сортировки будут 2,3,4,5,A
    if (cs[0].value == Value::V2 && cs[1].value == Value::V3 &&
        cs[2].value == Value::V4 && cs[3].value == Value::V5 && cs[4].value == Value::Ace) {
        return {true, Value::V5};
    }
    return {false, Value::V2};
}

inline std::unordered_map<int,int> valueCounts(const CardArr& cs) {
    std::unordered_map<int,int> cnt;
    for (const auto& c : cs) ++cnt[iv(c.value)];
    return cnt;
}

inline std::optional<Combination> predRoyalFlush(const CardArr& cs) {
    auto [isS, high] = straightInfo(cs);
    if (isS && isFlush(cs) && high == Value::Ace && iv(cs[0].value) == 10) {
        return Combination{CombinationType::RoyalFlush, Value::Ace};
    }
    return std::nullopt;
}

inline std::optional<Combination> predStraightFlush(const CardArr& cs) {
    auto [isS, high] = straightInfo(cs);
    if (isS && isFlush(cs)) {
        return Combination{CombinationType::StraightFlush, high};
    }
    return std::nullopt;
}

inline std::optional<Combination> predFourOfAKind(const CardArr& cs) {
    auto cnt = valueCounts(cs);
    for (auto& [v, c] : cnt) {
        if (c == 4) return Combination{CombinationType::FourOfAKind, static_cast<Value>(v)};
    }
    return std::nullopt;
}

inline std::optional<Combination> predFullHouse(const CardArr& cs) {
    auto cnt = valueCounts(cs);
    bool has3 = false, has2 = false;
    int v3 = 0, v2 = 0;
    for (auto& [v, c] : cnt) {
        if (c == 3) { has3 = true; v3 = v; }
        else if (c == 2) { has2 = true; v2 = v; }
    }
    if (has3 && has2) {
        return Combination{CombinationType::FullHouse, static_cast<Value>(v3)};
    }
    return std::nullopt;
}

inline std::optional<Combination> predFlush(const CardArr& cs) {
    if (isFlush(cs)) {
        return Combination{CombinationType::Flush, cs[4].value}; // старшая карта флеша
    }
    return std::nullopt;
}

inline std::optional<Combination> predStraight(const CardArr& cs) {
    auto [isS, high] = straightInfo(cs);
    if (isS) return Combination{CombinationType::Straight, high};
    return std::nullopt;
}

inline std::optional<Combination> predThreeOfAKind(const CardArr& cs) {
    auto cnt = valueCounts(cs);
    for (auto& [v, c] : cnt) {
        if (c == 3) return Combination{CombinationType::ThreeOfAKind, static_cast<Value>(v)};
    }
    return std::nullopt;
}

inline std::optional<Combination> predTwoPairs(const CardArr& cs) {
    auto cnt = valueCounts(cs);
    std::vector<int> pairs;
    for (auto& [v, c] : cnt) if (c == 2) pairs.push_back(v);
    if (pairs.size() == 2) {
        int highestPair = std::max(pairs[0], pairs[1]);
        return Combination{CombinationType::TwoPairs, static_cast<Value>(highestPair)};
    }
    return std::nullopt;
}

inline std::optional<Combination> predOnePair(const CardArr& cs) {
    auto cnt = valueCounts(cs);
    for (auto& [v, c] : cnt) if (c == 2)
        return Combination{CombinationType::OnePair, static_cast<Value>(v)};
    return std::nullopt;
}

inline Combination predHighCard(const CardArr& cs) {
    return Combination{CombinationType::HighCard, cs[4].value};
}

// ---------- Класс Hand ----------
using uCombinations = std::vector<Combination>;

class Hand {
public:
    explicit Hand(const std::array<std::string,5>& raw) {
        // 1) Парсинг строк вида "8C", "TS", ...
        for (size_t i = 0; i < 5; ++i) {
            if (raw[i].size() != 2)
                throw std::runtime_error("Bad card token: " + raw[i]);
            cards_[i] = Card{ valueFromChar(raw[i][0]), suitFromChar(raw[i][1]) };
        }
        // 2) Сортировка по значению (возрастание)
        std::sort(cards_.begin(), cards_.end(), [](const Card& a, const Card& b){
            return iv(a.value) < iv(b.value);
        });
        // 3) Вычисление комбинации через набор предикатов
        combination_ = evaluateCombinations(cards_);
    }

    const CardArr& cards() const { return cards_; }
    uCombinations combinations() const { return combination_; }

private:
    static uCombinations evaluateCombinations(const CardArr& sorted) {
		uCombinations combinations;

        if (auto c = predRoyalFlush(sorted))     combinations.push_back(*c);
        if (auto c = predStraightFlush(sorted))  combinations.push_back(*c);
        if (auto c = predFourOfAKind(sorted))    combinations.push_back(*c);
        if (auto c = predFullHouse(sorted))      combinations.push_back(*c);
        if (auto c = predFlush(sorted))          combinations.push_back(*c);
        if (auto c = predStraight(sorted))       combinations.push_back(*c);
        if (auto c = predThreeOfAKind(sorted))   combinations.push_back(*c);
        if (auto c = predTwoPairs(sorted))       combinations.push_back(*c);
        if (auto c = predOnePair(sorted))        combinations.push_back(*c);
		combinations.push_back(predHighCard(sorted));

        return combinations;
    }

    CardArr cards_{};
    uCombinations combination_;
};

// ---------- Чтение файла с руками двух игроков ----------
using HandPair = std::pair<Hand, Hand>;

std::vector<HandPair> readHandsFromFile(const std::string& filepath) {
    std::ifstream in(filepath);
    if (!in) throw std::runtime_error("Cannot open file: " + filepath);

    std::vector<HandPair> result;
    std::string line;
    while (std::getline(in, line)) {
        if (line.empty()) continue;
        std::istringstream iss(line);
        std::vector<std::string> tokens;
        std::string tok;
        while (iss >> tok) tokens.push_back(tok);
        if (tokens.size() != 10) {
            throw std::runtime_error("Line must contain 10 cards: " + line);
        }
        std::array<std::string,5> p1{};
        std::array<std::string,5> p2{};
        for (int i = 0; i < 5; ++i) p1[i] = tokens[i];
        for (int i = 0; i < 5; ++i) p2[i] = tokens[5 + i];
        result.emplace_back(Hand{p1}, Hand{p2});
    }
    return result;
}

enum eResult {
	First_Won,
	Second_Won,
	Tie
};

eResult compareCombinations(const Combination& c1, const Combination& c2)
{
	if (c1.type > c2.type || (c1.type == c2.type && c1.highest > c2.highest))
	{
		return eResult::First_Won;
	}
	else if (c1.type < c2.type || (c1.type == c2.type && c1.highest < c2.highest))
	{
		return eResult::Second_Won;
	}

	return eResult::Tie;
}

eResult compareHands(const Hand& first_hand, const Hand& second_hand)
{
	const auto& c1 = first_hand.combinations();
	const auto& c2 = second_hand.combinations();

	for (int i = 0; i < c1.size() && i < c2.size(); ++i)
	{
		auto result = compareCombinations(c1[0], c2[0]);
		if (result != eResult::Tie)
		{
			return result;
		}
	}

	return eResult::Tie;
}

// ---------- Пример использования ----------
int main() {
    try {
        auto games = readHandsFromFile("0054_poker.txt");
        int idx = 1;
		int first_wins_counter{0};

        for (auto& [h1, h2] : games) {
            // std::cout << "Game " << idx++ << ":" << std::endl;
            const auto& c1 = h1.combinations();
            const auto& c2 = h2.combinations();

            // std::cout << "  P1: " << std::endl;
			// for (const auto& comb : c1) { std::cout << "    * " << toString(comb.type) << " (high " << toString(comb.highest) << ")" << std::endl;  }
            // std::cout << "  P2: " << std::endl;
			// for (const auto& comb : c2) { std::cout << "    * " << toString(comb.type) << " (high " << toString(comb.highest) << ")" << std::endl; }

			auto result = compareHands(h1, h2);

			if (result == eResult::First_Won)
			{
            	// std::cout << "First  won!!!" << std::endl;
				++first_wins_counter;
			}
			else if (result == eResult::Second_Won)
			{
            	// std::cout << "Second won!!!" << std::endl;
			}
			else
			{
            	// std::cout << "Tie!!!" << std::endl;
			}

            // std::cout << "----" << std::endl;
        }

		std::cout << "Final answer: " << first_wins_counter << std::endl;

    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << "\n";
        return 1;
    }


    return 0;
}
