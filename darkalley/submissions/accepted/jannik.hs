{-# LANGUAGE OverloadedStrings #-}

import qualified Data.ByteString.Char8 as B
import Data.Array.Unboxed

mr :: Int
mr = 10^9 + 7
m x = rem x mr

newtype M = M { unM :: Int }
instance Num M where
  fromInteger = M . fromInteger . flip rem (toInteger mr)
  (M a) + (M b) = M . m $ a + b
  (M a) - (M b) = M . m $ a + mr - b
  (M a) * (M b) = M . m $ a * b
  signum = undefined
  abs = undefined
inv :: M -> M
inv x = x ^ (mr - 2)


data Tree a
  = Tree !a (Tree a) (Tree a)
  | Leaf !a
val (Tree v _ _) = v
val (Leaf v) = v
initTree 1 a = Leaf a
initTree n a = let m = div (n+1) 2 in mkTree (initTree m a) (initTree (n - m) a)
mkTree l r = Tree (val l + val r) l r
update t i n _ | i >= n = t
update (Leaf v) _ _ f = Leaf $ f v
update (Tree _ l r) i n f
  | i < m     = mkTree (update l i m f) r
  | otherwise = mkTree l                (update r (i - m) (n - m) f)
 where m = div (n+1) 2
query _ i _ | i < 0 = 0
query (Leaf v) _ _ = v
query (Tree v l r) i n = if i >= n then v else query l i m + query r (i - m) (n - m)
 where m = div (n+1) 2


int = (\(Just(x,_)) -> x) . B.readInt

main = B.getContents >>= putStr . unlines . map (show . unM) . solve . B.words

solve (n':_:ps:xs) = go (initTree n 0) (initTree n 0) xs
 where
  n = int n'
  p = let r = B.drop 2 ps; q = 10 ^ B.length r in M (q - int r) * inv (M q)
  pow_p', pow_i' :: UArray Int Int
  pow_p' = listArray (0,n-1) . map unM $ iterate (* p) 1
  pow_i' = listArray (0,n-1) . map unM $ iterate (* inv p) 1
  pow_p = M . (pow_p' !)
  pow_i = M . (pow_i' !)
  go l r ("?":x':xs) =
     (query l x n * pow_p x) +
     (query r y n * pow_p y) : go l r xs
   where x = int x' - 1; y = n - 1 - x
  go l r (op:b':x':xs) = go
     (update l x     n (pow_i x * b +))
     (update r (y+1) n (pow_i y * b +))
     xs
   where
    b = M $ (if op == "-" then (mr -) else id) (int b')
    x = int x' - 1
    y = n - 1 - x
  go _ _ _ = []
