#pragma once

#include <utility>
#include <vector>

#include <ai/decision/IActionInterpreter.hpp>

namespace minesweeper {

/**
 * @brief Interpreter for the "fixed actions per cell" output format.
 *
 * The model emits one score for every `(cell, action)` pair. For a
 * `width * height` board and `N = actions_coding.size()`, `scores` must
 * contain `width * height * N` values.
 *
 * Scores are grouped in row-major order. `ModelOutput::score_at()` converts
 * a position and action index into the matching score. `actions_coding`
 * defines which move kind each action index represents, so its order can
 * deliberately match the model output.
 */
class ActionsPerCell : public IActionInterpreter {
public:
    /**
     * @brief Sets the action-kind order in each model-score block.
     * @throws std::invalid_argument If no actions are provided.
     */
    ActionsPerCell(std::vector<ActionCode> actions_coding);

    /**
     * @throws std::runtime_error If the output shape does not match this
     * interpreter's action configuration.
     */
    ActionCandidates interpret(const ModelOutput& output) const;
private:
    std::vector<ActionCode> _actions_coding;
};

} // namespace minesweeper
