# Pipex

Pipex is a project of the 42-school cursus.
His goal is to simulate a pipe operator in the shell.
The mandatory part takes a file as input and a file as output. The program is executed as follows: `./pipex file1 cmd1 cmd2 file2`.

This project will familiarize you with the `execve`, `dup`, `dup2`, and `fork` functions.
To do so, I strongly recommend you to watch all the videos from the course [UNIX Processes in C](https://www.youtube.com/watch?v=cex9XrZCU14&list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY) from the channel CodeVault on YouTube.

## Tips

The tricky part on this project is the management of the child and the file descriptor. As a tip that will also be useful in mini shell, I recommend you to use `dup` or `dup2` only in the child so you won’t risk losing `STDIN` or `STDOUT` in a misfunction.
In this project, I used `dup2` in `STDOUT` in the parent. But I discovered in Minishell that it is way easier to avoid it as much as possible in your code.
Except this, there is no big difficulty in this project.

Please note that this README is intended to provide a brief overview of the Pipex project and some useful tips.

Happy coding!

## Edit : Somethings wrong with the Bonus part. I'll fixe it soon!
