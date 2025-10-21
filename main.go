package main

import (
	"fmt"
	"os"
	"time"

	"golang.org/x/term"
)

type point struct {
	x int
	y int
}

type snake struct {
	body []point
	dirX int
	dirY int
}

const (
	up    int = iota
	down  int = iota
	left  int = iota
	right int = iota
)

const (
	fps         int = 15
	width       int = 60
	height      int = 30
	pixelWidth  int = width * 2
	pixelHeight int = height * 4
)

var (
	screen = make([]byte, width*height)
	player = newSnake()
)

func newSnake() *snake {
	s := snake{
		body: make([]point, 5),
		dirX: 1,
	}
	s.body[0] = point{x: 15, y: 15}
	s.body[1] = point{x: 14, y: 15}
	s.body[2] = point{x: 13, y: 15}
	s.body[3] = point{x: 12, y: 15}
	s.body[4] = point{x: 11, y: 15}
	return &s
}

func (s *snake) move() {
	length := len(s.body)
	s.body = s.body[1:]
	head := s.body[length-2]
	newPoint := point{x: head.x + s.dirX, y: head.y + s.dirY}
	s.body = append(s.body, newPoint)
}

func main() {
	fd := int(os.Stdin.Fd())

	if !term.IsTerminal(fd) {
		fmt.Fprintln(os.Stderr, "Please run from a TTY")
		os.Exit(1)
	}

	oldState, err := term.MakeRaw(fd)
	if err != nil {
		fmt.Fprintln(os.Stderr, "Failed to change TTY to raw mode")
		os.Exit(1)
	}
	defer term.Restore(fd, oldState)

	drawBorder()

	c := make(chan int)
	go handleInput(c)
	done := false
	fmt.Print("\033[?25l")     // hide cursor
	fmt.Print("\033[H\033[2J") // clear screen
	for !done {
		select {
		case input, ok := <-c:
			if !ok {
				done = true
			}
			if input == down {
				player.dirX = 0
				player.dirY = 1
			}
			if input == up {
				player.dirX = 0
				player.dirY = -1
			}
			if input == left {
				player.dirX = -1
				player.dirY = 0
			}
			if input == right {
				player.dirX = 1
				player.dirY = 0
			}
		default:
			startTime := time.Now()
			eraseSnake()
			player.move()
			drawSnake()
			renderScreen()
			elapsedTime := time.Since(startTime)
			frameTime := time.Duration(1000.0/fps) * time.Millisecond
			time.Sleep(frameTime - elapsedTime)
		}
	}
	fmt.Print("\033[?25h") // show cursor
}

func drawBorder() {
	for i := range pixelWidth {
		setPixel(i, 0, true)
		setPixel(i, pixelHeight-1, true)
	}
	for i := 1; i < pixelHeight-1; i++ {
		setPixel(0, i, true)
		setPixel(pixelWidth-1, i, true)
	}
}

func setPixel(x int, y int, on bool) {
	if x < 0 || x >= pixelWidth || y < 0 || y >= pixelHeight {
		return
	}

	groupX := x / 2
	groupY := y / 4
	dotX := x % 2
	dotY := y % 4

	pixelGroup := screen[groupY*width+groupX]
	var mask byte = 0x80 >> (dotY*2 + dotX)
	if on {
		pixelGroup |= mask
	} else {
		pixelGroup &= ^mask
	}
	screen[groupY*width+groupX] = pixelGroup
}

func renderScreen() {
	fmt.Printf("\033[%dA", height+1)
	for y := range height {
		for x := range width {
			char := screen[y*width+x]
			fmt.Printf("%c", pixelGroupRune(char))
		}
		fmt.Print("\r\n")
	}
}

func eraseSnake() {
	for _, p := range player.body {
		setPixel(p.x, p.y, false)
	}
}

func drawSnake() {
	for _, p := range player.body {
		setPixel(p.x, p.y, true)
	}
}

func handleInput(c chan<- int) {
	done := false
	buf := make([]byte, 3)
	for !done {
		n, _ := os.Stdin.Read(buf)
		switch n {
		case 1:
			switch buf[0] {
			case 'q':
				done = true
			case 'j':
				c <- down
			case 'k':
				c <- up
			case 'h':
				c <- left
			case 'l':
				c <- right
			}
		case 3:
			switch buf[2] {
			case 'A':
				c <- up
			case 'B':
				c <- down
			case 'C':
				c <- right
			case 'D':
				c <- left
			}
		}
	}
	close(c)
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
