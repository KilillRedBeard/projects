package main

import (
	"fmt"
	"net/http"
	"net/url"
	"os"
	"path/filepath"
	"time"

	"golang.org/x/net/html"
)

var elements []Element

type Element struct {
	name   string
	answer string
}

func searchElement(name string) bool {
	for c := 0; c < len(elements); c += 1 {
		if elements[c].name == name {
			return true
		}
	}

	return false
}

func succsess() {
	fmt.Println("Test Complited")
	os.Exit(2)
}

func postAnswer(url string, cookies *http.Cookie) *http.Request {
	request, err := http.NewRequest("POST", url, nil)

	if err != nil {
		panic(err)
	}

	request.AddCookie(cookies)

	return request
}

func getNode(responce *http.Response, err error) (*html.Node, string) {
	if err != nil {
		panic(err)
	}

	doc, err := html.Parse(responce.Body)
	url := responce.Request.URL.String()

	if err != nil {
		panic(err)
	}

	return doc, url
}

func createPostRequest() string {
	var request string = "?"

	if len(elements) != 0 {
		for c := 0; c < len(elements); c += 1 {
			request += elements[c].name + "=" + elements[c].answer + "&"
		}
	}

	request = request[:len(request)-1]

	return request
}

func parse_html(n *html.Node) {
	request := ""

	if n.Type == html.ElementNode && n.Data == "a" {
		for _, element := range n.Attr {
			if element.Key == "href" {
				if element.Val == "/" {
					succsess()
				} else {
					fmt.Println("LINK: ", element.Val)
					request += element.Val
				}
			}

			request = request + element.Val
		}
	} else if n.Type == html.ElementNode && n.Data == "input" {
		if n.Attr[0].Key == "type" && n.Attr[0].Val == "radio" {
			if cap(elements) != 0 && searchElement(n.Attr[1].Val) {
				for c := 0; c < len(elements); c += 1 {
					if elements[c].name == n.Attr[1].Val {
						if len(elements[c].answer) < len(n.Attr[2].Val) {
							elements[c].answer = n.Attr[2].Val
						}
					}
				}

			} else {
				radio := Element{name: n.Attr[1].Val, answer: n.Attr[2].Val}
				elements = append(elements, radio)
			}
		} else if n.Attr[0].Key == "type" && n.Attr[0].Val == "text" {
			text := Element{name: n.Attr[1].Val, answer: "test"}
			elements = append(elements, text)
		}

	} else if n.Type == html.ElementNode && n.Data == "select" {
		sel := Element{name: n.Attr[0].Val, answer: ""}

		for op := n.FirstChild; op != nil; op = op.NextSibling {
			if op.Type == html.ElementNode && op.Data == "option" {
				if len(sel.answer) < len(op.Attr[0].Val) {
					sel.answer = op.Attr[0].Val
				}
			}
		}

		elements = append(elements, sel)
	}

	for c := n.FirstChild; c != nil; c = c.NextSibling {
		parse_html(c)
	}
}

func main() {

	var host string

	if len(os.Args) != 2 {
		host = "http://test.youplace.net"
		fmt.Println("Usage: ", filepath.Base(os.Args[0]), " URL")
	} else {
		host = os.Args[1]
	}

	URL, err := url.Parse(host)

	if err != nil {
		fmt.Println("Error in parsing: ", err)
		return
	}

	c := &http.Client{
		Timeout: 15 * time.Second,
	}

	request, err := http.NewRequest("GET", URL.String(), nil)

	if err != nil {
		fmt.Println("Get: ", err)
		return
	}

	httpData, err := c.Do(request)

	if err != nil {
		fmt.Println("Error in Do(): ", err)
		return
	}

	fmt.Println("Status code:", httpData.Status)

	cookies := httpData.Cookies()

	doc1, err := html.Parse(httpData.Body)

	if err != nil {
		panic(err)
	}

	parse_html(doc1)

	req, err := http.NewRequest("GET", URL.String()+"/question/1", nil)

	if err != nil {
		fmt.Println("Get: ", err)
		return
	}

	req.AddCookie(cookies[0])

	for true {
		node, url := getNode(c.Do(req))
		parse_html(node)
		fmt.Println(url)
		req = postAnswer(url+createPostRequest(), cookies[0])
	}
}
