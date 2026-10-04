#pragma once

#include <vector>

#include <engine/Action.hpp>

namespace minesweeper {

/** @brief A move with a model-assigned score or ranking. */
struct ActionCandidate
{
    Action action;
    float score;
};

/** @brief Candidate moves passed to a selection strategy. */
using ActionCandidates = std::vector<ActionCandidate>;

} // namespace minesweeper
