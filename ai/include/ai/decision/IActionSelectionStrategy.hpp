#pragma once

#include <ai/decision/ActionCandidate.hpp>
#include <engine/Action.hpp>

namespace minesweeper {

/**
 * @brief Interface for choosing one move from candidates.
 *
 * Separates model-output interpretation from selection rules, such as highest
 * score, random selection, or future filtering of illegal moves.
 */
class IActionSelectionStrategy
{
public:
    virtual ~IActionSelectionStrategy() = default;

    /** @brief Selects one move from scored candidates. */
    virtual Action select(const ActionCandidates& candidates) const = 0;
};

} // namespace minesweeper
