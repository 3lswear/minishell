# minishell
A bash-like Unix shell written in C
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
### Installation
Requires readline library and headers

e.g. installation for Ubuntu:

```sudo apt install libreadline8 libreadline-dev```

### What I've learned from this project
- Writing shells is **hard**
- Bash is in many places terrible and inconsistent but it's a de-facto standard and we have to live with it
