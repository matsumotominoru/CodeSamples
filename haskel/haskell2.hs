import Data.List
import Data.Char
initials :: String -> String -> String
initials firstname lastname = [f] ++ ". " ++ [l] ++ "."
    where (f:_) = firstname
          (l:_) = lastname
head' :: [a] -> a
head' xs = case xs of [] -> error "No head for empty lists!"
                      (x:_) -> x
describeList :: [a] -> String
describeList ls = "The list is "
                  ++ case ls of [] -> "empty."
                                [x] -> "a singleton list."
                                xs -> "a longer list."
maximum' :: (Ord a) => [a] -> a
maximum' [] = error "maximum of empty list!"
maximum' [x] = x
maximum' (x:xs) = max x (maximum' xs)
replicate' :: Int -> a -> [a]
replicate' n x
    | n <= 0    = []
    | otherwise = x : replicate' (n-1) x
take' :: Int -> [a] -> [a]
take' n _
    | n <= 0   = []
take' _ []     = []
take' n (x:xs) = x : take' (n-1) xs
reverse' :: [a] -> [a]
reverse' [] = []
reverse' (x:xs) = reverse' xs ++ [x]
repeat' :: a -> [a]
repeat' x = x : repeat' x
zip' :: [a] -> [b] -> [(a,b)]
zip' _ [] = []
zip' [] _ = []
zip' (x:xs) (y:ys) = (x,y) : zip' xs ys
day0fWeek :: Int -> String
day0fWeek n = case n of 1 -> "Sunday"
                        2 -> "Monday"
                        3 -> "Tuesday"
                        4 -> "Wednesday"
                        5 -> "Thursday"
                        6 -> "Saturday"
                        n -> error "None"
{- http://hackage.haskell.org/package/base-4.7.0.0/docs/Prelude.html -}
fibonacci k
    | k == 0  = 0
    | k == 1  = 1
    | 2 <= k  = fibonacci (k-1) + fibonacci (k-2)
    | k <= (-1) = error "Not"

multThree :: Int -> Int -> Int -> Int
multThree x y z = x*y*z
compareWH :: Int -> Ordering
compareWH = compare 100
applyTwice :: (a -> a) -> a -> a
applyTwice f x = f (f x)
zipWith' :: (a -> b -> c) -> [a] -> [b] -> [c]
zipWith' _ [] _ = []
zipWith' _ _ [] = []
zipWith' f (x:xs) (y:ys) = f x y : zipWith' f xs ys
map' :: (a -> b) -> [a] -> [b]
map' _ [] = []
map' f (x:xs) = f x : map' f xs
filter' :: (a -> Bool) -> [a] -> [a]
filter' _ [] = []
filter' p (x:xs)
    | p x       = x : filter' p xs
    | otherwise = filter' p xs
elem' :: (Eq a) => a -> [a] -> Bool
elem' a [] = False
elem' a (x:xs)
    | a == x    = True
    | otherwise = a `elem'` xs
quicksort :: (Ord a) => [a] -> [a]
quicksort [] = []
quicksort (x:xs) =
    let smallerOrEqual = [a | a <- xs, a <= x]
        larger = [a | a <- xs, a >x]
    in  quicksort smallerOrEqual ++ [x] ++ quicksort larger
largeDivisible :: Integer -> Integer
largeDivisible n = head (filter p [n,n-1..])
    where p x = x `mod` 3829 == 0
chain :: Integer -> [Integer]
chain 1 = [1]
chain n
    | even n = n : chain (n `div` 2)
    | odd n  = n : chain (n * 3 + 1)
numLongChains :: Int
numLongChains = length (filter isLong (map chain [1..100]))
    where isLong xs = length xs > 15
numLongChains' :: Int
numLongChains' = length (filter (\xs -> length xs > 15)
                               (map chain [1..100]))
flip' :: (a -> b -> c) -> b -> a -> c
flip' f = \x y -> f y x
mergesort lst =
   let merge xx yy = case (xx, yy) of
         ([], [])         -> []
         (xxs, [])        -> xxs
         ([], yys)        -> yys
         (x : xs, y : ys) -> if x < y then x : merge xs yy else y : merge xx ys
       split l = case l of
         []           -> ([], [])
         [_]          -> (l, [])
         x : y : rest -> let (xs, ys) = split rest in (x : xs, y : ys)
   in case lst of
     []  -> []
     [_] -> lst
     _   -> let (a, b) = split lst
            in merge (mergesort a) (mergesort b)
applymany :: (Eq a, Num a) => a -> (t -> t) -> t -> t
applymany 1 f x = f x
applymany n f x = f (applymany (n-1) f x)
divideByTen = (/10)
applyTwice' f x = f (f x)
sum' :: (Num a) => [a] -> a
sum' xs = foldl (\acc x -> acc + x) 0 xs
sam :: (Num a) => [a] -> a
sam = foldl (*) 1
mappy :: t -> [t -> a] -> [a]
mappy x [] = []
mappy x (f:xs) = f x : mappy x xs
first = \x-> \y-> x
pair = \a-> \b-> \z-> z a b
wordNums :: String -> [(String,Int)]
wordNums xs = map (\ws -> (head ws, length ws)) (group (sort (words xs)))
encode :: Int -> String -> String
encode offset = map (chr . (+ offset) . ord)
digitSum :: Int -> Int
digitSum = sum . map digitToInt . show
complexadd (a,b) (c,d) = (a+c,b+d)
complexsub (a,b) (c,d) = (a-c,b-d)
complexmult (a,b) (c,d) = (a*c-b*d,a*d+b*c)
complexdiv (a,b) (c,d) = ((a*c+b*d)/ccdd,(-a*d+b*c)/ccdd)
    where ccdd = c*c+d*d