## Tutorial: Compilar Projeto LaTeX do Overleaf com GitHub Actions
Este tutorial explica como configurar uma esteira (pipeline) no GitHub Actions para compilar automaticamente um projeto LaTeX baixado do Overleaf e gerar o arquivo ``.pdf`` de forma automatizada.

### Passos para configurar
1. Baixe os arquivos ``.tex`` do seu projeto no Overleaf.
2. Crie uma pasta chamada ``latex`` no repositório local e coloque todos os arquivos ``.tex``, imagens e subpastas nela.
3. Crie uma pasta ``.github`` na raiz do repositório.
4. Dentro de ``.github``, crie outra pasta chamada ``workflows``.
5. Dentro de ``workflows``, crie um arquivo YAML (por exemplo, ``compilar-latex.yml``) com o conteúdo abaixo:

#### Exemplo de arquivo compilar-latex.yml
```yml
name: Compilar LaTeX

on:
  push:
    branches: [main]
  pull_request:

jobs:
  build:
    runs-on: ubuntu-latest

    steps:
      - name: Baixar código
        uses: actions/checkout@v4

      - name: Compilar LaTeX
        uses: xu-cheng/latex-action@v3
        with:
          root_file: main.tex # arquivo principal dentro da pasta working_directory
          working_directory: latex # define a pasta onde estão main.tex e CAPITULOS

      - name: Upload do PDF como artefato
        uses: actions/upload-artifact@v4
        with:
          name: PDF-gerado
          path: latex/main.pdf

      - name: Publicar no Release
        if: startsWith(github.ref, 'refs/tags/')
        uses: softprops/action-gh-release@v2
        with:
          files: latex/main.pdf
        env:
          GITHUB_TOKEN: ${{ secrets.GITHUB_TOKEN }}
```

## Resultado
Após o commit e push do código para o repositório GitHub, a esteira será executada automaticamente. O arquivo PDF compilado será disponibilizado como artefato ou publicado no release, conforme a configuração acima.