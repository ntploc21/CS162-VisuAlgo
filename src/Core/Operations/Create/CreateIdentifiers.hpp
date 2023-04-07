#ifndef CORE_OPERATIONS_CREATE_CREATEIDENTIFIERS_HPP
#define CORE_OPERATIONS_CREATE_CREATEIDENTIFIERS_HPP

namespace CreateOperation {
    enum ID {
        Empty,
        Random,
        RandomFixedSize,
        UserDefined,
        ReadFromFile,
        OperationCount
    };
};

#endif  // CORE_OPERATIONS_CREATE_CREATEIDENTIFIERS_HPP