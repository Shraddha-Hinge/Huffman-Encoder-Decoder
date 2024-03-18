# Huffman Encoding Project

This Haskell project implements Huffman Encoding, a method used for lossless data compression. It includes functions to encode and decode text files using Huffman codes.

## Table of Contents
 -   Introduction
 -   Components
       - Custom Functions
       - Huffman Tree
       - Encoding and Decoding
 -   Usage

## Introduction

Huffman Encoding is a technique used to compress data by assigning variable-length codes to input characters, with shorter codes assigned to more frequent characters. This project provides an implementation of Huffman Encoding in Haskell, allowing users to encode and decode text files efficiently.

## Components
- ## Custom Functions

    countElem: Counts the occurrences of a given element in a list.
    filterElem: Filters out elements equal to the given value from a list.
    freqList: Generates a list of tuples containing characters and their frequencies in the input text.
    charToDigit: Converts a character representing a digit to its corresponding integer value.

- ## Huffman Tree

    HuffmanTree: Defines the data structure for Huffman trees, which can be either a leaf node containing a character or a node containing the sum of frequencies and references to its left and right subtrees.
    buildHuffmanTree: Constructs a Huffman tree from a list of character frequencies.
    combineTrees: Combines two Huffman trees into a single tree with their frequencies as weights.
    constructTree: Recursively constructs a Huffman tree by combining nodes until a single tree is formed.

- ## Encoding and Decoding

    generateHuffmanCodes: Generates Huffman codes for each character in the Huffman tree.
    huffmanEncode: Encodes a text string using Huffman codes.
    huffmanDecode: Decodes a Huffman-encoded string back to its original text.

## Usage

To use this project, follow these steps:

    Ensure you have Haskell installed on your system.
    Clone or download this repository.
    Navigate to the project directory in your terminal.
    Compile the Haskell files using GHC (Glasgow Haskell Compiler).
    Run the executable file with the name of the text file you want to encode/decode.
