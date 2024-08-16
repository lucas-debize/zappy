import argparse


def parse_args():
    parser = argparse.ArgumentParser(description='TCP/IP client for Zappy AI.')
    parser.add_argument('-p', '--port', type=int, required=True, help='Port number')
    parser.add_argument('-n', '--name', type=str, required=True, help='Name of the team')
    parser.add_argument('-H', '--host', type=str, default='localhost',
                        help='Name of the machine; localhost by default')

    return parser.parse_args()


def print_debug(message):
    with open("debug_log.txt", "a") as f:
        f.write(message + "\n")


def main():
    from ai.src.client import Client
    args = parse_args()
    client = Client(args.host, args.port, args.name + '\n')
    client.start()


if __name__ == "__main__":
    main()

