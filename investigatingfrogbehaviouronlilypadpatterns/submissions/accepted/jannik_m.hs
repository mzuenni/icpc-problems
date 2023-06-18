import qualified Data.ByteString.Char8 as C
import Control.Monad
import Control.Monad.State.Strict
import qualified Data.IntSet as S
import Data.Maybe
import Data.Function
import Data.Array.IO

int = fst . fromJust . C.readInt <$> state (\(x:xs) -> (x,xs))

main = C.getContents >>= evalStateT f . C.words

solve :: IOUArray Int Int -> S.IntSet -> Int -> IO S.IntSet
solve pos free id = do
  p <- readArray pos id
  let np = fromJust $ S.lookupGT p free
  writeArray pos id np
  print np
  pure $ S.insert p $ S.delete np free

f = do
  n <- int
  init <- replicateM n int
  let free = on (S.\\) S.fromDistinctAscList [1..1230002] init
  pos <- liftIO $ newListArray (1,n) init
  int >>= flip replicateM int >>= liftIO . foldM_ (solve pos) free
