#!/bin/bash
while true; do lsof | grep minishell | wc -l;sleep 0.4;done;