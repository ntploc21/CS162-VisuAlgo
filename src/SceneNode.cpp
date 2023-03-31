#include "SceneNode.hpp"

#include <algorithm>
#include <cassert>

SceneNode::SceneNode() : mParent(nullptr) {}

void SceneNode::AttachChild(Ptr child) {
    child->mParent = this;
    mChildren.push_back(std::move(child));
}

SceneNode::Ptr SceneNode::DetachChild(const SceneNode& node) {
    auto found = std::find_if(mChildren.begin(), mChildren.end(),
                              [&](Ptr& p) -> bool { return p.get() == &node; });
    assert(found != mChildren.end());

    Ptr result = std::move(*found);
    result->mParent = nullptr;
    mChildren.erase(found);
    return result;
}

void SceneNode::Draw() {
    DrawCurrent();
    for (auto it = mChildren.begin(); it != mChildren.end(); it++) {
        (*it)->Draw();
    }
}
