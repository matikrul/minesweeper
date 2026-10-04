#include <stdexcept>

#include <ai/decision/ActionsPerCell.hpp>

namespace minesweeper {

ActionsPerCell::ActionsPerCell(std::vector<ActionCode> actions_coding) : _actions_coding(std::move(actions_coding))
{
    if (_actions_coding.empty())
        throw std::invalid_argument("At least one action code is required");
}

ActionCandidates ActionsPerCell::interpret(const ModelOutput& output) const
{
    ActionCandidates results;

    const auto actions_per_cell = static_cast<int>(_actions_coding.size());
    if (output.actions_per_cell != actions_per_cell ||
        output.scores.size() != static_cast<std::size_t>(output.board_width) *
                                  static_cast<std::size_t>(output.board_height) *
                                  _actions_coding.size())
        throw std::runtime_error("Invalid output size");

    for (int row = 0; row < output.board_height; ++row)
    {
        for (int column = 0; column < output.board_width; ++column)
        {
            const Position position{row, column};

            for (int action_index = 0; action_index < actions_per_cell; ++action_index)
            {
                const auto action_code = _actions_coding[static_cast<std::size_t>(action_index)];
                const auto score = output.score_at(position, action_index);
                switch(action_code)
                {
                    case ActionCode::reveal:
                        results.push_back(ActionCandidate{RevealAction(position), score});
                        break;
                    case ActionCode::flag:
                        results.push_back(ActionCandidate{ToggleFlagAction(position), score});
                        break;
                    case ActionCode::reveal_neighbors:
                        results.push_back(ActionCandidate{RevealNeighborsAction(position), score});
                        break;
                    default:
                        throw std::runtime_error("Unsupported action code");
                }
            }
        }
    }
    return results;
}

} // namespace minesweeper
