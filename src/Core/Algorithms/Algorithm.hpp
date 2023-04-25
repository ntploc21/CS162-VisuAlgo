#ifndef CORE_ALGORITHMS_LINKEDLIST_ALGORITHM_HPP
#define CORE_ALGORITHMS_LINKEDLIST_ALGORITHM_HPP

#include <algorithm>
#include <cassert>
#include <chrono>
#include <functional>
#include <iostream>
#include <map>
#include <random>
#include <string>
#include <vector>

#include "Components/Common/CodeHighlighter.hpp"
#include "Core/Animation/AnimationController.hpp"
#include "Core/Animation/AnimationFactory.hpp"
namespace Algorithm {
    template< typename GUIAlgorithm, typename AnimationState >
    class Algorithm {
    public:
        Algorithm(GUI::CodeHighlighter::Ptr codeHighlighter,
                  typename Animation::AnimationController< AnimationState >::Ptr
                      animController,
                  FontHolder* fonts);
        Algorithm();
        ~Algorithm();

    public:
    protected:
        GUIAlgorithm visualizer;
        GUI::CodeHighlighter::Ptr codeHighlighter;
        typename Animation::AnimationController< AnimationState >::Ptr
            animController;

    protected:
        int Rand(int lower, int upper);

    public:
        virtual void Empty();
        virtual void Random();
        virtual void RandomFixedSize(int N);
        virtual void UserDefined(std::string input);
        virtual void ReadFromExternalFile(std::string path);
        virtual void ApplyInput(std::vector< int > input,
                                std::size_t nMaxSize = 10);

    protected:
        std::vector< int > EmptyGenerator();
        std::vector< int > RandomGenerator();

        std::vector< int > RandomFixedSizeGenerator(int nSize);

        std::vector< int > UserDefinedGenerator(std::string input);

        std::vector< int > ReadFromFileGenerator(std::string inputFile);

    protected:
        virtual void GenerateRelayoutAnimation(Vector2 newPosition);
        virtual AnimationState GenerateAnimation(float duration,
                                                 int highlightLine,
                                                 std::string actionDescription);
        virtual void InitAction(std::vector< std::string > code);
    };
};  // namespace Algorithm

#include <sstream>

template< typename GUIAlgorithm, typename AnimationState >
inline Algorithm::Algorithm< GUIAlgorithm, AnimationState >::Algorithm(
    GUI::CodeHighlighter::Ptr codeHighlighter,
    typename Animation::AnimationController< AnimationState >::Ptr
        animController,
    FontHolder* fonts)
    : codeHighlighter(codeHighlighter), animController(animController),
      visualizer(GUIAlgorithm(fonts)) {
    // visualizer.SetPosition(0, 150);
}

template< typename GUIAlgorithm, typename AnimationState >
Algorithm::Algorithm< GUIAlgorithm, AnimationState >::Algorithm() {}

template< typename GUIAlgorithm, typename AnimationState >
Algorithm::Algorithm< GUIAlgorithm, AnimationState >::~Algorithm() {}

template< typename GUIAlgorithm, typename AnimationState >
int Algorithm::Algorithm< GUIAlgorithm, AnimationState >::Rand(int lower,
                                                               int upper) {
    std::mt19937 rng(
        std::chrono::steady_clock::now().time_since_epoch().count());
    assert(lower <= upper);
    return lower + rng() % (upper - lower + 1);
}

template< typename GUIAlgorithm, typename AnimationState >
std::vector< int >
Algorithm::Algorithm< GUIAlgorithm, AnimationState >::EmptyGenerator() {
    return std::vector< int >();
}

template< typename GUIAlgorithm, typename AnimationState >
std::vector< int >
Algorithm::Algorithm< GUIAlgorithm, AnimationState >::RandomGenerator() {
    int nSize = Rand(1, 10);
    // params["nSize"] = (char)(nSize + '0');
    return RandomFixedSizeGenerator(nSize);
}

template< typename GUIAlgorithm, typename AnimationState >
std::vector< int >
Algorithm::Algorithm< GUIAlgorithm, AnimationState >::RandomFixedSizeGenerator(
    int nSize) {
    std::vector< int > answer(nSize);
    for (int& v : answer) v = Rand(1, 99);
    return answer;
}

template< typename GUIAlgorithm, typename AnimationState >
std::vector< int >
Algorithm::Algorithm< GUIAlgorithm, AnimationState >::UserDefinedGenerator(
    std::string input) {
    bool canParse =
        (!input.empty() &&
         std::all_of(
             input.begin(), input.end(),
             [](char c) { return ('0' <= c && c <= '9') || (c == ','); }) &&
         input.back() != ',');
    if (!canParse) return EmptyGenerator();

    std::vector< int > answer;

    std::istringstream f(input);
    std::string s;
    while (std::getline(f, s, ',')) {
        try {
            answer.push_back(atoi(s.c_str()));
        } catch (char* e) {
        }
    }
    return answer;
}

template< typename GUIAlgorithm, typename AnimationState >
std::vector< int >
Algorithm::Algorithm< GUIAlgorithm, AnimationState >::ReadFromFileGenerator(
    std::string inputFile) {
    // will be implemented later
    return std::vector< int >();
}

template< typename GUIAlgorithm, typename AnimationState >
inline void
Algorithm::Algorithm< GUIAlgorithm, AnimationState >::GenerateRelayoutAnimation(
    Vector2 newPosition) {
    AnimationState animRelayout =
        GenerateAnimation(0.5, -1,
                          "Re-layout the Linked List for visualization "
                          "(not in the actual Linked "
                          "List).\nThe whole process is still O(1).");
    animRelayout.SetAnimation(
        [this, newPosition](GUIAlgorithm srcDS, float playingAt, Vector2 base) {
            Vector2 newPos = srcDS.GetPosition();
            newPos.x += (newPosition.x - newPos.x) * playingAt;
            newPos.y += (newPosition.y - newPos.y) * playingAt;
            srcDS.SetPosition(newPos);

            srcDS.Draw(base, playingAt);

            return srcDS;
        });
    animController->AddAnimation(animRelayout);
}

template< typename GUIAlgorithm, typename AnimationState >
AnimationState
Algorithm::Algorithm< GUIAlgorithm, AnimationState >::GenerateAnimation(
    float duration, int highlightLine, std::string actionDescription) {
    AnimationState animation;
    animation.SetDuration(duration);
    animation.SetHighlightLine(highlightLine);
    animation.SetSourceDataStructure(visualizer);
    animation.SetActionDescription(actionDescription);
    return animation;
}

template< typename GUIAlgorithm, typename AnimationState >
void Algorithm::Algorithm< GUIAlgorithm, AnimationState >::InitAction(
    std::vector< std::string > code) {
    animController->Reset();
    // animController->Pause();
    animController->InteractionAllow();
    animController->Clear();
    codeHighlighter->AddCode(code);
    codeHighlighter->SetShowCode(true);
    codeHighlighter->SetShowAction(true);
}

template< typename GUIAlgorithm, typename AnimationState >
void Algorithm::Algorithm< GUIAlgorithm, AnimationState >::Empty() {
    ApplyInput(EmptyGenerator());
}

template< typename GUIAlgorithm, typename AnimationState >
void Algorithm::Algorithm< GUIAlgorithm, AnimationState >::Random() {
    ApplyInput(RandomGenerator());
}

template< typename GUIAlgorithm, typename AnimationState >
void Algorithm::Algorithm< GUIAlgorithm, AnimationState >::RandomFixedSize(
    int N) {
    ApplyInput(RandomFixedSizeGenerator(N));
}

template< typename GUIAlgorithm, typename AnimationState >
void Algorithm::Algorithm< GUIAlgorithm, AnimationState >::UserDefined(
    std::string input) {
    ApplyInput(UserDefinedGenerator(input));
}

template< typename GUIAlgorithm, typename AnimationState >
void Algorithm::Algorithm< GUIAlgorithm, AnimationState >::ReadFromExternalFile(
    std::string path) {
    ApplyInput(ReadFromFileGenerator(path));
}

template< typename GUIAlgorithm, typename AnimationState >
void Algorithm::Algorithm< GUIAlgorithm, AnimationState >::ApplyInput(
    std::vector< int > input, std::size_t nMaxSize) {
    if (input.size() > nMaxSize) input.resize(nMaxSize);
    InitAction({});

    codeHighlighter->SetShowCode(false);
    codeHighlighter->SetShowAction(false);

    visualizer.Import(input);

    AnimationState state;
    state.SetDuration(0.5);
    state.SetHighlightLine(-1);
    state.SetSourceDataStructure(visualizer);
    state.SetAnimation([this](GUIAlgorithm srcDS, float playingAt,
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

#endif  // CORE_ALGORITHMS_LINKEDLIST_ALGORITHM_HPP