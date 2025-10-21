package main

import "fmt"

const (
	width  int = 60
	height int = 30
)

var screen = make([]byte, width*height)

func main() {
	for y := range height {
		for x := range width {
			screen[y*width+x] = 0xFF
		}
	}

	drawScreen()
}

func drawScreen() {
	for y := range height {
		for x := range width {
			pixelGroup := screen[y*width+x]
			fmt.Printf("%c", pixelGroupRune(pixelGroup))
		}
		fmt.Println()
	}
}

func pixelGroupRune(pixelGroup byte) rune {
	var output rune = 0x2800
	output |= rune(pixelGroup&0b1000_0000) >> 7
	output |= rune(pixelGroup&0b0100_0000) >> 3
	output |= rune(pixelGroup&0b0010_0000) >> 4
	output |= rune(pixelGroup & 0b0001_0000)
	output |= rune(pixelGroup&0b0000_1000) >> 1
	output |= rune(pixelGroup&0b0000_0100) << 3
	output |= rune(pixelGroup&0b0000_0010) << 5
	output |= rune(pixelGroup&0b0000_0001) << 7
	return output
}
