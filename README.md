# nstdio_test

backend node から frontend node を経由して、interactive node にデータ転送する。
通信関数は　nstdio を使用している。事前に nstdio をインストールしておく必要がある。

## 基本的な考え方

マシンが3台あり、それぞれ、backend node,frontend node,interactive nodeとする。
nstdio　による接続の際に、frontendをサーバとし、backendとinteractiveをクライアントとする。
これは、server-clientモデルの通信の際のセッション作成の際ののみの役割であり、セッションが確立された後は、
server-client間で双方向にデータ転送が可能となる。

## 各ノードの役割
# backend

スパコン内のバックエンド計算ノードを想定している。
データを準備して、frontendに送信する。
実行コマンドは以下の通り。

# frontend

スパコンのフロントエンドサーバを想定している。
backend からデータを受信して、データを加工して（今回はbackendからのデータを2倍して）interactiveに送信する。
受信データと送信データを表示する。

# interactive

フロントエンドとデータをやり取りしている解析ノードもしくはローカルのパソコンを想定している。
frontendからデータを受信して、表示する。

## プログラムの使い方（sshを利用しない場合）

#IPとPortの情報例

以下、Port番号は自由に選べますが、とりあえず以下の情報でそのまま動作すると思われる。
nstdioでは、server側ではclientのIP(0.0.0.0も選択可能)とserverでの受信ポート番号を設定し、
client側ではserverのIPとserverでの受信ポート番号を指定する。

frontend:
IP:0.0.0.0、Port:30332 (backend向け接続情報)
IP:0.0.0.0、Port:30333 (interactive向け接続情報)

backend:
IP:frontend-IP、Port:30332　　（IPはスパコンバックエンド内でのアドレスを設定する必要あり）

interactive:
IP:frontend-IP、Port:30333　　（IPはローカルパソコンからsshする際のアドレスを指定）

#コマンド
以下の順番で起動する。
1. frontend上
$ ./sqf 0.0.0.0 30332 0.0.0.0 30333

2. interactive上
$ ./sqi frontend-IP 30333

3. backend上
$ ./sqb frontend-IP 30332

## SSH Portforwardingを利用する
