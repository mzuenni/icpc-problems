{-# LANGUAGE Strict #-}

import qualified Data.ByteString.Char8 as C
import Data.Array.Unboxed
import Data.Array.ST
import Control.Monad.ST
import Data.Word

newtype Perm = Perm (UArray Word8 Word8)
instance Semigroup Perm where
  (Perm p1) <> (Perm p2) = Perm $ amap (p2!) p1

mkPerm n = let n' = fromIntegral n in Perm $ listArray (1,n') [1..n']

swap x (Perm p) = Perm $ p // [ (x, p!(x+1)), (x+1, p!x) ]

cycles (Perm p) = runST $ do
  vis <- newArray (bounds p) False
  let go :: STUArray s Word8 Bool -> Word8 -> ST s Int
      go vis i = readArray vis i >>= \v -> if v
            then pure 0
            else 1 <$ (mapM_ (flip (writeArray vis) True) . (i:) . takeWhile (/=i) $ iterate (p!) (p!i))
  sum <$> mapM (go vis) (indices p)

data Tree a
  = Tree a (Tree a) (Tree a)
  | Leaf    a
val (Tree v _ _) = v
val (Leaf v) = v

initTree 1 a = Leaf a
initTree n a = let m = div (n+1) 2 in mkTree (initTree m a) (initTree (n - m) a)

mkTree l r = Tree (val l <> val r) l r

update (Leaf v) _ _ f = Leaf $ f v
update (Tree _ l r) i n f
    | i < m     = mkTree (update l i m f) r
    | otherwise = mkTree l                (update r (i - m) (n - m) f)
  where m = div (n+1) 2

int s = case C.readInt s of Just (x,_) -> x
main = C.getContents >>= solve . map int . C.words

solve (w:h:_:qs) = go (initTree h (mkPerm w)) qs
  where
    go t (y:x1:x2:qs) = let t' = update t (y-1) h (swap . fromIntegral $ min x1 x2)
                         in C.putStrLn (C.pack $ show $ w - cycles (val t')) >> go t' qs
    go _ _ = pure ()
