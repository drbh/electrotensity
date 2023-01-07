package main

import (
	"log"
	"strconv"
	"strings"

	"github.com/tarm/serial"
)

func main() {
	c := &serial.Config{Name: "/dev/cu.usbserial-1410", Baud: 115200}
	s, err := serial.OpenPort(c)
	if err != nil {
		log.Fatal(err)
	}

	for {
		buf := make([]byte, 32)
		n, err := s.Read(buf)
		if err != nil {
			log.Fatal(err)
		}
		line := string(buf[:n])
		// split line into words
		words := strings.Fields(line)
		// convert words to floats
		var floats []float64
		for _, word := range words {
			f, err := strconv.ParseFloat(word, 64)
			if err != nil {
				log.Fatal(err)
			}
			floats = append(floats, f)
		}

		measurement := floats[0]

		if measurement > 8.0 {
			log.Print("Power is ON \t-\t", measurement)
		} else {
			log.Print("Power is OFF \t-\t", measurement)
		}

		// log.Print(floats)
	}

}
