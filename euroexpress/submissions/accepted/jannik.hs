import qualified Data.ByteString.Char8 as B
main=B.getContents>>= \l->print$maximum [a*b*min a b|[Just(a,_),Just(b,_)]<-map B.readInt.B.words<$>B.lines l]
