# stack-simulator-VM

This project builds upon my earlier **[https://github.com/Badprogrammer123/Stack-Simulator-With-Array]** , which focused on understanding how a stack data structure operates at a low level.
The **Stack VM** extends that foundation by turning the stack into the core of a simple *virtual machine*.
Instead of receiving interactive commands like `push` and `pop`, it now loads from a .txt file, gets decoded into an opcode, gets stored in "ram", and executed as a sequence of commands.
