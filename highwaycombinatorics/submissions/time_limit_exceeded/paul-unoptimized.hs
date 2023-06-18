import Control.Monad
import Data.Array.Unboxed
import Data.List
import qualified Data.IntMap as M

p = 10^9 + 7 :: Int

(+:), (*:) :: Int -> Int -> Int
a +: b = (a + b) `rem` p
a *: b = (a * b) `rem` p

inv :: Int -> Int
inv a = go a (p-2)
  where
    go a n
      | n == 0     = 1
      | even n     = let x = go a (n`div`2) in x *: x
      | otherwise  = a *: go a (n-1)

fib, invFib :: UArray Int Int
fib = listArray (0,99) $ go 0 1
  where go a b = a : go b ((a+b)`mod`p)
invFib = amap inv fib

type Partition = (Int, Int, [Int])

partitions :: Int -> [Partition]
partitions n = go n n
  where
    f k (x,y,ks) = (x *: (fib!k), y *: (invFib!k), k:ks)
    go a n = (1,1,[]) : [f k u | k <- [3 .. min a n], u <- go k (n-k)]

findPartition :: Int -> [Int]
findPartition z = let Left res = foldM step M.empty $ partitions 99 in res
  where step m (x,y,u) = maybe (Right $ M.insert x u m) (\v -> Left (u ++ v)) $ M.lookup (z *: y) m

solve :: Int -> [String]
solve 0 = [".##", "##."]
solve n = replicate 2 $ intercalate "#" [replicate (k-1) '.' | k <- findPartition n]

main :: IO ()
main = interact $ unlines . solve . read
