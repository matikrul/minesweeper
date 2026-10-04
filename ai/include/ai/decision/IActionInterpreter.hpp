#pragma once

#include <ai/decision/ActionCandidate.hpp>
#include <ai/decision/ModelOutput.hpp>

namespace minesweeper {

class IActionInterpreter
{
public:
    virtual ~IActionInterpreter() = default;

    virtual ActionCandidates interpret(const ModelOutput& output) const = 0;
};

} // namespace minesweeper
