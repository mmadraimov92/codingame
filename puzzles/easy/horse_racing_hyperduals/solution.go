package main

import (
	"fmt"
	"math"
	"os"
)

type horse struct {
	velocity int
	elegance int
}

func (h1 horse) compare(h2 horse) int {
	return int(math.Abs(float64(h1.velocity-h2.velocity)) + math.Abs(float64(h1.elegance-h2.elegance)))
}

func main() {
	var N int
	fmt.Scan(&N)
	fmt.Fprintln(os.Stderr, N)

	horses := make([]horse, N)

	for i := 0; i < N; i++ {
		var V, E int
		fmt.Scan(&V, &E)
		horses[i] = horse{
			velocity: V,
			elegance: E,
		}
	}

	fmt.Println(distanceBetweenClosestHorses(horses))
}

func distanceBetweenClosestHorses(horses []horse) int {
	minDistance := math.MaxInt32
	for i := 0; i < len(horses)-1; i++ {
		for j := i + 1; j < len(horses); j++ {
			distanceBetween := horses[i].compare(horses[j])
			if minDistance >= distanceBetween {
				minDistance = distanceBetween
			}
		}
	}
	return minDistance
}
