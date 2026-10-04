#pragma once

#include <memory>

#include <ai/decision/IActionInterpreter.hpp>
#include <ai/decision/IActionSelectionStrategy.hpp>

namespace minesweeper {

/**
 * @brief Combines model-output interpretation with move selection.
 *
 * The flow is always: `ModelOutput` -> `IActionInterpreter` ->
 * `ActionCandidates` -> `IActionSelectionStrategy` -> `Action`.
 */
class ActionDecoder
{
public:
    /** @brief Takes ownership of an output interpreter and selection strategy. */
    ActionDecoder(std::unique_ptr<IActionInterpreter> interpreter,
                  std::unique_ptr<IActionSelectionStrategy> strategy) :
                  _interpreter(std::move(interpreter)), _strategy(std::move(strategy)) {}

    /** @brief Decodes raw model output into one engine move. */
    Action decode(const ModelOutput& output) const;

private:
    std::unique_ptr<IActionInterpreter> _interpreter;
    std::unique_ptr<IActionSelectionStrategy> _strategy;
};

}
