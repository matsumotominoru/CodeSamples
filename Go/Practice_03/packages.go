package main

import (
	"fmt"
	"math"
	"math/rand"
)

//Notice that the type comes after the variable name
//shortened x int , y int
func add(x, y int) int {
	return x + y
}

//A function can return any number of results
func swap(x, y string) (string, string) {
	return y, x
}

//Named return values are treated as variables defined at the top of the function.
func split(sum int) (x, y int) {
	x = sum * 4 / 9
	y = sum - x
	//"naked" return should be used only in short functions.
	return
}

func main() {
	//Packages
	fmt.Println("Random number:", rand.Intn(10))
	//Imports
	fmt.Printf("Now you have %g problems\n", math.Sqrt(7))
	//Exported names
	//When importing a package, you can refer only to its exported names that is begun with a capital letter.
	//Any "unexported" names are not accessible from outside the package.
	fmt.Println(math.Pi)
	//Functions
	fmt.Println(add(42, 13))
	//Multiple functions
	fmt.Println(swap("hello", "world"))
	//Named return value
	fmt.Println(split(17))
}
