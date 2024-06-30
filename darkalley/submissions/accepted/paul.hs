{-# LANGUAGE FlexibleContexts #-}

import Control.Monad
import Data.Array.IO
import Data.Array.Unboxed
import Data.Bits
import Data.Ratio
import Numeric
import qualified Data.ByteString.Char8 as B

pMod :: Int
pMod = 10^9 + 7

newtype ModInt = M { unM :: Int } deriving (Eq, Show)

instance Num ModInt where
  M a + M b = M $ (a+b) `mod` pMod
  M a - M b = M $ (a-b) `mod` pMod
  M a * M b = M $ (a*b) `mod` pMod
  abs = undefined
  signum = undefined
  fromInteger n = M $ fromInteger (n `mod` fromIntegral pMod)

instance Fractional ModInt where
  recip x = x^(pMod-2)
  fromRational p = fromIntegral (numerator p) / fromIntegral (denominator p)

addMod :: Int -> Int -> Int
addMod x y = unM $ fromIntegral x + fromIntegral y

lowBit :: Int -> Int
lowBit x = x .&. (-x)

modifyArray :: (MArray a e m, Ix i) => a i e -> (e -> e) -> i -> m ()
modifyArray a f i = readArray a i >>= \e -> writeArray a i (f e)

queryBIT :: Int -> IOUArray Int Int -> IO Int
queryBIT i arr = getBounds arr >>= go (i+1) 0 . snd
  where go i s n = if i < n then readArray arr i >>= \x -> go (i + lowBit i) (s+x) n else return s

addBIT :: Int -> Int -> IOUArray Int Int -> IO ()
addBIT i x arr = go i
  where go i = when (i > 0) $ modifyArray arr (addMod x) i >> go (i - lowBit i)

addRangeBIT :: Int -> Int -> Int -> IOUArray Int Int -> IO ()
addRangeBIT i j x arr = addBIT j x arr >> addBIT i (-x) arr

powers :: Int -> ModInt -> UArray Int Int
powers n p = listArray (-n,n) $ take (2*n+1) $ map unM $ iterate (*p) $ 1/p^n

parseInt :: B.ByteString -> Int
parseInt s = let Just (n, _) = B.readInt s in n

main :: IO ()
main = do
  [n', m', p'] <- B.words <$> B.getLine
  let n = parseInt n'; m = parseInt m'
  let p = 1 - fromRational (fst $ head $ readFloat $ B.unpack p')
  let pow = powers n p
  a <- newArray (0,n+2) 0
  c <- newArray (0,n+2) 0
  replicateM_ m $ do
    ws <- B.words <$> B.getLine
    if length ws == 3 then do
      let [x', k] = map parseInt $ tail ws
      let x = if B.head (head ws) == '+' then x' else -x'
      addBIT k (x * pow!k) c
      addRangeBIT k (n+1) (x * pow!(-k)) a
    else do
      let k = parseInt (last ws)
      x <- queryBIT k a
      y <- queryBIT k c
      B.putStrLn $ B.pack $ show $ addMod (x * pow!k) (y * pow!(-k))
