import socket



def tcp_server(host = '127.0.0.1', port = 5000):
  #create socket, AF_INET is IPv4, SOCK_STREAM is tcp
  with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
    #bind socket
    sock.bind((host, port))
    #listen for connection
    sock.listen()
    print("Sever listening on port 5000")
    #accept connection
    conn, addr = sock.accept() #conn is socket, addr is address info
    with conn:
      print(f"connected with {addr}")
      while True:
        data = conn.recv(1024)
        if not data:
          print("client disconnected")
          break
        message = data.decode()
        conn.sendall(message[::-1].encode()) #reverse message and send back
        #close after sending message
        if data.decode() == "end":
          print("Ending conneciton")
          break

if __name__ == "__main__":
  print("this works")
  tcp_server()