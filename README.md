# minishell

### `0. Instruction`
*As beautiful as a shell (23.08.15 ~ 23.09.17)*

|NAME|PART|
|------|---|
|seokklee|builtin, execute|
|youyoon|parsing, signal handling|


* * *
### `1. Evaluation Logs`

**1차 (fastshell)<br>**
*23.09.07* : cd error

**2차 (안 Fast shell)<br>**
*23.09.12* : memory leak

**3차 (천년만년 돌고돌아 Shell) : REAL FIN...😭<br>**
*23.09.17*


* * *
### `2. SUBJECT`

<br>

# **Chapter 1**

## Introduction

<br>

##### _The existence of shells is linked to the very existence of IT. At the time, all coders agreed that `communicating with a computer using aligned 1/0 switches was seriously irritating`. It was only logical that they came up with the idea to `communicate with a computer using interactive lines of commands in a language somewhat close to english`._


##### _With `Minishell`, you’ll be able to travel through time and come back to problems people faced when `Windows` didn’t exist._

<br>

# Chapter 2

## Common Instructions

<br>

- ##### _Your project must be written in accordance with the Norm. If you have bonus files/functions, they are included in the norm check and you will receive a 0 if there is a norm error inside._


- ##### _Your functions should not quit unexpectedly (segmentation fault, bus error, double free, etc) apart from undefined behaviors. If this happens, your project will be considered non functional and will receive a 0 during the evaluation._



- ##### _All heap allocated memory space must be properly freed when necessary. No leaks will be tolerated._


- ##### _If the subject requires it, you must submit a Makefile which will compile your source files to the required output with the flags -Wall, -Wextra and -Werror, and your Makefile must not relink._

  

- ##### _Your Makefile must at least contain the rules $(NAME), all, clean, fclean and re._

 
- ##### _To turn in bonuses to your project, you must include a rule bonus to your Makefile, which will add all the various headers, librairies or functions that are forbidden on the main part of the project. Bonuses must be in a different file \_bonus.{c/h}. Mandatory and bonus part evaluation is done separately._


- ##### _If your project allows you to use your libft, you must copy its sources and its associated Makefile in a libft folder with its associated Makefile. Your project’s Makefile must compile the library by using its Makefile, then compile the project._


- ##### _We encourage you to create test programs for your project even though this work won’t have to be submitted and won’t be graded. It will give you a chance to easily test your work and your peers’ work. You will find those tests especially useful during your defence. Indeed, during defence, you are free to use your tests and/or the tests of the peer you are evaluating._


- ##### _Submit your work to your assigned git repository. Only the work in the git repository will be graded. If Deepthought is assigned to grade your work, it will be done after your peer-evaluations. If an error happens in any section of your work during Deepthought’s grading, the evaluation will stop._


<br>

# Chapter 3

## Mandatory part

<br>

|                          |                                                                                                                                                                                                                                                                                                                                                                                                                  |
| ------------------------ | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **Program name**        | `minishell`                                                                                                                                                                                                                                                                                                                                                                                                      |
| **Turn in files**          | Makefile, *.h, *.c                                                                                                                                                                                                                                                                                                                                                                                                                 |
| **Makefile**             | NAME, all, clean, fclean, re                                                                                                                                                                                                                                                                                                                                                                                                   |
| **Arguments**                 |                                                                                                                                                                                                                                                                                                                                                                                                                  |
| **External functs.** | `readline, rl_on_new_line, rl_replace_line, rl_redisplay, add_history, printf, malloc, free, write, open, read, close, fork, wait, waitpid, wait3, wait4, signal, kill, exit, getcwd, chdir, stat, lstat, fstat, unlink, execve, dup, dup2, pipe, opendir, readdir, closedir, strerror, errno, isatty, ttyname, ttyslot, ioctl, getenv, tcsetattr, tcgetattr, tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs` |
| **Libft authorized**      | Yes                                                                                                                                                                                                                                                                                                                                                                                                        |
| **Description**                 | Write a shell                                                                                                                                                                                                                                                                                                                                                                                                    |

<br>

##### _Your shell should:_


- ##### _Not interpret unclosed quotes or unspecified special characters like \ or ;._


- ##### _Not use more than one global variable, think about it and be ready to explain why you do it._


- ##### _Show a prompt when waiting for a new command._


- ##### _Have a working History._


- ##### _Search and launch the right executable (based on the PATH variable or by using relative or absolute path)_


- ##### _It must implement the builtins:_


  - ##### _`echo` with option `-n`_


  - ##### _`cd` with only a relative or absolute path_
    

  - ##### _`pwd` with no options_


  - ##### _`export` with no options_


  - ##### _`unset` with no options_


  - ##### _`env` with no options or arguments_


  - ##### _`exit` with no options_


- ##### _’ inhibit all interpretation of a sequence of characters._


- ##### _" inhibit all interpretation of a sequence of characters except for $._


- ##### _Redirections:_


  - ##### _`<` should redirect input._


  - ##### _`>` should redirect output._


  - ##### _`<<` read input from the current source until a line containing only the delimiter is seen. it doesn’t need to update history!_


  - ##### _`>>` should redirect output with append mode._


- ##### _Pipes | The output of each command in the pipeline is connected via a pipe to the input of the next command._


- ##### _Environment variables ($ followed by characters) should expand to their values._


- ##### _$? should expands to the exit status of the most recently executed foreground pipeline._


- ##### _`ctrl-C, ctrl-D and ctrl-\` should have the same result as in bash._



- ##### When interactive:


  - ##### _`ctrl-C` print a new prompt on a newline._


  - ##### _`ctrl-D` exit the shell._


  - ##### _`ctrl-\` do nothing._
  
##### _Anything not asked is not required._

##### _For every point, if you have any doubt take bash as a reference_

<br>
