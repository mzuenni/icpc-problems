import Data.List

solve :: [Int] -> Int
solve [a,b] = (a+b) * length (nub [x`mod`(a+b) | x <- [a, -a, b+1, -b-1]]) `div` 2

main :: IO ()
main = interact $ (++ "\n") . show . solve . map read . words
