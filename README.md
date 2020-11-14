# 42_Exam_rank_03

42でのテストです。

# micro_paint

```
10 10 .
r 1.2 1.2 3.01 3.02 x
R 5.2 5.2 3.01 3.02 o
```

このようなファイルが与えられるのでそれをfopenで開いてfscanfで読み取り、
その情報を元に四角形を出力する問題。

### 与えられるファイルのフォーマット

1行目

```
zoneの横幅　zoneの縦幅　四角形以外の部分を埋める文字

0 < zoneの横幅 <= 300
0 < zoneの縦幅 <= 300
```

2行目

```

r　squareの左上の角のx_index　squareの左上の角のy_index \
squareの横幅　squareの縦幅 四角形を作る文字

squareの左上の角のx_index != 0
squareの左上の角のy_index != 0
```

3行目

```

R　squareの左上の角のx_index　squareの左上の角のy_index \
squareの横幅　squareの縦幅 四角形を作る文字

squareの左上の角のx_index != 0
squareの左上の角のy_index != 0
```

rとRはtype identifierで
r→真ん中が空いた四角形を出力。(幅の片方が2マスなら空かない)
R→全てが埋まった四角形を出力する。

上のファイルだとこのように出力されます。
->
```
..........
..........
..xxx.....
..x.x.....
..xxx.....
..........
......ooo.
......ooo.
......ooo.
..........
```
