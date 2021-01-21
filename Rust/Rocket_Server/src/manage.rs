//https://rustcc.gitbooks.io/rustprimer/content/action/db/readme.html
extern crate postgres;
use postgres::{Client, NoTls};

use chrono::prelude::*;
extern crate chrono;
extern crate rand;
use rand::Rng;

//make a new token for user login
//  make_token(source: String, time: String) -> String
pub fn make_token(source: String, time: String) -> String{
    let mut rng =rand::thread_rng();
    let token = source.clone() + "-" + &time.clone() + "-" + &hash_string(source.clone(), rng.gen::<u32>().to_string()).to_string() + &hash_string(time.clone(), rng.gen::<u32>().to_string()).to_string() + &hash_string(time.clone(), source.clone()).to_string();
    match postgres_connect_token_update(source, token.clone()) {
        Err(error)
            => { println!("     error = {:?}", error); String::from("Update Failed::Server Error!") }
        _   => { println!("     update successfully"); token}
    }
}

//30 minutes check
//  time_check(time: i64) -> bool
pub fn time_check(time: i64) -> bool {
    let dt = Local::now();
    println!("     time compare:\n      in_ : {}\n      res : {}\n         => {}", time, dt.timestamp_millis(), (dt.timestamp_millis() - time).abs() < 1000 * 60 * 30);
    if (dt.timestamp_millis() - time).abs() < 1000 * 60 * 30 {
        false
    } else {
        true
    }
}

//Algorithm :
//  hashstring(username, current_time) == password_in
//  && time must be in 30 minutes
pub fn hash_string(hashsource: String, time: String) -> u32 {
    let (mut hash, m) = (0 as u32, 999983);
    for c in hashsource.chars() {
        hash = hash * 256 + c as u32;
        hash = hash % m;
    }
    for c in time.chars() {
        hash = hash * 256 + c as u32;
        hash = hash % m;
    }
    hash
}

//Connect to PostgreSQL DataBase
//  Compare password
pub fn postgres_connect_user_validation(id_user: String, time_in:String, password_in: u32) -> Result<i32, postgres::Error> {
    let mut client = Client::connect("host=localhost port=5432 dbname=Dot user=postgres password=123", NoTls)?;
    let mut status: i32 = -1;

    for row in client.query("SELECT password, status FROM users where id = $1", &[&id_user])? {
        let password: String = row.get(0);
        status = row.get(1);
        println!("     password compare:\n      in_ : {}\n      res : {}\n         => {}", password_in.clone(), hash_string(password.clone(), time_in.clone()), hash_string(password.clone(), time_in.clone()) == password_in);
        if hash_string(password, time_in.clone()) != password_in {
            status = -2;
            break;
        }
    }
    Ok(status)
}

//Connect to PostgreSQL DataBase
//  token update
pub fn postgres_connect_token_update(id_user: String, token:String) -> Result<i32, postgres::Error> {
    let mut client = Client::connect("host=localhost port=5432 dbname=Dot user=postgres password=123", NoTls)?;
    client.query("UPDATE users SET token = $1 Where id = $2", &[&token, &id_user])?;
    Ok(0)
}

//Connect to PostgreSQL DataBase
//  token validation
pub fn postgres_connect_token_validation(id_user: String, token_in:String) -> Result<i32, postgres::Error> {
    let mut client = Client::connect("host=localhost port=5432 dbname=Dot user=postgres password=123", NoTls)?;
    let mut status: i32 = -1;
    for row in client.query("SELECT token FROM users where id = $1", &[&id_user])? {
        let token: String = row.get(0);
        println!("     token compare:\n      in_ : {}\n      res : {}\n         => {}", token_in.clone(), token.clone(), token_in.clone()==token.clone());
        if token_in.clone()==token.clone() {
            status = 1;
            break;
        }
    }
    Ok(status)
}