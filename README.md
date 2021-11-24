# nstdio_test

backend node から frontend node を経由して、interactive nodeにデータ転送する。
通信関数にはnstdioを使用している。事前にnstdioをインストールしておく必要がある。

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
###### frontend上  
$ ./sqf 0.0.0.0 30332 0.0.0.0 30333　　
　　
###### interactive上  
$ ./sqi localhost 30333　　
　　
######  backend上  
$ ./sqb localhost 30332　　

## コマンド（３台のコンピュータ内でテストする場合）
以下の順番で起動する。　　
###### frontend上 
$ ./sqf 0.0.0.0 30332 0.0.0.0 30333　　
　　
###### interactive上　　
$ ./sqi frontend-IP 30333　　
　　
###### backend上　　
$ ./sqb frontend-IP 30332　　

# プログラムの使い方SSH Portforwardingを利用する
