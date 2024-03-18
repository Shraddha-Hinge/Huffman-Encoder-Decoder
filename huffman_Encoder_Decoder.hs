import System.IO

-- Custom frequency count function
countElem :: (Eq a) => [a] -> a -> Int
countElem [] _ = 0
countElem (x:xs) e = if x == e then 1 + countElem xs e else countElem xs e

-- Filter out elements equal to the given value
filterElem :: (Eq a) => [a] -> a -> [a]
filterElem xs e = filter (/= e) xs

-- Generate frequency list
freqList :: Eq a => [a] -> [(a, Int)]
freqList [] = []
freqList (x:xs) = (x, countElem (x:xs) x) : freqList (filterElem xs x)

-- Tree data structure
data HuffmanTree = HuffmanLeaf Char | HuffmanNode Int HuffmanTree HuffmanTree deriving Show

-- Generate Huffman Tree
buildHuffmanTree :: [(Char, Int)] -> HuffmanTree
buildHuffmanTree xs = constructTree (sortNodes (map (\(x, y) -> (y, HuffmanLeaf x)) xs))

-- Sorting helper functions
sortNodes :: [(Int, HuffmanTree)] -> [(Int, HuffmanTree)]
sortNodes = foldr insertNode []

insertNode :: (Int, HuffmanTree) -> [(Int, HuffmanTree)] -> [(Int, HuffmanTree)]
insertNode x [] = [x]
insertNode x (y:ys) = if fst x <= fst y then x : y : ys else y : insertNode x ys

-- Combining trees in building Huffman Tree
combineTrees :: (Int, HuffmanTree) -> (Int, HuffmanTree) -> (Int, HuffmanTree)
combineTrees (p1, t1) (p2, t2) = (p1 + p2, HuffmanNode (p1 + p2) t1 t2)

-- Build Huffman Tree recursively
constructTree :: [(Int, HuffmanTree)] -> HuffmanTree
constructTree [(_, t)] = t
constructTree (a:b:xs) = constructTree (insertNode (combineTrees a b) xs)

-- Generating Huffman codes
generateHuffmanCodes :: HuffmanTree -> [(Char, String)]
generateHuffmanCodes tree = getPath tree ""

getPath :: HuffmanTree -> String -> [(Char, String)]
getPath (HuffmanLeaf s) path = [(s, path)]
getPath (HuffmanNode _ l r) path = getPath l (path ++ "0") ++ getPath r (path ++ "1")

-- Encoding string using Huffman codes
huffmanEncode :: String -> String
huffmanEncode xs = concatMap (\x -> encodeChar (generateHuffmanCodes (buildHuffmanTree (freqList xs))) x) xs

-- Decoding string using Huffman codes
huffmanDecode :: String -> String
huffmanDecode xs = decode xs (buildHuffmanTree (freqList xs))
  where
    decode [] _ = ""
    decode xs tree = case decodeChar xs tree of
                      Just (char, rest) -> char : decode rest tree
                      Nothing           -> error "Invalid Huffman encoding"

    decodeChar xs (HuffmanLeaf s) = Just (s, xs)
    decodeChar ('0':xs) (HuffmanNode _ l _) = decodeChar xs l
    decodeChar ('1':xs) (HuffmanNode _ _ r) = decodeChar xs r
    decodeChar _ _ = Nothing

-- Modified `ord` behavior to mimic 'Data.Char.ord' for '0'-'9'
-- Directly subtracting 48 assuming input will be '0'-'9'
charToDigit :: Char -> Int
charToDigit x = fromEnum x - 48

-- Example Main to demonstrate functionality
main :: IO ()
main = do
  putStrLn "Enter the name of the text file (with extension):"
  fileName <- getLine
  contents <- readFile fileName
  putStrLn "Original Text:"
  putStrLn contents
  putStrLn "Huffman Encoded:"
  let encoded = huffmanEncode contents
  putStrLn encoded
  putStrLn "Huffman Decoded:"
  let decoded = huffmanDecode encoded
  putStrLn decoded

