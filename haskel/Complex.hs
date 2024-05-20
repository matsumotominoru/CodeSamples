module Complex
( add
, sub
, multiply
, divide
) where


add :: (Num t, Num t1) => (t, t1) -> (t, t1) -> (t, t1)
add (a,b) (c,d) = (a+c,b+d)


sub :: (Num t, Num t1) => (t, t1) -> (t, t1) -> (t, t1)
sub (a,b) (c,d) = (a-c,b-d)


multiply :: Num t => (t, t) -> (t, t) -> (t, t)
multiply (a,b) (c,d) = (a*c-b*d,a*d+b*c)


divide :: Fractional t => (t, t) -> (t, t) -> (t, t)
divide (a,b) (c,d) = ((a*c+b*d)/ccdd,(-a*d+b*c)/ccdd)
    where ccdd = c*c+d*d
 