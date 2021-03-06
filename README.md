# nstdio_test

このプログラムでは、通常の並列クラスタ計算機やいわゆるスパコンを対象とした、backend nodeからfrontend nodeを経由して、interactive nodeへのデータ転送の仕組みを実装している。経由の際にはバケツリレーを行っている。この際、通信関数には[nstdio](https://github.com/y-morie/nstdio)を使用しており、事前にnstdioをインストールしておく必要がある。[nstdio](https://github.com/y-morie/nstdio)は主にC言語を対象とした、サーバ・クライアントモデルの接続方法を用いた非同期型の簡素で有用な通信ライブラリであり、プリミティブなデーモンプログラムを簡単に作成することも可能である。  
[第182回HPC研究発表会](http://www.ipsj.or.jp/kenkyukai/event/hpc182.html)発表済み


# 基本的な考え方

通信に関与するマシンを3台考え、それぞれ、backend node,frontend node,interactive nodeとする。
nstdioによる接続の際にはserver側とclient側を設定する必要があるが、今回はfrontendをserverとし、backendとinteractiveをclientとする。
これは、server-clientモデルの通信の際のセッション作成時のみの役割であり、セッションが確立された後はserver-client間で双方向にデータ転送が可能となる。

# 各ノードの役割
## backend

スパコン内のバックエンド計算ノードを想定している。
データを準備して、frontendに送信する。

## frontend

スパコンのフロントエンドサーバを想定している。
backendからデータを受信して、データを加工してinteractiveに送信し、受信データと送信データを表示する。

## interactive

フロントエンドとデータをやり取りしている解析ノードもしくはローカルのパソコンを想定している。frontendからデータを受信し、表示する。

# プログラムの使い方（sshを利用しない場合）

## IPとPortの情報例

以下、Port番号は自由に選べるが、とりあえず以下の情報でそのまま動作すると思われる（既存利用ポートと重複指定すると接続時にエラーとなる）。
nstdioでは、server側ではclientのIP(0.0.0.0も選択可能)とserverでの受信ポート番号を指定し、client側ではserverのIPとserver側での受信ポート番号を指定する。
このテストプログラムではbackendとinteractiveが両方ともfrontendと接続するため、frontendでは相手IPと受信ポートをそれぞれ2種類準備する必要がある。
1台のマシンでテストする際には、backendとinteractiveで指定するfrontend-IPをlocalhostとすれば良い。

### frontend
IP:0.0.0.0、Port:30332 (backend向け接続情報)　  
IP:0.0.0.0、Port:30333 (interactive向け接続情報)　　  
　
### backend
IP:frontend-IP、Port:30332　　（IPはスパコンバックエンド内でのアドレスを設定する必要あり）

### interactive
IP:frontend-IP、Port:30333　　（IPはローカルパソコンからsshする際のアドレスを指定）

## コマンド（1台のコンピュータ内でテストする場合）
以下の順番で起動する。　　
##### すべて同じコンピュータ上で  
$ ./sqf 0.0.0.0 30332 0.0.0.0 30333  
$ ./sqi localhost 30333  
$ ./sqb localhost 30332  

## コマンド（３台のコンピュータ内でテストする場合）
以下の順番で起動する。　　
##### frontend上 
$ ./sqf 0.0.0.0 30332 0.0.0.0 30333　　
　　
##### interactive上　　
$ ./sqi frontend-IP 30333　　　　（frontend-IPは外からのアクセス用IP）  
　　
##### backend上　　
$ ./sqb frontend-IP 30332　　　　（frontend-IPはバックエンドからのアクセス用IP）  

# プログラムの使い方（SSH Portforwardingを利用する）
一般のスパコンではssh接続を行う必要があり、さらにfrontendから外界のinteractiveへの直接接続と、frontendからバックエンドへの直接接続は一般には許されていない。そのため、backendからfrontendならびにintaractiveからfrontendへの方向でsshの Portforwardingのトンネルを作成しておき、この中にてnstdioの接続を行う。この際には、ローカルノードのinteractiveもしくはbackendのローカルポートへのアクセスを、リモートノードのfrontendにおける指定のポートに転送する、"-L"による指定を行う。frontend上では接続時にはserver側であるため受信側であり、portforwardingする必要はない。
上記の例で、interactiveからfrontendの30333番ポート、backendからfrontendの30332ポートにアクセスしたい場合には、以下のように行い、port-forwarding可能とする。
その後、　localhostの指定のポートにアクセスする。
##### frontend上 
$ ./sqf 0.0.0.0 30332 0.0.0.0 30333　　
##### interactive上
$ ssh -N -f -L 10333:localhost:30333 username@frontend-IP　　　（frontend-IPは外からのアクセス用IP）  
$ ./sqi frontend-IP 10333
##### backend上
$ ssh -N -f -L 10333:localhost:30332 username@frontend-IP　　　（frontend-IPはバックエンドからのアクセス用IP）    
$ ./sqb frontend-IP 10333
### 注意点
上記のsshコマンドは、バックグラウンドジョブとなるため、通信の終了後に自身でkillする必要がある。
## スクリプトの利用
上記を行うスクリプトを用意した。その際に、configファイルにて設定を行う。
##### interactiveとbackendで設定ファイルを編集
connect_test.configファイルを編集する。
## connect_test.configを利用したスクリプトによる投入コマンド（以下の順に行う）
##### frontend
$ ./sqf_wrapper
##### interactive
$ ./sqi_wrapper
##### backend
$ ./sqb_wrapper


