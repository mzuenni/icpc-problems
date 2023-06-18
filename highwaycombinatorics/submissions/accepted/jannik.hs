{-# LANGUAGE BangPatterns #-}
import qualified Data.IntMap as M
import Data.List
import Data.Array.Unboxed
import Data.Word

p = 10^9 + 7 :: Int

newtype M = M { fromM :: Int }
instance Num M where
  (M a) + (M b) = M $ (a + b) `rem` p
  (M a) * (M b) = M $ (a * b) `rem` p
  fromInteger = M . (`rem` p) . fromInteger

rnd :: [Int]
rnd = iterate (\s -> (1103515245*s + 12345) `rem` 2^31) 42

fibs = 1 : 1 : zipWith (+) fibs (tail fibs)
fib,invFib :: UArray Int Int
fib = listArray (1,100) $ fromM <$> fibs
invFib = amap (fromM . (^(p-2)) . M) fib

walk :: M.IntMap Int -> Int -> [Int]
walk _ 1 = []
walk vis a = let i = vis M.! a in i : walk vis ((a * invFib!i) `rem` p)

findPartition :: Int -> [Int]
findPartition n = go rnd 1 1 0 M.empty
  where
    go :: [Int] -> Int -> Int -> Int -> M.IntMap Int -> [Int]
    go (s:rs) !a !b !l !seen
      | l >= 98 = go (s:rs) 1 1 0 seen
      | otherwise =
        let i = 2 + rem s (98 - l)
            (a',b') = ((a * fib!i) `rem` p, (b * invFib!i) `rem` p)
            l' = l + 1 + i
            seen' = M.insertWith (flip const) a' i seen
        in if M.member ((b' * n) `rem` p) seen'
              then walk seen' a' ++ walk seen' ((b' * n) `rem` p)
              else go rs a' b' l' seen'


solve :: Int -> [String]
solve 0 = [".##", "##."]
solve 1 = [".", "."]
solve n = replicate 2 $ intercalate "#" [replicate (k-1) '.' | k <- findPartition n]

main = interact $ unlines . solve . read
