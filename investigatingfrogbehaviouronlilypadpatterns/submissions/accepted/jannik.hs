import qualified Data.ByteString.Char8 as C
import Control.Monad
import Control.Monad.State.Strict
import qualified Data.IntSet as S
import qualified Data.Sequence as Seq
import Data.Maybe
import Data.Function

int = fst . fromJust . C.readInt <$> state (\(x:xs) -> (x,xs))

main = C.getContents >>= evalStateT f . C.words

solve (pos,free) id = (Seq.update id np pos, S.insert p $ S.delete np free) <$ (liftIO $ print np)
  where
    p = pos `Seq.index` id
    np = fromJust $ S.lookupGT p free

f = do
  n <- int
  init <- replicateM n int
  let free = on (S.\\) S.fromDistinctAscList [1..1230002] init
  int >>= flip replicateM (pred <$> int) >>= foldM_ solve (Seq.fromList init, free)
