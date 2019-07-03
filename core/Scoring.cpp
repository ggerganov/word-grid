#include "Scoring.hpp"
#include "Grid.hpp"

namespace core
{

Scoring::Scoring() = default;
Scoring::~Scoring() = default;

void Scoring::setFlat(score_t flatScore)
{
    m_type = Type::Flat;
    m_flatScore = flatScore;
}

void Scoring::setLength(float lengthMultiplier)
{
    m_type = Type::Length;
    m_lengthMultiplier = lengthMultiplier;
}

namespace
{
struct GridCoordView
{
    GridCoordView(const Grid& g, chobo::const_memory_view<GridCoord>& c)
        : grid(g), coords(c)
    {}

    size_t size() const
    {
        return coords.size();
    }

    const WordElement& at(size_t i) const
    {
        return grid.at(coords[i]);
    }

    const Grid& grid;
    chobo::const_memory_view<GridCoord> coords;
};

struct WordElementView
{
    WordElementView(const chobo::const_memory_view<WordElement>& w)
        : word(w)
    {}

    size_t size() const
    {
        return word.size();
    }

    const WordElement& at(size_t i) const
    {
        return word.at(i);
    }

    chobo::const_memory_view<WordElement> word;
};
}

score_t Scoring::score(const Grid& grid, chobo::const_memory_view<GridCoord> coords) const
{
    return scoreDispatch(GridCoordView(grid, coords));
}

score_t Scoring::score(chobo::const_memory_view<WordElement> word) const
{
    return scoreDispatch(WordElementView(word));
}

template <typename WordView>
score_t Scoring::scoreDispatch(const WordView& wv) const
{
    switch (m_type)
    {
        case Type::Flat: return m_flatScore;
        case Type::Length: return scoreLength(wv);
        default:
            assert(false);
            return 0;
    }
}

template <typename WordView>
score_t Scoring::scoreLength(const WordView& view) const
{
    // find actual letter legnth
    size_t length = 0;
    for (size_t i = 0; i < view.size(); ++i)
    {
        length += view.at(i).matchLength();
    }
    return score_t(m_lengthMultiplier * length);
}

}
