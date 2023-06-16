#include "CodeMap.hpp"

CodeMap::CodeMap(Node* root, const Str& initialCode) {
    this->content = generateCodes(root, initialCode);
}

Str CodeMap::at(const char& c) const
{
    return this->content.at(c);
}

mapCode CodeMap::generateCodes(Node *nodePtr, const Str &currentPrefix) {
    mapCode codeMapping;

    if (nodePtr == nullptr)
        return codeMapping;

    if (!nodePtr->left && !nodePtr->right) {  // Leaf node has been reached.
        codeMapping[nodePtr->data] = currentPrefix;
        return codeMapping;
    }

    auto leftMap = generateCodes(nodePtr->left, currentPrefix + "0");
    auto rightMap = generateCodes(nodePtr->right, currentPrefix + "1");

    codeMapping.insert(leftMap.begin(), leftMap.end());
    codeMapping.insert(rightMap.begin(), rightMap.end());

    return codeMapping;
}