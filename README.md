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
- cmd history (2 blocks definitely lost) : access_history.c ligne 90 + read.c ligne 146
- edit inline (3 blocks definitely lost)
- [OK] $?

fix :
- [OK] parsing: pipe mal positionné ("| wc")
- [OK] parsing: ![image](https://user-images.githubusercontent.com/51337012/117170962-bfee5a00-adca-11eb-8c59-173d508d06bd.png)
- [OK] historique de cmds: plusieurs cmds en une ligne ![image](https://user-images.githubusercontent.com/51337012/117171290-09d74000-adcb-11eb-88c3-6ec888a75780.png)
- [OK] historique: segfault à fix si hist vide
- edit : pb avec la prise en compte du backspace en fin de ligne dans l'historique
- [OK mais à surveiller] edit / backspace : bug avec la touche echap qui permet d'effacer le prompt
- [OK] leaks exit avec trop de variables: j'ai déplacé le lstclear (le rendant pour le moment inutile) après l'appel à builtin_exit car j'avais besoin de récupérer la cmd contenant exit
- [OK] unset : ne fonctionne plus
- [OK] cd: gerer les cas où des var ont ete unset= home [OK], pwd [OK], oldpwd [OK] -> cas de 'cd -' à gérer
- prompt: gerer le cas où logname est unset
- [OK] cd: segfault au moment de exit au niveau des var modifiées au moment d'utiliser cd (OLDPWD, PWD)

leaks tgetent :
![image](https://user-images.githubusercontent.com/51337012/117141496-e6060100-adae-11eb-9e93-276c218c9832.png)

![image](https://user-images.githubusercontent.com/51337012/117823892-41803500-b26e-11eb-917b-74b21c7e4b1e.png)
![image](https://user-images.githubusercontent.com/51337012/117832000-64621780-b275-11eb-970c-82a16e505839.png)
