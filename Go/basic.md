# Go language basic

## I/O

### Sample1

```Go
package main

import (
	"fmt"
	"math"
    "math/cmplx"
)

func add(x int, y int) int {
	return x + y
}

func split(sum int) (x, y int) {
	x = sum * 4 / 9
	y = sum - x
	return
}

//Named return values
func swap(x, y string) (string, string) {
	return y, x
}

var c, python, java bool

var (
	ToBe   bool       = false
	MaxInt uint64     = 1<<64 - 1
	z      complex128 = cmplx.Sqrt(-5 + 12i)
)

func main() {
    var i, j int = 1, 2
    var c, python, java = true, false, "no!"
    k := 3
    var z uint = uint(i)
    const World = "世界"

	fmt.Printf("Now you have %g problems.\n", math.Sqrt(7))
	fmt.Println(math.Pi)
    fmt.Println(add(42, 13))
    fmt.Println(split(17))
    a, b := swap("hello", "world")
	fmt.Println(a, b)
    fmt.Printf("Type: %T Value: %v\n", ToBe, ToBe)
	fmt.Printf("Type: %T Value: %v\n", MaxInt, MaxInt)
	fmt.Printf("Type: %T Value: %v\n", z, z)
}
```
