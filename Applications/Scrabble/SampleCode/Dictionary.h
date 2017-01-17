#ifndef DICTIONARY_H_
#define DICTIONARY_H_

#include <set>
#include <string>
#include <unordered_set>

class Dictionary {
public:
  Dictionary() {}

  // Construct the dictionary from words in a file.
  bool readFile(const std::string& dictionaryFileName);

  // Return true if the word is in the dictionary.
  bool isDictionaryWord(const std::string& word) const;

  // Return true if the prefix is a prefix of a word in the dictionary.
  bool isDictionaryPrefix(const std::string& prefix) const;

  // Return number of words in the dictionary.
  int size() const { return words_.size(); }

private:
  // Use hashed sets for faster lookup.
  std::unordered_set<std::string> words_;

  std::unordered_set<std::string> prefixes_;
};

#endif // DICTIONARY_H_
