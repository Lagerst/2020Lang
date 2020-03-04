# Rocket Server

A Simple Server Practice based on Rocket

    cargo run

🔧 Configured for developmen
    => address: localhost
    => port: 8000
    => log: normal
    => workers: 8
    => secret key: generated
    => limits: forms = 32KiB
    => keep-alive: 5s
    => tls: disabled
🛰   Mounting /
    => GET / (index)
🛰   Mounting /:
    => GET /valid_check/<id>/<current_time> (valid_check)
🛰   Mounting /:
    => GET /login_check/<id>/<current_time>/<password_in> (login_check)
🛰   Mounting /:
    => GET /token_check/<token> (token_check)
    Rocket has launched from http://localhost:8000
