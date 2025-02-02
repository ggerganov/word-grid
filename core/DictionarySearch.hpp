#pragma once

#include "Word.hpp"

#include <vector>

namespace core
{

class DictionarySearch
{
public:
    const Word& word() const { return m_word; }

    struct Range
    {
        std::vector<Word>::const_iterator begin;
        std::vector<Word>::const_iterator end;
    };

    const chobo::static_vector<Range, WordTraits::Max_Length>& ranges() const { return m_ranges; }

    size_t length() const { return m_word.length(); }
    void pop()
    {
        m_word.pop_back();
        m_ranges.pop_back();
    }
private:
    friend class Dictionary;
    Word m_word;

    // ranges for each letter of word
    chobo::static_vector<Range, WordTraits::Max_Length> m_ranges;
};

}