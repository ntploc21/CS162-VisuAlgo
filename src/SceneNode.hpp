#ifndef SCENENODE_HPP
#define SCENENODE_HPP

#include <memory>
#include <vector>

#include "NonCopyable.hpp"

class SceneNode
// : public NonCopyable< SceneNode >
{
public:
    typedef std::unique_ptr< SceneNode > Ptr;

public:
    SceneNode();
    virtual ~SceneNode(){};
    void AttachChild(Ptr child);
    Ptr DetachChild(const SceneNode& node);
    virtual void Draw();
    virtual void DrawCurrent() = 0;
    // virtual void Update()
private:
    std::vector< Ptr > mChildren;
    SceneNode* mParent;
};

#endif  // SCENENODE_HPP