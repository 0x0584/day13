// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   archid-.go                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: archid- <archid-tudent.1337.ma>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2024/11/24 00:47:45 by archid-           #+#    #+#             //
//   Updated: 2024/11/24 12:43:55 by archid-          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

package main

import "fmt"
import "strings"
import "strconv"
import "io/ioutil"
import "net/http"
import "time"

func sendRequest(request string, buffer chan string) {
	resp, err := http.Get(request)
	if err != nil {
		return
	}
	defer resp.Body.Close()

	body, err := ioutil.ReadAll(resp.Body)
	if err != nil {
		return
	}
	buffer <- string(body)
}

func parseResponse(response string, buffer chan string) {
	var id, r, g, b int
	for _, part := range strings.Split(strings.Split(string(response), "-")[0], ",") {
		keyval := strings.Split(part, "=")
		switch keyval[0] {
		case "id":
			id, _ = strconv.Atoi(keyval[1])
		case "r":
			r, _ = strconv.Atoi(keyval[1])
		case "g":
			g, _ = strconv.Atoi(keyval[1])
		case "b":
			b, _ = strconv.Atoi(keyval[1])
		}
	}
	buffer <- fmt.Sprintf("http://0.0.0.0:8080/?id=%d&resp=%s",
		id, fmt.Sprintf("%02x%02x%02x", r, g, b))
}

func main() {
	buffer := make(chan string)
	for i := 0; i < 100; i++ {
		start := time.Now()
		go sendRequest("http://0.0.0.0:8080/", buffer)
		go parseResponse(<-buffer, buffer)
		go sendRequest(<-buffer, buffer)
		fmt.Printf("%16v > %s\n", time.Since(start), <-buffer)
	}
}
