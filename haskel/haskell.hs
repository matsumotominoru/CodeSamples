head' :: [a] -> a
head' [] = error "None"
head' (x:_) = x
max' :: (Ord a) => a -> a -> a
max' a b 
    | a <= b    = b
    | otherwise = a
a `mycompare` b 
    | a == b    = EQ
    | a <= b    = LT
    | otherwise = GT
fanctorial n
    | n == 0    = 1
    | otherwise = n*fanctorial(n-1)
aho (a,b) 
    | (a,b) == (0,0) = 0
    | otherwise      = 1
baka (a,b) 
    | a > 0 , b > 0    = 0
    | otherwise        = 1