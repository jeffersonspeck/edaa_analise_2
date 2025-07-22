import pandas as pd
import os
import re

# Caminho para os arquivos CSV
folder = "../output"
csv_files = sorted([f for f in os.listdir(folder) if re.match(r'\d+_results\.csv', f)], key=lambda x: int(x.split('_')[0]))

# Lista para armazenar os dataframes
dfs = []

# Ler e adicionar coluna de teste
for file in csv_files:
    test_number = int(file.split('_')[0])
    df = pd.read_csv(os.path.join(folder, file))
    df.insert(0, 'Test', test_number)
    dfs.append(df)

# Concatenar todos os dataframes
combined_df = pd.concat(dfs, ignore_index=True)

# Salvar como novo CSV
output_path = "../output/combined_by_test.csv"
combined_df.to_csv(output_path, index=False)
output_path
