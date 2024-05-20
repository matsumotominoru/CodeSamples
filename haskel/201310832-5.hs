{-(13-1) これは、再帰的に定義すればよい。n=1のときを定義し、その次に一般のnに対して、n-1の時のapplymanyを用いて定義する。-}
applymany :: (Eq a, Num a) => a -> (t -> t) -> t -> t
applymany 1 f x = f x
applymany n f x = f (applymany (n-1) f x)