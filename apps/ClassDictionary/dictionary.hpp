#ifndef DICTIONARY.HPP
#define DICTIONARY.HPP

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>


template <typename K, typename V>
class Dictionary {
	private:
		struct Entry {
			K key;
			V value;
			Entry(const K& k, const V& v) : key(k), value(v) {}
		};
		std::vector<Entry> entries;
		typename std::vector<Entry>::iterator findEntry(const K& key) {
			return std::find_if(entries.begin(), entries.end(),
				[&key](const Entry& entry) { return entry.key == key; });
		}
public:
	Dictionary() = default;
		void insert(const K& key, const V& value) {
			auto it = findEntry(key);
			if (it != entries.end()) {
				it->value = value; // Update existing value
			} else {
				entries.emplace_back(key, value); // Add new entry
			}
		}
		V& at(const K& key) {
			auto it = findEntry(key);
			if (it != entries.end()) {
				return it->value;
			} else {
				throw std::out_of_range("Key not found");
			}
		}
		V& operator[](const K& key) {
			auto it = findEntry(key);
			if (it != entries.end()) {
				return it->value;
			} else {
				entries.emplace_back(key, V());
				return entries.back().value;
			}
		}
		size_t size() const {
			return entries.size();
		}
		bool empty() const {
			return entries.empty();
		}
};


#endif // !DICTIONARY.HPP



