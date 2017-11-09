package google_dialog_flow_worker

import (
	"net/http"
	"os/exec"
	"log"
	"encoding/json"
	"os"
)

type MyResponse struct {
	Speech string `json:"speech"`
	DisplayText string `json:"displayText"`
}

func handler(w http.ResponseWriter, r *http.Request) {

	out, err := exec.Command("am", "start" , "org.xbmc.kodi/.Splash").Output()
	//out, err := exec.Command("ls").Output()

	log.Printf("Output: %s", out)
	if err != nil {
		log.Printf("Command finished with error: %v", err)
	}
	myResponse := MyResponse{"Yes my lord", "Yes my lord"}


	w.Header().Set("Content-Type", "application/json")
	w.WriteHeader(http.StatusCreated)
	json.NewEncoder(w).Encode(myResponse)
}

func main() {


	certFile := os.Getenv("certsPath")+"/server.crt"
	certKey := os.Getenv("certsPath")+"/server.key"

	log.Print("Server is running")
	http.HandleFunc("/", handler)
	err := http.ListenAndServeTLS(":64909", certFile, certKey, nil)
	if err != nil {
		log.Fatal("ListenAndServe: ", err)
	}

}
