# Go language basic

## printf

```Go
package main

import (
	"fmt"
	"math"
)

func main() {
    var a, b int = 1, 2

	//cast
	var i int = 5
    var z uint = uint(i)

    const World = "世界"

	fmt.Printf("Now you have %f problems.\n", math.Sqrt(7))
	fmt.Println(a, b)
    fmt.Printf("Type: %T Value: %v\n", World, World)
	fmt.Printf("Type: %T Value: %v\n", z, z)
}
```

## function call

```Go
package main

import (
	"fmt"
)

func add(x int, y int) int {
	return x + y
}

func split(sum int) (x, y int) {
	x = sum * 4 / 9
	y = sum - x
	return
}

func swap(x, y string) (string, string) {
	return y, x
}


func main() {

    fmt.Println(add(42, 13))

	//Named return values
    fmt.Println(split(17))

	//Multiple return values
    a, b := swap("hello", "world")
	fmt.Println(a,b)
}
```
