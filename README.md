# nstdio_test

backend node から frontend node を経由して、interactive node にデータ転送する。
通信関数は　nstdio を使用している。事前に nstdio をインストールしておく必要がある。

## 基本的な考え方

マシンが3台あり、それぞれ、backend node, frontend node, interactive node とする。
nstdio　による接続の際に、frontend をサーバとし、backend と interactive をクライアントとする。
これは、server-client モデルの通信の際のセッション作成の際ののみの役割であり、セッションが確立された後は、
server-client間で双方向にデータ転送が可能となる。

## 各ノードの役割
# backend

データを準備して、frontend に送信する。
実行コマンドは以下の通り。

# frontend

backend からデータを受信して、データを加工して（今回はここのデータを2倍して） interactive に送信する。
受信データと送信データを表示する。

# interactive

frontend からデータを受信して、表示する。
