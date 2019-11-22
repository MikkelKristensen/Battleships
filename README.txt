===============================================
Programming of Complex Software Systems

Battleships:

By Frederik Aarestrup Carlsen and Mikkel Tøt
===============================================
How to run:

The game is set to run on localhost by default, so simply do all of these steps on one computer.

1. Run the "server.exe" file. This has to run but can be minimized after starting it.

2. Open "client.exe" twice. 

After ship placement, the clients will the connect to the server and the game will initate.

===============================================
How to play:

The rules of the game are very similar to the original battleship, though with a few tweeks.

The players must first, each, place down their battleships.

The client will state for the player, what size ship they need to place.

First, enter a X coordiante and press enter, then enter a Y coordinate and press enter, lastly, write the direction you whish for the ship to be placed (up/down/left/right). For example: 

X = 3, Y = 8, Direction = Up.

The player will then see the ship placed on their board, and is asked to place the next ship until all four are placed.

When both players have set their ships, the attacking phase begins.

Both players will enter the x and y coordinates for where they whish to attack the other player.

Furthermore, they will be asked wheater they whish to use their "Super Attack", which is a devastating 3x3 attack that can only be used once.

If your opponent hit your ship, it will be marked with an X. If you hit an enemy ship, you are greeted with a "You hit!" message.

When a player has destroyed all of the enemy ships, they win.
