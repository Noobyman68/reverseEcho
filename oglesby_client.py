import socket

def tcp_client(host = '127.0.0.1', port = 5000):
  with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
    sock.connect((host, port))
    print("Connect to server. Type \"end\" to end connection")

    while True:
      message = input("Enter message: ")
      sock.sendall(message.encode())
      data = sock.recv(1024)
      print("reversed message:" + data.decode())
      if(message == "end"):
        print("Closing connection")
        break

if __name__ == "__main__":
  print("this works")
  tcp_client()