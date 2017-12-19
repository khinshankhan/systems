# that-forking-server
That Forking Server

Create a working forking server program, as described in class yesterday.

    * Check out the files in the src/ directory on https://github.com/mks65/fserver.
        * COPY them, do not move them!
    * Fill in the function definitions for server_setup and server_connect in pipe_networking.c.
    * Fill in the body of forking_server.c to implement a forking server program.
        * Use server_setup and server_connect, not server_handshake
        * Include a separate function for the subserver
        * Write your own process function
        * Make and test!