import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import os

# Carregar os dados combinados
df = pd.read_csv("../output/combined_by_test.csv")

# Função para remover o melhor e pior tempo de execução por grupo
def remover_extremos(grupo):
    if len(grupo) <= 2:
        return pd.DataFrame()  # não podemos remover extremos se há <=2
    grupo_ordenado = grupo.sort_values("TimeSeconds")
    return grupo_ordenado.iloc[1:-1]  # remove o menor e o maior

# Aplicar a remoção de extremos
filtrado_df = (
    df.groupby(["Filename", "Algorithm"], group_keys=False)
    .apply(remover_extremos)
    .reset_index(drop=True)
)

# Calcular média e desvio padrão
agg_df = filtrado_df.groupby(["Filename", "DataType", "Size", "Algorithm"]).agg(
    TimeSecondsMean=("TimeSeconds", "mean"),
    TimeSecondsStd=("TimeSeconds", "std"),
    ComparisonsMean=("Comparisons", "mean"),
    ComparisonsStd=("Comparisons", "std"),
    MemoryBytesMean=("MemoryBytes", "mean"),
    MemoryBytesStd=("MemoryBytes", "std")
).reset_index()

# Salvar em novo arquivo
output_path = "../output/metrics_filtered_with_std.csv"
agg_df.to_csv(output_path, index=False)


# Carregar o arquivo com médias e desvios padrão
df = pd.read_csv(output_path)

# Criar pasta para salvar os gráficos
output_dir = "graphs"
os.makedirs(output_dir, exist_ok=True)

# Lista dos algoritmos
algoritmos = df['Algorithm'].unique()

# Gerar gráficos para cada algoritmo separadamente
for algoritmo in algoritmos:
    plt.figure(figsize=(10, 6))
    subset = df[df['Algorithm'] == algoritmo]
    sns.lineplot(data=subset, x="Size", y="TimeSecondsMean", hue="DataType", marker="o")
    # plt.title(f"Tempo Médio - {algoritmo}")
    plt.xlabel("Tamanho do Conjunto de Dados")
    plt.ylabel("Tempo (segundos)")
    plt.legend(title="Tipo de Dados", loc='upper left', bbox_to_anchor=(0, 1))
    plt.tight_layout()
    plt.savefig(f"{output_dir}/{algoritmo.lower()}_tempo_por_tipo_dado.png")
    plt.close()
    
# Gerar gráficos com barras de erro para cada algoritmo
for algoritmo in algoritmos:
    plt.figure(figsize=(10, 6))
    subset = df[df['Algorithm'] == algoritmo]
    
    # Plot com barra de erro (desvio padrão)
    sns.lineplot(
        data=subset,
        x="Size",
        y="TimeSecondsMean",
        hue="DataType",
        style="DataType",
        markers=True,
        err_style="band",
        errorbar="sd"
    )

    # plt.title(f"Tempo Médio com Desvio Padrão - {algoritmo}")
    plt.xlabel("Tamanho do Conjunto de Dados")
    plt.ylabel("Tempo (segundos)")
    plt.legend(title="Tipo de Dados", loc='upper left', bbox_to_anchor=(0, 1))
    plt.tight_layout()
    plt.savefig(f"{output_dir}/{algoritmo.lower()}_tempo_com_std_por_tipo_dado.png")
    plt.close()    

tipos_dados = df['DataType'].unique()

# Gerar um gráfico para cada tipo de dados
for tipo in tipos_dados:
    plt.figure(figsize=(10, 6))
    subset = df[df['DataType'] == tipo]
    
    # Gráfico de linha com barra de erro (std)
    sns.lineplot(
        data=subset,
        x="Size",
        y="TimeSecondsMean",
        hue="Algorithm",
        style="Algorithm",
        markers=True,
        err_style="band",
        errorbar="sd"
    )

    # plt.title(f"Tempo Médio por Algoritmo - Dados: {tipo}")
    plt.xlabel("Tamanho do Conjunto de Dados")
    plt.ylabel("Tempo (segundos)")
    plt.legend(title="Algoritmo", loc='upper left', bbox_to_anchor=(0, 1))
    plt.tight_layout()
    filename = tipo.lower().replace(" ", "_")
    plt.savefig(f"{output_dir}/tempo_comparativo_por_algoritmo_{filename}.png")
    plt.close()    