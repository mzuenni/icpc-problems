main :: IO ()
main = interact $ (++ "\n") . show . maximum . map process . tail . lines
  where process = (\[a,b] -> a * b * min a b) . map read . words
