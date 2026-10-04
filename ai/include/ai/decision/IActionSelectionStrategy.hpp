#pragma once

#include <ai/decision/ActionCandidate.hpp>
#include <engine/Action.hpp>

namespace minesweeper {

class IActionSelectionStrategy
{
public:
    virtual ~IActionSelectionStrategy() = default;

    virtual Action select(const ActionCandidates& candidates) const = 0;
};

} // namespace minesweeper
