#include "Board.hpp"

namespace core
{

Board::Board(Grid&& grid, ScoredDictionary&& dictionary, duration dur)
    : m_grid(std::move(grid))
    , m_remainingTime(dur)
    , m_dictionary(std::move(dictionary))
{}

Board::~Board() = default;

Board::Board(Board&&) noexcept = default;
Board& Board::operator=(Board&&) noexcept = default;


}