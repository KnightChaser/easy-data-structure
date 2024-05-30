/**
 * @file huffman_code.cpp
 * @brief Huffman Code algorithm (string encoding/decoding) implementation using a priority queue
 */

#include <iostream>
#include <queue>
#include <map>
#include <vector>
#include <memory>
#include <string>

// Define the node structure for the Huffman tree
struct HuffmanNode {
    char character;                         // The character stored in the node
    unsigned int frequency;                 // The frequency(occurrence of appearance in the given std::stirng text) of the character
    std::shared_ptr<HuffmanNode> left;      // Pointer to the left child node
    std::shared_ptr<HuffmanNode> right;     // Pointer to the right child node

    // Constructor
    HuffmanNode(char character, unsigned int frequency) 
        : character(character), frequency(frequency), left(nullptr), right(nullptr) {}

    // Comparison operator for the priority queue (min heap)
    bool operator>(const HuffmanNode& other) const {
        return frequency > other.frequency;
    }

    // With using the overloaded operator, we can compare the HuffmanNode objects in the priority queue (for std::priority_queue<HuffmanNode>)
    struct Compare {
        bool operator()(const std::shared_ptr<HuffmanNode>& a, const std::shared_ptr<HuffmanNode>& b) const {
            return *a > *b;
        }
    };
};

// A function to build the Huffman tree
// Suppose we have "abracadabra" as an input string, then the characterOccurrenceFrequencies will be like:
// [a: 5, b: 2, r: 2, c: 1, d: 1]
// The Huffman tree will be like:
//              [11]
//        ----------------
//        |              |
//     [5: a]           [6]
//                   ---------
//                   |       |
//                  [2]     [4]
//                -----     -----------
//                |   |     |         |
//            [1: c] [1: d] [2: b] [2: r]
// Right branch is 1, left branch is 0 (Vice versa is also possible. Note that generateHuffmanCodes function)
// For example, "c" is reached "(root) -> right -> left -> left -> (c)", so encoded as "100"

std::shared_ptr<HuffmanNode> buildHuffmanTree(const std::map<char, unsigned int>& characterOccurrenceFrequencies) {
    // Build a priority queue to store the nodes of the Huffman tree in ascending order of frequencies
    //  - 1st parameter: type of the elements in the priority queue
    //  - 2nd parameter: container type to be used (default is std::vector)
    //  - 3rd parameter: comparison function to sort the elements in the priority queue
    std::priority_queue<std::shared_ptr<HuffmanNode>, std::vector<std::shared_ptr<HuffmanNode>>, HuffmanNode::Compare> huffmanPriorityQueue;

    // Push the nodes of the Huffman tree to the priority queue    
    for (const auto& characterOccurrenceFrequency : characterOccurrenceFrequencies) {
        huffmanPriorityQueue.push(std::make_shared<HuffmanNode>(characterOccurrenceFrequency.first, characterOccurrenceFrequency.second));
    }

    while (huffmanPriorityQueue.size() > 1) {
        // EXtract two lowest frequency nodes from the priority queue
        std::shared_ptr<HuffmanNode> leftNode = huffmanPriorityQueue.top(); huffmanPriorityQueue.pop();
        std::shared_ptr<HuffmanNode> rightNode = huffmanPriorityQueue.top(); huffmanPriorityQueue.pop();

        // Create a parent node with the sum of the frequencies of the left and right nodes
        std::shared_ptr<HuffmanNode> parentNode = std::make_shared<HuffmanNode>('\0', leftNode->frequency + rightNode->frequency);
        parentNode->left = leftNode;
        parentNode->right = rightNode;

        // The new parent node is pushed back to the priority queue
        huffmanPriorityQueue.push(parentNode);
    }

    return huffmanPriorityQueue.top();
}

// A function to generate the Huffman codes for each character
void generateHuffmanCodes(const std::shared_ptr<HuffmanNode>& root, std::map<char, std::string>& huffmanCodes, std::string code = "") {
    if (!root->left && !root->right) {
        huffmanCodes[root->character] = code;
    } else {
        generateHuffmanCodes(root->left, huffmanCodes, code + "0");
        generateHuffmanCodes(root->right, huffmanCodes, code + "1");
    }
}

// A function to decode the Huffman encoded string
std::string decodeHuffmanCode(const std::shared_ptr<HuffmanNode>& root, const std::string& encodedString) {
    std::string decodedString;
    auto currentNode = root;
    for (char bit : encodedString) {
        currentNode = (bit == '0') ? currentNode->left : currentNode->right;
        if (!currentNode->left && !currentNode->right) {
            decodedString += currentNode->character;
            currentNode = root;
        }
    }
    return decodedString;
}

int main() {
    std::string inputString = "abracadabra";

    // Calculate the frequency of each character in the input string
    std::map<char, unsigned int> characterOccurrenceFrequencies;
    for (char character : inputString) {
        characterOccurrenceFrequencies[character]++;
    }

    // Build the Huffman tree
    auto huffmanTreeRoot = buildHuffmanTree(characterOccurrenceFrequencies);

    // Generate the Huffman codes for each character
    std::map<char, std::string> huffmanCodes;
    generateHuffmanCodes(huffmanTreeRoot, huffmanCodes);

    // Print the Huffman codes for each character
    std::cout << "Huffman Codes:" << std::endl;
    for (const auto& huffmanCode : huffmanCodes) {
        std::cout << huffmanCode.first << ": " << huffmanCode.second << std::endl;
    }

    // Encode the input string
    std::string encodedString;
    for (char character : inputString) {
        encodedString += huffmanCodes[character];
    }
    std::cout << "Encoded String: " << encodedString << std::endl;

    // Decode the encoded string
    std::string decodedString = decodeHuffmanCode(huffmanTreeRoot, encodedString);
    std::cout << "Decoded String: " << decodedString << std::endl;

    return 0;
}

// Huffman Codes:
// a: 0
// b: 110
// c: 100
// d: 101
// r: 111
// Encoded String: 01101110100010101101110
// Decoded String: abracadabra