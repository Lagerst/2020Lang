package main

import (
	"./util"
	"fmt"
	"io"
	"io/ioutil"
	"log"
	"net/http"
	"os"
	"time"
)

var index string

func main() {
	var bytes []byte
	var err error
	bytes, err = ioutil.ReadFile(util.GetParentDirectory(util.CurrentFile()) + "/index.html")
	index = string(bytes)
	if err != nil {
		log.Printf("读取文件失败:%#v", err)
		return
	}

	fmt.Println("Server Started on 8888")

	http.HandleFunc("/index", Index)
	http.HandleFunc("/upload", ProcessImage)

	log.Fatal(http.ListenAndServe(":8888", nil))
}

func Index(w http.ResponseWriter, r *http.Request) {
	fmt.Println("Index Requested")
	w.Header().Set("Content-Type", "text/html; charset=utf-8")
	fmt.Fprint(w, index)
}

func ProcessImage(w http.ResponseWriter, r *http.Request) {
	fmt.Println("ProcessImage Requested")

	defer r.Body.Close()
	out, err := os.Create("/tmp/" + time.Now().Format("2006-01-02 15:04:05"))
	if err != nil {
		fmt.Fprintf(w, "Failed to open the file for writing")
		return
	}
	defer out.Close()
	defer os.Remove(out.Name())

	_, err = io.Copy(out, r.Body)
	if err != nil {
		fmt.Fprintln(w, err)
	}

	res := "测量结果为 " + util.GetDotValue(out.Name()) + "\n" + "版权所有 © 2021 南京金印龙智能技术有限公司";
	
	// the header contains useful info, like the original file name
	fmt.Fprintf(w, res)
}
