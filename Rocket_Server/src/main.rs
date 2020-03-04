#![feature(proc_macro_hygiene, decl_macro)]

#[macro_use] extern crate rocket;
//use rocket::response::status;
use rocket::response::content;
extern crate postgres;
use postgres::{Client, NoTls};
use chrono::prelude::*;
extern crate chrono;

//3 minutes check
fn time_check(time: i64) -> bool {
    let dt = Local::now();
    println!("      time compare: {} {} => {}", time, dt.timestamp_millis(), (dt.timestamp_millis() - time).abs() < 1000 * 60 * 3);
    if (dt.timestamp_millis() - time).abs() < 1000 * 60 * 3 {
        false
    } else {
        true
    }
}

//Algorithm :
//  hashstring(username, current_time) == password_in
//  && time must be in 3 minutes
fn hash_string(hashsource: String, time: String) -> u32 {
    let (mut hash, m) = (0 as u32, 49639);
    for c in hashsource.chars() {
        hash = hash * 256 + c as u32;
        hash = hash % m;
    }
    for c in time.chars() {
        hash = hash *256 + c as u32;
        hash = hash % m;
    }
    hash
}

//Connect to PostgreSQL DataBase
//  Compare password
fn postgres_connect_user_validation(id_user: String, time_in:String, password_in: u32) -> Result<i32, postgres::Error> {
    let mut client = Client::connect("host=localhost port=5432 dbname=Dot user=postgres password=123", NoTls)?;
    let mut status: i32 = -1;

    for row in client.query("SELECT password, status FROM users where id = $1", &[&id_user])? {
        let password: String = row.get(0);
        status = row.get(1);
        println!("      password compare: {} {} , {}", hash_string(password.clone(), time_in.clone()), password_in.clone(), hash_string(password.clone(), time_in.clone()) == password_in);
        if hash_string(password, time_in.clone()) != password_in {
            status = -2;
            break;
        }
    }

    Ok(status)
}

struct ReturnType {
    status  :   String,
    info    :   String,
    token   :   String,
}

impl ReturnType {
    fn to_json(&self) -> content::Json<&'static str> {
        let result= "{ \'status\':\'".to_string() + self.status.as_str() + "\', \'info\': \'" + self.info.as_str() + "\', \'token\': \'"+ self.token.as_str() + "\'}";
        content::Json(Box::leak(result.into_boxed_str()))
    }
}

#[get("/")]
fn index() -> content::Json<&'static str> {
    ReturnType{
        status  :   "200".to_string(),
        info    :   "Index".to_string(),
        token   :   "hello, index".to_string()
    }.to_json()
}

#[get("/valid_check/<id>/<current_time>")]
fn valid_check(id: String, current_time:String) -> content::Json<String> {
    let result: String;
    if time_check(current_time.parse::<i64>().unwrap()) {
        result = "  001 Invalid input".to_string();
    } else {
        match postgres_connect_user_validation(id, current_time, 0) {
            Ok(s)
                => {
                    if s != -1 {
                        result = "200 Pass".to_string();
                    } else {
                        result = "400 User Not Exist".to_string();
                    }
                }
            Err(error)
                => {
                    result = "  800 Default Error".to_string();
                    println!("      error = {:?}", error)
                },
        }
    }
    content::Json(result)
}

#[get("/login_check/<id>/<current_time>/<password_in>")]
fn login_check(id: String, current_time:String, password_in: String) -> content::Json<String> {
    let result: String;
    if time_check(current_time.parse::<i64>().unwrap()) {
        result = "  001 Invalid input".to_string();
    } else {
        match postgres_connect_user_validation(id, current_time, password_in.parse::<u32>().unwrap()) {
            Ok(s)
                => {
                    match s {
                        -2  =>  result = "  801 Password Error".to_string(),
                        -1  =>  result = "  400 User Not Exist".to_string(),
                        1   =>  result = "  201 Admin User Pass".to_string(),
                        2   =>  result = "  202 Normal User Pass".to_string(),
                        3   =>  result = "  203 Guest User Pass".to_string(),
                        _   =>  result = "  800 Default Error".to_string(),
                    }
                }
            Err(error)
                => {
                    result = "  800 Default Error".to_string();
                    println!("      error = {:?}", error)
                },
        }
    }
    content::Json(result)
}

fn main() {
    rocket::ignite()
        .mount("/", routes![index])
        .mount("/", routes![valid_check])
        .mount("/", routes![login_check])
        .launch();
}