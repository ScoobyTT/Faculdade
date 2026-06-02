"""
rtp_client.py — Cliente RTP sobre UDP com exibição real (OpenCV)
Requisitos: pip install cryptography opencv-python
"""

import socket
import struct
import cv2
import numpy as np
from collections import defaultdict
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
from cryptography.hazmat.backends import default_backend

# ─── Configurações ────────────────────────────────────────────
LISTEN_IP   = "127.0.0.1"
LISTEN_PORT = 5004

# Chave fixa — mesma do servidor
AES_KEY = bytes.fromhex("00112233445566778899aabbccddeeff")
AES_IV  = bytes.fromhex("aabbccddeeff00112233445566778899")

# ─── Descriptografia AES-CTR ──────────────────────────────────
def decrypt(data):
    cipher = Cipher(algorithms.AES(AES_KEY), modes.CTR(AES_IV),
                    backend=default_backend())
    dec = cipher.decryptor()
    return dec.update(data) + dec.finalize()

# ─── Parser do cabeçalho RTP ──────────────────────────────────
def parse_rtp(data):
    if len(data) < 12:
        return None
    byte0, byte1, seq, timestamp, ssrc = struct.unpack("!BBHII", data[:12])
    return {
        "marker":    (byte1 >> 7) & 0x01,
        "seq":       seq,
        "timestamp": timestamp,
        "ssrc":      ssrc,
        "payload":   data[12:]
    }

# ─── Cliente principal ────────────────────────────────────────
def main():
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.bind((LISTEN_IP, LISTEN_PORT))
    sock.settimeout(10.0)

    # Buffer de fragmentos por timestamp
    fragments = defaultdict(list)

    print(f"[Cliente RTP] Escutando em {LISTEN_IP}:{LISTEN_PORT}")
    print("[Cliente RTP] Aguardando frames... (pressione Q na janela pra sair)\n")

    while True:
        try:
            data, _ = sock.recvfrom(65535)
        except socket.timeout:
            print("[Cliente RTP] Timeout — nenhum pacote recebido.")
            break

        pkt = parse_rtp(data)
        if pkt is None:
            continue

        # Descriptografa e acumula fragmento
        payload = decrypt(pkt["payload"])
        fragments[pkt["timestamp"]].append(payload)

        # Quando chega o último fragmento (Marker=1), monta o frame
        if pkt["marker"] == 1:
            frame_bytes = b"".join(fragments.pop(pkt["timestamp"]))

            np_arr = np.frombuffer(frame_bytes, dtype=np.uint8)
            frame  = cv2.imdecode(np_arr, cv2.IMREAD_COLOR)

            if frame is not None:
                cv2.imshow("Streaming RTP", frame)
                print(f"[RX] Frame exibido | TS={pkt['timestamp']} | {len(frame_bytes)}B")

        # Q pra sair
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

    cv2.destroyAllWindows()
    sock.close()
    print("[Cliente RTP] Encerrado.")

if __name__ == "__main__":
    main()
