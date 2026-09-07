#pragma once

#include <vector>

#include <engine/Action.hpp>

namespace minesweeper {

struct ActionCandidate
{
    Action action;
    float score;
};

using ActionCandidates = std::vector<ActionCandidate>;

} // namespace minesweeper