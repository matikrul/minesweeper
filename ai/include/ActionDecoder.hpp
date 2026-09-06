#pragma once

#include <memory>
#include <vector>
#include <cstddef>

#include <Action.hpp>

namespace minesweeper {

using ModelOutput = std::vector<float>;

struct ActionCandidate
{
    Action action;
    float score;
};

using ActionCandidates = std::vector<ActionCandidate>;

class ActionInterpreter
{
public:
    virtual ~ActionInterpreter() = default;

    virtual ActionCandidates interpret(const ModelOutput& output) const = 0;
};

class ActionSelectionStrategy
{
public:
    virtual ~ActionSelectionStrategy() = default;

    virtual Action select(const ActionCandidates& candidates) const = 0;
};

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