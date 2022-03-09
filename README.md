# minishell
A bash-like Unix shell written in C

![demo](https://raw.githubusercontent.com/3lswear/minishell/master/assets/cast.svg)
### Features
- Dynamic prompt
- History
- PATH handling
- Environment variables setting and expanding
- Getting exit code with `$?`
- String literal support (`'`, `"`)
- Bash-like syntax
- Pipes
- IO redirections (`>`, `<`, `>>`)
- Heredoc (`<< EOF`)
- Builtins: 
  - `echo [-n]`
  - `cd [-]`
  - `pwd`
  - `export`
  - `unset`
  - `env`
  - `exit` 
- Readline
  - You can use your Ctrl+A Ctrl+E Alt-F Alt+B Ctrl+W all you want.
### Installation
Requires readline library and headers

e.g. installation for Ubuntu:

```
sudo apt install libreadline8 libreadline-dev
```

### What I've learned from this project
- IO redirection sometimes is pure magic
- Writing shells is **hard**
- Bash is in many places terrible and inconsistent but it's a de-facto standard and we have to live with it.

### Team

This is a team project coded by:

- [sunderle](https://github.com/3lswear)
- [talyx](https://github.com/talyx)
