#pragma once

#include <ai/decision/ActionCandidate.hpp>
#include <ai/decision/ModelOutput.hpp>

namespace minesweeper {

class ActionInterpreter
{
public:
    virtual ~ActionInterpreter() = default;

    virtual ActionCandidates interpret(const ModelOutput& output) const = 0;
};

} // namespace minesweeper