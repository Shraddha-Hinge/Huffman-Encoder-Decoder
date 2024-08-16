#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

// Custom frequency count function
template <typename T>
int countElem(const vector<T>& xs, T e) {
    int count = 0;
    for (const auto& x : xs) {
        if (x == e) {
            count++;
        }
    }
    return count;
}

// Filter out elements equal to the given value
template <typename T>
vector<T> filterElem(const vector<T>& xs, T e) {
    vector<T> filtered;
    for (const auto& x : xs) {
        if (x != e) {
            filtered.push_back(x);
        }
    }
    return filtered;
}

// Generate frequency list
template <typename T>
vector<pair<T, int>> freqList(const vector<T>& xs) {
    vector<pair<T, int>> freqs;
    for (const auto& x : xs) {
        int count = countElem(xs, x);
        auto it = find_if(freqs.begin(), freqs.end(), [x](const pair<T, int>& p) {
            return p.first == x;
        });
        if (it == freqs.end()) {
            freqs.push_back(make_pair(x, count));
        }
    }
    return freqs;
}

// Tree data structure
struct HuffmanTree {
    char character;
    int frequency;
    HuffmanTree* left;
    HuffmanTree* right;
    HuffmanTree(char c, int freq) : character(c), frequency(freq), left(nullptr), right(nullptr) {}
};

// Sorting helper function for nodes
bool sortByFrequency(const pair<int, HuffmanTree*>& a, const pair<int, HuffmanTree*>& b) {
    return a.first < b.first;
}

// Generate Huffman Tree
HuffmanTree* buildHuffmanTree(const vector<pair<char, int>>& freqs) {
    vector<pair<int, HuffmanTree*>> nodes;
    for (const auto& p : freqs) {
        nodes.push_back(make_pair(p.second, new HuffmanTree(p.first, p.second)));
    }

    while (nodes.size() > 1) {
        sort(nodes.begin(), nodes.end(), sortByFrequency);
        auto first = nodes[0];
        auto second = nodes[1];
        nodes.erase(nodes.begin(), nodes.begin() + 2);

        HuffmanTree* combined = new HuffmanTree('\0', first.first + second.first);
        combined->left = first.second;
        combined->right = second.second;

        nodes.push_back(make_pair(first.first + second.first, combined));
    }

    return nodes[0].second;
}

// Generating Huffman codes
void generateHuffmanCodes(HuffmanTree* tree, map<char, string>& codes, string path) {
    if (tree->left == nullptr && tree->right == nullptr) {
        codes[tree->character] = path;
    } else {
        generateHuffmanCodes(tree->left, codes, path + "0");
        generateHuffmanCodes(tree->right, codes, path + "1");
    }
}

// Encoding string using Huffman codes
string huffmanEncode(const string& xs, const map<char, string>& codes) {
    string encoded;
    for (char c : xs) {
        encoded += codes.at(c);
    }
    return encoded;
}

// Decoding string using Huffman codes
string huffmanDecode(const string& xs, HuffmanTree* tree) {
    string decoded;
    HuffmanTree* current = tree;
    for (char bit : xs) {
        if (bit == '0') {
            current = current->left;
        } else if (bit == '1') {
            current = current->right;
        }

        if (current->left == nullptr && current->right == nullptr) {
            decoded += current->character;
            current = tree;
        }
    }
    return decoded;
}

int main() {
    cout << "Enter the name of the text file (with extension):" << endl;
    string fileName;
    cin >> fileName;

    ifstream file(fileName);
    if (!file.is_open()) {
        cerr << "Error opening file." << endl;
        return 1;
    }

    string contents((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();

    cout << "Original Text:" << endl;
    cout << contents << endl;

    auto freqs = freqList(contents);

    HuffmanTree* tree = buildHuffmanTree(freqs);

    map<char, string> codes;
    generateHuffmanCodes(tree, codes, "");

    cout << "Huffman Encoded:" << endl;
    string encoded = huffmanEncode(contents, codes);
    cout << encoded << endl;

    cout << "Huffman Decoded:" << endl;
    string decoded = huffmanDecode(encoded, tree);
    cout << decoded << endl;

    return 0;
}
