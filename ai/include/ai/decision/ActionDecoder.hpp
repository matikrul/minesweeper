#pragma once

#include <memory>

#include <ai/decision/ActionInterpreter.hpp>
#include <ai/decision/ActionSelectionStrategy.hpp>

namespace minesweeper {

class ActionDecoder
{
public:
    ActionDecoder(std::unique_ptr<ActionInterpreter> interpreter,
                  std::unique_ptr<ActionSelectionStrategy> strategy) :
                  _interpreter(std::move(interpreter)), _strategy(std::move(strategy)) {}

    Action decode(const ModelOutput& output) const;

private:
    std::unique_ptr<ActionInterpreter> _interpreter;
    std::unique_ptr<ActionSelectionStrategy> _strategy;
};

}