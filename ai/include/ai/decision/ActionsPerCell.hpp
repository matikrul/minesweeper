#pragma once

#include <utility>
#include <vector>

#include <ai/decision/IActionInterpreter.hpp>

namespace minesweeper {

class ActionsPerCell : public IActionInterpreter {
public:
    ActionsPerCell(std::vector<ActionCode> actions_coding);

    ActionCandidates interpret(const ModelOutput& output) const;
private:
    std::vector<ActionCode> _actions_coding;
};

} // namespace minesweeper
