#pragma once

#include <ai/decision/IActionSelectionStrategy.hpp>

namespace minesweeper {

/**
 * @brief Selects the candidate with the highest model score.
 *
 * On a tie, keeps the first candidate in interpreter order, making the
 * decision deterministic.
 */
class MaxScoreStrategy : public IActionSelectionStrategy {
public:
    /** @throws std::runtime_error If the candidate list is empty. */
    Action select(const ActionCandidates& candidates) const;
};

} // namespace minesweeper
