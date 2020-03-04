#![feature(proc_macro_hygiene, decl_macro)]

#[macro_use] extern crate rocket;
use rocket::response::status;
use rocket::response::content;

pub mod manage;
use crate::manage::*;

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
        token   :   "Invalid".to_string()
    }.to_json()
}

#[get("/<id>")]
fn echo_handler(id: usize) -> status::Accepted<String> {
    status::Accepted(Some(format!("id: '{}'", id)))
}

#[post("/<id>")]
fn post_handler(id: usize) -> status::Accepted<String> {
    status::Accepted(Some(format!("id: '{}'", id)))
}

#[get("/valid_check/<id>/<current_time>")]
fn valid_check(id: String, current_time:String) -> content::Json<&'static str> {
    if time_check(current_time.parse::<i64>().unwrap()) {
        ReturnType{
            status  :   "100".to_string(),
            info    :   "Invalid input".to_string(),
            token   :   "Invalid".to_string()
        }.to_json()
    } else {
        match postgres_connect_user_validation(id, current_time, 0) {
            Ok(s)
                => {
                    if s != -1 {
                        ReturnType{
                            status  :   "299".to_string(),
                            info    :   "Pass".to_string(),
                            token   :   "Invalid".to_string()
                        }.to_json()
                    } else {
                        ReturnType{
                            status  :   "400".to_string(),
                            info    :   "User Not Exist".to_string(),
                            token   :   "Invalid".to_string()
                        }.to_json()
                    }
                }
            Err(error)
                => {
                    println!("      error = {:?}", error);
                    ReturnType{
                        status  :   "800".to_string(),
                        info    :   "Default Error".to_string(),
                        token   :   "Invalid".to_string()
                    }.to_json()
                },
        }
    }
}

#[get("/login_check/<id>/<current_time>/<password_in>")]
fn login_check(id: String, current_time:String, password_in: String) -> content::Json<&'static str> {
    if time_check(current_time.parse::<i64>().unwrap()) {
        ReturnType{
            status  :   "100".to_string(),
            info    :   "Invalid input".to_string(),
            token   :   "Invalid".to_string()
        }.to_json()
    } else {
        match postgres_connect_user_validation(id.clone(), current_time.clone(), password_in.parse::<u32>().unwrap()) {
            Ok(s)
                => {
                    match s {
                        -2  =>  {
                            ReturnType{
                                status  :   "801".to_string(),
                                info    :   "Password Error".to_string(),
                                token   :   "Invalid".to_string()
                            }.to_json()
                        }
                        -1  =>  {
                            ReturnType{
                                status  :   "400".to_string(),
                                info    :   "User Not Exist".to_string(),
                                token   :   "Invalid".to_string()
                            }.to_json()
                        }
                        1   =>  {
                            ReturnType{
                                status  :   "201".to_string(),
                                info    :   "Admin User Pass".to_string(),
                                token   :   make_token(id, current_time)
                            }.to_json()
                        }
                        2   =>  {
                            ReturnType{
                                status  :   "202".to_string(),
                                info    :   "Normal User Pass".to_string(),
                                token   :   make_token(id, current_time)
                            }.to_json()
                        }
                        3   =>  {
                            ReturnType{
                                status  :   "203".to_string(),
                                info    :   "Guest User Pass".to_string(),
                                token   :   make_token(id, current_time)
                            }.to_json()
                        }
                        _   =>  {
                            ReturnType{
                                status  :   "800".to_string(),
                                info    :   "Default Error".to_string(),
                                token   :   "Invalid".to_string()
                            }.to_json()
                        }
                    }
                }
            Err(error)
                => {
                    println!("      error = {:?}", error);
                    ReturnType{
                        status  :   "800".to_string(),
                        info    :   "Default Error".to_string(),
                        token   :   "Invalid".to_string()
                    }.to_json()
                },
        }
    }
}

#[get("/token_check/<token>")]
fn token_check(token: String) -> content::Json<&'static str> {
    fn token_time_check(token: String) -> bool {
        let mut flag = true;
        let mut res:i64 = 0;
        for i in token.chars() {
            if flag && (i != '-') {
                continue;
            } else if i == '-' {
                if flag == false {
                    break;
                }
                flag = false;
                continue;
            }
            res = res * 10 + i as i64 - '0' as i64;
        }
        println!("     Extract time from token : {}", res);
        time_check(res)
    }
    fn token_get_id(token: String) -> String {
        let mut res = String::from("");
        for i in token.chars() {
            if i == '-' {
                break;
            }
            res.push(i);
        }
        println!("     Extract urid from token : {}", res);
        res
    }
    if token_time_check(token.clone()) {
        ReturnType{
            status  :   "100".to_string(),
            info    :   "Token Time Out".to_string(),
            token   :   token
        }.to_json()
    } else {
        match postgres_connect_token_validation(token_get_id(token.clone()), token.clone()) {
            Ok(s)
                => {
                    if s != -1 {
                        ReturnType{
                            status  :   "299".to_string(),
                            info    :   "Pass".to_string(),
                            token   :   token
                        }.to_json()
                    } else {
                        ReturnType{
                            status  :   "401".to_string(),
                            info    :   "Token Error".to_string(),
                            token   :   token
                        }.to_json()
                    }
                }
            Err(error)
                => {
                    println!("      error = {:?}", error);
                    ReturnType{
                        status  :   "800".to_string(),
                        info    :   "Default Error".to_string(),
                        token   :   token
                    }.to_json()
                },
        }
    }
}

fn main() {
    rocket::ignite()
        .mount("/", routes![index])
        .mount("/", routes![valid_check])
        .mount("/", routes![login_check])
        .mount("/", routes![token_check])
        .launch();
}