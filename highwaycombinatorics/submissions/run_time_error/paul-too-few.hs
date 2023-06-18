import Data.Array.Unboxed
import Data.List
import Data.Maybe
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

halves :: [(Int, Int, [Int])]
halves = take 777777 $ tail $ go 99 99
  where
    f k (x,y,ks) = (fib!k *: x, invFib!k *: y, k:ks)
    go a n = (1,1,[]) : [f k c | let b = min a n, k <- [b,b-1..3], c <- go k (n-k)]

findPartition :: Int -> [Int]
findPartition z = head [is++js | (_,y,is) <- halves, js <- maybeToList $ M.lookup (z *: y) m]
  where m = M.fromList [(x,ks) | (x,_,ks) <- halves]

solve :: Int -> [String]
solve 0 = [".##", "##."]
solve n = replicate 2 $ intercalate "#" [replicate (k-1) '.' | k <- findPartition n]

main :: IO ()
main = interact $ unlines . solve . read
