use std::{env, io, net};

fn main() -> io::Result<()> {
    let mut args = env::args();
    args.next();
    let mode = args.next().unwrap();
    let adr = args.next().unwrap().parse().unwrap();

    match mode.as_str() {
        "client" => client(addr)?,
        "server" => server(addr)?,
    }

    Ok(())
}

fn client(addr: net::SocketAddr) -> io::Result<()> {}

fn server(addr: net::SocketAddr) -> io::Result<()> {}
