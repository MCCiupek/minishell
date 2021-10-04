# minishell

The objective of this project is for you to create a simple shell. Yes, your little bash or zsh. You will learn a lot about processes and file descriptors. The program is capable of parsing a prompt and launching executables with arguments, along with a few built-in functions.

## Skills
* Rigor
* Unix
* Imperative programming

## Use

Use ``make`` will to create the ``minishell`` executable. 

Then run: ``./minishell``


## Available otpions 

Minishell runs executables from an absolute, relative or environment PATH (``/bin/ls`` or ``ls``), including arguments or options. ``'`` and ``"`` work as in bash, except for multiline commands.

You can separate commands with ``;``, and use redirections ``>`` ``>>`` ``<`` as well as pipes ``|``.

Environment variables are handled, like ``$HOME``, including the return code ``$?``.

Finally, you can use ``Ctrl-C`` to interrupt and ``Ctrl-\`` to quit a program, as well as ``Ctrl-D`` to throw an EOF, same as in bash.

A few of the functions are "built-in", meaning we don't call the executable, we re-coded them directly. It's the case for :

* ``echo`` with option ``-n``
* ``pwd`` without options
* ``cd`` with an absolute or relative path
* ``env`` without options nor arguments
* ``export`` without options
* ``unset``  without options
* ``exit`` without options

You can navigate through the command history using up and down arrows and edit them inline with left and right arrows. 

## Example
![image](https://user-images.githubusercontent.com/51337012/135822328-305c4446-05e7-441d-8c55-d041f8eab0b9.png)

##
Grade : 96/100
