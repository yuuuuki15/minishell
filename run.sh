#!/bin/bash
valgrind --leak-check=full --error-limit=no --suppressions=./valgrind-readline.supp --gen-suppressions=all --track-fds=yes --trace-children=yes ./minishell
