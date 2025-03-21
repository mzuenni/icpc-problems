{-# LANGUAGE FlexibleContexts #-}
import qualified Data.ByteString.Char8 as B
import qualified Data.IntSet as S
import Control.Monad.Trans.Writer
import Control.Monad.Trans
import Control.Monad
import Control.Monad.ST
import Data.List
import Data.Monoid
import Data.Bool
import Data.Array.ST
import GHC.Arr

pairs (x:y:xs) = (x,y) : (y,x) : pairs xs
pairs [] = []

split xs = snd $ foldr
 (\i (xs,acc) -> bool (i:xs,acc) ([],xs:acc) (i<0))
 ([],[])
 ((-1) : maybe
   xs 
   (\i -> let (l,r) = splitAt i (init xs) in r++l)
   (elemIndex (-1) xs))

tells x = tell $ Endo (x:)

mA a i f = readArray a i >>= writeArray a i . f

solve (n:_:xs) = print (length result) >> forM_ result (\xs -> print (length xs) >> putStrLn (unwords $ show <$> xs))
 where
  walks = runST $ do
    g <- newSTArray (1,n) S.empty
    let euler i = lift (S.minView <$> readArray g i) >>= maybe
          (tells i)
          (\(j,e) -> lift (writeArray g i e >> mA g (div j 2) (S.delete (i*2 + rem j 2))) >> euler (div j 2) >> when (odd j) (tells (-1)) >> euler i)
    mapM_ (\(u,e) -> mA g u $ S.insert (2*e)) $ pairs $ drop (2*n) xs
    filterM (fmap (odd . S.size) . readArray g) [1..n] >>= mapM_ (\(u,e) -> mA g u (S.insert (2*e+1))) . pairs
    forM [1..n] $ fmap (`appEndo` []) . execWriterT . euler
  result = concatMap (filter ((>1) . length) . split) walks

main = B.getContents >>= solve . map ((\(Just (x,_)) -> x) . B.readInt) . B.words
