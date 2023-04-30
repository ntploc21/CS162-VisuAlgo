#include "StaticArray.hpp"

#include <algorithm>
#include <cstring>
#include <iomanip>

#include "Global.hpp"
#include "StateStack.hpp"

Algorithm::StaticArray::StaticArray() {}

Algorithm::StaticArray::StaticArray(
    GUI::CodeHighlighter::Ptr codeHighlighter,
    DArrayAnimationController::Ptr animController, FontHolder* fonts)
    : Algorithm::Algorithm(codeHighlighter, animController, fonts) {
    Random();
}

Algorithm::StaticArray::~StaticArray() {}

void Algorithm::StaticArray::Update(int index, int value) {
    InitAction({"arr[i] = v;"});

    /* Animation goes here */
    auto& node = visualizer.GetList().at(index);
    node.AnimationOnNode(true);
    node.SetNodeState(GUI::Node::State::Active);

    DArrayAnimation anim = GenerateAnimation(
        1, 0, "Update node i's value to " + std::to_string(value));

    anim.SetAnimation([this, index, value](GUI::DynamicArray srcDS,
                                           float playingAt, Vector2 base) {
        GUI::Node& node = srcDS.GetList().at(index);
        if (playingAt >= 0.85f) node.SetValue(value);
        srcDS.Draw(base, std::min(1.0f, playingAt * (1.00f / 0.75f)));
        return srcDS;
    });
    animController->AddAnimation(anim);

    node.AnimationOnNode(false);
    node.SetNodeState(GUI::Node::State::Default);
    node.SetValue(value);
}

void Algorithm::StaticArray::Access(int index) {
    InitAction({"return arr[i];"});

    DArrayAnimation anim =
        GenerateAnimation(0.75, 0,
                          "The current Linked List is empty, the head we "
                          "return will be NULL.");
    if (visualizer.GetLength() > index) {
        visualizer[index].AnimationOnNode(true);
        visualizer[index].SetNodeState(GUI::Node::State::Active);
        anim = GenerateAnimation(0.75, 0,
                                 "Return the value stored at the head: " +
                                     std::to_string(visualizer[0].GetValue()) +
                                     ".");
        visualizer[index].SetNodeState(GUI::Node::State::Default);
        visualizer[index].AnimationOnNode(false);
    }
    animController->AddAnimation(anim);
}

void Algorithm::StaticArray::Search(int value) {
    InitAction({"for(int i=0;i<N;i++) {", "	if(arr[i] == v) return i;", "}",
                "return -1; // no element found"});

    /* Animation goes here */
    auto& nodes = visualizer.GetList();
    bool foundElement = false;
    for (int k = 0; k < nodes.size() && !foundElement; k++) {
        int curValue = nodes[k].GetValue();
        {  // Line 1
            DArrayAnimation animLoopFor = GenerateAnimation(
                0.75, 0, "Increment k, index specified has not been reached.");
            if (k == 0)
                animLoopFor.SetActionDescription(
                    "Enter the loop.\nk is now: 0");
            else
                nodes[k - 1].AnimationOnNode(false);
            animController->AddAnimation(animLoopFor);
        }

        {  // Line 2
            nodes[k].SetNodeState(GUI::Node::Active);
            nodes[k].SetLabel(std::to_string(k));
            nodes[k].AnimationOnNode(true);

            DArrayAnimation animLoop1 = GenerateAnimation(
                0.75, 1,
                "arr[" + std::to_string(k) + "] = " + std::to_string(curValue) +
                    " is not equal to " + std::to_string(value) +
                    ", we move to the next iteration.");

            if (curValue == value) {
                foundElement = true;
                nodes[k].SetNodeState(GUI::Node::ActiveGreen);
                animLoop1 = GenerateAnimation(
                    0.75, 1,
                    "arr[" + std::to_string(k) +
                        "] = " + std::to_string(curValue) + " = " +
                        std::to_string(value) + ", we have found the answer!");
            }

            animController->AddAnimation(animLoop1);

            nodes[k].SetNodeState(GUI::Node::Iterated);
            nodes[k].ClearLabel();
        }
    }
    if (!foundElement) {
        nodes.back().AnimationOnNode(false);
        DArrayAnimation animNotFound =
            GenerateAnimation(0.75, 3, "No element found!");
        animController->AddAnimation(animNotFound);
    }
    ResetVisualizer();
}

void Algorithm::StaticArray::ApplyInput(std::vector< int > input,
                                        std::size_t nMaxSize) {
    if (input.size() > nMaxSize) input.resize(nMaxSize);
    InitAction({});

    codeHighlighter->SetShowCode(false);
    codeHighlighter->SetShowAction(false);

    visualizer.Import(input);
    for (int i = visualizer.GetLength(); i < visualizer.GetCapacity(); i++) {
        visualizer.GetList().at(i).SetNodeState(GUI::Node::State::Hide);
    }

    float sizeX = 40 * visualizer.GetLength() +
                  visualizer.mNodeDistance * (visualizer.GetLength() - 1);

    visualizer.SetPosition((global::SCREEN_WIDTH - sizeX) / 2, 150);

    DArrayAnimation state;
    state.SetDuration(0.5);
    state.SetHighlightLine(-1);
    state.SetSourceDataStructure(visualizer);
    state.SetAnimation([this](GUI::DynamicArray srcDS, float playingAt,
                              Vector2 base) {
        auto& nodes = srcDS.GetList();
        for (GUI::Node& node : nodes) {
            node.SetRadius(AnimationFactory::ElasticOut(playingAt) * 20);
            node.SetValueFontSize(AnimationFactory::ElasticOut(playingAt) * 24);
            node.SetLabelFontSize(AnimationFactory::ElasticOut(playingAt) * 20);
        }
        srcDS.Draw(base, playingAt, true);
        return srcDS;
    });
    animController->AddAnimation(state);
    animController->Reset();
    animController->InteractionLock();
}

void Algorithm::StaticArray::ResetVisualizer() {
    auto& nodes = visualizer.GetList();
    for (GUI::Node& node : nodes) {
        node.AnimationOnNode(false);
        node.SetNodeState(GUI::Node::Default);
    }
}