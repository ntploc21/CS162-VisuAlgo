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

std::size_t Algorithm::StaticArray::size() const {
    return visualizer.GetLength();
}

void Algorithm::StaticArray::Insert(int index, int value) {
    InitAction({"if(arr[length - 1] != 0) return;",
                "for(int k=length;k>i;k--) arr[k] = arr[k-1];", "arr[i] = v;"});

    std::size_t currentSize = visualizer.GetLength() - 1;
    if (visualizer[currentSize].GetValue() != 0) {
        visualizer[currentSize].SetNodeState(GUI::Node::State::ActiveRed);
        visualizer[currentSize].AnimationOnNode(true);
        DArrayAnimation animFull = GenerateAnimation(
            0.75, 0,
            "The current array is full, we cannot insert any more node.");
        animController->AddAnimation(animFull);
        ResetVisualizer();
        return;
    }

    visualizer[currentSize].SetNodeState(GUI::Node::State::Active);
    visualizer[currentSize].AnimationOnNode(true);
    DArrayAnimation animContinue = GenerateAnimation(
        0.75, 0,
        "The current array is not full, we will proceed to the next step.");
    animController->AddAnimation(animContinue);
    visualizer[currentSize].AnimationOnNode(false);

    {  // Line 2
        for (int i = currentSize; i > index; i--) {
            auto& node_prev = visualizer.GetList()[i - 1];
            node_prev.SetReachable(true);
            node_prev.AnimationOnNode(true);
            node_prev.SetNodeState(GUI::Node::State::ActiveBlue);

            DArrayAnimation animMove1 = GenerateAnimation(
                0.5, 1, "Copy node (k - 1)'s value to node k's value.");
            animController->AddAnimation(animMove1);

            node_prev.AnimationOnNode(false);
            auto& node = visualizer.GetList()[i];
            node.SetReachable(true);
            node.AnimationOnNode(true);
            node.SetNodeState(GUI::Node::State::Active);

            DArrayAnimation animMove2 = GenerateAnimation(
                0.5, 1, "Copy node (k - 1)'s value to node k's value.");
            animMove2.SetAnimation([this, i](GUI::DynamicArray srcDS,
                                             float playingAt, Vector2 base) {
                GUI::Node& node = srcDS.GetList().at(i);
                GUI::Node& node_prev = srcDS.GetList().at(i - 1);
                if (playingAt >= 0.85f) node.SetValue(node_prev.GetValue());
                srcDS.Draw(base, playingAt);
                return srcDS;
            });
            animController->AddAnimation(animMove2);
            node.SetValue(node_prev.GetValue());
            node.AnimationOnNode(false);
            node_prev.AnimationOnNode(false);
        }
    }

    {  // Line 3
        visualizer[index].SetNodeState(GUI::Node::ActiveGreen);
        visualizer[index].AnimationOnNode(true);
        DArrayAnimation animUpdate =
            GenerateAnimation(0.5, 2, "Update value v at index i.");
        animUpdate.SetAnimation([this, index, value](GUI::DynamicArray srcDS,
                                                     float playingAt,
                                                     Vector2 base) {
            GUI::Node& node = srcDS.GetList().at(index);
            if (playingAt >= 0.85f) node.SetValue(value);
            srcDS.Draw(base, std::min(1.0f, playingAt * (1.00f / 0.75f)));
            return srcDS;
        });
        animController->AddAnimation(animUpdate);
    }
    ResetVisualizer();
}

void Algorithm::StaticArray::Delete(int index) {
    InitAction({"if(length == 0) return;", "arr[i] = 0;",
                "for(int k=i;k<length-1;k++) arr[k] = arr[k+1];",
                "arr[length-1] = 0;"});
    if (visualizer.GetLength() == 0) {
        DArrayAnimation animNoElement =
            GenerateAnimation(0.75, 0, "No element in the array to pop out.");
        animController->AddAnimation(animNoElement);
        return;
    }
    DArrayAnimation animHasElement = GenerateAnimation(
        0.75, 0,
        "The array is not empty, so we will proceed to the next step.");
    animController->AddAnimation(animHasElement);

    {  // Line 2
        GUI::Node& node = visualizer[index];
        node.SetNodeState(GUI::Node::State::ActiveRed);
        node.AnimationOnNode(true);
        node.SetLabel("del");
        DArrayAnimation animRemove =
            GenerateAnimation(0.5, 0,
                              "Set the i element to 0, and shift all the "
                              "elements after i to the left.");
        animRemove.SetAnimation([index, this](GUI::DynamicArray srcDS,
                                              float playingAt, Vector2 base) {
            if (playingAt >= 0.80f) srcDS[index].SetValue(0);
            srcDS.Draw(base, playingAt);
            return srcDS;
        });
        animController->AddAnimation(animRemove);
        node.ClearLabel();
        node.SetValue(0);
        node.AnimationOnNode(false);
    }

    {  // Line 3
        for (int i = index; i < visualizer.GetLength() - 1; i++) {
            auto& node_next = visualizer.GetList()[i + 1];
            node_next.SetReachable(true);
            node_next.AnimationOnNode(true);
            node_next.SetNodeState(GUI::Node::State::ActiveBlue);
            DArrayAnimation animMove1 = GenerateAnimation(
                0.5, 2, "Copy node k's value to node (k + 1)'s value.");
            animController->AddAnimation(animMove1);

            node_next.AnimationOnNode(false);
            auto& node = visualizer.GetList()[i];
            node.SetReachable(true);
            node.AnimationOnNode(true);
            node.SetNodeState(GUI::Node::State::Active);

            DArrayAnimation animMove2 = GenerateAnimation(
                0.5, 2, "Copy node k's value to node (k + 1)'s value.");
            animMove2.SetAnimation([this, i](GUI::DynamicArray srcDS,
                                             float playingAt, Vector2 base) {
                GUI::Node& node = srcDS.GetList().at(i);
                GUI::Node& node_next = srcDS.GetList().at(i + 1);
                if (playingAt >= 0.85f) node.SetValue(node_next.GetValue());
                srcDS.Draw(base, playingAt);
                return srcDS;
            });
            animController->AddAnimation(animMove2);
            node.SetValue(node_next.GetValue());
            node.AnimationOnNode(false);
            node_next.AnimationOnNode(false);
        }
    }

    {  // Line 4
        GUI::Node& node = visualizer[visualizer.GetLength() - 1];
        node.SetNodeState(GUI::Node::State::ActiveRed);
        node.AnimationOnNode(true);
        node.SetLabel("back");
        DArrayAnimation animPopBack = GenerateAnimation(
            1.50, 3,
            "Reset the current element's value and decrease the array length.");
        animPopBack.SetAnimation(
            [this](GUI::DynamicArray srcDS, float playingAt, Vector2 base) {
                if (playingAt <= 0.3f) {
                    srcDS.Draw(base, std::min(1.0f, playingAt * (1.0f / 0.3f)));
                    return srcDS;
                }
                if (playingAt >= 0.45f)
                    srcDS[srcDS.GetLength() - 1].SetValue(0);
                if (playingAt >= 0.60f)
                    srcDS[srcDS.GetLength() - 1].SetReachable(false);
                if (playingAt >= 0.7f) {
                    srcDS[srcDS.GetLength() - 1].SetNodeState(
                        GUI::Node::State::Iterated);
                    srcDS.Draw(base, (playingAt - 0.7f) * (1.0f / 0.3f));
                } else
                    srcDS.Draw(base, 1.0f);
                return srcDS;
            });
        animController->AddAnimation(animPopBack);

        visualizer[visualizer.GetLength() - 1].ClearLabel();
        visualizer[visualizer.GetLength() - 1].SetValue(0);
    }
    ResetVisualizer();
}

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
    visualizer[index].AnimationOnNode(true);
    visualizer[index].SetNodeState(GUI::Node::State::Active);
    anim =
        GenerateAnimation(0.75, 0,
                          "Return the value stored at the head: " +
                              std::to_string(visualizer[0].GetValue()) + ".");
    visualizer[index].SetNodeState(GUI::Node::State::Default);
    visualizer[index].AnimationOnNode(false);
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

    DArrayAnimation state = GenerateAnimation(0.5, -1, "");
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
    for (int i = 0; i < visualizer.GetLength(); i++) {
        auto& node = visualizer[i];
        node.AnimationOnNode(false);
        node.SetNodeState(GUI::Node::Default);
    }
}