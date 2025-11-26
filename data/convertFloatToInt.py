import os
import re

# Caminhos das pastas
input_dir = r"C:\Users\User\Desktop\code\aa\projeto-aa\data\raw\uniform"
output_dir = r"C:\Users\User\Desktop\code\aa\projeto-aa\data\raw\uniformInt"

# Cria a pasta de saída se não existir
os.makedirs(output_dir, exist_ok=True)

# Controle para evitar duplicações
inputs_processados = set()

# Regex para capturar o valor do input no nome do arquivo
padrao_input = re.compile(r"input-(\d+)-")

# Percorre todos os arquivos .txt da pasta
for filename in os.listdir(input_dir):
    if filename.endswith(".txt") and "float" in filename:

        # extrair input size do nome
        match = padrao_input.search(filename)
        if not match:
            print(f"Nome inesperado, ignorando: {filename}")
            continue

        input_size = match.group(1)

        # Caminho original
        input_path = os.path.join(input_dir, filename)

        # Se já existe um arquivo desse input convertido, deletar duplicado original e pular
        if input_size in inputs_processados:
            print(f"Duplicado detectado. Deletando arquivo original: {filename}")
            os.remove(input_path)
            continue

        # Marca como processado
        inputs_processados.add(input_size)

        # Novo nome com int
        new_filename = filename.replace("float", "int")
        output_path = os.path.join(output_dir, new_filename)

        # Lê, converte e salva
        with open(input_path, 'r') as f_in:
            content = f_in.read().split()

        int_values = [str(int(float(value))) for value in content]

        with open(output_path, 'w') as f_out:
            f_out.write("\n".join(int_values))

        print(f"Convertido (primeiro de {input_size}): {filename} -> {new_filename}")

print("Finalizado!")
