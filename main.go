package main

import "fmt"

const (
	width  int = 120
	height int = 30
)

func main() {
	for range height {
		for range width {
			fmt.Print("\u28FF")
		}
		fmt.Println()
	}
}
