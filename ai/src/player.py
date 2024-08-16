import math
import multiprocessing
import re
from ai.src.utils import *
from ai.src.main import main


def pathfinding(position):
    r = math.floor(math.sqrt(position))
    threshold = (r * r) + r
    result = ["Forward" for _ in range(r)]
    if position > threshold:
        result.append("Right")
        result += ["Forward" for _ in range(r)]
    else:
        result.append("Left")
        result += ["Forward" for _ in range(r)]
    return result


def print_log_in_file(message):
    with open("log.txt", "a") as f:
        f.write(message + "\n")


class Player:
    def __init__(self, host, port, name):
        self.host = host
        self.port = port
        self.client = None
        self.level = 1
        self.team = name
        self.nbr_connected = 0
        self.nb_responses = 0
        self.nb_player_at_tile = 1
        self.previous_messages = []
        self.inventory = {
            "food": 10,
            "linemate": 0,
            "deraumere": 0,
            "sibur": 0,
            "mendiane": 0,
            "phiras": 0,
            "thystame": 0
        }
        self.position = (0, 0)
        self.direction = 0
        self.vision = {
            "player": 0,
            "food": 0,
            "linemate": 0,
            "deraumere": 0,
            "sibur": 0,
            "mendiane": 0,
            "phiras": 0,
            "thystame": 0
        }
        self.view = []
        self.elevation_asked = False
        self.waiting = False
        self.non_asked_elevation = False

    def take_all_objects_at_tile(self, tile):
        tile = tile.split(' ')
        self.nb_player_at_tile = 0
        for resource in tile:
            if resource == "egg":
                continue
            if resource == "player":
                self.nb_player_at_tile += 1
                continue
            if resource == "food" or self.inventory["food"] > MINIMAL_FOOD[self.level]:
                self.take_call(resource)

    def look_call(self):
        self.client.send("Look\n")
        resp = self.client.receive()
        resp = self.check_response(resp)
        if resp[0] != "[":
            print("\033[91m Error while receiving look response \033[0m")
            return
        self.view = resp
        array = re.split(', |,', self.view.replace("[ ", "").replace(" ]", "").replace("\n", ""))
        self.view = array
        # print("array: " + str(array[0]))
        self.vision = {
            "player": array.count("player"),
            "food": array.count("food"),
            "linemate": array.count("linemate"),
            "deraumere": array.count("deraumere"),
            "sibur": array.count("sibur"),
            "mendiane": array.count("mendiane"),
            "phiras": array.count("phiras"),
            "thystame": array.count("thystame")
        }
        i = 0
        for message in self.previous_messages:
            if i == 5:
                break
            message = message.split(", ")
            if int(message[0].split(" ")[1] == 0):
                return
            else:
                i += 1
        self.take_all_objects_at_tile(array[0])

    def check_response(self, resp):
        if resp == "":
            return
        responses = resp.split("\n")[:-1]
        len_resp = len(responses)
        i = 0
        i = 0
        while i < len(responses):
            if "message" in responses[i]:
                if i == len(responses) - 1:
                    self.previous_messages.insert(0, responses[i])
                    responses = self.client.receive().split("\n")[:-1]
                    i = 0
                    continue
                else:
                    self.previous_messages.insert(0, responses[i])
                    i += 1
                    continue
            if "Elevation underway" in responses[i]:
                if i == len(responses) - 1:
                    # print("catching elev underway")
                    responses = self.client.receive().split("\n")[:-1]
                    i = 0
                    if self.elevation_asked is False:
                        self.non_asked_elevation = True
                    continue
                else:
                    i += 1
                    continue
            if "Current level:" in responses[i]:
                lvl = responses[i].replace("Current level: ", "")
                self.level = int(lvl)
                if i == len(responses) - 1:
                    if not self.elevation_asked:
                        responses = self.client.receive().split("\n")[:-1]
                        i = 0
                        continue
                    else:
                        return
                else:
                    i += 1
                    continue
            if "dead" in responses:
                print("Player is dead at level " + str(self.level))
                print_log_in_file("Player is dead at level " + str(self.level) + " with inventory: " + str(self.inventory))
                exit(0)
            return responses[i] + "\n"

    def inventory_call(self):
        self.client.send("Inventory\n")
        resp = self.client.receive()
        resp = self.check_response(resp)
        if resp[0] != "[":
            print("\033[91m Error while getting inventory \033[0m")
            return
        self.inventory = resp
        array = self.inventory.replace("[ ", "").replace(" ]", "").replace("\n", "").split(", ")
        self.inventory = {
            "food": int(array[0].split(" ")[1]),
            "linemate": int(array[1].split(" ")[1]),
            "deraumere": int(array[2].split(" ")[1]),
            "sibur": int(array[3].split(" ")[1]),
            "mendiane": int(array[4].split(" ")[1]),
            "phiras": int(array[5].split(" ")[1]),
            "thystame": int(array[6].split(" ")[1])
        }

    def forward_call(self):
        self.client.send("Forward\n")
        resp = self.client.receive()
        resp = self.check_response(resp)
        self.position = resp

    def right_call(self):
        self.client.send("Right\n")
        resp = self.client.receive()
        resp = self.check_response(resp)
        self.direction = resp

    def left_call(self):
        self.client.send("Left\n")
        resp = self.client.receive()
        resp = self.check_response(resp)
        self.direction = resp

    def broadcast_call(self, message):
        self.client.send(f"Broadcast {message}\n")
        resp = self.client.receive()
        self.check_response(resp)

    def connect_nbr_call(self):
        self.client.send("Connect_nbr\n")
        resp = self.client.receive()
        resp = self.check_response(resp)
        if resp == "ko\n":
            self.nbr_connected = -1
        if resp[:-1].isdigit():
            self.nbr_connected = int(resp)

    def fork_call(self):
        self.client.send("Fork\n")
        resp = self.client.receive()
        resp = self.check_response(resp)
        if resp == "ko\n":
            return
        n = multiprocessing.Process(target=main)
        n.start()

    def eject_call(self):
        self.client.send("Eject\n")
        resp = self.client.receive()
        self.check_response(resp)

    def take_call(self, resource):
        self.client.send(f"Take {resource}\n")
        resp = self.client.receive()
        self.check_response(resp)

    def set_call(self, resource):
        self.client.send(f"Set {resource}\n")
        resp = self.client.receive()
        self.check_response(resp)

    def incantation_call(self):
        self.client.send("Incantation\n")
        self.elevation_asked = True
        current_level = self.level
        response = self.client.receive()
        response = self.check_response(response)
        self.elevation_asked = False
        if response == "ko\n":
            return
        if current_level == self.level:
            self.client.receive()

    def move_to(self, position):
        if self.waiting is True and self.inventory["food"] >= MINIMAL_FOOD[self.level]:
            return
        path = pathfinding(position)
        for action in path:
            if action == "Forward":
                self.forward_call()
            elif action == "Right":
                self.right_call()
            elif action == "Left":
                self.left_call()

    def move_to_direction(self, direction):
        if self.waiting is True:
            return
        if direction == 0:
            # self.incantation_call()
            self.waiting = True
            return
        for action in DIRECTIONS[direction]:
            print("action: " + action)
            if action == "Forward":
                self.forward_call()
            elif action == "Right":
                self.right_call()
            elif action == "Left":
                self.left_call()

    def join_call(self):
        i = 0
        highest_level = 0
        if self.inventory["food"] < MINIMAL_FOOD[self.level]:
            return
        if len(self.previous_messages) == 0:
            return
        for message in self.previous_messages:
            if i == len(self.previous_messages) - 1:
                break
            if i == 5:
                break
            message = message.split(", ")
            split_message = message[0].split(" ")
            if int(split_message[1]) == 0 and int(message[1]) == self.level:
                self.waiting = True
                return
            else:
                if int(message[1]) == self.level:
                    self.waiting = True
                    print("joining incantation at direction: " + message[0].split(" ")[1])
                    self.move_to_direction(int(split_message[1]))
                    return
                i += 1

    def is_resource_needed(self, resource):
        if resource not in self.inventory or resource == "food":
            return False
        if self.inventory[resource] < LEVELS[self.level][resource]:
            return True
        return False

    def find_resource(self, resource):
        for i, tiles in enumerate(self.view):
            if i == 0:
                continue
            tiles = tiles.split(' ')
            for tile in tiles:
                tile = tile.strip()
                if tile == resource:
                    return i
        return -1

    def look_handler(self, view):
        if self.inventory["food"] < (MINIMAL_FOOD[self.level] + 10) and self.find_resource("food") != -1:
            food_position = self.find_resource("food")
            self.move_to(food_position)
            self.look_call()
        if self.waiting is True:
            return
        self.forward_call()

    def pass_incantation(self):
        self.inventory_call()
        if self.inventory["food"] < MINIMAL_FOOD[self.level]:
            self.waiting = False
            return
        for resource in LEVELS[self.level]:
            if resource not in self.inventory:
                continue
            if self.inventory[resource] < LEVELS[self.level][resource]:
                return
        if self.level == 8:
            return
        if self.level == 1:
            self.set_call("linemate")
            self.incantation_call()
            return
        for resource in LEVELS[self.level]:
            if resource not in self.inventory:
                continue
        if self.inventory["food"] > (MINIMAL_FOOD[self.level] + 10) and self.level > 2:
            while self.inventory["food"] > MINIMAL_FOOD[self.level]:
                self.broadcast_call(str(self.level))
                self.waiting = True
                self.inventory_call()
                self.broadcast_call(str(self.level))
                self.look_call()
                if self.nb_player_at_tile >= LEVELS[self.level]["player"]:
                    self.broadcast_call(str(self.level))
                    for resource, quantity in LEVELS[self.level].items():
                        for _ in range(quantity):
                            self.set_call(resource)
                    self.incantation_call()
                    return
        if self.nb_player_at_tile >= LEVELS[self.level]["player"]:
            if self.inventory["food"] > (MINIMAL_FOOD[self.level]):
                for resource, quantity in LEVELS[self.level].items():
                    for _ in range(quantity):
                        if self.inventory["food"] > (MINIMAL_FOOD[self.level]):
                            self.set_call(resource)
            self.incantation_call()

    def fork_handler(self):
        self.nb_responses += 1
        self.connect_nbr_call()
        if self.nbr_connected > 0:
            n = multiprocessing.Process(target=main)
            n.start()

    def game_loop(self):
        self.connect_nbr_call()
        self.fork_call()
        while True:
            self.inventory_call()
            self.look_call()
            self.pass_incantation()
            self.join_call()
            self.look_handler(self.view)
            print("Player level: " + str(self.level))
            print_log_in_file("Player level: " + str(self.level) + " inventory: " + str(self.inventory))
