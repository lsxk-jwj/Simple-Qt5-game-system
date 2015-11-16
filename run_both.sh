#!/usr/bin/zsh

# Clear rbenv variables before starting tmux
unset RBENV_VERSION
unset RBENV_DIR

tmux start-server\; has-session -t cn-game 2>/dev/null

if [ "$?" -eq 1 ]; then
  cd /home/tony/course/cn/game

  # Run pre command.
  

  # Create the session and the first window. Manually switch to root
  # directory if required to support tmux < 1.9
  TMUX= tmux new-session -d -s cn-game -n main
  tmux send-keys -t cn-game:0 cd\ /home/tony/course/cn/game C-m


  # Create other windows.


  # Window "main"
  tmux send-keys -t cn-game:0.0 make\ run_client C-m

  tmux splitw -c /home/tony/course/cn/game -t cn-game:0
  tmux select-layout -t cn-game:0 tiled
  tmux send-keys -t cn-game:0.1 make\ run_client C-m

  tmux splitw -c /home/tony/course/cn/game -t cn-game:0
  tmux select-layout -t cn-game:0 tiled
  tmux send-keys -t cn-game:0.2 make\ run C-m

  tmux select-layout -t cn-game:0 tiled

  tmux select-pane -t cn-game:0.0

  tmux select-window -t 0

  tmux send-keys -t cn-game:0.0 run C-m
  tmux send-keys -t cn-game:0.1 run C-m
fi

if [ -z "$TMUX" ]; then
  tmux -u attach-session -t cn-game
else
  tmux -u switch-client -t cn-game
fi


