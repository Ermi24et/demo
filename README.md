simple shell group project

our command interpreter looks like this

-> Firstly we asked a user to enter a command by printing the prompt sign($)
-> Secondly a user enters a command to our shell, then we parsed the entered command using strtok
-> Thirdly we checked the parsed command if it starts with the special characters "/"... if it is, it means it is a binary file so, we directly pass it the execve function, because it means it is executable. but if it is not starting with "/" it means we have to find it in the environment variable and we concatenate the command to the environment variable and finally pass it to the execve function.
-> Finally we handled the errors the same as the sh shell.
 -> so our simple shell looks like this if you have any suggestions you can contact us in github.
