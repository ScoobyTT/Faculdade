import socket

servidor = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
servidor.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
servidor.bind(("0.0.0.0", 8080))
servidor.listen(5)

print("Servidor rodando em http://localhost:8080")

while True:
    cliente_socket, endereco_cliente = servidor.accept()
    print(f"Conexão recebida de {endereco_cliente}")

    requisicao = cliente_socket.recv(1024).decode("utf-8")
    print(f"\n--- REQUISIÇÃO ---\n{requisicao}")

    #  Pega a primeira linha (ex: GET / HTTP/1.1)
    linha_inicial = requisicao.split("\n")[0]

    corpo_resposta = ""

    #  Se for POST
    if "POST" in linha_inicial:
        partes = requisicao.split("\r\n\r\n")

        if len(partes) > 1:
            corpo_post = partes[1]
        else:
            corpo_post = "vazio"

        print("Corpo do POST:", corpo_post)

        corpo_resposta = f"""
        <html>
            <body>
                <h1>POST recebido!</h1>
                <p>Dados: {corpo_post}</p>
            </body>
        </html>
        """

    #  Se for GET
    else:
        corpo_resposta = """
        <html>
            <body>
                <h1>Servidor HTTP funcionando!</h1>
                <p>Envie um POST para ver os dados recebidos.</p>
                <p>PEGA BAHIA!!! </p>
                <p>ERIK PULGA MEU 11!!! </p>
                <form method="POST">
                    <input type="text" name="nome" placeholder="Digite seu nome">
                    <button type="submit">Enviar</button>
                </form>
            </body>
        </html>
        """

    resposta = (
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html; charset=utf-8\r\n"
        f"Content-Length: {len(corpo_resposta.encode('utf-8'))}\r\n"
        "Connection: close\r\n"
        "\r\n"
        + corpo_resposta
    )

    cliente_socket.sendall(resposta.encode("utf-8"))
    cliente_socket.close()
