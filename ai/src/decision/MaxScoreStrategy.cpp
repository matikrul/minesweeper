#include <stdexcept>

#include <ai/decision/MaxScoreStrategy.hpp>

namespace minesweeper {

Action MaxScoreStrategy::select(const ActionCandidates& candidates) const
{
    if (candidates.empty())
        throw std::runtime_error("No candidates available");

    const auto max_it = std::max_element(candidates.begin(), candidates.end(),
        [](const auto& a, const auto& b) { return a.score < b.score; });

    return max_it->action;
}

} // namespace minesweeper