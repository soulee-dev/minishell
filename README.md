# minishell

ascii art small

가독성을 위한 규칙
1. 함수/변수명 Snake Case로
2. 함수/변수명은 최대한 길더라도, 어떤 기능을 하는지 서술할것
3. 함수 명은 동사로 시작할것. ex.) get_line
4. 기능별 단위를 최대한 나눌것.
5. 변수 선언은 길이 오름차순으로.
6. 커밋메시지 add/fix/delete형으로 시작하고, 최대한 구체적으로 서술, 가능한 기능별 커밋

-l 은 라이브러리 사용
-L 은 라이브러리 폴더 위치

# brew 설치
```sh
`rm -rf $HOME/.brew && git clone --depth=1` `[https://github.com/Homebrew/brew](https://github.com/Homebrew/brew)` `$HOME/.brew && export PATH=$HOME/.brew/bin:$PATH && brew update && echo "export PATH=$HOME/.brew/bin:$PATH" >> ~/.zshrc`
```

# readline 설치
```sh
brew install readline
```

# 파싱
- [ ] 작은 따옴표
- [ ] 큰 따옴표
- [ ] 리다이렉션 < > << >> 
- [ ] 파이프
- [ ] 환경변수
- [ ] $?

구현하지 않아도 되는 문자들
- [ ] backslash
- [ ] semicolon
- [x] double vertical bar
- [x] only single vertical bar

파이프 기준으로 하나의 스코프로 가정함.
그렇게 해서 모든 따옴표 내용을 그대로 넘겨줌

# bash 실행하면서 배운 점
[builtin 함수 실행 case](https://velog.io/@hey-chocopie/minishell-builtin%ED%95%A8%EC%88%98%EA%B5%AC%ED%98%84-cdpwd)
```shell
echo                               a
```
정상적으로 실행 된다 (a)

```shell
<< ls >>
```
ls 기준으로 heredoc이 되고, 잘 읽어 오다가, >>가 나오면 parse error (outfile이 없음)

```shell
<<
```
하나만 실행하면, parse error (infile이 없음)

```shell
echo "hello"
"echo" "hello"
```
실행 잘 됨

```shell
"echo hello"
```
실행 안 됨 (이유는 모르겠음)

```shell
|
| ls
```
에러

```shell
cat || ls
```
실행 됨 > 더블 버티컬바 (에러 처리 필요? > 보너스 구현이므로 할 필요 없음)

```shell
ls|wc -l
```

```shell
< infile | cat | ""echo ls"" > outfile
```

```shell
cat < infile1 | cat < infile2 | cat
```
이 같은 경우도 실행됨

```shell
< infile cat > outfile | < outfile cat > outfile2
```
여러 번 redirection 해야 하는 경우도 처리할 것

# Git 형상 관리
- branch 나눠야 할 필요?
- commit message, pull request message 등 

# 코드 형상 관리
- 코드 관리는?
