# minishell
School 42 project. Implementation of a simple shell <minishell>.

## Features
`pipes`, `semicolons`, `escape sequences`, `enviroment variables`, `$?`, `~`, redirections: `>` `>>` `<`

Builtins: `cd`, `pwd`, `echo`, `export`, `unset`, `env`, `exit`.

Signals: `Ctrl-C`, `Ctrl-\`, `Ctrl-D`.

Parser opens quotes `'` `"` like in bash and handles `\` even in `'` `"` different context.

Commands work with absolute and relative paths.
