#![feature(proc_macro_hygiene, decl_macro)]

#[macro_use] extern crate rocket;
use rocket::response::status;
use rocket::response::content;
extern crate postgres;
use postgres::{Client, NoTls};

fn hash_string(hashsource: String) -> u32 {
    let (mut hash, m) = (0 as u32, 9973);
    for c in hashsource.chars() {
        hash = hash * 256 + c as u32;
        hash = hash % m;
    }
    hash
}

fn postgres_connect(id_user: String, password_in: u32) -> Result<i32, postgres::Error> {
    let mut client = Client::connect("host=localhost port=5432 dbname=Dot user=postgres password=123", NoTls)?;
    let mut status: i32 = -1;

    for row in client.query("SELECT password, status FROM users where id = $1", &[&id_user])? {
        let password: String = row.get(0);
        status = row.get(1);
        if hash_string(password) != password_in {
            status = -2;
            break;
        }
    }

    Ok(status)
}

#[get("/")]
fn index() -> content::Json<&'static str> {
    content::Json("{ 'index': 'index page' }")
}

#[get("/<id>")]
fn echo_handler(id: usize) -> status::Accepted<String> {
    status::Accepted(Some(format!("id: '{}'", id)))
}

#[post("/<id>")]
fn post_handler(id: usize) -> status::Accepted<String> {
    status::Accepted(Some(format!("id: '{}'", id)))
}

#[get("/valid_check/<id>")]
fn valid_check(id: String) -> content::Json<String> {
    let result: String;
    match postgres_connect(id, 0) {
        Ok(s)
            => {
                if s != -1 {
                    result = "Pass".to_string();
                } else {
                    result = "User Not Exist".to_string();
                }
            }
        Err(error)
            => {
                result = "  Default Error".to_string();
                println!("      error = {:?}", error)
            },
    }
    content::Json(result)
}

#[get("/login/<id>/<password_in>")]
fn login_check(id: String, password_in: String) -> content::Json<String> {
    let result: String;
    match postgres_connect(id, password_in.parse::<u32>().unwrap()) {
        Ok(s)
            => {
                match s {
                    -2  =>  result = "  Password Error".to_string(),
                    -1  =>  result = "  User Not Exist".to_string(),
                    1   =>  result = "  Admin User Pass".to_string(),
                    2   =>  result = "  Normal User Pass".to_string(),
                    3   =>  result = "  Guest User Pass".to_string(),
                    _   =>  result = "  Default Error".to_string(),
                }
            }
        Err(error)
            => {
                result = "  Default Error".to_string();
                println!("      error = {:?}", error)
            },
    }
    content::Json(result)
}

fn main() {
    rocket::ignite()
        .mount("/", routes![index])
        .mount("/", routes![echo_handler])
        .mount("/", routes![post_handler])
        .mount("/", routes![valid_check])
        .mount("/", routes![login_check])
        .launch();
}