#ifndef RESOURCEIDENTIFIER_HPP
#define RESOURCEIDENTIFIER_HPP

namespace Fonts {
    enum ID { Default, Default_Italic, Default_Bold, Silkscreen, Count };
};

namespace Textures {
    enum ID {
        Blank,
        StaticArray,
        DynamicArray,
        SinglyLinkedList,
        DoublyLinkedList,
        CircularLinkedList,
        Stack,
        Queue,
        Favicon,
        Count
    };
};

#endif  // RESOURCEIDENTIFIER_HPP