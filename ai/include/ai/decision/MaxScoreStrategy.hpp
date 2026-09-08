#pragma once

#include <ai/decision/ActionSelectionStrategy.hpp>

namespace minesweeper {

class MaxScoreStrategy : public ActionSelectionStrategy {
public:
    Action select(const ActionCandidates& candidates) const;
};

} // namespace minesweeper