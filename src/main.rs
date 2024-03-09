use serde::{de::DeserializeOwned, Serialize};
use std::{
    env,
    io::{self, Read, Write},
    net,
};

fn main() -> io::Result<()> {
    let mut args = env::args();
    args.next();
    let mode = args.next().unwrap();
    let address = args.next().unwrap().parse().unwrap();

    match mode.as_str() {
        "client" => client(address)?,
        "server" => server(address)?,
        _ => todo!(),
    }

    Ok(())
}

fn client(address: net::SocketAddr) -> io::Result<()> {
    let mut stream = net::TcpStream::connect(address)?;

    let private_address = stream.local_addr()?;
    println!("connected to {address} from {private_address}");

    let public_address: net::SocketAddr = receive_value(&mut stream)?;
    println!("got public address {public_address}");

    let peer_address: net::SocketAddr = receive_value(&mut stream)?;
    println!("got peer address {peer_address}");

    let is_listener: bool = receive_value(&mut stream)?;
    if is_listener {
        println!("i am listener");
        let listener = net::TcpListener::bind(private_address)?;
        let mut client_stream = listener.incoming().next().unwrap()?;

        for i in 0_u32.. {
            send_value(&mut client_stream, &i)?;
            let n: u32 = receive_value(&mut client_stream)?;
            dbg!(n);
        }
    } else {
        println!("i am stream");
        let mut stream = net::TcpStream::connect(peer_address)?;

        for i in 0_u32.. {
            send_value(&mut stream, &i)?;
            let n: u32 = receive_value(&mut stream)?;
            dbg!(n);
        }
    }

    Ok(())
}

fn server(address: net::SocketAddr) -> io::Result<()> {
    let listener = net::TcpListener::bind(address)?;
    let mut clients = Vec::new();

    for stream in listener.incoming() {
        let mut stream = stream?;

        let client_address = stream.peer_addr()?;
        println!("accepted connection from {client_address}");
        send_value(&mut stream, &client_address)?;

        clients.push(stream);

        if clients.len() == 2 {
            let mut a = clients.pop().unwrap();
            let mut b = clients.pop().unwrap();

            let a_address = a.peer_addr()?;
            let b_address = b.peer_addr()?;

            println!("paired clients {a_address} and {b_address}");

            send_value(&mut a, &b_address)?;
            send_value(&mut b, &a_address)?;
            send_value(&mut a, &true)?;
            send_value(&mut b, &false)?;

            a.shutdown(net::Shutdown::Both)?;
            b.shutdown(net::Shutdown::Both)?;
        }
    }

    Ok(())
}

fn send_value<T: Serialize>(stream: &mut net::TcpStream, value: &T) -> io::Result<()> {
    let bytes = bincode::serialize(value).unwrap();
    let length = (bytes.len() as u32).to_le_bytes();
    stream.write_all(&length)?;
    stream.write_all(&bytes)?;
    stream.flush()?;
    Ok(())
}

fn receive_value<T: DeserializeOwned>(stream: &mut net::TcpStream) -> io::Result<T> {
    let mut length_bytes = [0; 4];
    stream.read_exact(&mut length_bytes)?;
    let length = u32::from_le_bytes(length_bytes);

    let mut value_bytes = vec![0; length as usize];
    stream.read_exact(&mut value_bytes)?;

    Ok(bincode::deserialize(&value_bytes).unwrap())
}
