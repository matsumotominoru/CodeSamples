{-(11-0) a=2mn,b=n^2-m^2,c=n^2+m^2 のとき、簡単な計算によって、a^2+b^2=c^2 が成り立つ。a,bはkより小さく、a,b,cが整数であることより、a=bとはなり
えないので、aがｂより小さいとすると、bはmより大きく、kより小さい。よって、次のように定義すればよい。-}
pythagoras k = [ (2*m*n,n*n-m*m,n*n+m*m) | m <- [1..k-2], n <- [m+1..k-1]]
{-a,bが互いに素であれば、3数は互いに素となるので、gcdを使って、次のように定めればよい。-}
primepythagoras k = [ (2*m*n,n*n-m*m,n*n+m*m) | m <- [1..k-2], n <- [m+1..k-1], gcd (2*m*n) (n*n-m*m) == 1]
{-(11-1)複素数の和と差は成分同士の和や差になる。また、複素数の積や割り算は、定義より次のように定めればよい。-}
complexadd (a,b) (c,d) = (a + c,b + d)
complexsub (a,b) (c,d) = (a - c,b - d)
complexmult (a,b) (c,d) = (a*c-b*d,b*c+a*d)
complexdiv (a,b) (c,d) = ((a*c+b*d)/(c^2+d^2),(b*c-a*d)/(c^2+d^2))
{- ガードを使って定義する。ただし、偏角θは、0<=θ<2πの範囲で考える。まず、z=0のときは、偏角は0、絶対値は0とする。
次に、虚部が0以上のの時は、0<=θ<=πだから、acosの値域が0からπであることから、以下のように定める。
それ以外の時、すなわち、虚部が負の時は、π<θ<2πだから、asinの値域が-π/2からπ/2であることから、それに3π/2を足して、以下のように定める。-}
polar (a,b)
    | (a,b) == (0,0)  = (0,0)
    | b >= 0          = (sqrt (a^2 + b^2), acos (a/(sqrt (a^2 + b^2))))
    | otherwise       = (sqrt (a^2 + b^2), asin (a/(sqrt (a^2 + b^2))) + 3*pi/2)
{-(11-2) それぞれの型は、以下のようになる。
*Main> :t ""
"" :: [Char]
*Main> :t ['a','b','c']
['a','b','c'] :: [Char]
*Main> :t ('a','b','c')
('a','b','c') :: (Char, Char, Char)
*Main> :t [(False,'0'),(True,'b')]
[(False,'0'),(True,'b')] :: [(Bool, Char)]
*Main> :t [tail,init,reverse]
[tail,init,reverse] :: [[a] -> [a]]
*Main> -}
{-(11-3)Boundedに属する型は5つあり、それぞれのminBoundとmaxBoundの値は以下のようになる。
*Main> minBound :: Ordering
LT
*Main> maxBound :: Ordering
GT
*Main> minBound :: Int
-2147483648
*Main> maxBound :: Int
2147483647
*Main> maxBound :: Char
'\1114111'
*Main> minBound :: Char
'\NUL'
*Main> minBound :: Bool
False
*Main> maxBound :: Bool
True
*Main> maxBound :: ()
()
*Main> minBound :: ()
()　　-}
