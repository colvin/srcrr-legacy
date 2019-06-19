# srcrr

A utility to load a development context by name, using a `PATH` like searching
process to find the source directory.

The `SRCPATH` environment variable should contain a colon-delimited list of one
or more directories in which projects are located. Like the `PATH` variable,
each element of the list is of lower priority than the element to its left.

The `srcrr` utility walks each directory in the `SRCPATH` variable looking for
a directory of the given project name. The search terminates as soon as a
directory is found. If the directory is found, Bourne-shell compatible shell
script is emitted on standard output. This shell script provides the necessary
instructions for changing directories and running additional contextualization
commands using the optional `.srcrrrc` file.

The `src` shell function is provided in the `func.*` files, which can be added
to your shell initialization file (eg, `$HOME/.bashrc`). This function invokes
`srcrr` and executes the statements it emits in the current shell session.

If the project directory contains a file named `.srcrrrc`, it will
automatically be sourced into your current shell session. This provides the
ability to run arbitrary setup operations when starting a development session:
loading virtual environments, setting the terminal title, setting other
environment variables, etc.

If `srcrr` is not able to locate the given project directory, no output is
produced. It is not an error for `SRCPATH` to contain a non-existent directory,
but an error message will be printed to standard error if the verbose flag is
given.

## EXAMPLE

If I have projects in my home directory `$HOME/src` as well as in
`/mnt/share/src`, I would set the `SRCPATH` environment variable in my shell
configuration:

```
export SRCPATH="$HOME/src:/mnt/share/src"
```

Using `srcrr`'s shell function wrapper, `src`, I can load my `foobar` project,
which is actually located in `/mnt/share/src/foobar`:

```
src foobar
```

If my `foobar` project has a `.srcrrrc` file, it will be sourced in the current
shell session. For instance, if this was a Python project:

```
# foobar/.srcrrrc

. /path/to/virtualenvs/foobar/bin/activate
export PS1="[foobar] $PS1"
```
