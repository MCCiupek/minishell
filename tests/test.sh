CMD="ls"
echo $CMD
bash -c $CMD; ./minishell -c $CMD
echo

CMD="cd ; pwd"
echo $CMD
bash -c $CMD; ./minishell -c $CMD
echo

CMD="cd . ; pwd"
echo $CMD
bash -c $CMD; ./minishell -c $CMD
echo

CMD="cd /Users ; pwd"
echo $CMD
bash -c $CMD; ./minishell -c $CMD
echo

CMD="pwd"
echo $CMD
bash -c $CMD; ./minishell -c $CMD
echo

CMD="cd ; pwd"
echo $CMD
bash -c $CMD; ./minishell -c $CMD
echo

CMD="cd // ; pwd"
echo $CMD
bash -c $CMD; ./minishell -c $CMD
echo

CMD="cd '//' ; pwd"
echo $CMD
bash -c $CMD; ./minishell -c $CMD
echo

CMD="cd ////// ; pwd"
echo $CMD
bash -c $CMD; ./minishell -c $CMD
echo

CMD="cd ./././ ; pwd"
echo $CMD
bash -c $CMD; ./minishell -c $CMD
echo

CMD="pwd ; cd . ; pwd"
echo $CMD
bash -c $CMD; ./minishell -c $CMD
echo

CMD="cd / ; cd Users ; pwd ; cd .. ; pwd"
echo $CMD
bash -c $CMD; ./minishell -c $CMD
echo

CMD="cd '/////' 2>/dev/null ; pwd"
echo $CMD
bash -c $CMD; ./minishell -c $CMD
echo

CMD="cd '/etc' ; pwd"
echo $CMD
bash -c $CMD; ./minishell -c $CMD
echo

CMD="cd '/var' ; pwd"
echo $CMD
bash -c $CMD; ./minishell -c $CMD
echo

CMD="cd "$PWD/file_tests" ; pwd"
echo $CMD
bash -c $CMD; ./minishell -c $CMD
echo

CMD="cd "doesntexist" ; pwd"
echo $CMD
bash -c $CMD; ./minishell -c $CMD
echo

CMD="cd "doesntexist" 2>/dev/null ; pwd"
echo $CMD
bash -c $CMD; ./minishell -c $CMD
echo

CMD="cd ../../.. ; pwd ; echo $PWD $OLDPWD"
echo $CMD
bash -c $CMD; ./minishell -c $CMD
echo

CMD="cd "wtf" 2>/dev/null ; pwd ; echo $PWD $OLDPWD"
echo $CMD
bash -c $CMD; ./minishell -c $CMD
echo

CMD="cd .. ; unset OLDPWD ; cd $OLDPWD ; pwd "
echo $CMD
bash -c $CMD; ./minishell -c $CMD
echo

CMD="cd .. ; unset PWD ; cd $PWD ; pwd"
echo $CMD
bash -c $CMD; ./minishell -c $CMD
echo

CMD="cd ?"
echo $CMD
bash -c $CMD; ./minishell -c $CMD
echo

CMD="cd +"
echo $CMD
bash -c $CMD; ./minishell -c $CMD
echo

CMD="cd _"
echo $CMD
bash -c $CMD; ./minishell -c $CMD
echo

CMD="cd woof"
echo $CMD
bash -c $CMD; ./minishell -c $CMD
echo

CMD="cd bark bark"
echo $CMD
bash -c $CMD; ./minishell -c $CMD
echo

CMD="cd '/' ; pwd"
echo $CMD
bash -c $CMD; ./minishell -c $CMD
echo

CMD="cd $PWD/file_tests ; pwd"
echo $CMD
bash -c $CMD; ./minishell -c $CMD
echo

CMD="cd $OLDPWD/something ; pwd"
echo $CMD
bash -c $CMD; ./minishell -c $CMD
echo

