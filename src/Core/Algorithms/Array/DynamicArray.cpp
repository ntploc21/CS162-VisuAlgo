#include "DynamicArray.hpp"

#include "Global.hpp"

Algorithm::DynamicArray::DynamicArray() {}

Algorithm::DynamicArray::DynamicArray(
    GUI::CodeHighlighter::Ptr codeHighlighter,
    DArrayAnimationController::Ptr animController, FontHolder* fonts)
    : Algorithm::Algorithm(codeHighlighter, animController, fonts) {
    Random();
}

Algorithm::DynamicArray::~DynamicArray() {}

void Algorithm::DynamicArray::PushBack(int value) {
    InitAction({"if(length == capacity) {",
                "	capacity = (capacity == 0) ? 1 : 2 * capacity;",
                "	int* new_arr[capacity];",
                "	for(int k=0;k<length;k++) new_arr[k] = arr[k];",
                "	delete[] arr, arr = new_arr;", "}",
                "arr[length++] = v;"});

    if (visualizer.GetLength() == visualizer.GetCapacity()) {
        DArrayAnimation anim1 =
            GenerateAnimation(0.75, 0,
                              "Length == Capacity, we need to reserve "
                              "more capacity for the newly pushed element.");
        animController->AddAnimation(anim1);

        DArrayAnimation anim2 =
            GenerateAnimation(0.75, 1,
                              "As the array size is constant, we have to "
                              "calculate a new capacity for a new array.");
        animController->AddAnimation(anim2);

        GUI::DynamicArray newVisualizer = visualizer;
        for (int k = 0; k < visualizer.GetLength(); k++) {
            newVisualizer[k].SetValue(0);
        }
        newVisualizer.Reserve(
            visualizer.GetCapacityFromLength(visualizer.GetLength() + 1));

        DArrayAnimation anim3 = GenerateAnimation(
            1.50f, 2,
            "Allocate a new array, our old data will be moved there.");

        float sizeX =
            40 * newVisualizer.GetCapacity() +
            newVisualizer.mNodeDistance * (newVisualizer.GetCapacity() - 1);

        Vector2 newPos = (Vector2){(global::SCREEN_WIDTH - sizeX) / 2, 90};
        newVisualizer.SetPosition((Vector2){newPos.x, newPos.y + 60});

        anim3.SetAnimation([this, newVisualizer, newPos](
                               GUI::DynamicArray srcDS, float playingAt,
                               Vector2 base) mutable {
            Vector2 curPos = srcDS.GetPosition();
            curPos.x +=
                (newPos.x - curPos.x) *
                AnimationFactory::BounceOut(std::min(1.0f, playingAt * 2));
            curPos.y +=
                (newPos.y - curPos.y) *
                AnimationFactory::BounceOut(std::min(1.0f, playingAt * 2));
            srcDS.SetPosition(curPos);

            if (playingAt >= 0.5f) {
                auto& nodes = newVisualizer.GetList();
                for (GUI::Node& node : nodes) {
                    node.SetRadius(
                        AnimationFactory::ElasticOut(playingAt * 2 - 1.0f) *
                        20);
                    node.SetValueFontSize(
                        AnimationFactory::ElasticOut(playingAt * 2 - 1.0f) *
                        24);
                    node.SetLabelFontSize(
                        AnimationFactory::ElasticOut(playingAt * 2 - 1.0f) *
                        20);
                }
                newVisualizer.Draw(base, playingAt * 2 - 1.0f);
            }
            srcDS.Draw(base, 1.0f);

            return srcDS;
        });
        animController->AddAnimation(anim3);
        visualizer.SetPosition(newPos);

        for (int k = 0; k < visualizer.GetLength(); k++) {
            visualizer[k].AnimationOnNode(true);
            visualizer[k].SetNodeState(GUI::Node::State::ActiveBlue);

            DArrayAnimation animCopyElement1 =
                GenerateAnimation(0.25, 3,
                                  "Copying arr element " + std::to_string(k) +
                                      "'s value to new_arr.");

            animCopyElement1.SetAnimation(
                [this, newVisualizer](GUI::DynamicArray srcDS, float playingAt,
                                      Vector2 base) mutable {
                    srcDS.Draw(base, playingAt);
                    newVisualizer.Draw(base, 1.0f);
                    return srcDS;
                });
            animController->AddAnimation(animCopyElement1);

            visualizer[k].AnimationOnNode(false);
            newVisualizer[k].SetNodeState(GUI::Node::State::Active);
            newVisualizer[k].AnimationOnNode(true);

            DArrayAnimation animCopyElement2 =
                GenerateAnimation(0.25, 3,
                                  "Copying arr element " + std::to_string(k) +
                                      "'s value to new_arr.");

            animCopyElement2.SetAnimation(
                [this, newVisualizer, k](GUI::DynamicArray srcDS,
                                         float playingAt,
                                         Vector2 base) mutable {
                    srcDS.Draw(base, 1.0f);

                    if (playingAt == 1.0f)
                        newVisualizer[k].SetValue(srcDS[k].GetValue());
                    newVisualizer.Draw(base, playingAt);
                    return srcDS;
                });
            animController->AddAnimation(animCopyElement2);

            newVisualizer[k].AnimationOnNode(false);
            newVisualizer[k].SetValue(visualizer[k].GetValue());
        }
        DArrayAnimation animDeleteOld =
            GenerateAnimation(0.5, 4, "Deallocate the old array.");
        animDeleteOld.SetAnimation([this, newVisualizer](
                                       GUI::DynamicArray srcDS, float playingAt,
                                       Vector2 base) mutable {
            auto& nodes = srcDS.GetList();
            for (auto& node : nodes) {
                node.SetRadius(AnimationFactory::ElasticOut(1.0f - playingAt) *
                               20);
                node.SetValueFontSize(
                    AnimationFactory::ElasticOut(1.0f - playingAt) * 24);
                node.SetLabelFontSize(
                    AnimationFactory::ElasticOut(1.0f - playingAt) * 20);
            }
            srcDS.Draw(base, 1.0f);
            newVisualizer.Draw(base, 1.0f);
            return srcDS;
        });
        animController->AddAnimation(animDeleteOld);

        visualizer = newVisualizer;
    } else {
        DArrayAnimation anim1 =
            GenerateAnimation(0.5, 0,
                              "Length != Capacity, so we don't need to reserve "
                              "more capacity for the newly pushed element. "
                              "Move to the next step.");
        animController->AddAnimation(anim1);
    }
    std::size_t index = visualizer.GetLength();
    auto& node = visualizer.GetList()[index];
    node.SetReachable(true);
    node.AnimationOnNode(true);
    node.SetNodeState(GUI::Node::State::Active);

    DArrayAnimation anim = GenerateAnimation(
        0.5, 6, "Update node i's value to " + std::to_string(value));

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
    visualizer.InsertNode(index, node, false);

    ResetVisualizer();
}

void Algorithm::DynamicArray::PopBack() {
    InitAction({"if(length == 0) return;", "arr[--length] = 0;"});

    if (visualizer.GetLength() == 0) {
        DArrayAnimation animNoElement =
            GenerateAnimation(0.75, 0, "No element in the array to pop out.");
        animController->AddAnimation(animNoElement);
        return;
    }
    DArrayAnimation animHasElement = GenerateAnimation(
        0.75, 0,
        "The array is not empty, so we will pop out the last element.");
    animController->AddAnimation(animHasElement);

    GUI::Node& node = visualizer[visualizer.GetLength() - 1];
    node.SetNodeState(GUI::Node::State::ActiveRed);
    node.AnimationOnNode(true);
    node.SetLabel("back");
    DArrayAnimation animPopBack = GenerateAnimation(
        1.50, 0,
        "Reset the current element's value and decrease the array length.");
    animPopBack.SetAnimation(
        [this](GUI::DynamicArray srcDS, float playingAt, Vector2 base) {
            if (playingAt <= 0.3f) {
                srcDS.Draw(base, std::min(1.0f, playingAt * (1.0f / 0.3f)));
                return srcDS;
            }
            if (playingAt >= 0.45f) srcDS[srcDS.GetLength() - 1].SetValue(0);
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

    visualizer.DeleteNode(visualizer.GetLength() - 1);
    // node.ClearLabel();
    // node.SetNodeState(GUI::Node::Default);
    // node.SetValue(0);
    // node.AnimationOnNode(false);
}

void Algorithm::DynamicArray::Update(int index, int value) {
    if (index >= visualizer.GetLength()) return;
    InitAction({"arr[i] = v;"});

    /* Animation goes here */
    auto& node = visualizer[index];
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

void Algorithm::DynamicArray::Search(int value) {
    InitAction({"for(int i=0;i<N;i++) {", "	if(arr[i] == v) return i;", "}",
                "return -1; // no element found"});

    /* Animation goes here */
    bool foundElement = false;
    for (int k = 0; k < visualizer.GetLength() && !foundElement; k++) {
        int curValue = visualizer[k].GetValue();
        {  // Line 1
            DArrayAnimation animLoopFor = GenerateAnimation(
                0.75, 0, "Increment k, index specified has not been reached.");
            if (k == 0)
                animLoopFor.SetActionDescription(
                    "Enter the loop.\nk is now: 0");
            else
                visualizer[k - 1].AnimationOnNode(false);
            animController->AddAnimation(animLoopFor);
        }

        {  // Line 2
            visualizer[k].SetNodeState(GUI::Node::Active);
            visualizer[k].SetLabel(std::to_string(k));
            visualizer[k].AnimationOnNode(true);

            DArrayAnimation animLoop1 = GenerateAnimation(
                0.75, 1,
                "arr[" + std::to_string(k) + "] = " + std::to_string(curValue) +
                    " is not equal to " + std::to_string(value) +
                    ", we move to the next iteration.");

            if (curValue == value) {
                foundElement = true;
                visualizer[k].SetNodeState(GUI::Node::ActiveGreen);
                animLoop1 = GenerateAnimation(
                    0.75, 1,
                    "arr[" + std::to_string(k) +
                        "] = " + std::to_string(curValue) + " = " +
                        std::to_string(value) + ", we have found the answer!");
            }

            animController->AddAnimation(animLoop1);

            visualizer[k].SetNodeState(GUI::Node::Iterated);
            visualizer[k].ClearLabel();
        }
    }
    if (!foundElement) {
        visualizer[visualizer.GetLength() - 1].AnimationOnNode(false);
        DArrayAnimation animNotFound =
            GenerateAnimation(0.75, 3, "No element found!");
        animController->AddAnimation(animNotFound);
    }
    ResetVisualizer();
}

void Algorithm::DynamicArray::ApplyInput(std::vector< int > input,
                                         std::size_t nMaxSize) {
    if (input.size() > nMaxSize) input.resize(nMaxSize);
    InitAction({});

    codeHighlighter->SetShowCode(false);
    codeHighlighter->SetShowAction(false);

    visualizer.Import(input);

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

void Algorithm::DynamicArray::ResetVisualizer() {
    auto& nodes = visualizer.GetList();
    for (GUI::Node& node : nodes) {
        node.AnimationOnNode(false);
        node.SetNodeState(GUI::Node::Default);
    }
}
