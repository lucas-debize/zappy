import argparse
import logging
import socket
from ai.src.player import Player


class Client:
    def __init__(self, host, port, name):
        self.host = host
        self.port = port
        self.name = name
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    def connect(self):
        server_address = (self.host, self.port)
        print(f"Connecting to {server_address}")
        self.sock.connect(server_address)
        receive = self.sock.recv(1024)
        if receive.decode() == "ko\n":
            print("Connection failed")
            self.close()
            exit(0)
        print(f"Received: {receive.decode()}")
        self.sock.send(self.name.encode())
        receive = self.sock.recv(1024)
        if receive.decode() == "ko\n":
            print("Connection failed")
            self.close()
            exit(0)
        print(f"Received: {receive.decode()}")

    def send(self, message):
        try:
            print(f"Sending: {message}")
            self.sock.sendall(message.encode())
        except Exception as e:
            logging.error(f"Error while sending message: {e}")
            self.close()
            exit(0)

    def receive(self):
        print("Waiting for message")
        try:
            data = self.sock.recv(4096)
            if data:
                print(f"Received: \"{data.decode()}\"")
                return data.decode()
        except Exception as e:
            logging.error(f"Error while receiving message: {e}")
            self.close()
            exit(0)

    def close(self):
        print("Closing connection")
        self.sock.close()

    def start(self):
        self.connect()
        player = Player(self.host, self.port, self.name)
        player.client = self
        player.game_loop()










