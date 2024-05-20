{- (13-3) mapの定義をまねて、次のように定義すればよい。 -}
mappy :: t -> [t -> a] -> [a]
mappy x [] = []
mappy x (f:xs) = f x : mappy x xs
