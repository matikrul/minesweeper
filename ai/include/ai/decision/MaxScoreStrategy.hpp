#pragma once

#include <ai/decision/IActionSelectionStrategy.hpp>

namespace minesweeper {

class MaxScoreStrategy : public IActionSelectionStrategy {
public:
    Action select(const ActionCandidates& candidates) const;
};

} // namespace minesweeper
