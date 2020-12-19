package service

import (
	"database/sql"
	"fmt"
	_ "github.com/go-sql-driver/mysql"
	"time"
)

type User struct {
	ID       uint64
	Name     string
	Password string
}

var db, err = sql.Open("mysql", "root:1234@/users?charset=utf8")

func CheckIfDataBaseConnected() bool {
	if err != nil {
		fmt.Println(err)
	} else {
		fmt.Println("DataBase Connected")
	}
	return err != nil
}

func DataBaseDisConnect() {
	defer db.Close()
}

func GetUsersInDataBase() []User {
	var id uint64
	var name string
	var password string
	rows, err := db.Query("select user_id, user_name, user_password from userinfo")
	if err != nil {
		fmt.Println(err)
		return []User{}
	}
	users := []User{}
	for rows.Next() {
		rows.Scan(&id, &name, &password)
		users = append(users, User{id, name, password})
	}
	defer rows.Close()
	return users
}

func GetNameByIdInDataBase(id string) string {
	var name string
	rows, err := db.Query("select user_name from userinfo where user_id = \"" + id + "\"")
	if err != nil {
		fmt.Println(err)
		return "Error"
	}
	for rows.Next() {
		rows.Scan(&name)
	}
	defer rows.Close()
	if name == "" {
		name = "The user's id " + id + " is not found"
	}
	return name
}

func GetIdByNameInDataBase(name string) string {
	var id, res string
	rows, err := db.Query("select user_id from userinfo where user_name = \"" + name + "\"")
	if err != nil {
		fmt.Println(err)
		return "Error"
	}
	for rows.Next() {
		rows.Scan(&id)
		res += "{" + id + "}-"
	}
	res += "{}"
	defer rows.Close()
	if res == "{}" {
		res = "The user's name " + name + "is not found"
	}
	return res
}

func AddUserInDataBase(user User) bool {
	rows, err := db.Query("INSERT INTO userinfo (user_name, user_password, last_date) VALUES (\"" + user.Name + "\", \"" + user.Password + "\", \"" + time.Now().Format("2006-01-02 15:04:05") + "\")")
	if err != nil {
		fmt.Println(err)
		return false
	}
	defer rows.Close()
	return true
}

func AddDefaultUserInDataBase() bool {
	AddUserInDataBase(User{ID: 0, Name: "王二麻", Password: "123"})
	return true
}
