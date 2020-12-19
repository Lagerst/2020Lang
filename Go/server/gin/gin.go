package main

import (
	"github.com/gin-gonic/gin"
	"./service"
)

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

func Handle(r *gin.Engine, httpMethods []string, relativePath string, handlers ...gin.HandlerFunc) gin.IRoutes {
	var routes gin.IRoutes
	for _, httpMethod := range httpMethods {
		routes = r.Handle(httpMethod, relativePath, handlers...)
	}
	return routes
}

func main() {
	service.CheckIfDataBaseConnected()
	r := gin.Default()
	r.GET("/", func(context *gin.Context) {
		context.JSON(200, gin.H{
			"Hi": "Simple Gin Server",
		})
	})
	r.GET("/GetUsers", func(context *gin.Context) {
		context.JSON(200, service.GetUsersInDataBase())
	})
	r.GET("/AddUser", func(context *gin.Context) {
		if (context.Query("username") != "" && context.Query("password") != "") {
			context.JSON(200, service.AddUserInDataBase(service.User{
				ID: 0,
				Name: context.Query("username"),
				Password: context.Query("password")}))
		} else {
			context.JSON(200, "AddUser Fail: Invalid Argument;")
		}
	})
	r.POST("/AddUser", func(context *gin.Context) {
		if (context.Query("username") != "" && context.Query("password") != "") {
			context.JSON(200, service.AddUserInDataBase(service.User{
				ID: 0,
				Name: context.Query("username"),
				Password: context.Query("password")}))
		} else {
			context.JSON(200, "AddUser Fail: Invalid Argument;")
		}
	})
	r.GET("/GetNameById/:id", func(context *gin.Context) {
		context.String(200, service.GetNameByIdInDataBase(context.Param("id")))
	})
	r.GET("/GetIdByName/*username", func (context *gin.Context)  {
		context.String(200, service.GetIdByNameInDataBase(context.Param("username")[1:]))
	})
	Handle(r, []string{"GET", "POST"}, "/AddDefaultUser", func(context *gin.Context) {
		service.AddDefaultUserInDataBase()
		context.JSON(200, service.GetUsersInDataBase())
	})

	r.Run(":8080")

	service.DataBaseDisConnect()
}
