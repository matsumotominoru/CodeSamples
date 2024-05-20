{- (12-0) caseを用いて、次のように定義すればよい。 -}
day0fWeek :: Int -> String
day0fWeek n = case n of 0 -> "Sunday"
                        1 -> "Monday"
                        2 -> "Tuesday"
                        3 -> "Wednesday"
                        4 -> "Thursday"
                        5 -> "Friday"
                        6 -> "Saturday"
                        n -> error "Not between 0 and 6"
{- (12-1) これはガードを用いて、次のように定義する。負の整数の時はエラーを表示するように定義する。-}
fibonacci k
    | k == 0  = 0
    | k == 1  = 1
    | 2 <= k  = fibonacci (k-1) + fibonacci (k-2)
    | k <= (-1) = error "Not natural number"
{- (12-3) これも、ガードを用いて定義する。大きい方から順に条件を書く。-}
evaluate n 
    | 101 <= n       = error "Not between 0 and 100"
    | 90 <= n        = "A+"
    | 80 <= n        = "A"
    | 70 <= n        = "B"
    | 60 <= n        = "C"
    | 0 <= n         = "D"
    | otherwise      = error "Not between 0 and 100"