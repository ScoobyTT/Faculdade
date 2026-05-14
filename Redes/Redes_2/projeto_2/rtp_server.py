"""
rtp_server.py — Servidor RTP sobre UDP com QoS e segurança (SRTP simplificado)

Estrutura do pacote RTP (RFC 3550):
 0                   1                   2                   3
 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|V=2|P|X|  CC   |M|     PT      |       sequence number         |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|                           timestamp                           |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|           synchronization source (SSRC) identifier           |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|                         payload...                            |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
"""

import socket
import struct
import time
import random
import threading
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
from cryptography.hazmat.backends import default_backend
import os

# ─── Configurações ────────────────────────────────────────────
SERVER_IP   = "127.0.0.1"
SERVER_PORT = 5004          # porta padrão RTP
PAYLOAD_TYPE = 26           # PT=26 → MJPEG (vídeo)
CLOCK_RATE  = 90000         # Hz (padrão para vídeo)
FPS         = 25            # frames por segundo simulados
FRAME_SIZE  = 1024          # bytes por frame simulado
DSCP_VIDEO  = 0b101110      # DSCP EF (Expedited Forwarding) → QoS alta prioridade
AES_KEY     = os.urandom(16)  # chave AES-128 compartilhada (em prod: troca via DTLS)
AES_IV      = os.urandom(16)  # IV aleatório por sessão

# ─── Montar cabeçalho RTP (12 bytes fixos) ─────────────────────
def build_rtp_header(seq: int, timestamp: int, ssrc: int, marker: bool = False) -> bytes:
    """
    Campos:
      V=2, P=0, X=0, CC=0  → primeiro byte = 0x80
      M (marker) + PT       → segundo byte
      seq                   → 16 bits
      timestamp             → 32 bits
      ssrc                  → 32 bits
    """
    version_flags = 0x80           # V=2, P=0, X=0, CC=0
    m_pt = (int(marker) << 7) | (PAYLOAD_TYPE & 0x7F)
    header = struct.pack("!BBHII",
                         version_flags,
                         m_pt,
                         seq & 0xFFFF,
                         timestamp & 0xFFFFFFFF,
                         ssrc & 0xFFFFFFFF)
    return header

# ─── Criptografia AES-CTR (SRTP simplificado) ──────────────────
def encrypt_payload(data: bytes) -> bytes:
    """Cifra o payload com AES-128-CTR (núcleo do SRTP)."""
    cipher = Cipher(
        algorithms.AES(AES_KEY),
        modes.CTR(AES_IV),
        backend=default_backend()
    )
    encryptor = cipher.encryptor()
    return encryptor.update(data) + encryptor.finalize()

# ─── Aplicar DSCP para QoS ─────────────────────────────────────
def set_dscp(sock: socket.socket, dscp_value: int):
    """
    Define o campo DSCP no IP ToS.
    DSCP é os 6 bits mais significativos do byte ToS.
    EF (101110) → ToS = 0xB8 → alta prioridade para vídeo em tempo real.
    """
    tos = dscp_value << 2  # DSCP ocupa bits [7:2]
    try:
        sock.setsockopt(socket.IPPROTO_IP, socket.IP_TOS, tos)
        print(f"[QoS] DSCP configurado: {bin(dscp_value)} | ToS byte: {hex(tos)}")
    except Exception as e:
        print(f"[QoS] Não foi possível configurar DSCP: {e}")

# ─── Servidor RTP ──────────────────────────────────────────────
def rtp_server():
    ssrc = random.randint(0, 0xFFFFFFFF)  # identificador único da fonte
    seq  = random.randint(0, 0xFFFF)      # número de sequência inicial aleatório
    timestamp = 0
    frame_duration = int(CLOCK_RATE / FPS)  # incremento de timestamp por frame

    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    set_dscp(sock, DSCP_VIDEO)

    print(f"[Servidor RTP] Iniciado | SSRC={hex(ssrc)} | Destino={SERVER_IP}:{SERVER_PORT}")
    print(f"[Servidor RTP] Chave AES={AES_KEY.hex()} | IV={AES_IV.hex()}")
    print(f"[Servidor RTP] FPS={FPS} | Clock={CLOCK_RATE}Hz | ΔTimestamp={frame_duration}\n")

    frame_count = 0
    try:
        while True:
            # Simula um frame de vídeo (em prod: captura real com OpenCV/ffmpeg)
            frame_data = bytes([frame_count % 256] * FRAME_SIZE)

            # Fragmentation: divide frame em segmentos UDP (MTU ~1400 bytes)
            mtu = 1400
            chunks = [frame_data[i:i+mtu] for i in range(0, len(frame_data), mtu)]
            total_chunks = len(chunks)

            for i, chunk in enumerate(chunks):
                marker = (i == total_chunks - 1)  # M=1 no último fragmento do frame

                # Cifra o payload (SRTP simplificado)
                encrypted_chunk = encrypt_payload(chunk)

                # Monta pacote RTP
                header  = build_rtp_header(seq, timestamp, ssrc, marker)
                packet  = header + encrypted_chunk

                sock.sendto(packet, (SERVER_IP, SERVER_PORT))

                print(f"[TX] Frame={frame_count:04d} | Frag={i+1}/{total_chunks} | "
                      f"Seq={seq} | TS={timestamp} | Marker={int(marker)} | "
                      f"Bytes={len(packet)}")

                seq = (seq + 1) & 0xFFFF  # wrap-around 16 bits

            timestamp = (timestamp + frame_duration) & 0xFFFFFFFF
            frame_count += 1
            time.sleep(1 / FPS)

    except KeyboardInterrupt:
        print("\n[Servidor RTP] Encerrado.")
    finally:
        sock.close()

if __name__ == "__main__":
    rtp_server()
