# minishell

handle ctrl-C, ctrl-D and ctrl-\ :
- use tcsetattr() and tcgetattr() to silence echo ^C
https://stackoverflow.com/questions/59922972/how-to-stop-echo-in-terminal-using-c

Add environment variables only with export :
![image](https://user-images.githubusercontent.com/51337012/115218643-0ffcc980-a107-11eb-8174-7399a5d6aa21.png)

leaks a corriger :
- cd
- export
- unset
- [OK] cmd not found
- cmd history (2 blocks definitely lost)
- edit inline (3 blocks definitely lost)

fix :
- parsing: pipe mal positionné ("| wc")

leaks tgetent :
![image](https://user-images.githubusercontent.com/51337012/117141496-e6060100-adae-11eb-9e93-276c218c9832.png)
