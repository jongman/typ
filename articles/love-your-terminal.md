title: 터미널 사용자를 위한 유용한 프로그램들
date: 2013-01-01
categories: 개발, 리눅스

리눅스 프로그래머가 가장 많은 시간을 보내는 곳은 아마도 터미널일 것이다. 터미널에서 어떤 쉘을 쓰느냐, 어떻게 셋업해서 쓰느냐, 어떤 프로그램을 쓰느냐는 개발자의 생산성에 엄청난 영향을 미친다. 한 시간만 들여서 새로운 도구를 몇 개 깔고 커스터마이즈하자. 인생이 달라진다.

추가로 소개하면 좋을 만한 다른 팁이나 프로그램들이 있다면 트위터로 알려주면 추가하겠다.

----

<!-- PREVIEW_END -->

### zsh

[zsh](http://zsh.sourceforge.net/)는 현재도 활발하게 개발되고 있는 강력한 쉘이다. zsh는 우리가 익숙한 bash와 거의 비슷하게 동작하기 때문에 사용자 입장에서 진입 장벽은 굉장히 낮으면서도, 다양한 면에서 훨씬 나아진 사용성을 보여준다. [zsh FAQ](http://zsh.sourceforge.net/FAQ/zshfaq01.html#l4)에는 zsh의 장점들을 소개하고 있는데, 이 중 내가 느끼기에 큰 요소는 다음 두 가지다.

* 강력한 tab-completion 및 globbing (파일명 autocompletion): 파일명 중간에서부터도 오토컴플리션이 되고, 탭이나 화살표 키를 이용해 선택지중 하나를 간단히 고를 수도 있다.
* 다양한 테마와 플러그인을 갖춘 커뮤니티 프로젝트: [oh-my-zsh](https://github.com/robbyrussell/oh-my-zsh)는 다양한 프로그램에 대한 zsh 플러그인과 테마 등을 모아 놓은 커뮤니티 프로젝트다. 예를 들어 여기의 git 플러그인은 현재 디렉토리가 git repository일 경우 현재 브랜치, 파일을 수정했는지 여부 등을 프롬프트에 추가해 준다. 

### z 

* [https://github.com/rupa/z](https://github.com/rupa/z)

`z`는 `cd`의 대체품인 스크립트로, 평소에 자주 가는 디렉토리들을 기억해 놨다가 패턴 매칭을 통해 움직일 수 있게 해 준다. 그래서 `cd ~/git/algospot/www/judge/templates/submission`를 치는 대신에 `z sub`를 쳐서 이동할 수 있도록 해 준다. 

zsh에서 쓰면 물론 탭 컴플리션도 된다!

### scm-breeze

* [https://github.com/ndbroadbent/scm_breeze.git](https://github.com/ndbroadbent/scm_breeze.git)

터미널에서 git을 쓰고 있다면, 다음과 같은 커맨드를 매일 쳐야 할 것이다.

	git add judge/templates/submission/detail.html
	git commit -v

`scm_breeze`는 `git status`를 `gs` 커맨드로 alias해주는데, 이 결과의 각 파일에 번호를 붙여준다. 이렇게:

	(typ)[3:26:01] jongman:~/git/typ git:(master*) $ gs
	# On branch: master  |  [*] => $e*
	#
	➤ Changes not staged for commit
	#
	#       modified: [1] articles/love-your-terminal.md 
	#
	➤ Untracked files
	#
	#      untracked: [2] articles/.love-your-terminal.md.swp 
	#      untracked: [3] assets/img/feed-icon-28x28.png 
	#      untracked: [4] assets/img/feedicons-standard.zip 
	#      untracked: [5] flat.html 
	#      untracked: [6] output/ 
	#      untracked: [7] rss.xml 
	#      untracked: [8] test.html 

그러면 `git add`를 alias한 `ga`와 `git commit -v`를 alias한 `gcv` 커맨드 등에 이 번호를 쓸 수 있다. 이렇게:

	(typ)[3:27:55] jongman:~/git/typ git:(master*) $ ga 2
	# Added '/home/jongman/git/typ/templates/base.html'
	#
	# On branch: master  |  [*] => $e*
	#
	➤ Changes to be committed
	#
	#       modified:  [1] templates/base.html 

### tmux, 혹은 byobu 사용하기

* [https://launchpad.net/byobu](https://launchpad.net/byobu)

GNU screen은 서버에서 오래 돌려야 하는 프로세스를 돌리거나 할 때 아주 유용하지만, 그냥 쓰려면 몇 가지 불편한 점이 있다.

* 적응하면 괜찮지만, 새 창 만들기, 다음 창으로 바꾸기 등의 작업을 하는 핫키가 불편하다. 예를 들면 다음 창 넘어가기가 `^a n`.
* 스크린을 띄웠는지 아닌지, 지금 창이 몇 개나 떠 있는지, 그 중 몇 번째가 지금 떠 있는지를 알 방법이 없다.

다행히 이 문제들은 모두 설정 파일인 `.screenrc`를 통해 해결 가능하다. 그런데 이것을 아예 완전히 뜯어고치는 수준으로 커스터마이즈한 셋업이 있으니 이게 `byobu`이다. F2로 새 창을 열고, F3, F4로 창 사이를 오갈 수 있다.

아예 `screen`을 쓰지 않고 좀더 현대적이고 최근 개발되고 있는 `tmux`를 쓰는 방법도 있다.

둘 다 우분투 리눅스에서는 `apt-get`으로 깔 수 있다.

### ack-grep 사용하기

* [http://betterthangrep.com/](http://betterthangrep.com/)

`grep`에는 `.git` 디렉토리 안도 검색한다던가, `.bak` 파일들도 검색한다던가, 바이너리 파일도 검색해버린다던가 하는 문제들이 있다. `ack-grep`은 이와 같은 문제를 해결하고 상식적인 디폴트 값을 넣은 `grep`의 대체품이다.

우분투 리눅스에서는 `apt-get`으로 깔 수 있다.

### most 사용하기

* [http://www.jedsoft.org/most/](http://www.jedsoft.org/most/)

터미널에서 많은 양의 텍스트를 다루는 경우, 좌우 스크롤을 하고 싶은 경우가 왕왕 있다. 커다란 csv 파일을 출력할 때라던가. 이 때 흔히 쓰는 페이저인 `less`나 `more`는 좌우 스크롤을 지원하지 않는다는 문제가 있다. `most`는 좌우 스크롤도 지원하고, 여러 개의 윈도우를 지원하는 등 훨씬 강력하다. 물론 난 좌우 슨크롤 기능밖에 쓰지 않는다.

우분투 리눅스에서는 `apt-get`으로 깔 수 있다.

### Dropbox 혹은 github에 설정 파일 저장하기

한번 시간을 들여 터미널 설정을 최적화하고 나면 [Dropbox](http://db.tt/sxgsW4zu)나 github에 설정 파일들을 저장해 놓는 것도 좋은 생각이다. 이렇게 하고 나면 운영체제를 새로 깔고 셋업에 걸리는 시간이 세 시간에서 3분으로 줄어든다. 윈도우에서 필요한 프로그램을 하나하나 깔고, 설정 탭 찾아다니면서 설정 변경하던 시절을 생각해 보라.

### 가난한 자의 CSV 뷰어

csv 파일을 콘솔에서 간단히 확인하고 싶은데, vi 등의 텍스트 편집기로 열면 정렬이 되어 있지 않아 알아보기가 힘들다. 이 때 `column`을 쓰면 좋다.

	$ cat a.csv | column -t -s ,
	1  2   3   4    5     6     7     8      9    
	1  3   6   10   15    21    28    36     45   
	1  4   10  20   35    56    84    120    165  
	1  5   15  35   70    126   210   330    495  
	1  6   21  56   126   252   462   792    1287 
	1  7   28  84   210   462   924   1716   3003 

### 가난한 자의 웹서버

HTML을 편집하고 있다거나 등의 이유로 현재 디렉토리를 웹 브라우저에서 보고 싶을 때가 있다. 다행히 파이썬에는 간단한 웹서버가 딸려 있어서 이것을 쓰면 간단하다. 다음 alias를 `.zshrc` 혹은 `.bashrc`에 넣어 두자.

	alias serve="python -mSimpleHTTPServer"

serve를 치면 현재 디렉토리를 8000번 포트에서 서빙해 준다.

### vim/emacs

터미널을 잘 사용하려면 결국 콘솔 기반 에디터를 사용하는 것이 좋다. vi나 emacs는 오래되었지만 그만큼 강력하고, 큰 유저 베이스가 그간 만들어놓은 툴이 있다. 어떤 언어를 사용하건간에 같은 에디터를 사용할 수 있다는 것은 꽤나 큰 장점이다.

vim을 어떻게 최적화하느냐에 관한 내용은 이 글의 전체 내용보다 훨씬 길어질 수 있으니 다음에 따로 쓰도록 하겠다.
