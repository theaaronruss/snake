package main

import (
	"fmt"
	"os"
	"os/signal"
	"syscall"
	"time"
)

const (
	fps         int = 15
	width       int = 60
	height      int = 30
	pixelWidth  int = width * 2
	pixelHeight int = height * 4
)

type point struct {
	x int
	y int
}

var screen = make([]byte, width*height)
var snake []point

func main() {
	snake = append(snake, point{x: 11, y: 15})
	snake = append(snake, point{x: 12, y: 15})
	snake = append(snake, point{x: 13, y: 15})
	snake = append(snake, point{x: 14, y: 15})
	snake = append(snake, point{x: 15, y: 15})
	for _, p := range snake {
		setPixel(p.x, p.y)
	}

	// hide cursor
	fmt.Print("\033[?25l")

	// show cursor on exit
	defer fmt.Print("\033[?25h")

	// make sure cursor is shown again even when not exiting normally
	c := make(chan os.Signal, 1)
	signal.Notify(c, os.Interrupt, syscall.SIGTERM)
	go func() {
		<-c
		fmt.Print("\033[?25h")
		os.Exit(1)
	}()

	for {
		startTime := time.Now()
		drawScreen()
		clearSnake()
		head := snake[len(snake)-1]
		// fmt.Printf("X: %d Y: %d\n", head.x, head.y)
		snake = snake[1:]
		// fmt.Printf("len: %d\n", len(snake))
		snake = append(snake, point{x: head.x + 1, y: head.y})
		drawSnake()
		elapsedTime := time.Since(startTime)
		sleepTime := 1000.0/fps - int(elapsedTime.Milliseconds())
		time.Sleep(time.Millisecond * time.Duration(sleepTime))
	}
}

func setPixel(x int, y int) {
	if x < 0 || x >= pixelWidth || y < 0 || y >= pixelHeight {
		return
	}

	groupX := x / 2
	groupY := y / 4
	dotX := x % 2
	dotY := y % 4
	dot := screen[groupY*width+groupX]
	dot |= 0x80 >> (dotY*2 + dotX)
	screen[groupY*width+groupX] = dot
}

func clearPixel(x int, y int) {
	if x < 0 || x >= pixelWidth || y < 0 || y >= pixelHeight {
		return
	}

	groupX := x / 2
	groupY := y / 4
	dotX := x % 2
	dotY := y % 4
	dot := screen[groupY*width+groupX]
	var change byte = 0x80 >> (dotY*2 + dotX)
	dot &= ^change
	screen[groupY*width+groupX] = dot
}

func clearSnake() {
	for _, p := range snake {
		clearPixel(p.x, p.y)
	}
}

func drawSnake() {
	for _, p := range snake {
		setPixel(p.x, p.y)
	}
}

func drawScreen() {
	for i := range pixelWidth {
		setPixel(i, 0)
		setPixel(i, pixelHeight-3)
	}
	for i := 1; i < pixelHeight-2; i++ {
		setPixel(0, i)
		setPixel(pixelWidth-1, i)
	}

	// move cursor up to redraw screen
	fmt.Printf("\033[%dA", height+1)

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
