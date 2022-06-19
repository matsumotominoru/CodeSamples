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

## Flow control

```Go
package main

import (
	"fmt"
	"math"
	"time"
	"runtime"
	)

func main() {
	//for loop
	sum := 0
	for i := 0; i < 10; i++ {
		sum += i
	}
	fmt.Println(sum)

	//while loop
	sum = 1
	for sum < 1000 {
		sum += sum
	}
	fmt.Println(sum)

	//If
	if v := math.Pow(2, 5); v < 50 {
		fmt.Printf("%v is lower than 50\n", v)
	} else {
		fmt.Printf("%v is equal or greater than 50\n", v)
	}
	// can't use v here, though

	//defer stacked
	fmt.Println("defer:counting")

	for i := 0; i < 10; i++ {
		defer fmt.Println(i)
	}

	fmt.Println("defer:done")

	//switch
	switch os := runtime.GOOS; os {
	case "darwin":
		fmt.Println("OS X.")
	case "linux":
		fmt.Println("Linux.")
	default:
		// freebsd, openbsd,
		// plan9, windows...
		fmt.Printf("%s.\n", os)
	}

	//switch
	today := time.Now().Weekday()
	switch time.Saturday {
	case today + 0:
		fmt.Println("Today.")
	case today + 1:
		fmt.Println("Tomorrow.")
	case today + 2:
		fmt.Println("In two days.")
	default:
		fmt.Println("Too far away.")
	}

	//Alternative to long if-else statement
	t := time.Now()
	switch {
	case t.Hour() < 12:
		fmt.Println("Good morning!")
	case t.Hour() < 17:
		fmt.Println("Good afternoon.")
	default:
		fmt.Println("Good evening.")
	}
}
```
