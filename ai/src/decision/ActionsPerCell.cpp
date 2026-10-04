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

    if (output.scores.size() != output.board_width * output.board_height * _actions_coding.size())
        throw std::runtime_error("Invalid output size");

    const auto actions_per_cell = _actions_coding.size();

    for (std::size_t i = 0; i < output.scores.size(); ++i)
    {
        const auto cell_index = i / actions_per_cell;
        const auto action_index = i % actions_per_cell;

        const auto row = cell_index / output.board_width;
        const auto column = cell_index % output.board_width;

        const Position position{static_cast<int>(row), static_cast<int>(column)};

        const auto action_code = _actions_coding[action_index];
        switch(action_code)
        {
            case ActionCode::reveal:
                results.push_back(ActionCandidate{RevealAction(position), output.scores[i]});
                break;
            case ActionCode::flag:
                results.push_back(ActionCandidate{ToggleFlagAction(position), output.scores[i]});
                break;
            case ActionCode::reveal_neighbors:
                results.push_back(ActionCandidate{RevealNeighborsAction(position), output.scores[i]});
                break;
            default:
                throw std::runtime_error("Unsupported action code");
        }
    }
    return results;
}

} // namespace minesweeper