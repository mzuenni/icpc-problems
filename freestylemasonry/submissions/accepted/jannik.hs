import qualified Data.ByteString.Char8 as C
import Data.List
import Data.Bool

int s = case C.readInt s of Just (x,_) -> x
main = C.getContents >>= putStrLn . solve . map int . C.words

solve :: [Int] -> String
solve (_:h:hs) = bool "impossible" "possible" possible
  where
    possible = h == foldl' (\top x -> bool
        (-1)
        (min h $ top + 1 - 2 * mod (top - x) 2)
        (top >= x)) h hs
