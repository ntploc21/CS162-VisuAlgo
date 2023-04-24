#include "StaticArray.hpp"

#include <algorithm>
#include <cstring>
#include <iomanip>

#include "StateStack.hpp"

Algorithm::StaticArray::StaticArray() {}

Algorithm::StaticArray::StaticArray(GUI::CodeHighlighter::Ptr codeHighlighter,
                                    SLLAnimationController::Ptr animController,
                                    FontHolder* fonts)
    : Algorithm::Algorithm(codeHighlighter, animController, fonts) {
    visualizer.SetDefaultArrowType(ArrowType::Hidden);
    visualizer.SetShowHeadAndTail(false);
    visualizer.SetShape(defaultShape);
    Random();
}

Algorithm::StaticArray::~StaticArray() {}

void Algorithm::StaticArray::Update(int index, int value) {
    InitAction({"arr[i] = v;"});

    /* Animation goes here */
    auto& node = visualizer.GetList().at(index);
    node.AnimationOnNode(true);
    node.SetNodeState(GUI::Node::State::Active);

    SLLAnimation anim = GenerateAnimation(
        1, 0, "Update node i's value to " + std::to_string(value));

    anim.SetAnimation([this, index, value](GUI::SinglyLinkedList srcDS,
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

void Algorithm::StaticArray::Search(int value) {
    InitAction({"for(int i=0;i<N;i++) {", "	if(arr[i] == v) return i;", "}",
                "return -1; // no element found"});

    /* Animation goes here */
    auto& nodes = visualizer.GetList();
    bool foundElement = false;
    for (int k = 0; k < nodes.size() && !foundElement; k++) {
        int curValue = nodes[k].GetValue();
        {  // Line 1
            SLLAnimation animLoopFor = GenerateAnimation(
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

            SLLAnimation animLoop1 = GenerateAnimation(
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
        SLLAnimation animNotFound =
            GenerateAnimation(0.75, 3, "No element found!");
        animController->AddAnimation(animNotFound);
    }
    ResetVisualizer();
}

void Algorithm::StaticArray::ResetVisualizer() {
    auto& nodes = visualizer.GetList();
    for (GUI::Node& node : nodes) {
        node.AnimationOnNode(false);
        node.SetNodeState(GUI::Node::Default);
    }
}