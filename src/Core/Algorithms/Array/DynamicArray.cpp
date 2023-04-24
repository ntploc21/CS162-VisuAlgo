#include "DynamicArray.hpp"

Algorithm::DynamicArray::DynamicArray() {}

Algorithm::DynamicArray::DynamicArray(
    GUI::CodeHighlighter::Ptr codeHighlighter,
    DArrayAnimationController::Ptr animController, FontHolder* fonts)
    : Algorithm::Algorithm(codeHighlighter, animController, fonts) {
    Random();
}

Algorithm::DynamicArray::~DynamicArray() {}

void Algorithm::DynamicArray::PushBack(int value) {}

void Algorithm::DynamicArray::PopBack() {}

void Algorithm::DynamicArray::Update(int index, int value) {}

void Algorithm::DynamicArray::Search(int value) {}

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
