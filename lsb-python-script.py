from PIL import Image # pip install Pillow

def bits_to_bytes(bits):
    b = []
    for i in range(0, len(bits), 8):
        byte = bits[i:i+8]
        if len(byte) < 8:
            break
        val = 0
        for bit in byte:
            val = (val << 1) | int(bit)
        b.append(val)
    return bytes(b)

def extract_lsb(path, use_channels=('r','g','b')):
    im = Image.open(path).convert('RGB')
    pixels = list(im.getdata())
    bits = []
    for px in pixels:
        r,g,b = px
        if 'r' in use_channels:
            bits.append(str(r & 1))
        if 'g' in use_channels:
            bits.append(str(g & 1))
        if 'b' in use_channels:
            bits.append(str(b & 1))
    return bits

if __name__ == "__main__":
    path = input("Podaj ścieżkę do pliku: ").strip('"')
    bits = extract_lsb(path, use_channels=('r','g','b'))
    data = bits_to_bytes(bits)
    try:
        s = data.decode('utf-8', errors='ignore')
        print("\n=== Ukryty tekst (pierwsze 1000 znaków) ===\n")
        print(s[:1000])
    except:
        print("Nie udało się zdekodować tekstu.")
