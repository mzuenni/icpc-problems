import qualified Data.ByteString.Char8 as C
main = C.interact $ solve . C.strip
solve s = if ns==s then C.pack "nO" else ns
  where
    i = head [ i+1 | (c,i) <- zip [1,3..] (C.elemIndices ')' s), c == i ]
    (l,r) = C.splitAt i s
    ns = C.append r l
