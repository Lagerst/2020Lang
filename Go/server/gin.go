package main

import (
	"fmt"
	"strconv"
	"database/sql"
	"github.com/gin-gonic/gin"
	_ "github.com/go-sql-driver/mysql"
)

type User struct {
	ID       uint64
	Name     string
	Password string
}

// // Any registers a route that matches all the HTTP methods.
// // GET, POST, PUT, PATCH, HEAD, OPTIONS, DELETE, CONNECT, TRACE.
// func (group *RouterGroup) Any(relativePath string, handlers ...HandlerFunc) IRoutes {
// 	group.handle("GET", relativePath, handlers)
// 	group.handle("POST", relativePath, handlers)
// 	group.handle("PUT", relativePath, handlers)
// 	group.handle("PATCH", relativePath, handlers)
// 	group.handle("HEAD", relativePath, handlers)
// 	group.handle("OPTIONS", relativePath, handlers)
// 	group.handle("DELETE", relativePath, handlers)
// 	group.handle("CONNECT", relativePath, handlers)
// 	group.handle("TRACE", relativePath, handlers)
// 	return group.returnObj()
// }

var db, err = sql.Open("mysql", "root:1234@/users?charset=utf8")

func Handle(r *gin.Engine, httpMethods []string, relativePath string, handlers ...gin.HandlerFunc) gin.IRoutes {
	var routes gin.IRoutes
	for _, httpMethod := range httpMethods {
		routes = r.Handle(httpMethod, relativePath, handlers...)
	}
	return routes
}

func AddUserInDataBase(user User) []User {
	fmt.Println("Add::received usename: " + user.Name)
	fmt.Println("Add::received password: " + user.Password)
	return GetUsersInDataBase()
}

func GetUsersInDataBase() []User {
	var id uint64
    var name string
    var password string
    rows, err := db.Query("select user_id, user_name, user_password from userinfo")
    if err != nil {
        fmt.Println(err)
	}
	users := []User{}
    for rows.Next() {
        rows.Scan(&id, &name, &password)
		users = append(users, User{id, name, password});
    }
    defer rows.Close()
	return users
}

func main() {
	if err != nil {
		fmt.Println(err)
	}
	users := []User{{ID: 0, Name: "张三", Password: ""}, {ID: 1, Name: "李四", Password: ""}}
	var id uint64 = 2
	r := gin.Default()
	r.GET("/", func(context *gin.Context) {
		context.JSON(200, gin.H{
			"Hi": "Simple Gin Server",
		})
	})
	r.GET("/GetUsers", func(context *gin.Context) {
		context.JSON(200, GetUsersInDataBase())
	})
	r.GET("/AddUser", func(context *gin.Context) {
		if (context.Query("username") != "" && context.Query("password") != "") {
			context.JSON(200, AddUserInDataBase(User{
				ID: 0,
				Name: context.Query("username"),
				Password: context.Query("password")}))
		} else {
			context.JSON(200, "AddUser Fail: Invalid Argument;")
		}
	})
	r.POST("/AddUser", func(context *gin.Context) {
		if (context.Query("username") != "" && context.Query("password") != "") {
			context.JSON(200, AddUserInDataBase(User{
				ID: 0,
				Name: context.Query("username"),
				Password: context.Query("password")}))
		} else {
			context.JSON(200, "AddUser Fail: Invalid Argument;")
		}
	})
	r.GET("/GetNameById/:id", func(context *gin.Context) {
		id := context.Param("id")
		for i := 0; i < len(users); i++{
			if (strconv.Itoa(int(users[i].ID)) == id) {
				context.String(200, "The user name is %s", users[i].Name)
				return
			}
		}
        context.String(200, "The user id is not found")
	})
	r.GET("/GetIdByName/*username", func (context *gin.Context)  {
		username := context.Param("username")
		for i := 0; i < len(users); i++{
			if (users[i].Name == username[1:]) {
				context.String(200, "The user id is %d", users[i].ID)
				return
			}
		}
		context.String(200, "The user id is not found")
	})
	Handle(r, []string{"GET", "POST"}, "/AddDefaultUser", func(context *gin.Context) {
		users = append(users, User{ID: id, Name: "王二麻"})
		id++
		context.JSON(200, users)
	})

	r.Run(":8080")

	defer db.Close()
}
