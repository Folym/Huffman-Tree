# Huffman-Tree
## Trabalho de Estruturas de Dados 2

###QUESTÃO 1)
  a) Um algoritmo para construção da árvore de Huffman (utilize uma lista encadeada 
ordenada no processo de construção da árvore). A árvore não deverá ter a palavra e sim 
um símbolo (numérico, um código). Os espaços em branco da frase também devem ser 
considerados e terá um símbolo na árvore. A frequência das palavras e dos espaços 
deverá ser contada e armazenada na lista do item b) antes de montar a árvore.

  b) Uma lista (de registos) para armazenar: o símbolo, a palavra, a frequência e os códigos 
de Huffman. Essa lista deverá ser gravada em arquivo em disco (arquivo binário), assim 
como a frase codificada (uma sequência de bits sem espaços em arquivo texto).

###QUESTÃO 2)
  a) Um algoritmo que abra os arquivos binário e texto (frase codificada), faça a decodificação 
da frase e mostre na tela. Para fazer a decodificação monte uma árvore binária a partir 
dos códigos de huffman armazenados da tabela (arquivo binário), e com varreduras na 
árvore seguindo as sequências binárias você chegará nas folhas, onde estão os códigos 
das palavras. Vá no arquivo, busque o código e pegue a palavra ou o espaço em branco, 
concatene em uma string e você terá a frase decodificada. Após ter a frase decodificada 
mostre na tela.
