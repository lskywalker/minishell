Welcome to the 42-minishell project! This is a simple implementation of a shell that has some basic functionality, such as executing commands and handling input/output redirection.

The project is designed to be a good starting point for understanding the inner workings of a shell and how it interacts with the operating system.

To get started, clone the repository and run make to build the executable. You can then run the shell by executing the generated binary file.

The minishell supports the following features:

• Running commands

• Handling simple commands with arguments

• Handling simple commands with input/output redirection

• Handling environment variables

• Handling built-ins like cd, echo, env, exit, export, unset, and pwd

• Built-in commands are not fork and execve

• Handling signal
