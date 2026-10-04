#pragma once

#include <memory>

#include <ai/decision/IActionInterpreter.hpp>
#include <ai/decision/IActionSelectionStrategy.hpp>

namespace minesweeper {

class ActionDecoder
{
public:
    ActionDecoder(std::unique_ptr<IActionInterpreter> interpreter,
                  std::unique_ptr<IActionSelectionStrategy> strategy) :
                  _interpreter(std::move(interpreter)), _strategy(std::move(strategy)) {}

    Action decode(const ModelOutput& output) const;

private:
    std::unique_ptr<IActionInterpreter> _interpreter;
    std::unique_ptr<IActionSelectionStrategy> _strategy;
};

}
